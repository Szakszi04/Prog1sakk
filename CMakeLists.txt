cmake_minimum_required(VERSION 3.11)
project(nagyhazi C)

set(CMAKE_C_STANDARD 23)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
# find_package(SDL2_net REQUIRED)
# find_package(SDL2_mixer REQUIRED)
find_package(SDL2_gfx REQUIRED)

add_executable(nagyhazi)
target_sources(nagyhazi PRIVATE
    src/fajl.c
    src/grafika.c
    src/lancolt_lista.c
    src/lepesek_babukra.c
    src/lepesek.c
    src/lepeskisegitofuggvenyek.c
    src/main.c
    src/sakktabla.c
)

target_compile_options(nagyhazi PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
target_link_libraries(nagyhazi PRIVATE
    SDL2::Main
    SDL2::Image
    SDL2::TTF
    # SDL2::Net
    # SDL2::Mixer
    SDL2::GFX
)

target_compile_options(nagyhazi PRIVATE -fsanitize=address -fno-omit-frame-pointer)
target_link_options(nagyhazi PRIVATE -fsanitize=address)
