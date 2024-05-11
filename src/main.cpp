
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
#include "SpecialSquare.h"


double  to_degres(double rad){
    return rad*180/M_PI;
}

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 505, screenHeight = 600;

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.
void CV_render() {
    CV::rect(Vector2(20.,20.), Vector2(120.,120.));

    Frames::updateFrames();



    for (Renderizable *item: CV::render_stack) {
        CV::color(black);
        item->render_caller();
    }

    CV::color(idk_1);
    CV::line(Vector2{50.,50.}, Vector2{100.,100.});
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
       CV::line(Vector2(50.,50.), Vector2(150., 150.));
       CV::circle(Vector2(50.,50.), 25., 8);
       CV::circle(Vector2(150.,150.), 25., 8);


    }
};

class Teste : public Renderizable{
    public:
        Vector2 from, to;
    void render() override{
        CV::color(green);
        CV::line(from, to);
       //CV::circle(Vector2(50.,50.), 25., 8);
       CV::circle(to, 25., 8);

    }
    };

#include "collisions.h"
#include "Game.h"
int main(){

    Game G = Game();

    CV::render_stack.push_back(&G);
    CV::render_stack.push_back(&(G.blocks.poligonos));
    CV::render_stack.push_back(&(G.cannon));

    EventListener::add_event(&G, en_mouse_move);
    EventListener::add_event(&G, en_mouse_left);

    CV::init(screenWidth, screenHeight, "Canvas2D");
    CV::run();


    return 0;
}

int main2() {

    solution_rect_rect sol = collisions::rect_rect(Vector2(0.,1.), Vector2(4.,-2.),Vector2(2.,2.), Vector2(1.,1.));
    std::cout << sol.status << std::endl;
    std::cout << sol.varA << std::endl;
    std::cout << sol.varB << std::endl;


    auto surface = Segment({0.,0.}, {150.,300.});

    auto p1 = SpecialSquare(50., Vector2(0.,0.), 25.);
    p1.draw_collision = true;
    p1.setColor(black);

    Blocks block = Blocks();
    block.poligonos.setRelativePos(20.,20.);

    std::vector<Vector2> points = std::vector<Vector2>();

    data_moveCircle dt = block.moveCircle(Vector2{50.,50.}, Vector2{100.,100.}, 25, &points);

    auto p = Polygon_(points);

    std::cout << dt.collision << std::endl;
    std::cout << dt.pos_final.x << std::endl;
    std::cout << dt.pos_final.y << std::endl;

    auto teste = Teste();
    teste.to = dt.pos_final;
    teste.from = Vector2(50.,50.);

    p.setColor(red);

    CV::render_stack.push_back(&p);
    CV::render_stack.push_back(&surface);
    CV::render_stack.push_back(&block.poligonos);
    CV::render_stack.push_back(&teste);


    CV::init(screenWidth, screenHeight, "Canvas2D");
    CV::run();
}
