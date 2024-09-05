#ifndef ETC_H
#define ETC_H

#define SCREEN_WIDTH 320 * 5
#define SCREEN_HEIGHT 200 * 5

#define CANVAS_WIDTH 320 * 4
#define CANVAS_HEIGHT 200 * 4

#define CANVAS_OFFSET 16

#define DEFAULT_BRUSH_SIZE 10

typedef struct Brush {
    Image image;
    int size;
}Brush;
typedef struct Canvas {
    Image image;
    Texture2D texture;
    Color color;
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
    Texture2D texture;
    MousePos pos;
}Cursor;

#endif