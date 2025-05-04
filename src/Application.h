#ifndef APPLICATION_H
#define APPLICATION_H

#if defined(__APPLE__)
    #include "../bobcat_ui/all.h"
#else
    #include <bobcat_ui/all.h>
#endif

#include "Toolbar.h"
#include "Canvas.h"
#include "ColorSelector.h"
#include "SizeSelector.h"


class Application : public bobcat::Application_ {
    bobcat::Window *window;
    Toolbar *toolbar;
    Canvas *canvas;
    ColorSelector *colorSelector;
    SizeSelector *sizeSelector;
    float lastX, lastY;
    bool dragging;

    void onCanvasMouseDown(bobcat::Widget *sender, float mx, float my);

    void onCanvasDrag(bobcat::Widget *sender, float mx, float my);

    void onToolbarChange(bobcat::Widget *sender);

    void onSizeChange(bobcat::Widget *sender);

    void onColorChange(bobcat::Widget *sender);

public:
    Application();
};

#endif
