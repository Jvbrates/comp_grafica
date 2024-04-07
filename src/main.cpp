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


#include "gl_canvas2d.h"
#include "EventListener.h"
#include "ImageSelector.h"
#include "TextBox.h"
#include "Histogram.h"
#include "Conteiner.h"
#include "button.h"

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 1200, screenHeight = 700;


//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.
void CV_render()
{
    for (Renderizable* item: CV::render_stack){
        CV::color(black);
        item->render_caller();
    }


}


int main()
{
    
    //Botão slider de brilho
    

    EventListener::captureEvent[en_mouse_move] = true;
    // Agrupa todas as imagens carregadas, permine move-las e selecioná-las
    ImageSelector Mng = ImageSelector();

    //Carrega as Três imagens iniciais
    Mng.loadImage("./images/a.bmp", {50. ,200.});
    Mng.loadImage("./images/b.bmp", {0. ,100.});
    Mng.loadImage("./images/c.bmp", {0. ,300.});





    //DECOMPOSICAO DE CANAL

    // 0 - Titulos

    auto decomposicao_text =std::make_shared<TextBox>("Canais de Cores", center_center,
                                                      Vector2<float>{0.,0.}, Vector2<float>{200., 2*PXL_STR_H});
    decomposicao_text->setBackground(black);
    decomposicao_text->setTextColor(green);

    auto brigthness_text =std::make_shared<TextBox>("Brilho:", center_center,
                                                      Vector2<float>{0.,0.}, Vector2<float>{200., 2*PXL_STR_H});
    brigthness_text->setBackground(black);
    brigthness_text->setTextColor(green);

    auto hisogram_text =std::make_shared<TextBox>("Histogramas", center_center,
                                                      Vector2<float>{0.,0.}, Vector2<float>{200., 2*PXL_STR_H});
    hisogram_text->setBackground(black);
    hisogram_text->setTextColor(green);

    auto flip_text =std::make_shared<TextBox>("Espelhamento ", center_center,
                                                  Vector2<float>{0.,0.}, Vector2<float>{200., 2*PXL_STR_H});
    flip_text->setBackground(black);
    flip_text->setTextColor(green);


    auto spacing0 =std::make_shared<TextBox>("--------------------", center_center,
                                                      Vector2<float>{0.,0.}, Vector2<float>{200., 2*PXL_STR_H});
    spacing0->setBackground(black);
    spacing0->setTextColor(white);
    auto spacing1 =std::make_shared<TextBox>("--------------------", center_center,
                                                      Vector2<float>{0.,0.}, Vector2<float>{200., 2*PXL_STR_H});
    spacing1->setBackground(black);
    spacing1->setTextColor(white);

    auto spacing2 =std::make_shared<TextBox>("--------------------", center_center,
                                             Vector2<float>{0.,0.}, Vector2<float>{200., 2*PXL_STR_H});
    spacing2->setBackground(black);
    spacing2->setTextColor(white);

    auto spacing3 =std::make_shared<TextBox>("--------------------", center_center,
                                             Vector2<float>{0.,0.}, Vector2<float>{200., 2*PXL_STR_H});
    spacing3->setBackground(black);
    spacing3->setTextColor(white);


    // Botoes Canais de Cores
    // 1.1 - Instancia os Botões
    auto dec_R = std::make_shared<Button>((states_t){{10.,0},{50.,50},{10.,45},black, red, "R"});
    auto dec_G = std::make_shared<Button>((states_t){{10.,0},{50.,50},{10.,45},black,green,"G"});
    auto dec_B = std::make_shared<Button>((states_t){{10.,0},{50.,50},{10.,45},black, blue,"B"});
    auto dec_L = std::make_shared<Button>((states_t){{10.,0},{50.,50},{10.,45},black,white,"L"});

    // 1.2- Define Ação de cada botão
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

    
    
    // 1.3- Organiza os botões em um conteiner/grid  1x4
    auto conteiner_btn_decomposicao = std::make_shared<Conteiner>();
    conteiner_btn_decomposicao->elements.push_back(dec_R);
    conteiner_btn_decomposicao->elements.push_back(dec_G);
    conteiner_btn_decomposicao->elements.push_back(dec_B);
    conteiner_btn_decomposicao->elements.push_back(dec_L);
    dec_R->active = true;
    dec_G->active = true;
    dec_B->active = true;
    dec_L->active = true;

    conteiner_btn_decomposicao->position_type = line;
    conteiner_btn_decomposicao->composer();

    // Controle de Brilho

    //1.0 Instância do slider
    auto brightness_slider = std::make_shared<SliderRangeButton>(200, white, green);
    
    //1.1Define ação do botão slider
    brightness_slider->onclick([&brightness_slider, &Mng](void *inutil){
        auto valor = brightness_slider->getValue();
        auto Imagem = Mng.getSelected();

        valor = 255/SliderRangeButton::MAX_VALUE * valor;
        Imagem->setBrightnessMod((int)valor);

        return false;
    }, nullptr);
    brightness_slider->active = true;


    //HISTOGRAMAS

    // 2.0 InstânciaHistogramas e Botões de Histogramas
    auto selectedImage = Mng.getSelected();
    auto histRed   = std::make_shared<HistogramRender>(selectedImage->get_channel_pointer(en_redscale),   en_redscale);
    auto histGreen = std::make_shared<HistogramRender>(selectedImage->get_channel_pointer(en_bluescale),  en_bluescale);
    auto histBlue  = std::make_shared<HistogramRender>(selectedImage->get_channel_pointer(en_greenscale), en_greenscale);
    auto histGray  = std::make_shared<HistogramRender>(selectedImage->get_channel_pointer(en_grayscale),  en_grayscale);
    

    // Histogramas iniciam-se invisiveis
    histGray->visible = histBlue->visible = histGreen->visible = histRed->visible = false;

    // 2.1 Conteiner/Grid de Histogramas 4x1
    auto conteiner_hist = Conteiner();
    conteiner_hist.elements.push_back(histRed);
    conteiner_hist.elements.push_back(histBlue);
    conteiner_hist.elements.push_back(histGreen);
    conteiner_hist.elements.push_back(histGray);
    conteiner_hist.position_type = column;
    conteiner_hist.composer();


    //Posiciona-os a direita
    conteiner_hist.setRelativePos({(float)screenWidth-histGray->size.x, 6.});



    //2.2 Criação checkbox Histogramas
    std::shared_ptr<CheckboxButton> btn_hist_red = std::make_shared<CheckboxButton>(20., Vector2<float>{20.,200.}, "R:");
    std::shared_ptr<CheckboxButton> btn_hist_green = std::make_shared<CheckboxButton>(20., Vector2<float>{20.,200.}, "G:");
    std::shared_ptr<CheckboxButton> btn_hist_blue = std::make_shared<CheckboxButton>(20., Vector2<float>{20.,200.}, "B:");
    std::shared_ptr<CheckboxButton> btn_hist_gray = std::make_shared<CheckboxButton>(20., Vector2<float>{20.,200.}, "L:");

    // 2.3 Definição da acção dos checkbox
    btn_hist_red->onclick([&histRed, &btn_hist_red](void * a){
        if(btn_hist_red->getState() == 1){
            histRed->visible = true;
        } else {
            histRed->visible = false;
        }

        return true;
    }, nullptr);
    btn_hist_green->onclick([&histGreen, &btn_hist_green](void * a){
        if(btn_hist_green->getState() == 1){
            histGreen->visible = true;
        } else {
            histGreen->visible = false;
        }

        return true;
    }, nullptr);
    btn_hist_blue->onclick([&histBlue, &btn_hist_blue](void * a){
        if(btn_hist_blue->getState() == 1){
            histBlue->visible = true;
        } else {
            histBlue->visible = false;
        }

        return true;
    }, nullptr);
    btn_hist_gray->onclick([&histGray, &btn_hist_gray](void * a){
        if(btn_hist_gray->getState() == 1){
            histGray->visible = true;
        } else {
            histGray->visible = false;
        }

        return true;
    }, nullptr);

    btn_hist_red->active = true;
    btn_hist_green->active = true;
    btn_hist_blue->active = true;
    btn_hist_gray->active = true;

    //2.4 Criando conteiner de Checkbox 2x2

    auto conteiner_check_l1 = std::make_shared<Conteiner>();
    auto conteiner_check_l2 = std::make_shared<Conteiner>();
    auto conteiner_check_hist = std::make_shared<Conteiner>();

    conteiner_check_l1->push(btn_hist_red);
    conteiner_check_l1->push(btn_hist_green);
    conteiner_check_l1->position_type = line;
    conteiner_check_l1->composer();

    conteiner_check_l2->push(btn_hist_blue);
    conteiner_check_l2->push(btn_hist_gray);
    conteiner_check_l2->position_type = line;
    conteiner_check_l2->composer();

    conteiner_check_hist->push(conteiner_check_l1);
    conteiner_check_hist->push(conteiner_check_l2);
    conteiner_check_hist->position_type = column;
    conteiner_check_hist->composer();


    // Espelhamento
    //3.0 Criando botoes Checkbox
    std::shared_ptr<CheckboxButton> flip_vertical_check = std::make_shared<CheckboxButton>(20., Vector2<float>{20.,200.}, "Vertical:  ");
    std::shared_ptr<CheckboxButton> flip_horizontal_check = std::make_shared<CheckboxButton>(20., Vector2<float>{20.,200.}, "Horizontal:");
    flip_horizontal_check->active = true;
    flip_vertical_check->active = true;

    //Definindo acao botoes checkbox
    flip_horizontal_check->onclick([&Mng, &flip_horizontal_check](void *any){
        auto seleted = Mng.getSelected();

        if(flip_horizontal_check->getState()){
            seleted->setHorizontalFlip(true);
        } else {
            seleted->setHorizontalFlip(false);
        }

        return false;

    }, nullptr);
    flip_vertical_check->onclick([&Mng, &flip_vertical_check](void *any){
        auto seleted = Mng.getSelected();

        if(flip_vertical_check->getState()){
            seleted->setVerticalFlip(true);
        } else {
            seleted->setVerticalFlip(false);
        }

        return false;

    }, nullptr);


    //Atualização dos Histogramas para apontar para imagem correta
    //Atualização do Slider de brilho para receber o valor correto
    //Atualização do Flip/espelhamento de brilho para receber o valor correto

    Mng.setCallback([&histRed,&histGreen,&histBlue,&histGray, &brightness_slider, &flip_vertical_check, &flip_horizontal_check]
    (auto image){

        histRed->reset(image->get_channel_pointer(en_redscale), en_redscale);
        histGreen->reset(image->get_channel_pointer(en_greenscale), en_greenscale);
        histBlue->reset(image->get_channel_pointer(en_bluescale), en_bluescale);
        histGray->reset(image->get_channel_pointer(en_grayscale), en_grayscale);

        brightness_slider->setValue(SliderRangeButton::convert(image->getBrightnessMod(), 255.f));
        flip_vertical_check->setState(image->getVerticalFlip());
        flip_horizontal_check->setState(image->getHorizontalFlip());

    });



    // Agrupando Menu
    auto Menu = Conteiner();
    Menu.push(decomposicao_text);
    Menu.push(conteiner_btn_decomposicao);
    Menu.push(spacing0);
    Menu.push(brigthness_text);
    Menu.push(brightness_slider);
    Menu.push(spacing1);
    Menu.push(hisogram_text);
    Menu.push(conteiner_check_hist);
    Menu.push(spacing2);
    Menu.push(flip_text);
    Menu.push(flip_horizontal_check);
    Menu.push(flip_vertical_check);
    Menu.push(spacing3);
    Menu.position_type = column;
    Menu.composer();
    Menu.visible = true;

    dbg dbg_instance = dbg(&Mng);

    CV::render_stack.push_back(&(Mng.images));
    CV::render_stack.push_back(&Menu);
    CV::render_stack.push_back(&conteiner_hist);
    CV::render_stack.push_back(&dbg_instance);



    //Eventos que serão esperados pela classe Mng
    EventListener::add_event(&Mng,en_mouse_left);
    EventListener::add_event(&Mng,en_mouse_right);
    EventListener::add_event(&Mng,en_mouse_move);
    EventListener::add_event(&Mng,en_keyboard_down);


    CV::init(screenWidth, screenHeight, "Canvas2D");
    CV::run();



}

