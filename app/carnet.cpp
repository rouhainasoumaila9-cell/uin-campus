#include "uincampus/saisie.hpp"

#include <algorithm>
#include <print>
#include <vector>

namespace carnet {

enum class Ordre { Croissant, Decroissant };

struct Statistiques {
    double minimum{};
    double maximum{};
    double moyenne{};
    int nbValidees{};
};

// Calcul des statistiques, sans entree-sortie
[[nodiscard]] Statistiques calculerStatistiques(
    const std::vector<double>& notes)
{
    const auto [mini, maxi] = std::ranges::minmax(notes);

    double somme{0.0};
    int validees{0};

    for (double note : notes) {
        somme += note;

        if (note >= 10.0) {
            ++validees;
        }
    }

    return {
        mini,
        maxi,
        somme / static_cast<double>(notes.size()),
        validees
    };
}

// Appliquer un bonus sans entree-sortie
void appliquerBonus(std::vector<double>& notes, double bonus)
{
    std::ranges::for_each(notes, [bonus](double& note) {
        note = std::clamp(note + bonus, 0.0, 20.0);
    });
}

// Trier les notes sans entree-sortie
void trier(std::vector<double>& notes, Ordre ordre)
{
    if (ordre == Ordre::Croissant) {
        std::ranges::sort(notes);
    } else {
        std::ranges::sort(notes, [](double a, double b) {
            return a > b;
        });
    }
}

void ajouterNote(std::vector<double>& notes)
{
    notes.push_back(uin::lireNote("Saisir une note : "));
    std::println("Note ajoutee avec succes !");
}

void afficherNotes(const std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note.");
        return;
    }

    std::println("\n===== LISTE DES NOTES =====");

    for (std::size_t i = 0; i < notes.size(); ++i) {
        std::println("{:>3}. {:6.2f}", i + 1, notes[i]);
    }
}

void modifierNote(std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note a modifier.");
        return;
    }

    afficherNotes(notes);

    const int position = uin::lireEntier(
        "Numero de la note a modifier : ",
        1,
        static_cast<int>(notes.size())
    );

    notes[static_cast<std::size_t>(position - 1)] =
        uin::lireNote("Nouvelle note : ");

    std::println("Note modifiee avec succes !");
}

void supprimerNote(std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note a supprimer.");
        return;
    }

    afficherNotes(notes);

    const int position = uin::lireEntier(
        "Numero de la note a supprimer : ",
        1,
        static_cast<int>(notes.size())
    );

    notes.erase(notes.begin() + (position - 1));

    std::println("Note supprimee avec succes !");
}

void trierNotes(std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note a trier.");
        return;
    }

    std::println("1. Ordre croissant");
    std::println("2. Ordre decroissant");

    const int choix = uin::lireEntier("Votre choix : ", 1, 2);

    trier(notes, choix == 1 ? Ordre::Croissant : Ordre::Decroissant);

    afficherNotes(notes);
}

void afficherStatistiques(const std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note.");
        return;
    }

    const auto [mini, maxi, moyenne, validees] =
        calculerStatistiques(notes);

    std::println("\n===== STATISTIQUES =====");
    std::println("Minimum : {:.2f}", mini);
    std::println("Maximum : {:.2f}", maxi);
    std::println("Moyenne : {:.2f}", moyenne);
    std::println("Notes validees : {} / {}", validees, notes.size());
}

[[nodiscard]] int afficherMenu()
{
    std::println("\n===== CARNET DE NOTES =====");
    std::println("1. Ajouter une note");
    std::println("2. Afficher les notes");
    std::println("3. Modifier une note");
    std::println("4. Supprimer une note");
    std::println("5. Trier les notes");
    std::println("6. Statistiques");
    std::println("7. Appliquer un bonus");
    std::println("0. Quitter");

    return uin::lireEntier("Votre choix : ", 0, 7);
}

} // namespace carnet

int main()
{
    std::vector<double> notes;
    int choix{};

    do {
        choix = carnet::afficherMenu();

        switch (choix) {
        case 1:
            carnet::ajouterNote(notes);
            break;

        case 2:
            carnet::afficherNotes(notes);
            break;

        case 3:
            carnet::modifierNote(notes);
            break;

        case 4:
            carnet::supprimerNote(notes);
            break;

        case 5:
            carnet::trierNotes(notes);
            break;

        case 6:
            carnet::afficherStatistiques(notes);
            break;

        case 7: {
            const double bonus = uin::lireNote("Bonus : ");
            carnet::appliquerBonus(notes, bonus);
            std::println("Bonus applique avec succes !");
            break;
        }

        case 0:
            std::println("Fin du programme.");
            break;
        }

    } while (choix != 0);

    return 0;
}
