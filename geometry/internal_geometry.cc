#include "geometry/internal_geometry.h"

#include <memory>

#include "common/drake_assert.h"
#include "geometry/make_mesh_for_deformable.h"

namespace drake {
namespace geometry {
namespace internal {

using math::RigidTransform;

InternalGeometry::InternalGeometry(SourceId source_id,
                                   std::unique_ptr<Shape> shape,
                                   FrameId frame_id,
                                   GeometryId geometry_id,
                                   std::string name,
                                   RigidTransform<double> X_FG)
    : shape_spec_(std::move(shape)),
      id_(geometry_id),
      name_(std::move(name)),
      source_id_(source_id),
      frame_id_(frame_id),
      X_FG_(std::move(X_FG)) {}

InternalGeometry::InternalGeometry(SourceId source_id,
                                   std::unique_ptr<Shape> shape,
                                   FrameId frame_id,
                                   GeometryId geometry_id,
                                   std::string name,
                                   RigidTransform<double> X_FG,
                                   double resolution_hint)
    : shape_spec_(std::move(shape)),
      id_(geometry_id),
      name_(std::move(name)),
      source_id_(source_id),
      frame_id_(frame_id),
      X_FG_(std::move(X_FG)) {
    // The function creates the mesh in frame G.
    reference_mesh_ = MakeMeshForDeformable(*shape_spec_, resolution_hint);
}

bool InternalGeometry::has_role(Role role) const {
    switch (role) {
        case Role::kProximity:
            return has_proximity_role();
        case Role::kIllustration:
            return has_illustration_role();
        case Role::kPerception:
            return has_perception_role();
        case Role::kUnassigned:
            return !(has_proximity_role() || has_perception_role() || has_illustration_role());
    }
    DRAKE_UNREACHABLE();
}

const GeometryProperties* InternalGeometry::properties(Role role) const {
    switch (role) {
        case Role::kUnassigned:
            return nullptr;
        case Role::kProximity:
            return proximity_properties();
            break;
        case Role::kIllustration:
            return illustration_properties();
            break;
        case Role::kPerception:
            return perception_properties();
            break;
    }
    DRAKE_UNREACHABLE();
}

}  // namespace internal
}  // namespace geometry
}  // namespace drake
