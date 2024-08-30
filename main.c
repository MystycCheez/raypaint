#include "includes.h"

int main(void)
{
    SetTraceLogLevel(LOG_WARNING);

    // unsigned int ToolState = TOOL_BRUSH;

    const int screenWidth  = 320 * 5;
    const int screenHeight = 200 * 5;

    Image Canvas_image = GenImageColor(screenWidth, screenHeight, DARKGREEN);

    Brush brush = InitBrush();

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

        DrawBrush(Canvas_image, brush, mousePos_old, mousePos_cur);

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