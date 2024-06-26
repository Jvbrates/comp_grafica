//
// Created by jvbrates on 4/7/24.
//

#include "Renderizable.h"
#include "gl_canvas2d.h"

void Renderizable::render_caller() {
    CV::relative_translate(posRelative);
    if(visible) {
        render();
    }
    CV::relative_translate(posRelative * -1);
}

Vector2<float> Renderizable::getAbsolutePos() {
    return this->posRelative + this->posAbsoluteSuper;
}

Vector2<float> Renderizable::getRelativePos() {
    return this->posRelative;
}

void Renderizable::setRelativePos(Vector2<float> pos) {
    this->posRelative = pos;

}

void Renderizable::setRelativePos(float x, float y) {
    this->posRelative = Vector2<float>(x,y);

}

