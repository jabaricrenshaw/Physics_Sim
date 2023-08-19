#include <vector>
#include <time.h>
#include <unistd.h>
#include <cstdint>
#include "Object.h"

int main(int argc, char** argv){

    enum { STATE_CONTINUE, STATE_PAUSE } state = STATE_CONTINUE;

    std::vector<Object> objects;
    //   Vertical 3 balls stacked
    /*
    objects.push_back( Object(Pair_2{ WIDTH/2, HEIGHT / 2 }, 100.f, Color{0,0,0,255}) );
    objects.push_back( Object(Pair_2{ WIDTH/2, HEIGHT / 3 }, 100.f, Color{0,0,0,255}) );
    objects.push_back( Object(Pair_2{ WIDTH/2, HEIGHT / 1.5 }, 100.f, Color{0,0,0,255}) );
    */

    //  Horizontal 3 balls evenly spaced

    objects.push_back( Object(Pair_2{ WIDTH/3, 50 }, 100.f, Color{0,0,0,255}, Pair_2{0.f, 0.f}, Pair_2{-5.f, 0.f} ) );
    objects.push_back( Object(Pair_2{ WIDTH/2, 50 }, 100.f, Color{0,0,0,255}, Pair_2{0.f, 0.f}, Pair_2{0.f, 0.f} ) );
    objects.push_back( Object(Pair_2{ WIDTH/1.5, 50 }, 100.f, Color{0,0,0,255}, Pair_2{0.f, 0.f}, Pair_2{5.f, 0.f} ) );


    /*
    objects.push_back( Object(Pair_2{ WIDTH/3, HEIGHT/2 }, 100.f, Color{0,0,0,255}, Pair_2{0.f, 0.f}, Pair_2{5.f, 0.f}) );
    objects.push_back( Object(Pair_2{ WIDTH/1.5, HEIGHT/2 }, 100.f, Color{0,0,0,255}, Pair_2{0.f, 0.f}, Pair_2{-1.f, 0.f}) );
    */

    char coll_text[32];
    uint32_t coll_count = 0;
    //auto coll_text2 = "# Collsions: " + std::to_string(coll_count);

    InitWindow(WIDTH, HEIGHT, "Physics Sim");
    SetTargetFPS(FPS);

    while(!WindowShouldClose()){
        BeginDrawing();
        switch(state){
        case STATE_CONTINUE:

            ClearBackground(DARKBROWN);
            sprintf(coll_text, "Collisions: %d", coll_count);
            DrawText(coll_text, 5, 5, 20, WHITE);

            for(size_t i = 0; i < objects.size(); ++i){

                if(IsKeyPressed(KEY_SPACE)){
                    state = STATE_PAUSE;
                }else if(IsKeyDown(KEY_S)){
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
                    //Edit frame time
                    if(i != j && objects[i].collidesWith(objects[j], GetFrameTime())){
                        coll_count++;
                        printf("\t\t\tCOLLISION DETECTED\n");
                    }
                }

                DrawCircle(objects[i].getPos().x, objects[i].getPos().y, 50, objects[i].getColor());
            }

            break;
        case STATE_PAUSE:
            if(IsKeyPressed(KEY_SPACE)){
                state = STATE_CONTINUE;
            }

            break;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
