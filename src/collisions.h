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


typedef enum {
    en_none,   // Nenhuma solução
    en_one,    // Multipla soluções
    en_infinity// Infinitas soluções
} enum_solution;

typedef struct {

    //Caso seja diferente de "one",
    // os demais parametros deste struct devem ser desconsiderados
    enum_solution status;
    float varA;
    float varB;
} solution_rect_rect;

class get_y;


get_y line_equation(Vector2 coord_A, Vector2 coord_B);

namespace collisions{

    Vector2  rotate(Vector2  pos, double rot);

    bool rectangle(Vector2 point, Vector2 rect_1, Vector2 rect_2);

    bool polygon(Vector2  point, std::vector<std::tuple<Vector2 , Vector2 >> edges);

    bool circle(Vector2 point, Vector2 circle_pos, float radius);

    // Retorna o escalar que indica a posição em que a reta A intersecta a reta B,
    solution_rect_rect rect_rect(Vector2 srcA, Vector2 dirA, Vector2 srcB, Vector2 dirB);

}




#endif //COMP_GRAFICA_collisions_H
