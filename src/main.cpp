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

#include <cstdio>
#include "iostream"

#include "gl_canvas2d.h"
#include "EventListener.h"
#include "ImageManagement.h"
#include "ImageSelector.h"
#include "Conteiner.h"

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 500, screenHeight = 500;



Image *imgAbstract, *imgAbstract2;


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
    switch(state_c){
        case 'r':
            imgAbstract->setColor(en_redscale);
            break;
        case 'g':
            imgAbstract->setColor(en_greenscale);
            break;
        case 'b':
            imgAbstract->setColor(en_bluescale);
            break;
        case 'u':
            imgAbstract->setRotation(imgAbstract->getRotation()+10);
            break;
        case 'j':
            imgAbstract->setRotation(imgAbstract->getRotation()-10);
            break;
        case '+':
            imgAbstract->setBrightnessMod(imgAbstract->getBrightnessMod()+5);
            break;
        case '-':
            imgAbstract->setBrightnessMod(imgAbstract->getBrightnessMod()-5);
            break;
        case '1':
            imgAbstract->setHorizontalFlip(true);
            break;
        case '2':
            imgAbstract->setHorizontalFlip(false);
            break;
        case '3':
            imgAbstract->setVerticalFlip(true);
            break;
        case '4':
            imgAbstract->setVerticalFlip(false);
            break;
        default:
            imgAbstract->setColor(en_rgb);
    }


    return false;

}



teste t_class = teste();



//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.
void CV_render()
{

    float x = 0.;
    for (Renderizable* item: CV::render_stack){

        CV::color(black);
        item->render_caller();
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


    ImageSelector Mng = ImageSelector();

    Mng.loadImage("./images/b.bmp", {0. ,100.});
    Mng.loadImage("./images/a.bmp", {50. ,200.});
    EventListener::add_event(&Mng,en_mouse_left);
    EventListener::add_event(&Mng,en_mouse_move);

    /*
    Bmp image = Bmp("./images/b.bmp");

    EventListener::add_event(&t_class, en_keyboard_up);
    image.convertBGRtoRGB();

    imgAbstract = new Image(image);


    //*imgAbstract2 = Image(*imgAbstract, en_greenscale);

    imgAbstract->grayChannel();
    Image img_gray(*imgAbstract, en_grayscale);
    Image img_red(*imgAbstract, en_redscale);
    Image img_green(*imgAbstract, en_greenscale);
    Image img_blue(*imgAbstract, en_bluescale);


    Conteiner conteiner = Conteiner();
    Conteiner conteiner2 = Conteiner();
    Conteiner conteiner3 = Conteiner();

    conteiner.elements = std::vector<Renderizable *>();
    conteiner2.elements = std::vector<Renderizable *>();
    conteiner3.elements = std::vector<Renderizable *>();

    conteiner.elements.push_back(imgAbstract);
    conteiner.elements.push_back(&img_gray);
    conteiner.elements.push_back(&img_red);

    conteiner2.elements.push_back(&img_green);
    conteiner2.elements.push_back(&img_blue);

    conteiner3.elements.push_back(&conteiner);
    conteiner3.elements.push_back(&conteiner2);

    conteiner.position_type = line;
    conteiner2.position_type = column;
    conteiner3.position_type = line;
    conteiner.composer();
    conteiner2.composer();
    conteiner3.composer();
*/

    CV::render_stack.push_back(&(Mng.images));

    CV::init(screenWidth, screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
    CV::run();



}
