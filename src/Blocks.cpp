#include "Blocks.h"
#include "SpecialSquare.h"
#include <memory>
#include <vector>
#include "collisions.h"
#include <math.h>
Blocks::Blocks()
{

    poligonos.push(std::make_shared<SpecialSquare>(30., Vector2(50., 40.), 5.));
    poligonos.push(std::make_shared<SpecialSquare>(30., Vector2(-20., 80.), 5.));


}

Blocks::~Blocks()
{
    //dtor
}


data_moveCircle Blocks::moveCircle(Vector2 pos, Vector2 movement, float radius,
                                   std::vector<Vector2> *col_points){
    //Como a grade inteira de blocos pode estar movida, então pos é traduzido para posição correta
    auto tpos = pos - this->poligonos.getAbsolutePos();

    col_points->push_back(pos);

    data_moveCircle dt = this->recursiveMoveCircle(tpos, movement, radius, col_points);

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

    std::shared_ptr<Polygon_> colide;
    solution_rect_rect save_colision = {en_none, std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()};
    Vector2 save_segment;

    //Obtem a colisão, caso haja
    std::for_each(filtered.begin(), filtered.end(),
                  [pos, mov, &save_colision, &colide, &save_segment](std::shared_ptr<Polygon_> item){
                    for(int i = 0; i < item->countEdge(); i++){
                        auto aresta = item->getEdge(i);
                        solution_rect_rect tmp = collisions::rect_rect(pos, mov, aresta[0], aresta[1]-aresta[0]);

                    if(tmp.status == en_one  //Colisão de linhas
                        && tmp.varA < save_colision.varA && tmp.varA > 0.f //Colisão dentro do segmento A
                        && tmp.varB < 1 && tmp.varB >=0
                       ){
                            save_colision = tmp;
                            colide = item;
                            save_segment = aresta[1]-aresta[0];

                        }
                    }

                  });


    if(save_colision.status == en_one && save_colision.varA  < 1.f){
        Vector2 reflex = mov*(1-save_colision.varA);

        reflex = Vector2::reflex(reflex, save_segment);

        return data_moveCircle{pos+(mov*save_colision.varA),reflex, true};
    } else {
        return data_moveCircle {pos+mov, mov, false};
    }


}

data_moveCircle Blocks::recursiveMoveCircle(Vector2 pos, Vector2 movement, float radius,
                                            std::vector<Vector2> *col_points){


    //Filtra quais blocos possivelmente participaram da colisão
   std::vector<std::shared_ptr<Polygon_>> filtered_blocks = this->selectByRectangle(pos, movement);


   //Caso não haja nenhuma colisão
   if(filtered_blocks.empty()){
    return data_moveCircle{pos+movement,movement};
   }
   data_moveCircle dtMove = this->firstCollision(filtered_blocks, pos, movement);



   this->sanitizePolygons();

    col_points->push_back(dtMove.pos_final + this->poligonos.getAbsolutePos());

   if(dtMove.collision == false){
        return dtMove;
   } else {
        return this->recursiveMoveCircle(dtMove.pos_final, dtMove.reflex, radius, col_points);
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

