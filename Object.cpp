#include "Object.h"

Object::Object(const Pair_2 &pos, const float &mass, const Color &color, const Pair_2 &acc, const Pair_2 &vel){
    this->mass = mass;
    this->color = color;
    this->pos = pos;
    this->acc = acc;
    this->vel = vel;
    this->gpe = 0.f;
    this->ke = Pair_2 {0.f, 0.f};
    this->force = Pair_2 {0.f, 0.f};
}

void Object::update(const float &d_t){
    // Total time elapsed update
    tot_dt += d_t;

    // Gravity Calculations
    this->force = Pair_2{ this->force.x, this->mass * f_gravity };
    this->acc = Pair_2{ this->acc.x / this->mass, this->force.y / this->mass };
    this->vel = Pair_2 { this->vel.x + this->acc.x * d_t, this->vel.y + this->acc.y * d_t };
    this->pos = Pair_2 { this->pos.x + this->vel.x + (0.5f * this->acc.x * d_t * d_t), this->pos.y + this->vel.y + 0.5f * this->acc.y * d_t * d_t};

    this->gpe = this->mass * f_gravity * ( static_cast<float>(HEIGHT) - this->pos.y );
    this->ke = Pair_2{ 0.5f * this->mass * this->vel.x * this->vel.x, 0.5f * this->mass * this->vel.y * this->vel.y};

    // Boundaries Check
    checkBounds(d_t);

    // Logging
    printf("Force: (%.2f, %.2f)\tAccel: (%.2f, %.2f)\tVel: (%.2f, %.2f)\tPos: (%.2f, %.2f)ΔT: %f\n", this->force.x, this->force.y, this->acc.x, this->acc.y, this->vel.x, this->vel.y, this->pos.x, this->pos.y, tot_dt);
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

    this->gpe = this->mass * f_gravity * ( static_cast<float>(HEIGHT) - this->pos.y );
    this->ke = Pair_2{ 0.5f * this->mass * this->vel.x * this->vel.x, 0.5f * this->mass * this->vel.y * this->vel.y};


    // Boundaries Check
    checkBounds(d_t);

    this->force.x = 0;

    // Logging
    printf("Force: (%.2f, %.2f)\tAccel: (%.2f, %.2f)\tVel: (%.2f, %.2f)\tPos: (%.2f, %.2f)ΔT: %f\n", this->force.x, this->force.y, this->acc.x, this->acc.y, this->vel.x, this->vel.y, this->pos.x, this->pos.y, tot_dt);

}

bool Object::collidesWith(Object &obj, const float &d_t){
    bool coll = abs(this->pos.x - obj.pos.x) < 100 && abs(this->pos.y - obj.pos.y) < 100;

    /*
    *   Write better code here to make force transfer happen...
    *   !!! Image pendulum balls... seems to be simulating this with velocity updates only
    *   !!!Maybe actually do this 'force wise'
    *
    *   Why the fuck is this fucking up
    *   balls get stuck in each other...
    */

    /*
    *   Force from velocity
    *   F = (m * v)/d_t
    *   F * d_t = m * v
    *   v = (F * d_t) / m
    */

    // X
    if(coll){
        /*
        *   Update function overrides changes to velocity.
        *   ... Especially with working gravity.
        *   Special calcs for vert.
        *
        *   !!! This collision needs to be completed with energy calculations !!!
        */


        Pair_2 temp = this->vel;
        this->vel = Pair_2 { obj.vel.x, obj.vel.y };
        obj.setVel(Pair_2 { temp.x, temp.y });


        /*
        *   SCRAP
        *    obj.applyForce(Pair_2 { this->mass * (this->vel.x/d_t), 0}, d_t);
        *    printf("Applied force to otherObject -> x: %f\ty: %f\n", this->mass * (this->vel.x/1), 0);
        *    printf("F = %f * (%f/%f) = %f\n", this->mass, this->vel.x, 1, this->mass * (this->vel.x/1));
        *
        *    this->applyForce(Pair_2 { obj.mass * (obj.vel.x/d_t), 0}, d_t);
        *    printf("Applied force to *this -> x: %f\ty: %f\n", obj.mass * (obj.vel.x/1), 0);
        *    printf("F = %f * (%f/%f) = %f\n", obj.mass, obj.vel.x, 1, obj.mass * (obj.vel.x/1));
        *    this->color = RED;
        */




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
