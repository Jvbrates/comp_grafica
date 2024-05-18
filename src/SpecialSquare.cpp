#include "SpecialSquare.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>


SpecialSquare::SpecialSquare(): Polygon_(){
}

SpecialSquare::SpecialSquare(float size, Vector2 pos, int life_): Polygon_()
{


    this->life = life_;

    this->drawPol = std::vector<Vector2>();


    this->vertex.push_back(pos);
    //this->vertex.push_back(pos - Vector2(radius, radius));


    this->vertex.push_back(pos + Vector2(size, 0.));
    //this->vertex.push_back(pos + Vector2(size, 0.) + Vector2(radius, radius*-1));

    this->vertex.push_back(pos + Vector2(size, size));
    //this->vertex.push_back(pos + Vector2(size, size) + Vector2(radius, radius));

    this->vertex.push_back(pos + Vector2(0., size));
    //this->vertex.push_back(pos + Vector2(0., size) + Vector2(radius*-1, radius));


    this->meanPoint();
}

SpecialSquare::SpecialSquare(float size, Vector2 pos, int life_, en_shape shape): Polygon_()
{


    this->life = life_;
    this->setRelativePos(pos);
    switch(shape){


    case en_diamond: {
        this->addVertex(0.f, -size/2.f);
        this->addVertex(size/2.f, 0);
        this->addVertex(0.f, size/2.f);
        this->addVertex(-size/2.f, 0.);

    break;
    }

    case en_losangulo: {
        this->addVertex(0.f, -size/2.f);
        this->addVertex(size/4.f, 0);
        this->addVertex(0.f, size/2.f);
        this->addVertex(-size/4.f, 0.);
    break;}

     case en_losangulo2: {
        this->addVertex(0.f, -size/4.f);
        this->addVertex(size/2.f, 0);
        this->addVertex(0.f, size/4.f);
        this->addVertex(-size/2.f, 0.);
    break;}


    case en_triagle_re_0: {
        //this->addVertex(-size/2.f, -size/2.f);
        this->addVertex(-size/2.f, size/2.f);
        this->addVertex(size/2.f, size/2.f);
        this->addVertex(size/2.f, -size/2.f);
    break;
    }

        case en_triagle_re_1: {
        this->addVertex(-size/2.f, -size/2.f);
        //this->addVertex(-size/2.f, size/2.f);
        this->addVertex(size/2.f, size/2.f);
        this->addVertex(size/2.f, -size/2.f);
    break;
    }

        case en_triagle_re_2: {
        this->addVertex(-size/2.f, -size/2.f);
        this->addVertex(-size/2.f, size/2.f);
        //this->addVertex(size/2.f, size/2.f);
        this->addVertex(size/2.f, -size/2.f);
    break;
    }

        case en_triagle_re_3: {
        this->addVertex(-size/2.f, -size/2.f);
        this->addVertex(-size/2.f, size/2.f);
        this->addVertex(size/2.f, size/2.f);
        //this->addVertex(size/2.f, -size/2.f);
    break;
    }

    case en_square:
    default:{
        this->addVertex(-size/2.f, -size/2.f);
        this->addVertex(-size/2.f, size/2.f);
        this->addVertex(size/2.f, size/2.f);
        this->addVertex(size/2.f, -size/2.f);
    break;
    }

    }

    this->meanPoint();

}


int SpecialSquare::getLife(){
    return this->life;
}

void SpecialSquare::decreaseLife(int i){
    this->life -= i;
}


void SpecialSquare::render() {

    CV::color(color);


    if(fill)
        CV::polygonFill(vertex);
    else
        CV::polygon(vertex);



    if(this->show_text){
        CV::color(black);
        auto txt_life = std::to_string(life);
        CV::text(mean_point - Vector2(5.*txt_life.size(),5.), txt_life);
    }
}

bool SpecialSquare::noLife()
{
        return this->no_life;
}

void SpecialSquare::noLife(bool l)
{
    this->no_life = l;
}

bool SpecialSquare::showText()
{
    return this->show_text;
}

void SpecialSquare::showText(bool t)
{
    this->show_text = t;
}
