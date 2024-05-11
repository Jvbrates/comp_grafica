#ifndef BLOCKS_H
#define BLOCKS_H

#include "Conteiner.h"
#include "geometry/Polygon.h"
#include <stdio.h>


typedef struct {
    Vector2 pos_final;  //Posi��o final do vetor

    //Vetor que cont�m o resto do movimento em caso de colis�o
    // ou a dire��o final do vetor para o proximo frame
    Vector2 reflex;

    //Indica o �ponto em que ocorreu a colis�o, relativo ao comprimento do vetor,
    // caso == 1, n�o houve colis�o
    bool collision;


    // Indica o ultimo segmento em que ocorreu uma colis�o. Isto serve para evitar
    //que seja considerada uma colis�o no mesmo local em sequencia
    std::vector<Vector2> prev_segment;
} data_moveCircle;

class Blocks
{
    public:
        Blocks();
        Blocks(char *);
        virtual ~Blocks();
        Conteiner poligonos;

        int linhas, colunas, total_linhas, linhas_carregadas = 0;
        Vector2 unitsize = Vector2(50., 50.);
        FILE *mapa;


        // Calcula a posi��o final do circulo, decrementa os blocos atingidos
        data_moveCircle moveCircle(Vector2 pos, Vector2 movement, float radius, std::vector<Vector2>*);

        // Desce uma linha de blocos
        void lineDown();
        void loadLine(); //Carrega uma linha de poligonos

    protected:

        void init(); //Carrega os blocos iniciais do lvl;

        void moveDown(); //Move poligonos para baixo


        // calcula as colis�es e em que momento isto ocorrou de 0 a 1.
        data_moveCircle firstCollision(std::vector<std::shared_ptr<Polygon_>> filtered, Vector2 pos, Vector2 mov, std::vector<Vector2>);

        //Obtem poligonos que t�m pelo menos um poonto dentro do retangulo passado como par�metro
        std::vector<std::shared_ptr<Polygon_>> selectByRectangle(Vector2 pos, Vector2 size_);

        //Fun��o principal para calcular o movimento do circulo,
        // a contraparte publica s� realiza transla��o e entra na fun��o recursiva
        data_moveCircle recursiveMoveCircle(Vector2 pos, Vector2 movement, float radius, std::vector<Vector2>*, std::vector<Vector2>);

        //Remove blocos com life == 0
        void sanitizePolygons();


};

#endif // BLOCKS_H
