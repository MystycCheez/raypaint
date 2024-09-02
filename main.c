#include "includes.h"

int main(void)
{
    SetTraceLogLevel(LOG_WARNING);

    unsigned int ToolState = TOOL_BRUSH;

    const int brushSize = 10;

    bool toggle_f1 = true;

    Canvas canvas;
    canvas.color = DARKGREEN;
    canvas.image = GenImageColor(SCREEN_WIDTH, SCREEN_HEIGHT, canvas.color);

    Brush brush = InitBrush(brushSize, BRUSH_SQUARE);

    Cursor cursor;
    cursor.image = brush.image;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib paint");
    assert(IsWindowReady());

    SetMousePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    
    SetTargetFPS(144);

    while(!WindowShouldClose())
    {
        HideCursor();

        cursor.pos.old = cursor.pos.current;

        int mouseWheelMove = (int)GetMouseWheelMove();

        if (IsKeyDown(KEY_C)) {
            ImageClearBackground(&canvas.image, canvas.color);
        }
        if (IsKeyDown(KEY_R)) {
            brush.scale = 1.0;
        }
        if (IsKeyDown(KEY_B)) {
            ToolState = TOOL_BRUSH;
        }
        if (IsKeyDown(KEY_E)) {
            ToolState = TOOL_ERASE;
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        cursor.pos.current = GetMousePosition();

        switch (ToolState)
        {
        case TOOL_BRUSH:
            brush.image = GenImageColor(brush.image.width, brush.image.height, RAYWHITE);
            DrawBrush(canvas, brush, cursor.pos);
            break;
        case TOOL_ERASE:
            brush.image = GenImageColor(brush.image.width, brush.image.height, canvas.color);
            DrawBrush(canvas, brush, cursor.pos);
            break;
        }
        // DrawBrush2();

        } else if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) {
            cursor.pos.current = GetMousePosition();
        }

        BeginDrawing();

        canvas.texture = LoadTextureFromImage(canvas.image);
        cursor.texture = LoadTextureFromImage(cursor.image);

        DrawTexture(canvas.texture, 0, 0, WHITE);

        if (IsKeyPressed(KEY_F1)) {
            toggle_f1 = !toggle_f1;
        }
        if (toggle_f1) {
            DrawText("Shift + Scroll Wheel - Change brush size", 20, 20, 30, RAYWHITE);
            DrawText("C - Clear", 20, 50, 30, RAYWHITE);
            DrawText("R - Reset brush size", 20, 80, 30, RAYWHITE);
            DrawText("B - Brush", 20, 110, 30, RAYWHITE);
            DrawText("E - Erase", 20, 140, 30, RAYWHITE);
            DrawText("F1 - Toggle this text", 20, 170, 30, RAYWHITE);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            DrawText(TextFormat("%1.f", brush.scale * 10), 
            cursor.pos.current.x + 10, cursor.pos.current.y - 30, 30, RAYWHITE);
            if (0 != mouseWheelMove) {
                brush.scale += mouseWheelMove * 0.1;
                brush.scale = Clamp(brush.scale, 0.1, 3.0);
            }
        }

        DrawTextureEx(cursor.texture, cursor.pos.current, 0.0, brush.scale, WHITE);

        EndDrawing();
        UnloadTexture(canvas.texture);
        UnloadTexture(cursor.texture);
    }

    CloseWindow();

    return 0;
}