//
// Created by jvbrates on 4/22/24.
//

#include "Polygon.h"
#include "../collisions.h"
#include <tuple>

Polygon_::Polygon_(std::vector<Vector2> v): fill(false) {
    this->vertex = v;
}

Polygon_::Polygon_(): fill(false) {
    this->vertex = std::vector<Vector2>();
}

void Polygon_::addVertex(Vector2 vertex_) {
    this->vertex.push_back(vertex_);
}

void Polygon_::addVertex(float x, float y) {
    this->vertex.push_back(Vector2(x,y));
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



std::vector<Vector2> Polygon_::getVertex() {
    return (this->vertex);
}

std::vector<Vector2> Polygon_::getEdge(int i) {

    return std::vector<Vector2>{this->vertex[i%(this->vertex.size())] + this->getRelativePos(),
                                this->vertex[(i+1)%(this->vertex.size())] + this->getRelativePos()};
}

//
bool Polygon_::inside(Vector2 point) {
    //Usando tupla por causa do antigo collisions
    auto edges = std::vector<std::tuple<Vector2 , Vector2 >>(0);

    for(auto i = 0; i < this->vertex.size(); i++){
        edges.push_back(
            std::tuple<Vector2 , Vector2 >(
                                            this->vertex[i%this->vertex.size()],
                                            this->vertex[(i+1)%this->vertex.size()]
                                           )
            );

    }

    return collisions::polygon(point, edges);
}

Vector2 Polygon_::meanPoint(){
    int i = 0;
    Vector2 tmp = Vector2(0.,0.);
    for(;i< countEdge(); i++){
        tmp+=vertex[i];
    }

    mean_point = tmp/(float)i;
    return mean_point;
}



void Polygon_::render() {

    CV::color(color);

    if(fill)
        CV::polygonFill(vertex);
    else
        CV::polygon(vertex);
}

void Polygon_::rotate(double rad)
{
    for(Vector2 &item: this->vertex){
        item.setAngle(item.getAngle()+rad);
    }
}

void Polygon_::setAngle(double rad)
{

    if(this->vertex.empty()){
        return;
    }

        for(Vector2 &item: this->vertex){
        item.setAngle(rad);
    }
}

void Polygon_::translate(Vector2 t)
{
    for(Vector2 &item: this->vertex){
        item = item + t;
    }

    this->meanPoint();

}

void Polygon_::scale(float scale)
{
    for(Vector2 &item: this->vertex){
        item = item*scale;
    }

}
