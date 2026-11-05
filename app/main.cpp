#include "uincampus/version.hpp"
#include "uincampus/regles.hpp"
#include "uincampus/saisie.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <format>
#include <iostream>
#include <print>
#include <string>
#include <vector>

int main()
{
    // Informations du projet
    std::println("UIN-Campus - Systeme de gestion academique");
    std::println("Version {}", uin::version());

    // Saisie du nom de l'UE
    std::cout << "\nNom de l'UE : ";
    std::string ue;
    if (!std::getline(std::cin, ue)) {
        return 1;
    }

    // Saisie du nombre d'étudiants
    const int nb = uin::lireEntier(
        "Nombre d'etudiants (1 a 200) : ", 1, 200
    );

    // Saisie des notes
    std::vector<double> notes;
    notes.reserve(static_cast<std::size_t>(nb));

    for (int i{1}; i <= nb; ++i) {
        notes.push_back(
            uin::lireNote(
                std::format("Note de l'etudiant {} : ", i)
            )
        );
    }

    // Calcul des statistiques
    double minimum{uin::noteMax};
    double maximum{uin::noteMin};
    double somme{0.0};

    std::size_t admis{0};

    std::array<std::size_t, uin::nbMentions> repartition{};

    for (double note : notes) {
        minimum = std::min(minimum, note);
        maximum = std::max(maximum, note);
        somme += note;

        if (note >= uin::seuilValidation) {
            ++admis;
        }

        const auto indice = static_cast<std::size_t>(
            uin::mentionPour(note)
        );

        ++repartition[indice];
    }

    const double taille = static_cast<double>(notes.size());
    const double moyenne = somme / taille;

    // Calcul de l'écart-type
    double sommeEcarts{0.0};

    for (double note : notes) {
        sommeEcarts += (note - moyenne) * (note - moyenne);
    }

    const double ecartType = std::sqrt(sommeEcarts / taille);

    // Affichage des statistiques
    std::println("\nStatistiques — {} ({} etudiants)", ue, nb);
    std::println("{:-<58}", "");

    std::println("{:<18}: {:6.2f}", "Note minimale", minimum);
    std::println("{:<18}: {:6.2f}", "Note maximale", maximum);
    std::println("{:<18}: {:6.2f}", "Moyenne", moyenne);
    std::println("{:<18}: {:6.2f}", "Ecart-type", ecartType);

    std::println(
        "{:<18}: {} ({:.1f} %)",
        "Admis",
        admis,
        100.0 * static_cast<double>(admis) / taille
    );

    // Histogramme des mentions
    std::println("\nRepartition par mention");

    for (std::size_t i{0}; i < uin::nbMentions; ++i) {
        const auto mention = static_cast<uin::Mention>(i);

        std::println(
            "{:<12} {} ({})",
            uin::libelle(mention),
            std::string(repartition[i], '*'),
            repartition[i]
        );
    }

    return 0;
}