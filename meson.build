project('main', 'cpp',
    default_options: [
        'default_library=static',
        'optimization=3',
        'cpp_std=c++17',
        'warning_level=3'
    ],
)
message('optimization level is ' + get_option('optimization'))
message('standard: ' + get_option('cpp_std'))

sdl2_dep = dependency('sdl2')
sdl2_ttf_dep = dependency('SDL2_ttf')
sdl2_image_dep = dependency('SDL2_image')
sdl2_mixer_dep = dependency('SDL2_mixer')

executable('main', 
    sources: [
        'src/main.cpp',
        'src/game.cpp',
        'src/graphics.cpp',
        'src/entity.cpp',
        'src/random.cpp',
        'src/audio.cpp',
        'src/sprite.cpp',
        'src/sprite_resource.cpp',
        'src/grid.cpp',
        'src/utils.cpp',
        'src/ball.cpp',
        'src/paddle.cpp',
        'src/score_zone.cpp',
        'src/test_entity.cpp',
        'src/sequencer.cpp',
        'src/camera.cpp',
        'src/sprite_assets.cpp'
    ],
    include_directories: [
        'src/headers',
        'src/libs',
    ],
    dependencies: [
        sdl2_dep,
        sdl2_image_dep,
        sdl2_ttf_dep,
        sdl2_mixer_dep,
    ],
)
