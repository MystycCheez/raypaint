#include "includes.h"

int main(void)
{
    SetTraceLogLevel(LOG_WARNING);

    // unsigned int ToolState = TOOL_BRUSH;

    const int brushSize = 10;

    bool toggle_f1;

    Image canvas_image = GenImageColor(SCREEN_WIDTH, SCREEN_HEIGHT, DARKGREEN);

    Brush brush = InitBrush(brushSize, BRUSH_SQUARE);
    Image cursor_image = brush.image;

    MousePos mousePos;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib paint");
    assert(IsWindowReady());

    SetMousePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    
    SetTargetFPS(144);

    while(!WindowShouldClose())
    {
        int mouseWheelMove = (int)GetMouseWheelMove();

        HideCursor();

        mousePos.old = mousePos.current;

        if (IsKeyDown(KEY_C)) {
            ImageClearBackground(&canvas_image, DARKGREEN);
        }
        if (IsKeyDown(KEY_R)) {
            brush.scale = 1.0;
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        mousePos.current = GetMousePosition();

        DrawBrush(canvas_image, brush, mousePos.old, mousePos.current);
        // DrawBrush2();

        } else if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) {
            mousePos.current = GetMousePosition();
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
            DrawText(TextFormat("%1.f", brush.scale * 10), 
            mousePos.current.x + 10, mousePos.current.y - 30, 30, RAYWHITE);
            if (0 != mouseWheelMove) {
                brush.scale += mouseWheelMove * 0.1;
                brush.scale = Clamp(brush.scale, 0.1, 3.0);
            }
        }

        DrawTextureEx(cursor_texture, mousePos.current, 0.0, brush.scale, WHITE);

        EndDrawing();
        UnloadTexture(canvas_texture);
        UnloadTexture(cursor_texture);
    }

    CloseWindow();

    return 0;
}