#include "raylib.h"
#include "raymath.h"

#include "etc.h"

void DrawBrush(Image canvas_image, Brush brush, Vector2 mousePos_old, Vector2 mousePos_cur)
{
    Vector2 brushPos = mousePos_old;

    Rectangle brush_dest_rect =
    {mousePos_cur.x, mousePos_cur.y, brush.scale * brush.size, brush.scale * brush.size};

    if (Vector2Equals((Vector2){0, 0}, GetMouseDelta())) {
        ImageDraw(&canvas_image, brush.image, brush.rect, brush_dest_rect, WHITE);
    }
    else {
        float dist_start_and_finish = Vector2Distance(mousePos_old, mousePos_cur);
        for (float i = 0.0; i < dist_start_and_finish;)
        {
            brushPos = Vector2MoveTowards(brushPos, mousePos_cur, brush.scale);
            brush_dest_rect.x = brushPos.x;
            brush_dest_rect.y = brushPos.y;
            ImageDraw(&canvas_image, brush.image, brush.rect, brush_dest_rect, WHITE);

            i = i + (brush.scale);
        }
    }
}

Brush InitBrush(int size, int Brush_Type)
{
    Brush brush;

    brush.size = size;
    brush.scale = 1.0;

    switch (Brush_Type)
    {
    case BRUSH_SQUARE:
        brush.image = GenImageColor(brush.size, brush.size, RAYWHITE);
        break;
    case BRUSH_ROUND:
        brush.image = GenImageColor(brush.size, brush.size, (Color){0, 0, 0, 0});
        ImageDrawCircleV(&brush.image, (Vector2){brush.size / 2, brush.size / 2}, brush.size / 2, RAYWHITE);
        break;
    default: // Same as BRUSH_SQUARE
        brush.image = GenImageColor(brush.size, brush.size, RAYWHITE);
        break;
    }

    // ImageResize(&brush.image, size / 10, size / 10);

    brush.rect.x = 0;
    brush.rect.y = 0;
    brush.rect.width = brush.image.width;
    brush.rect.height = brush.image.height;


    return brush;
}