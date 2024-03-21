//
// Created by jvbrates on 3/18/24.
//

#include "button.h"

button::button(Vector2<float> pos, Vector2<float> size, colors_enum fill_color){
    this->fill_color = fill_color;
    this->size = size;
    this->position = pos;

}

void button::render() {
    CV::translate(this->position);
    CV::color(fill_color);
    CV::rectFill(this->size);
    if(!texto.empty()) {
        CV::color(text_color);
        CV::text(this->position + this->text_offset, (this->texto).c_str());
    }
}

void button::text(Vector2<float> offset, std::string _texto, colors_enum color){
    this->text_offset = offset;
    this->texto = _texto;
    this->text_color = color;
}