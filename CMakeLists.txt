cmake_minimum_required(VERSION 3.5.1)

project(alpha-mario)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")


find_package(PkgConfig)
pkg_check_modules(SDL2 REQUIRED sdl2)


add_executable(alpha-mario
        src/main.c
        src/fonctionsBasiques.c src/fonctionsBasiques.h 
        src/fonctionsMenu.c src/fonctionsMenu.h
        src/fonctionsPersonnage.c src/fonctionsPersonnage.h)

target_compile_options(alpha-mario PUBLIC ${SDL2_CFLAGS_OTHER})
target_link_libraries(alpha-mario ${SDL2_LIBRAIRIES})
include_directories(alpha-mario ${SDL2_INCLUDE_DIRS})

