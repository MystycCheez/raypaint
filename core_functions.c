#include "raylib.h"
#include "raymath.h"

#include "etc.h"

void DrawBrush(Image canvas_image, Brush brush, Vector2 mousePos_old, Vector2 mousePos_cur)
{
    Vector2 brushPos = mousePos_old;

    Rectangle Brush_dest_rect =
    {mousePos_cur.x, mousePos_cur.y, brush.image.width, brush.image.height};

    if (Vector2Equals((Vector2){0, 0}, GetMouseDelta())) {
        ImageDraw(&canvas_image, brush.image, brush.rect, Brush_dest_rect, WHITE);
    }
    else {
        float dist_start_and_finish = Vector2Distance(mousePos_old, mousePos_cur);
        for (int i = 0; i < (int)dist_start_and_finish; i++)
        {
            brushPos = Vector2MoveTowards(brushPos, mousePos_cur, 4.0);
            Brush_dest_rect.x = brushPos.x;
            Brush_dest_rect.y = brushPos.y;
            ImageDraw(&canvas_image, brush.image, brush.rect, Brush_dest_rect, WHITE);
        }
    }
}

void DrawBrushCursor(Image canvas_image, Brush brush, Vector2 mousePos)
{
    Rectangle Brush_dest_rect =
    {mousePos.x, mousePos.y, brush.image.width, brush.image.height};

    ImageDraw(&canvas_image, brush.image, brush.rect, Brush_dest_rect, WHITE);
}

Brush InitBrush(Vector2 size)
{
    Brush brush;

    brush.image = GenImageColor(size.x, size.y, RAYWHITE);

    brush.rect.x = 0;
    brush.rect.y = 0;
    brush.rect.width = brush.image.width;
    brush.rect.height = brush.image.height;

    return brush;
}