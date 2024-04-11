/*
 * Conteiner:
 * - subclasse de EventClient e Renderizable
 * - Agrupa e organiza instancias de Renderizable;
 * - usa EventClient para capturar clicks e evitar que sejam passados para outros objetos posicionados atrás de si;
 *
 * std::vector<std::shared_ptr<Renderizable>> elements: Vetor de Pointeiros para instâncias de Renderizable;
 *
 * push(): Insere em elements;
 *
 * pop(): Remove o último item de elements;
 *
 * lasElement(): Retorna último item de elements;
 *
 * findRemove(): Busca e remove de elements;
 *
 * position_type: Leia composer();
 *
 * composer(): Organiza os itens contidos(elements) com base em position_type:
 * - relative: Não altera o posicionamentos dos itens;
 * - line: Altera a posição relativa para que os itens fiquem organizados lado a lado;
 * - column: Altera a posição relativa para que os itens fiquem organizados em coluna, de cima para baixo;
 * Ao fim altera seu size para emoldurar os itens;
 *
 *
 * color: Leia render()
 *
 * render(): Caso visible, desenha um retângulo de cor color e do seu tamanho e posição (Usado para desenhar fundo)
 * Chama render_caller() para cada um dos itens em elements.
 * */

//
// Created by jvbrates on 3/27/24.
//

#ifndef COMP_GRAFICA_CONTEINER_H
#define COMP_GRAFICA_CONTEINER_H
#include "gl_canvas2d.h"
#include <vector>
#include <memory>
#include "EventListener.h"
#include "Renderizable.h"
#include "Vector2.h"
typedef enum {relative, line, column}position_enum;





class Conteiner : public Renderizable, public EventClient {
    colors_enum color = black;
public:
    void backgroundColor(colors_enum);
    void render() override;
    std::vector<std::shared_ptr<Renderizable>> elements;
    position_enum position_type = relative;
    bool visible = false;
    void composer();
    void push(std::shared_ptr<Renderizable> item);
    void findRemove(std::shared_ptr<Renderizable> item);
    void pop();
    std::shared_ptr<Renderizable> lastElement();
    void updateElementsPos();
    void setRelativePos(Vector2  pos) override;
    void setRelativePos(float x, float y) override;
    ~Conteiner();


    //Evitar clicks por detrás do conteiner; ISSUE #8
    bool mouse_left(int state);
    bool mouse_right(int state);


};


#endif //COMP_GRAFICA_CONTEINER_H
