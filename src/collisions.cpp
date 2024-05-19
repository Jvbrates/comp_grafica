/*
 * Namespace collisions:
 * rotate: rotaciona um Vector2 em radianos;
 * rectangle: Determina se um ponto está dentro de um retângulo
 * polygon:   Determina se um ponto está dentro de um poligono
 * circle:    Determina se um ponto está dentro de um circulo
 * */
//
// Created by jvbrates on 3/24/24.
//


#include <algorithm>
#include "vector"
#include "Vector2.h"
#include "collisions.h"




class get_y;


get_y line_equation(Vector2 coord_A, Vector2 coord_B);


class get_y{
    float ang;
    float displacement;
public:
    get_y(float ang_,float displacement_){
        this->ang = ang_;
        this->displacement = displacement_;

    }

    float operator()(float y_){
        if(std::isnan(ang))
            return displacement;
        return (y_ - displacement)/ang;
    }

};


get_y line_equation(Vector2 coord_A, Vector2 coord_B){
    float ang = (coord_A.y - coord_B.y)/
            (coord_A.x - coord_B.x);

    float displacement = coord_A.y - coord_A.x*ang;
    if((coord_A.x - coord_B.x) == 0) {
        displacement = coord_A.x;
        ang = 0.f/0.f;
    }
    auto funct = get_y (ang, displacement);

    return funct;
}


bool collisions::rectangle(Vector2  point, Vector2  rect_1, Vector2  rect_2) {
    if((point.x < rect_1.x && point.x < rect_2.x) ||
       (point.y < rect_1.y && point.y < rect_2.y) ||
       (point.x > rect_1.x && point.x > rect_2.x) ||
       (point.y > rect_1.y && point.y > rect_2.y)
            ) {
        return false;

    }
    return true;
}

Vector2  collisions::rotate(Vector2  pos, double rot){
    return Vector2 {
             static_cast<float>((pos.x * cos(rot) - pos.y * sin(rot))),
             static_cast<float>((pos.x* sin(rot) + pos.y * cos(rot)))};
}


bool collisions::polygon(Vector2  point, std::vector<repl_tuple_t> edges) {


    auto edges_filtered = std::vector<repl_tuple_t>(0);


    /* Filtrando, removendo arestas que não cortam o eixo Y do ponto buscado
     * ou estão completamente a direita. */
    std::copy_if(edges.begin(), edges.end(), std::back_inserter(edges_filtered),
                 [point](repl_tuple_t item) {

                     //item = Segmento AB;
                     auto coord_A = item.itemA;
                     auto coord_B = item.itemB;

                     if ((point.y < coord_A.y && point.y < coord_B.y) ||
                         (point.y > coord_A.y && point.y > coord_B.y))
                         return false;

                     if (point.x > coord_A.x && point.x > coord_B.x)
                         return false;

                     return true;

                 });


    uint acm {0};

    /*Conhecimentos necessários de Geometria Analíica:
     * 1 - A partir de dois pontos descobrir a equação da reta;
     * 2 - Dado um ponto Y(ponto de colisao) descobrir o ponto X equivalente
     * a partir da equação da reta;
     * 3 - Caso o ponto X descoberto está a direta do ponto de colisao,
     * então soma-se 1 ao acumulador.
     * 4 - Repete-se para cada vértice;
     * */


    std::for_each(edges_filtered.begin(), edges_filtered.end(),
                  [&acm, point](repl_tuple_t item){

                      auto eq = line_equation (item.itemA, item.itemB);

                      auto resultado = eq(point.y);
                      if(point.x <=  resultado) // Aqui eu considero que uma colisao no limite, está dentro.
                          acm++;
                  });

    // 5 - Se o acumulador for impar, então o ponto de colisão está dentro do polígono;


    return (acm%2!=0);
}


bool collisions::circle(Vector2 point, Vector2 circle_pos, float radius){
    float x_diff = point.x - circle_pos.x;
    float y_diff = point.y - circle_pos.y;

    float dist = std::sqrt(pow(x_diff,2)+pow(y_diff,2));

    return dist < radius;
}


solution_rect_rect collisions::rect_rect(Vector2 srcA, Vector2 dirA, Vector2 srcB, Vector2 dirB){
    /*
    O objetivo aqui não é cria uma solução elegante para equações lineares, é só resolver
    o problema especifico de encontrar o ponto de colisão de duas retas.
    Isto implica, por exemplo, que não serão tratados casos em que um dos vetores
    diretores é nulo
    */


    auto diff_src = srcB - srcA;

    float matrix[2][3]; //Matriz


    //Dividir primeira linha pelo primeiro valor
    if(dirA.x != 0 ){
        dirB =dirB*-1;
        matrix[0][0] = dirA.x;
        matrix[0][1] = dirB.x;
        matrix[0][2] = diff_src.x;
        matrix[1][0] = dirA.y;
        matrix[1][1] = dirB.y;
        matrix[1][2] = diff_src.y;



        matrix[0][0] /= dirA.x;
        matrix[0][1] /= dirA.x;
        matrix[0][2] /= dirA.x;

        auto tmp = matrix[1][0]/matrix[0][0];

        matrix[1][0] = 0; // Não é necessário realizar o calculo, mas seria -= matrix[0][0]*tmp
        matrix[1][1] -= matrix[0][1]*tmp;
        matrix[1][2] -= matrix[0][2]*tmp;


        if(matrix[1][1] == 0){
            if(diff_src.y){
                return {en_none, 0.,0.};
            } else {





                return {en_infinity, 0.,0.};
            }
        }

        matrix[1][0] /= matrix[1][1];
        matrix[1][2] /= matrix[1][1];
        matrix[1][1] /= matrix[1][1]; // Valor dividido por si próprio


        tmp = matrix[0][1];

        matrix[0][1] = 0;
        matrix[0][2] -= matrix[1][2]*tmp;


        return {en_one, matrix[0][2], matrix[1][2]};


    } else if (dirA.y){ // Dividir primeira linha pelo segundo valor
        dirB = dirB *-1;
        matrix[1][0] = dirA.x;
        matrix[1][1] = dirB.x;
        matrix[1][2] = diff_src.x;
        matrix[0][0] = dirA.y;
        matrix[0][1] = dirB.y;
        matrix[0][2] = diff_src.y;



        matrix[0][0] /= dirB.x;
        matrix[0][2] /= dirB.x;
        matrix[0][1] /= dirB.x;

        auto tmp = matrix[1][0]/matrix[0][0];

        matrix[1][0] = 0; // Não é necessário realizar o calculo, mas seria -= matrix[0][0]*tmp
        matrix[1][1] -= matrix[0][1]*tmp;
        matrix[1][2] -= matrix[0][2]*tmp;


        if(matrix[1][1] == 0){
            if(diff_src.y){
                return {en_none, 0.,0.};
            } else {
                return {en_infinity, 0.,0.};
            }
        }

        matrix[1][0] /= matrix[1][1];
        matrix[1][2] /= dirA.y;
        matrix[1][1] = 1; // Valor dividido por si próprio


        tmp = matrix[0][1];

        matrix[0][1] = 0;
        matrix[0][2] -= matrix[1][2]*tmp;


        return {en_one, matrix[0][2], matrix[1][2]};


    }


    return {en_none, 0., 0.};

}
