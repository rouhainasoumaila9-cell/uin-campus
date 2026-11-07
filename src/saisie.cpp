#include "uincampus/saisie.hpp"
#include "uincampus/regles.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

namespace uin {

namespace {

struct EntierLu {
    bool valide;
    int valeur;
};

struct ReelLu {
    bool valide;
    double valeur;
};

[[nodiscard]] EntierLu versEntier(std::string_view ligne)
{
    std::istringstream flux{std::string(ligne)};
    int valeur{};
    char reste{};

    if (!(flux >> valeur) || (flux >> reste)) {
        return {false, 0};
    }

    return {true, valeur};
}

[[nodiscard]] ReelLu versReel(std::string ligne)
{
    for (char& caractere : ligne) {
        if (caractere == ',') {
            caractere = '.';
        }
    }

    std::istringstream flux{ligne};
    double valeur{};
    char reste{};

    if (!(flux >> valeur) || (flux >> reste) || !std::isfinite(valeur)) {
        return {false, 0.0};
    }

    return {true, valeur};
}

} // namespace

int lireEntier(std::string_view invite, int minimum, int maximum)
{
    while (true) {
        std::cout << invite;

        std::string ligne;
        if (!std::getline(std::cin, ligne)) {
            return minimum;
        }

        const auto [valide, valeur] = versEntier(ligne);

        if (!valide) {
            std::cout << "Saisie invalide.\n";
        } else if (valeur < minimum || valeur > maximum) {
            std::cout << "Valeur comprise entre "
                      << minimum << " et " << maximum << ".\n";
        } else {
            return valeur;
        }
    }
}

double lireNote(std::string_view invite)
{
    while (true) {
        std::cout << invite;

        std::string ligne;
        if (!std::getline(std::cin, ligne)) {
            return noteMin;
        }

        const auto [valide, note] = versReel(ligne);

        if (!valide) {
            std::cout << "Saisie invalide.\n";
        } else if (note < noteMin || note > noteMax) {
            std::cout << "La note doit être comprise entre 0 et 20.\n";
        } else {
            return note;
        }
    }
}

} // namespace uin
