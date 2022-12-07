//
// Created by michelle on 17/05/18.
//

#ifndef STRING_RENDER_DATA_H
#define STRING_RENDER_DATA_H

enum StringAlignment {
    ALIGN_LEFT,
    ALIGN_RIGHT,
    ALIGN_CENTER
};

struct StringRenderData {
    const char* key;
    const char* font;
    const char* string;
    const float scale;
    const int x;
    const int y;
    const StringAlignment alignment;
    const float rotation;
};

#endif