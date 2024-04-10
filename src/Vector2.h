#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

#include <cmath>
#include <iostream>

typedef unsigned int uint;

class Vector2
{
public:
   float x, y;

   Vector2()
   {
      x = y = 0;
   }

   Vector2(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    explicit Vector2(std::tuple<float, float> vec){
       this->x = std::get<0>(vec);
       this->y = std::get<1>(vec);
   }

    static std::tuple<float, float>polar(float ray, double ang){
        std::tuple<float, float> ret = std::tuple<float, float>();
        std::get<0>(ret) = ray* cos(ang);
        std::get<1>(ret) = ray* sin(ang);

        return ret;
   }

    std::tuple<float, double> getPolar(){
       auto ray = std::sqrt(x*x+y*y);
       double ang = std::acos(x/ray);
        return {ray, ang};
   }

   std::tuple<float, float> getCartesian(){
       return {x, y};
   }

   void setAngle(double ang){
       auto ray = std::sqrt(x*x+y*y);

       this->x = ray*cos(ang);
       this->y = ray*sin(ang);

   }

   void setRay(float ray){
       double ang = std::acos(x/ray);

       this->x = ray*cos(ang);
       this->y = ray*sin(ang);

   }

   void set(float _x, float _y)
   {
       x = _x;
       y = _y;
   }

   void normalize()
   {
       auto norm = (float)sqrt(x*x + y*y);

       if(norm==0.0)
       {
          //printf("\n\nNormalize::Divisao por zero");
          std::cout << "\n\nNormalize::Divisao por zero\n";
          x = 1;
          y = 1;
          return;
       }
       x /= norm;
       y /= norm;
   }

   float nomr(){
       return (float)sqrt(x*x + y*y);
   }

   Vector2 operator - (const Vector2& v)
   {
        Vector2 aux( x - (float)v.x, y - (float)v.y);
        return( aux );
   }

   Vector2 operator + (const Vector2& v)
   {
       Vector2 aux( x + (float)v.x, y + (float)v.y);
       return( aux );
   }

    Vector2 operator * (const int& i)
    {
        Vector2 aux( x*i, y*i);
        return( aux );
    }

    Vector2 operator / (const float& i)
    {
        Vector2 aux( x/i, y/i);
        return( aux );
    }

    float operator ^ (const Vector2& i)
    {

       return (this->x*i.x + this->y*i.y);
    }

    Vector2 operator += (const Vector2& i)
    {
        this->x += i.x;
        this->y += i.y;

        return *this;
    }


    //Adicionem os demais overloads de operadores aqui.

   static float distance(Vector2 a, Vector2 b){
       float x = a.x - b.x;
       float y = a.y - b.y;

       return sqrt(x*x+y*y);
   }

};

#endif
