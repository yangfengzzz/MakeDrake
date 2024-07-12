#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "common/test_utilities/expect_no_throw.h"
#include "math/rigid_transform.h"
#include "math/rotation_matrix.h"
#include "multibody/parsing/parser.h"
#include "multibody/plant/multibody_plant.h"
#include "multibody/test_utilities/add_fixed_objects_to_plant.h"
#include "systems/framework/context.h"
#include "systems/framework/diagram_builder.h"

namespace drake {

using Eigen::Translation3d;
using Eigen::Vector3d;
using math::RigidTransformd;
using math::RotationMatrixd;
using multibody::Parser;
using systems::Context;
using systems::Diagram;
using systems::DiagramBuilder;

namespace multibody {
namespace {

// Tests that we can do discrete updates even when the model has no DOFs.
// Relates to #12066.
GTEST_TEST(MbpWithTamsiSolver, FixedWorld) {
    systems::DiagramBuilder<double> builder;

    // We create a discrete model that uses the TAMSI solver for contact.
    const double discrete_update_period = 1.0e-3;
    auto items =
            AddMultibodyPlantSceneGraph(&builder, std::make_unique<MultibodyPlant<double>>(discrete_update_period));
    MultibodyPlant<double>& plant = items.plant;

    // Add the fixed objects to the world.
    test::AddFixedObjectsToPlant(&plant);

    // Done defining the world.
    plant.Finalize();

    // And build the Diagram:
    auto diagram = builder.Build();

    // The model has zero dofs.
    EXPECT_EQ(plant.num_velocities(), 0);
    EXPECT_EQ(plant.num_positions(), 0);

    // However it is not empty, it has all anchored geometry.
    EXPECT_EQ(plant.num_collision_geometries(), 3);

    auto context = diagram->CreateDefaultContext();

    auto& discrete_state_vector = context->get_discrete_state_vector();
    EXPECT_EQ(discrete_state_vector.size(), 0);

    auto new_discrete_state = diagram->AllocateDiscreteVariables();
    const systems::VectorBase<double>& new_discrete_state_vector = new_discrete_state->get_vector();
    EXPECT_EQ(new_discrete_state_vector.size(), 0);

    // Verify we can to do discrete updates even if we have zero DOFs.
    DRAKE_EXPECT_NO_THROW(diagram->CalcForcedDiscreteVariableUpdate(*context, new_discrete_state.get()));
}

}  // namespace
}  // namespace multibody
}  // namespace drake
