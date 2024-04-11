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

class get_y;


get_y line_equation(Vector2 coord_A, Vector2 coord_B);

namespace collisions{

    Vector2  rotate(Vector2  pos, double rot);

    bool rectangle(Vector2 point, Vector2 rect_1, Vector2 rect_2);

    bool polygon(Vector2  point, std::vector<std::tuple<Vector2 , Vector2 >> edges);

    bool circle(Vector2 point, Vector2 circle_pos, float radius);


}




#endif //COMP_GRAFICA_collisions_H
