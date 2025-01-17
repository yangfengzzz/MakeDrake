#pragma once

#include <ostream>

#include "common/fmt_ostream.h"

namespace drake {
namespace solvers {
/**
 * Some options can be applied to not one solver, but many solvers (for example,
 * many solvers support printing out the progress in each iteration).
 * CommonSolverOption contain the names of these supported options.
 * The user can use these options as "key" in SolverOption::SetOption().
 */
enum class CommonSolverOption {
    /** Many solvers support printing the progress of each iteration to a file.
     * The user can call SolverOptions::SetOption(kPrintFileName, file_name) where
     * file_name is a string. If the user doesn't want to print to a file, then
     * use SolverOptions::SetOption(kPrintFileName, ""), where the empty string ""
     * indicates no print.
     */
    kPrintFileName,
    /** Many solvers support printing the progress of each iteration to the
     * console, the user can call SolverOptions::SetOption(kPrintToConsole, 1) to
     * turn on printing to the console, or
     * SolverOptions::SetOption(kPrintToConsole, 0) to turn off printing to the
     * console.
     */
    kPrintToConsole,
    /** Some of our solver interfaces support writing a standalone (e.g. it does
     * not depend on Drake) minimal reproduction of the problem to a file. This is
     * especially useful for sending bug reports upstream to the developers of the
     * solver. To enable this, use e.g.
     * SolverOptions::SetOption(kStandaloneReproductionFileName,
     * "reproduction.txt"). To disable, use
     * SolverOptions::SetOption(kStandaloneReproductionFileName, ""), where the
     * empty string "" indicates that no file should be written.
     */
    kStandaloneReproductionFileName,
};

std::ostream& operator<<(std::ostream& os, CommonSolverOption common_solver_option);
}  // namespace solvers
}  // namespace drake

// TODO(jwnimmer-tri) Add a real formatter and deprecate the operator<<.
namespace fmt {
template <>
struct formatter<drake::solvers::CommonSolverOption> : drake::ostream_formatter {};
}  // namespace fmt
