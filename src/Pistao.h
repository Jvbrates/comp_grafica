#ifndef PISTAO_H
#define PISTAO_H

#include "Obj3D.h"

class Pistao: public Obj3D
{
public:
    Pistao(int n_points, float arm_length, float arm_ray, float head_length, float head_ray, float z_displace);
};


#endif // PISTAO_H
