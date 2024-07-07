#ifndef OBJ3D_H
#define OBJ3D_H


#include <vector>
#include <memory>

#include "gl_canvas2d.h"
#include "Arestas.h"



using namespace std;

class Obj3D
{
    static shared_ptr<point3d_t> p_zero;
    friend class CV;
    friend void CV_render();

    public:
        bool rotate_old = true;

        std::array<std::array<float, 3>, 3> matriz_rot = {{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    }};;


        Vector3 coordinates = Vector3(0., 0.,0.);

        aresta_t angle_x = aresta_st(p_zero, make_shared<point3d_t>(50., 0., 0.), red);
        aresta_t angle_y = aresta_st(p_zero, make_shared<point3d_t>(0., 50., 0.), green);
        aresta_t angle_z = aresta_st(p_zero, make_shared<point3d_t>(0., 0., 50.), blue);

        Vector3 angle_vector_y = Vector3(1., 0., 0.);
        Vector3 angle_vector_x = Vector3(0., 1., 0.);
        Vector3 angle_vector_z = Vector3(0., 0., 1.);

        double rotate_y = 0.0;
        double rotate_x = 0.0;
        double rotate_z = 0.0;

        vector<shared_ptr<point3d_t>> points;
        vector<vector<aresta_t>> arestas;




    protected:

    private:

        void rotations();
        void translation();
        void projection(float d);
        void camera_transformation();
        void render();
};

#endif // OBJ3D_H
