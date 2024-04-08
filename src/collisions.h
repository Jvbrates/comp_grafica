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
#ifndef COMP_GRAFICA_collisions_H
#define COMP_GRAFICA_collisions_H

#include <algorithm>
#include "vector"
#include "Vector2.h"

template<typename T>
class get_y;


template<typename T>
get_y<T> line_equation(Vector2<T>coord_A, Vector2<T>coord_B);

namespace collisions{

    template<typename T>
    Vector2<T> rotate(Vector2<T> pos, double rot);

    template<typename T>
    bool rectangle(Vector2<T>point, Vector2<T>rect_1, Vector2<T>rect_2);

    template<typename T>
    bool polygon(Vector2<T> point, std::vector<std::tuple<Vector2<T>, Vector2<T>>> edges);


    template<typename T>
    bool circle(Vector2<T>point, Vector2<T>circle_pos, T radius);


}


template<typename T>
class get_y{
    T ang;
    T displacement;
public:
    get_y(T ang_,T displacement_){
        this->ang = ang_;
        this->displacement = displacement_;

    }

    T operator()(T y_){
        if(std::isnan(ang))
            return displacement;
        return (y_ - displacement)/ang;
    }

};


template<typename T>
get_y<T> line_equation(Vector2<T>coord_A, Vector2<T>coord_B){
    T ang = (coord_A.y - coord_B.y)/
            (coord_A.x - coord_B.x);

    T displacement = coord_A.y - coord_A.x*ang;
    if((coord_A.x - coord_B.x) == 0) {
        displacement = coord_A.x;
        ang = 0.f/0.f;
    }
    auto funct = get_y<T>(ang, displacement);

    return funct;
}


template<typename T>
bool collisions::rectangle(Vector2<T> point, Vector2<T> rect_1, Vector2<T> rect_2) {
    if((point.x < rect_1.x && point.x < rect_2.x) ||
       (point.y < rect_1.y && point.y < rect_2.y) ||
       (point.x > rect_1.x && point.x > rect_2.x) ||
       (point.y > rect_1.y && point.y > rect_2.y)
            ) {
        return false;

    }
    return true;
}

template<typename T>
Vector2<T> collisions::rotate(Vector2<T> pos, double rot){
    return Vector2<T>{
            static_cast<T>(pos.x * cos(rot) - pos.y * sin(rot)),
            static_cast<T>(pos.x* sin(rot) + pos.y * cos(rot))};
}


template<typename T>
bool collisions::polygon(Vector2<T> point, std::vector<std::tuple<Vector2<T>, Vector2<T>>> edges) {


    auto edges_filtered = std::vector<std::tuple<Vector2<T>, Vector2<T>>>(0);


    /* Filtrando, removendo arestas que não cortam o eixo Y do ponto buscado
     * ou estão completamente a direita. */
    std::copy_if(edges.begin(), edges.end(), std::back_inserter(edges_filtered),
                 [point](std::tuple<Vector2<T>, Vector2<T>> item) {

                     //item = Segmento AB;
                     auto coord_A = std::get<0>(item);
                     auto coord_B = std::get<1>(item);

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
                  [&acm, point](auto item){

                      auto eq = line_equation<T>(std::get<0>(item), std::get<1>(item));

                      auto resultado = eq(point.y);
                      if(point.x <=  resultado) // Aqui eu considero que uma colisao no limite, está dentro.
                          acm++;
                  });

    // 5 - Se o acumulador for impar, então o ponto de colisão está dentro do polígono;


    return (acm%2!=0);
}


template<typename T>
bool collisions::circle(Vector2<T>point, Vector2<T>circle_pos, T radius){
    T x_diff = point.x - circle_pos.x;
    T y_diff = point.y - circle_pos.y;

    T dist = std::sqrt(pow(x_diff,2)+pow(y_diff,2));

    return dist < radius;
}


#endif //COMP_GRAFICA_collisions_H
