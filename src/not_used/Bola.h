#ifndef __BOLA_H__
#define __BOLA_H__

#include "gl_canvas2d.h"
#include <cstdlib>
/*
 * listen {
 * mouse_right
 * mouse_left
 * mouse_whell
 * mouse_move_x
 * mouse_move_y
 * keyboard
 * }
 * */

float distance(float x, float y, float x_, float y_){
    float distance_x = x - x_;
    float distance_y = y - y_;
    return sqrt(pow(distance_x,2)+ pow(distance_y,2));

}


class Bola{

public:
    float getCenterX() const {
        return center_x;
    }

    void setCenterX(float centerX) {
        center_x = centerX;
    }

    float getCenterY() const {
        return center_y;
    }

    void setCenterY(float centerY) {
        center_y = centerY;
    }

    float getRadius() const {
        return radius;
    }

    void setRadius(float radius) {
        Bola::radius = radius;
    }

    bool isHover() const {
        return hover;
    }

    void setHover(bool hover) {
        this->hover = hover;
    }

    bool isDrag() const {
        return drag;
    }

    void setDrag(bool drag) {
        this->drag = drag;
    }

private:
    colors_enum color;
    float center_x;
    float center_y;
    float radius;
    bool hover;
    bool drag;

  public:
     Bola(float center_x, float center_y, float radius, colors_enum color){
         this->center_x = center_x;
         this->center_y = center_y;
         this->radius = radius;
         this->color = color;
     }
     void mouse_hover(float x, float y);
     //void mouse_drag(float x, float y);


};

void Bola::mouse_hover(float x, float y) {
    float distance_var = abs(distance(x,y, this->center_x, this->center_y ));
    this->hover = distance_var <= radius;
}




#endif
