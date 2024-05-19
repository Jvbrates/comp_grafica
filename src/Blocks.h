#ifndef BLOCKS_H
#define BLOCKS_H

#include "Conteiner.h"
#include "Polygon.h"

/*
    - Mantem todos os blocos(poligonos), incluindo os limites laterais da tela.
    - moveDown(): Move todos os blocos para baixo.
    - loadLine(): Carrega uma nova linha de blocos, caso haja.
    - sanitizePolygons(): Remove blocos com life == 0.
    - firstCollision() e moveCircle(): Calcula a colis�o de uma esfera.

*/

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


//As fases eram anteriiormente lidas de arquivos, agora ser�o armazenadas em uma struct
typedef struct lvl{
    int blocos_altura;
    int blocos_largura;
    int blocos_altura_total;
    int count_;
    int *blocos;

    void read(int *life, int *shape){

        if(count_ >= this->blocos_largura * this->blocos_altura_total * 2){
            return;
        }

        *life = blocos[count_++];
        *shape = blocos[count_++];
    }

    lvl(int alt, int larg, int t_alt, int *blocos): count_(0){
        this->blocos_altura = alt;
        this->blocos_altura_total = t_alt;
        this->blocos_largura = larg;
        this->blocos = blocos;
    }
    lvl(): count_(0){};


} level;

class Blocks
{
    public:
        level fase;
        Blocks();
        void operator()(int i);
        Blocks(int i);
        virtual ~Blocks();
        Conteiner poligonos;

        int linhas, colunas, total_linhas, linhas_carregadas = 0;
        Vector2 unitsize = Vector2(50., 50.);


        // Calcula a posi��o final do circulo, decrementa os blocos atingidos
        data_moveCircle moveCircle(Vector2 pos, Vector2 movement, float radius, std::vector<Vector2>*);

        // Desce uma linha de blocos
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
