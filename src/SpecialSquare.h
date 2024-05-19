#ifndef SPECIALSQUARE_H
#define SPECIALSQUARE_H

/*
    Não trata somente de quadrados, apesar do nome;
    Extensão da classe Polygon_, com adição de "vida".
    Permite criação rápida de diferentes formas geométricas (en_shape);
    Os blocos de cada fase usem esta classe;
*/

#include "Polygon.h"

typedef enum {
    en_square = 10,
    en_diamond = 11,
    en_losangulo = 20,
    en_losangulo2 = 21,
    en_triagle_re_0 = 30,
    en_triagle_re_1 = 31,
    en_triagle_re_2= 32,
    en_triagle_re_3 = 33 ,
}en_shape;

class SpecialSquare : public Polygon_
{
    public:
        SpecialSquare(float size, Vector2 pos, int life_);
        SpecialSquare(float size, Vector2 pos, int life_, en_shape shape);
        SpecialSquare();
        void render() override;
        bool draw_collision = false;
        int getLife();
        void decreaseLife(int);
        bool noLife();
        void noLife(bool);
        bool showText();
        void showText(bool);
    protected:
        bool no_life = false;
        bool show_text = true;
        std::vector<Vector2> drawPol;
        int life = 200;

    private:
};

#endif // SPECIALSQUARE_H
