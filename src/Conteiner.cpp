//
// Created by jvbrates on 3/27/24.
//

#include "Conteiner.h"

void Renderizable::render_caller() {
    CV::relative_translate(pos_relative);
    render();
    CV::relative_translate(pos_relative*-1);
}
