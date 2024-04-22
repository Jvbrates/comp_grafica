#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

#include <cmath>
#include <iostream>

typedef unsigned int uint;



class Vector2 {
public:
    float x, y;

    Vector2() {
        x = y = 0;
    }

    Vector2(float _x, float _y) {
        x = _x;
        y = _y;
    }


    // Cria vetor a partir de tupla
    explicit Vector2(std::tuple<float, float> vec) {
        this->x = std::get<0>(vec);
        this->y = std::get<1>(vec);
    }

    // Cria tupla (x,y) a partir de angulo e raio
    static std::tuple<float, float> polar(float ray, double ang) {
        std::tuple<float, float> ret = std::tuple<float, float>();
        std::get<0>(ret) = ray * cos(ang);
        std::get<1>(ret) = ray * sin(ang);

        return ret;
    }

    // Retorna tupla (raio, angulo)
    std::tuple<float, double> getPolar() {
        auto ray = std::sqrt(x * x + y * y);
        double ang = std::acos(x / ray);
        return {ray, ang};
    }

    // Retorna tupla (x, y)
    std::tuple<float, float> getCartesian() {
        return {x, y};
    }

    // define o angulo do vetor mantendo o raio
    void setAngle(double ang) {
        auto ray = std::sqrt(x * x + y * y);

        this->x = ray * cos(ang);
        this->y = ray * sin(ang);

    }

    // Define o raio mantendo o angulo
    void setRay(float ray) {
        double ang = std::acos(x / ray);

        this->x = ray * cos(ang);
        this->y = ray * sin(ang);

    }

    // Retorna o raio
    float getRay() {
        return std::sqrt(x * x + y * y);

    }

    // Retorna o angulo
    double getAngle() {
        auto ray = std::sqrt(x * x + y * y);
        auto angle =  std::acos(x / ray);

        if(y <= 0) return angle;
        else return (2*M_PI)-angle;

    }

    //Angulo em relação ao vetor argumento
    double getAngle(Vector2 vec) {

        auto angle = Vector2::angle(*this, vec);

        return angle;

    }


    // Define x e y
    void set(float _x, float _y) {
        x = _x;
        y = _y;
    }

    // Transforma o vetor em vetor Normal
    void normalize() {
        auto norm = (float) sqrt(x * x + y * y);

        if (norm == 0.0) {
            //printf("\n\nNormalize::Divisao por zero");
            std::cout << "\n\nNormalize::Divisao por zero\n";
            x = 1;
            y = 1;
            return;
        }
        x /= norm;
        y /= norm;
    }

    // Retorna um novo vetor normalizado
    static Vector2 normalize(Vector2 v){
        auto v_cpy = Vector2(v);
        v_cpy.normalize();
        return v_cpy;
    }

    // Retorna a norma do vetor
    float norma() {
        return (float) sqrt(x * x + y * y);
    }


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

    static float distance(Vector2 a, Vector2 b) {
        float x = a.x - b.x;
        float y = a.y - b.y;

        return sqrt(x * x + y * y);
    }

    static float angle(Vector2 a, Vector2 b) {
        a.normalize();
        b.normalize();
        auto p_intern = a ^ b;

        auto angle = (float)acos(p_intern);

        if(a.x*b.y < a.y*b.x) {
            angle = angle;
        } else {
            angle = angle*-1;
        }
        
        
        
        return angle;
    }

    static Vector2 projection(Vector2 a, Vector2 b){
        auto dot_ab = a^b;
        auto dot_bb = b^b;

        auto projection = b*(dot_ab/dot_bb);

        return projection;
    }


    Vector2 projection(Vector2 b){
        return Vector2::projection(*this, b);
    }



    static Vector2 reflex(Vector2 a, Vector2 b){
        auto proj_ab = a.projection(b);
        return (a - proj_ab*2);
    }

    Vector2 reflex(Vector2 b){
        return Vector2::reflex(*this,b);
    }

};



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
