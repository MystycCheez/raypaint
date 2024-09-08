#include "includes.h"

int main(void)
{
    SetTraceLogLevel(LOG_WARNING);

    bool toggle_f1 = true;
    bool cursorWithinCanvas = false;
    bool held_shift = false;
    bool shape_changed = false;

    Background background = InitBackground();

    Canvas canvas = InitCanvas(DARKGREEN);

    Image img_brushes[2];

    img_brushes[SHAPE_SQUARE] = GenImageColor(DEFAULT_BRUSH_SIZE, DEFAULT_BRUSH_SIZE,DEFAULT_BRUSH_COLOR);
    img_brushes[SHAPE_CIRCLE] = GenImageColor(512, 512, (Color){0, 0, 0, 0});
    ImageDrawCircle(&img_brushes[SHAPE_CIRCLE], 256, 256, 256, DEFAULT_BRUSH_COLOR);

    Brush brush = InitBrush(img_brushes[DEFAULT_BRUSH_SHAPE],
     DEFAULT_BRUSH_SHAPE, DEFAULT_BRUSH_TYPE, DEFAULT_BRUSH_SIZE, DEFAULT_BRUSH_COLOR);

    Cursor cursor;
    cursor.image = brush.image;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib paint");
    assert(IsWindowReady());

    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);

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

        if (IsKeyDown(KEY_C)) {ImageClearBackground(&canvas.image, canvas.color);}
        if (IsKeyDown(KEY_R)) {brush.size = 10;}

        if (IsKeyDown(KEY_KP_1) && (brush.shape != SHAPE_SQUARE)) {
            brush.shape = SHAPE_SQUARE;
            shape_changed = true;
        } else if (IsKeyDown(KEY_KP_2) && (brush.shape != SHAPE_CIRCLE)) {
            brush.shape = SHAPE_CIRCLE;
            shape_changed = true;
        } else {shape_changed = false;}

        if (shape_changed) {
            if (brush.size == 1) {
                brush = InitBrush(img_brushes[SHAPE_SQUARE], SHAPE_SQUARE, BRUSH_BASIC, brush.size, DEFAULT_BRUSH_COLOR);
            } else {brush = InitBrush(img_brushes[brush.shape], brush.shape, BRUSH_BASIC, brush.size, DEFAULT_BRUSH_COLOR);}
            cursor.image = brush.image;
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            held_shift = true;
            if (0 != mouseWheelMove) { // if-else within here is formatted like this for clarity
                brush.size += mouseWheelMove;
                brush.size = Clamp(brush.size, 1, 60);
                if (brush.shape == SHAPE_CIRCLE) {
                    if (brush.size == 1) // circle too small to draw at 1x1 pixel
                    {brush = InitBrush(img_brushes[SHAPE_SQUARE], SHAPE_SQUARE, BRUSH_BASIC, brush.size, DEFAULT_BRUSH_COLOR); cursor.image = brush.image;} 
                    else 
                    {brush = InitBrush(img_brushes[SHAPE_CIRCLE], SHAPE_CIRCLE, BRUSH_BASIC, brush.size, DEFAULT_BRUSH_COLOR); cursor.image = brush.image;}
                }
            }
        } else {held_shift = false;}

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

        if (held_shift) {DrawTextWithShadow(TextFormat("%d", brush.size), 
        cursor.pos.current.x + 10, cursor.pos.current.y - 30, 30, RAYWHITE, 3, 3, BLACK);}

        if (IsKeyPressed(KEY_F1)) {
            toggle_f1 = !toggle_f1;
        }
        if (toggle_f1) {
            DrawTextWithShadow("Shift + Scroll Wheel - Change brush size", 20, 20, 30, RAYWHITE, 3, 3, BLACK);
            DrawTextWithShadow("C - Clear", 20, 50, 30, RAYWHITE, 3, 3, BLACK);
            DrawTextWithShadow("R - Reset brush size", 20, 80, 30, RAYWHITE, 3, 3, BLACK);
            DrawTextWithShadow("B - Brush", 20, 110, 30, RAYWHITE, 3, 3, BLACK);
            DrawTextWithShadow("E - Erase", 20, 140, 30, RAYWHITE, 3, 3, BLACK);
            DrawTextWithShadow("F1 - Toggle this text", 20, 170, 30, RAYWHITE, 3, 3, BLACK);
            DrawTextWithShadow("NUMPAD 1 - Square brush", 20, 210, 30, RAYWHITE, 3, 3, BLACK);
            DrawTextWithShadow("NUMPAD 2 - Circle brush", 20, 240, 30, RAYWHITE, 3, 3, BLACK);
        }

        if (cursorWithinCanvas) {
            DrawTextureEx(cursor.texture, cursor.pos.current,
            0.0, (float)brush.size / brush.image.width, WHITE);
        }

        DrawTexture(background.texture, 0, 0, WHITE);
        GuiButton((Rectangle){CANVAS_WIDTH + 64, 64, 90, 90}, "test");
        GuiDrawIcon(ICON_BRUSH_PAINTER, CANVAS_WIDTH + 256, 64, 3, RAYWHITE);

        EndDrawing();
        UnloadTexture(background.texture);
        UnloadTexture(canvas.texture);
        UnloadTexture(cursor.texture);
    }

    CloseWindow();

    return 0;
}