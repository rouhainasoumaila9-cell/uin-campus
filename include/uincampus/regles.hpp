#pragma once

#include <cstddef>
#include <string_view>

namespace uin {

enum class Mention {
    Ajourne,
    Passable,
    AssezBien,
    Bien,
    TresBien
};

inline constexpr std::size_t nbMentions = 5;

inline constexpr double noteMin = 0.0;
inline constexpr double noteMax = 20.0;
inline constexpr double seuilValidation = 10.0;

Mention mentionPour(double note);

std::string_view libelle(Mention mention);

} // namespace uin