#pragma once

#include <string>
#include <vector>

#include "common/default_scalars.h"
#include "common/drake_copyable.h"
#include "common/eigen_types.h"
#include "multibody/tree/joint_actuator.h"
#include "multibody/tree/mobilizer.h"
#include "multibody/tree/multibody_element.h"
#include "multibody/tree/multibody_tree_indexes.h"

namespace drake {
namespace multibody {

/// @file
/// @anchor model_instance
/// Model instance information for multibody trees.
///
/// A MultiBodyTree is composed of a number of MultibodyElement items.  In
/// more complex trees, these items will be loaded from multiple models
/// (e.g. robot arm, attached gripper, free bodies being manipulated).  Each
/// model may have a different controller or observer, so the ability to view
/// the state or command actuation for each model independently can be useful.
/// For this reason, elements are associated with a ModelInstanceIndex to
/// determine which model an element belongs to.  In most cases, the allocation
/// of model instances and assignment of elements to the appropriate model
/// instance will be handled by the parser loading the model.
///
/// There are two special ModelElementIndex values.  The world body is always
/// ModelInstanceIndex 0, and ModelInstanceIndex 1 is reserved for all elements
/// with no explicit model instance.  This is generally only relevant for
/// elements created programmatically (and for which a model instance is not
/// explicitly specified), as model parsers should handle creating model
/// elements as needed.
///
/// For different types of MultibodyElement, the model instance is
/// sometimes specified explicitly, and sometimes inferred when the
/// element is created.  The current convention is:
///
/// * Body: Specified at creation
/// * BodyNode: Same as the associated Body
/// * Frame: Same as the associated Body
/// * Joint: Same as the child frame
/// * JointActuator: Same as the associated Joint
/// * Mobilizer:
///   * Same as the joint (if created from a joint)
///   * Same as the body (for free floating bodies)
///   * When creating mobilizers for other reasons (e.g. for unit tests) the
///     author should take care to choose a reasonable model instance.
/// * ForceElement: Depends on the type of element
///   * UniformGravityFieldElement: uses the world model instance

namespace internal {

// @tparam_default_scalar
template <typename T>
class ModelInstance final : public MultibodyElement<T> {
public:
    DRAKE_NO_COPY_NO_MOVE_NO_ASSIGN(ModelInstance);

    // Creates a new instance with the given values. The name must not be empty.
    ModelInstance(ModelInstanceIndex index, std::string name);

    ~ModelInstance();

    // Returns this element's unique index.
    ModelInstanceIndex index() const { return this->template index_impl<ModelInstanceIndex>(); }

    // Gets the `name` associated with this model instance. The name will never be
    // empty.
    const std::string& name() const { return name_; }

    // Sets the `name` associated with this model instance. The name must not be
    // empty.
    void set_name(std::string name);

    int num_positions() const { return num_positions_; }
    int num_velocities() const { return num_velocities_; }
    int num_states() const { return num_positions_ + num_velocities_; }
    int num_actuators() const { return joint_actuators_.size(); }
    int num_actuated_dofs() const { return num_actuated_dofs_; }

    void add_mobilizer(const Mobilizer<T>* mobilizer) {
        num_positions_ += mobilizer->num_positions();
        num_velocities_ += mobilizer->num_velocities();
        mobilizers_.push_back(mobilizer);
    }

    // Adds an actuator to this model instance. Actuators must be added in
    // monotonically increasing order of JointActuatorIndex (or else throws).
    void add_joint_actuator(const JointActuator<T>* joint_actuator) {
        DRAKE_THROW_UNLESS(joint_actuator != nullptr);
        num_actuated_dofs_ += joint_actuator->joint().num_velocities();
        // Verify the documented requirement.
        DRAKE_THROW_UNLESS(joint_actuators_.empty() || joint_actuators_.back()->index() < joint_actuator->index());
        joint_actuators_.push_back(joint_actuator);
    }

    // Returns a vector of JointActuatorIndex for this model instance. Within the
    // returned vector, actuator indexes are sorted in ascending order.
    std::vector<JointActuatorIndex> GetJointActuatorIndices() const;

    std::vector<JointIndex> GetActuatedJointIndices() const;

    // Returns the actuation for `this` model instance extracted from `u`.
    // @param[in] u Actuation for the full plant model, ordered by monotonically
    // increasing JointActuatorIndex (see
    // MultibodyPlant::get_actuation_input_port()).
    // @returns the per model instance actuation, order by monotonically
    // increasing JointActuatorIndex within this model instance.
    // @throws std::exception if `u` is not of size
    //         MultibodyTree::num_actuators().
    VectorX<T> GetActuationFromArray(const Eigen::Ref<const VectorX<T>>& u) const;

    // Given the actuation values `u_instance` for all actuators in `this` model
    // instance, updates the portion of the actuation vector `u` corresponding to
    // the actuators for this model instance.
    // @param[in] u_instance Actuation values for this model instance. It must be
    //   of size equal to the number of degrees of freedom of all of the actuated
    //   joints in this model instance. It is ordered by monotonically increasing
    //   JointActuatorIndex within this model instance (see
    //   MultibodyPlant::get_actuation_input_port()).
    // @param[in,out] u Actuation values for the entire plant model to which
    //   `this` actuator belongs (ordered by monotonically increasing
    //   JointActuatorIndex). It must be of size equal to the number of degrees of
    //   freedom of all of the actuated joints in the entire MultibodyTree model.
    //   Only values corresponding to this model instance are updated.
    // @throws std::exception if `u_instance` is not of size equal to the number
    //   of degrees of freedom of all of the actuated joints in this model or `u`
    //   is not of size equal to the number of degrees of freedom of all of the
    //   actuated joints in the entire MultibodyTree model to which `this`
    //   actuator belongs to.
    void SetActuationInArray(const Eigen::Ref<const VectorX<T>>& u_instance, EigenPtr<VectorX<T>> u) const;

    // Returns an Eigen vector of the generalized positions
    // for `this` model instance from a vector `q` of generalized
    // positions for the entire MultibodyTree model.
    // @throws std::exception if `q` is not of size
    //         MultibodyTree::num_positions().
    VectorX<T> GetPositionsFromArray(const Eigen::Ref<const VectorX<T>>& q) const;

    // (Advanced) Takes an output vector q_out and populates it with the
    // generalized positions for `this` model instance from a vector `q` of
    // generalized positions for the entire MultibodyTree model.
    // @throws std::exception if `q` is not of size
    //         MultibodyTree::num_positions().
    void GetPositionsFromArray(const Eigen::Ref<const VectorX<T>>& q, EigenPtr<VectorX<T>> q_out) const;

    // Sets the vector of generalized positions for `this` model instance in
    // the relevant locations of an array that corresponds to the positions for
    // the entire MultibodyTree model. Elements of the array that do not
    // correspond to `this` are not altered. Note that calling
    // `SetPositionsInArray(q_instance, q)` causes
    // `GetPositionsFromArray(q)` to yield `q_instance`.
    // @throws std::exception if `q` is not of size
    //         MultibodyTree::num_positions() or `q_instance` is not of size
    //         num_positions().
    void SetPositionsInArray(const Eigen::Ref<const VectorX<T>>& q_instance, EigenPtr<VectorX<T>> q) const;

    // Returns an Eigen vector of the generalized velocities
    // for `this` mobilizer from a vector `v` of generalized velocities for
    // the entire MultibodyTree model.
    // @throws std::exception if `v` is not of size
    //         MultibodyTree::num_velocities().
    VectorX<T> GetVelocitiesFromArray(const Eigen::Ref<const VectorX<T>>& v) const;

    // (Advanced) Takes an output vector v_out and populates with the generalized
    // velocities for `this` model instance from a vector `v` of
    // generalized velocities for the entire MultibodyTree model.
    // @throws std::exception if `v` is not of size
    //         MultibodyTree::num_velocities().
    void GetVelocitiesFromArray(const Eigen::Ref<const VectorX<T>>& v, EigenPtr<VectorX<T>> v_out) const;

    // Sets the vector of generalized velocities for `this` model instance in
    // the relevant locations of an array corresponding to the velocities for the
    // entire MultibodyTree model. Elements of the array that do not
    // correspond to `this` are not altered. Note that calling
    // `SetVelocitiesInArray(v_instance, v)` causes
    // `GetVelocitiesFromArray(v)` to yield `v_instance`.
    // @throws std::exception if `v` is not of size
    //         MultibodyTree::num_velocities() or `v_instance` is not of size
    //         num_velocities().
    void SetVelocitiesInArray(const Eigen::Ref<const VectorX<T>>& v_instance, EigenPtr<VectorX<T>> v) const;

private:
    void DoSetTopology(const MultibodyTreeTopology&) final {}

    std::string name_;

    int num_positions_{0};
    int num_velocities_{0};
    int num_actuated_dofs_{0};

    std::vector<const Mobilizer<T>*> mobilizers_;
    std::vector<const JointActuator<T>*> joint_actuators_;
};

}  // namespace internal
}  // namespace multibody
}  // namespace drake

DRAKE_DECLARE_CLASS_TEMPLATE_INSTANTIATIONS_ON_DEFAULT_SCALARS(class ::drake::multibody::internal::ModelInstance);
