#include "SpecialSquare.h"
#define _USE_MATH_DEFINES
#include <math.h>

SpecialSquare::SpecialSquare(float size, Vector2 pos, float radius): Polygon_()
{


    radius = radius * std::sin(M_PI/4);

    this->drawPol = std::vector<Vector2>();


    this->drawPol.push_back(pos);
    this->vertex.push_back(pos - Vector2(radius, radius));


    this->drawPol.push_back(pos + Vector2(size, 0.));
    this->vertex.push_back(pos + Vector2(size, 0.) + Vector2(radius, radius*-1));

    this->drawPol.push_back(pos + Vector2(size, size));
    this->vertex.push_back(pos + Vector2(size, size) + Vector2(radius, radius));

    this->drawPol.push_back(pos + Vector2(0., size));
    this->vertex.push_back(pos + Vector2(0., size) + Vector2(radius*-1, radius));
}


void SpecialSquare::render() {

    CV::color(color);

    if(draw_collision){
        CV::polygon(vertex);
    }

    if(fill)
        CV::polygonFill(drawPol);
    else
        CV::polygon(drawPol);
}
