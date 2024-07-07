#include "Cilindro.h"

Cilindro::Cilindro(int n_points, float internal_ray, float external_ray, float height)
    {
        float step = (M_PI*2)/(float)n_points;


        vector<shared_ptr<point3d_t>> tmp = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp2 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp3 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp4 = vector<shared_ptr<point3d_t>>();


        for(int i = 0; i < n_points; i++)
        {
            tmp.push_back(make_shared<point3d_t>(
                              internal_ray*cos(i*step),
                              internal_ray - external_ray,
                              internal_ray*sin(i*step)
                          ));

            tmp2.push_back(make_shared<point3d_t>(
                               internal_ray*cos(i*step),
                               - height,
                               internal_ray*sin(i*step)
                           ));


            tmp3.push_back(make_shared<point3d_t>(
                               external_ray*cos(i*step),
                               0,
                               external_ray*sin(i*step)
                           ));

            tmp4.push_back(make_shared<point3d_t>(
                               external_ray*cos(i*step),
                               - height,
                               external_ray*sin(i*step)
                           ));
        }



        arestas.push_back(Arestas::linear(tmp, true));
        arestas.push_back(Arestas::linear(tmp2, true));
        arestas.push_back(Arestas::linear(tmp3, true));
        arestas.push_back(Arestas::linear(tmp4, true));
        arestas.push_back(Arestas::intercalado(tmp, tmp2));
        arestas.push_back(Arestas::intercalado(tmp3, tmp4));




        for(auto p: tmp )
        {
            points.push_back(p);
        }
        for(auto p: tmp2)
        {
            points.push_back(p);
        }
        for(auto p: tmp3)
        {
            points.push_back(p);
        }
        for(auto p: tmp4)
        {
            points.push_back(p);
        }



    }

