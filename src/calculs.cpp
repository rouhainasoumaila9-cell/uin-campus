#include "uincampus/calculs.hpp"
#include "uincampus/regles.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <ranges>

namespace uin {

double somme(const std::vector<double>& valeurs)
{
    return std::accumulate(valeurs.begin(), valeurs.end(), 0.0);
}

double moyenne(const std::vector<double>& notes)
{
    assert(!notes.empty());

    return somme(notes) / static_cast<double>(notes.size());
}

double moyenne(
    const std::vector<double>& notes,
    const std::vector<double>& coefficients
)
{
    assert(!notes.empty());
    assert(notes.size() == coefficients.size());

    const double totalCoefficients =
        std::accumulate(coefficients.begin(), coefficients.end(), 0.0);

    assert(totalCoefficients > 0.0);

    const double totalPondere = std::inner_product(
        notes.begin(),
        notes.end(),
        coefficients.begin(),
        0.0
    );

    return totalPondere / totalCoefficients;
}

Statistiques calculerStatistiques(const std::vector<double>& notes)
{
    assert(!notes.empty());

    const auto [minimum, maximum] =
        std::ranges::minmax(notes);

    const double moy = moyenne(notes);

    const double sommeEcarts = std::accumulate(
        notes.begin(),
        notes.end(),
        0.0,
        [moy](double total, double note) {
            return total + std::pow(note - moy, 2);
        }
    );

    const double ecartType = std::sqrt(
        sommeEcarts / static_cast<double>(notes.size())
    );

    return {minimum, maximum, moy, ecartType};
}

std::size_t compterValidees(const std::vector<double>& notes)
{
    return static_cast<std::size_t>(
        std::ranges::count_if(notes, [](double note) {
            return note >= seuilValidation;
        })
    );
}

double arrondir(double valeur, int decimales)
{
    const double facteur = std::pow(10.0, decimales);

    return std::round(valeur * facteur) / facteur;
}

} // namespace uin
