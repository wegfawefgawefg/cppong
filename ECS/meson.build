project('main', 'cpp',
    default_options: [
        'default_library=static',
        'optimization=3',
        'cpp_std=c++17',
    ],
)
message('optimization level is ' + get_option('optimization'))
message('standard: ' + get_option('cpp_std'))

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
        'external',
    ],
    dependencies: [
        dependency('sdl2'),
        dependency('SDL2_ttf'),
        dependency('SDL2_image'),
        dependency('SDL2_mixer'),
        dependency('glm', required : true, fallback : ['glm','glm_dep']),
    ],
)
