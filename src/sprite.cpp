#include <iostream>
#include <vector>

#include "sprite.hpp"

Sprite::Sprite(SpriteResource& resource) : resource(resource) {
    anim_index = 0;
    frame_index = 0;
    timer = 0;
    speed = 1.0;
    // randomize_timer();
}
