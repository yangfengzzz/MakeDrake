#include "solvers/common_solver_option.h"

#include "common/drake_assert.h"

namespace drake {
namespace solvers {
std::ostream& operator<<(std::ostream& os, CommonSolverOption common_solver_option) {
    switch (common_solver_option) {
        case CommonSolverOption::kPrintFileName:
            os << "kPrintFileName";
            return os;
        case CommonSolverOption::kPrintToConsole:
            os << "kPrintToConsole";
            return os;
        case CommonSolverOption::kStandaloneReproductionFileName:
            os << "kStandaloneReproductionFileName";
            return os;
        default:
            DRAKE_UNREACHABLE();
    }
}
}  // namespace solvers
}  // namespace drake
