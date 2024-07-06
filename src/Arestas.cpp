#include "Arestas.h"


namespace Arestas {

    vector<aresta_t> linear(vector<shared_ptr<point3d_t>>points, bool circular)
    {

        vector<aresta_t> retorno = vector<aresta_t>();

        for(int i = 0; i < points.size() -1; i++){
            retorno.emplace_back(points[i], points[i+1]);

        }

        if(circular){
            retorno.emplace_back(points[points.size()-1], points[0]);
        }

        return retorno;
    }

    vector<aresta_t> intercalado(vector<aresta_t>points1, vector<aresta_t>points2, bool linear)
    {
        vector<aresta_t> retorno = vector<aresta_t>();
        if(points1.size() > points2.size()){
            for(int i = 0; i < points2.size(); i++){
                retorno.emplace_back(points2[i].p1, points1[i].p1);
                if(!linear){
                    retorno.emplace_back(points2[i].p2, points1[i].p2);
                }
            }
        } else {
            for(int i = 0; i < points1.size(); i++){
                retorno.emplace_back(points1[i].p1, points2[i].p1);
                if(!linear){
                    retorno.emplace_back(points1[i].p2, points2[i].p2);
                }
            }
        }

        return retorno;
    }


    vector<aresta_t> intercalado(vector<shared_ptr<point3d_t>>points1, vector<shared_ptr<point3d_t>>points2){
        vector<aresta_t> retorno = vector<aresta_t>();
        if(points1.size() > points2.size()){
            for(int i = 0; i < points2.size(); i++){
                retorno.emplace_back(points2[i], points1[i]);
            }
        } else {
            for(int i = 0; i < points1.size(); i++){
                retorno.emplace_back(points2[i], points1[i]);
            }
        }

        return retorno;
    }

    vector<aresta_t> central(vector<shared_ptr<point3d_t>>points, shared_ptr<point3d_t>center){

        vector<aresta_t> tmp = vector<aresta_t>();

        for(shared_ptr<point3d_t> point: points){
            tmp.push_back(aresta_st(point, center));
        }

        return tmp;
    }

}
