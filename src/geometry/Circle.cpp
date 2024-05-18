//
// Created by jvbrates on 4/22/24.
//

#include "Circle.h"

float Circle::getRay() const {
    return ray;
}

void Circle::setRay(float ray_) {
    Circle::ray = ray_;
}

bool Circle::isFill() const {
    return fill;
}

void Circle::setFill(bool fill_) {
    Circle::fill = fill_;
}

colors_enum Circle::getColor() const {
    return color;
}

void Circle::setColor(colors_enum color_) {
    Circle::color = color_;
}


void Circle::render() {
    CV::color(color);

    if(fill){
        CV::circleFill({0.,0.},
                       ray,
                       vertex);
    } else {
        CV::circle({0.,0.},
                       ray,
                       vertex);
    }

}

Circle::Circle(float ray_, unsigned int vertex_, colors_enum color_, bool filled) {
    this->ray = ray_;
    this->vertex = vertex_;
    this->color = color_;
    this->fill = filled;

}


//Função grande?

