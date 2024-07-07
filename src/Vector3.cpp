#include "Vector3.h"
#include "math.h"

Vector3::Vector3(float _x, float _y, float _z): x(_x), y(_y), z(_z){}

float Vector3::norma()
{
    return sqrt(x*x+y*y+z*z);

}

Vector3::~Vector3()
{
    //dtor
}


void Vector3::rotacionaY(double rad){
    if(!(*this != Vector3(0.,0.,0.))){return;}


     Vector3 aux = Vector3(x*std::cos(rad) + z*std::sin(rad),
                    y,
                    z*std::cos(rad)- x*std::sin(rad)
                    );

    x = aux.x;
    y = aux.y;
    z = aux.z;

}



void Vector3::rotateArbitrary(const Vector3& axis, double theta) {
        // Normaliza o vetor de rotação
        Vector3 u = axis;



        // Calcula as componentes da matriz de rotação
        double cos_theta = cos(theta);
        double sin_theta = sin(theta);
        double one_minus_cos_theta = 1 - cos_theta;

        // Aplica a matriz de rotação ao vetor original
        double x_rot = (cos_theta + u.x * u.x * one_minus_cos_theta) * x
                     + (u.x * u.y * one_minus_cos_theta - u.z * sin_theta) * y
                     + (u.x * u.z * one_minus_cos_theta + u.y * sin_theta) * z;

        double y_rot = (u.y * u.x * one_minus_cos_theta + u.z * sin_theta) * x
                     + (cos_theta + u.y * u.y * one_minus_cos_theta) * y
                     + (u.y * u.z * one_minus_cos_theta - u.x * sin_theta) * z;

        double z_rot = (u.z * u.x * one_minus_cos_theta - u.y * sin_theta) * x
                     + (u.z * u.y * one_minus_cos_theta + u.x * sin_theta) * y
                     + (cos_theta + u.z * u.z * one_minus_cos_theta) * z;

        // Atualiza as coordenadas do vetor rotacionado
        x = x_rot;
        y = y_rot;
        z = z_rot;
    }



Vector3 mmult(const Vector3& vec, const std::array<std::array<float, 3>, 3>& rotation_matrix) {
    Vector3 result = Vector3(
        rotation_matrix[0][0] * vec.x + rotation_matrix[0][1] * vec.y + rotation_matrix[0][2] * vec.z,
        rotation_matrix[1][0] * vec.x + rotation_matrix[1][1] * vec.y + rotation_matrix[1][2] * vec.z,
        rotation_matrix[2][0] * vec.x + rotation_matrix[2][1] * vec.y + rotation_matrix[2][2] * vec.z
    );
    return result;
}

Vector3 operator*(Vector3 v1, Vector3 v2) {
    return Vector3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );}



void Vector3::rotacionaX(double rad){

    if(!(*this != Vector3(0.,0.,0.))){return;}

    Vector3 aux = Vector3( x,
                     y*std::cos(rad) - z*std::sin(rad),
                     y*std::sin(rad) + z*std::cos(rad)

             );

    x = aux.x;
    y = aux.y;
    z = aux.z;
}

void Vector3::rotacionaZ(double rad){
    if(!(*this != Vector3(0.,0.,0.))){return;}


    Vector3 aux = Vector3(
                    x*std::cos(rad) - y*std::sin(rad),
                    x*std::sin(rad) + y*std::cos(rad),
                    z
             );

    x = aux.x;
    y = aux.y;
    z = aux.z;
}



float Vector3::angle(Vector3 a, Vector3 b)
{
    a = a.normalizado();
    b = b.normalizado();

    auto p_intern = a^b;

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


bool operator!=(Vector3 v1, Vector3 v2){
    return (v1.x != v2.x || v1.y != v2.y || v1.z != v2.z);
}



