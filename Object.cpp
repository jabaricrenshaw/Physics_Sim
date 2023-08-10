#include "Object.h"

Object::Object(const Pair_2 &pos, const float &mass, const Color &color){
    this->mass = mass;
    this->color = color;
    this->pos = pos;
    this->acc = Pair_2 {};
    this->vel = Pair_2 {};
    this->force = Pair_2 {0.f, this->mass * f_gravity};
}

void Object::update(const float &d_t){
    tot_dt += d_t;
    this->setForce( Pair_2{ this->force.x, this->mass * f_gravity });
    this->setAcc(Pair_2 { this->acc.x / this->mass, this->force.y / this->mass });
    this->setVel(Pair_2 { this->vel.x + this->acc.x * d_t, this->vel.y + this->acc.y * d_t });
    this->setPos(Pair_2 { this->pos.x + this->vel.x + (0.5f * this->acc.x * d_t * d_t), this->pos.y + this->vel.y + 0.5f * this->acc.y * d_t * d_t});

    if(this->pos.y >= HEIGHT - 50){
        this->setAcc(Pair_2 {this->acc.x, 0 });
        this->setVel(Pair_2 { this->vel.x, 0 });
        this->setPos(Pair_2 {this->pos.x, HEIGHT - 50 });
    }else if(this->pos.y < 50){
        this->setAcc(Pair_2 {this->acc.x, this->mass * f_gravity });
        this->setVel(Pair_2 { this->vel.x, 0 });
        this->setPos(Pair_2 {this->pos.x, 50 });
    }

    if(this->pos.x >= WIDTH - 50){
        this->setAcc(Pair_2 { 0, this->acc.y });
        this->setVel(Pair_2 { 0, this->vel.y });
        this->setPos(Pair_2 { WIDTH - 50, this->pos.y });
    }else if(this->pos.x < 50){
        this->setAcc(Pair_2 { 0, this->acc.y });
        this->setVel(Pair_2 { 0, this->vel.y });
        this->setPos(Pair_2 { 50, this->pos.y });
    }

    printf("X Force: %f\tAccel: %f\tVel: %f\tPos: %f\tTime: %f\tTotal Time: %f\n", this->force.x, this->acc.x, this->vel.x, this->pos.x, d_t, tot_dt);
    printf("Y Force: %f\tAccel: %f\tVel: %f\tPos: %f\tTime: %f\tTotal Time: %f\n", this->force.y, this->acc.y, this->vel.y, this->pos.y, d_t, tot_dt);
}

void Object::applyForce(const Pair_2 &force, const float &d_t){
    /* Can use +/- for this, just change bindings opposite.
     *   this->setForce ... this->mass * (f_gravity - force.y)
     *   ... should really be sum of forces
    */

    this->setForce(Pair_2 { force.x, this->mass * (f_gravity - force.y) });
    this->setAcc(Pair_2 { this->force.x / this->mass, this->force.y / this->mass });
    this->setVel(Pair_2 { this->vel.x + this->acc.x * d_t, this->vel.y + ( this->acc.y * d_t ) });
    this->setPos(Pair_2 { this->pos.x + this->vel.x + (0.5f * this->acc.x * d_t * d_t), this->pos.y + this->vel.y + ( 0.5f * this->acc.y * d_t * d_t ) });

    if(this->pos.y >= HEIGHT - 50){
        this->setPos(Pair_2 {this->pos.x, HEIGHT - 50 });
    }else if(this->pos.y < 50){
        this->setPos(Pair_2 {this->pos.x, 50 });
    }

    if(this->pos.x >= WIDTH - 50){
        this->setPos(Pair_2 { WIDTH - 50, this->pos.y });
    }else if(this->pos.x < 50){
        this->setPos(Pair_2 { 50, this->pos.y });
    }

    printf("X Force: %f\tAccel: %f\tVel: %f\tPos: %f\tTime: %f\tTotal Time: %f\n", this->force.x, this->acc.x, this->vel.x, this->pos.x, d_t, tot_dt);
    printf("Y Force: %f\tAccel: %f\tVel: %f\tPos: %f\tTime: %f\tTotal Time: %f\n", this->force.y, this->acc.y, this->vel.y, this->pos.y, d_t, tot_dt);

}

const Pair_2 &Object::getPos(){ return this->pos; }
const Pair_2 &Object::getAcc(){ return this->acc; }
const Pair_2 &Object::getVel(){ return this->vel; }
const Pair_2 &Object::getForce(){ return this->force; }
const Color &Object::getColor(){ return this->color; }

const float f_gravity = 9.80665f;
float mass, tot_dt;
Pair_2 pos, acc, vel, force;
Color color;

void Object::setPos(Pair_2 pos){ this->pos = pos; }
void Object::setAcc(Pair_2 acc){ this->acc = acc; }
void Object::setVel(Pair_2 vel){ this->vel = vel; }
void Object::setForce(Pair_2 force){ this->force = force; }
void Object::setColor(Color color){ this->color = color; }
