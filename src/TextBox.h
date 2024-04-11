/*
 * A classe TextBox representa uma caixa de texto em uma interface gráfica,
 * capaz de renderizar um texto com quebras de linha e alinhamento específico.
 * Ela possui métodos para configurar o texto, alinhamento, cor de fundo e cor do texto,
 * além de calcular o tamanho necessário para renderizar o texto corretamente.
 * A classe inclui um método parseLines para separar o texto em linhas, levando em
 * consideração as quebras de linha implícitas no texto. O método render desenha a caixa
 * de texto na tela, alinhando o texto de acordo com a configuração especificada.
 * */
//
// Created by jvbrates on 4/5/24.
//

#ifndef COMP_GRAFICA_TEXTBOX_H
#define COMP_GRAFICA_TEXTBOX_H

#include "Conteiner.h"

typedef enum {
                left_top,
                left_center,
                left_bottom,
                center_top,
                center_center,
                center_bottom,
                right_top,
                right_center,
                right_bottom
              }text_align_t;


class TextBox: public Renderizable {
protected:
    std::vector<std::string> text;
    float whithText;
    text_align_t align;
    Vector2  textPos = {0.,0.};
    void parseLines(std::string string);
    colors_enum color = n_of_colors;
    colors_enum textColor = black;
    void render() override;

public:
    TextBox(std::string text, text_align_t align, Vector2  pos, Vector2  size);
    TextBox(std::string text, text_align_t, Vector2  pos);
    void resize();
    void setBackground(colors_enum color);
    void setTextColor(colors_enum color);
    void setAlign(text_align_t textAlign);
    std::string  getText();
    void setString(std::string text_);
    float getHeightText();
    float getWhithText();

};


#endif //COMP_GRAFICA_TEXTBOX_H
