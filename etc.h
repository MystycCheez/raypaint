#ifndef ETC_H
#define ETC_H

#define SCREEN_WIDTH 320 * 5
#define SCREEN_HEIGHT 200 * 5

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