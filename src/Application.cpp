#include "Application.h"
#include "Enums.h"
#include <iostream>

using namespace bobcat;

void Application::onCanvasMouseDown(bobcat::Widget *, float mx, float my) {
    TOOL t = toolbar->getTool();

    switch (t) {
        case ERASER: {
            canvas->eraseAt(mx, my);
            canvas->redraw();
            return;
        }

        case MOUSE: {
            bool hit = canvas->selectAt(mx, my);
            dragging = hit;

            if (hit) {
                auto *obj = canvas->getSelected();
                colorSelector->setColorRGB(obj->getR(), obj->getG(), obj->getB());
                sizeSelector->setSize(obj->getSize());
                lastX = mx;
                lastY = my;
            } else {
                canvas->unselect();
            }

            canvas->redraw();
            return;
        }

        default: {
            auto [r, g, b] = colorSelector->getRGB();
            canvas->startPrint(t, r, g, b, sizeSelector->getSize(), mx, my);
            canvas->redraw();
            break;
        }
    }
}

void Application::onCanvasDrag(bobcat::Widget *, float mx, float my) {
    TOOL t = toolbar->getTool();

    switch (t) {
        case PENCIL:
            canvas->addPointToActive(mx, my);
            canvas->redraw();
            break;

        case MOUSE:
            if (dragging && canvas->hasSelected()) {
                float dx = mx - lastX;
                float dy = my - lastY;
                lastX = mx;
                lastY = my;
                canvas->moveSelectedBy(dx, dy);
                canvas->redraw();
            }
            break;

        case ERASER:
            canvas->eraseAt(mx, my);
            canvas->redraw();
            break;

        default:
            break;
    }
}

void Application::onToolbarChange(bobcat::Widget *) {
    ACTION act = toolbar->getAction();

    switch (act) {
        case CLEAR:
            canvas->clear();
            return;

        case SEND_TO_BACK:
            if (canvas->hasSelected()) {
                canvas->sendSelectedToBack();
                canvas->redraw();
            }
            break;

        case BRING_TO_FRONT:
            if (canvas->hasSelected()) {
                canvas->bringSelectedToFront();
                canvas->redraw();
            }
            break;

        default:
            break;
    }
}

void Application::onSizeChange(bobcat::Widget *) {
    if (canvas->hasSelected()) {
        canvas->getSelected()->setSize(sizeSelector->getSize());
        canvas->redraw();
    }
}

void Application::onColorChange(bobcat::Widget *) {
    if (canvas->hasSelected()) {
        auto [r, g, b] = colorSelector->getRGB();
        canvas->getSelected()->setColor(r, g, b);
        canvas->redraw();
    }
}

Application::Application() {
    window = new bobcat::Window(20, 20, 500, 500, "Programming Project");
    toolbar = new Toolbar(0, 0, 50, 600);
    canvas = new Canvas(50, 0, 450, 450);
    colorSelector = new ColorSelector(50, 450, 350, 50);
    sizeSelector = new SizeSelector(400, 450, 100, 50);
    colorSelector->box(FL_BORDER_BOX);

    window->add(toolbar);
    window->add(canvas);
    window->add(colorSelector);
    window->add(sizeSelector);

    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_DRAG(canvas, Application::onCanvasDrag);
    ON_CHANGE(toolbar, Application::onToolbarChange);
    ON_CHANGE(sizeSelector, Application::onSizeChange);
    ON_CHANGE(colorSelector, Application::onColorChange);

    lastX = lastY = 0;
    dragging = false;

    window->show();
}
