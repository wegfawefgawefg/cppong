project('main',
    'cpp',
    version: '0.0.1',
    default_options: [
        'default_library=static',
        'optimization=3',
        'cpp_std=c++20',
    ]
)

message('optimization level is ' + get_option('optimization'))

message('standard: ' + get_option('cpp_std'))

sdl2_proj = subproject('sdl2')
sdl2_dep = sdl2_proj.get_variable('sdl2_dep')

SDL2_image_proj = subproject('sdl2_image')
SDL2_image_dep = SDL2_image_proj.get_variable('sdl2_image_dep')

SDL2_mixer_proj = subproject('sdl2_mixer')
SDL2_mixer_dep = SDL2_mixer_proj.get_variable('sdl2_mixer_dep')

SDL2_ttf_proj = subproject('sdl2_ttf')
SDL2_ttf_dep = SDL2_ttf_proj.get_variable('sdl2_ttf_dep')

glm_proj = subproject('glm')
glm_dep = glm_proj.get_variable('glm_dep')

flecs_proj = subproject('flecs')
flecs_dep = flecs_proj.get_variable('flecs_dep')

executable('main',
    sources: [
        'Game.cpp',
        'Graphics.cpp',
        'Grid.cpp',
        'main.cpp',
        'Mixer.cpp',
        'Utilities.cpp',
    ],
    include_directories: [
        'headers',
    ],
    dependencies: [
        sdl2_dep,
        SDL2_image_dep,
        SDL2_mixer_dep,
        SDL2_ttf_dep,
        glm_dep,
        flecs_dep,
    ],
)
