#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

#include <cmath>
#include <iostream>

template< typename numeric>
class Vector2
{
public:
   numeric x, y;

   Vector2()
   {
      x = y = 0;
   }

   Vector2(numeric _x, numeric _y)
    {
        x = _x;
        y = _y;
    }


   void set(numeric _x, numeric _y)
   {
       x = _x;
       y = _y;
   }

   void normalize()
   {
       auto norm = (numeric)sqrt(x*x + y*y);

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

   Vector2 operator - (const Vector2& v)
   {
        Vector2 aux( x - v.x, y - v.y);
        return( aux );
   }

   Vector2 operator + (const Vector2& v)
   {
       Vector2 aux( x + v.x, y + v.y);
       return( aux );
   }

    Vector2 operator * (const int& i)
    {
        Vector2 aux( x*i, y*i);
        return( aux );
    }


   //Adicionem os demais overloads de operadores aqui.

   static numeric distance(Vector2 a, Vector2 b){
       numeric x = a.x - b.x;
       numeric y = a.y - b.y;

       return sqrt(x*x+y*y);
   }

};

#endif
