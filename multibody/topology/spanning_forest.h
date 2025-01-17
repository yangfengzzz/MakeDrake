#pragma once

#ifndef DRAKE_MULTIBODY_TOPOLOGY_FOREST_INCLUDED
#error Do not include this file. Use "drake/multibody/topology/forest.h".
#endif

#include <functional>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "common/drake_copyable.h"
#include "common/ssize.h"
#include "multibody/topology/graph.h"

namespace drake {
namespace multibody {
// TODO(sherm1) Promote from internal once API has stabilized: issue #11307.
namespace internal {

using WeldedMobodsIndex = TypeSafeIndex<class WeldedMobodsTag>;

// TODO(sherm1) The following describes the aspirational SpanningForest but
//  some functionality is missing. See PR #20225 for the full implementation.

/** SpanningForest models a LinkJointGraph via a set of spanning trees and
loop-closing constraints. This is a directed forest, with edges ordered from
inboard (closer to World) to outboard. The nodes are mobilized bodies (Mobods)
representing a body and its inboard mobilizer. While building the Forest we also
study the original LinkJointGraph and update it to reflect:
  - how each of its elements was modeled,
  - any new elements that needed to be added for the model, and
  - which Links are welded together into composites.

Welded-together Links have no relative motion so should be excluded from mutual
collision computations and can (optionally) be modeled with a single mobilized
body.

Problem statement

We're given a disjoint collection of directed, possibly cyclic, graphs whose
nodes represent links and whose parent->child directed edges represent joints.
Some graphs contain edges to World, others are free-floating. The task here is
to efficiently convert the input graph collection into a single directed
_acyclic_ graph considered as a forest of directed trees. The nodes of the trees
are _mobilized bodies_ (Mobods), each of which has a unique edge ("mobilizer")
connecting it to its _inboard_ (closer to World) mobilized body, and directed
inboard->outboard. Each tree spans one of the input graphs and is given an edge
to World if there wasn't one already. Links are cut to break cycles, with each
half getting its own Mobod. The forest is augmented with weld constraints
that will act on the two Mobods to reconnect the Link halves. The resulting
forest (with its associated welds) is to be optimized for computation speed and
numerical accuracy, consistent with user preferences.

Input links and joints can be annotated with properties that may affect how we
build the forest. For example, a joint may be fixed (a weld) indicating that its
connected links can be combined. Links may be massless in which case they can't
be terminal nodes of a tree unless they are also welded to something massful.
Users may also have modeling preferences, such as which nodes should be used to
connect free-floating input graphs to World, and how they should be connected
(e.g. fixed or floating base).

These are the properties the resulting forest _must_ have:
  - All nodes (Mobods) have a path from World.
  - Massless bodies never appear as terminal nodes in the forest
  - Mobod nodes are numbered depth-first.
  - Position and velocity coordinates q and v are assigned to the edges
    (mobilizers) with the same depth-first ordering.
  - Excluding World, the trees partition the Mobods and each tree contains a
    consecutively-numbered subset of Mobods and their coordinates.
  - Specific user modeling instructions are obeyed.

And these additional properties are highly desirable:
  - The maximum branch length is minimized when breaking cycles.
  - Input parent->child edge directions are preserved as inboard->outboard
    directions when possible without increasing the maximum branch length.
  - Welded-together links are combined into a single Mobod (optionally).

Discussion

A LinkJointGraph consists of Links (user-defined rigid bodies) and Joints in a
directed, possibly cyclic graph. Link 0 is designated as the World and is
modeled by Mobod 0 in the Forest. Each Joint connects a "parent" Link to a
"child" Link. The parent->child ordering is arbitrary but sets the user's
expected sign conventions for the Joint coordinates. Those must be preserved,
even though inboard->outboard ordering may differ from parent->child (even if
there are no loops). We distinguish "moving" (or "articulated") Joints from
"weld" (0 dof) Joints; every moving Joint is modeled by a mobilizer, but welds
may be eliminated by creating LinkComposites that require only a single
mobilizer for a group of Links.

The SpanningForest contains a Mobod node corresponding to each Link or
LinkComposite (group of welded-together Links). A mobilizer connects each Mobod
to an inboard Mobod (except for World). An additional "shadow" Link and its
Mobod is created whenever a loop is broken by cutting a Link, and a
LoopConstraint is added to reconnect the primary Link to its shadow. Every
moving Joint will map to a Mobod and there will be additional floating or weld
mobilizers added as needed to connect tree root nodes (a.k.a. "base bodies") to
World.

When extra bodies, mobilizers, and constraints are needed to construct the
Forest, corresponding _ephemeral_ Links, Joints, and LoopConstraints are added
to the LinkJointGraph so a user can view the Forest as an extended
LinkJointGraph (the original graph is retained). For example, added 6dof
mobilizers can be viewed as though they had been floating Joints in the
LinkJointGraph.

We sort the mobilized bodies into depth-first order, beginning with the 0th
Mobod corresponding to World. The data structures are designed to support fast
computation directly so that the information here does not need to be duplicated
elsewhere.

Things we get for free (O(1)) here as a side effect of building the Forest:
  - access the mobilized bodies (Mobods) in depth-first order
  - access Trees also in depth-first order and find out which Mobods belong
      to a given Tree and what range of coordinates belongs to each Tree or
      subtree
  - ask a Mobod which Tree it is in, and which coordinates it uses
  - find out which groups of Mobods are welded together (so have no relative
    motion)
  - ask a Mobod which WeldedMobods grouping it belongs to, if any
  - ask a coordinate (q or v) which Mobod or Tree it belongs to
  - ask for the max height of a Tree or the level of a particular Mobod
  - determine which Mobods are anchored to World, directly or indirectly
  - find out which Mobod(s) represents a given Link
  - find out which Mobod (if any) represents a given Joint (welds internal
    to LinkComposites are not modeled)
  - find all the Links that follow a particular Mobod (for composites)
  - find out what (ephemeral) Links, Joints, and LoopConstraints appear in the
      Forest but not the source Graph.

Supported operations at minimal cost:
  - find the path from World to a given Link or Mobod
  - find the closest common ancestor of a pair of Links or Mobods.
*/
class SpanningForest {
public:
    // Constructors and assignment are private; only LinkJointGraph may access.
    // These can't be default because there are back pointers to clean up.

    class Mobod;  // Defined in separate headers.
    class Tree;
    class LoopConstraint;

    using Link = LinkJointGraph::Link;
    using Joint = LinkJointGraph::Joint;

    /** Returns a reference to the graph that owns this forest (as set during
    construction). */
    const LinkJointGraph& graph() const {
        DRAKE_ASSERT(data_.graph != nullptr);
        return *data_.graph;
    }

    /** Returns `true` if this forest is up to date with respect to its owning
    graph. */
    bool is_valid() const { return graph().forest_is_valid(); }

    /** Returns `true` if this forest can be used for dynamics (the usual case).
    Otherwise, the presence of a terminal massless body will make the resulting
    mass matrix singular, restricting use to kinematic operations. */
    bool dynamics_ok() const { return data_.dynamics_ok; }

    /** If dynamics_ok() returns `false`, returns a human-readable message
    explaining why. Otherwise returns the empty string. */
    const std::string& why_no_dynamics() const { return data_.why_no_dynamics; }

    /** Provides convenient access to the owning graph's links. */
    const std::vector<Link>& links() const { return graph().links(); }

    /** Provides convenient access to one of the owning graph's links. Requires
    a BodyIndex, not a plain integer.
    @pre link_index is in range */
    const Link& links(BodyIndex link_index) const { return graph().links(link_index); }

    /** Provides convenient access to the owning graph's joints. */
    const std::vector<Joint>& joints() const { return graph().joints(); }

    /** Provides convenient access to one of the owning graph's joints. Requires
    a JointIndex, not a plain integer.
    @pre joint_index is in range */
    const Joint& joints(JointIndex joint_index) const { return graph().joints(joint_index); }

    /** All the mobilized bodies, in depth-first order. World comes first,
    then every Mobod in tree 0, then every Mobod in tree 1, etc. Free bodies
    that weren't explicitly connected to World by a Joint come last. */
    const std::vector<Mobod>& mobods() const { return data_.mobods; }

    /** Provides convenient access to a particular Mobod. Requires a MobodIndex,
    not a plain integer.
    @pre mobod_index is in range */
    inline const Mobod& mobods(MobodIndex mobod_index) const;

    /** The mobilized body (Mobod) corresponding to the World Link.
    @pre The forest is valid. */
    // Internal use only: this is valid during BuildForest() also.
    const Mobod& world_mobod() const { return mobods(MobodIndex(0)); }

    /** Constraints we added to close loops we had to cut. */
    const std::vector<LoopConstraint>& loop_constraints() const { return data_.loop_constraints; }

    /** Provides convenient access to a particular LoopConstraint. Requires a
    LoopConstraintIndex, not a plain integer. */
    inline const LoopConstraint& loop_constraints(LoopConstraintIndex index) const;

    /** The partitioning of the forest of mobilized bodies into trees. Each Tree
    has a base (root) mobilized body that is connected directly to the World
    Mobod (which may represent a LinkComposite). World is not considered to
    be part of any Tree; it is the root of the Forest. */
    const std::vector<Tree>& trees() const { return data_.trees; }

    /** Provides convenient access to a particular Tree. Requires a TreeIndex,
    not a plain integer.
    @pre tree_index is in range */
    inline const Tree& trees(TreeIndex tree_index) const;

    /** When this %SpanningForest is valid (i.e., after BuildForest() returns)
    this is the height of the forest, defined as the height of the tallest
    Tree, plus 1 for World. Returns zero for an invalid forest. */
    // Internal use only: During BuildForest() this will track the largest
    // height seen so far.
    int height() const { return data_.forest_height; }

    /** Returns precalculated groups of mobilized bodies that are mutually
    interconnected by Weld mobilizers so have no relative degrees of freedom.
    Note that if you have chosen the modeling option to combine welded-together
    Links into single bodies, then each LinkComposite gets only a single Mobod
    and hence there won't be any WeldedMobods groups here (except for World which
    is always considered to be in a WeldedMobods group even if nothing is welded
    to it). Use mobod_to_links() to find all the Links following a single Mobod.

    The World WeldedMobods group comes first and contains World, mobilized bodies
    representing Links marked "Static", and bodies (if any) welded to Static
    bodies or World (recursively). Those are the "anchored" mobilized bodies. The
    other groups represent sets of welded-together mobilized bodies, with the
    first one in the group the only Mobod with a non-weld inboard mobilizer.
    That moving Mobod is necessarily the lowest numbered (most inboard) Mobod
    of the WeldedMobods group. The remaining Mobods are in no particular order.

    Except for World, Mobods not welded to any other Mobods do not appear here.
    @see mobod_to_links() */
    const std::vector<std::vector<MobodIndex>>& welded_mobods() const { return data_.welded_mobods; }

    /** Provides convenient access to a particular WeldedMobods group. Requires a
    WeldedMobodsIndex, not a plain integer.
    @pre index is in range */
    const std::vector<MobodIndex>& welded_mobods(WeldedMobodsIndex index) const { return welded_mobods().at(index); }

    /** Returns the global ForestBuildingOptions in effect in the owning graph. */
    ForestBuildingOptions options() const { return graph().get_global_forest_building_options(); }

    /** Returns the ForestBuildingOptions in effect for elements of the given
    ModelInstance. If we don't have specific options for this instance, we
    return the global ForestBuildingOptions as returned by options().
    @pre index is valid (but not necessarily one we've seen before) */
    ForestBuildingOptions options(ModelInstanceIndex index) const {
        return graph().get_forest_building_options_in_use(index);
    }

    /** Returns the Link that is represented by the given Mobod. This could be
    one of the Links from the original graph or an added shadow Link. If this
    Mobod represents a LinkComposite, the Link returned here is the
    "active" Link, that is, the one whose mobilizer is used to move the whole
    Composite. Cost is O(1) and very fast.
    @pre mobod_index is in range */
    inline BodyIndex mobod_to_link(MobodIndex mobod_index) const;

    /** Returns all the Links mobilized by this Mobod. The "active" Link returned
    by mobod_to_link() comes first, then any other Links in the same Composite.
    O(1), very fast.
    @pre mobod_index is in range  */
    inline const std::vector<BodyIndex>& mobod_to_links(MobodIndex mobod_index) const;

    /** Returns the total number of generalized position coordinates q used by
    this model. O(1), very fast. */
    int num_positions() const { return ssize(data_.q_to_mobod); }

    /** Returns the total number of generalized velocity coordinates v used by
    this model. O(1), very fast. */
    int num_velocities() const { return ssize(data_.v_to_mobod); }

    /** Returns the Mobod to which a given position coordinate q belongs.
    O(1), very fast.
    @pre q_index is in range [0, num_positions) */
    MobodIndex q_to_mobod(int q_index) const {
        DRAKE_ASSERT(0 <= q_index && q_index < num_positions());
        return data_.q_to_mobod[q_index];
    }

    /** Returns the Mobod to which a given velocity coordinate v belongs.
    O(1), very fast.
    @pre v_index is in range [0, num_velocities) */
    MobodIndex v_to_mobod(int v_index) const {
        DRAKE_ASSERT(0 <= v_index && v_index < num_velocities());
        return data_.v_to_mobod[v_index];
    }

    /** Returns the Tree to which a given position coordinate q belongs.
    O(1), very fast.
    @pre q_index is in range [0, num_positions) */
    inline TreeIndex q_to_tree(int q_index) const;

    /** Returns the Tree to which a given velocity coordinate v belongs.
    O(1), very fast.
    @pre v_index is in range [0, num_velocities) */
    inline TreeIndex v_to_tree(int v_index) const;

    // TODO(sherm1) Remove this.
    // (Testing stub only) Add enough fake elements to the forest to allow
    // testing of the Tree and LoopConstraint APIs.
    void AddStubTreeAndLoopConstraint();

private:
    friend class LinkJointGraph;
    friend class copyable_unique_ptr<SpanningForest>;

    // Only the owning LinkJointGraph may call this constructor. The owner must
    // outlive this model, which may be built and rebuilt repeatedly for the same
    // owner. For copy and move, the owner is responsible for repairing the back
    // pointer via SetNewOwner().
    // @pre `graph` is non-null
    explicit SpanningForest(LinkJointGraph* graph) {
        DRAKE_DEMAND(graph != nullptr);
        data_.graph = graph;
    }

    // The caller (only LinkJointGraph) must provide a new back pointer after copy
    // or move so these can't be default.
    DRAKE_DECLARE_COPY_AND_MOVE_AND_ASSIGN(SpanningForest);

    // LinkJointGraph uses this to fix the graph back pointer after copy or move.
    void SetNewOwner(LinkJointGraph* graph) {
        DRAKE_DEMAND(graph != nullptr);
        data_.graph = graph;
    }

    // After copy/move/assign: any element that has a pointer back to its owning
    // SpanningForest should replace the pointer with `this`.
    void FixInternalPointers();

    // Clears the existing forest and builds a new one using the current forest
    // building options in the owning LinkJointGraph. This is for LinkJointGraph
    // to call _after_ it has cleaned out its own ephemeral elements and
    // out-of-date modeling information. New ephemeral elements and modeling info
    // will be written to the graph.
    // @returns true if the forest can be used for anything
    //          false if it can't be used for dynamics.
    // @see LinkJointGraph::BuildForest() documentation for more about whether
    //      the result can be used for dynamics.
    bool BuildForest();

    // Restores this SpanningTree to the state it has immediately after
    // construction. The owning LinkJointGraph remains unchanged.
    void Clear();

    // Produces the optimal forest, but with suboptimal node ordering.
    void ChooseForestTopology();

    // Determines proposed depth-first reordering. Index the `old_to_new` result
    // using the original MobodIndex to obtain the new MobodIndex.
    // @retval old_to_new
    std::vector<MobodIndex> CreateDepthFirstReordering() const;

    // Updates the forest to reorder the Mobods into depth-first order, and
    // updates the as-modeled information in the graph to match.
    void FixupForestToUseNewNumbering(const std::vector<MobodIndex>& old_to_new);

    // Once we have a depth-first ordering, assigns q's and v's.
    void AssignCoordinates();

    // Given a set of Joints, each of which has one of its Links already
    // modeled by some Mobod, grows the trees by modeling these Joints and the
    // other Link they connect. Then continues growing in a breadth-first manner,
    // one level at a time. On return, num_unprocessed_links will have been
    // decremented by the number of Links that were modeled.
    void ExtendTrees(const std::vector<JointIndex>& joints_to_model, int* num_unprocessed_links);

    // Grows the trees containing each of the given Joints by one level. The
    // output parameter `joints_to_model_next` (cleared on entry) on return
    // contains the set of Joints that should be modeled at the next level.
    // @pre the pointers are non-null and joints_to_model is not empty. On return,
    // num_unprocessed_links will have been decremented by the number of Links
    // that were modeled.
    void ExtendTreesOneLevel(const std::vector<JointIndex>& joints_to_model,
                             int* num_unprocessed_links,
                             std::vector<JointIndex>* joints_to_model_next);

    // After dealing with everything that had some path to World, deals with
    // remaining disconnected subgraphs and lone free bodies. On return,
    // num_unprocessed_links will have been decremented by the number of Links
    // that were modeled.
    void ChooseBaseBodiesAndAddTrees(int* num_unprocessed_links);

    // Adds a new mobilized body outboard of the given inboard body:
    //  - sets the level to one higher than the inboard level
    //  - if inboard is World, starts a new tree otherwise new Mobod is in
    //    the same tree as inboard
    //  - adds the new Mobod to the list of outboard Mobods in the inboard body
    //  - updates maps of link-to-mobod and joint-to-mobod
    //  - if joint type is Weld, we are creating or joining a WeldedMobods group
    //    and LinkComposite; if welded to World the Mobod is "anchored". */
    const Mobod& AddNewMobod(BodyIndex outboard_link_index,
                             JointIndex joint_index,
                             MobodIndex inboard_mobod_index,
                             bool is_reversed);

    // Given a list of Static or MustBeBaseBody Links, adds a weld or floating
    // Joint to World for each Link that doesn't already have one.
    void ConnectLinksToWorld(const std::vector<BodyIndex>& links, bool use_weld);

    // Sets the comparison function to be used in making the "best" choice.
    void SetBaseBodyChoicePolicy();

    // The not-yet-modeled Joint given by `loop_joint_index` connects two Links
    // both of which are already modeled in the Forest. We will model the Joint by
    // splitting off a shadow of one of the Links and mobilizing the shadow with a
    // forward or reversed Mobilizer of the Joint's type. Then we add a Weld
    // Constraint to attach the shadow to its primary. Some details:
    //  - if one link is massless, split the other one
    //  - if both are massless we have an invalid forest
    //  - either or both Links may be composites; it is the mass properties
    //    of the whole composite that determines masslessness.
    void HandleLoopClosure(JointIndex loop_joint_index);

    // Adds a shadow Link of the given primary and mobilizes the shadow with
    // the given joint which was originally connected to the primary. Adds a
    // weld constraint to reattach the shadow to the primary. The shadow and
    // weld are added to the graph as ephemeral elements.
    const Mobod& AddShadowMobod(BodyIndex primary_link_index, JointIndex shadow_joint_index);

    bool model_instance_is_static(ModelInstanceIndex index) const {
        return static_cast<bool>(options(index) & ForestBuildingOptions::kStatic);
    }

    bool use_fixed_base(ModelInstanceIndex index) const {
        return static_cast<bool>(options(index) & ForestBuildingOptions::kUseFixedBase);
    }

    bool use_rpy_floating_joint(ModelInstanceIndex index) const {
        return static_cast<bool>(options(index) & ForestBuildingOptions::kUseRpyFloatingJoints);
    }

    // Returns the index to the traits for the appropriate joint type to use for
    // this model instance when attaching a base body to World. Can be fixed or
    // floating, and floating can be rpy or quaternion, depending on modeling
    // options.
    JointTraitsIndex base_joint_traits_index(ModelInstanceIndex model_instance_index) const {
        if (use_fixed_base(model_instance_index)) return LinkJointGraph::weld_joint_traits_index();
        return use_rpy_floating_joint(model_instance_index) ? LinkJointGraph::rpy_floating_joint_traits_index()
                                                            : LinkJointGraph::quaternion_floating_joint_traits_index();
    }

    bool link_is_already_in_forest(BodyIndex link_index) const { return graph().link_to_mobod(link_index).is_valid(); }

    LinkJointGraph& mutable_graph() {
        DRAKE_ASSERT(data_.graph != nullptr);
        return *data_.graph;
    }

    struct Data {
        // These are all default but definitions deferred to .cc file so
        // that all the local classes are defined (Mac requirement).
        Data();
        Data(const Data&);
        Data(Data&&);
        ~Data();
        Data& operator=(const Data&);
        Data& operator=(Data&&);

        LinkJointGraph* graph{};  // The graph we're modeling.

        // A valid SpanningForest always has at least one mobilized body: World.
        std::vector<Mobod> mobods;

        // If we had to break any loops we'll add constraints to re-close them.
        std::vector<LoopConstraint> loop_constraints;

        // How the forest is partitioned into trees.
        std::vector<Tree> trees;

        // This is zero for an invalid forest, starts at 1 during BuildForest()
        // to count World, then adds in the height of the tallest tree seen so
        // far. Upon return from BuildForest() the forest is marked valid and
        // this contains the height of the tallest tree, plus 1.
        int forest_height{0};

        // Welded Mobod groups. These are disjoint sets of Mobods that have no
        // relative motion due to _modeled_ weld Joints (and _not_ due to weld
        // constraints). (If we are building LinkComposites, there won't be any
        // Mobods welded together because we'll make all welded-together Links
        // follow a single Mobod.) The World Mobod group is always present and comes
        // first even if nothing is welded to it. Other Mobods appear here only if
        // they are welded to at least one other Mobod. The indexes here must be
        // renumbered by FixupForestToUseNewNumbering().
        std::vector<std::vector<MobodIndex>> welded_mobods;

        // Map from mobilizer coordinates to their associated mobilized bodies.
        // These are filled in late with the post-renumbered MobodIndex values so
        // should NOT be renumbered by FixupForestToUseNewNumbering().
        std::vector<MobodIndex> q_to_mobod;  // size is nq (total number of q's)
        std::vector<MobodIndex> v_to_mobod;  // size is nv (total number of v's)

        // This policy is expressed as a "less than" comparator of the type used by
        // std::priority_queue. It should return true if the left argument is a
        // worse choice than the right argument, according to the policy.
        std::function<bool(const BodyIndex&, const BodyIndex&)> base_body_policy;

        // Set to false if we had to end a branch with a massless body.
        bool dynamics_ok{true};
        // Human-readable explanation for the above.
        std::string why_no_dynamics;
    } data_;
};

}  // namespace internal
}  // namespace multibody
}  // namespace drake
