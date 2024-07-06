#include "Obj3D.h"

/*
Copia source para modified e aplica rotacoes
*/

shared_ptr<point3d_t> Obj3D::p_zero = make_shared<point3d_t>(0.,0.,0.);


void Obj3D::rotations()
{
    //angle_vector.rotacionaY(rotate_y);

    Vector3 tmp_x_y = Vector3(1.f,0.f,0.f);
    Vector3 tmp_z_y = Vector3(0.f,0.f,1.f);

    tmp_x_y.rotateArbitrary(Vector3(0.,0.,1.), rotate_y);
    tmp_z_y.rotateArbitrary(Vector3(0.,0.,1.), rotate_y);

    tmp_z_y.rotateArbitrary(tmp_x_y, rotate_x);

    this->angle_x.p1->modified_vec = this->angle_x.p1->source;
    this->angle_y.p1->modified_vec = this->angle_y.p1->source;
    this->angle_z.p1->modified_vec = this->angle_z.p1->source;


    this->angle_x.p2->modified_vec = this->angle_x.p2->source;
    this->angle_y.p2->modified_vec = this->angle_y.p2->source;
    this->angle_z.p2->modified_vec = this->angle_z.p2->source;

    DEBUG(endl << "ROTACAO Y (" << angle_x.vecN() << this->angle_y.p2->modified_vec);
    this->angle_y.p2->modified_vec.rotateArbitrary(angle_x.vecN(), rotate_x);
    DEBUG(endl << "  " << this->angle_y.p2->modified_vec);


    //ROTATE X
    angle_y.p2->modified_vec.rotateArbitrary(angle_x.vecN(), rotate_x);
    angle_z.p2->modified_vec.rotateArbitrary(angle_x.vecN(), rotate_x);

    //ROTATE Y
    angle_x.p2->modified_vec.rotateArbitrary(angle_y.vecN(), rotate_y);
    angle_z.p2->modified_vec.rotateArbitrary(angle_y.vecN(), rotate_y);


    //ROTATE Z
    angle_y.p2->modified_vec.rotateArbitrary(angle_z.vecN(), rotate_z);
    angle_x.p2->modified_vec.rotateArbitrary(angle_z.vecN(), rotate_z);



    cout  << "ROTACAO X EM TORNO DE:"  << angle_x.vecN() << endl;

    for(auto &item : points){
        if(!(item->rotated)){
                item->modified_vec = item->source;

                //Rotaciona X
                item->modified_vec.rotateArbitrary(angle_x.vecN(), rotate_x);



                item->rotated = true;
        }




                //item->modified_vec.rotateArbitrary(Vector3(0.,0.,1.), rotate_y);

                //item->modified_vec.rotateArbitrary(tmp_z_y, rotate_z);
    }



    for(auto &item : points){

        item->modified_vec.rotateArbitrary(angle_y.vecN(), rotate_y);
    }



    for(auto &item : points){
        item->modified_vec.rotateArbitrary(angle_z.vecN(), rotate_z);

    }


}

/*
Aplica rotacoes para modified
*/
void Obj3D::translation()
{

    for(auto &item : points){
        if(!(item->translated)){
                (item->modified_vec)+=(this->coordinates);
                item->translated= true;
        }
    }

    //Angulos de apoio
    this->angle_x.p1->modified_vec +=  this->coordinates;
    this->angle_x.p2->modified_vec +=  this->coordinates;

    this->angle_y.p1->modified_vec +=  this->coordinates;
    this->angle_y.p2->modified_vec +=  this->coordinates;

    this->angle_z.p1->modified_vec +=  this->coordinates;
    this->angle_z.p2->modified_vec +=  this->coordinates;

}


void Obj3D::projection(float d){



    for(auto &item : points){
        if(!(item->projected)){

                item->projZ(d);
                item->projected = true;

              // DEBUG( item->modified_vec << "-->" << item->projected_vec << endl)
        }
    }

}


void Obj3D::camera_transformation(){

    for(shared_ptr<point3d_t> point : points){
        point->camera_vec = point->modified_vec;
        //point->camera_vec -= CV::camera_coord;
    }
}

void Obj3D::render()
{

    /*
    DEBUG(endl << "Arestas originais" << endl)
    for(vector<aresta_t> &l_arestas: this->arestas){
            DEBUG( "Malha" << endl)
        for(aresta_st aresta: l_arestas){

                DEBUG(aresta.p1->source << " -- " << aresta.p2->source << endl)
        }
    }

*/
    rotations();
    translation();

/*
    DEBUG( endl << "Rotacao e Translação" << endl)
    for(vector<aresta_t> &l_arestas: this->arestas){
            DEBUG( "Malha" << endl)
        for(aresta_st aresta: l_arestas){
                DEBUG(aresta.p1->modified_vec << " -- " << aresta.p2->modified_vec<< endl)
        }
    }

*/

    camera_transformation();
    projection(CV::camera_d);
/*
        DEBUG(endl << "Projecoes" << endl)
    for(vector<aresta_t> &l_arestas: this->arestas){
            DEBUG( "Malha" << endl)
        for(aresta_st aresta: l_arestas){
                DEBUG(aresta.p1->projected_vec << " -- " << aresta.p2->projected_vec<< endl)
        }
    }


*/


    for(vector<aresta_t> &l_arestas: this->arestas){
        for(aresta_st aresta: l_arestas){
            CV::color(aresta.color);
            CV::line(aresta.p1->projected_vec, aresta.p2->projected_vec);


            aresta.p1->projected = false;
            aresta.p2->rotated = false;
            aresta.p2->translated = false;
        }
    }

    //TESTE     //Angulos de apoio

    this->angle_x.p1->projZ(CV::camera_d);
    this->angle_x.p2->projZ(CV::camera_d);
    this->angle_y.p1->projZ(CV::camera_d);
    this->angle_y.p2->projZ(CV::camera_d);
    this->angle_z.p1->projZ(CV::camera_d);
    this->angle_z.p2->projZ(CV::camera_d);
    CV::color(this->angle_x.color);
    CV::line(this->angle_x.p1->projected_vec, this->angle_x.p2->projected_vec);

    CV::color(this->angle_y.color);
    CV::line(this->angle_y.p1->projected_vec, this->angle_y.p2->projected_vec);

    CV::color(this->angle_z.color);
    CV::line(this->angle_z.p1->projected_vec, this->angle_z.p2->projected_vec);


    DEBUG(endl << this->angle_x.p1->source << this->angle_x.p2->source << endl)
    DEBUG(this->angle_x.p1->modified_vec<< this->angle_x.p2->modified_vec << endl)
    DEBUG(this->angle_x.p1->projected_vec << this->angle_x.p2->projected_vec  << endl)


    DEBUG(this->angle_y.p1->source << this->angle_y.p2->source << endl)
    DEBUG(this->angle_y.p1->modified_vec<< this->angle_y.p2->modified_vec << endl)
    DEBUG(this->angle_y.p1->projected_vec << this->angle_y.p2->projected_vec  << endl)

    DEBUG(this->angle_z.p1->source << this->angle_z.p2->source << endl)
    DEBUG(this->angle_z.p1->modified_vec<< this->angle_z.p2->modified_vec << endl)
    DEBUG(this->angle_z.p1->projected_vec << this->angle_z.p2->projected_vec  << endl)
    //DEBUG("";exit(0);)

}
