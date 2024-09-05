#include "raylib.h"
#include "raymath.h"

#include "etc.h"

void DrawBrush(Canvas canvas, Brush brush, MousePos mousePos)
{ // TODO: Optimize drawing - Make it to where it doesn't need to resize every DrawBrush() call, somehow
    Vector2 brushPos = mousePos.old;

    Rectangle brush_src_rect = 
    {0, 0, brush.image.width, brush.image.height};
    Rectangle brush_dest_rect =
    {mousePos.current.x - CANVAS_OFFSET, mousePos.current.y - CANVAS_OFFSET, brush.size, brush.size};
    Rectangle brush_resized_rect =
    {0, 0, brush.size, brush.size};

    Image reszied_img = ImageFromImage(brush.image, brush_src_rect);
    ImageResizeNN(&reszied_img, brush.size, brush.size);

    if (Vector2Equals((Vector2){0, 0}, GetMouseDelta())) {
        ImageDraw(&canvas.image, reszied_img, brush_resized_rect, brush_dest_rect, WHITE);
    }
    else {
        float dist_start_and_finish = Vector2Distance(mousePos.old, mousePos.current);
        for (int i = 0; i < dist_start_and_finish; i++)
        {
            brushPos = Vector2MoveTowards(brushPos, mousePos.current, 1.0);
            brush_dest_rect.x = brushPos.x - CANVAS_OFFSET;
            brush_dest_rect.y = brushPos.y - CANVAS_OFFSET;
            ImageDraw(&canvas.image, reszied_img, brush_resized_rect, brush_dest_rect, WHITE);
        }
    }
}

Brush InitBrush(Image brush_image, int size)
{
    Brush brush;
    brush.size = size;
    brush.image = brush_image;

    return brush;
}

Canvas InitCanvas(Color color)
{
    Canvas canvas;
    canvas.color = color;
    canvas.image = GenImageColor(CANVAS_WIDTH, CANVAS_HEIGHT, canvas.color);

    return canvas;
}

Background InitBackground()
{
    int b1_border_size = 8;
    int b2_border_size = 3;

    Background background;
    background.image = GenImageGradientLinear(SCREEN_WIDTH, SCREEN_HEIGHT, 45, BLACK, DARKBLUE);    

    ImageDrawRectangle(&background.image, CANVAS_OFFSET, CANVAS_OFFSET, 
    CANVAS_WIDTH, CANVAS_HEIGHT, (Color){0, 0, 0, 0});

    ImageDrawRectangleLines(&background.image,
    (Rectangle){CANVAS_OFFSET - b1_border_size, CANVAS_OFFSET - b1_border_size, CANVAS_WIDTH + (b1_border_size * 2), CANVAS_HEIGHT + (b1_border_size * 2)},
    b1_border_size, DARKGRAY);
    ImageDrawRectangleLines(&background.image,
    (Rectangle){CANVAS_OFFSET - b2_border_size - 2, CANVAS_OFFSET - b2_border_size - 2, CANVAS_WIDTH + (b2_border_size * 2) + 4, CANVAS_HEIGHT + (b2_border_size * 2) + 4},
    b2_border_size, LIGHTGRAY);

    return background;
}

Button InitButton(Image image, Vector2 pos, bool state)
{
    Button button;

    button.image = image;
    button.pos = pos;
    button.state = state;

    button.collisionBox = (Rectangle){0, 0, button.image.width, button.image.height};

    return button;
}

ColorBox InitColorBox(Color color, Vector2 pos, int size)
{
    ColorBox colorBox;

    colorBox.image = GenImageColor(size, size, color);
    colorBox.color = color;
    colorBox.pos = pos;

    colorBox.collisionBox = (Rectangle){0, 0, size, size};

    return colorBox;
}

Slider InitSlider()
{
    
}