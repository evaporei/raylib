/*******************************************************************************************
*
*   raylib [core] example - input virtual controls
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.0
*
*   Example create by GreenSnakeLinux (@GreenSnakeLinux),
*   lighter by oblerion (@oblerion) and 
*   reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <math.h>
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    rlInitWindow(screenWidth, screenHeight, "raylib [core] example - input virtual controls");

    const int dpadX = 90;
    const int dpadY = 300;
    const int dpadRad = 25;//radius of each pad
    rlColor dpadColor = BLUE;
    int dpadKeydown = -1;//-1 if not down, else 0,1,2,3 

    
    const float dpadCollider[4][2]= // collider array with x,y position
    {
        {dpadX,dpadY-dpadRad*1.5},//up
        {dpadX-dpadRad*1.5,dpadY},//left
        {dpadX+dpadRad*1.5,dpadY},//right
        {dpadX,dpadY+dpadRad*1.5}//down
    };
    const char dpadLabel[4]="XYBA";//label of Dpad

    float playerX=100;
    float playerY=100;

    rlSetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!rlWindowShouldClose())    // Detect window close button or ESC key
    {
	// Update 
	//--------------------------------------------------------------------------
        dpadKeydown = -1; //reset
        float inputX=0;
        float inputY=0;
        if(rlGetTouchPointCount()>0)
        {//use touch pos
            inputX = rlGetTouchX();
            inputY = rlGetTouchY();
        }
        else
        {//use mouse pos
            inputX = rlGetMouseX();
            inputY = rlGetMouseY();
        }
        for(int i=0;i<4;i++)
        {
            //test distance each collider and input < radius
            if( fabsf(dpadCollider[i][1]-inputY) + fabsf(dpadCollider[i][0]-inputX) < dpadRad)
            {
                dpadKeydown = i;
                break;
            }
        }
        // move player
        switch(dpadKeydown){
            case 0: playerY -= 50*rlGetFrameTime();
            break;
            case 1: playerX -= 50*rlGetFrameTime();
            break;
            case 2: playerX += 50*rlGetFrameTime();
            break;
            case 3: playerY += 50*rlGetFrameTime();
            default:;
        };
	//--------------------------------------------------------------------------
	    
	// Draw 
	//--------------------------------------------------------------------------
       rlBeginDrawing();
            rlClearBackground(RAYWHITE);
            for(int i=0;i<4;i++)
            {
                //draw all pad
                rlDrawCircle(dpadCollider[i][0],dpadCollider[i][1],dpadRad,dpadColor);
                if(i!=dpadKeydown)
                {
                    //draw label
                    rlDrawText(rlTextSubtext(dpadLabel,i,1),
                             dpadCollider[i][0]-5,
                             dpadCollider[i][1]-5,16,BLACK);
                }

            }
            rlDrawText("Player",playerX,playerY,16,BLACK);
        rlEndDrawing();
	//--------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    rlCloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

