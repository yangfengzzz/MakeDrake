r"""Utility for fixing invalid inertia data in URDF or SDFormat files, by
writing a complete, updated file.

Inertia properties for links are inferred from geometry. Only the file
supplied as an input is updated; any included or referred-to files are left
untouched. The inferred geometry for each body is determined by the first role
which has geometry defined. The roles are visited in the order specified by
--geom_inertia_role_order, whose default order is
"proximity illustration perception".

The output file should differ from the input file only by the contents of
`<inertial>` tags. It is possible that some comments may be lost within those
tags.

**Running**:

    From a Drake source build, run this as::

            bazel run //tools:fix_inertia -- --help

    From a Drake binary release (including pip releases), run this as::

            python3 -m pydrake.multibody.fix_inertia --help

    Run with output to the standard output::

            bazel run //tools:fix_inertia -- path/to/some_model.urdf

    Run with output to a separate file::

            bazel run //tools:fix_inertia -- \
                path/to/some_model.urdf output.urdf

    Run with output overwriting the input file (sometimes convenient within a
    source code control workspace)::

            bazel run //tools:fix_inertia -- --in_place path/to/some_model.urdf

    This program respects the ROS_PACKAGE_PATH; if your model uses external
    resources then you will need to set that environment variable.

**Using the results**:

    The output file will be well-formed XML and parse cleanly in Drake, but it
    may not be exactly suited to the purpose at hand. Be sure to examine the
    model file differences, and use `model_visualizer` to examine the resulting
    inertial ellipsoids.

    See `model_visualizer` documentation here:
    https://drake.mit.edu/pydrake/pydrake.visualization.model_visualizer.html

    Once the effect of the changes is clear, either use the new output file
    as-is, or merge in the desired changes using any text file merging tool.

"""

import argparse
import logging
import numpy as np
import os
from pathlib import Path

from pydrake.common import configure_logging as _configure_logging
from pydrake.multibody import _inertia_fixer

_logger = logging.getLogger("drake")


def _main():
    _configure_logging()
    geom_inertia_role_order_str_default = _inertia_fixer.role_list_to_str_list(
        _inertia_fixer.GEOM_INERTIA_ROLE_ORDER_DEFAULT
    )
    geom_role_choices_str = _inertia_fixer.role_list_to_str_list(
        _inertia_fixer.GEOM_INERTIA_ROLE_AVAILABLE
    )

    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument(
        "input_file", type=str,
        help="Filesystem path to an SDFormat or URDF file.")
    parser.add_argument(
        "output_file", type=str, nargs='?',
        help="[Optional] Filesystem path to write output with repaired"
             " inertias. If missing, output will go to stdout.")
    parser.add_argument(
        "--in_place", action="store_true",
        help="Modify the input file in-place. Any output_file argument"
             " will be ignored.")
    parser.add_argument(
        "--geom_inertia_role_order",
        type=str,
        nargs="+",
        choices=geom_role_choices_str,
        default=geom_inertia_role_order_str_default,
    )
    args = parser.parse_args()

    if 'BUILD_WORKSPACE_DIRECTORY' in os.environ:
        os.chdir(os.environ['BUILD_WORKING_DIRECTORY'])

    geom_inertia_role_order = _inertia_fixer.str_list_to_role_list(
        args.geom_inertia_role_order
    )
    fixer = _inertia_fixer.InertiaFixer(
        input_file=args.input_file,
        output_file=args.output_file,
        in_place=args.in_place,
        geom_inertia_role_order=geom_inertia_role_order,
    )
    fixer.fix_inertia()


if __name__ == "__main__":
    _main()
