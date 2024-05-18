#include "Vector2.h"

Vector2::Vector2()
{
    x = y = 0;
}

Vector2::Vector2(float _x, float _y)
{
    x = _x;
    y = _y;
}


void Vector2::setAngle(double ang)
{
    auto ray = std::sqrt(x * x + y * y);

    this->x = ray * cos(ang);
    this->y = ray * sin(ang);

}

void Vector2::setRay(float ray)
{
    double ang = std::acos(x / ray);

    this->x = ray * cos(ang);
    this->y = ray * sin(ang);

}

float Vector2::getRay()
{
    return std::sqrt(x * x + y * y);

}

double Vector2::getAngle()
{
    auto angle = Vector2::angle(*this, Vector2(10.,0));

    return angle;

}

double Vector2::getAngle(Vector2 vec)
{

    auto angle = Vector2::angle(*this, vec);

    return angle;

}

void Vector2::set(float _x, float _y)
{
    x = _x;
    y = _y;
}

void Vector2::normalize()
{
    auto norm = (float) sqrt(x * x + y * y);

    if (norm == 0.0)
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


Vector2 normalize(Vector2 v)
{
    auto v_cpy = Vector2(v);
    v_cpy.normalize();
    return v_cpy;
}

float Vector2::norma()
{
    return (float) sqrt(x * x + y * y);
}


float Vector2::distance(Vector2 a, Vector2 b)
{
    float x = a.x - b.x;
    float y = a.y - b.y;

    return sqrt(x * x + y * y);
}


float Vector2::angle(Vector2 a, Vector2 b)
{
    a.normalize();
    b.normalize();
    auto p_intern = a ^ b;

    auto angle = (float)acos(p_intern);

    if(a.x*b.y < a.y*b.x)
    {
        angle = angle;
    }
    else
    {
        angle = angle*-1;
    }



    return angle;
}

Vector2 Vector2::projection(Vector2 a, Vector2 b)
{
    auto dot_ab = a^b;
    auto dot_bb = b^b;

    auto projection = b*(dot_ab/dot_bb);

    return projection;
}

Vector2 Vector2::projection(Vector2 b)
{
    return Vector2::projection(*this, b);
}

Vector2 Vector2::reflex(Vector2 a, Vector2 b)
{
    auto proj_ab = a.projection(b);
    return (proj_ab*2 - a);
}

Vector2 Vector2::reflex(Vector2 b)
{
    return Vector2::reflex(*this,b);
}



Vector2 polarVec(float ray, float angle)
{
    return Vector2(12.f,12.f);
}

Vector2 Vector2::cpy(){
    return Vector2(this->x, this->y);
}


bool operator!=(const Vector2 &a, const Vector2 &b){
    return (a.x != b.x || b.y != a.y);
};
