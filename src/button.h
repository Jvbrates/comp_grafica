//
// Created by jvbrates on 3/18/24.
//

#ifndef SRC_BUTTON_H
#define SRC_BUTTON_H
#include "Vector2.h"
#include "EventListener.h"
#include "gl_canvas2d.h"
#include "string"


class button: public EventListener, public Renderizable{

private:
    Vector2<float> position, size, text_offset;
    colors_enum fill_color = gray;
    std::string texto;
    colors_enum text_color = gray;
public:
    button(Vector2<float> pos, Vector2<float>, colors_enum fill_color);
    void text(Vector2<float> offset, std::string texto, colors_enum color);
    void render() override;

};


#endif //SRC_BUTTON_H
