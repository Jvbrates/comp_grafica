#ifndef VIRABREQUIM_H
#define VIRABREQUIM_H

#include "Obj3D.h"

class Virabrequim: public Obj3D
{

public:
    Virabrequim(int points, float ray, float distance, float dist_pratos, float ray_x, float depth, float cil_ray);
};

#endif // VIRABREQUIM_H
