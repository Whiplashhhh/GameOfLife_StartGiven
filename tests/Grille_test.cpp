//
// Created by samuel on 19/11/25.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Grille.h"

// =================================================================================
// 1. Tests de Base (Constructeur, Getters et Setters)
// =================================================================================

TEST_CASE("Grille - Initialisation et Getters") {
    // Test 1: Grille 5x5, non toroïdale
    Grille g(5, 5, false);

    // Vérification des dimensions
    CHECK(g.getWidth() == 5);
    CHECK(g.getHeight() == 5);

    // Vérification de l'état initial (toutes les cellules doivent être mortes)
    for (int x = 0; x < g.getWidth(); ++x) {
        for (int y = 0; y < g.getHeight(); ++y) {
            CHECK_FALSE(g.isCellAlive(x, y));
        }
    }
}

TEST_CASE("Grille - setCellAlive et isCellAlive") {
    Grille g(3, 3, false);

    // Test 2: Activation d'une cellule et vérification
    g.setCellAlive(1, 1, true);
    CHECK(g.isCellAlive(1, 1));

    // Test 3: Vérification d'une autre cellule
    CHECK_FALSE(g.isCellAlive(0, 0));

    // Test 4: Désactivation de la cellule
    g.setCellAlive(1, 1, false);
    CHECK_FALSE(g.isCellAlive(1, 1));

    // Test 5: Tentative de définir une cellule hors limites (ne devrait rien faire)
    g.setCellAlive(3, 3, true);
    // Si la fonction était publique, nous testerions countAliveNeighbors directement,
    // mais elle est privée. Nous testerons donc indirectement via l'update.
}

// =================================================================================
// 2. Tests de la Logique de Voisinage et de Mise à Jour (Topologie Standard)
// =================================================================================

TEST_CASE("Grille Standard - Règle de Survie et Sous-population") {
    // Grille 3x3, non-toroïdale
    Grille g(3, 3, false);

    // Configurer un "Blink Light" au centre (une cellule vivante)
    g.setCellAlive(1, 1, true);

    // Test 6: Cellule vivante avec 0 voisin (sous-population) -> doit mourir
    g.update();
    CHECK_FALSE(g.isCellAlive(1, 1));
}

TEST_CASE("Grille Standard - Règle de Naissance") {
    // Grille 3x3, non-toroïdale
    Grille g(3, 3, false);

    // Configurer un "bloc" pour tester la naissance
    g.setCellAlive(0, 1, true);
    g.setCellAlive(1, 0, true);
    g.setCellAlive(2, 1, true);

    // Test 7: La cellule (1, 1) est morte et a 3 voisins -> doit naître
    g.update();
    CHECK(g.isCellAlive(1, 1));
}

TEST_CASE("Grille Standard - Exemple du Blinker (Période 2)") {
    // Grille 5x5, non-toroïdale
    Grille g(5, 5, false);

    // Phase 1 (Vertical) : 2,1 | 2,2 | 2,3
    g.setCellAlive(2, 1, true);
    g.setCellAlive(2, 2, true);
    g.setCellAlive(2, 3, true);

    // Après 1 update, il doit devenir Horizontal : 1,2 | 2,2 | 3,2
    g.update();

    // Test 8: Vérifier la nouvelle configuration (Horizontal)
    CHECK(g.isCellAlive(1, 2));
    CHECK(g.isCellAlive(2, 2));
    CHECK(g.isCellAlive(3, 2));
    CHECK_FALSE(g.isCellAlive(2, 1)); // L'ancienne cellule verticale doit être morte

    // Après 2 updates, il doit revenir à Vertical
    g.update();

    // Test 9: Vérifier le retour à la configuration initiale (Vertical)
    CHECK(g.isCellAlive(2, 1));
    CHECK(g.isCellAlive(2, 2));
    CHECK(g.isCellAlive(2, 3));
    CHECK_FALSE(g.isCellAlive(1, 2)); // L'ancienne cellule horizontale doit être morte
}

// =================================================================================
// 3. Tests de la Logique de Voisinage (Topologie Toroïdale)
// =================================================================================

TEST_CASE("Grille Toroïdale - Voisins aux Bords") {
    // Grille 3x3, toroïdale
    Grille g(3, 3, true);

    // Activer la cellule centrale (1, 1) et toutes les cellules d'angle
    g.setCellAlive(1, 1, true);
    g.setCellAlive(0, 0, true);
    g.setCellAlive(2, 0, true);
    g.setCellAlive(0, 2, true);
    g.setCellAlive(2, 2, true);

    // Test 10: La cellule (1, 1) a 4 voisins vivants.
    // L'implémentation de `countAliveNeighbors` est privée, nous devons donc tester l'effet sur `update`.
    // La cellule (1, 1) avec 4 voisins doit MOURIR (surpopulation).
    g.update();
    CHECK_FALSE(g.isCellAlive(1, 1));

    // Test 11: Vérifier un cas de wrap-around pour la Naissance.
    // La cellule (1, 0) est morte et a les voisins (0, 0), (2, 0), et (1, 1) (tous vivants) = 3 voisins.
    // Après l'update, (1, 1) est morte, mais (0, 0) et (2, 0) sont vivantes.
    // Réinitialisation pour un test clair
    Grille g_wrap(3, 3, true);
    g_wrap.setCellAlive(0, 2, true); // Voisin Nord-Ouest de (2, 0) via wrap
    g_wrap.setCellAlive(2, 2, true); // Voisin Nord-Est de (0, 0) via wrap
    g_wrap.setCellAlive(1, 0, true); // Voisin Nord de (1, 2)

    // La cellule (1, 2) a 3 voisins : (0, 2), (2, 2) et (1, 0) via wrap -> doit NAÎTRE
    g_wrap.update();
    CHECK(g_wrap.isCellAlive(1, 2));
}

// =================================================================================
// 4. Tests additionnels demandés (randomDistribution)
// =================================================================================

TEST_CASE("Grille - randomDistribution produit des grilles différentes") {
    // Utiliser une taille raisonnable pour réduire fortement la probabilité de collision aléatoire identique.
    const int W = 10;
    const int H = 10;

    Grille g1(W, H, false);
    Grille g2(W, H, false);

    // Remplir aléatoirement les deux grilles
    g1.randomDistribution();
    g2.randomDistribution();

    // Vérifier qu'il existe au moins une cellule différente entre les deux grilles
    bool differ = false;
    for (int x = 0; x < W && !differ; ++x) {
        for (int y = 0; y < H; ++y) {
            if (g1.isCellAlive(x, y) != g2.isCellAlive(x, y)) {
                differ = true;
                break;
            }
        }
    }

    CHECK(differ); // Très improbable d'être false pour 10x10 random
}
