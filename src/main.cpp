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

#include "gl_canvas2d.h"
#include "EventListener.h"
#include "image/ImageSelector.h"
#include "TextBox.h"
#include "image/Histogram.h"
#include "Conteiner.h"
#include "button.h"

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 1200, screenHeight = 700;

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.
void CV_render() {
    for (Renderizable *item: CV::render_stack) {
        CV::color(black);
        item->render_caller();
    }
}


class Circle: public Renderizable {
public:
    Vector2 move, position;
    float velocidade = 1., raio = 10.f;
    int polygns = 10;

    void render() override{

        this->position =
                position +
                move*velocidade
                ;


        if(this->position.x > screenWidth or this->position.x < 0){
            move.x = -1*move.x;
        }


        if(this->position.y > screenHeight or this->position.y < 0){
            move.y = -1*move.y;
        }


        CV::circleFill(this->position, raio, polygns);

    }


    explicit Circle(Vector2 direction, Vector2 position_){
        this->move = direction;
        this->position = position_;
    }


};

class Canon : public Renderizable, public EventClient {

public:
    Conteiner bullets2;

    std::vector<Circle> bullets = std::vector<Circle>();


    explicit Canon(Vector2 mira_) {
        this->mira = mira_;
        this->base = {100., 100.};
    }

    Vector2 mira, base = {100., 100.};


    void render() override {
        CV::color(green);
        CV::line(base, CV::get_mouse_pos());
        CV::color(red);
        CV::line(base, base+mira);

    }

    bool mouse_move(Vector2 pos, Vector2 desloc) override {
        auto base_pos = pos-base;
        double angle = base_pos.getAngle();
        CV::line(base, pos);


        if(pos.y < base.y){
            angle = angle*-1;
        }

      /*  if(base_pos.x*pos.y < base_pos.y*pos.x) {
            angle = angle;
        } else {
            angle = angle*-1;
        }
*/

        mira.setAngle(angle);
        return false;
    }


    bool mouse_left(int state) override{
        if(state == 1){

            auto direction = polarVec(10.f, this->mira.getAngle());

            if(CV::get_mouse_pos().y < base.y){
                direction.y = direction.y*-1;
            }

            auto position = Vector2(base+mira);

            auto bullet = std::make_shared<Circle>(direction, position);

            this->bullets2.push(bullet);

        }
        return false;
    }


};

class Engrenagem : public Renderizable {

    double rotate_acm = 0.;
public:
    double rotate_step = 0.02;
    double periods;
    std::vector<Vector2> points;

    explicit Engrenagem(std::vector<Vector2> points_) {
        this->points = points_;
        this->periods = points_[points_.size() - 1].getAngle() - points_[0].getAngle();

    }

    void render() override {
        rotate_acm += rotate_step;
        auto points_cpy = points;


        for (int i = 0; i <= PI_2 / (periods) + 1; i++) {

            CV::color(black);

            for (int j = 0; j < points.size() - 2; ++j) {

                points_cpy[j].setAngle(points[j].getAngle() + i * periods + rotate_acm);
                points_cpy[j + 1].setAngle(points[j + 1].getAngle() + i * periods + rotate_acm);

                CV::line(points_cpy[j], points_cpy[j + 1]);
            }

            auto last = points.size() - 1;

            CV::color(red);
            points_cpy[last].setAngle(points[last].getAngle() + i * periods + rotate_acm);
            points_cpy[0].setAngle(points[0].getAngle() + (i + 1) * periods + rotate_acm);
            CV::line(points_cpy[last], points_cpy[0]);


            /*CV::color(green);
            points_cpy[0].setAngle(points[0].getAngle() + periods*i);
            CV::line(points_cpy[3], points_cpy[0]);*/



        }

    }

};


class Lock {

public:
    Lock(){
        std:: cout << "Locked ";
    }

    ~Lock(){
        std::cout << "Unlocked " << std::endl;
    }

};

int main() {

    auto canhao = Canon({10.,0.});


    EventListener::add_event(&canhao, en_mouse_move);
    EventListener::add_event(&canhao, en_mouse_left);
    CV::render_stack.push_back(&canhao);
    CV::render_stack.push_back(&canhao.bullets2);

    //INIT
    CV::init(screenWidth, screenHeight, "Canvas2D");
    CV::run();

    {
        auto hold = Lock();

        std::cout << "Doing something ";

    }



}

