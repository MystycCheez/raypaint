#include "raylib.h"
#include "raymath.h"

#include "etc.h"

void DrawBrush(Image canvas_image, Brush brush, Vector2 mousePos_old, Vector2 mousePos_cur)
{
    Vector2 brushPos = mousePos_old;

    Rectangle brush_dest_rect =
    {mousePos_cur.x, mousePos_cur.y, brush.scale * 10, brush.scale * 10};

    if (Vector2Equals((Vector2){0, 0}, GetMouseDelta())) {
        ImageDraw(&canvas_image, brush.image, brush.rect, brush_dest_rect, WHITE);
    }
    else {
        float dist_start_and_finish = Vector2Distance(mousePos_old, mousePos_cur);
        for (float i = 0.0; i < dist_start_and_finish;)
        {
            brushPos = Vector2MoveTowards(brushPos, mousePos_cur, 1.0);
            brush_dest_rect.x = brushPos.x;
            brush_dest_rect.y = brushPos.y;
            ImageDraw(&canvas_image, brush.image, brush.rect, brush_dest_rect, WHITE);

            i = i + 0.1;
        }
    }
}

Brush InitBrush(int size)
{
    Brush brush;

    brush.image = GenImageColor(size, size, RAYWHITE);

    brush.rect.x = 0;
    brush.rect.y = 0;
    brush.rect.width = brush.image.width;
    brush.rect.height = brush.image.height;

    brush.scale = 1.0;

    return brush;
}