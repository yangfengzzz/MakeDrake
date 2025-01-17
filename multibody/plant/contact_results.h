#pragma once

#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include "common/copyable_unique_ptr.h"
#include "common/default_scalars.h"
#include "common/drake_copyable.h"
#include "common/eigen_types.h"
#include "common/ssize.h"
#include "multibody/plant/deformable_contact_info.h"
#include "multibody/plant/hydroelastic_contact_info.h"
#include "multibody/plant/point_pair_contact_info.h"

namespace drake {
namespace multibody {

#ifndef DRAKE_DOXYGEN_CXX
template <typename T>
class MultibodyPlant;
#endif

/**
 A container class storing the contact results information for each contact
 pair for a given state of the simulation. Note that copying this data structure
 is expensive when `num_hydroelastic_contacts() > 0` because a deep copy is
 performed.

 @tparam_default_scalar
 */
template <typename T>
class ContactResults {
public:
    ContactResults();
    ContactResults(const ContactResults&);
    ContactResults(ContactResults&&) = default;
    ContactResults& operator=(const ContactResults&);
    ContactResults& operator=(ContactResults&&) = default;
    ~ContactResults();

    /** Returns the number of point pair contacts. */
    int num_point_pair_contacts() const { return static_cast<int>(point_pairs_info_.size()); }

    /** Returns the number of hydroelastic contacts. */
    int num_hydroelastic_contacts() const;

    /** Returns the number of deformable contacts. */
    int num_deformable_contacts() const { return ssize(deformable_contact_info_); }

    /** Retrieves the ith PointPairContactInfo instance. The input index i
     must be in the range [0, `num_point_pair_contacts()`) or this method
     throws. */
    const PointPairContactInfo<T>& point_pair_contact_info(int i) const;

    /** Retrieves the ith HydroelasticContactInfo instance. The input index i
     must be in the range [0, `num_hydroelastic_contacts()`) or this
     method throws. */
    const HydroelasticContactInfo<T>& hydroelastic_contact_info(int i) const;

    /** Retrieves the ith DeformableContactInfo instance. The input index i
     must be in the range [0, `num_deformable_contacts()`) or this method
     throws. */
    const DeformableContactInfo<T>& deformable_contact_info(int i) const;

    /** Returns the plant that produced these contact results. In most cases the
    result will be non-null, but default-constructed results might have nulls. */
    const MultibodyPlant<T>* plant() const;

    /** Returns ContactResults with only HydroelasticContactInfo instances
     satisfying the selection criterion and with all PointPairContactInfo
     instances.

     @param selector Boolean predicate that returns true to select which
                     HydroelasticContactInfo.

     @note It uses deep copy. */
    ContactResults<T> SelectHydroelastic(std::function<bool(const HydroelasticContactInfo<T>&)> selector) const;

// The following methods should only be called by MultibodyPlant and testing
// fixtures and are undocumented rather than being made private with friends.
#ifndef DRAKE_DOXYGEN_CXX
    /* Sets the plant that produced these contact results. */
    void set_plant(const MultibodyPlant<T>* plant);

    /* Clears the set of contact information for when the old data becomes
     invalid. This includes clearing the `plant` back to nullptr. */
    void Clear();

    /* Adds a new contact pair result to `this`. */
    void AddContactInfo(const PointPairContactInfo<T>& point_pair_info) {
        point_pairs_info_.push_back(point_pair_info);
    }

    /* Adds a new hydroelastic contact to `this`, assuming that `this` is not the
     result of a copy operation (AddContactInfo() asserts that is the case). The
     pointer must remain valid for the lifetime of this object. */
    void AddContactInfo(const HydroelasticContactInfo<T>* hydroelastic_contact_info);

    /* Adds a new deformable contact result to `this`. */
    void AddContactInfo(DeformableContactInfo<T> deformable_contact_info) {
        deformable_contact_info_.push_back(std::move(deformable_contact_info));
    }
#endif

private:
    enum OwnershipMode { kAliasedPointers, kOwnsCopies };

    OwnershipMode hydroelastic_contact_vector_ownership_mode() const {
        return std::holds_alternative<std::vector<const HydroelasticContactInfo<T>*>>(hydroelastic_contact_info_)
                       ? kAliasedPointers
                       : kOwnsCopies;
    }

    const std::vector<const HydroelasticContactInfo<T>*>& hydroelastic_contact_vector_of_pointers() const {
        return std::get<std::vector<const HydroelasticContactInfo<T>*>>(hydroelastic_contact_info_);
    }

    std::vector<const HydroelasticContactInfo<T>*>& hydroelastic_contact_vector_of_pointers() {
        return std::get<std::vector<const HydroelasticContactInfo<T>*>>(hydroelastic_contact_info_);
    }

    const std::vector<std::unique_ptr<HydroelasticContactInfo<T>>>& hydroelastic_contact_vector_of_unique_ptrs() const {
        return std::get<std::vector<std::unique_ptr<HydroelasticContactInfo<T>>>>(hydroelastic_contact_info_);
    }

    std::vector<std::unique_ptr<HydroelasticContactInfo<T>>>& hydroelastic_contact_vector_of_unique_ptrs() {
        return std::get<std::vector<std::unique_ptr<HydroelasticContactInfo<T>>>>(hydroelastic_contact_info_);
    }

    std::vector<PointPairContactInfo<T>> point_pairs_info_;

    /* We use a variant type to keep from copying already owned data (from a
     cache), i.e., the HydroelasticContactInfo, into this data structure, if
     possible. By default, the variant stores the first type, i.e.,
     std::vector<const HydroelasticContactInfo<T>*>. If this data structure is
     copied, however, the variant changes to instead store the second type, a
     vector of unique pointers. In that case, all of the underlying
     HydroelasticContactInfo objects are copied and
     AddContactInfo(const HydroelasticContactInfo*) can no longer be called on the
     copy (see assertion in AddContactInfo).

     Note that we jump through these hoops because storing ContactResults into
     a cache entry requires that it be placed into a Value<ContactResults>, which
     in turn requires that ContactResults be copyable.
     */
    std::variant<std::vector<const HydroelasticContactInfo<T>*>,
                 std::vector<std::unique_ptr<HydroelasticContactInfo<T>>>>
            hydroelastic_contact_info_;

    std::vector<DeformableContactInfo<T>> deformable_contact_info_;

    const MultibodyPlant<T>* plant_{nullptr};
};

}  // namespace multibody
}  // namespace drake

DRAKE_DECLARE_CLASS_TEMPLATE_INSTANTIATIONS_ON_DEFAULT_SCALARS(class ::drake::multibody::ContactResults);
