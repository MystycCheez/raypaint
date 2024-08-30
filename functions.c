#include "raylib.h"
#include "raymath.h"

Image ImageGenerateSquareCheckerboard(int boardResolution, int boardFactor, Color color1, Color color2){
    Image img = GenImageColor(boardResolution, boardResolution, BLACK);
    for (int i = 0; i < boardResolution * boardResolution; i++)
    // checkerboard
    {
        int x = i / boardResolution;
        int y = i % boardResolution;            
        if(((x / boardFactor) % 2 == 0) ^ ((y / boardFactor) % 2 == 0))
        {ImageDrawPixel(&img, x, y, BROWN);} else {ImageDrawPixel(&img, x, y, BEIGE);}
    } 
    return img;
}
Image ImageLoadBrush(char* filename)
{

}
Image ImageDrawImageLineV(Image *dst, Image src, Vector2 startPos, Vector2 endPos, Color tint)
{

}