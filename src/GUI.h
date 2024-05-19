#ifndef GUI_H
#define GUI_H

/*
    A classe GUI é responsável por administrar a aplicação como um todo,
    alternando entre telas de menu e telas de jogo (Game).
*/


#include "TextBox.h"
#include "button.h"
#include "Game.h"

typedef enum {
    init,
    play,
    win_level,
    win,
    loose
} en_app_state;

class GUI: public Renderizable, public EventClient
{
    public:
        GUI();
        bool mouse_left(int) override;
        virtual ~GUI();
        void render() override;

    protected:



        int level_count = 0;

        void exitState(en_app_state);
        void enterState(en_app_state);

        en_app_state prev_state = init;
        en_app_state state = init;

        //INIT
        TextBox textInit = TextBox("Trabalho 3 - Computacao Grafica\nBalls Bounce", center_center, Vector2(100.,500.));
        Button btnPlay;
        Button btnNext;
        Button btnRetry;

        Game game;

    private:
};

#endif // GUI_H
