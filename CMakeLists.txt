cmake_minimum_required(VERSION 3.12)
project(RetroMenu VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(retro_menu
    src/main.c
    src/graphics.c
    src/input.c
    src/menu.c
)

target_link_libraries(retro_menu
    ${SDL2_LIBRARIES}
    SDL2_ttf
)

install(TARGETS retro_menu DESTINATION bin)