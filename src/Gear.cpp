#include "Gear.h"

Gear::Gear(float external_ray, float z_value, float rotate_z_ , float miolo){
        this->rotate_z = rotate_z_;

        vector<shared_ptr<point3d_t>> p1 = Arestas::gear_points(external_ray, z_value/2.f);
        vector<shared_ptr<point3d_t>> p2 = Arestas::gear_points(external_ray, z_value/-2.f);


        vector<aresta_st> m1 = Arestas::linear(p1, true);
        vector<aresta_st> m2 = Arestas::linear(p2, true);
        vector<aresta_st> m3 = Arestas::intercalado(p1, p2);

        for(auto p: p1)
        {
            points.push_back(p);
        }
        for(auto p: p2)
        {
            points.push_back(p);
        }

        arestas.push_back(m1);
        arestas.push_back(m2);
        arestas.push_back(m3);


        vector<shared_ptr<point3d_t>> tmp = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp1 = vector<shared_ptr<point3d_t>>();

        float step = (M_PI*2)/20.;
        for(int i = 0; i < 20; i++)
        {
            tmp.push_back(make_shared<point3d_t>(miolo*cos(i*step),
                                                 miolo*sin(i*step),
                                                 z_value/2.f
                                                ));

            tmp1.push_back(make_shared<point3d_t>(miolo*cos(i*step),
                                                  miolo*sin(i*step),
                                                  z_value/-2.f
                                                 ));

        }




        arestas.push_back(Arestas::linear(tmp, true));
        arestas.push_back(Arestas::linear(tmp1, true));

        arestas.push_back(Arestas::intercalado(tmp, tmp1));

        for(auto p: tmp)
        {
            points.push_back(p);
        }
        for(auto p: tmp1)
        {
            points.push_back(p);
        }


    }
