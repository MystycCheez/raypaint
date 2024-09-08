#ifndef ETC_H
#define ETC_H

#define SCREEN_WIDTH 320 * 6
#define SCREEN_HEIGHT 200 * 6

#define CANVAS_WIDTH 320 * 5
#define CANVAS_HEIGHT 200 * 5

#define CANVAS_OFFSET 16

#define DEFAULT_BRUSH_SIZE 10

enum BrushShapes{
    BRUSH_SQUARE,
    BRUSH_CIRCLE,
};

typedef struct Brush {
    Image image;
    int size;
}Brush;
typedef struct Canvas {
    Image image;
    Color color;
    Texture2D texture;
}Canvas;
typedef struct Background {
    Image image;
    Texture2D texture;
}Background;

typedef struct MousePos {
    Vector2 current;
    Vector2 old;
}MousePos;
typedef struct Cursor {
    Image image;
    MousePos pos;
    Texture2D texture;
}Cursor;

#endif