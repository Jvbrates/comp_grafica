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


data_moveCircle Blocks::moveCircle(Vector2 pos, Vector2 movement, float radius){
    //Como a grade inteira de blocos pode estar movida, então pos é traduzido para posição correta
    auto tpos = pos - this->poligonos.getAbsolutePos();

    data_moveCircle dt = this->recursiveMoveCircle(tpos, movement, radius);

    //Retorna translação
    dt.pos_final+= this->poligonos.getAbsolutePos();

    return dt;

    }



void Blocks::sanitizePolygons(){
        //Remove blocos com life == 0
    this->poligonos.elements.erase(
               std::remove_if(this->poligonos.elements.begin(), this->poligonos.elements.end(),
                [](std::shared_ptr<Renderizable> item) {
                std::shared_ptr<SpecialSquare> cast_item = std::dynamic_pointer_cast<SpecialSquare>(item);
                if(cast_item->getLife() == 0) return true;}
                )
              , this->poligonos.elements.end()
              );
}

// Será responsavel por calcular a existencia de colisão, caso exista retorna
// collision: true
// pos: posicao da colisao
// reflex: Vetor de reflexão que será usado recursivamente
data_moveCircle Blocks::firstCollision(std::vector<std::shared_ptr<Polygon_>> filtered, Vector2 pos, Vector2 mov){
    return data_moveCircle();
}

data_moveCircle Blocks::recursiveMoveCircle(Vector2 pos, Vector2 movement, float radius){


    //Filtra quais blocos possivelmente participaram da colisão
   std::vector<std::shared_ptr<Polygon_>> filtered_blocks = this->selectByRectangle(pos, movement);


   //Caso não haja nenhuma colisão
   if(filtered_blocks.size() == 0){
    return data_moveCircle{pos+movement,movement};
   }

   data_moveCircle dtMove = this->firstCollision(filtered_blocks, pos, movement);


   this->sanitizePolygons();

   if(dtMove.collision == false){
        return dtMove;
   } else {
        return this->recursiveMoveCircle(dtMove.pos_final, dtMove.reflex, radius);
   }
}

std::vector<std::shared_ptr<Polygon_>> Blocks::selectByRectangle(Vector2 pos, Vector2 size_){
    auto retorno = std::vector<std::shared_ptr<Polygon_>>();

    for(std::shared_ptr<Renderizable> i: this->poligonos.elements){
        std::shared_ptr<Polygon_>p = std::dynamic_pointer_cast<Polygon_>(i);
        for (Vector2 point: p->getVertex()){
            if( collisions::rectangle(point, pos, pos+size_)){
                retorno.push_back(p);
                p->setColor(red);
                break;
            }
        }

    }

    return retorno;
}

