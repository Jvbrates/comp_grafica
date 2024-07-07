#ifndef CILINDRO_H
#define CILINDRO_H

#include "Obj3D.h"

class Cilindro: public Obj3D
{
public:
    Cilindro(int n_points, float internal_ray, float external_ray, float height);
};
#endif // CILINDRO_H
