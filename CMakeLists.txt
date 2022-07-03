cmake_minimum_required(VERSION 3.0.0)
project(cppong VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(src/headers)

add_executable(cppong
    src/main.cpp
    src/audio.cpp
    src/emitter.cpp
    src/entity.cpp
    src/game.cpp
    src/graphics.cpp
    src/random.cpp
    src/sprite_resource.cpp
    src/sprite.cpp
    src/transient.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static)

find_package(sdl2-ttf CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2_ttf)

find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2_image)

find_package(sdl2-mixer CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2_mixer)
