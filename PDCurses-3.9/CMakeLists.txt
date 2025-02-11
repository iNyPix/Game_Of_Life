cmake_minimum_required(VERSION 3.30)
project(PDCurse)

set(CMAKE_C_STANDARD 99)

# Ajouter les fichiers sources communs de PDCurse
file(GLOB PDCurse_COMMON_SOURCES "${CMAKE_SOURCE_DIR}/pdcurses/*.c")

# Détecter la plateforme et ajouter les fichiers sources spécifiques
if(WIN32)
    set(PDCurse_PLATFORM_SOURCES
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/wincon/pdcclip.c"
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/wincon/pdcdisp.c"
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/wincon/pdcgetsc.c"
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/wincon/pdckbd.c"
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/wincon/pdcscrn.c"
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/wincon/pdcsetsc.c"
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/wincon/pdcutil.c"
    )
elseif(UNIX)
    set(PDCurse_PLATFORM_SOURCES
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/x11/pdcclip.c"
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/x11/pdcdisp.c"
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/x11/pdcgetsc.c"
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/x11/pdckbd.c"
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/x11/pdcscrn.c"
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/x11/pdcsetsc.c"
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/x11/pdcutil.c"
            "${CMAKE_SOURCE_DIR}/PDCurses-3.9/x11/pdcx11.c"
    )
endif()

add_library(pdcurses STATIC ${PDCurse_COMMON_SOURCES} ${PDCurse_PLATFORM_SOURCES})

# Spécifier les chemins d'inclusion
include_directories(${CMAKE_SOURCE_DIR})
