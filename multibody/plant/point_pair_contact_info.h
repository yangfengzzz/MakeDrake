#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "common/default_scalars.h"
#include "common/drake_copyable.h"
#include "common/eigen_types.h"
#include "geometry/query_results/penetration_as_point_pair.h"
#include "multibody/tree/multibody_tree_indexes.h"

namespace drake {
namespace multibody {

/**
 A class containing information regarding contact response between two bodies
 including:

    - The pair of bodies that are contacting, referenced by their BodyIndex.
    - A resultant contact force.
    - A contact point.
    - Separation speed.
    - Slip speed.

 @tparam_default_scalar
 */
template <typename T>
class PointPairContactInfo {
public:
    DRAKE_DEFAULT_COPY_AND_MOVE_AND_ASSIGN(PointPairContactInfo);
    /**
     Constructs the contact information for a given pair of two colliding bodies.
     @param bodyA_index
       Index that references body A in `this` contact pair.
     @param bodyB_index
       Index that references body B in `this` contact pair.
     @param f_Bc_W
       Force on body B applied at contact point C, expressed in the world frame W.
     @param p_WC
       Position of the contact point C in the world frame W.
     @param separation_speed
       Separation speed along the normal direction between body A and body B,
       in meters per second. A positive value indicates bodies are moving apart.
       A negative value indicates bodies are moving towards each other.
     @param slip_speed
       Slip speed, that is, the magnitude of the relative tangential velocity at
       the contact point in meters per second. A non-negative value always.
     @param point_pair
       Additional point pair information for `this` contact info. Refer to the
       documentation for PenetrationAsPointPair for further details. It is
       expected that the body indexed by `bodyA_index` is the same body that
       contains the geometry indexed by `point_pair.id_A`. Likewise for the body
       indexed by `bodyB_index` and the body contining geometry with id
       `point_pair.id_B`.
     @pre The two body indexes must reference bodies from the same MultibodyPlant.
     Contact values should likewise be generated by the same MultibodyPlant.
     */
    PointPairContactInfo(BodyIndex bodyA_index,
                         BodyIndex bodyB_index,
                         const Vector3<T>& f_Bc_W,
                         const Vector3<T>& p_WC,
                         const T& separation_speed,
                         const T& slip_speed,
                         const drake::geometry::PenetrationAsPointPair<T>& point_pair);

    /// Returns the index of body A in the contact pair.
    BodyIndex bodyA_index() const { return bodyA_index_; }

    /// Returns the index of body B in the contact pair.
    BodyIndex bodyB_index() const { return bodyB_index_; }

    /// Returns the contact force `f_Bc_W` on B at contact point C expressed in
    /// the world frame W.
    const Vector3<T>& contact_force() const { return f_Bc_W_; }

    /// Returns the position `p_WC` of the contact point C in the world frame W.
    const Vector3<T>& contact_point() const { return p_WC_; }

    /// Returns the slip speed between body A and B at contact point C.
    const T& slip_speed() const { return slip_speed_; }

    /// Returns the separation speed between body A and B along the normal
    /// direction (see PenetrationAsPointPair::nhat_BA_W) at the contact point.
    /// It is defined positive for bodies moving apart in the normal direction.
    const T& separation_speed() const { return separation_speed_; }

    /// Returns additional information for the geometric contact query for `this`
    /// pair as a PenetrationAsPointPair. The body containing `point_pair().id_A`
    /// is the same body indexed by `bodyA_index()`. Likewise, the body containing
    /// `point_pair().id_B` is the same body indexed by `bodyB_index()`.
    const drake::geometry::PenetrationAsPointPair<T>& point_pair() const { return point_pair_; }

private:
    // Point pair containing information regarding the geometric query for this
    // contact pair.
    drake::geometry::PenetrationAsPointPair<T> point_pair_;
    // Body associated with the geometry with identifier point_pair_.id_A.
    BodyIndex bodyA_index_;
    // Body associated with the geometry with identifier point_pair_.id_B.
    BodyIndex bodyB_index_;
    // Contact force on body B applied at the contact point C, expressed in the
    // world frame W.
    Vector3<T> f_Bc_W_;
    // Position of the contact point in the world frame.
    Vector3<T> p_WC_;
    // The separation speed, in m/s, of the contact pair. That is, the rate of
    // change of the signed distance function. That is, separation_speed_ > 0
    // when bodies are moving away from each other.
    T separation_speed_;
    // Sliding speed, the norm of the tangential velocity.
    T slip_speed_;
};

}  // namespace multibody
}  // namespace drake

DRAKE_DECLARE_CLASS_TEMPLATE_INSTANTIATIONS_ON_DEFAULT_SCALARS(class ::drake::multibody::PointPairContactInfo);
