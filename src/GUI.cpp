#include "GUI.h"
#include "TextBox.h"


bool GUI::mouse_left(int){

return true;
}

GUI::GUI():
    btnPlay(states_t(Vector2(200, 250), Vector2(100,60), green, black, "PLAY")),
    btnNext(states_t(Vector2(200, 250), Vector2(100,60), green, black, "NEXT LEVEL")),
    btnRetry(states_t(Vector2(200, 250), Vector2(100,60), green, black, "RETRY"))

{




    //INITIAL STATE
    enterState(init);
    CV::render_stack.push_back(&btnPlay);
    CV::render_stack.push_back(&btnRetry);
    CV::render_stack.push_back(&btnNext);

    btnNext.active = false;
    btnRetry.active = false;
    btnNext.visible = false;
    btnRetry.visible = false;

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
    btnPlay.onclick([this](void *arg){
                    this->state = play;
                     return true;
                     }, nullptr);

    // BTN RETRY
    btnRetry.onclick([this](void *arg){
                    this->state = play;
                     return true;
                     }, nullptr);

    // BTN NEXT
    btnNext.onclick([this](void *arg){
                    std::cout << "Clickou em NEXT" << std::endl;
                    this->state = play;
                     return true;
                     }, nullptr);

}

void GUI::enterState(en_app_state st){

    switch(st){
    case init:
        textInit.visible = true;
        btnPlay.visible  = true;
        btnPlay.active   = true;
    break;

    case play:
        game(level_count, 35);
        game.visible                  = true;
        game.cannon.visible           = true;
        game.blocks.poligonos.visible = true;
        break;

    case loose:
        btnRetry.active = true;
        btnRetry.visible = true;

        textInit.setString("Trabalho 3 - Computacao Grafica\nBalls Bounce\nTENTE NOVAMENTE");
        textInit.visible = true;

        break;

    case win_level:
        btnNext.active = true;
        btnNext.visible = true;

        textInit.setString("Trabalho 3 - Computacao Grafica\nBalls Bounce\nVENCEU!");
        textInit.visible = true;
        break;

    case win:
        textInit.setString("Trabalho 3 - Computacao Grafica\nBalls Bounce\nParabens!\nVoce venceu todos os niveis");
        textInit.visible = true;

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

    case play:
        game.visible                  = false;
        game.cannon.visible           = false;
        game.blocks.poligonos.elements.clear();
        break;


    case loose:
        btnRetry.active = false;
        btnRetry.visible = false;

        //textInit.setString("RUIM!\nTENTE NOVAMENTE");
        textInit.visible = false;

        break;

    case win_level:

        btnNext.active = false;
        btnNext.visible = false;
        textInit.visible = false;

        break;


    default:
        std::cout << "Caso não tratatdo" << std::endl;
        exit(21);
        break;

    }
}

void GUI::render() {

    if(state == play && prev_state == play){
            game_state_t g_state = game.getState();
        if(g_state == en_win){
            if(level_count == 1){
                state = win;
            } else if (level_count == 0){
                state = win_level;
                level_count++;
            }


        } else if (g_state == en_lose){
        state = loose;
        }
    }


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
