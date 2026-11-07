#include "uincampus/version.hpp"
#include "uincampus/regles.hpp"
#include "uincampus/saisie.hpp"
#include "uincampus/calculs.hpp"

#include <cstddef>
#include <format>
#include <iostream>
#include <print>
#include <string>
#include <string_view>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc > 1 && std::string_view{argv[1]} == "--version") {
        std::println("UIN-Campus version {}", uin::version());
        return 0;
    }

    std::println("UIN-Campus - Releve de notes academique");

    std::cout << "\nNom de l'etudiant : ";
    std::string nom;

    if (!std::getline(std::cin, nom)) {
        return 1;
    }

    const int nbUE = uin::lireEntier(
        "Nombre d'UE (1 a 20) : ", 1, 20
    );

    std::vector<double> notes;
    std::vector<double> coefficients;

    notes.reserve(static_cast<std::size_t>(nbUE));
    coefficients.reserve(static_cast<std::size_t>(nbUE));

    for (int i{1}; i <= nbUE; ++i) {
        std::println("\nUE {}", i);

        const double note = uin::lireNote(
            std::format("Note de l'UE {} : ", i)
        );

        const int coefficient = uin::lireEntier(
            std::format("Coefficient de l'UE {} (1 a 10) : ", i),
            1,
            10
        );

        notes.push_back(note);
        coefficients.push_back(static_cast<double>(coefficient));
    }

    const auto statistiques = uin::calculerStatistiques(notes);
    const double moyenneSimple = uin::moyenne(notes);
    const double moyennePonderee = uin::moyenne(notes, coefficients);
    const std::size_t validees = uin::compterValidees(notes);

    const double pourcentage =
        100.0 * static_cast<double>(validees)
        / static_cast<double>(notes.size());

    const auto mention = uin::mentionPour(moyennePonderee);

    std::println("\n======================================");
    std::println("          RELEVE DE NOTES");
    std::println("======================================");

    std::println("Etudiant : {}", nom);
    std::println("Nombre d'UE : {}", nbUE);

    std::println("\nStatistiques :");

    std::println("Note minimale     : {:6.2f}", statistiques.minimum);
    std::println("Note maximale     : {:6.2f}", statistiques.maximum);
    std::println("Moyenne simple    : {:6.2f}", moyenneSimple);
    std::println("Moyenne ponderee  : {:6.2f}", moyennePonderee);
    std::println("Ecart-type        : {:6.2f}", statistiques.ecartType);

    std::println(
        "UE validees       : {} / {} ({:.1f} %)",
        validees,
        notes.size(),
        pourcentage
    );

    std::println("Mention           : {}", uin::libelle(mention));
    std::println("======================================");

    return 0;
}

