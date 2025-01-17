import logging
import numpy as np
from pathlib import Path
import xml.etree.ElementTree

from pydrake.geometry import (
    ReadObjToTriangleSurfaceMesh,
)
from pydrake.multibody.tree import (
    CalcSpatialInertia,
    SpatialInertia,
)

_logger = logging.getLogger("drake")

_PACKAGE_TEMPLATE = """
<?xml version="1.0"?>
<package format="2">
  <name>{name}</name>
  <version>0.0.0</version>
  <description>
    Package generated by mesh_to_model from mesh file: {mesh_name}.
  </description>
  <maintainer email="nobody@example.com">Nobody</maintainer>
  <license>unknown</license>
</package>
"""

_SDF_TEMPLATE = """<?xml version='1.0'?>
<sdf xmlns:drake="http://drake.mit.edu" version="1.8">
  <model name='{name}'>
    <link name='{name}'>
      <inertial>
        <pose>{inertial_pose}</pose>
        <mass>{mass}</mass>
        <inertia>
          <ixx>{ixx}</ixx>
          <ixy>{ixy}</ixy>
          <ixz>{ixz}</ixz>
          <iyy>{iyy}</iyy>
          <iyz>{iyz}</iyz>
          <izz>{izz}</izz>
        </inertia>
      </inertial>
      <visual name='visual'>
        <pose>{geometry_position} 0 0 0</pose>
        <geometry>
          <mesh>
            <uri>{mesh_uri}</uri>
            <scale>{mesh_scale}</scale>
          </mesh>
        </geometry>
      </visual>
      <collision name='collision'>
        <pose>{geometry_position} 0 0 0</pose>
        <geometry>
          <mesh>
            <uri>{mesh_uri}</uri>
            <scale>{mesh_scale}</scale>
          </mesh>
        </geometry>
        <!-- The proximity properties immediately below enable the hydroelastic
             contact model for this body. To use point contact instead, delete
             or comment out the <drake:rigid_hydroelastic> element. -->
        <drake:proximity_properties>
          <drake:mu_dynamic>0.5</drake:mu_dynamic>
          <drake:mu_static>0.5</drake:mu_static>
          <drake:rigid_hydroelastic/>
        </drake:proximity_properties>
      </collision>
    </link>
  </model>
</sdf>
"""


class MeshModelMaker:
    """Converts a mesh file into a model, documenting the work as it goes."""

    def __init__(self, *,
                 mesh_path: Path,
                 output_dir: Path = None,
                 scale: float = 1.0,
                 model_name: str = None,
                 density: float = 1000.0,
                 mass: float = None,
                 at_com: bool = False,
                 p_GoBo: np.array = None,
                 encoded_package: str = 'none'):
        """
        Read the given mesh definition and construct a corresponding SDFormat
        file representing a single model with a single body. The body's mass
        properties are inferred from the volume enclosed by the mesh.

        For more details, read the documentation in mesh_to_model.py.

        Either ``density`` or ``mass`` defines how the mass is specified. At
        least one must be provided. If mass is provided, it will be used and
        density will be ignored.

        ``at_com`` and ``p_GoBo`` control the relative position of the
        geometry and body frames. There are three options:
        - Body origin at geometry origin (at_com=False, p_GoBo=None).
        - Body origin at geometry center of mass (at_com=True, p_GoBo=None).
        - Body origin at arbitrary point (measured and expressed in geometry
          frame) (at_com=False, p_GoBo=[x_cm, y_cm, z_cm]).
        It is an error to define at_com=True and p_GoBo not None.

        If ``output_dir`` is not None, it must name a valid directory.
        """
        if density is None and mass is None:
            raise ValueError("Neither mass nor density were provided.")
        if density is not None and mass is not None:
            density = None
        if at_com and p_GoBo is not None:
            raise ValueError("Specify either at_com=True or p_GoBo, not both.")
        if output_dir is None:
            output_dir = None if mesh_path is None else mesh_path.parent
        elif not output_dir.is_dir():
            raise ValueError("The output directory must name an existing "
                             f"directory; given {output_dir}.")
        self.mesh_path = mesh_path
        self.output_dir = output_dir
        self.scale = scale
        self.model_name = model_name
        self.density = density
        self.mass = mass
        self.at_com = at_com
        self.p_GoBo = p_GoBo
        self.encoded_package = encoded_package

    def make_model(self):
        """
        Creates a model from the mesh given at mesh_path and writes the
        corresponding model to the file at model_path based on the maker's
        configurations.

        See the documentation for mesh_to_model.py for a discussion of the
        configuration parameters.
        """
        _logger.info(f"Creating a model from: {self.mesh_path}")

        # Figure out the mesh URI and model names.
        mesh_uri = MeshModelMaker._make_mesh_uri(self.encoded_package,
                                                 self.mesh_path)

        if self.scale <= 0:
            raise ValueError(
                f"Scale value must be positive, given {self.scale}.")

        mesh_G = ReadObjToTriangleSurfaceMesh(filename=str(self.mesh_path),
                                              scale=self.scale)
        p_GoMin, p_GoMax = mesh_G.CalcBoundingBox()
        size = p_GoMax - p_GoMin
        _logger.info("Mesh-model summary:")
        _logger.info(f"    Bounding box (in geometry frame): {size[0]} x "
                     f"{size[1]} x {size[2]} meters")

        # TODO(SeanCurtis-TRI): Confirm that the mesh is watertight.

        if self.mass is not None:
            # If mass is defined, it wins.
            # Neither the unit inertia nor the center of mass depend on the
            # density. So, we can compute those quantities for an arbitrary
            # density and then reconfigure the SpatialInertia with the desired
            # mass.
            density = 1.0
            M_GGo_G = CalcSpatialInertia(mesh=mesh_G, density=density)
            volume = M_GGo_G.get_mass() / density
            M_GGo_G = SpatialInertia(mass=self.mass,
                                     p_PScm_E=M_GGo_G.get_com(),
                                     G_SP_E=M_GGo_G.get_unit_inertia())
        else:
            M_GGo_G = CalcSpatialInertia(mesh=mesh_G,
                                         density=self.density)
            volume = M_GGo_G.get_mass() / self.density

        p_GoGcm = M_GGo_G.get_com()
        M_GGcm_G = M_GGo_G.Shift(p_GoGcm)
        mass = M_GGo_G.get_mass()

        _logger.info(f"    Mass: {mass} kg")

        if self.p_GoBo is None:
            if self.at_com:
                p_BoGo = -p_GoGcm
                p_BoBcm = (0.0, 0.0, 0.0)
            else:
                # Default case.
                p_BoGo = (0.0, 0.0, 0.0)
                p_BoBcm = p_GoGcm
        else:
            p_BoGo = -self.p_GoBo
            p_BoBcm = p_GoGcm - self.p_GoBo

        _logger.info(f"    p_GoGcm: [{p_GoGcm[0]}, {p_GoGcm[1]}, "
                     f"{p_GoGcm[2]}]")
        _logger.info(f"    p_BoBcm: [{p_BoBcm[0]}, {p_BoBcm[1]}, "
                     f"{p_BoBcm[2]}]")

        # The Empire State building conveniently exemplifies 1e6 cubic meters.
        # https://en.wikipedia.org/wiki/Empire_State_Building#Interior
        huge_volume = 1e6
        if volume > huge_volume:
            _logger.warning(f"Mesh volume [{volume} m³] exceeds the volume"
                            f" of the Empire State Building"
                            f" [{huge_volume} m³]. Consider using the"
                            f" --scale option.")

        # Medium sand tops out at 0.5 mm diameter, leading to the approximate
        # volume shown below.
        # https://en.wikipedia.org/wiki/Grain_size
        tiny_volume = 6e-11
        if volume < tiny_volume:
            _logger.warning(f"Mesh volume [{volume} m³] is smaller than the"
                            f" volume of a grain of sand [{tiny_volume} m³]."
                            f" Consider using the --scale option.")

        # In SDF files, the inertia tensor is always reported around the center
        # of mass.
        I_GGcm_G = M_GGcm_G.CalcRotationalInertia()
        moments = I_GGcm_G.get_moments()
        products = I_GGcm_G.get_products()

        subs = dict()
        # model_name is None *or* model_name == "" prefers mesh_stem.
        subs["name"] = self.model_name or self.mesh_path.stem
        # With zero rotation, this is simply the position of com in B.
        p_BoBcm_str = " ".join([str(x) for x in p_BoBcm])
        subs["inertial_pose"] = f"{p_BoBcm_str} 0 0 0"
        subs["mass"] = mass
        subs["ixx"] = moments[0]
        subs["iyy"] = moments[1]
        subs["izz"] = moments[2]
        subs["ixy"] = products[0]
        subs["ixz"] = products[1]
        subs["iyz"] = products[2]
        subs["mesh_uri"] = mesh_uri
        subs["mesh_scale"] = "{s} {s} {s}".format(s=self.scale)
        subs["geometry_position"] = " ".join([str(x) for x in p_BoGo])

        output_path = self.output_dir / f"{self.mesh_path.stem}.sdf"
        with open(output_path, "w") as f:
            f.write(_SDF_TEMPLATE.format(**subs))

    @staticmethod
    def _make_mesh_uri(package_spec: str, mesh_path: Path):
        """
        Given an encoded package protocol and path to the mesh, creates the
        uri to be used. May create a package.xml file in the same directory as
        the mesh file (depending on the value of package_spec).

        If package_spec contains the path to a package.xml file, that file must
        be located in an ancestor directory of the mesh file.

        Args:
            package_spec: Can be one of "none", "auto", or a path to a
                package.xml file.
            mesh_path: The path to the mesh file being processed. Used if
                package_spec is not "none". A package.xml file in that
                directory will be used or created.

        Returns:
            A string representing the uri to use the SDFormat file to reference
            the mesh.
        """
        mesh_name = mesh_path.name

        if package_spec == "none":
            return mesh_name

        package_path = None
        if package_spec.endswith("package.xml"):
            # The mesh must lie in the tree rooted at the package.
            package_spec = Path(package_spec)
            if not package_spec.exists():
                raise ValueError(
                    "The indicated package.xml cannot be found: "
                    f"'{package_spec}'")
            abs_package = package_spec.resolve().absolute()
            abs_mesh = mesh_path.resolve().absolute()
            try:
                mesh_rel_path = abs_mesh.relative_to(abs_package.parent)
            except ValueError:
                raise ValueError(
                    "When specifying the package, the mesh must be located in "
                    f"the file tree of the package.\n  package: {abs_package}"
                    f"\n  mesh: {abs_mesh}")
            package_name = MeshModelMaker._read_package_name(package_spec)
            package_path = f"package://{package_name}/{mesh_rel_path}"

        if package_spec == "auto":
            mesh_dir = mesh_path.resolve().absolute().parent
            candidate_package_path = mesh_dir / "package.xml"
            if candidate_package_path.exists():
                package_name = MeshModelMaker._read_package_name(
                    candidate_package_path)
            else:
                # The name of the *package* is the name of the mesh file's
                # directory.
                package_name = mesh_dir.name
                subs = {"name": package_name, "mesh_name": mesh_name}
                with open(candidate_package_path, "w") as f:
                    f.write(_PACKAGE_TEMPLATE.format(**subs))
            package_path = f"package://{package_name}/{mesh_name}"

        if package_path is not None:
            return package_path

        raise ValueError(
            f"Unrecognized package specification: '{package_spec}'.")

    @staticmethod
    def _read_package_name(package_path: Path):
        """
        Reads the ROS package manifest file at the given path, returning the
        value of the name tag.
        """
        root = xml.etree.ElementTree.parse(package_path).getroot()
        name_element = root.find("name")
        if name_element is None:
            raise ValueError("The provided package.xml is missing a 'name' "
                             f"element: {package_path}.")
        return name_element.text.strip()
