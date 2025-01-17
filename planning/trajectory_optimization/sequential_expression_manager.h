#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "common/drake_copyable.h"
#include "common/eigen_types.h"
#include "common/string_unordered_map.h"
#include "common/symbolic/expression.h"

namespace drake {
namespace planning {
namespace trajectory_optimization {
namespace internal {
/*
 * Represents a collection of sequential expression vectors (expression vectors
 * that take on different values for each index in {0, ..., `num_samples` - 1}).
 * Each sequential expression vector is identified by a name and has an
 * associated vector of placeholder variables. These placeholder variables can
 * be replaced with the corresponding expressions for a given index by means of
 * the symbolic::Substitution that ConstructPlaceholderVariableSubstitution()
 * returns.
 */
class SequentialExpressionManager {
public:
    DRAKE_DEFAULT_COPY_AND_MOVE_AND_ASSIGN(SequentialExpressionManager);

    /*
     * @pre `num_samples` > 0
     */
    explicit SequentialExpressionManager(int num_samples);

    ~SequentialExpressionManager() = default;

    /*
     * Registers a sequential expression vector and returns a vector of
     * placeholder variables.
     * @param sequential_expressions [num_expressions x num_samples] matrix of
     * symbolic expressions. sequential_expressions(i, j) is the value of the i-th
     * expression at the j-th index.
     * @param name Name for the newly registered sequential expression vector. The
     * i-th element of the placeholder variable vector will be named name_i.
     * @pre `sequential_expressions` has num_samples() columns.
     * @pre `name` must not duplicate the name of any previously registered
     * sequential expression vector.
     * @returns placeholder variable vector for use with
     * ConstructPlaceholderVariableSubstitution().
     */
    VectorX<symbolic::Variable> RegisterSequentialExpressions(
            const Eigen::Ref<const MatrixX<symbolic::Expression>>& sequential_expressions, const std::string& name);

    /*
     * Registers a placeholder variables and the associated sequential expression
     * vector.
     *
     * @param placeholders Placeholder variables.
     * @param sequential_expressions [size_of_placeholder_variables x num_samples]
     *                               matrix of symbolic expressions.
     *                               sequential_expressions(i, j) is the value of
     *                               the i-th expression at the j-th index.
     * @param name Name for the newly registered sequential expression vector.
     * @throws std::exception unless `sequential_expressions` has
     *                        `placeholders.size()` rows.
     * @throws std::exception unless `sequential_expressions` has num_samples()
     *                        columns.
     * @throws std::exception if it has an existing registration under the
     *                        `name`.
     */
    void RegisterSequentialExpressions(const VectorX<symbolic::Variable>& placeholders,
                                       const Eigen::Ref<const MatrixX<symbolic::Expression>>& sequential_expressions,
                                       const std::string& name);

    /*
     * Returns a symbolic::Substitution for replacing all placeholder variables
     * with their respective `index`-th expression.
     * @pre 0 <= index < num_samples()
     */
    symbolic::Substitution ConstructPlaceholderVariableSubstitution(int index) const;

    /*
     * Returns a vector with each placeholder symbolic::Variable in `vars`
     * replaced by the symbolic::Variable corresponding to that placeholder at
     * `index`. @throws std::exception if the placeholder variable at `index` is
     * an Expression which does not correspond to a single Variable.
     */
    VectorX<symbolic::Variable> GetVariables(const Eigen::Ref<const VectorX<symbolic::Variable>>& vars,
                                             int index) const;

    /*
     * Returns the `index`-th vector of expressions for `name`.
     * @pre `name` is associated with a registered sequential expression vector.
     * @pre 0 <= index < num_samples()
     **/
    VectorX<symbolic::Expression> GetSequentialExpressionsByName(const std::string& name, int index) const;

    /* Returns all the sequential expression names in this manager.
     */
    std::vector<std::string> GetSequentialExpressionNames() const;

    /*
     * Returns the number of samples for the sequential expressions managed by
     * `this`.
     */
    int num_samples() const { return num_samples_; }

    /*
     * Returns the number of rows for the sequential expression vector `name`.
     * @pre `name` is associated with a registered sequential expression vector.
     */
    int num_rows(const std::string& name) const;

private:
    int num_samples_{};
    string_unordered_map<VectorX<symbolic::Variable>> name_to_placeholders_;
    std::unordered_map<symbolic::Variable, RowVectorX<symbolic::Expression>> placeholders_to_expressions_;
};
}  // namespace internal
}  // namespace trajectory_optimization
}  // namespace planning
}  // namespace drake
