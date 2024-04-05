//
// Created by jvbrates on 3/18/24.
//

#include "button.h"
#include "colisions.h"


void Button::render() {

    auto state_i = this->getState();
    auto curr_state = this->state_array[state_i];
    CV::color(curr_state.fill_color);
    CV::rectFill({0., 0.,}, curr_state.size);
    if (!curr_state.texto.empty()) {
        CV::color(black);
        CV::text(curr_state.text_offset, (curr_state.texto).c_str());
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

void Button::setState(int state_) {
    this->state = state_;
}

void Button::addState(states_t state_) {

}

bool Button::callWraper() {

    if (this->f_onclick && this->active) return (this->f_onclick(this->argument));

    return false;
}

bool Button::mouse_left(int i) {
    if (colisions::rectangle(CV::get_mouse_pos(), this->getAbsolutePos(), this->size + this->getAbsolutePos()) && i == 1) {
        return callWraper();
    }
    return false;
}


Button::Button() {}

//FIXME porque este initialize nao funciona?
CheckboxButton::CheckboxButton(float size, Vector2<float> pos, std::string label) : Button() {
    this->setRelativePos(pos);

    EventListener::add_event(this, en_mouse_left);
    this->size = {size, size};
    states_t s1 = {pos, {size, size}, {-10., size}, white, label};
    states_t s2 = {pos, {size, size}, {-10., size}, black, label};
    this->state_array.push_back(s1);
    this->state_array.push_back(s2);
}


bool CheckboxButton::mouse_left(int i) {
    if (colisions::rectangle(CV::get_mouse_pos(), this->getRelativePos(), this->size + this->getRelativePos()) && i == 1) {
        setState(!getState());
        std::cout << "State" << this->state << std::endl;


        return callWraper();
    }
    return false;

}


//--------------------------------------------------

SliderRangeButton::SliderRangeButton(float largura, colors_enum rect_color, colors_enum circle_color) : Button() {
    this->size = {largura, CIRCLE_WIDTH};
    this->rect_color = rect_color;
    this->circle_color = circle_color;

    EventListener::add_event(this, en_mouse_left);
}

void SliderRangeButton::render() {

    CV::color(rect_color);
    CV::rectFill({CIRCLE_WIDTH / 2.f, CIRCLE_WIDTH / 4.f}, {size.x - CIRCLE_WIDTH / 2.f, CIRCLE_WIDTH * .75f});
    CV::color(circle_color);

    // Deslocamento máximo do circulo em unidades de distância
    float middle_pos = (size.x - CIRCLE_WIDTH / 2.f) / 2;

    float value_pos = (middle_pos / MAX_VALUE) * value;

    CV::circleFill({middle_pos + value_pos, size.y / 2.f}, CIRCLE_WIDTH / 2.f, 10);

}

bool SliderRangeButton::mouse_left(int state) {
    if (!state) {
        std::cout << "Nothing" << state << std::endl;
        this->value = std::fmod(this->value + 10.f, this->MAX_VALUE);
        return false;
    }
    return false;
}
