#include "Canvas.h"
#include <cmath>

Canvas::Canvas(int x, int y, int w, int h): Canvas_(x, y, w, h) {
    active = -1;
    selected = -1;
}

void Canvas::startPrint(TOOL tool, float r, float g, float b, int size, float x, float y) {
    prints.emplace_back(tool, r, g, b, size);
    active = prints.size() - 1;
    prints.back().addPoint(x, y);
    selected = -1;
}

void Canvas::addPointToActive(float x, float y) {
    if (active >= 0) {
        prints[active].addPoint(x, y);
    }
}

void Canvas::eraseAt(float x, float y) {
    int hp = h();
    for (int i = (int) prints.size() - 1; i >= 0; --i) {
        float thr = prints[i].getSize() * 2.0f / hp, thr2 = thr * thr;
        for (auto &p: prints[i].getPoints()) {
            float dx = p.x - x, dy = p.y - y;
            if (dx * dx + dy * dy <= thr2) {
                prints.erase(prints.begin() + i);
                active = -1;
                if (selected == i)selected = -1;
                if (selected > i)--selected;
                redraw();
                return;
            }
        }
    }
}

void Canvas::clear() {
    prints.clear();
    active = -1;
    selected = -1;
    redraw();
}

void Canvas::setLastPointActive(float x, float y) {
    if (active >= 0) {
        prints[active].setLastPoint(x, y);
    }
}

bool Canvas::selectAt(float x, float y) {
    int hp = h();
    for (int i = (int) prints.size() - 1; i >= 0; --i) {
        float thr = prints[i].getSize() * 2.0f / hp;
        float thr2 = thr * thr;
        for (auto &p: prints[i].getPoints()) {
            float dx = p.x - x;
            float dy = p.y - y;
            if (dx * dx + dy * dy <= thr2) {
                selected = i;
                return true;
            }
        }
    }

    return false;
}


void Canvas::unselect() {
    selected = -1;
}

bool Canvas::hasSelected() const {
    return selected != -1;
}

void Canvas::moveSelectedBy(float dx, float dy) {
    if (selected >= 0) {
        prints[selected].moveBy(dx, dy);
    }
}

Scribbles *Canvas::getSelected() {
    return selected < 0 ? nullptr : &prints[selected];
}

void Canvas::sendSelectedToBack() {
    if (selected <= 0) {
        return;
    }

    Scribbles obj = prints[selected];
    prints.erase(prints.begin() + selected);
    prints.insert(prints.begin(), obj);
    selected = 0;
}

void Canvas::bringSelectedToFront() {
    if (selected < 0 || selected == (int) prints.size() - 1) {
        return;
    }

    Scribbles obj = prints[selected];
    prints.erase(prints.begin() + selected);
    prints.push_back(obj);
    selected = prints.size() - 1;
}

void Canvas::render() {
    if (!valid()) {
        glViewport(0, 0, w(), h());
    }
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float wpx = static_cast<float>(w());
    float hpx = static_cast<float>(h());
    float aspect = wpx / hpx;

    constexpr float sel_px = 4.0f;
    constexpr float sel_line_width = 2.0f;
    float selu = 2.0f * sel_px / hpx;

    for (size_t idx = 0; idx < prints.size(); ++idx) {
        auto &p = prints[idx];

        glColor3f(p.getR(), p.getG(), p.getB());
        float u = 2.0f * p.getSize() / hpx;

        switch (p.getTool()) {
            case PENCIL:
                glLineWidth(p.getSize());
                glBegin(GL_LINE_STRIP);
                for (auto &pt : p.getPoints()) glVertex2f(pt.x, pt.y);
                glEnd();
                break;

            case CIRCLE: {
                auto c = p.getPoint(0);
                glBegin(GL_POLYGON);
                for (int i = 0; i < 64; ++i) {
                    float a = i * 2.0f * M_PI / 64.0f;
                    glVertex2f(c.x + cosf(a) * u, c.y + sinf(a) * u * aspect);
                }
                glEnd();
                break;
            }

            case RECTANGLE: {
                auto c = p.getPoint(0);
                glBegin(GL_POLYGON);
                glVertex2f(c.x - u, c.y - u * aspect);
                glVertex2f(c.x + u, c.y - u * aspect);
                glVertex2f(c.x + u, c.y + u * aspect);
                glVertex2f(c.x - u, c.y + u * aspect);
                glEnd();
                break;
            }

            case TRIANGLE: {
                auto c = p.getPoint(0);
                glBegin(GL_POLYGON);
                glVertex2f(c.x,     c.y + u * aspect);
                glVertex2f(c.x - u, c.y - u * aspect);
                glVertex2f(c.x + u, c.y - u * aspect);
                glEnd();
                break;
            }

            case POLYGON: {
                auto c = p.getPoint(0);
                glBegin(GL_POLYGON);
                for (int i = 0; i < 5; ++i) {
                    float a = i * 2.0f * M_PI / 5.0f - M_PI / 2.0f;
                    glVertex2f(c.x + cosf(a) * u, c.y + sinf(a) * u * aspect);
                }
                glEnd();
                break;
            }

            default: break;
        }


    }

    glFlush();
    swap_buffers();
}
