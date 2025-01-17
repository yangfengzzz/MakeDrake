#pragma once

#include <memory>

#include "common/drake_assert.h"
#include "common/eigen_types.h"
#include "multibody/tree/body_node.h"
#include "multibody/tree/mobilizer.h"
#include "multibody/tree/multibody_tree_topology.h"

namespace drake {
namespace multibody {
namespace internal {

// TODO(sherm1) Most of the across-mobilizer code for kinematics and
//  dynamics should live in this class since the hinge matrices
//  and related downstream calculations have a compile-time fixed size.

// For internal use only of the MultibodyTree implementation.
// While all code that is common to any node can be placed in the BodyNode
// class, %BodyNodeImpl provides compile-time fixed-size BodyNode
// implementations so that all operations can be performed with fixed-size
// stack-allocated Eigen variables. For a more detailed discussion of the role
// of a BodyNode in a MultibodyTree refer to the class documentation for
// BodyNode.
template <typename T, int num_positions, int num_velocities>
class BodyNodeImpl : public BodyNode<T> {
public:
    // static constexpr int i = 42; discouraged.  See answer in:
    // http://stackoverflow.com/questions/37259807/static-constexpr-int-vs-old-fashioned-enum-when-and-why
    enum : int { nq = num_positions, nv = num_velocities };

    // Given a body and its inboard mobilizer in a MultibodyTree this constructor
    // creates the corresponding %BodyNode. See the BodyNode class documentation
    // for details on how a BodyNode is defined.
    // @param[in] parent_node
    //   A const pointer to the parent BodyNode object in the tree structure of
    //   the owning MultibodyTree. It can be a `nullptr` only when `body` **is**
    //   the **world** body, otherwise the parent class constructor will abort.
    // @param[in] body The body B associated with `this` node.
    // @param[in] mobilizer The mobilizer associated with this `node`. It can
    //                      only be a `nullptr` for the **world** body.
    BodyNodeImpl(const internal::BodyNode<T>* parent_node, const RigidBody<T>* body, const Mobilizer<T>* mobilizer)
        : BodyNode<T>(parent_node, body, mobilizer) {}

    ~BodyNodeImpl() override;

    // TODO(amcastro-tri): Implement methods for computing velocity kinematics
    //  using fixed-size Eigen matrices.
};

}  // namespace internal
}  // namespace multibody
}  // namespace drake
