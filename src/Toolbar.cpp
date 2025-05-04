#include "Toolbar.h"
#include <cstdio>
#include <iostream>
#include "Enums.h"

using namespace bobcat;

void Toolbar::visualizeSelectedTool() {
    // deselect all tools
    mouseButton->color(FL_BACKGROUND_COLOR);
    pencilButton->color(FL_BACKGROUND_COLOR);
    eraserButton->color(FL_BACKGROUND_COLOR);

    circleButton->color(FL_BACKGROUND_COLOR);
    triangleButton->color(FL_BACKGROUND_COLOR);
    rectangleButton->color(FL_BACKGROUND_COLOR);
    polygonButton->color(FL_BACKGROUND_COLOR);

    sendToBackButton->color(FL_BACKGROUND_COLOR);
    bringToFrontButton->color(FL_BACKGROUND_COLOR);

    clearButton->color(FL_BACKGROUND_COLOR);


    // render new tool
    if (tool == MOUSE) {
        mouseButton->color(FL_WHITE);
    } else if (tool == PENCIL) {
        pencilButton->color(FL_WHITE);
    } else if (tool == ERASER) {
        eraserButton->color(FL_WHITE);
    } else if (tool == CIRCLE) {
        circleButton->color(FL_WHITE);
    } else if (tool == TRIANGLE) {
        triangleButton->color(FL_WHITE);
    } else if (tool == RECTANGLE) {
        rectangleButton->color(FL_WHITE);
    } else if (tool == POLYGON) {
        polygonButton->color(FL_WHITE);
    }
}

void Toolbar::onClick(bobcat::Widget *sender) {
    action = NONE;

    if (sender == mouseButton) {
        tool = MOUSE;
    } else if (sender == pencilButton) {
        tool = PENCIL;
    } else if (sender == eraserButton) {
        tool = ERASER;
    } else if (sender == circleButton) {
        tool = CIRCLE;
    } else if (sender == triangleButton) {
        tool = TRIANGLE;
    } else if (sender == rectangleButton) {
        tool = RECTANGLE;
    } else if (sender == polygonButton) {
        tool = POLYGON;
    } else if (sender == clearButton) {
        action = CLEAR;
    } else if (sender == sendToBackButton) {
        action = SEND_TO_BACK;
    } else if (sender == bringToFrontButton) {
        action = BRING_TO_FRONT;
    }

    visualizeSelectedTool();

    if (onChangeCb) onChangeCb(this);
    redraw();
}

Toolbar::Toolbar(int x, int y, int w, int h) : Group(x, y, w, h) {
    int btnWidth = 50, btnHeight = 50, spacing = 50;
    int yOffset = y;

    //
    mouseButton = new Image(x, yOffset, btnWidth, btnHeight, "./assets/mouse.png");
    pencilButton = new Image(x, yOffset += spacing, btnWidth, btnHeight, "./assets/pencil.png");
    eraserButton = new Image(x, yOffset += spacing, btnWidth, btnHeight, "./assets/eraser.png");

    //
    circleButton = new Image(x, yOffset += spacing, btnWidth, btnHeight, "./assets/circle.png");
    triangleButton = new Image(x, yOffset += spacing, btnWidth, btnHeight, "./assets/triangle.png");
    rectangleButton = new Image(x, yOffset += spacing, btnWidth, btnHeight, "./assets/rectangle.png");
    polygonButton = new Image(x, yOffset += spacing, btnWidth, btnHeight, "./assets/polygon.png");

    //
    sendToBackButton = new Image(x, yOffset += spacing, btnWidth, btnHeight, "./assets/send-to-back.png");
    bringToFrontButton = new Image(x, yOffset += spacing, btnWidth, btnHeight, "./assets/bring-to-front.png");

    // 
    clearButton = new Image(x, yOffset += spacing, btnWidth, btnHeight, "./assets/clear.png");

    tool = PENCIL;
    action = NONE;

    mouseButton->box(FL_BORDER_BOX);
    pencilButton->box(FL_BORDER_BOX);
    eraserButton->box(FL_BORDER_BOX);

    circleButton->box(FL_BORDER_BOX);
    triangleButton->box(FL_BORDER_BOX);
    rectangleButton->box(FL_BORDER_BOX);
    polygonButton->box(FL_BORDER_BOX);

    sendToBackButton->box(FL_BORDER_BOX);
    bringToFrontButton->box(FL_BORDER_BOX);

    clearButton->box(FL_BORDER_BOX);

    visualizeSelectedTool();

    ON_CLICK(pencilButton, Toolbar::onClick);
    ON_CLICK(eraserButton, Toolbar::onClick);
    ON_CLICK(circleButton, Toolbar::onClick);
    ON_CLICK(triangleButton, Toolbar::onClick);
    ON_CLICK(rectangleButton, Toolbar::onClick);
    ON_CLICK(polygonButton, Toolbar::onClick);
    ON_CLICK(mouseButton, Toolbar::onClick);
    ON_CLICK(clearButton, Toolbar::onClick);
    ON_CLICK(sendToBackButton, Toolbar::onClick);
    ON_CLICK(bringToFrontButton, Toolbar::onClick);
}

TOOL Toolbar::getTool() const {
    return tool;
}

ACTION Toolbar::getAction() const {
    return action;
}
