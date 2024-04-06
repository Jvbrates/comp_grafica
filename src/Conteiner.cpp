//
// Created by jvbrates on 3/27/24.
//

#include "Conteiner.h"




void Renderizable::render_caller() {
    CV::relative_translate(posRelative);
    if(visible) {
        render();
    }
    CV::relative_translate(posRelative * -1);
}

void Conteiner::composer(){

    if(elements.size() == 0) return;


    switch (this->position_type) {
        case relative: {

            float max_x = elements[0]->size.x;
            float max_y = elements[0]->size.y;

            for (int i = 1; i < elements.size(); ++i) {
                if(elements[i]->size.x > max_x)
                    max_x = elements[i]->size.x;
                if(elements[i]->size.x > max_y)
                    max_y = elements[i]->size.y;

            }
            this->size = {max_x, max_y};


            break;
        }
        case column: {

            if(elements.size() == 0) return;


            elements[0]->setRelativePos(0.,0.);
            float max_x = elements[0]->size.x;
            float y_acm = 0;
            for (int i = 1; i < elements.size(); ++i) {
                y_acm += elements[i-1]->size.y;
                elements[i]->setRelativePos({0.,y_acm});

                if(elements[i]->size.x > max_x)
                    max_x = elements[i]->size.x;
            }


            this->size = {max_x, y_acm + elements[elements.size()-1]->size.y};
            break;
        }
        case line: {

            if(elements.size() == 0) return;

            elements[0]->setRelativePos(0.,0);
            float max_y = elements[0]->size.y;

            float x_acm = 0;
            for (int i = 1; i < elements.size(); ++i) {
                x_acm += elements[i-1]->size.x;
                elements[i]->setRelativePos(x_acm,0.);

                if(elements[i]->size.x > max_y)
                    max_y = elements[i]->size.y;
            }

            this->size = {x_acm+elements[elements.size()-1]->size.x, max_y};

            break;
        }
    }
}

void Conteiner::render() {
    if(visible) {
        CV::color(color);
        CV::rectFill({0.,0.}, this->size);
    }

    for (auto &item: elements) {
        item->render_caller();
    }
}


Vector2<float> Renderizable::getAbsolutePos() {
    return this->posRelative + this->posAbsoluteSuper;
}

Vector2<float> Renderizable::getRelativePos() {
    return this->posRelative;
}


void Conteiner::push(std::shared_ptr<Renderizable> item) {
    this->elements.push_back(item);
    item->posAbsoluteSuper = this->getAbsolutePos();
}


void Conteiner::pop() {
    auto ultimo = this->elements[this->elements.size() -1];
    ultimo->posAbsoluteSuper = {0.,0.};
    this->elements.pop_back();

}

void Conteiner::findRemove(std::shared_ptr<Renderizable> item) {
    auto item_find = std::find(this->elements.begin(), this->elements.end(), item);

    if(item_find != this->elements.end()) {
        (*item_find)->posAbsoluteSuper = {0.,0.};
        this->elements.erase(item_find);
    }
}

std::shared_ptr<Renderizable> Conteiner::lastElement() {
    if(this->elements.size()) {
        return elements[elements.size() - 1];
    }
}

Conteiner::~Conteiner() {
    for (auto &item: elements){
        item->posAbsoluteSuper = {0.,0.};
    }
}


void Renderizable::setRelativePos(Vector2<float> pos) {
    this->posRelative = pos;

}

void Renderizable::setRelativePos(float x, float y) {
    this->posRelative = Vector2<float>(x,y);

}

void Conteiner::setRelativePos(float x, float y) {
    this->posRelative = Vector2<float>{x,y};
    updateElementsPos();
}

void Conteiner::updateElementsPos(){
    for (auto &item: this->elements){
        item->posAbsoluteSuper = this->getAbsolutePos();

        auto sla_oq_e_isso = std::dynamic_pointer_cast<Conteiner>(item);
        if(sla_oq_e_isso){
            sla_oq_e_isso->updateElementsPos();
        }
    }
}

void Conteiner::setRelativePos(Vector2<float> pos) {
    this->posRelative = pos;
    updateElementsPos();
}

void Conteiner::backgroundColor(colors_enum c) {
    this->color = c;
}

