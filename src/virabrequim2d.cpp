#include "virabrequim2d.h"
#include <math.h>
#include <malloc.h>
#define _USE_MATH_DEFINES


virabrequim2d::virabrequim2d(float center_ext_ray, float center_int_ray, float conn_ext_ray, float conn_int_ray, float dist, int points)
{

    double period = M_PI*2 / points;
    this->n_points = points;


    int c = 0;
    for(double i = 0.f; i < M_PI*2; i += period){

        Vector2 tmp = Vector2(0.,0.);

        if(sin(i) >= 0){
            tmp = Vector2(conn_ext_ray * cos(i), conn_ext_ray * sin(i)) + Vector2(0, dist);
        } else {
            tmp = Vector2(center_ext_ray * cos(i), center_ext_ray * sin(i));
        }

        this->points.push_back(tmp);
    }


}
virabrequim2d::~virabrequim2d()
{

}


double virabrequim2d::getAngle()
{

}

void virabrequim2d::rotate(double angle)
{

}

void virabrequim2d::setAngle(double angle)
{

}

Vector2 virabrequim2d::getDiretor()
{

}
