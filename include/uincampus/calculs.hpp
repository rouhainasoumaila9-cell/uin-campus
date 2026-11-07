#pragma once

#include <cstddef>
#include <vector>

namespace uin {

struct Statistiques {
    double minimum;
    double maximum;
    double moyenne;
    double ecartType;
};

[[nodiscard]] double somme(const std::vector<double>& valeurs);

[[nodiscard]] double moyenne(const std::vector<double>& notes);

[[nodiscard]] double moyenne(
    const std::vector<double>& notes,
    const std::vector<double>& coefficients
);

[[nodiscard]] Statistiques calculerStatistiques(
    const std::vector<double>& notes
);

[[nodiscard]] std::size_t compterValidees(
    const std::vector<double>& notes
);

[[nodiscard]] double arrondir(double valeur, int decimales = 2);

} // namespace uin
