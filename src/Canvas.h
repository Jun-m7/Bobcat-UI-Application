#ifndef CANVAS_H
#define CANVAS_H

#include "../bobcat_ui/all.h"
#include <vector>
#include "Scribbles.h"

class Canvas : public bobcat::Canvas_ {
    std::vector<Scribbles> prints;

    int active;
    int selected;

public:
    Canvas(int x, int y, int w, int h);

    void startPrint(TOOL tool, float r, float g, float b, int size, float x, float y);

    void addPointToActive(float x, float y);

    void setLastPointActive(float x, float y);

    void eraseAt(float x, float y);

    void clear();

    bool selectAt(float x, float y);

    void unselect();

    bool hasSelected() const;

    void moveSelectedBy(float dx, float dy);

    Scribbles *getSelected();

    void sendSelectedToBack();

    void bringSelectedToFront();

    void render() override;
};

#endif
