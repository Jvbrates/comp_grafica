#include "Blocks.h"
#include "SpecialSquare.h"
#include <memory>
#include <vector>
#include "collisions.h"
#include <math.h>
#include <errno.h>

Blocks::Blocks()
{



    poligonos.push(std::make_shared<SpecialSquare>(500., Vector2(5., 4.), 5.));

    auto tmp = std::dynamic_pointer_cast<SpecialSquare>(this->poligonos.lastElement());

    tmp->noLife(true);
    tmp->showText(false);

    poligonos.push(std::make_shared<SpecialSquare>(100., Vector2(-50., -40.), 5.));
    poligonos.lastElement()->setRelativePos(100.,100.);

    poligonos.push(std::make_shared<SpecialSquare>(50., Vector2(455., 455.), 5.));
    poligonos.push(std::make_shared<SpecialSquare>(50., Vector2(405., 455.), 5.));
    poligonos.push(std::make_shared<SpecialSquare>(50., Vector2(355., 455.), 5.));
    poligonos.push(std::make_shared<SpecialSquare>(50., Vector2(305., 455.), 5.));
    poligonos.push(std::make_shared<SpecialSquare>(50., Vector2(255., 455.), 5.));
    poligonos.push(std::make_shared<SpecialSquare>(50., Vector2(205., 455.), 5.));
    poligonos.push(std::make_shared<SpecialSquare>(50., Vector2(155., 455.), 5.));
    poligonos.push(std::make_shared<SpecialSquare>(50., Vector2(105., 455.), 5.));
    poligonos.push(std::make_shared<SpecialSquare>(50., Vector2(55., 455.), 5.));
    poligonos.push(std::make_shared<SpecialSquare>(50., Vector2(5., 455.), 5.));


}

Blocks::~Blocks()
{
    //dtor

    if(mapa){
        fclose(mapa);
        mapa = nullptr;
    }
}

void Blocks::moveDown(){
    //O primeiro item não deve ser movido pois é
    for(std::vector<std::shared_ptr<Renderizable>>::iterator it = poligonos.elements.begin() + 1; it != poligonos.elements.end(); it++){
        std::shared_ptr<Polygon_> c_it = std::dynamic_pointer_cast<Polygon_>(*it);

        c_it->translate(Vector2(0.,this->unitsize.y*-1));

    }
}

void Blocks::loadLine(){
    moveDown();

    if(linhas_carregadas == total_linhas){
        return;
    }

    for(int j = 0;j < colunas; j++){
            int tmp_ = 0;
            int t   =  fscanf(mapa, "%i", &tmp_);

            std::cout << "Leu: " << tmp_ << ":" << feof(mapa) << ":" << t << std::endl;
            if(tmp_ != 0){
                poligonos.push(std::make_shared<SpecialSquare>(unitsize.x, Vector2(j*unitsize.x, (linhas-1)*unitsize.y), tmp_));
            }
        }

    linhas_carregadas++;


}

void Blocks::init(){
    if(!mapa){
            std::cout << "Falha ao abrir arquivo" << std::endl;
        exit(0);
    }

    for(int i = 0; i < linhas; i++){
        for(int j = 0;j < colunas; j++){

            int tmp = 0;
            int t   =  fscanf(mapa, "%i", &tmp);

            std::cout << "Leu: " << tmp << ":" << strerror(errno) << ":" << t << std::endl;

            if(tmp != 0){
                poligonos.push(std::make_shared<SpecialSquare>(unitsize.x, Vector2(j*unitsize.x, i*unitsize.y), tmp));
            }
        }
    }

    linhas_carregadas = linhas;
}

Blocks::Blocks(char *file)
{

    mapa = fopen(file, "r");

    if(!mapa){
            std::cout << "Falha ao abrir arquivo" << std::endl;
        exit(0);
    }



    fscanf(this->mapa, "%i", &(this->colunas));
    fscanf(this->mapa, "%i", &(this->linhas));
    fscanf(this->mapa, "%i", &(this->total_linhas));

    //Limites principais
    auto ref_size = Vector2(this->unitsize.x*colunas,this->unitsize.y*linhas) + Vector2(0.5,0.5);


    std::shared_ptr<SpecialSquare> grade = std::make_shared<SpecialSquare>();

    grade->addVertex(Vector2(-0.5,-0.5));
    grade->addVertex(Vector2(-0.5,ref_size.y));
    grade->addVertex(ref_size);
    grade->addVertex(Vector2(ref_size.x, -0.5));

    grade->noLife(true);
    grade->showText(false);

    this->poligonos.push(grade);

    init();

}

data_moveCircle Blocks::moveCircle(Vector2 pos, Vector2 movement, float radius,
                                   std::vector<Vector2> *col_points){
    //Como a grade inteira de blocos pode estar movida, então pos é traduzido para posição correta
    auto tpos = pos - this->poligonos.getAbsolutePos();

    if(col_points){
    col_points->push_back(pos);
    }
    std::vector<Vector2> tmp = {pos, pos};

    data_moveCircle dt = this->recursiveMoveCircle(tpos, movement, radius, col_points, tmp);

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
                if(cast_item->getLife() <= 0 && !cast_item->noLife()) return true;}
                )
              , this->poligonos.elements.end()
              );
}

// Será responsavel por calcular a existencia de colisão, caso exista retorna
// collision: true
// pos: posicao da colisao
// reflex: Vetor de reflexão que será usado recursivamente
data_moveCircle Blocks::firstCollision(std::vector<std::shared_ptr<Polygon_>> filtered, Vector2 pos, Vector2 mov, std::vector<Vector2> prev_segment){

    std::shared_ptr<SpecialSquare> colide;
    solution_rect_rect save_colision = {en_none, std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()};
    std::vector<Vector2> save_segment = std::vector<Vector2>();
    save_segment.reserve(2);

    //Obtem a colisão, caso haja
    std::for_each(filtered.begin(), filtered.end(),
                  [pos, mov, &save_colision, &colide, &save_segment, prev_segment](std::shared_ptr<Polygon_> item){
                    for(int i = 0; i < item->countEdge(); i++){
                        auto aresta = item->getEdge(i);
                        solution_rect_rect tmp = collisions::rect_rect(pos, mov, aresta[0], aresta[1]-aresta[0]);

                    if(tmp.status == en_one  //Colisão de linhas
                        && tmp.varA < save_colision.varA && tmp.varA > 0.f && tmp.varA < 1.f //Colisão dentro do segmento A
                        && tmp.varB < 1 && tmp.varB >=0 //Colisão dentro do Segmento B
                        && prev_segment[0] != aresta[0]   // Uma colisão não pode ocorrer em sequencia no mesmo segmento
                        && prev_segment[1] != aresta[1]
                       ){
                            save_colision = tmp;
                            colide =  std::dynamic_pointer_cast<SpecialSquare>(item);
                            save_segment[0] = aresta[0];
                            save_segment[1] = aresta[1];

                        }
                    }

                  });


    if(save_colision.status == en_one && save_colision.varA  < 1.f){
        Vector2 reflex = mov*(1-save_colision.varA);

        reflex = Vector2::reflex(reflex, save_segment[1] - save_segment[0]);

        colide->decreaseLife(4);
        data_moveCircle tmp = {pos+(mov*save_colision.varA),reflex, true};
        tmp.prev_segment.push_back(save_segment[0]);
        tmp.prev_segment.push_back(save_segment[1]);
        return tmp;
    } else {
        return data_moveCircle {pos+mov, mov, false, prev_segment};
    }


}

data_moveCircle Blocks::recursiveMoveCircle(Vector2 pos, Vector2 movement, float radius,
                                            std::vector<Vector2> *col_points,
                                            std::vector<Vector2> prev_segment){


    //Filtra quais blocos possivelmente participaram da colisão
   std::vector<std::shared_ptr<Polygon_>> filtered_blocks = std::vector<std::shared_ptr<Polygon_>>();

   for(auto item: this->poligonos.elements){
    filtered_blocks.push_back(std::static_pointer_cast<Polygon_>(item));
   }


   //Caso não haja nenhuma colisão
   if(filtered_blocks.empty()){
    return data_moveCircle{pos+movement,movement, false};
   }
   data_moveCircle dtMove = this->firstCollision(filtered_blocks, pos, movement, prev_segment);



   this->sanitizePolygons();

   if(col_points){
    col_points->push_back(dtMove.pos_final + this->poligonos.getAbsolutePos());
   }
   if(dtMove.collision == false){
        return dtMove;
   } else {
       Vector2 tmp = Vector2(1.,1.); //Evitar que o limite de precisao float cause problemas
        tmp.setAngle(movement.getAngle());
        tmp = tmp * -1;



        return this->recursiveMoveCircle(dtMove.pos_final, dtMove.reflex, radius, col_points, dtMove.prev_segment);
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

