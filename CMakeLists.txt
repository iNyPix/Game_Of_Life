cmake_minimum_required(VERSION 3.30)
project(Game_Of_Life)

set(CMAKE_CXX_STANDARD 20)

# Ajouter les chemins d'inclusion pour PDCurse
include_directories(${CMAKE_SOURCE_DIR}/PDCurses-3.9)
include_directories(${CMAKE_SOURCE_DIR}/PDCurses-3.9/pdcurses)

# Ajouter les fichiers sources de PDCurse
file(GLOB PDCurse_SOURCES "${CMAKE_SOURCE_DIR}/PDCurses-3.9/pdcurses/*.c")

# Ajouter les fichiers sources de ton projet
set(SOURCES
        main.cpp
        ${PDCurse_SOURCES}
)

# Ajouter le sous-projet PDCurse
add_subdirectory(${CMAKE_SOURCE_DIR}/PDCurses-3.9)

add_executable(Game_Of_Life ${SOURCES})

# Lier les bibliothèques nécessaires
target_link_libraries(Game_Of_Life pdcurses)
