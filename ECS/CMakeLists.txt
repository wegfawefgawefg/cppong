cmake_minimum_required(VERSION 3.22)
project(ecs_test)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/headers)

include_directories(${PROJECT_SOURCE_DIR}/external)

add_executable(
        ${PROJECT_NAME}
        external/flecs/flecs.c
        external/flecs/flecs.h
        headers/Components.h
        headers/Game.h
        headers/Graphics.h
        headers/Mixer.h
        headers/Utilities.h
        main.cpp
        Game.cpp
        Graphics.cpp
        Mixer.cpp
        Utilities.cpp
)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static)

find_package(sdl2-ttf CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2_ttf)

find_package(sdl2-mixer CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2_mixer)
