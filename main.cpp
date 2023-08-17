#include <vector>
#include <time.h>
#include "Object.h"

int main(int argc, char** argv){

    enum { STATE_CONTINUE, STATE_PAUSE } state = STATE_CONTINUE;

    std::vector<Object> objects;
    objects.push_back( Object(Pair_2{ WIDTH/3, 50 }, 100.f, Color{0,0,0,255}) );
    objects.push_back( Object(Pair_2{ WIDTH/2, 50 }, 100.f, Color{0,0,0,255}) );
    objects.push_back( Object(Pair_2{ WIDTH/1.5, 50 }, 100.f, Color{0,0,0,255}) );

    InitWindow(WIDTH, HEIGHT, "Physics Sim");
    SetTargetFPS(FPS);

    while(!WindowShouldClose()){
        BeginDrawing();
        switch(state){
        case STATE_CONTINUE:

            ClearBackground(DARKBROWN);

            for(size_t i = 0; i < objects.size(); ++i){

                if(IsKeyDown(KEY_S)){
                    objects[i].applyForce(Pair_2 {0, 490}, GetFrameTime());
                }else if(IsKeyDown(KEY_A)){
                    objects[i].applyForce(Pair_2 {-490, 0}, GetFrameTime());
                }else if(IsKeyDown(KEY_W)){
                    objects[i].applyForce(Pair_2 {0, -490}, GetFrameTime());
                }else if(IsKeyDown(KEY_D)){
                    objects[i].applyForce(Pair_2 {490, 0}, GetFrameTime());
                }else{
                    objects[i].update(GetFrameTime());
                }

                for(size_t j = 0; j < objects.size(); ++j){
                    if(i == j) continue;
                    if(objects[i].collidesWith(objects[j])){
                        printf("\t\t\tCOLLISION DETECTED");
                    }
                }

                DrawCircle(objects[i].getPos().x, objects[i].getPos().y, 50, objects[i].getColor());

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
