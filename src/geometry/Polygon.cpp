//
// Created by jvbrates on 4/22/24.
//

#include "Polygon.h"

Polygon_::Polygon_(std::vector<Vector2> v): fill(false) {
    this->vertex = v;
}

void Polygon_::addVertex(Vector2 vertex_) {
    this->vertex.push_back(vertex_);
}

void Polygon_::setFill(bool f) {
    this->fill = f;
}

void Polygon_::setColor(colors_enum color_) {
    this->color = color_;
}

int Polygon_::countEdge() {
    return this->vertex.size();
}



std::vector<Vector2> *Polygon_::getVertex() {
    return &(this->vertex);
}

std::vector<Vector2> Polygon_::getEdge(int i) {
    i = i%(this->vertex.size());
    return std::vector<Vector2>{this->vertex[i],
                                this->vertex[i+1]};
}

void Polygon_::render() {

    CV::color(color);

    if(fill)
        CV::polygonFill(vertex);
    else
        CV::polygon(vertex);
}
