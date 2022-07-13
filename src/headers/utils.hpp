#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>
#include <iostream>

void print_glm_vec2(glm::vec2 p){
    std::cout << "( " << p.x << ", " << p.y << " )" << std::endl;
}

#endif