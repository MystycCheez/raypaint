#ifndef ETC_H
#define ETC_H

enum Tool {
    TOOL_BRUSH,
    TOOL_ERASE,
    TOOL_FILL
};

typedef struct Brush {
    Image image;
    Rectangle rect;
    Vector2 pos;
}Brush;

#endif