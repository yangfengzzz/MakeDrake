#pragma once

#include <filesystem>
#include <optional>
#include <string>

#include "common/diagnostic_policy.h"
#include "geometry/geometry_properties.h"
#include "geometry/rgba.h"

namespace drake {
namespace geometry {
namespace internal {

/* Reports how UVs have been assigned to the mesh receiving a material. Textures
 should only be applied to meshes with *fully* assigned UVs. */
enum class UvState { kNone, kFull, kPartial };

/* Specifies a mesh material as currently supported by Drake. We expect this
 definition to grow with time. */
struct RenderMaterial {
    /* The diffuse appearance at a point on a geometry surface is defined by the
     channel-wise product of the `diffuse` and the image color of `diffuse_map`
     applied as a texture according to the geometry's texture coordinates. If
     `diffuse_map` is empty, it acts as the multiplicative identity. */
    Rgba diffuse;

    /* The optional texture to use as diffuse map. For universal compatibility,
     it is an image file path. However, in RenderEngine implementations that
     construct and consume their own %RenderMaterial instances, the file path
     can be replaced with an arbitrary string which the RenderEngine
     implementation knows how to map to an actual texture. Such %RenderMaterial
     instances should be kept hidden within those implementations.

     Regardless of how a non-empty string is interpreted, an empty string always
     means no diffuse map. */
    std::string diffuse_map;

    /* OpenGL defines image origin at the bottom-left corner of the texture. Some
     geometry formats (e.g., glTF), define the origin at the top-left corner.
     When set to true, the texture coordinates need to be flipped in the y
     direction for this material's texture to render correctly. */
    bool flip_y{false};

    /* Whether the material definition comes from the mesh itself, e.g., an .mtl
     file, as opposed to the user specification or an implied texture. */
    bool from_mesh_file{false};
};

/* Creates a RenderMaterial with the specified diffuse color.

 Consumers of RenderMesh can call this function to produce an untextured
 RenderMaterial with the prescribed diffuse color when presented with RenderMesh
 instances that do not come with their own material definitions.

 @param diffuse  The RGBA color to be used as the diffuse color for the
 material. */
RenderMaterial MakeDiffuseMaterial(const Rgba& diffuse);

/* Dispatches a warning to the given diagnostic policy if the props contain a
 material definition. It is assumed an intrinsic material has already been found
 for the named mesh. */
void MaybeWarnForRedundantMaterial(const GeometryProperties& props,
                                   std::string_view mesh_name,
                                   const drake::internal::DiagnosticPolicy& policy);

/* If a mesh definition doesn't include a single material (e.g., as in an .mtl
 file for an .obj mesh), this function applies a cascading priority for
 potentially defining a material. Failing everything in the priority list, it
 will return std::nullopt.

 The material is defined with the following protocol:

   - If the properties indicate a material at all, the material is derived
     purely from the properties (e.g., ("phong", "diffuse_map") and
     ("phong", "diffuse").
   - Otherwise, if an image can be located with a "compatible name" (e.g.,
     foo.png for a mesh foo.obj), a material with an unmodulated texture is
     created.
   - Otherwise, if a default_diffuse value is provided, a material is created
     with the given default_diffuse color value.
   - Finally, if no material is defined, std::nullopt is returned. In such a
     case, a consumer of the returned mesh can generate its own material using
     its default diffuse color with MakeDiffuseMaterial(). Such a material would
     be compliant with the heuristic defined in @ref geometry_materials.

 References to textures will be included in the material iff they can be read
 and the `uv_state` is full. Otherwise, a warning will be dispatched.

 @pre The mesh (named by `mesh_filename`) is a valid mesh and did not have an
      acceptable material definition). */
std::optional<RenderMaterial> MaybeMakeMeshFallbackMaterial(const GeometryProperties& props,
                                                            const std::filesystem::path& mesh_path,
                                                            const std::optional<Rgba>& default_diffuse,
                                                            const drake::internal::DiagnosticPolicy& policy,
                                                            UvState uv_state);

/* Creates a RenderMaterial from the given set of geometry properties. If no
 material properties exist, a material with the given default diffuse color is
 returned.

 If only a texture is specified, the diffuse color will be white. If the
 texture is not available, the diffuse map will be cleared, but the color will
 remain white, signaling a data error in the material specification.

 The `default_diffuse` color is only applied in the total absence of material
 properties. */
RenderMaterial DefineMaterial(const GeometryProperties& props,
                              const Rgba& default_diffuse = Rgba(1, 1, 1),
                              const drake::internal::DiagnosticPolicy& policy = {},
                              UvState uv_state = UvState::kFull);

}  // namespace internal
}  // namespace geometry
}  // namespace drake
