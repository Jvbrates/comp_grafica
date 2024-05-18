/*
 * A classe Button representa um botão genérico em uma interface gráfica,
 * com suporte para diferentes estados (como pressionado, desativado, etc.) e
 * capacidade de resposta a eventos de clique do mouse. Ela possui métodos
 * para renderizar o botão na tela, configurar sua função de clique e estado atual,
 * além de verificar se houve clique sobre ele.
 *
 * A classe CheckboxButton é uma especialização de Button para representar um botão de
 * seleção (checkbox), com suporte para renderizar o botão de acordo com o estado de seleção.
 *
 * Já a classe SliderRangeButton representa um botão deslizante que permite selecionar um
 * valor dentro de um intervalo predefinido, com métodos para atualizar o valor do botão
 * com base no movimento do mouse e renderizar o botão na tela de acordo com o valor selecionado.
 * */
//
// Created by jvbrates on 3/18/24.
//

#ifndef SRC_BUTTON_H
#define SRC_BUTTON_H
#include "Vector2.h"
#include "EventListener.h"
#include "Conteiner.h"
#include "gl_canvas2d.h"
#include "string"

typedef struct states{
    Vector2  position, size, text_offset; // FIXME text offset não é util
    colors_enum fill_color = gray, text_color = black;
    std::string texto;


    states(Vector2 position_, Vector2 size_, colors_enum fill_, colors_enum text_, std::string textt_){
        this->fill_color = fill_;
        this->text_color = text_;
        this->position = position_;
        this->size = size_;
        this->texto = textt_;
    }


    states(){};
} states_t;


class Button: public EventClient, public Renderizable{


protected:
    std::vector<states_t>  state_array = std::vector<states_t>();
    int state = 0;
    std::function<bool(void *)> f_onclick;
    void * argument;

protected:
    bool mouse_left(int) override;
    bool callWraper();

public:
    bool active = false;
    explicit Button(states_t start_state);
    Button();

    void addState(states_t state);
    void setState(int state);
    states_t * getState(int index);
    int getState();
    void onclick(std::function<bool(void *)> f, void *argument);
    void setArgument(void * arg);
    void render() override;

};

class CheckboxButton: public Button{
protected:
    bool mouse_left(int) override;
    void render() override;

public:
    CheckboxButton(float size, Vector2 pos, std::string label);
};

class SliderRangeButton: public Button {
    /* Valor é referente a posição do deslizante, este valor terá uma variação fixa de -100.f à +100.f;
     * Isto não irá impedir a aplicação em qualquer necessidade de valor, basta fazer a conversão.
     * Ex.: 255 à -255 ->  (X/510)*200
     *
     * Dimensões:
     * Isto será formado por um retângulo e um círculo:
     * O retângulo terá 1/2 a altura circulo que ficará alinhada verticalmente com o centro do retângulo;
     * O círculo se moverá horizontalmente até que o centro encontre um dos limites laterais do retângulo:
     * Portanto, a largura total do objeto será a largura do retângulo mais o diâmetro do círculo;
     * O diâmetro do círculo é fixado e logo, a altura também;
     * */
private:

    colors_enum rect_color, circle_color;
    float value = 0;
    void render() override;
protected:
    bool mouse_left_hold = false;
    bool mouse_left(int) override;
    bool mouse_move(Vector2 ,Vector2 ) override;
    void updateValue();
public:
    static float CIRCLE_WIDTH;
    static float MAX_VALUE;
    SliderRangeButton(float largura, colors_enum rect_color, colors_enum circle_color);
    void setValue(float value);
    float getValue();

    static float convert(float value, float range);
};


#endif //SRC_BUTTON_H
