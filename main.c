#include "includes.h"

int main(void)
{
    SetTraceLogLevel(LOG_WARNING);

    bool toggle_f1 = true;
    bool cursorWithinCanvas = false;
    bool held_shift = false;
    bool shape_changed = false;

    bool btn_brush_pressed = false;
    bool btn_canvas_pressed = false;
    bool slider_r_moved = false;
    bool slider_g_moved = false;
    bool slider_b_moved = false;
    
    int selection = BRUSH;

    ColorFloat sliderColor;
    sliderColor = ConvertToColorFloat(DEFAULT_BRUSH_COLOR);    

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib paint");
    assert(IsWindowReady());

    Background background = InitBackground();

    Canvas canvas = InitCanvas(DARKERBLUE);

    ImageNode* CanvasImageTail = NewImageNode(canvas.image);
    ImageNode* CanvasImageHead = CanvasImageTail;
    assert(CanvasImageHead != NULL);

    Image img_brushes[NUM_BRUSH_SHAPES];

    img_brushes[SHAPE_SQUARE] = GenImageColor(DEFAULT_BRUSH_SIZE, DEFAULT_BRUSH_SIZE, DEFAULT_BRUSH_COLOR);
    img_brushes[SHAPE_CIRCLE] = GenImageColor(512, 512, BLANK);
    ImageDrawCircle(&img_brushes[SHAPE_CIRCLE], 256, 256, 256, DEFAULT_BRUSH_COLOR);

    Brush brush = InitBrush(img_brushes[DEFAULT_BRUSH_SHAPE],
    DEFAULT_BRUSH_SHAPE, DEFAULT_BRUSH_TYPE, DEFAULT_BRUSH_SIZE, DEFAULT_BRUSH_COLOR);

    Cursor cursor;
    cursor.image = ImageCopy(brush.image);

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

        if (btn_brush_pressed && (selection != BRUSH)){
            sliderColor = ConvertToColorFloat(brush.color);
            selection = BRUSH;
        }
        if (btn_canvas_pressed && (selection != CANVAS)) {
            sliderColor = ConvertToColorFloat(canvas.color);
            selection = CANVAS;
        }

        if (slider_r_moved || slider_g_moved || slider_b_moved) {
            if (selection == BRUSH) {
                for (uint8_t i = 0; i < NUM_BRUSH_SHAPES; i++)
                {ImageColorReplace(&img_brushes[i], brush.color, ConvertFromColorFloat(sliderColor));}
                brush = InitBrush(img_brushes[brush.shape], brush.shape, BRUSH_BASIC, brush.size, brush.color);
                brush.color = ConvertFromColorFloat(sliderColor);
                cursor.image = ImageCopy(brush.image);
            } else if (selection == CANVAS) {
                canvas.color = ConvertFromColorFloat(sliderColor);
                Image temp_img = GenImageColor(CANVAS_WIDTH, CANVAS_HEIGHT, canvas.color);
                canvas.tex_backgroundLayer = LoadTextureFromImage(temp_img);
                UnloadImage(temp_img);
            }
        }

        cursor.pos.old = cursor.pos.current;
        cursor.pos.current = GetMousePosition();

        int mouseWheelMove = (int)GetMouseWheelMove();

        if (IsKeyDown(KEY_C)) {ImageClearBackground(&CanvasImageHead->image, BLANK);}

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
                brush = InitBrush(img_brushes[SHAPE_SQUARE], SHAPE_SQUARE, BRUSH_BASIC, brush.size, brush.color);
            } else {brush = InitBrush(img_brushes[brush.shape], brush.shape, BRUSH_BASIC, brush.size, brush.color);}
            cursor.image = ImageCopy(brush.image);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            held_shift = true;
            if (0 != mouseWheelMove) {
                brush.size += mouseWheelMove;
                brush.size = Clamp(brush.size, 1, 60);
                if (brush.shape == SHAPE_CIRCLE) { // if-else below here is formatted like so for clarity
                    if (brush.size == 1) // circle too small to draw at 1x1 pixel
                    {brush = InitBrush(img_brushes[SHAPE_SQUARE], SHAPE_SQUARE, BRUSH_BASIC, brush.size, brush.color); cursor.image = ImageCopy(brush.image);} 
                    else 
                    {brush = InitBrush(img_brushes[SHAPE_CIRCLE], SHAPE_CIRCLE, BRUSH_BASIC, brush.size, brush.color); cursor.image = ImageCopy(brush.image);}
                }
            }
        } else {held_shift = false;}

        if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
            if      (IsKeyPressed(KEY_Z)) {TraverseImageNodeBackward(&CanvasImageHead);}
            else if (IsKeyPressed(KEY_Y)) {TraverseImageNodeForward(&CanvasImageHead);}
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && cursorWithinCanvas) {
            ReplaceNextImageNode(&CanvasImageHead, CanvasImageHead->image);
            TraverseImageNodeForward(&CanvasImageHead);
        }
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {DrawBrush(CanvasImageHead->image, brush, cursor.pos);}

        // Begin Drawing //
        BeginDrawing();

        cursor.texture = LoadTextureFromImage(cursor.image);
        canvas.tex_paintLayer = LoadTextureFromImage(CanvasImageHead->image);

        DrawTexture(canvas.tex_backgroundLayer, CANVAS_OFFSET, CANVAS_OFFSET, WHITE);
        DrawTexture(canvas.tex_paintLayer, CANVAS_OFFSET, CANVAS_OFFSET, WHITE);

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
        
        btn_canvas_pressed = GuiButton((Rectangle){CANVAS_OFFSET + CANVAS_WIDTH + 8 + (SCALAR * 4), 64, 160, 80}, "Canvas");
        btn_brush_pressed = GuiButton((Rectangle){SCREEN_WIDTH - (SCALAR * 4) - 160, 64, 160, 80}, "Brush");

        slider_r_moved = GuiSlider((Rectangle){CANVAS_OFFSET + CANVAS_WIDTH + 8 + (SCALAR * 8), 240, 320 - (SCALAR * 12), 16}, 
        "0", "255", &sliderColor.r, (float)0, (float)255);
        slider_g_moved = GuiSlider((Rectangle){CANVAS_OFFSET + CANVAS_WIDTH + 8 + (SCALAR * 8), 280, 320 - (SCALAR * 12), 16}, 
        "0", "255", &sliderColor.g, (float)0, (float)255);
        slider_b_moved = GuiSlider((Rectangle){CANVAS_OFFSET + CANVAS_WIDTH + 8 + (SCALAR * 8), 320, 320 - (SCALAR * 12), 16}, 
        "0", "255", &sliderColor.b, (float)0, (float)255);
        sliderColor = (ColorFloat){sliderColor.r, sliderColor.g, sliderColor.b, 0xFF};

        EndDrawing();
        UnloadTexture(canvas.tex_paintLayer);
        UnloadTexture(cursor.texture);
    }

    UnloadTexture(background.texture);
    UnloadTexture(canvas.tex_backgroundLayer);

    CloseWindow();

    return 0;
}