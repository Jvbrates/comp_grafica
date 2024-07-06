#ifndef VIRABREQUIM2D_H
#define VIRABREQUIM2D_H
#include "vector"
#include "Vector2.h"

class virabrequim2d
{
    public:
        virabrequim2d(float center_ext_ray, float center_int_ray, float conn_ext_ray, float conn_int_ray, float dist, int points);
        double getAngle();
        void rotate(double angle);
        void setAngle(double angle);
        Vector2 getDiretor();
        int n_points;
        std::vector<Vector2> points = std::vector<Vector2>();
        ~virabrequim2d();


    protected:
        Vector2 diretor = Vector2(0.,1);


    private:
};

#endif // VIRABREQUIM2D_H
