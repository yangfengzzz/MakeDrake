#pragma once

#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/drake_copyable.h"
#include "common/sorted_pair.h"
#include "multibody/tree/multibody_tree_indexes.h"

namespace drake {
namespace multibody {
namespace internal {

/* Type used to identify joint types. */
using JointTypeIndex = TypeSafeIndex<class JointTypeTag>;

/* Defines a multibody graph consisting of rigid bodies interconnected by
joints. The graph is defined by a sequence of calls to AddRigidBody() and
AddJoint(). Anytime during the lifetime of the graph, a user can ask graph
specific questions such as how bodies are connected, by which joints or even
perform more complex queries such as what set of bodies are welded together. */
// TODO(amcastro-tri): consider moving outside internal:: and available to users
// of MBP, towards #11307.
class MultibodyGraph {
public:
    // We can't use the DRAKE_DEFAULT_COPY... macro for this class; see below for
    // the declarations of the copy, assign, and move functions.

    // The classes are defined later on in this header file.
    class RigidBody;
    class Joint;

    MultibodyGraph();

    // Because we use vectors of forward-declared classes (e.g.,
    // vector<RigidBody>) as member fields, we can only _declare_ our default
    // copyable functions here; we must _define_ them only after MbG::RigidBody
    // and MbG::Joint are defined, i.e., in our *.cc file.
    MultibodyGraph(const MultibodyGraph&);
    MultibodyGraph& operator=(const MultibodyGraph&);
    MultibodyGraph(MultibodyGraph&&);
    MultibodyGraph& operator=(MultibodyGraph&&);

    /* Add a new RigidBody to the graph.
    @param[in] name
      The unique name of the new body in the particular `model_instance`. Several
      bodies can have the same name within a %MultibodyGraph however, their name
      within their model instance must be unique.
    @param[in] model_instance
      The model instance to which this body belongs, see @ref model_instance.
    @note The first call to AddRigidBody() defines the "world" body's `name`. For
    this first call `model_instance` must be world_model_instance().
    @returns The unique BodyIndex for the added joint in the graph. */
    BodyIndex AddRigidBody(const std::string& name, ModelInstanceIndex model_instance);

    /* Add a new Joint to the graph.
    @param[in] name
      The unique name of the new Joint in the particular `model_instance`. Several
      joints can have the same name within a %MultibodyGraph however, their name
      within their model instance must be unique.
    @param[in] model_instance
      The model instance to which this joint belongs, see @ref model_instance.
    @param[in] type
      A string designating the type of this joint, such as "revolute" or
      "ball". This must be chosen from the set of joint types previously
      registered with calls to RegisterJointType().
    @param[in] parent_body_index
      This must be the index of a body previously obtained with a call to
      AddRigidBody(), or it must be the designated index for the world body
      (world_index()).
    @param[in] child_body_index
      This must be the index of a body previously obtained with a call to
      AddRigidBody(), or it must be the designated index for the world body
      (world_index()).
    @returns The unique JointIndex for the added joint in the graph.
    @throws std::exception iff `name` is duplicated within `model_instance`.
    @throws std::exception iff `type` has not been registered with
    RegisterJointType().
    @throws std::exception iff `parent_body_index` or `child_body_index` are
    not valid body indexes for `this` graph. */
    JointIndex AddJoint(const std::string& name,
                        ModelInstanceIndex model_instance,
                        const std::string& type,
                        BodyIndex parent_body_index,
                        BodyIndex child_body_index);

    // Removes the Joint with index `joint_index` from the graph.
    // @throws std::exception if has_joint(joint_index) == false.
    void RemoveJoint(JointIndex joint_index);

    /* Returns the body that corresponds to the world. This body added via the
    first call to AddRigidBody().
    @throws std::exception iff AddRigidBody() was not called even once yet. */
    const RigidBody& world_body() const;

    /* Returns the name we recognize as the World (or Ground) body. This is
    the name that was provided in the first AddRigidBody() call.
    In Drake, MultibodyPlant names it the "world".
    @throws std::exception iff AddRigidBody() was not called even once yet. */
    const std::string& world_body_name() const;

    /* Returns the unique index that identifies the "weld" joint type (always
    zero).
    @note The SDF format calls this type a "fixed" joint. */
    static JointTypeIndex weld_type_index() { return JointTypeIndex(0); }

    /* Returns the unique name reserved to identify weld joints (always "weld").
     */
    static std::string weld_type_name() { return "weld"; }

    /* Register a joint type by name.
    MultibodyGraph() registers "weld" at construction as Drake reserves this name
    to identify weld joints. "weld" joint type has index `weld_type_index()`.
    @param[in] joint_type_name
      A unique string identifying a joint type, such as "pin" or "prismatic".
    @throws std::exception if `joint_type_name` already identifies a
    previously registered joint type.
    @retval JointTypeIndex Index uniquely identifying the new joint type. */
    JointTypeIndex RegisterJointType(const std::string& joint_type_name);

    /* @returns `true` iff the given `joint_type_name` was previously registered
    via a call to RegisterJointType(), or iff it equals weld_type_name(). */
    bool IsJointTypeRegistered(const std::string& joint_type_name) const;

    /* Returns the number of registered joint types. */
    int num_joint_types() const;

    /* Returns the number of bodies, including all added bodies, and the world
    body.
    @see AddRigidBody(), world_index(), world_body_name(). */
    int num_bodies() const;

    /** Returns the number joints. */
    int num_joints() const;

    /* Gets a RigidBody by index. The world body has index world_index().
    @throws std::exception iff `index` does not correspond to a body in this
    graph. */
    const RigidBody& get_body(BodyIndex index) const;

    /* Returns whether this graph contains a joint with index `joint_index`. */
    bool has_joint(JointIndex joint_index) const;

    /* Gets a Joint by index.
    @throws std::exception iff `index` does not correspond to a joint in this
    graph. */
    const Joint& get_joint(JointIndex index) const;

    /* @returns `true` if a body named `name` was added to `model_instance`.
    @see AddRigidBody().
    @throws std::exception if `model_instance` is not a valid index. */
    bool HasBodyNamed(const std::string& name, ModelInstanceIndex model_instance) const;

    /* @returns `true` if a joint named `name` was added to `model_instance`.
    @see AddRigidBody().
    @throws std::exception if `model_instance` is not a valid index. */
    bool HasJointNamed(const std::string& name, ModelInstanceIndex model_instance) const;

    /* This method partitions the %MultibodyGraph into sub-graphs such that (a)
    every body is in one and only one sub-graph, and (b) two bodies are in the
    same sub-graph iff there is a path between them which includes only weld
    joints (see weld_type_name()). Each sub-graph of welded bodies is represented
    as a set of body indices. By definition, these sub-graphs will be disconnected
    by any non-weld joint between two bodies. The first sub-graph will have all of
    the bodies welded to the world, including the world body itself; all
    subsequent sub-graphs will be in no particular order. A few more notes:
      - Each body in the %MultibodyGraph is included in one set and one set only.
      - The maximum number of returned sub-graphs equals the number of bodies in
        the graph (num_bodies()). This corresponds to a graph with no weld joints.
      - The world body is also included in a set of welded bodies, and this set is
        element zero in the returned vector.
      - The minimum number of sub-graphs is one. This corresponds to a graph with
        all bodies welded to the world. */
    std::vector<std::set<BodyIndex>> FindSubgraphsOfWeldedBodies() const;

    /* Returns all bodies that are transitively welded, or rigidly affixed, to
    `body_index`, per these two definitions:
      1. A body is always considered welded to itself.
      2. Two unique bodies are considered welded together exclusively by the
         presence of a weld joint, not by other constructs such as constraints.
    Therefore, if `body_index` is a valid index to a RigidBody in this graph, then
    the return vector will always contain at least one entry storing `body_index`.
    @throws std::exception iff `body_index` does not correspond to a body in this
    graph. */
    std::set<BodyIndex> FindBodiesWeldedTo(BodyIndex body_index) const;

private:
    // Finds the assigned index for a joint type from the type name. Returns an
    // invalid index if `joint_type_name` was not previously registered with a
    // call to RegisterJointType().
    JointTypeIndex GetJointTypeIndex(const std::string& joint_type_name) const;

    RigidBody& get_mutable_body(BodyIndex body_index);

    // Recursive helper method for FindSubgraphsOfWeldedBodies().
    // The first thing this helper does is to mark `parent_body` as "visited" in
    // the output array `visited`.
    // Next, it scans the sibling bodies connected to `parent_index` by a joint.
    // If the sibling was already visited, it moves on to the next sibling, if
    // any. For a sibling visited for the first time there are two options:
    //   1) if it is connected by a weld joint, it gets added to parent_subgraph.
    //      Recursion continues starting with parent_index = sibling and the
    //      parent sub-graph. Otherwise,
    //   2) a new sub-graph is created for the sibling and gets added to the
    //      list of all `subgraphs`. Recursion continues starting with
    //      parent_index = sibling and the new sub-graph for this sibling.
    void FindSubgraphsOfWeldedBodiesRecurse(const RigidBody& parent_body,
                                            std::set<BodyIndex>* parent_subgraph,
                                            std::vector<std::set<BodyIndex>>* subgraphs,
                                            std::vector<bool>* visited) const;

    // bodies_ includes the world body at world_index() with name
    // world_body_name().
    std::vector<RigidBody> bodies_;
    // Stores the joints in the graph at their JointIndex. If a nullopt value is
    // found at index i, then the joint with index i was removed from the graph.
    std::vector<std::optional<Joint>> joints_;

    // Keeps track of the number of non-nullopt entries in `joints_`
    int num_joints_{0};

    std::unordered_map<std::string, JointTypeIndex> joint_type_name_to_index_;

    // Map used to detect redundant joints.
    using BodiesKey = SortedPair<BodyIndex>;
    std::unordered_map<BodiesKey, JointIndex> bodies_to_joint_;

    // The xxx_name_to_index_ structures are multimaps because
    // bodies/joints/actuators/etc may appear with the same name in different
    // model instances. The index values are still unique across the graph.
    std::unordered_multimap<std::string, BodyIndex> body_name_to_index_;
    std::unordered_multimap<std::string, JointIndex> joint_name_to_index_;
};

class MultibodyGraph::RigidBody {
public:
    DRAKE_DEFAULT_COPY_AND_MOVE_AND_ASSIGN(RigidBody);

    /* @returns its unique index in the graph. */
    BodyIndex index() const { return index_; }

    /* @returns its model instance. */
    ModelInstanceIndex model_instance() const { return model_instance_; }

    /* @returns its name, unique within model_instance(). */
    const std::string& name() const { return name_; }

    /* @returns all the joints that connect to `this` body. */
    const std::vector<JointIndex>& joints() const { return joints_; }

private:
    // Restrict construction and modification to only MultibodyGraph.
    friend class MultibodyGraph;

    RigidBody(BodyIndex index, const std::string& name, ModelInstanceIndex model_instance)
        : index_(index), name_(name), model_instance_(model_instance) {}

    // Notes that this body is connected by `joint`.
    void add_joint(JointIndex joint) { joints_.push_back(joint); }

    void RemoveJoint(JointIndex joint) { std::erase(joints_, joint); }

    BodyIndex index_;
    std::string name_;
    ModelInstanceIndex model_instance_;

    // All joints connecting this body. The union (in no particular order) of
    // joints_as_parent_ and joints_as_child_.
    std::vector<JointIndex> joints_;
};

class MultibodyGraph::Joint {
public:
    DRAKE_DEFAULT_COPY_AND_MOVE_AND_ASSIGN(Joint);

    ModelInstanceIndex model_instance() const { return model_instance_; }

    const std::string& name() const { return name_; }

    BodyIndex parent_body() const { return parent_body_index_; }
    BodyIndex child_body() const { return child_body_index_; }

    JointTypeIndex type_index() const { return type_index_; }

private:
    // Restrict construction and modification to only MultibodyGraph.
    friend class MultibodyGraph;

    Joint(const std::string& name,
          ModelInstanceIndex model_instance,
          JointTypeIndex joint_type_index,
          BodyIndex parent_body_index,
          BodyIndex child_body_index)
        : name_(name),
          model_instance_(model_instance),
          type_index_(joint_type_index),
          parent_body_index_(parent_body_index),
          child_body_index_(child_body_index) {}

    std::string name_;
    ModelInstanceIndex model_instance_;
    JointTypeIndex type_index_;
    BodyIndex parent_body_index_;
    BodyIndex child_body_index_;
};

}  // namespace internal
}  // namespace multibody
}  // namespace drake
