#pragma once

#include <string>

#include "common/name_value.h"

namespace drake {
namespace multibody {

/// The set of configurable properties on a MultibodyPlant.
///
/// The field names and defaults here match MultibodyPlant's defaults exactly,
/// with the exception of time_step.
struct MultibodyPlantConfig {
    /// Passes this object to an Archive.
    /// Refer to @ref yaml_serialization "YAML Serialization" for background.
    template <typename Archive>
    void Serialize(Archive* a) {
        a->Visit(DRAKE_NVP(time_step));
        a->Visit(DRAKE_NVP(penetration_allowance));
        a->Visit(DRAKE_NVP(stiction_tolerance));
        a->Visit(DRAKE_NVP(contact_model));
        a->Visit(DRAKE_NVP(discrete_contact_approximation));
        a->Visit(DRAKE_NVP(discrete_contact_solver));
        a->Visit(DRAKE_NVP(sap_near_rigid_threshold));
        a->Visit(DRAKE_NVP(contact_surface_representation));
        a->Visit(DRAKE_NVP(adjacent_bodies_collision_filters));
    }

    /// Configures the MultibodyPlant::MultibodyPlant() constructor time_step.
    ///
    /// There is no default value for this within MultibodyPlant itself, so here
    /// we choose a nominal value (a discrete system, with a 1ms periodic update)
    /// as a reasonably conservative estimate that works in many cases.
    double time_step{0.001};

    /// Configures the MultibodyPlant::set_penetration_allowance().
    double penetration_allowance{0.001};

    /// Configures the MultibodyPlant::set_stiction_tolerance().
    double stiction_tolerance{0.001};

    /// Configures the MultibodyPlant::set_contact_model().
    /// Refer to drake::multibody::ContactModel for details.
    /// Valid strings are:
    /// - "point"
    /// - "hydroelastic"
    /// - "hydroelastic_with_fallback"
    std::string contact_model{"hydroelastic_with_fallback"};

    /// Configures the MultibodyPlant::set_discrete_contact_solver().
    /// Refer to drake::multibody::DiscreteContactSolver for details.
    /// Valid strings are:
    /// - "tamsi", uses the TAMSI model approximation.
    /// - "sap"  , uses the SAP model approximation.
    ///
    /// @note If empty, the contact solver is determined by
    /// discrete_contact_approximation, see
    /// MultibodyPlant::set_discrete_contact_approximation(). If both
    /// discrete_contact_solver and discrete_contact_approximation are empty, the
    /// default model (and solver) is TAMSI.
    ///
    /// @warning discrete_contact_solver is deprecated.
    /// Use discrete_contact_approximation to set the contact model approximation.
    /// The underlying solver will be inferred automatically. The deprecated code
    /// will be removed from Drake on or after 2024-04-01.
    std::string discrete_contact_solver{""};

    // TODO(amcastro-tri): Along the removal of discrete_contact_solver on or
    // after 2024-04-01, update the default value of
    // discrete_contact_approximation to be non-empty. The value will be either
    // "similar" or "lagged", to be decided based on the information we collect
    // from our users.
    /// Configures the MultibodyPlant::set_discrete_contact_approximation().
    /// Refer to drake::multibody::DiscreteContactApproximation for details.
    /// Valid strings are:
    /// - "tamsi"
    /// - "sap"
    /// - "similar"
    /// - "lagged"
    ///
    /// Refer to MultibodyPlant::set_discrete_contact_approximation() and the
    /// references therein for further details.
    ///
    /// @note If empty, the contact approximation is determined by
    /// discrete_contact_solver, see set_discrete_contact_solver(). If both
    /// discrete_contact_solver and discrete_contact_approximation are empty, the
    /// default model (and solver) is TAMSI.
    std::string discrete_contact_approximation{""};

    // TODO(amcastro-tri): Change default to zero, or simply eliminate.
    /// Non-negative dimensionless number typically in the range [0.0, 1.0],
    /// though larger values are allowed even if uncommon. This parameter controls
    /// the "near rigid" regime of the SAP solver, β in section V.B of [Castro et
    /// al., 2021]. It essentially controls a threshold value for the maximum
    /// amount of stiffness SAP can handle robustly. Beyond this value, stiffness
    /// saturates as explained in [Castro et al., 2021].
    /// A value of 1.0 is a conservative choice to avoid numerical
    /// ill-conditioning. However, this might introduce artificial softening of
    /// the contact constraints. If this is your case try:
    ///   1. Set this parameter to zero.
    ///   2. For difficult problems (hundreds of contacts for instance), you might
    ///      need to use a low value if the solver fails to converge.
    ///      For instance, set values in the range (1e-3, 1e-2).
    double sap_near_rigid_threshold{1.0};

    /// Configures the MultibodyPlant::set_contact_surface_representation().
    /// Refer to drake::geometry::HydroelasticContactRepresentation for details.
    /// Valid strings are:
    /// - "triangle"
    /// - "polygon"
    ///
    /// The default value used here is consistent with the default time_step
    /// chosen above; keep this consistent with
    /// MultibodyPlant::GetDefaultContactSurfaceRepresentation().
    std::string contact_surface_representation{"polygon"};

    /// Configures the MultibodyPlant::set_adjacent_bodies_collision_filters().
    bool adjacent_bodies_collision_filters{true};
};

}  // namespace multibody
}  // namespace drake
