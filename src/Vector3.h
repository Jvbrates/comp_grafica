#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vector2.h"
#include "array"

using namespace std;

class Vector3
{
    public:
        float x, y, z;
        Vector3(float _x, float _y, float _z);
        float norma();

        virtual ~Vector3();


    Vector3 operator-(const Vector3 &v) {
        Vector3 aux(x - (float) v.x, y - (float) v.y, z - v.z);
        return (aux);
    }

    Vector3 operator+(const Vector3 &v) {
        Vector3 aux(x + (float) v.x, y + (float) v.y, z + (float) v.z);
        return (aux);
    }

    //Multiplicação escalar
    Vector3 operator*(const int &i) {
        Vector3 aux(x * i, y * i, z*i);
        return (aux);
    }

    Vector3 operator*(const float &i) {
        Vector3 aux(x * i, y * i, z * i);
        return (aux);
    }

    //Divisao escalar
    Vector3 operator/(const float &i) {
        Vector3 aux(x / i, y / i, z /i);
        return (aux);
    }


    //Produto Interno
    float operator^(const Vector3 &i) {
        return (this->x * i.x + this->y * i.y + this->z * i.z);
    }


    Vector3 operator+=(const Vector3 &i) {
        this->x += i.x;
        this->y += i.y;
        this->z += i.z;

        return *this;
    }


    Vector3 operator-=(const Vector3 &i) {
        this->x -= i.x;
        this->y -= i.y;
        this->z -= i.z;

        return *this;
    }

    void rotacionaX(double rad);
    void rotacionaY(double rad);
    void rotacionaZ(double rad);
    void rotateArbitrary(const Vector3& axis, double theta);
    friend std::ostream& operator<<(std::ostream &out, Vector3 const& data) {
        out << "( ";
        out << data.x << "; ";
        out << data.y << "; ";
        out << data.z << ")";
        return out;
    }


    Vector3 normalizado(){
        return (*this)/this->norma();
    }



    static float angle(Vector3 a, Vector3 b);

    protected:

    private:
};


bool operator!=(Vector3 v1, Vector3 v2);

Vector3 mmult(const Vector3& vec, const array<array<float, 3>, 3>& rotation_matrix);

Vector3 operator*(Vector3 v1, Vector3 v2);
//float operator^(Vector3 v1, Vector3 v2);

#endif // VECTOR3_H
