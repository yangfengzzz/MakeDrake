#include "solvers/solution_result.h"

namespace drake {
namespace solvers {
std::string to_string(SolutionResult solution_result) {
    switch (solution_result) {
        case SolutionResult::kSolutionFound:
            return "SolutionFound";
        case SolutionResult::kInvalidInput:
            return "InvalidInput";
        case SolutionResult::kInfeasibleConstraints:
            return "InfeasibleConstraints";
        case SolutionResult::kUnbounded:
            return "Unbounded";
        case SolutionResult::kInfeasibleOrUnbounded:
            return "InfeasibleOrUnbounded";
        case SolutionResult::kIterationLimit:
            return "IterationLimit";
        case SolutionResult::kSolverSpecificError:
            return "SolverSpecificError";
        case SolutionResult::kDualInfeasible:
            return "DualInfeasible";
        case SolutionResult::kSolutionResultNotSet:
            return "SolutionResultNotSet";
    }
    // The following lines should not be reached, we add this line due to a defect
    // in the compiler.
    throw std::runtime_error("Should not reach here");
}

std::ostream& operator<<(std::ostream& os, SolutionResult solution_result) {
    os << to_string(solution_result);
    return os;
}
}  // namespace solvers
}  // namespace drake
