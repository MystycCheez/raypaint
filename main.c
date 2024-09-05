#include "includes.h"

int main(void)
{
    SetTraceLogLevel(LOG_WARNING);

    bool toggle_f1 = true;
    bool cursorWithinCanvas = false;

    Background background = InitBackground();

    Canvas canvas = InitCanvas(DARKGREEN);

    Image square = GenImageColor(DEFAULT_BRUSH_SIZE, DEFAULT_BRUSH_SIZE, RAYWHITE);

    Image circle = GenImageColor(512, 512, (Color){0, 0, 0, 0});
    ImageDrawCircle(&circle, 256, 256, 256, RAYWHITE);

    Brush brush = InitBrush(circle, DEFAULT_BRUSH_SIZE);

    Cursor cursor;
    cursor.image = brush.image;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib paint");
    assert(IsWindowReady());

    SetMousePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    
    SetTargetFPS(144);

    while(!WindowShouldClose())
    {
        cursorWithinCanvas = CheckCollisionPointRec(cursor.pos.current, 
        (Rectangle){CANVAS_OFFSET, CANVAS_OFFSET, CANVAS_WIDTH, CANVAS_HEIGHT});
        if (cursorWithinCanvas) {
            HideCursor();
        } else {ShowCursor();}

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

        background.texture = LoadTextureFromImage(background.image);
        canvas.texture = LoadTextureFromImage(canvas.image);
        cursor.texture = LoadTextureFromImage(cursor.image);

        DrawTexture(canvas.texture, CANVAS_OFFSET, CANVAS_OFFSET, WHITE);

        if (IsKeyPressed(KEY_F1)) {
            toggle_f1 = !toggle_f1;
        }
        if (toggle_f1) {
            DrawText("Shift + Scroll Wheel - Change brush size", 20, 20, 30, RAYWHITE);
            DrawText("C                         - Clear", 20, 50, 30, RAYWHITE);
            DrawText("R                         - Reset brush size", 20, 80, 30, RAYWHITE);
            DrawText("B                         - Brush", 20, 110, 30, RAYWHITE);
            DrawText("E                         - Erase", 20, 140, 30, RAYWHITE);
            DrawText("F1                        - Toggle this text", 20, 170, 30, RAYWHITE);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            DrawText(TextFormat("%d", brush.size), 
            cursor.pos.current.x + 10, cursor.pos.current.y - 30, 30, RAYWHITE);
            if (0 != mouseWheelMove) {
                brush.size += mouseWheelMove;
                brush.size = Clamp(brush.size, 1, 60);
                brush = InitBrush(circle, brush.size);
            }
        }

        if (cursorWithinCanvas) {
            DrawTextureEx(cursor.texture, cursor.pos.current,
            0.0, (float)brush.size / brush.image.width, WHITE);
        }
        DrawTexture(background.texture, 0, 0, WHITE);

        EndDrawing();
        UnloadTexture(background.texture);
        UnloadTexture(canvas.texture);
        UnloadTexture(cursor.texture);
    }

    CloseWindow();

    return 0;
}