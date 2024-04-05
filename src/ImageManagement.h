//*********************************************************
//
// classe para fazer o carregamento de arquivos no formato BMP
// Autor: Cesar Tadeu Pozzer
//        pozzer@inf.ufsm.br
//
//  Referencia:  http://astronomy.swin.edu.au/~pbourke/dataformats/bmp/
//  Versao 09/2010
//
//**********************************************************

#ifndef ___BMP__H___
#define ___BMP__H___

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <memory>
#include "Conteiner.h"
#include "gl_canvas2d.h"

#define HEADER_SIZE      14 //sizeof(HEADER) vai dar 16 devido ao alinhamento de bytes
#define INFOHEADER_SIZE  40 //sizeof(INFOHEADER) da 40 e esta correto.
#define uchar unsigned char

typedef struct {
    unsigned short int type;                 /* Magic identifier            */
    unsigned int size;                       /* File size in bytes          */
    unsigned short int reserved1, reserved2;
    unsigned int offset;                     /* Offset to image data em bytes*/
} HEADER;


typedef struct {
    unsigned int size;               /* Header size in bytes      */
    int width, height;                /* Width and height of image */
    unsigned short int planes;       /* Number of colour planes   */
    unsigned short int bits;         /* Bits per pixel            */
    unsigned int compression;        /* Compression type          */
    unsigned int imagesize;          /* Image size in bytes       */
    int xresolution, yresolution;     /* Pixels per meter          */
    unsigned int ncolours;           /* Number of colours         */
    unsigned int impcolours;         /* Important colours         */
} INFOHEADER;

//FIXME Use SmartPointers
class Bmp {
private:
    int width, height, imagesize, bytesPerLine, bits;
    unsigned char *data;

    HEADER header;
    INFOHEADER info;

    void load(const char *fileName);

public:
    Bmp(const char *fileName);

    uchar *getImage();

    void applyGammaCorrection(float gamma);

    int getBytesPerLine();

    int getWidth(void);

    int getHeight(void);

    void convertBGRtoRGB(void);

    HEADER getHeader(void);

    INFOHEADER getInfoHeader(void);
};

// Histogram
typedef struct Histogram{
    uint colors;
    std::vector<uint> vector;

    Histogram(uint colors_n){
        colors = colors_n;
        vector = std::vector<uint>(colors_n,0);
    }

} histogram_t;

typedef struct ColorData{
    std::vector<uchar> pixels;
    histogram_t histogram;


    explicit ColorData(uint colors_n) : pixels(0), histogram(colors_n) {}

    void push( uchar color){
        pixels.push_back(color);
        histogram.vector[color]++;
    }

}color_data_t;

// Image Abstraction

typedef enum {
    en_grayscale,
    en_redscale,
    en_greenscale,
    en_bluescale,
    en_rgb
} enum_colors;


class Image : public Renderizable{
private:
    int priority = 0;               //Não faz muito sentido isto estar aqui, mas ok
    enum_colors colors = en_rgb;
    int brightness_mod = 0;
    uint bytesPerLine = 0;
    uint height;
    uint width;
    double rotation = 0;
    bool horizontal_flip = false;
    bool vertical_flip = false;

    //Canais de Cores
    std::shared_ptr<color_data_t> red_channel = nullptr;
    std::shared_ptr<color_data_t> green_channel = nullptr;
    std::shared_ptr<color_data_t> blue_channel = nullptr;
    std::shared_ptr<color_data_t> gray_channel = nullptr;


public:
    void grayChannel();

    uint getHeight();
    uint getWidth();
    uint getBytesPerLyne();
    int getPriority();
    void setPriority(int prio_);
    Vector2<float> rotate_diff;

    explicit Image(Bmp src);
    explicit Image(std::string path);
    Image(const Image& src, enum_colors color = en_rgb);
    void setColor(enum_colors);
    enum_colors getColor();
    void setRotation(float rads);
    float getRotation();
    void setBrightnessMod(int );
    int getBrightnessMod();
    void render() override;
    void setHorizontalFlip(bool flip);

    void setVerticalFlip(bool flip);

    std::shared_ptr<color_data_t> get_channel_pointer(enum_colors color);

};

#endif
