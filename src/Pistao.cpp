#include "Pistao.h"

Pistao::Pistao(int n_points, float arm_length, float arm_ray, float head_length, float head_ray, float z_displace)
    {

        // Haste
        float step = (M_PI*2)/(float)n_points;

        vector<shared_ptr<point3d_t>> tmp = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp2 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp3 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp4 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp5 = vector<shared_ptr<point3d_t>>();

        for(int i = 0; i < n_points; i++)
        {
            tmp.push_back(make_shared<point3d_t>(
                              arm_ray*cos(i*step),
                              - z_displace,
                              arm_ray*sin(i*step)
                          ));

            tmp2.push_back(make_shared<point3d_t>(
                               arm_ray*cos(i*step),
                               arm_length - z_displace,
                               arm_ray*sin(i*step)
                           ));


            tmp3.push_back(make_shared<point3d_t>(
                               head_ray*cos(i*step),
                               arm_length - z_displace,
                               head_ray*sin(i*step)
                           ));

            tmp4.push_back(make_shared<point3d_t>(
                               head_ray*cos(i*step),
                               head_length + arm_length - z_displace,
                               head_ray*sin(i*step)
                           ));


            tmp5.push_back(make_shared<point3d_t>(
                               arm_ray*cos(i*step),
                               head_length + arm_length - z_displace,
                               arm_ray*sin(i*step)
                           ));
        }




        arestas.push_back(Arestas::linear(tmp, true));
        arestas.push_back(Arestas::linear(tmp2, true));
        arestas.push_back(Arestas::linear(tmp3, true));
        arestas.push_back(Arestas::linear(tmp4, true));
        arestas.push_back(Arestas::linear(tmp5, true));
        arestas.push_back(Arestas::intercalado(tmp, tmp2));
        arestas.push_back(Arestas::intercalado(tmp3, tmp4));
        arestas.push_back(Arestas::intercalado(tmp3, tmp2));
        arestas.push_back(Arestas::intercalado(tmp5, tmp4));

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
        for(auto p: tmp5)
        {
            points.push_back(p);
        }

    }
