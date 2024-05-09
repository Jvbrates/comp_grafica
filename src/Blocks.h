#ifndef BLOCKS_H
#define BLOCKS_H

#include "Conteiner.h"
#include "geometry/Polygon.h"

typedef struct {
    Vector2 pos_final;  //Posição final do vetor

    //Vetor que contém o resto do movimento em caso de colisão
    // ou a direção final do vetor para o proximo frame
    Vector2 reflex;

    //Indica o ´ponto em que ocorreu a colisão, relativo ao comprimento do vetor,
    // caso == 1, não houve colisão
    bool collision;
} data_moveCircle;

class Blocks
{
    public:
        Blocks();
        virtual ~Blocks();
        Conteiner poligonos;

        // Calcula a posição final do circulo, decrementa os blocos atingidos
        data_moveCircle moveCircle(Vector2 pos, Vector2 movement, float radius, std::vector<Vector2>*);

        // Desce uma linha de blocos
        void lineDown();
    protected:
        // calcula as colisões e em que momento isto ocorrou de 0 a 1.
        data_moveCircle firstCollision(std::vector<std::shared_ptr<Polygon_>> filtered, Vector2 pos, Vector2 mov);

        //Obtem poligonos que têm pelo menos um poonto dentro do retangulo passado como parâmetro
        std::vector<std::shared_ptr<Polygon_>> selectByRectangle(Vector2 pos, Vector2 size_);

        //Função principal para calcular o movimento do circulo,
        // a contraparte publica só realiza translação e entra na função recursiva
        data_moveCircle recursiveMoveCircle(Vector2 pos, Vector2 movement, float radius, std::vector<Vector2>*);

        //Remove blocos com life == 0
        void sanitizePolygons();


};

#endif // BLOCKS_H
