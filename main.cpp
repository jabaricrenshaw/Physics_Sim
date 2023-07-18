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
        //Gravity calculations
        //Position
        Pair_2 new_pos = {
            this->pos.x,
            this->pos.y + this->vel.y * d_t - (0.5f * f_gravity * f_gravity) * -1
        };

        //Velocity
        Pair_2 new_vel = {
            this->vel.x,
            this->vel.y - (f_gravity * d_t) * -1
        };

        this->pos = new_pos;
        this->vel = new_vel;
    }

    void applyForce(Pair_2 force){
        Pair_2 new_force = {
            this->getForce().x + force.x,
            this->getForce().y + force.y
        };
        this->force = new_force;
        this->f_gravity = 0;
    }

    Pair_2 getPos(){ return this->pos; }
    Pair_2 getAcc(){ return this->acc; }
    Pair_2 getVel(){ return this->vel; }
    Pair_2 getForce(){ return this->force; }


private:
    float f_gravity = 9.807f;
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
        Object(Pair_2{400.0f, 500.0f})
    );
    float time = 0;

    InitWindow(WIDTH, HEIGHT, "Physics Sim");
    SetTargetFPS(FPS);

    while(!WindowShouldClose()){
        BeginDrawing();
        switch(state){
        case STATE_CONTINUE:

            //ClearBackground(DARKBROWN);
            time += GetFrameTime();
            for(size_t i = 0; i < objects.size(); ++i){
                if(IsKeyDown(KEY_SPACE)){
                    objects[i].applyForce(Pair_2 {0, 100});
                    std::cout << objects[i].getForce().x << ' ' << objects[i].getForce().y << std::endl;
                    std::cout << objects[i].getPos().x << ' ' << objects[i].getPos().y << std::endl;
                }else{
                    objects[i].update(time);
                }
                DrawCircle(objects[i].getPos().x, objects[i].getPos().y, 50, RED);
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
