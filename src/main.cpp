/*
    Lista de Instruções:
    O usuário interage  com a aplicação usando somente o mouse,
    para atirar use o botão esquerdo, para rotacionar o canhão mova o mouse;

    Quesitos Implementados:
    Além dos critérios básicos de avaliação, foram implementados.
    - Outros tipos de primitivas, além de quadrados (0.5 pontos).
    - Menu incial (0.5 pontos).
    - Criação de várias fases do jogo (até 1 ponto). Muda-se de fase quando
    todos os quadrados são removidos.

*/


#include "gl_canvas2d.h"
#include "Frames.h"
#include "GUI.h"
#include "EventListener.h"
#include <string>

double  to_degres(double rad){
    return rad*180/M_PI;
}

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 505, screenHeight = 600;

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.
void CV_render() {

    Frames::updateFrames();
    float fps = Frames::getFrames();

    CV::text(Vector2(10.,10.),std::to_string(fps));

    for (Renderizable *item: CV::render_stack) {

        //Movido para reduzir o custo de processamento
        if(item->visible == false){
            continue;
        }

        CV::color(black);
        item->render_caller();
    }


}

int main(){


    GUI I = GUI();

    EventListener::captureEvent[en_mouse_left] = true;


    CV::render_stack.push_back(&I);


    CV::init(screenWidth, screenHeight, "T3_JOAO_VITOR_RATES");
    CV::run();


    return 0;
}
