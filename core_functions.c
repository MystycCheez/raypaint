#include "includes.h"
#include "raylib.h"

// Not a raylib func, no pointer image dst
void ImageDrawBrush(Image dstImg, Image srcImg, Rectangle srcRect, Rectangle dstRect, BrushType BrushType)
{
    Color imgCol;
    bool matchedCol;

    Image resizedImg = ImageCopy(srcImg);
    ImageCrop(&resizedImg, srcRect);
    ImageResizeNN(&resizedImg, dstRect.width, dstRect.height);
    for (int i = 0; i < resizedImg.width * resizedImg.height; i++)
        {
            imgCol = GetImageColor(resizedImg, i % resizedImg.height, i / resizedImg.height);
            matchedCol = !ColorIsEqual(imgCol, BLANK);
            if (matchedCol) {
                switch (BrushType) {
                case BRUSH_BASIC:
                    ImageDrawPixel(&dstImg,
                    (i % resizedImg.height) + dstRect.x,
                    (i / resizedImg.height) + dstRect.y, 
                    imgCol);
                    break;
                case BRUSH_ERASE:
                ImageDrawPixel(&dstImg,
                    (i % resizedImg.height) + dstRect.x,
                    (i / resizedImg.height) + dstRect.y, 
                    BLANK);
                    break;
                }
            }
        }
}

void DrawBrush(Image canvasImage, Brush brush, MousePos mousePos)
{
    Vector2 brushPos = mousePos.old;

    Rectangle brush_src_rect = 
    {0, 0, brush.image.width, brush.image.height};
    Rectangle brush_dest_rect =
    {mousePos.current.x - CANVAS_OFFSET, mousePos.current.y - CANVAS_OFFSET, brush.size, brush.size};
    Rectangle resized_brush_rect =
    {0, 0, brush.size, brush.size};

    Image reszied_brush_img = ImageFromImage(brush.image, brush_src_rect);
    ImageResizeNN(&reszied_brush_img, brush.size, brush.size);

    if (Vector2Equals((Vector2){0, 0}, GetMouseDelta())) {
        ImageDrawBrush(canvasImage, reszied_brush_img, resized_brush_rect, brush_dest_rect, brush.type);
    }
    else {
        float dist_start_and_finish = Vector2Distance(mousePos.old, mousePos.current);
        for (int i = 0; i < dist_start_and_finish; i++)
        {
            brushPos = Vector2MoveTowards(brushPos, mousePos.current, 1.0);
            brush_dest_rect.x = brushPos.x - CANVAS_OFFSET;
            brush_dest_rect.y = brushPos.y - CANVAS_OFFSET;
            ImageDrawBrush(canvasImage, reszied_brush_img, resized_brush_rect, brush_dest_rect, brush.type);
        }
    }
}

Brush InitBrush(Image image, uint8_t shape, uint8_t type, uint8_t size, Color color)
{
    Brush brush;
    brush.image = ImageCopy(image);
    brush.shape = shape;
    brush.type = type;
    brush.size = size;
    brush.color = color;

    return brush;
}

Canvas InitCanvas(Color color)
{
    Canvas canvas;
    canvas.color = color;
    canvas.image = GenImageColor(CANVAS_WIDTH, CANVAS_HEIGHT, (Color){0, 0, 0, 0});
    canvas.tex_backgroundLayer = LoadTextureFromImage(GenImageColor(CANVAS_WIDTH, CANVAS_HEIGHT, canvas.color));

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

    background.texture = LoadTextureFromImage(background.image);

    return background;
}

void DrawTextWithShadow(const char* text, int posX, int posY, int fontSize, Color color, int offsetX, int offsetY, Color shadowColor)
{
    DrawText(text, posX + offsetX, posY + offsetY, fontSize, shadowColor);
    DrawText(text, posX, posY, fontSize, color);
}

Color ConvertFromColorFloat(ColorFloat colorFloat)
{
    Color color;

    color.r = (float)colorFloat.r;
    color.g = (float)colorFloat.g;
    color.b = (float)colorFloat.b;
    color.a = (float)colorFloat.a;

    return color;
}

ColorFloat ConvertToColorFloat(Color color)
{
    ColorFloat colorFloat;

    colorFloat.r = (int)color.r;
    colorFloat.g = (int)color.g;
    colorFloat.b = (int)color.b;
    colorFloat.a = (int)color.a;

    return colorFloat;
}

void SetCanvasColor(Canvas* canvas, Color color)
{
    canvas->color = color;
    Image temp_img = GenImageColor(CANVAS_WIDTH, CANVAS_HEIGHT, canvas->color);
    canvas->tex_backgroundLayer = LoadTextureFromImage(temp_img);
    UnloadImage(temp_img);
}

void SetBrushColor(Brush* brush, Color color)
{
    ImageColorReplace(&brush->image, brush->color, color);
    brush->color = color;
}