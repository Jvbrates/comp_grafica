//
// Created by jvbrates on 3/18/24.
//

#include "button.h"
#include "colisions.h"


void Button::render() {

    auto state_i = this->getState();
    auto curr_state = this->state_array[state_i];
    CV::color(curr_state.fill_color);
    CV::rectFill({0.,0.,}, curr_state.size);
    if(!curr_state.texto.empty()) {
        CV::color(black);
        CV::text(curr_state.text_offset, (curr_state.texto).c_str());
    }

}

Button::Button(states_t start_state) {

    EventListener::add_event(this, en_mouse_left);
    this->state_array.push_back(start_state);
    this->size = start_state.size;
    this->posRelative = start_state.position;
}

void Button::onclick(std::function<bool(void *)> f, void * argument_onclick){
    this->argument = argument_onclick;
    this->f_onclick = f;
}

void Button::setArgument(void * arg){
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

bool Button::callWraper(){

    if(this->f_onclick && this->active) return  (this->f_onclick(this->argument));

    return false;
}

bool Button::mouse_left(int i) {
    if(colisions::rectangle(CV::get_mouse_pos(), this->posRelative, this->size + this->posRelative) && i == 1){
        return  callWraper();
    }
    return false;
}


Button::Button() {}

//FIXME porque este initialize nao funciona?
CheckboxButton::CheckboxButton(float size, Vector2<float>pos, std::string label) : Button(){
    this->posRelative = pos;

    EventListener::add_event(this, en_mouse_left);
    this->size = {size, size};
    states_t  s1 = {pos, {size,size}, {-10.,size}, white, label};
    states_t s2 = {pos, {size,size}, {-10.,size}, black, label};
    this->state_array.push_back(s1);
    this->state_array.push_back(s2);
}


bool CheckboxButton::mouse_left(int i) {
    if(colisions::rectangle(CV::get_mouse_pos(), this->posRelative, this->size + this->posRelative) && i == 1){
        setState(!getState());
        std::cout << "State" << this->state << std::endl;


        return  callWraper();
    }
    return false;

}





