#include <iostream>
#include <vector>
#include <time.h>

#include "include/raylib.h"
//#include "Object.h"

#define WIDTH   800
#define HEIGHT  600
#define FPS     60

typedef struct {
    float x;
    float y;
} Pair_2;

class Object {
public:
    Object(Pair_2 pos){
        this->mass = 100.0f;
        this->pos = pos;
        this->acc = Pair_2 {0, 0};
        this->vel = Pair_2 {0, 0};
        this->force = Pair_2 {0, this->mass * f_gravity};
    };

    void update(float d_t){

        if(this->getPos().y >= HEIGHT - 50){
            this->setAcc(Pair_2 {this->acc.x, 0 });
            this->setVel(Pair_2 { this->vel.x, 0 });
            this->setPos(Pair_2 {this->pos.x, HEIGHT - 50 });
            printf("Force: %f   Accel: %f   Vel: %f     Pos: %f     Time: %f\n", this->force.y, this->acc.y, this->vel.y, this->pos.y, d_t);
            return;
        }

        //this->setForce( Pair_2{ this->force.x, this->mass * f_gravity });
        this->setAcc(Pair_2 { this->force.x, this->force.y / this->mass });
        this->setVel(Pair_2 { this->vel.x, this->vel.y + this->acc.y * d_t });
        this->setPos(Pair_2 { this->pos.x, this->pos.y + this->vel.y + 0.5f * this->acc.y * d_t * d_t});

        printf("Force: %f   Accel: %f   Vel: %f     Pos: %f     Time: %f\n", this->force.y, this->acc.y, this->vel.y, this->pos.y, d_t);

    }

    void applyForce(Pair_2 force, float d_t){
        // F = ma

        this->setForce(Pair_2{ this->force.x, this->mass * f_gravity });
        this->setAcc(Pair_2 { this->force.x, this->force.y / this->mass });
        this->setVel(Pair_2 { this->vel.x, 0 });
        this->setPos(Pair_2 { this->pos.x, HEIGHT/2 });

        //std::cout << "Apply: "<< this->force.y << std::endl;
    }

    Pair_2 getPos(){ return this->pos; }
    Pair_2 getAcc(){ return this->acc; }
    Pair_2 getVel(){ return this->vel; }
    Pair_2 getForce(){ return this->force; }


private:
    float f_gravity = 9.80665f;
    float mass;
    Pair_2 pos;
    Pair_2 acc;
    Pair_2 vel;
    Pair_2 force;

    void setPos(Pair_2 pos){ this->pos = pos; }
    void setAcc(Pair_2 acc){ this->acc = acc; }
    void setVel(Pair_2 vel){ this->vel = vel; }
    void setForce(Pair_2 force){ this->force = force; }
};

int main(int argc, char** argv){

    enum { STATE_CONTINUE, STATE_PAUSE } state = STATE_CONTINUE;

    std::vector<Object> objects;
    objects.push_back(
        Object(Pair_2{WIDTH/2, HEIGHT/2})
    );
    float time = 0;

    InitWindow(WIDTH, HEIGHT, "Physics Sim");
    SetTargetFPS(FPS);

    while(!WindowShouldClose()){
        BeginDrawing();
        switch(state){
        case STATE_CONTINUE:

            ClearBackground(DARKBROWN);

            for(size_t i = 0; i < objects.size(); ++i){

                if(IsKeyDown(KEY_SPACE)){
                    objects[i].applyForce(Pair_2 {0, 50}, time);
                    //std::cout << objects[i].getForce().x << ' ' << objects[i].getForce().y << std::endl;
                    //std::cout << objects[i].getPos().x << ' ' << objects[i].getPos().y << std::endl;
                }else{
                    objects[i].update(GetFrameTime());
                }
                DrawCircle(objects[i].getPos().x, objects[i].getPos().y, 50, RED);
                //printf("Force: %f   Accel: %f   Vel: %f     Pos: %f\n", objects[i].getForce().y, objects[i].getAcc().y, objects[i].getVel().y, objects[i].getPos().y);
                //std::cout << objects[i].getPos().x << ' ' << objects[i].getPos().y << std::endl;
                //printf("I-> x: %f   y: %d\n", objects[i].getPos().x, objects[i].getPos().y);
            }

            break;
        case STATE_PAUSE:
            if(IsKeyPressed(KEY_R)){
                state = STATE_CONTINUE;
            }

            break;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
