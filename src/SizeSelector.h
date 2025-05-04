#ifndef SIZE_SELECTOR_H
#define SIZE_SELECTOR_H

#if defined(__APPLE__)
    #include "../bobcat_ui/all.h"
#else
    #include <bobcat_ui/all.h>
#endif

#include <iostream>
#include "Enums.h"

class SizeSelector : public bobcat::Group {
    bobcat::Button *minusButton;
    bobcat::Button *plusButton;

    int val;
    int minVal;
    int maxVal;
    int step;


    void minus(bobcat::Widget *) {
        if (val - step >= minVal) val -= step;
        if (onChangeCb) onChangeCb(this);
    }

    void plus(bobcat::Widget *) {
        if (val + step <= maxVal) val += step;
        if (onChangeCb) onChangeCb(this);
    }

public:
    SizeSelector(int x, int y, int w, int h, int initial = 10, int minV = 1, int maxV = 100, int stepV = 1)
        : Group(x, y, w, h), val(initial), minVal(minV), maxVal(maxV), step(stepV) {
        minusButton = new bobcat::Button(x, y, h, h, "-");
        plusButton = new bobcat::Button(x + w - h, y, h, h, "+");
        ON_CLICK(minusButton, SizeSelector::minus);
        ON_CLICK(plusButton, SizeSelector::plus);
    }

    int getSize() const {
        return val;
    }

    void setSize(int v) {
        if (v < minVal) v = minVal;
        if (v > maxVal) v = maxVal;
        val = v;
    }
};

#endif