#ifndef SCRIBBLES_H
#define SCRIBBLES_H

#include "Enums.h"
#include <vector>
#include <cmath>

struct Point {
    float x;
    float y;

    Point(float x, float y): x(x), y(y) {}

};

class Scribbles {

    std::vector<Point> points;

    TOOL tool;

    float r, g, b;

    int size;

public:
    Scribbles(TOOL t, float r, float g, float b, int s): tool(t), r(r), g(g), b(b), size(s) {}

    void addPoint(float x, float y) { points.emplace_back(x, y); }
    const std::vector<Point> &getPoints() const { return points; }
    Point getPoint(std::size_t i) const { return points.at(i); }
    TOOL getTool() const { return tool; }
    float getR() const { return r; }
    float getG() const { return g; }
    float getB() const { return b; }
    int getSize() const { return size; }

    void setColor(float rr, float gg, float bb) {
        r = rr;
        g = gg;
        b = bb;
    }

    void setSize(int s) { size = s; }

    bool hit(float x, float y) const {
        float thr = std::max(3, size);
        float t2 = thr * thr;
        for (auto &p: points) {
            float dx = p.x - x, dy = p.y - y;
            if (dx * dx + dy * dy <= t2)return true;
        }
        return false;
    }

    void setLastPoint(float x, float y) {
        if (!points.empty()) {
            points.back().x = x;
            points.back().y = y;
        }
    }

    void moveBy(float dx, float dy) {
        for (auto &p: points) {
            p.x += dx;
            p.y += dy;
        }
    }
};

#endif 