#include <vector>
#include <iostream>

#include "graphics.hpp"

void Graphics::load_sprite_resources() {
    this->add_sprite_resource(  //  missing
        "assets/images/missing.png",
        48, 48,
        std::vector<int> { 1 },
        0.2
    );
    this->add_sprite_resource(  //  guy
        "assets/images/guy.png",
        128, 128,
        std::vector<int> { 4, 4, 4, 4 },
        0.2
    );
    this->add_sprite_resource(  //  reticle
        "assets/images/reticle.png",
        64, 64,
        std::vector<int> { 1 },
        0.2
    );
}