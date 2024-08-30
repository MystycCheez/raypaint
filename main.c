#include "core_functions.c"
#include "etc.h"

#include "raylib.h"
#include "raymath.h"

#include "stdio.h"

#include <stdlib.h>
#include <assert.h>

int main(void)
{
    SetTraceLogLevel(LOG_WARNING);

    // unsigned int ToolState = TOOL_BRUSH;

    const int screenWidth  = 320 * 5;
    const int screenHeight = 200 * 5;

    // int x,y = 0;

    Image Canvas_image = GenImageColor(screenWidth, screenHeight, DARKGREEN);
    // Rectangle Canvas_rect = {0, 0, Canvas_image.width, Canvas_image.height};

    Image Brush_image = GenImageColor(8, 8, RAYWHITE);
    Rectangle Brush_src_rect = {0, 0, Brush_image.width, Brush_image.height};

    Vector2 mousePos_cur;

    InitWindow(screenWidth, screenHeight, "raylib paint");
    assert(IsWindowReady());
    
    SetTargetFPS(144);

    while(!WindowShouldClose())
    {
        Vector2 mousePos_old = mousePos_cur;

        if (IsKeyDown(KEY_C)) {
            ImageClearBackground(&Canvas_image, DARKGREEN);
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        mousePos_cur = GetMousePosition();
        Vector2 brushPos = mousePos_old;

        // DrawBrush(Canvas_image, Brush_image, Brush_src_rect, mousePos_old, mousePos_cur);

        Rectangle Brush_dest_rect = 
        {mousePos_cur.x, mousePos_cur.y, Brush_src_rect.width, Brush_src_rect.height};

        if (Vector2Equals((Vector2){0, 0}, GetMouseDelta())) {
                ImageDraw(&Canvas_image, Brush_image, Brush_src_rect, Brush_dest_rect, WHITE);
            } 
        else {
        float dist_start_and_finish = Vector2Distance(brushPos, mousePos_cur);
        for (int i = 0; i < (int)dist_start_and_finish; i++)
        {
            brushPos = Vector2MoveTowards(brushPos, mousePos_cur, 1.0);
            Brush_dest_rect.x = brushPos.x;
            Brush_dest_rect.y = brushPos.y;

            ImageDraw(&Canvas_image, Brush_image, Brush_src_rect, Brush_dest_rect, WHITE);
        }
            }
        } else if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) {
            mousePos_cur = GetMousePosition();
        }
        
        BeginDrawing();

        // DrawText("test", screenHeight + 40, 40, 40, RAYWHITE);
        Texture2D Canvas_texture = LoadTextureFromImage(Canvas_image);
        DrawTexture(Canvas_texture, 0, 0, WHITE);

        EndDrawing();
        UnloadTexture(Canvas_texture);
    }

    CloseWindow();

    return 0;
}