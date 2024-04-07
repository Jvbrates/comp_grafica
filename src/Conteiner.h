//
// Created by jvbrates on 3/27/24.
//

#ifndef COMP_GRAFICA_CONTEINER_H
#define COMP_GRAFICA_CONTEINER_H
#include "gl_canvas2d.h"
#include <vector>
#include <memory>
#include "EventListener.h"
#include "Vector2.h"
typedef enum {relative, line, column}position_enum;


class Renderizable {

private:
    friend void CV_render();
    friend class Conteiner;

    Vector2<float> posAbsoluteSuper = {0.,0.};
    Vector2<float> posRelative {0., 0.};

public:
    Vector2<float> size {0.,0.};
    int priority = 0;
    bool visible = true;
    virtual void render() = 0;
    Vector2<float> getAbsolutePos();
    Vector2<float> getRelativePos();
    virtual void setRelativePos(Vector2<float> pos);
    virtual void setRelativePos(float x, float y);

private:

    virtual void render_caller() final;
};



class Conteiner : public Renderizable, public EventClient {
    colors_enum color = black;
public:
    void backgroundColor(colors_enum);
    void render() override;
    std::vector<std::shared_ptr<Renderizable>> elements;
    position_enum position_type = relative;
    bool visible = false;
    void composer();
    void push(std::shared_ptr<Renderizable> item);
    void findRemove(std::shared_ptr<Renderizable> item);
    void pop();
    std::shared_ptr<Renderizable> lastElement();
    void updateElementsPos();
    void setRelativePos(Vector2<float> pos) override;
    void setRelativePos(float x, float y) override;
    ~Conteiner();


    //Evitar clicks por detrás do conteiner; ISSUE #8
    bool mouse_left(int state);
    bool mouse_right(int state);


};


#endif //COMP_GRAFICA_CONTEINER_H
