#pragma once

#include <iostream>
#include "include/raylib.h"
#define WIDTH   800
#define HEIGHT  600
#define FPS     60

typedef struct {
    float x = 0.f;
    float y = 0.f;
} Pair_2;


class Object {
public:
    Object(const Pair_2 &pos, const float &mass, const Color &color);
    void update(const float &d_t);
    void applyForce(const Pair_2 &force, const float &d_t);
    const Pair_2 &getPos();
    const Pair_2 &getAcc();
    const Pair_2 &getVel();
    const Pair_2 &getForce();
    const Color &getColor();
    ~Object(){ }

private:
    const float f_gravity = 9.80665f;
    float mass, tot_dt;
    Pair_2 pos, acc, vel, force;
    Color color;

    void setPos(Pair_2 pos);
    void setAcc(Pair_2 acc);
    void setVel(Pair_2 vel);
    void setForce(Pair_2 force);
    void setColor(Color color);
};
