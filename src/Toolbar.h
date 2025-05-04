#ifndef TOOLBAR_H
#define TOOLBAR_H

#if defined(__APPLE__)
    #include "../bobcat_ui/all.h"
#else
    #include <bobcat_ui/all.h>
#endif

#include "Enums.h"

class Toolbar : public bobcat::Group {
    // 
    bobcat::Image *mouseButton;
    bobcat::Image *pencilButton;
    bobcat::Image *eraserButton;

    // 
    bobcat::Image *circleButton;
    bobcat::Image *triangleButton;
    bobcat::Image *rectangleButton;
    bobcat::Image *polygonButton;

    //
    bobcat::Image *sendToBackButton;
    bobcat::Image *bringToFrontButton;

    //
    bobcat::Image *clearButton;

    TOOL tool;
    ACTION action;

    void visualizeSelectedTool();

    void onClick(bobcat::Widget *sender);

public:
    Toolbar(int x, int y, int w, int h);

    TOOL getTool() const;

    ACTION getAction() const;
};

#endif
