#include "raylib.h"
#include "raymath.h"

#include "etc.h"

void DrawBrush(Canvas canvas, Brush brush, MousePos mousePos)
{
    Vector2 brushPos = mousePos.old;

    Rectangle brush_src_rect = 
    {0, 0, brush.image.width, brush.image.height};
    Rectangle brush_dest_rect =
    {mousePos.current.x, mousePos.current.y, brush.size, brush.size};

    if (Vector2Equals((Vector2){0, 0}, GetMouseDelta())) {
        ImageDraw(&canvas.image, brush.image, brush_src_rect, brush_dest_rect, WHITE);
    }
    else {
        float dist_start_and_finish = Vector2Distance(mousePos.old, mousePos.current);
        for (float i = 0.0; i < dist_start_and_finish;)
        {
            brushPos = Vector2MoveTowards(brushPos, mousePos.current, (float)brush.size / 10);
            brush_dest_rect.x = brushPos.x;
            brush_dest_rect.y = brushPos.y;
            ImageDraw(&canvas.image, brush.image, brush_src_rect, brush_dest_rect, WHITE);

            i = i + ((float)brush.size / 10);
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