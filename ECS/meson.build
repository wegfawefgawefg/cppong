project('main',
    'cpp',
    version: '0.0.1',
    default_options: [
        'default_library=static',
        'optimization=3',
        'cpp_std=c++17',
        'buildtype=debug',
    ]
)

message('optimization level is ' + get_option('optimization'))

message('standard: ' + get_option('cpp_std'))

sdl2_dep = dependency('sdl2')
SDL2_image_dep = dependency('SDL2_image')
SDL2_mixer_dep = dependency('SDL2_mixer')
SDL2_ttf_dep = dependency('SDL2_ttf')

glm_proj = subproject('glm')
glm_dep = glm_proj.get_variable('glm_dep')

flecs_proj = subproject('flecs')
flecs_dep = flecs_proj.get_variable('flecs_dep')

executable('main',
    sources: [
        'src/Game.cpp',
        'src/Graphics.cpp',
        'src/Grid.cpp',
        'src/main.cpp',
        'src/Mixer.cpp',
        'src/Utilities.cpp',
    ],
    include_directories: [
        'src/headers',
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
