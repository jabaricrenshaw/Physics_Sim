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
    Object(const Pair_2 &pos){
        this->pos = pos;
        this->acc = Pair_2 {0, 0};
        this->vel = Pair_2 {0, 0};
        this->force = Pair_2 {0, 0};
    };

    void update(const float &d_t){
        //Gravity calculations
        //Position
        Pair_2 new_pos = {
            this->pos.x,
            this->pos.y + this->vel.y * d_t - (0.5f * f_gravity * f_gravity)
        };

        //Velocity
        Pair_2 new_vel = {
            this->vel.x,
            this->vel.y - (f_gravity * d_t)
        };

        //Force

        if(new_pos.y > HEIGHT){
            new_pos.y = HEIGHT;
        }
        if(new_pos.y < 0){
            new_pos.y = 0;
        }
        if(new_pos.x > WIDTH){
            new_pos.x = WIDTH;
        }
        if(new_pos.x < 0){
            new_pos.x = 0;
        }

        this->pos = new_pos;
        this->vel = new_vel;
    }

    Pair_2 getPos(){ return this->pos; }
    Pair_2 getAcc(){ return this->acc; }
    Pair_2 getVel(){ return this->vel; }
    Pair_2 getForce(){ return this->force; }

    ~Object(){ }

private:
    float f_gravity = 9.807f;
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
        Object(Pair_2{400.0f, 300.0f})
    );
    float time = 0;

    InitWindow(WIDTH, HEIGHT, "Physics Sim");
    SetTargetFPS(FPS);

    while(!WindowShouldClose()){
        BeginDrawing();
        switch(state){
        case STATE_CONTINUE:

            ClearBackground(DARKBROWN);
            time += GetFrameTime();
            for(size_t i = 0; i < objects.size(); ++i){
                objects[i].update(time);
                //printf("I-> x: %f   y: %d\n", objects[i].getPos().x, objects[i].getPos().y);
                DrawCircle(objects[i].getPos().x, objects[i].getPos().y, 50, RED);
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
