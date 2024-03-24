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
#include "ImageManagement.h"
#include "button.h"
#include "unistd.h"

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 500, screenHeight = 500;


auto image = Bmp("./images/exodia4.bmp");
Image *imgAbstract;


class teste : public EventClient{

public:
    colors_enum color;


    bool key_press(int state) override;

    bool key_up(int state) override;
};

int i;


bool teste::key_press(int state) {
    printf("AAAA");
    this->color = gray;
    return false;
}

bool teste::key_up(int state) {
    printf("%c\n", state);

    auto state_c = (char)state;

    if(state_c == 'r'){
        imgAbstract->setColor(en_redscale);
    } else if (state_c == 'g'){
        imgAbstract->setColor(en_greenscale);
    } else if (state_c == 'b') {
        imgAbstract->setColor(en_bluescale);
    } else if (state_c == 'u'){
        imgAbstract->setRotation(imgAbstract->getRotation()+10);
    } else if (state_c == 'j'){
        imgAbstract->setRotation(imgAbstract->getRotation()-10);
    } else {
        imgAbstract->setColor(en_rgb);
    }

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


   // Usando Image
/*   std::shared_ptr<color_data_t>green_channel  = imgAbstract->get_channel_pointer(en_greenscale);
   std::shared_ptr<color_data_t>red_channel  = imgAbstract->get_channel_pointer(en_redscale);
   std::shared_ptr<color_data_t>blue_channel  = imgAbstract->get_channel_pointer(en_bluescale);

    uint bytes_line = imgAbstract->getBytesPerLyne();

    for (uint y=imgAbstract->getHeight(); y>0; y--){
        for (int x = 0; x < imgAbstract->getWidth(); ++x){

            CV::color(255,green_channel->pixels[x+y*imgAbstract->getWidth()], 255);
            CV::point(x,y);
        }

    }*/

}


int main(void)
{

    /*auto btn = button({50.,50.},{100.,50.}, red);
    btn.text({0.,0.}, "Texto", black);

   CV::render_stack.push_back(&btn);

    */

    EventListener::add_event(&t_class, en_keyboard_up);
    image.convertBGRtoRGB();

    imgAbstract = new Image(image);

    CV::render_stack.push_back(imgAbstract);

    CV::init(screenWidth, screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
   CV::run();



}
