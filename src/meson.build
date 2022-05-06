project('main', 'cpp',
    default_options: [
        'default_library=static',
        'optimization=3',
    ],
)
message('optimization level is ' + get_option('optimization'))

sdl2_dep = dependency('sdl2')
sdl2_ttf_dep = dependency('SDL2_ttf')
sdl2_image_dep = dependency('SDL2_image')
sdl2_mixer_dep = dependency('SDL2_mixer')

executable('main', 
    sources: [
        'main.cpp',
        'game.cpp',
        'graphics.cpp'
    ],
    include_directories: [
        'headers',
    ],
    dependencies: [
        sdl2_dep,
        sdl2_image_dep,
        sdl2_ttf_dep,
        sdl2_mixer_dep,
    ],
)

