#include "raylib.h"
#include "raymath.h"

#include "etc.h"

void DrawBrush(Canvas canvas, Brush brush, MousePos mousePos)
{ // TODO: Optimize drawing - Make it to where it doesn't need to resize every DrawBrush() call, somehow
    Vector2 brushPos = mousePos.old;

    Rectangle brush_src_rect = 
    {0, 0, brush.image.width, brush.image.height};
    Rectangle brush_dest_rect =
    {mousePos.current.x, mousePos.current.y, brush.size, brush.size};
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
            brush_dest_rect.x = brushPos.x;
            brush_dest_rect.y = brushPos.y;
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