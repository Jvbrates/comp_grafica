//
// Created by jvbrates on 3/27/24.
//

#include "Conteiner.h"

void Renderizable::render_caller() {
    CV::relative_translate(pos_relative);
    render();
    CV::relative_translate(pos_relative * -1);
}

void Conteiner::render() {
    for (auto &item: elements) {
        item->render_caller();
    }
}