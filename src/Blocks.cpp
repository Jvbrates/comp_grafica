#include "Blocks.h"
#include "SpecialSquare.h"
#include <memory>
#include <vector>
#include "collisions.h"
Blocks::Blocks()
{
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            poligonos.push(std::make_shared<SpecialSquare>(20., Vector2(20.*i, 20.*j), 5.));

        }
    }
}

Blocks::~Blocks()
{
    //dtor
}

typedef struct {
    Vector2 pos_final;
    float used;
} data_moveCircle;

Vector2 Blocks::moveCircle(Vector2 pos, Vector2 movement, float radius){

    pos = pos - this->poligonos.getAbsolutePos();


   std::vector<std::shared_ptr<Polygon_>> filtered_blocks = this->selectByRectangle(pos, movement);
}

std::vector<std::shared_ptr<Polygon_>> Blocks::selectByRectangle(Vector2 pos, Vector2 movement){
    auto retorno = std::vector<std::shared_ptr<Polygon_>>();

    for(std::shared_ptr<Renderizable> i: this->poligonos.elements){
        std::shared_ptr<Polygon_>p = std::dynamic_pointer_cast<Polygon_>(i);
        for (Vector2 point: p->getVertex()){
            if( collisions::rectangle(point, pos, pos+movement)){
                retorno.push_back(p);
                p->setColor(red);
                break;
            }
        }

    }

    return retorno;
}

