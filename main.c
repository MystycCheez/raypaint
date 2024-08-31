#include "includes.h"

int main(void)
{
    SetTraceLogLevel(LOG_WARNING);

    // unsigned int ToolState = TOOL_BRUSH;

    const int screenWidth  = 320 * 5;
    const int screenHeight = 200 * 5;

    const int brushSize = 10;

    bool toggle_f1;

    Image canvas_image = GenImageColor(screenWidth, screenHeight, DARKGREEN);

    Brush brush = InitBrush(brushSize);
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

        Texture2D canvas_texture = LoadTextureFromImage(canvas_image);
        Texture2D cursor_texture = LoadTextureFromImage(cursor_image);

        DrawTexture(canvas_texture, 0, 0, WHITE);

        if (IsKeyPressed(KEY_F1)) {
            toggle_f1 = !toggle_f1;
        }
        if (toggle_f1) {
            DrawText("Press C to Clear", 20, 20, 30, RAYWHITE);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            DrawText(TextFormat("%2.1f", brush.scale), 
            mousePos_cur.x + 10, mousePos_cur.y - 30, 30, RAYWHITE);
            if (0 != mouseWheelMove) {
                brush.scale += mouseWheelMove * 0.1;
                brush.scale = Clamp(brush.scale, 0.1, 10.0);
            }
        }

        DrawTextureEx(cursor_texture, mousePos_cur, 0.0, brush.scale, WHITE);

        EndDrawing();
        UnloadTexture(canvas_texture);
        UnloadTexture(cursor_texture);
    }

    CloseWindow();

    return 0;
}