#pragma once

#include <string>
#include <vector>

#include "common/drake_copyable.h"
#include "common/eigen_types.h"
#include "common/random.h"
#include "math/rigid_transform.h"
#include "multibody/plant/multibody_plant.h"

namespace drake {
namespace multibody {

/**
 * A wrapper class around the IK planner. This class improves IK's usability by
 * handling constraint relaxing and multiple initial guesses internally.
 *
 * @ingroup planning_kinematics
 */
class ConstraintRelaxingIk {
public:
    DRAKE_NO_COPY_NO_MOVE_NO_ASSIGN(ConstraintRelaxingIk);

    /**
     * Cartesian waypoint. Input to the IK solver.
     */
    struct IkCartesianWaypoint {
        /// Desired end effector pose in the world frame.
        math::RigidTransformd pose;
        /// Bounding box for the end effector in the world frame.
        Vector3<double> pos_tol{Vector3<double>(0.005, 0.005, 0.005)};
        /// Max angle difference (in radians) between solved end effector's
        /// orientation and the desired.
        double rot_tol{0.05};
        /// Signals if orientation constraint is enabled.
        bool constrain_orientation{false};
    };

    /**
     * Constructor. Instantiates an internal MultibodyPlant from @p model_path.
     * @param model_path Path to the model file.
     * @param end_effector_link_name Link name of the end effector.
     */
    ConstraintRelaxingIk(const std::string& model_path, const std::string& end_effector_link_name);

    /**
     * Sets end effector to @p link_name.
     */
    void SetEndEffector(const std::string& link_name) {
        end_effector_body_idx_ = plant_.GetBodyByName(link_name).index();
    }

    /**
     * Generates IK solutions for each waypoint sequentially. For waypoint wp_i,
     * the IK tries to solve q_i that satisfies the end effector constraints in
     * wp_i and minimizes the squared difference to q_{i-1}, where q_{i-1} is the
     * solution to the previous wp_{i-1}. q_{i-1} = @p q_current when i = 0. This
     * function internally does constraint relaxing and initial condition
     * guessing if necessary.
     *
     * Note that @p q_current is inserted at the beginning of @p q_sol.
     *
     * @param waypoints A sequence of desired waypoints.
     * @param q_current The initial generalized position.
     * @param[out] q_sol Results.
     * @param keep_going Optional callback to allow for cancellation.
     *   When given, this function will be called prior to every IK solve; if it
     *   returns false, the PlanSequentialTrajectory will stop and return false.
     *   The function is passed the index of the waypoint currently being solved.
     *   This can be used to enable timeouts for difficult plans.
     * @return True if solved successfully.
     */
    bool PlanSequentialTrajectory(const std::vector<IkCartesianWaypoint>& waypoints,
                                  const VectorX<double>& q_current,
                                  std::vector<Eigen::VectorXd>* q_sol,
                                  const std::function<bool(int)>& keep_going = {});

private:
    bool SolveIk(const IkCartesianWaypoint& waypoint,
                 const VectorX<double>& q0,
                 const Vector3<double>& pos_tol,
                 double rot_tol,
                 VectorX<double>* q_res);

    RandomGenerator rand_generator_;
    MultibodyPlant<double> plant_;
    BodyIndex end_effector_body_idx_{};
};

}  // namespace multibody
}  // namespace drake
