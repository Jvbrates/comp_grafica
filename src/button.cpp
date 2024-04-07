//
// Created by jvbrates on 3/18/24.
//

#include "button.h"
#include "collisions.h"


void Button::render() {

    auto state_i = this->getState();
    auto curr_state = this->state_array[state_i];
    CV::color(curr_state.fill_color);
    CV::rectFill({0., 0.,}, curr_state.size);
    if (!curr_state.texto.empty()) {
        CV::color(curr_state.text_color);
        CV::text({
            (this->size.x - curr_state.texto.length()*PXL_STR)/2,
            (this->size.y - PXL_STR_H)/2 + PXL_STR_H
            }, (curr_state.texto).c_str());
    }

}

Button::Button(states_t start_state) {

    EventListener::add_event(this, en_mouse_left);
    this->state_array.push_back(start_state);
    this->size = start_state.size;
    this->setRelativePos(start_state.position);
}

void Button::onclick(std::function<bool(void *)> f, void *argument_onclick) {
    this->argument = argument_onclick;
    this->f_onclick = f;
}

void Button::setArgument(void *arg) {
    this->argument = arg;
}

int Button::getState() {
    return this->state;
}

states_t * Button::getState(int index){
    return &(this->state_array[index]);
}

void Button::setState(int state_) {
    this->state = state_;
}

void Button::addState(states_t state_) {
    this->state_array.push_back(state_);
}

bool Button::callWraper() {

    if (this->f_onclick && this->active) return (this->f_onclick(this->argument));

    return false;
}

bool Button::mouse_left(int i) {

    if (collisions::rectangle<float>(CV::get_mouse_pos(), this->getAbsolutePos(), this->size + this->getAbsolutePos()) && i == 1) {
        return callWraper();
    }
    return false;
}


Button::Button() {}

//FIXME porque este initialize nao funciona?
CheckboxButton::CheckboxButton(float size, Vector2<float> pos, std::string label) : Button() {
    this->setRelativePos(pos);

    EventListener::add_event(this, en_mouse_left);
    this->size = {size+label.length()*10, size};
    states_t s1 = {pos, {size, size}, {label.length()*PXL_STR, size}, black, green,label};
    states_t s2 = {pos, {size, size}, {label.length()*PXL_STR, size}, green, green,label};
    this->state_array.push_back(s1);
    this->state_array.push_back(s2);
}

void CheckboxButton::render() {
    auto state_i = this->getState();
    auto curr_state = this->state_array[state_i];
    CV::color(curr_state.fill_color);
    if(this->state) {
        CV::color(curr_state.fill_color);
        CV::rectFill({curr_state.text_offset.x, 0.,}, curr_state.size + Vector2{curr_state.text_offset.x,0.f});
        CV::color(curr_state.text_color);
        CV::rect({curr_state.text_offset.x, 0.,}, curr_state.size + Vector2{curr_state.text_offset.x,0.f});
    } else {

        CV::color(curr_state.fill_color);
        CV::rectFill({curr_state.text_offset.x, 0.,}, curr_state.size + Vector2{curr_state.text_offset.x,0.f});
        CV::color(curr_state.text_color);
        CV::rect({curr_state.text_offset.x, 0.,}, curr_state.size + Vector2{curr_state.text_offset.x,0.f});
    }
    if (!curr_state.texto.empty()) {
        CV::color(curr_state.text_color);
        CV::text({0.f, curr_state.text_offset.y-5.f}, (curr_state.texto).c_str());
    }
}


bool CheckboxButton::mouse_left(int i) {
    if (collisions::rectangle<float>(CV::get_mouse_pos(), this->getAbsolutePos(), this->size + this->getAbsolutePos()) && i == 1) {
        setState(!getState());
        std::cout << "State" << this->state << std::endl;


        return callWraper();
    }
    return false;

}


//--------------------------------------------------

float SliderRangeButton::CIRCLE_WIDTH = 10.f;
float SliderRangeButton::MAX_VALUE = 100.f;

SliderRangeButton::SliderRangeButton(float largura, colors_enum rect_color, colors_enum circle_color) : Button() {
    this->size = {largura, CIRCLE_WIDTH};
    this->rect_color = rect_color;
    this->circle_color = circle_color;

    EventListener::add_event(this, en_mouse_left);
    EventListener::add_event(this, en_mouse_move);
}


//Offset é definido em relação ao centro
// size: referente retângulo, não ao conjunto inteiro
inline float conversion_to_value(float offset, float MAX_VALUE, float size){
    return (MAX_VALUE/(size/2)*offset);
}

inline float conversion_to_offset(float value, float MAX_VALUE, float size){

    return (size/2.f)/MAX_VALUE * value;
}


void SliderRangeButton::render() {

    CV::color(rect_color);
    CV::rectFill({CIRCLE_WIDTH / 2.f, CIRCLE_WIDTH / 4.f}, {size.x - CIRCLE_WIDTH / 2.f, CIRCLE_WIDTH * .75f});
    CV::color(circle_color);

    // Deslocamento máximo do circulo em unidades de distância
    float middle_pos = (size.x/ 2.f);

    float value_pos = conversion_to_offset(value, MAX_VALUE, size.x - CIRCLE_WIDTH);

    CV::circleFill({middle_pos + value_pos, size.y / 2.f}, CIRCLE_WIDTH / 2.f, 10);

}

bool SliderRangeButton::mouse_left(int state) {
    if (!state &&
        collisions::rectangle<float>(CV::get_mouse_pos(), //Posição do mouse
                        this->getAbsolutePos() + Vector2<float>{CIRCLE_WIDTH / 2.f, 0.}, // Posições do slider
                        this->getAbsolutePos() + this->size - Vector2<float>{CIRCLE_WIDTH / 2.f, 0.})
        )
    {
        this->mouse_left_hold = true;
        std::cout << "Nothing" << state << std::endl;
        this->value = std::fmod(this->value + 10.f, this->MAX_VALUE);

        updateValue();

        return true;
    } else {
        if(this->mouse_left_hold)
            this->mouse_left_hold = false;
    }
    return false;
}


void SliderRangeButton::updateValue() {

    auto offset = CV::get_mouse_pos().x - (getAbsolutePos().x + size.x / 2.f);

    auto size_rect = (size.x - CIRCLE_WIDTH);

    auto new_value = conversion_to_value(offset, MAX_VALUE, size_rect);

    if(new_value > 100.f){
        value = 100.f;
    } else if (new_value < -100.f){
        value = -100.f;
    } else {
        value = new_value;
    }


    callWraper();
}

bool SliderRangeButton::mouse_move(Vector2<float> pos, Vector2<float> desloc) {
    if(mouse_left_hold){
        updateValue();
        return true;
    }

    return false;
}


void SliderRangeButton::setValue(float new_value) {
    if(new_value > 100.f){
        value = 100.f;
    } else if (new_value < -100.f){
        value = -100.f;
    } else {
        value = new_value;
    }
}


/*
 * Diferença entre zero e o valor máximo
 * */
float SliderRangeButton::convert(float value, float range) {
    return SliderRangeButton::MAX_VALUE/ range * value;
}

float SliderRangeButton::getValue() {
    return value;
}
