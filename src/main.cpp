
#include <iosfwd>
#include <sstream>
#include <iomanip>

#include "gl_canvas2d.h"
#include "Frames.h"
#include "EventListener.h"
#include "image/ImageSelector.h"
#include "TextBox.h"
#include "image/Histogram.h"
#include "Conteiner.h"
#include "button.h"
#include "Blocks.h"

#include "geometry/Circle.h"
#include "geometry/Triangle.h"
#include "geometry/Polygon.h"
#include "geometry/SpecialSquare.h"


double  to_degres(double rad){
    return rad*180/M_PI;
}

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 600, screenHeight = 600;

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.
void CV_render() {

    Frames::updateFrames();
    for (Renderizable *item: CV::render_stack) {
        CV::color(black);
        item->render_caller();
    }
}


class Bullet: public Circle, public EventClient {
public:
    Vector2 move;

    using Circle::Circle;

    void render() override {
        //Desenhando o Circulo
        Circle::render();

        //Ignorando redimensionamento de FPS por enquanto

        //Desenha guias
        auto l1 = move.cpy();
        l1.setRay(this->getRay());

        CV::color(red);
        CV::line({0.,0.}, move);
        CV::color(green);
        CV::line({0.,0.}, l1);


        auto sup = l1.cpy();
        CV::color(blue);

        sup.setAngle(sup.getAngle()+M_PI/2);

        //auto sup_line = l1+sup;
        CV::line({0.,0.}, sup);
        CV::line(sup, sup+move+l1);


        CV::color(brown);
        auto inf = l1.cpy();
        inf.setAngle(inf.getAngle()-M_PI/2);

        //auto inf_line = l1+inf;
        CV::line({0.,0.}, inf);
        CV::line(inf, inf+move+l1);



        //Guide

        CV::circle(CV::getMouseRelative(), Circle::getRay(), vertex);



    }


    bool mouse_move(Vector2 pos, Vector2 displ) override{
        this->move = CV::get_mouse_pos() - this->getAbsolutePos();

        return false;
    }

};

typedef std::vector<Vector2> polign_t;

void draw_polign(polign_t p){
    std::cout << "Desenhando poligonos" << std::endl;
    CV::polygon(p);
}

std::vector<polign_t > vect_pol =std::vector<polign_t>();

void CV_render2(){
    CV::translate(300, 300);
    CV::line(-300, 0, 600, 0);
    CV::line(0, -300, 0, 600);


    colors_enum  color = static_cast<colors_enum>(0);
    CV::color(black);

    for (const auto &item: vect_pol){
        CV::color(color);
        color = static_cast<colors_enum>(((int) color + 1)%n_of_colors);
        draw_polign(item);
    }
}



void rotate(polign_t *p, double rad){
    for (auto &item: *p){
        item.setAngle(item.getAngle()+rad);

   /*     item.x = item.x*cos(rad) - item.y*sin(rad);
        item.y = item.y*cos(rad) + item.x*sin(rad);
*/
    }
}


void translate(polign_t *p, Vector2 pos){
    for (auto &item: *p){
        item += pos;
    }
}


void scale(polign_t *p, float scale){
    for (auto &item: *p){
        item.x *= scale;
        item.y *= scale;
    }
}

polign_t copy(polign_t src){
    auto poligono2 = polign_t();
    for (const auto &item: src){
        poligono2.push_back(item);
    }
    return poligono2;

}

class Segment: public Renderizable, public EventClient {
public:
    Vector2 direct;

    Segment(Vector2 src, Vector2 vec){
        this->setRelativePos(src);
        this->direct = vec;
    }


    void render() override{
        CV::line({0.,0.},direct);

        auto mouse_vec = CV::getMouseRelative();
        CV::line({0.,0.},mouse_vec);
        auto angle =  mouse_vec.getAngle(direct);

        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << angle*180/M_PI;
        std::string s = stream.str();

        CV::text(direct, s);


        auto proj = mouse_vec.projection(direct);

        CV::color(red);

        CV::line(Vector2{0.,0.}, proj);


        CV::line(Vector2{0.,0.} + mouse_vec, (mouse_vec).reflex(direct) + mouse_vec);
        CV::circle(mouse_vec, 10.f, 8);
    }
};

int main() {

    auto surface = Segment({400.,200.}, {-150.,300.});

    auto p1 = SpecialSquare(50., Vector2(100.,100.), 25.);
    p1.draw_collision = true;

    auto block = Blocks();
    CV::render_stack.push_back(&surface);
    CV::render_stack.push_back(&block.poligonos);
    CV::render_stack.push_back(&p1);
    //CV::render_stack.push_back(&p2);
    CV::init(screenWidth, screenHeight, "Canvas2D");
    CV::run();
}
