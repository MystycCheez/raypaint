#ifndef ETC_H
#define ETC_H

#define SCREEN_WIDTH 320 * 5
#define SCREEN_HEIGHT 200 * 5

enum Tool {
    TOOL_BRUSH,
    TOOL_ERASE,
    TOOL_FILL
};
enum BrushType {
    BRUSH_SQUARE,
    BRUSH_ROUND,
};

typedef struct Brush {
    Image image;
    Rectangle rect;
    int size;
    float scale;
}Brush;
typedef struct MousePos {
    Vector2 old;
    Vector2 current;
}MousePos;

#endif