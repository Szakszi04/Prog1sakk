cmake_minimum_required(VERSION 3.11)
project(chess)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
# find_package(SDL2_net REQUIRED)
# find_package(SDL2_mixer REQUIRED)
find_package(SDL2_gfx REQUIRED)

add_executable(chess)
target_sources(chess PRIVATE
    src/babuk_lepese.c
    src/bool_nelkuli.c
    src/main.c
)
target_include_directories(chess PRIVATE include/chess)
target_compile_options(chess PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
target_link_libraries(chess PRIVATE
    SDL2::Main
    SDL2::Image
    SDL2::TTF
    # SDL2::Net
    # SDL2::Mixer
    SDL2::GFX
)
target_compile_options(chess PRIVATE -fsanitize=address -fno-omit-frame-pointer)
target_link_options(chess PRIVATE -fsanitize=address)
