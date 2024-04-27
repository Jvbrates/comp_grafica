/*
 * Funcionalidades Implementadas:
 *  - Selecionar Imagens: Click com botão esquerdo do mouse
 *  - Arrastar Imagens: Mover mouse com botão esquerdo pressionado
 *  - Rotacionar Imagens: Mover mouse com botão direito pressionado
 *  - Gerar nova em imagem com canal de cores decomposto:
 *      No menu a direita clicar em um dos botões abaixo do título "Canais de Cores"
 *      R: Gerar imagem vermelho
 *      G: Gerar imagem verde
 *      B: Gerar imagem azul
 *      L: Gerar imagem em tons de luminância(ao longo do código foi usado a palavra
 *      grayscale)
 *  - Alterar brilho: Modifica a imagem selecionada ao interagir com o slider abaixo
 *  do título "Brilho:"
 *  - Visualizar histogramas: Interação com os checkbox na seção Histogramas
 *  - Espelhamento: Interação com os checkbox na seção Espelhamento
 *  - Mover "Câmera": Todas as imagens podem ser movidas conjuntamente pressionando
 *  as setas do teclado.
 *
 *
 *  Como requerido todo arquivo header possuí uma descrição, para um melhor
 *  entendimento do código sugere-se que sejam lidos na seguinte ordem
 *
 *  - gl_canvas2d.h (Descrito as modificações)
 *  - EventListener.h
 *  - collisions.h
 *  - Renderizable.h
 *  - Conteiner.h
 *  - ImageManagement.h
 *  - ImageSelector.h
 *  - Histogram.h
 *  - Button.h
 *  - TextBox.h
 *
 *  main.cpp
 *  - Instancia a classe que possuí as imagens (ImageSelector)
 *  - Cria o Menu e seus botões e define sua organização(posicionamento);
 *  - Cria os Histogramas e define sua organização
 *  - Confere interação com usuário e comunicação entre as partes
 *  Menu->Imagens, Menu->Histogramas;
 *
 *  A função render foi renomeada para CV_render a fim de evitar a colisão
 *  de nomes, ela será descrita em gl_canvas2d.h;
 *
 * */
#include <iosfwd>
#include <sstream>
#include <iomanip>

#include "gl_canvas2d.h"
#include "EventListener.h"
#include "image/ImageSelector.h"
#include "TextBox.h"
#include "image/Histogram.h"
#include "Conteiner.h"
#include "button.h"

#include "geometry/Circle.h"
#include "geometry/Triangle.h"


double  to_degres(double rad){
    return rad*180/M_PI;
}

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 600, screenHeight = 600;

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.
void CV_render() {
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

        CV::line({0.,0.}, proj);

    }
};

int main() {

    //auto canhao = Canon({10.,0.});

//
//    EventListener::add_event(&canhao, en_mouse_move);
//    EventListener::add_event(&canhao, en_mouse_left);
//    CV::render_stack.push_back(&canhao);
//    CV::render_stack.push_back(&canhao.bullets2);

    auto segmento = Segment({200,200}, {100,0});
    CV::render_stack.push_back(&segmento);
    auto segmento2 = Segment({200,200}, {100,100});
    auto segmento3 = Segment({200,200}, {0,100});
    auto segmento4 = Segment({200,200}, {100,-100});
    auto segmento5 = Segment({200,200}, {-100,100});
    auto segmento6 = Segment({200,200}, {-100,-100});
    auto segmento7 = Segment({200,200}, {0,-100});
    auto segmento8 = Segment({200,200}, {-100,0});
    //segmento2.color = red;
    CV::render_stack.push_back(&segmento);
    CV::render_stack.push_back(&segmento2);
    CV::render_stack.push_back(&segmento3);
    CV::render_stack.push_back(&segmento4);
    CV::render_stack.push_back(&segmento5);
    CV::render_stack.push_back(&segmento6);
    CV::render_stack.push_back(&segmento7);
    CV::render_stack.push_back(&segmento8);


    //std::vector<Vector2>pontos = {Vector2{300.,300.}, Vector2{0.,0.}, Vector2{300.,0.}};


    //auto P = Polygon_(pontos);
    //P.setRelativePos(300.,300.);

//
//    auto bullet = Bullet(80., 20, black, true);
//    bullet.move = {100.,100.};
//    bullet.setRelativePos({200., 200.});
//
//    EventListener::add_event(&bullet, en_mouse_move);
//
    //INIT
   // CV::render_stack.push_back(&P);
   // CV::render_stack.push_back(&bullet);


    CV::init(screenWidth, screenHeight, "Canvas2D");
    CV::run();
}
