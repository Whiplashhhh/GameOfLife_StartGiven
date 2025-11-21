cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- Configuration de l'exécutable principal (GUI) ---

# Ajouter l'exécutable
add_executable(
        GameOfLife
        src/main_graphic.cpp
        src/Grille.cpp
        src/Renderer.cpp
        src/Grille.cpp
        src/main_graphic.cpp
)

# Définir le chemin vers SFML (à adapter)
set(SFML_DIR "C:/Users/vanba/OneDrive/Desktop/_IUT/_BUT2_INFO/semeste_3/R3_02_cpp_py/cpp/tp3_base_prof/GameOfLife_StartGiven/SFML-2.5.1/lib/cmake/SFML")

# Rechercher et lier la bibliothèque SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(GameOfLife sfml-graphics sfml-window sfml-system)

# Ajouter le répertoire 'src' et 'includes' aux includes
target_include_directories(
        GameOfLife
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

# --- Configuration des tests unitaires ---
enable_testing()

add_executable(GameOfLifeTests tests/Grille_test.cpp src/Grille.cpp)
target_include_directories(
        GameOfLifeTests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
)
add_test(
        NAME GameOfLifeTests
        COMMAND GameOfLifeTests
)