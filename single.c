#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

void game_step();

int SPEED = 6.5f;
int BALL_RADIUS = 5;

int player_score = 0;

const int screenWidth = 450;
const int screenHeight = 800;

Rectangle player = { (float)screenWidth/2, 600, 50,10};

Vector2 ballPos = { (float)screenWidth/2, (float)screenHeight/2 };
Vector2 ballSpeed = { 0,-4};

float epsilon = 0;
int n_games= 0;

void train(){
    int total_score = 0;
    int record = 0;
    while (1){
        float old_state = {ballPos.x,ballPos.y,player.x,player.y,ballSpeed.x,ballSpeed.y};

        epsilon = 80- n_games;


    }

}


int main(void)
{

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        game_step();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


void game_step(){
    if (IsKeyDown(KEY_A)) player.x -= SPEED;
    if (IsKeyDown(KEY_D)) player.x += SPEED;

    ballPos = Vector2Add(ballPos,ballSpeed);

    if ((player.x + player.width) >= GetScreenWidth()) player.x = GetScreenWidth() - player.width;
    else if (player.x <=0) player.x = 0;

    if ((ballPos.y + BALL_RADIUS) >= GetScreenHeight()){
        ballSpeed.y *=-1;
        ballPos.y = GetScreenHeight() - BALL_RADIUS;
    }
    if (ballPos.y - BALL_RADIUS <= 0){
        player_score++;
        ballSpeed.y *=-1;
    }

    if (ballPos.x - BALL_RADIUS <= 0){
        ballSpeed.x *=-1;
    }
    else if (ballPos.x + BALL_RADIUS >= GetScreenWidth() ){
        ballSpeed.x *=-1;
    }

    if (ballPos.y  >= player.y + 70){
        puts("LOST");
        ballPos.x= (float)screenWidth/2;
        ballPos.y=(float)screenHeight/2;
    }
    // BALL COLLISION
    if(CheckCollisionCircleRec(ballPos,BALL_RADIUS,player)){
        float playerCenter = player.x + (player.width/2);
        float d = (playerCenter - ballPos.x) ;
        ballSpeed.x += d * -0.1;
        ballSpeed.y *= -1;
    }

    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText(TextFormat("Player Score: %i", player_score), 10, 10, 20, DARKGRAY);


    DrawRectangleRec(player,BLUE);


    DrawCircleV(ballPos, BALL_RADIUS, BLACK);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
