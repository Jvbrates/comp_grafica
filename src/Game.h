#ifndef GAME_H
#define GAME_H

/*
    A classe Game administra cada fase/partida.

    S�o tr�s itens principais mantidos por game:
    - O canh�o. Muda de posi��o a cada fim de turno e � rotacionado pelo movimento do mouse.
    - Os proj�teis (Bullet).
    - Os blocos. Administra��o delegada para classe Blocks.
*/

#include "Blocks.h"
#include "SpecialSquare.h"


typedef enum {
    stop,
    mirando,
    atirando,
    transicao_atira_mira,
    teste_fim,
    en_win,
    en_lose
} game_state_t;

typedef struct {
    Vector2 pos;
    Vector2 mov;
} bullet;


class Game: public Renderizable, public EventClient
{
    public:
        Game();

        void operator() (int level, int power);

        Game(int);
        bool lose();
        bool win();

        Blocks blocks;
        game_state_t getState();
        Vector2 mov = Vector2(200, 200.6);

        bool mouse_move(Vector2 pos, Vector2 desl) override;
        bool mouse_left(int state) override;


        void render() override;
        Polygon_ cannon;

    protected:
        game_state_t state = stop;
        void stateAtirando(); // Move, desenha, remove proj�teis
        void transAtiraMira();
        void lineDown(float downSize);
        void testeFim();


                //Canh�o
        bool cannon_rotate = true;
        Vector2 cannon_angle = {0.,10.}; // Vetor Auxiliar para controlar os angulos dos pontos do canh�o

        //Projeteis
        float mod_speed = 5.f; //Modificador de velocidade
        float db_bullets = 25.f; // Dist�ncia entre projeteis de uma mesma rajada
        int power = 40; //Numero de projeteis lan�ados no pr�ximo turno
        std::vector<bullet> bullets = std::vector<bullet>(0); //Projeteis
        std::vector<Vector2> bullets_tmp = std::vector<Vector2>(0); // Armazena as balas provisoriamente
        int ammo = 0; //Quantas balas restam ser lan�adas
        Vector2 last_pos_bullet; //Posi��o onde o ultimo proj�til morreu

    private:
};

#endif // GAME_H