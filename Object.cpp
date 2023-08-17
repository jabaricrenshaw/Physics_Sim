#include "Object.h"

Object::Object(const Pair_2 &pos, const float &mass, const Color &color, const Pair_2 &acc, const Pair_2 &vel){
    this->mass = mass;
    this->color = color;
    this->pos = pos;
    this->acc = acc;
    this->vel = vel;
    this->force = Pair_2 {0.f, 0.f};
}

void Object::update(const float &d_t){
    // Total time elapsed update
    tot_dt += d_t;

    // Calculations
    this->force = Pair_2{ this->force.x, this->mass * f_gravity };
    this->acc = Pair_2{ this->acc.x / this->mass, this->force.y / this->mass };
    this->vel = Pair_2 { this->vel.x + this->acc.x * d_t, this->vel.y + this->acc.y * d_t };
    this->pos = Pair_2 { this->pos.x + this->vel.x + (0.5f * this->acc.x * d_t * d_t), this->pos.y + this->vel.y + 0.5f * this->acc.y * d_t * d_t};

    // Boundaries Check
    checkBounds(d_t);

    // Logging
    printf("X Force: %f\tAccel: %f\tVel: %f\tPos: %f\tTime: %f\tTotal Time: %f\n", this->force.x, this->acc.x, this->vel.x, this->pos.x, d_t, tot_dt);
    printf("Y Force: %f\tAccel: %f\tVel: %f\tPos: %f\tTime: %f\tTotal Time: %f\n", this->force.y, this->acc.y, this->vel.y, this->pos.y, d_t, tot_dt);
}

void Object::applyForce(const Pair_2 &force, const float &d_t){
    // Total time elapsed update
    tot_dt += d_t;

    // Calculations
    /*
     *  this->setForce ... this->mass * (f_gravity - force.y)
     *  Can use +/- for this, just change bindings opposite.
     *  ... should really be sum of forces
    */
    this->force = force;
    if(this->force.y == 0) this->force.y = this->mass * f_gravity;
    this->acc = Pair_2 { this->force.x / this->mass, this->force.y / this->mass };
    this->vel = Pair_2 { this->vel.x + this->acc.x * d_t, this->vel.y + ( this->acc.y * d_t ) };
    this->pos = Pair_2 { this->pos.x + this->vel.x + (0.5f * this->acc.x * d_t * d_t), this->pos.y + this->vel.y + ( 0.5f * this->acc.y * d_t * d_t ) };

    // Boundaries Check
    checkBounds(d_t);

    this->force.x = 0;

    // Logging
    printf("X Force: %f\tAccel: %f\tVel: %f\tPos: %f\tTime: %f\tTotal Time: %f\n", this->force.x, this->acc.x, this->vel.x, this->pos.x, d_t, tot_dt);
    printf("Y Force: %f\tAccel: %f\tVel: %f\tPos: %f\tTime: %f\tTotal Time: %f\n", this->force.y, this->acc.y, this->vel.y, this->pos.y, d_t, tot_dt);

}

bool Object::collidesWith(Object &obj){
    bool coll = abs(this->pos.x - obj.pos.x) < 100 && abs(this->pos.y - obj.pos.y) < 100;

    /*
    *   Write better code here to make force transfer happen...
    *   Image pendulum balls...
    *
    *   Why the fuck is this fucking up
    *   balls get stuck in each other...
    *   Maybe actually do this 'force wise'
    */

    if(coll){
        this->vel = Pair_2 { this->vel.x * -1, this->vel.y };
        obj.setVel(Pair_2 { obj.vel.x * -1, obj.vel.y });
    }

    return coll;
}

void Object::checkBounds(const float &d_t){
    // Y
    if(this->pos.y >= HEIGHT - 50){
        this->force = Pair_2 { this->force.x, this->mass * f_gravity };
        this->acc = Pair_2 { this->acc.x, 0 };
        this->vel = Pair_2 { this->vel.x, 0 };
        this->pos = Pair_2 { this->pos.x, HEIGHT - 50 };
    }else if(this->pos.y < 50){
        this->force = Pair_2 { this->force.x, this->mass * f_gravity };
        this->acc = Pair_2 { this->acc.x, 0 };
        this->vel = Pair_2 { this->vel.x, 0 };
        this->pos = Pair_2 {this->pos.x, 50 };
    }

    // X
    /*
    *   Left and right walls allow bouncing
    *   Returns 100% of velocity in neg direction
    *
    *   Balls start to get stuck in walls under ~70%
    *   velocity return.
    */
    if(this->pos.x >= WIDTH - 50){
        this->force = Pair_2 {0, this->force.y};
        this->acc = Pair_2 { 0, this->acc.y };
        this->vel = Pair_2 { this->vel.x * -1, this->vel.y };
        //this->pos = Pair_2 { WIDTH - 50, this->pos.y };
    }else if(this->pos.x < 50){
        this->force = Pair_2 {0, this->force.y};
        this->acc = Pair_2 { 0, this->acc.y };
        this->vel = Pair_2 { this->vel.x * -1, this->vel.y };
        //this->pos = Pair_2 { 50, this->pos.y };
    }
}

const Pair_2 &Object::getPos(){ return this->pos; }
const Pair_2 &Object::getAcc(){ return this->acc; }
const Pair_2 &Object::getVel(){ return this->vel; }
const Pair_2 &Object::getForce(){ return this->force; }
const Color &Object::getColor(){ return this->color; }

void Object::setPos(Pair_2 pos){ this->pos = pos; }
void Object::setAcc(Pair_2 acc){ this->acc = acc; }
void Object::setVel(Pair_2 vel){ this->vel = vel; }
void Object::setForce(Pair_2 force){ this->force = force; }
void Object::setColor(Color color){ this->color = color; }
