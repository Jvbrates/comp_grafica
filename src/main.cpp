/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2024
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instru��es:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/


#include <cmath>
#include <cstdio>
#include "iostream"

#include "gl_canvas2d.h"
#include "EventListener.h"
#include "button.h"

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 500, screenHeight = 500;

class teste : public EventClient{

public:
    colors_enum color;


    bool key_press(int state) override;

    bool key_up(int state) override;
};

bool teste::key_press(int state) {
    std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAA";
    this->color = gray;
    return false;
}

bool teste::key_up(int state) {
    color = yellow;
    return false;

}



teste t_class = teste();





//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.
void render()
{
    for (Renderizable* item: CV::render_stack){
        CV::translate(0,0);
        CV::color(black);
        item->render();
    }

}

int main(void)
{

    auto btn = button({50.,50.},{100.,50.}, red);
    btn.text({0.,0.}, "Texto", black);

   CV::render_stack.push_back(&btn);

   CV::init(screenWidth, screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");

   CV::run();



}
