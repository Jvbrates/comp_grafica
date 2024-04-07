//
// Created by jvbrates on 3/28/24.
//

#include "ImageSelector.h"
#include "collisions.h"
#include <memory>



void ImageSelector::loadImage(std::string path, Vector2<float> position) {

    //auto Img = Image(path);

    auto Img = std::make_shared<Image>(path);

    Img->setRelativePos(position);

    //Se já houver imagem selecionada troca a seleção:
    if(this->images.elements.size() > 1){
        this->images.lastElement()->priority = 0;
    }

    this->images.elements.push_back(Img);
    this->images.lastElement()->priority = 20;
    select();

}

void ImageSelector::loadImage(Image Img, enum_colors channel, Vector2<float> position) {


    auto Img_cpy = std::make_shared<Image>(Img, channel);
    Img_cpy->setRelativePos(position);

    //Se já houver imagem selecionada troca a seleção:
    if(this->images.elements.size() > 1){
        this->images.elements[images.elements.size() - 1]
                ->priority = 0;
    }

    this->images.elements.push_back(Img_cpy);
    this->images.elements[images.elements.size() - 1]->priority = 20;
    select();

}


void ImageSelector::sort(){
    /*
     * Isto será usado para desenhar as imagens uma a frente da outra,
     * trazendo-as para frente quando for selecionada e desenhando um
     * retângulo atrás da selecionada.
     * 0 -  Prioridade padrão
     * 10 - Retângulo
     * 20 - Imagem Selecionada
     *
     * */

    std::sort(images.elements.begin(),
              images.elements.end(),
              [](auto a, auto b){


                  return a->priority < b->priority;
        /*auto A_image = std::dynamic_pointer_cast<Image>(a);
        auto B_image = std::dynamic_pointer_cast<Image>(b);

                  return A_image->getPriority() < B_image->getPriority();*/
    });
}

bool ImageSelector::mouse_left(int state){
    if(state == 1){
        mouse_left_press = false;

    } else {

        for (int i = images.elements.size() - 1; i >= 0; --i) {
            if(images.elements[i]->priority == 10)
                continue;


            auto item = std::dynamic_pointer_cast<Image>(images.elements[i]);

            // Pontos da Imagem origem em {0,0}
            auto x1 =  0.f;
            auto y1 = 0.f;
            auto x2 = item->getWidth() + x1;
            auto y2 = item->getHeight() + y1;

            // Mesmos pontos rotacionados:


            collisions::rotate<float>({0.,0.}, 50);
            auto rot_x1_y1 = collisions::rotate<float>({x1,y1}, item->getRotation()) + item->rotate_diff + item->getRelativePos() + images.getRelativePos();
            auto rot_x2_y2 = collisions::rotate<float>({x2,y2}, item->getRotation()) + item->rotate_diff + item->getRelativePos() + images.getRelativePos();
            auto rot_x1_y2 = collisions::rotate<float>({x1,y2}, item->getRotation()) + item->rotate_diff + item->getRelativePos() + images.getRelativePos();
            auto rot_x2_y1 = collisions::rotate<float>({x2,y1}, item->getRotation())+ item->rotate_diff + item->getRelativePos() + images.getRelativePos();


            std::vector<std::tuple<Vector2<float>, Vector2<float>>> edges =
                    {{rot_x1_y1,rot_x2_y1},
                     {rot_x2_y1,rot_x2_y2},
                     {rot_x2_y2,rot_x1_y2},
                     {rot_x1_y2,rot_x1_y1}
                    };




            auto result = collisions::polygon<float>(Vector2<float>{
                                                            static_cast<float>(CV::get_mouse_pos().x),
                                                            static_cast<float>(CV::get_mouse_pos().y)},
                                                    edges);


            if(result){

                if(i != this->images.elements.size() -1){
                    std::cout << "Bring to front" << std::endl;
                    swap(i);
                }
                mouse_left_press = true;

                return true;
            }

        }

        mouse_left_press = true;
    }

    return false;
}

bool ImageSelector::mouse_right(int state) {
    if(state == 1) {
        mouse_right_press = false;
    } else {
        mouse_right_press = true;
        auto selected = getSelected();
        auto middle= getSelected()->getAbsolutePos() + Vector2<float>{static_cast<float>(selected->getWidth()), static_cast<float>(selected->getHeight())}/2;

        vec_mouse_rigth_click = CV::get_mouse_pos() - middle;
        save_rotate = getSelected()->getRotation();
    }

    return true;
}

void ImageSelector::swap(int i){
    if(i != this->images.elements.size() -1){


        auto item = images.elements[i];
        images.elements[this->images.elements.size() -1]->priority = 0;

        item->priority = 20;

        select();


    }
}

void ImageSelector::select(){
    this->sort();
    this->updateQuadri();
    if(this->f_callback) this->f_callback(this->getSelected());
}

void ImageSelector::updateQuadri(){
    if(images.elements[images.elements.size() -1]->priority == 20){
        auto item = std::dynamic_pointer_cast<Image>(images.elements[images.elements.size()-1]);

        // Pontos absolutos da Imagem
        auto x1 =  -15.f;
        auto y1 = -15.f;
        auto x2 = item->getWidth() + x1 + 30;
        auto y2 = item->getHeight() + y1 + 30;

        // Mesmos pontos rotacionados:
        auto rot_x1_y1 = collisions::rotate<float>({x1,y1}, item->getRotation()) + item->rotate_diff + item->getRelativePos();
        auto rot_x2_y2 = collisions::rotate<float>({x2,y2}, item->getRotation()) + item->rotate_diff + item->getRelativePos();
        auto rot_x1_y2 = collisions::rotate<float>({x1,y2}, item->getRotation()) + item->rotate_diff + item->getRelativePos();
        auto rot_x2_y1 = collisions::rotate<float>({x2,y1}, item->getRotation())+ item->rotate_diff + item->getRelativePos();


        quadri->p1 = rot_x1_y1;
        quadri->p2 = rot_x2_y1;
        quadri->p3 = rot_x2_y2;
        quadri->p4 = rot_x1_y2;

    }
}

void ImageSelector::render() {

}


ImageSelector::ImageSelector() {
    this->quadri = std::make_shared<Quadrilatero>();
    this->images.elements.push_back(quadri);
    quadri->priority = 10;
}

ImageSelector::ImageSelector(std::shared_ptr<Image> * pointer) {
    this->poiter = pointer;
    this->quadri = std::make_shared<Quadrilatero>();
    this->images.elements.push_back(quadri);
    quadri->priority = 10;
}


ImageSelector::ImageSelector(std::function<void(std::shared_ptr<Image>)> callback) {
    this->f_callback = callback;
    this->quadri = std::make_shared<Quadrilatero>();
    this->images.elements.push_back(quadri);
    quadri->priority = 10;
}


bool ImageSelector::mouse_move(Vector2<float> pos, Vector2<float> desloc) {
    updateQuadri();

    if(mouse_left_press && !mouse_right_press){
        images.elements[images.elements.size()-1]->setRelativePos(desloc + images.elements[images.elements.size()-1]->getRelativePos()
        );
        updateQuadri();
    }

    if(mouse_right_press){
        auto selected = getSelected();

        auto middle= selected->getAbsolutePos() + Vector2<float>{static_cast<float>(selected->getWidth()), static_cast<float>(selected->getHeight())}/2;

        auto vec_mouse_image = (CV::get_mouse_pos() - middle);
        vec_mouse_image.normalize();
        vec_mouse_rigth_click.normalize();

        auto cosseno = (vec_mouse_image^vec_mouse_rigth_click)/(
                vec_mouse_image.nomr()*vec_mouse_rigth_click.nomr()
                );


        if(vec_mouse_image.x*vec_mouse_rigth_click.y < vec_mouse_image.y*vec_mouse_rigth_click.x) {
            selected->setRotation(save_rotate + acos(cosseno));
        } else {
            selected->setRotation(save_rotate - acos(cosseno));
        }

        updateQuadri();
    }


    return true;
}

bool ImageSelector::key_press(int i) {

    //NOTE: Eu explicitamente estou ignorando o refresh do teclado

    switch (i) {
        case 201:{
            auto image = getSelected();
            image->setRelativePos(image->getRelativePos()+Vector2{0.f,-5.f});
            updateQuadri();
            break;
        }
        case 202:{
            auto image = getSelected();
            image->setRelativePos(image->getRelativePos()+Vector2{5.f,0.f});
            updateQuadri();
            break;
        }
        case 203:{
            auto image = getSelected();
            image->setRelativePos(image->getRelativePos()+Vector2{0.f,5.f});
            updateQuadri();
            break;
        }
        case 200:{
            auto image = getSelected();
            image->setRelativePos(image->getRelativePos()+Vector2{-5.f,0.f});
            updateQuadri();
            break;
        }

    }


    return false;
}

std::shared_ptr<Image> ImageSelector::getSelected() {
    if(this->images.elements.size() >= 2)
        return std::dynamic_pointer_cast<Image>(this->images.elements[this->images.elements.size() -1]);
    return nullptr;
}



void ImageSelector::setCallback(std::function<void(std::shared_ptr<Image>)> function) {
    this->f_callback = function;
}

void dbg::render() {
    auto selected = img->getSelected();

    auto middle= selected->getAbsolutePos() + Vector2<float>{static_cast<float>(selected->getWidth()), static_cast<float>(selected->getHeight())}/2.f;

    auto vec_mouse_image = (CV::get_mouse_pos() - middle);
    vec_mouse_image.normalize();
    img->vec_mouse_rigth_click.normalize();


    CV::color(black);
    CV::line(middle, middle + img->vec_mouse_rigth_click*1000);
    CV::line(middle, middle + vec_mouse_image*1000);
}

dbg::dbg(ImageSelector *i) {
    this->img = i;
}
