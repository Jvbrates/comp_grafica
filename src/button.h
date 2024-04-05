//
// Created by jvbrates on 3/18/24.
//

#ifndef SRC_BUTTON_H
#define SRC_BUTTON_H
#include "Vector2.h"
#include "EventListener.h"
#include "gl_canvas2d.h"
#include "string"

typedef struct states{
    Vector2<float> position, size, text_offset;
    colors_enum fill_color = gray;
    std::string texto;
} states_t;


class Button: public EventClient, public Renderizable{


protected:
    std::vector<states_t>  state_array = std::vector<states_t>();
    int state = 0;
    std::function<bool(void *)> f_onclick;
    void * argument;

protected:
    bool mouse_left(int) override;
    bool callWraper();

public:
    bool active = false;
    explicit Button(states_t start_state);
    Button();

    void addState(states_t state);
    void setState(int state);
    int getState();
    void onclick(std::function<bool(void *)> f, void *argument);
    void setArgument(void * arg);
    void render() override;

};

class CheckboxButton: public Button{
protected:
    bool mouse_left(int) override;

public:
    CheckboxButton(float size, Vector2<float>pos, std::string label);
};

#endif //SRC_BUTTON_H
