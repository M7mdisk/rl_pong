#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

int SPEED = 5.0f;

int enemy_score, player_score = 0;

int BALL_RADIUS = 5;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    Rectangle player = { 100, (float)screenHeight/2, 10,50};
    Rectangle enemy = { screenWidth - 100, (float)screenHeight/2,10, 50 };

    Vector2 ballPos = { (float)screenWidth/2, (float)screenHeight/2 };
    Vector2 ballSpeed = { -3,-3};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_W)) player.y -= SPEED;
        if (IsKeyDown(KEY_S)) player.y += SPEED;

        if (IsKeyDown(KEY_K)) enemy.y -= SPEED;
        if (IsKeyDown(KEY_J)) enemy.y += SPEED;

        ballPos = Vector2Add(ballPos,ballSpeed);

        // LIMIT MOVEMENT

        if ((player.y + player.height) >= GetScreenHeight()) player.y = GetScreenHeight() - player.height;
        else if (player.y <=0) player.y = 0;
        if ((enemy.y + enemy.height) >= GetScreenHeight()) enemy.y = GetScreenHeight() - enemy.height;
        else if (enemy.y <=0) enemy.y = 0;

        if ((ballPos.y + BALL_RADIUS) >= GetScreenHeight()){
            ballSpeed.y *=-1;
            ballPos.y = GetScreenHeight() - BALL_RADIUS;
        }
        if (ballPos.y - BALL_RADIUS <= 0){
            ballSpeed.y *=-1;
        }
        // BALL COLLISION
        if(CheckCollisionCircleRec(ballPos,BALL_RADIUS,player)){
            float playerCenter = player.y + (player.height/2);
            float d = (playerCenter - ballPos.y) / 10;
            ballSpeed.y += d * -0.1;
            ballSpeed.x *= -1;
        }

        if(CheckCollisionCircleRec(ballPos,BALL_RADIUS,enemy)){
            float enemyCenter = enemy.y + (enemy.height/2);
            float d = (enemyCenter - ballPos.y) / 10;
            ballSpeed.y += d * -0.1;
            ballSpeed.x *= -1;
        }
        
        //----------------------------------------------------------------------------------
        // Check win state
        //----------------------------------------------------------------------------------

        if (ballPos.x < player.x - 50){
            puts("ENEMY WON");
            enemy_score +=1;
            ballPos.x =  (float)screenWidth/2;
            ballPos.y =(float)screenHeight/2 ;
        }else if (ballPos.x > enemy.x + 50){
            puts("PLAYER WON");
            player_score +=1;
            ballPos.x =  (float)screenWidth/2;
            ballPos.y =(float)screenHeight/2 ;
        }


        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Player Score: %i, Enemy Score: %i", player_score, enemy_score), 10, 10, 20, DARKGRAY);
        

        DrawRectangleRec(player,BLUE);
        DrawRectangleRec(enemy,MAROON);


        DrawCircleV(ballPos, BALL_RADIUS, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


