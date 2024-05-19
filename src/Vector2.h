#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

/*
    Vector2: Implementação de vetores 2D.
*/

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

typedef unsigned int uint;



class Vector2 {
public:
    float x, y;

    Vector2();

    Vector2(float _x, float _y);

    // define o angulo do vetor mantendo o raio
    void setAngle(double ang);

    // Define o raio mantendo o angulo
    void setRay(float ray);

    // Retorna o raio
    float getRay();

    // Retorna o angulo
    double getAngle();

    //Angulo em relação ao vetor argumento
    double getAngle(Vector2 vec);

    // Define x e y
    void set(float _x, float _y);
    // Transforma o vetor em vetor Normal
    void normalize();

    // Retorna um novo vetor normalizado
    static Vector2 normalize(Vector2 v);
    // Retorna a norma do vetor
    float norma();

    // Operadores

    Vector2 operator-(const Vector2 &v) {
        Vector2 aux(x - (float) v.x, y - (float) v.y);
        return (aux);
    }

    Vector2 operator+(const Vector2 &v) {
        Vector2 aux(x + (float) v.x, y + (float) v.y);
        return (aux);
    }

    //Multiplicação escalar
    Vector2 operator*(const int &i) {
        Vector2 aux(x * i, y * i);
        return (aux);
    }

    Vector2 operator*(const float &i) {
        Vector2 aux(x * i, y * i);
        return (aux);
    }

    //Divisao escalar
    Vector2 operator/(const float &i) {
        Vector2 aux(x / i, y / i);
        return (aux);
    }


    //Produto Interno
    float operator^(const Vector2 &i) {

        return (this->x * i.x + this->y * i.y);
    }



    Vector2 operator+=(const Vector2 &i) {
        this->x += i.x;
        this->y += i.y;

        return *this;
    }


    Vector2 operator-=(const Vector2 &i) {
        this->x -= i.x;
        this->y -= i.y;

        return *this;
    }





    //Funcoes estaticas

    static float distance(Vector2 a, Vector2 b);

    static float angle(Vector2 a, Vector2 b);

    static Vector2 projection(Vector2 a, Vector2 b);

    Vector2 projection(Vector2 b);


    static Vector2 reflex(Vector2 a, Vector2 b);

    Vector2 reflex(Vector2 b);

    Vector2 cpy();

};

Vector2 polarVec(float ray, float angle);

bool operator!=(const Vector2 &a, const Vector2 &b);
/*
 * Colisão de Circulo e Aresta
 * MOVE_COLISION (CIRCULO, ARESTA, VetorMovimento):
 *  retorna um valor de 0.f a 1.f,
 *  caso o retorno seja 1.f não ouve colisão;
 *  caso haja colisão este valor representa o multiplo do
 *  VetorMovimento em que o círculo estará posicionado no momento da colisão.
 *
 * REFLEXÃO (VetorMovimento, VetorARESTA): <-- Função primária para calcular colisão;
 * Retorna o mesmo vetor só que refletido na superficie da aresta;
 * */





#endif
