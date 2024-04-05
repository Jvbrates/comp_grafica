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
    Vector2<float> position, size, text_offset;
    colors_enum fill_color = gray;
    std::string texto;
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
    int getState();
    void onclick(std::function<bool(void *)> f, void *argument);
    void setArgument(void * arg);
    void render() override;

};

class CheckboxButton: public Button{
protected:
    bool mouse_left(int) override;

public:
    CheckboxButton(float size, Vector2<float>pos, std::string label);
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
    float CIRCLE_WIDTH = 10.;
    float MAX_VALUE = 100.;
    colors_enum rect_color, circle_color;
    float value = 0;
    void render() override;
protected:
    bool mouse_left(int) override;

public:
    SliderRangeButton(float largura, colors_enum rect_color, colors_enum circle_color);

};


enum {verdadeiro,
        falso,
        terceiro};
#endif //SRC_BUTTON_H
