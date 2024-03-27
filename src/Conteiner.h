//
// Created by jvbrates on 3/27/24.
//

#ifndef COMP_GRAFICA_CONTEINER_H
#define COMP_GRAFICA_CONTEINER_H
#include "gl_canvas2d.h"
#include <vector>

#include "Vector2.h"
typedef enum {relative, line, column}position_enum;


class Conteiner : public Renderizable{

    void render() override;

public:
    std::vector<Renderizable*> elements;
    position_enum position_type = relative;

};


#endif //COMP_GRAFICA_CONTEINER_H
