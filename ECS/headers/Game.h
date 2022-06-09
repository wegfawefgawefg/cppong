//
// Created by Kyle Dougan on 6/6/22.
//

#pragma once

#include <SDL.h>

#include "flecs/flecs.h"
#include "Graphics.h"
#include "Mixer.h"

class Game
{
public:
    Game();

    ~Game() = default;

    void run();

    void handleEvents();

    void update();

private:
    int screenWidth = 640;
    int screenHeight = 480;

    Graphics *graphics;
    Mixer *mixer;

    bool isRunning = false;
    Uint64 lastFrameTime = 0;
    flecs::entity fpsText;
    flecs::world world;

    void setupSystems();
};
