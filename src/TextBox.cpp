//
// Created by jvbrates on 4/5/24.
//

#include "TextBox.h"
#include <sstream>

TextBox::TextBox(std::string text, text_align_t align, Vector2  pos, Vector2  size){
    parseLines(text);
    this->align = align;
    this->size  = size;
    this->setRelativePos(pos);

}

TextBox::TextBox(std::string text, text_align_t align, Vector2  pos){
    parseLines(text);
    this->align = align;
    this->setRelativePos(pos);
    this->size = {this->whithText, (float)this->text.size()};
    this->resize();

}

void TextBox::resize() {
    this->size.y = getHeightText();
    this->size.x = getWhithText();
}

void TextBox::setBackground(colors_enum color_) {
    this->color = color_;
}

void TextBox::setAlign(text_align_t textAlign) {
    this->align = textAlign;
}

std::string TextBox::getText() {
    return std::string();
}

void TextBox::setString(std::string text_) {
    parseLines(text_);
}

float TextBox::getHeightText() {
    return this->text.size()*PXL_STR_H;
}

float TextBox::getWhithText() {
    return whithText*PXL_STR;
}

void TextBox::render(){

    if(color != n_of_colors){
        CV::color(color);
        CV::rectFill({0.,0.}, size);
    }

    int line = 1;
    float align_vertical = (size.y - getHeightText())/2;
    CV::color(textColor);
    for (const auto &item: text){
        switch (align) {
            case center_center:{
                CV::text({
                    (size.x - item.length()*PXL_STR)/2,
                    line++*PXL_STR_H + align_vertical},
                         item);
                break;
            }
            default:{
                CV::text({0.,line++*PXL_STR_H}, item);
                break;
            }
        }
    }

};

void TextBox::parseLines(std::string string_) {

    std::istringstream iss(string_);
    std::string tmp;
    this->text.clear();//Reseta
    while (std::getline(iss, tmp)) {
        this->text.insert(this->text.begin(), tmp);
    }


    this->whithText = -1;

    for (const auto &item: this->text){
        if(item.length() > this->whithText){
            this->whithText = item.length();
        }
    }

}

void TextBox::setTextColor(colors_enum color) {
    this->textColor = color;
}
