#include "uincampus/saisie.hpp"
#include "uincampus/regles.hpp"

#include <iostream>
#include <sstream>
#include <string>

namespace uin {

int lireEntier(std::string_view invite, int minimum, int maximum)
{
    while (true) {
        std::cout << invite;

        std::string ligne;
        if (!std::getline(std::cin, ligne)) {
            return minimum;
        }

        std::istringstream flux{ligne};
        int valeur{};
        char reste{};

        if (!(flux >> valeur) || (flux >> reste)) {
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

        for (char& caractere : ligne) {
            if (caractere == ',') {
                caractere = '.';
            }
        }

        std::istringstream flux{ligne};
        double note{};
        char reste{};

        if (!(flux >> note) || (flux >> reste)) {
            std::cout << "Saisie invalide.\n";
        } else if (note < noteMin || note > noteMax) {
            std::cout << "La note doit être comprise entre 0 et 20.\n";
        } else {
            return note;
        }
    }
}

} // namespace uin