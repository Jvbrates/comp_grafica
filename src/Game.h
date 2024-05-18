#ifndef GAME_H
#define GAME_H

#include "Blocks.h"
#include "SpecialSquare.h"


typedef enum {
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

        void operator() (char level[], int power);

        Game(char level[]);
        bool lose();
        bool win();

        Blocks blocks;
        game_state_t getState();
        Vector2 bullet0 = Vector2(100., 100.);
        Vector2 mov = Vector2(200, 200.6);

        bool mouse_move(Vector2 pos, Vector2 desl) override;
        bool mouse_left(int state) override;


        void render() override;
        Polygon_ cannon;

    protected:
        game_state_t state = mirando;
        void stateAtirando(); // Move, desenha, remove projéteis
        void transAtiraMira();
        void lineDown(float downSize);
        void testeFim();


                //Canhão
        bool cannon_rotate = true;
        Vector2 cannon_angle = {0.,10.}; // Vetor Auxilia para controlar os angulos dos pontos do canhão

        //Projeteis
        float mod_speed = 5.f; //Modificador de velocidade
        float db_bullets = 25.f; // Distância entre projeteis de uma mesma rajada
        int power = 40; //Numero de projeteis lançados no próximo turno
        std::vector<bullet> bullets = std::vector<bullet>(0); //Projeteis
        std::vector<Vector2> bullets_tmp = std::vector<Vector2>(0); // Armazena as balas provisoriamente
        int ammo = 0; //Quantas balas restam ser lançadas
        Vector2 last_pos_bullet; //Posição onde o ultimo projétil morreu

    private:
};

#endif // GAME_H
