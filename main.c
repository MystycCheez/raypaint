#include "includes.h"

int main(void)
{
    SetTraceLogLevel(LOG_WARNING);

    bool toggle_f1 = true;

    Canvas canvas;
    canvas.color = DARKGREEN;
    canvas.image = GenImageColor(SCREEN_WIDTH, SCREEN_HEIGHT, canvas.color);

    Image square = GenImageColor(DEFAULT_BRUSH_SIZE, DEFAULT_BRUSH_SIZE, RAYWHITE);

    Brush brush = InitBrush(square, DEFAULT_BRUSH_SIZE);

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
            brush.size = 10;
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        cursor.pos.current = GetMousePosition();

        DrawBrush(canvas, brush, cursor.pos);

        } else if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) {
            cursor.pos.current = GetMousePosition();
        }

        // Begin Drawing //
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
            DrawText(TextFormat("%d", brush.size), 
            cursor.pos.current.x + 10, cursor.pos.current.y - 30, 30, RAYWHITE);
            if (0 != mouseWheelMove) {
                brush.size += mouseWheelMove;
                brush.size = Clamp(brush.size, 1, 30);
            }
        }

        DrawTextureEx(cursor.texture, cursor.pos.current, 0.0, (float)brush.size / 10.0, WHITE);

        EndDrawing();
        UnloadTexture(canvas.texture);
        UnloadTexture(cursor.texture);
    }

    CloseWindow();

    return 0;
}