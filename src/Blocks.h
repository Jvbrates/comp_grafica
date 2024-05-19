#ifndef BLOCKS_H
#define BLOCKS_H

#include "Conteiner.h"
#include "Polygon.h"

/*
    - Mantem todos os blocos(poligonos), incluindo os limites laterais da tela.
    - moveDown(): Move todos os blocos para baixo.
    - loadLine(): Carrega uma nova linha de blocos, caso haja.
    - sanitizePolygons(): Remove blocos com life == 0.
    - firstCollision() e moveCircle(): Calcula a colisão de uma esfera.

*/

typedef struct {
    Vector2 pos_final;  //Posição final do vetor

    //Vetor que contém o resto do movimento em caso de colisão
    // ou a direção final do vetor para o proximo frame
    Vector2 reflex;

    //Indica o ´ponto em que ocorreu a colisão, relativo ao comprimento do vetor,
    // caso == 1, não houve colisão
    bool collision;


    // Indica o ultimo segmento em que ocorreu uma colisão. Isto serve para evitar
    //que seja considerada uma colisão no mesmo local em sequencia
    std::vector<Vector2> prev_segment;
} data_moveCircle;


//As fases eram anteriiormente lidas de arquivos, agora serão armazenadas em uma struct
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


        // Calcula a posição final do circulo, decrementa os blocos atingidos
        data_moveCircle moveCircle(Vector2 pos, Vector2 movement, float radius, std::vector<Vector2>*);

        // Desce uma linha de blocos
        void loadLine(); //Carrega uma linha de poligonos

    protected:

        void init(); //Carrega os blocos iniciais do lvl;

        void moveDown(); //Move poligonos para baixo


        // calcula as colisões e em que momento isto ocorrou de 0 a 1.
        data_moveCircle firstCollision(std::vector<std::shared_ptr<Polygon_>> filtered, Vector2 pos, Vector2 mov, std::vector<Vector2>);

        //Obtem poligonos que têm pelo menos um poonto dentro do retangulo passado como parâmetro
        std::vector<std::shared_ptr<Polygon_>> selectByRectangle(Vector2 pos, Vector2 size_);

        //Função principal para calcular o movimento do circulo,
        // a contraparte publica só realiza translação e entra na função recursiva
        data_moveCircle recursiveMoveCircle(Vector2 pos, Vector2 movement, float radius, std::vector<Vector2>*, std::vector<Vector2>);

        //Remove blocos com life == 0
        void sanitizePolygons();


};

#endif // BLOCKS_H
