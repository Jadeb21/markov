cmake_minimum_required(VERSION 3.24)
project(2526_TI301_PJT C)

set(CMAKE_C_STANDARD 11)

set(SOURCES
        main.c
        utils.c
        hasse.c
        list.c # Ajoute ce fichier seulement si tes fonctions sont dedans
)

add_executable(TI_301_PJT ${SOURCES})

