#include "multibody/tree/frame_base.h"

#include "common/default_scalars.h"

namespace drake {
namespace multibody {

template <typename T>
FrameBase<T>::~FrameBase() = default;

}  // namespace multibody
}  // namespace drake

DRAKE_DEFINE_CLASS_TEMPLATE_INSTANTIATIONS_ON_DEFAULT_SCALARS(class drake::multibody::FrameBase);
