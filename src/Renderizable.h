/*
 * Renderizable:
 * Todo objeto desenhável é subclasse de renderizable;
 * - Um Renderizable pode estar dentro de um Conteiner(subclasse de renderizável).
 * - Posicionamento absoluto indica o deslocamento a partir da do canto esquerdo superior da tela
 * - Posicionamento relativo indica o deslocamento a partir do conteiner em que se está inserido;
 *
 * Vector2  posAbsoluteSuper: Posição absoluta do conteiner em que está inserido, caso não
 * estejá inserido em conteiner este valor será {0.,0.}
 *
 * Vector2  posRelative: Posição relativa ao canto esquerdo superior do conteiner em que
 * está inserido. Caso não estejá inserido em um conteiner, será relativo ao canto superior
 * esquerdo da tela;
 *
 * Vector2  size : Tamanho do Renderizable.
 * int priority: Usado para ordenar listas de Renderizable's
 * bool visible: Caso false, não irá renderizar o objeto mesmo que este esteja na CV::render_stack
 *
 * void render(): Função que deve ser sobrescrita por subclasses
 *
 * void render_caller: Desloca-se com uso de CV::relativeTranslation até a posição relativa e
 * então chama render() [se visible == true]. Por fim usa CV::relativeTranslation para retornar
 * a translação anterior;
 *
 *
 * Vector2  getRelativePos(): Obtem posicionamento relativo
 * Vector2  setRelativePos(Vector2 ): define posicionamento relativo
 *
 * Vector2  getAbsolutePos(): Obtem posicionamento absoluto
 *
 *
 * */

//
// Created by jvbrates on 4/7/24.
//

#ifndef COMP_GRAFICA_RENDERIZABLE_H
#define COMP_GRAFICA_RENDERIZABLE_H

#include "Vector2.h"

class Renderizable {

private:
    friend void CV_render();
    friend class Conteiner;

    Vector2  posAbsoluteSuper = {0.,0.};
    Vector2  posRelative {0., 0.};

public:
    Vector2  size {0.,0.};
    int priority = 0;
    bool visible = true;
    virtual void render() = 0;
    Vector2  getAbsolutePos();
    Vector2  getRelativePos();
    virtual void setRelativePos(Vector2  pos);
    virtual void setRelativePos(float x, float y);

private:

    virtual void render_caller() final;
};


#endif //COMP_GRAFICA_RENDERIZABLE_H
