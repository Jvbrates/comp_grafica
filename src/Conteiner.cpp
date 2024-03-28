//
// Created by jvbrates on 3/27/24.
//

#include "Conteiner.h"

void Renderizable::render_caller() {
    CV::relative_translate(posRelative);
    render();
    CV::relative_translate(posRelative * -1);
}

void Conteiner::composer(){
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

            elements[0]->posRelative = {0.,0};
            float max_x = elements[0]->size.x;
            float y_acm = 0;
            for (int i = 1; i < elements.size(); ++i) {
                y_acm += elements[i-1]->size.y;
                elements[i]->posRelative = {0.,y_acm};

                if(elements[i]->size.x > max_x)
                    max_x = elements[i]->size.x;
            }


            this->size = {max_x, y_acm + elements[elements.size()-1]->size.y};
            break;
        }
        case line: {

            elements[0]->posRelative = {0.,0};
            float max_y = elements[0]->size.y;

            float x_acm = 0;
            for (int i = 1; i < elements.size(); ++i) {
                x_acm += elements[i-1]->size.x;
                elements[i]->posRelative = {x_acm,0.};

                if(elements[i]->size.x > max_y)
                    max_y = elements[i]->size.y;
            }

            this->size = {x_acm+elements[elements.size()-1]->size.x, max_y};

            break;
        }
    }
}

void Conteiner::render() {
    for (auto &item: elements) {
        item->render_caller();
    }
}