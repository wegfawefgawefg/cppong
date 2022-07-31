#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>


#include "sprite.hpp"

Sprite::Sprite(SpriteResource* resource) {
    this->resource = resource;
    anim_index = 0;
    frame_index = 0;
    timer = 0;
    speed = 1.0;
    // randomize_timer();
}

Sprite::~Sprite() {
    /*  DO NOT closing the sprite resource here,
      many sprites will be sharing the same resource*/
}

void Sprite::reset_speed() {
    this->speed = 1.0;
}

void Sprite::randomize_timer() {
    this->timer = fmodf(rand(), this->resource->frame_duration);
}

void Sprite::set_speed(float speed) {
    speed = fabs(speed); // speed must be positive
    this->speed = speed;
}

void Sprite::rollover_to_begining_of_anim() {
    // if the current frame is greater than the number of frames in the target animation,
    // set the frame to the first frame of the target animation
    if (this->frame_index >= this->resource->anims_num_frames[this->anim_index]) {
        this->frame_index = 0;
        this->timer = 0;
    }
}

void Sprite::set_anim_frame_index(int frame_index) {
    this->frame_index = frame_index;
    this->rollover_to_begining_of_anim();
}

void Sprite::set_anim(int anim_index) {
    this->anim_index = anim_index;
    // if the animation is invalid, set it to the first animation
    //  //  EMERGENCY TO PREVENT CRASHING BUT IF THIS HAPPENS YOU HAVE A BUG
    if (anim_index >= this->resource->get_num_anims()) {
        this->anim_index = 0;
    }
    this->rollover_to_begining_of_anim();
}

void Sprite::set_scale(glm::vec2 scale) {
    this->scale = scale;
}

void Sprite::set_size(glm::vec2 size) {
    glm::vec2 resource_size = glm::vec2(this->resource->width, this->resource->height);
    this->scale = size / resource_size;
}

void Sprite::multiply_scale(glm::vec2 scale) {
    this->scale *= scale;
}

void Sprite::step(float dt) {
    this->timer += dt * this->speed;
    if (this->timer >= this->resource->frame_duration) {
        this->timer = 0;
        this->frame_index++;
        if (this->frame_index >= this->resource->anims_num_frames[this->anim_index]) {
            this->frame_index = 0;
        }
    }
}