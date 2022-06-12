//
// Created by Kyle Dougan on 6/6/22.
//

#pragma once

#include <random>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

enum class Align
{
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    CENTER_LEFT,
    CENTER,
    CENTER_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT
};

glm::vec2 getAlignOffsets(Align align, int width, int height);

float frand(float min, float max);

std::vector<std::string> getFilesInDirectory(const std::string &directory, const std::string &pattern);
