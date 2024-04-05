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
#include "Histogram.h"
#include "Conteiner.h"
#include "button.h"

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 1200, screenHeight = 700;



Image *imgAbstract, *imgAbstract2;


class teste : public EventClient{

    Renderizable * hist;
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
        case 'h':
            hist = CV::render_stack[CV::render_stack.size()-1];
            CV::render_stack.pop_back();
            break;
        case 'y':
            CV::render_stack.push_back(hist);
            break;
        default:
            break;

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

    CV::line(50,50, 510,50);
    CV::line(50,150, 51210,150);



}



int main(void)
{

    std::shared_ptr<Image> a = nullptr;

    // Agrupa todas as imagens carregadas, permine move-las e selecioná-las
    ImageSelector Mng = ImageSelector(&a);

    //Carrega as Três imagens iniciais
    Mng.loadImage("./images/a.bmp", {50. ,200.});
    Mng.loadImage("./images/b.bmp", {0. ,100.});
    Mng.loadImage("./images/c.bmp", {0. ,100.});

    //Eventos que serão esperados pela classe Mng
    EventListener::add_event(&Mng,en_mouse_left);
    EventListener::add_event(&Mng,en_mouse_move);
    EventListener::add_event(&Mng,en_keyboard_down);

    teste t = teste();
    EventListener::add_event(&t,en_keyboard_up);

    //Mng.updateQuadri();


    //Botoes de decomposição de Canal
    // 1 - Instancia os Botões
    auto dec_R = std::make_shared<Button>((states_t){{10.,0},{50.,50},{10.,45},gray,"R"});
    auto dec_G = std::make_shared<Button>((states_t){{10.,0},{50.,50},{10.,45},gray,"G"});
    auto dec_B = std::make_shared<Button>((states_t){{10.,0},{50.,50},{10.,45},gray,"B"});
    auto dec_L = std::make_shared<Button>((states_t){{10.,0},{50.,50},{10.,45},gray,"L"});

    // 2- Define Ação de cada botão
    dec_R->onclick([&Mng](void * arg){

        auto image = Mng.getSelected();

        if(image->getColor() == en_rgb){
            Mng.loadImage(*image, en_redscale, image->getRelativePos() + Vector2<float>{50.,50.});
        }


       return true;
    }, nullptr);
    dec_G->onclick([&Mng](void * arg){

        auto image = Mng.getSelected();

        if(image->getColor() == en_rgb){
            Mng.loadImage(*image, en_greenscale, image->getRelativePos() + Vector2<float>{50.,50.});
        }


        return true;
    }, nullptr);
    dec_B->onclick([&Mng](void * arg){

        auto image = Mng.getSelected();

        if(image->getColor() == en_rgb){
            Mng.loadImage(*image, en_bluescale, image->getRelativePos() + Vector2<float>{50.,50.});
        }


        return true;
    }, nullptr);
    dec_L->onclick([&Mng](void * arg){

        auto image = Mng.getSelected();

        if(image->getColor() == en_rgb){
            if(image->get_channel_pointer(en_grayscale) == nullptr){
                image->grayChannel();
            }

            //Isto daqui gera um objeto cópia e como cópia não define o grayscale ele acaba ficando nulo
            auto a = *image;

            Mng.loadImage(a, en_grayscale, image->getRelativePos() + Vector2<float>{50.,50.});
        }


        return true;
    }, nullptr);

    //conteiner que conterá botões
    auto conteiner_btn_decomposicao = Conteiner();
    conteiner_btn_decomposicao.elements.push_back(dec_R);
    conteiner_btn_decomposicao.elements.push_back(dec_G);
    conteiner_btn_decomposicao.elements.push_back(dec_B);
    conteiner_btn_decomposicao.elements.push_back(dec_L);
    dec_R->active = true;
    dec_G->active = true;
    dec_B->active = true;
    dec_L->active = true;

    conteiner_btn_decomposicao.position_type = line;
    conteiner_btn_decomposicao.composer();
    conteiner_btn_decomposicao.setRelativePos(50.,50.);


    // Histogramas e Botões de Histogramas
    auto selectedImage = Mng.getSelected();
    auto histRed   = std::make_shared<HistogramRender>(a->get_channel_pointer(en_redscale),   en_redscale);
    auto histGreen = std::make_shared<HistogramRender>(a->get_channel_pointer(en_bluescale),  en_bluescale);
    auto histBlue  = std::make_shared<HistogramRender>(a->get_channel_pointer(en_greenscale), en_greenscale);
    auto histGray  = std::make_shared<HistogramRender>(a->get_channel_pointer(en_grayscale),  en_grayscale);

    // Conteiner de Histogramas
    auto conteiner_hist = Conteiner();
    conteiner_hist.elements.push_back(histRed);
    conteiner_hist.elements.push_back(histBlue);
    conteiner_hist.elements.push_back(histGreen);
    conteiner_hist.elements.push_back(histGray);

    conteiner_hist.position_type = column;
    conteiner_hist.composer();

    conteiner_hist.elements.clear();

    conteiner_hist.setRelativePos({(float)screenWidth-histGray->size.x, 6.});

    //Atualização dos Histogramas para apontar para imagem correta
    Mng.setCallback([&histRed,&histGreen,&histBlue,&histGray](auto image){
        histRed->reset(image->get_channel_pointer(en_redscale), en_redscale);
        histGreen->reset(image->get_channel_pointer(en_greenscale), en_greenscale);
        histBlue->reset(image->get_channel_pointer(en_bluescale), en_bluescale);
        histGray->reset(image->get_channel_pointer(en_grayscale), en_grayscale);
    });


    //Criação checkbox Histogramas
    std::shared_ptr<CheckboxButton> btn_hist_red = std::make_shared<CheckboxButton>(20., Vector2<float>{20.,200.}, "R:");

    btn_hist_red->onclick([histRed, &btn_hist_red, &conteiner_hist](void * a){
        if(btn_hist_red->getState() == 1){
            conteiner_hist.elements.push_back(histRed);
        } else {
            auto hist_vector = conteiner_hist.elements;
            auto index = std::find(hist_vector.begin(), hist_vector.end(), histRed);
            conteiner_hist.elements.erase(index);
        }

        return true;
    }, nullptr);
    btn_hist_red->active = true;


    CV::render_stack.push_back(&(Mng.images));
    CV::render_stack.push_back(&conteiner_btn_decomposicao);
    CV::render_stack.push_back(&conteiner_hist);
    CV::render_stack.push_back(&(*btn_hist_red));



    CV::init(screenWidth, screenHeight, "Canvas2D");
    CV::run();



}

