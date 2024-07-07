#ifndef ARESTAS_H
#define ARESTAS_H

#include "gl_canvas2d.h"
#include "Vector3.h"
#include <vector>
#include <memory>

using namespace std;


struct piped_point_st
{
    Vector3 source;
    Vector3 modified_vec = Vector3(0.,0.,0.);
    Vector3 camera_vec = Vector3(0.,0.,0.);
    Vector2 projected_vec = Vector2(0.,0.);


    bool rotated = false;
    bool translated = false;
    bool projected = false;


    piped_point_st(float _x, float _y, float _z): source(_x,_y,_z) {};

    void projZ(float d)
    {

        float r = 1;

        r = this->camera_vec.z!=0?(d/this->camera_vec.z):1.f;
        this->projected_vec = Vector2(this->camera_vec.x*r, this->camera_vec.y*r);




    }



};

typedef piped_point_st point3d_t;


struct aresta_st
{
    shared_ptr<point3d_t> p1;
    shared_ptr<point3d_t> p2;

    colors_enum color = black; //Talvez use;


    aresta_st (shared_ptr<point3d_t> p1_, shared_ptr<point3d_t> p2_,colors_enum color_ = black)
    {

        this->p1 = p1_;
        this->p2 = p2_;
        this->color = color_;
    }

    Vector3 vecN()
    {
        Vector3 aux = this->p2->modified_vec - this->p1->modified_vec;
                      return aux.normalizado();
    }
};

typedef aresta_st aresta_t;

namespace Arestas
{

vector<aresta_t> linear(vector<shared_ptr<point3d_t>> points, bool circular  = true);

vector<aresta_t> intercalado(vector<aresta_t> points1, vector<aresta_t> points2, bool linear = true);

vector<aresta_t> intercalado(vector<shared_ptr<point3d_t>>points1, vector<shared_ptr<point3d_t>>points2);

vector<aresta_t> central(vector<shared_ptr<point3d_t>>points, shared_ptr<point3d_t>center);

vector<shared_ptr<point3d_t>> gear_points(float external_ray, float z);

};

#endif // ARESTAS_H
