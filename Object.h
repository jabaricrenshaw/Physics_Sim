#pragma once

#include <iostream>
#include "include/raylib.h"

#define WIDTH   800
#define HEIGHT  600
#define FPS     60

struct Pair_2 {
    float x = 0.f;
    float y = 0.f;
};


class Object {
public:
    Object(const Pair_2 &pos, const float &mass, const Color &color, const Pair_2 &acc = Pair_2 {0.f, 0.f}, const Pair_2 &vel = Pair_2 {0.f, 0.f});
    void update(const float &d_t);
    void applyForce(const Pair_2 &force, const float &d_t);
    bool collidesWith(Object &obj, const float &d_t);
    const Pair_2 &getPos();
    const Pair_2 &getAcc();
    const Pair_2 &getVel();
    const Pair_2 &getForce();
    const Color &getColor();
    float tot_dt = 0;
    ~Object(){ }

private:
    const float f_gravity = 9.80665f;
    float mass;
    float gpe;
    Pair_2 pos, acc, vel, force, ke;
    Color color;

    void setPos(Pair_2 pos);
    void setAcc(Pair_2 acc);
    void setVel(Pair_2 vel);
    void setForce(Pair_2 force);
    void setColor(Color color);
    void checkBounds(const float &d_t);
};
