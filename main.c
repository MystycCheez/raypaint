#include "includes.h"

int main(void)
{
    SetTraceLogLevel(LOG_WARNING);

    // unsigned int ToolState = TOOL_BRUSH;

    const int screenWidth  = 320 * 5;
    const int screenHeight = 200 * 5;

    float brush_scale = 1.0;

    Image canvas_image = GenImageColor(screenWidth, screenHeight, DARKGREEN);

    Brush brush = InitBrush((Vector2){16, 16});
    Image cursor_image = brush.image;

    Vector2 mousePos_cur;

    InitWindow(screenWidth, screenHeight, "raylib paint");
    assert(IsWindowReady());

    SetMousePosition(screenWidth / 2, screenHeight / 2);
    
    SetTargetFPS(144);

    while(!WindowShouldClose())
    {
        int mouseWheelMove = (int)GetMouseWheelMove();

        HideCursor();

        Vector2 mousePos_old = mousePos_cur;

        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            if (0 != mouseWheelMove) {
                brush_scale += mouseWheelMove * 0.1;
            }
        }

        if (IsKeyDown(KEY_C)) {
            ImageClearBackground(&canvas_image, DARKGREEN);
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        mousePos_cur = GetMousePosition();
        DrawBrush(canvas_image, brush, mousePos_old, mousePos_cur);
        } else if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) {
            mousePos_cur = GetMousePosition();
        }

        BeginDrawing();

        // DrawText("test", screenHeight + 40, 40, 40, RAYWHITE);
        Texture2D canvas_texture = LoadTextureFromImage(canvas_image);
        Texture2D cursor_texture = LoadTextureFromImage(cursor_image);

        DrawTexture(canvas_texture, 0, 0, WHITE);
        DrawTextureEx(cursor_texture, mousePos_cur, 0.0, brush_scale, WHITE);

        if (IsKeyDown(KEY_F1)) {
            DrawText("Press C to Clear", 20, 20, 30, RAYWHITE);
        }

        EndDrawing();
        UnloadTexture(canvas_texture);
        UnloadTexture(cursor_texture);
    }

    CloseWindow();

    return 0;
}