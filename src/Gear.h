#ifndef GEAR_H
#define GEAR_H

#include "Obj3D.h"

class Gear: public Obj3D
{
public:
    Gear(float external_ray, float z_value, float rotate_z_ = 0.f, float miolo = 5.0);
};



#endif // GEAR_H
