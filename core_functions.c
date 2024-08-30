#include "raylib.h"
#include "raymath.h"

void DrawBrush(Image Canvas_image, Image Brush_image, Rectangle Brush_src_rect, Vector2 mousePos_old, Vector2 mousePos_cur)
{
    Rectangle Brush_dest_rect =
    {mousePos_cur.x, mousePos_cur.y, Brush_src_rect.width, Brush_src_rect.height};

    if (Vector2Equals((Vector2){0, 0}, GetMouseDelta())) {
        ImageDraw(&Canvas_image, Brush_image, Brush_src_rect, Brush_dest_rect, WHITE);
    }
    else {
        float dist_start_and_finish = Vector2Distance(mousePos_old, mousePos_cur);
        for (int i = 0; i < (int)dist_start_and_finish; i++)
        {
            Vector2 brushPos = Vector2MoveTowards(mousePos_old, mousePos_cur, 1.0);
            Brush_dest_rect.x = brushPos.x;
            Brush_dest_rect.y = brushPos.y;
            ImageDraw(&Canvas_image, Brush_image, Brush_src_rect, Brush_dest_rect, WHITE);
        }
    }
}