#include "GUI.h"
#include "TextBox.h"


bool GUI::mouse_left(int){

return true;
}

GUI::GUI()
{




    //INITIAL STATE
    enterState(init);
    CV::render_stack.push_back(&btnPlay);
    CV::render_stack.push_back(&textInit);

        game = Game();
//
    CV::render_stack.push_back(&game);
    CV::render_stack.push_back(&(game.cannon));
    CV::render_stack.push_back(&(game.blocks.poligonos));

    game.visible = false;
    game.cannon.visible = false;
    game.blocks.poligonos.visible = false;

    EventListener::add_event(&game, en_mouse_move);
    EventListener::add_event(&game, en_mouse_left);



    //BTN PLAY INIT
    std::cout << "Criando  objeto" << std::endl;
    btnPlay = Button(states_t(Vector2(200, 250), Vector2(100,60), green, black, "PLAY"));
//    btnPlay.onclick([this](void *arg){
//                     this->state = play;
//                     std::cout << "Click Button" << std::endl;
//                     return true;
//                     }, nullptr);



}

void GUI::enterState(en_app_state st){

    switch(st){
    case init:
        textInit.visible = true;
        btnPlay.visible  = true;
        btnPlay.active   = true;
    break;
    case play:
        game("Z:\\cg\\comp_grafica\\src\\lvl2.txt", 35);
        game.visible                  = true;
        game.cannon.visible           = true;
        game.blocks.poligonos.visible = true;
        break;

    default :
    break;
    }


}

void GUI::exitState(en_app_state st){
    switch(st){
    case init:
        textInit.visible = false;
        btnPlay.visible  = false;
        btnPlay.active   = false;
    break;

    }
}

void GUI::render() {




    //Troca de estados, remover e colocar na pilha de renderização
    if(prev_state != state){
        exitState(prev_state);
        enterState(state);
    }
    //Save prev State
    prev_state = state;

}


GUI::~GUI()
{
    //dtor
}
