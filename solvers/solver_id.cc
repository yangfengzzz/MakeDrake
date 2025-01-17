#include "solvers/solver_id.h"

#include <atomic>
#include <utility>

#include "common/never_destroyed.h"
#include "common/text_logging.h"

namespace drake {
namespace solvers {
namespace {

int get_next_id() {
    // Note that id 0 is reserved for the moved-from SolverId.  As a result, we
    // have an invariant "get_next_id() > 0".
    static never_destroyed<std::atomic<int>> next_id{1};
    return next_id.access()++;
}

}  // namespace

SolverId::SolverId(std::string name) : id_{get_next_id()}, name_{std::move(name)} {
    if (name_.length() > 15) {
        static const logging::Warn log_once("The SolverId(name='{}') exceeds the recommended name length of 15.",
                                            name_);
    }
}

bool operator==(const SolverId& a, const SolverId& b) {
    return a.id_ == b.id_;
}

bool operator!=(const SolverId& a, const SolverId& b) {
    return a.id_ != b.id_;
}

std::ostream& operator<<(std::ostream& os, const SolverId& self) {
    // N.B. The ID is _not_ exposed to callers.
    os << self.name();
    return os;
}

}  // namespace solvers
}  // namespace drake
