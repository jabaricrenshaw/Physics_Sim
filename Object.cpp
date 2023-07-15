#pragma once
#include <iostream>
#include "Object.h"


Object::Object(Pair_2 pos){
    this->pos = pos;
    this->acc = Pair_2 {0, 0};
    this->vel = Pair_2 {0, 0};
    this->force = Pair_2 {1, 0};
};

void Object::update(float d_t){
    //Gravity calculations

    //Position
    /*
    Pair_2 new_pos = {
        400,
        this->pos.y + this->vel.y * d_t - (0.5f * f_gravity * f_gravity)
    };


    //Velocity
    Pair_2 new_vel = {
        300,
        this->vel.y - (f_gravity * d_t)
    };
    */

    //Force
    this->pos.y = this->pos.y + 5;
    std::cout << this->pos.y << std::endl;


    //this->pos = new_pos;
    //this->vel = new_vel;
}

Pair_2 Object::getPos(){
    return this->pos;
}

Pair_2 Object::getAcc(){
    return this->acc;
}

Pair_2 Object::getVel(){
    return this->vel;
}

Pair_2 Object::getForce(){
    return this->force;
}

float f_gravity = 9.807f;
Pair_2 pos {0, 0};
Pair_2 acc {0, 0};
Pair_2 vel {0, 0};
Pair_2 force {0, 0};
