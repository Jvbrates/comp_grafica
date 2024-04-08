/*
 * Quadrilatero:
 * Classe auxiliar para desenhar um retângulo atrás da imagem selecionada
 *
 * ImagemSelector:
 *  é responsável por gerenciar a seleção e exibição de imagens, oferecendo
 *  funcionalidades para carregar imagens a partir de arquivos ou diretamente
 *  de objetos ImageManagement.
 *  Ela também inclui métodos para interagir com o mouse e o teclado, como
 *  detectar cliques e movimentos do mouse, além de fornecer um menu de comunicação
 *  para obter a imagem selecionada.
 *
 * */
//
// Created by jvbrates on 3/28/24.
//

#ifndef COMP_GRAFICA_IMAGESELECTOR_H
#define COMP_GRAFICA_IMAGESELECTOR_H

#include "EventListener.h"
#include "ImageManagement.h"
#include "Conteiner.h"


class Quadrilatero : public Renderizable{
public:
    colors_enum color = yellow;
    Vector2<float> p1 = {0., 0.},
            p2 = {0., 0.},
            p3 = {0., 0.},
            p4 = {0., 0.};

    void render() override{
        CV::color(color);
        CV::polygonFill({{p1,p2},
                     {p2,p3},
                     {p3,p4},
                     {p4,p1}});
    }
};



class ImageSelector;

class dbg: public Renderizable{

public:
    explicit dbg(ImageSelector *i);
    ImageSelector *img;
    void render() override;
};

class ImageSelector: public EventClient, public Renderizable{
private:

    friend class dbg;
    std::function<void(std::shared_ptr<Image>)> f_callback;


    uint posImages = -1;
    bool mouse_left_press = false;
    bool mouse_right_press = false;
    Vector2<float> vec_mouse_rigth_click = {0.,0.};
    float save_rotate;

    std::shared_ptr<Quadrilatero> quadri;

    void swap(int i);
    void sort();
    std::shared_ptr<Image> * poiter;

public:

    explicit ImageSelector(std::function<void(std::shared_ptr<Image>)> function);
    explicit ImageSelector(std::shared_ptr<Image> * pointer);
    explicit ImageSelector();
    void setCallback(std::function<void(std::shared_ptr<Image>)> function);
    void select();

    void loadImage(Image Img, enum_colors channel, Vector2<float> position);
    void loadImage(std::string path, Vector2<float> position);

    void render() override;
    bool mouse_left(int state) override;
    bool mouse_right(int state) override;
    bool mouse_move(Vector2<float> pos, Vector2<float> desloc) override;
    bool key_press(int) override;
    void updateQuadri();

    //Menu Comunication:
    std::shared_ptr<Image> getSelected();

    Conteiner images;
};


#endif //COMP_GRAFICA_IMAGESELECTOR_H
