#ifndef ETC_H
#define ETC_H

#define DARKERBLUE (Color){16, 32, 96, 255}

#define SCALAR 5

#define SCREEN_WIDTH 320 * SCALAR
#define SCREEN_HEIGHT 200 * SCALAR

#define CANVAS_WIDTH 240 * SCALAR
#define CANVAS_HEIGHT 160 * SCALAR

#define CANVAS_OFFSET 16

#define DEFAULT_BRUSH_SIZE 10
#define DEFAULT_BRUSH_COLOR RAYWHITE
#define DEFAULT_BRUSH_SHAPE SHAPE_SQUARE
#define DEFAULT_BRUSH_TYPE BRUSH_BASIC

#define NUM_BRUSH_SHAPES 2
#define NUM_BRUSH_TYPES 2

enum BrushShapes{
    SHAPE_SQUARE,
    SHAPE_CIRCLE,
};
enum BrushTypes{
    BRUSH_BASIC,
    BRUSH_ERASE
};
enum SelectionTypes{
    BRUSH,
    CANVAS
};

typedef struct ColorFloat {
    float r;
    float g;
    float b;
    float a;
}ColorFloat;

typedef struct ImageNode {
    Image image;
    struct ImageNode* next;
    struct ImageNode* prev;
}ImageNode;

typedef struct Brush {
    Image image;
    uint8_t shape;
    uint8_t type;
    uint8_t size;
    Color color;
}Brush;
typedef struct Canvas {
    Image image;
    Color color;
    Texture2D tex_paintLayer;
    Texture2D tex_backgroundLayer;
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