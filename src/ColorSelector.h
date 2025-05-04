#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H

#if defined(__APPLE__)
    #include "../bobcat_ui/all.h"
#else
    #include <bobcat_ui/all.h>
#endif

#include "Enums.h"
#include <iostream>

class ColorSelector:public bobcat::Group{
    struct Color{float r;float g;float b;Color(float r=0,float g=0,float b=0):r(r),g(g),b(b){}};
    bobcat::Button* redButton;bobcat::Button* orangeButton;bobcat::Button* yellowButton;
    bobcat::Button* greenButton;bobcat::Button* blueButton;bobcat::Button* indigoButton;
    bobcat::Button* violetButton;COLOR selectedColor;
    void deselectAllColors(){
        redButton->label("");orangeButton->label("");yellowButton->label("");
        greenButton->label("");blueButton->label("");indigoButton->label("");violetButton->label("");
    }
    void visualizeSelectedColor(){
        if(selectedColor==RED)redButton->label("@+5square");
        else if(selectedColor==ORANGE)orangeButton->label("@+5square");
        else if(selectedColor==YELLOW)yellowButton->label("@+5square");
        else if(selectedColor==GREEN)greenButton->label("@+5square");
        else if(selectedColor==BLUE)blueButton->label("@+5square");
        else if(selectedColor==INDIGO)indigoButton->label("@+5square");
        else violetButton->label("@+5square");
    }
    void onClick(bobcat::Widget* sender){
        deselectAllColors();
        if(sender==redButton)selectedColor=RED;else if(sender==orangeButton)selectedColor=ORANGE;
        else if(sender==yellowButton)selectedColor=YELLOW;else if(sender==greenButton)selectedColor=GREEN;
        else if(sender==blueButton)selectedColor=BLUE;else if(sender==indigoButton)selectedColor=INDIGO;
        else selectedColor=VIOLET;
        visualizeSelectedColor();redraw();if(onChangeCb)onChangeCb(this);
    }
public:
    ColorSelector(int x,int y,int w,int h):Group(x,y,w,h){
        redButton=new bobcat::Button(x,y,50,50,"");
        orangeButton=new bobcat::Button(x+50,y,50,50,"");
        yellowButton=new bobcat::Button(x+100,y,50,50,"");
        greenButton=new bobcat::Button(x+150,y,50,50,"");
        blueButton=new bobcat::Button(x+200,y,50,50,"");
        indigoButton=new bobcat::Button(x+250,y,50,50,"");
        violetButton=new bobcat::Button(x+300,y,50,50,"");
        selectedColor=RED;
        redButton->color(fl_rgb_color(255,0,0));orangeButton->color(fl_rgb_color(255,127,0));
        yellowButton->color(fl_rgb_color(255,255,0));greenButton->color(fl_rgb_color(0,255,0));
        blueButton->color(fl_rgb_color(0,0,255));indigoButton->color(fl_rgb_color(75,0,130));
        violetButton->color(fl_rgb_color(148,0,211));
        redButton->labelcolor(FL_WHITE);orangeButton->labelcolor(FL_WHITE);yellowButton->labelcolor(FL_WHITE);
        greenButton->labelcolor(FL_WHITE);blueButton->labelcolor(FL_WHITE);indigoButton->labelcolor(FL_WHITE);
        violetButton->labelcolor(FL_WHITE);
        visualizeSelectedColor();
        ON_CLICK(redButton,ColorSelector::onClick);ON_CLICK(orangeButton,ColorSelector::onClick);
        ON_CLICK(yellowButton,ColorSelector::onClick);ON_CLICK(greenButton,ColorSelector::onClick);
        ON_CLICK(blueButton,ColorSelector::onClick);ON_CLICK(indigoButton,ColorSelector::onClick);
        ON_CLICK(violetButton,ColorSelector::onClick);
    }
    Color getColor()const{
        if(selectedColor==RED)return{1,0,0};
        else if(selectedColor==ORANGE)return{1,127/255.0f,0};
        else if(selectedColor==YELLOW)return{1,1,0};
        else if(selectedColor==GREEN)return{0,1,0};
        else if(selectedColor==BLUE)return{0,0,1};
        else if(selectedColor==INDIGO)return{75/255.0f,0,130/255.0f};
        else return{148/255.0f,0,211/255.0f};
    }
    std::tuple<float,float,float> getRGB()const{auto c=getColor();return{c.r,c.g,c.b};}
    void setColorRGB(float r,float g,float b){
        struct C{float r,g,b;COLOR id;};C arr[7]={{1,0,0,RED},{1,127/255.0f,0,ORANGE},{1,1,0,YELLOW},
            {0,1,0,GREEN},{0,0,1,BLUE},{75/255.0f,0,130/255.0f,INDIGO},{148/255.0f,0,211/255.0f,VIOLET}};
        float best=1e9;COLOR id=RED;
        for(auto&v:arr){float d=(v.r-r)*(v.r-r)+(v.g-g)*(v.g-g)+(v.b-b)*(v.b-b);if(d<best){best=d;id=v.id;}}
        selectedColor=id;deselectAllColors();visualizeSelectedColor();redraw();
    }
};

#endif
