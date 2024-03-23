//*********************************************************
//
// classe para fazer o carregamento de arquivos no formato BMP
// Autor: Cesar Tadeu Pozzer
//        pozzer@inf.ufsm.br
//  Versao 09/2010
//
//**********************************************************

#include "ImageManagement.h"
#include "gl_canvas2d.h"
#include <string.h>
#include <cmath>
#include <exception>

Bmp::Bmp(const char *fileName) {
    width = height = 0;
    data = NULL;
    if (fileName != NULL && strlen(fileName) > 0) {
        load(fileName);
    } else {
        printf("Error: Invalid BMP filename");
    }
}

int Bmp::getBytesPerLine() {
    return this->bytesPerLine;
}

uchar *Bmp::getImage() {
    return data;
}

int Bmp::getWidth(void) {
    return width;
}

int Bmp::getHeight(void) {
    return height;
}

void Bmp::convertBGRtoRGB() {
    unsigned char tmp;
    if (data != NULL) {
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width * 3; x += 3) {
                int pos = y * bytesPerLine + x;
                tmp = data[pos];
                data[pos] = data[pos + 2];
                data[pos + 2] = tmp;
            }
    }


}

void Bmp::load(const char *fileName) {
    FILE *fp = fopen(fileName, "rb");
    if (fp == NULL) {
        printf("\nErro ao abrir arquivo %s para leitura", fileName);
        return;
    }

    printf("\n\nCarregando arquivo %s", fileName);

    //le o HEADER componente a componente devido ao problema de alinhamento de bytes. Usando
    //o comando fread(header, sizeof(HEADER),1,fp) sao lidos 16 bytes ao inves de 14
    fread(&header.type, sizeof(unsigned short int), 1, fp);
    fread(&header.size, sizeof(unsigned int), 1, fp);
    fread(&header.reserved1, sizeof(unsigned short int), 1, fp);
    fread(&header.reserved2, sizeof(unsigned short int), 1, fp);
    fread(&header.offset, sizeof(unsigned int), 1, fp); //indica inicio do bloco de pixels

    //le o INFOHEADER componente a componente devido ao problema de alinhamento de bytes
    fread(&info.size, sizeof(unsigned int), 1, fp);
    fread(&info.width, sizeof(int), 1, fp);
    fread(&info.height, sizeof(int), 1, fp);
    fread(&info.planes, sizeof(unsigned short int), 1, fp);
    fread(&info.bits, sizeof(unsigned short int), 1, fp);
    fread(&info.compression, sizeof(unsigned int), 1, fp);
    fread(&info.imagesize, sizeof(unsigned int), 1, fp);
    fread(&info.xresolution, sizeof(int), 1, fp);
    fread(&info.yresolution, sizeof(int), 1, fp);
    fread(&info.ncolours, sizeof(unsigned int), 1, fp);
    fread(&info.impcolours, sizeof(unsigned int), 1, fp);

    width = info.width;
    height = info.height;
    bits = info.bits;
    bytesPerLine = (3 * (width + 1) / 4) * 4;
    imagesize = bytesPerLine * height;
    int delta = bytesPerLine - (3 * width);

    printf("\nImagem: %dx%d - Bits: %d", width, height, bits);
    printf("\nbytesPerLine: %d", bytesPerLine);
    printf("\nbytesPerLine: %d", width * 3);
    printf("\ndelta: %d", delta);
    printf("\nimagesize: %d %d", imagesize, info.imagesize);


    //realiza diversas verificacoes de erro e compatibilidade
    if (header.type != 19778) {
        printf("\nError: Arquivo BMP invalido");
        getchar();
        exit(0);
    }

    if (width * height * 3 != imagesize) {
        printf("\nWarning: Arquivo BMP nao tem largura multipla de 4");
        getchar();
    }

    if (info.compression != 0) {
        printf("\nError: Formato BMP comprimido nao suportado");
        getchar();
        return;
    }
    if (bits != 24) {
        printf("\nError: Formato BMP com %d bits/pixel nao suportado", bits);
        getchar();
        return;
    }

    if (info.planes != 1) {
        printf("\nError: Numero de Planes nao suportado: %d", info.planes);
        getchar();
        return;
    }

    data = new unsigned char[imagesize];
    fseek(fp, header.offset, SEEK_SET);
    fread(data, sizeof(unsigned char), imagesize, fp);

    fclose(fp);

}

HEADER Bmp::getHeader(void) {
    return this->header;
}

INFOHEADER Bmp::getInfoHeader(void) {
    return this->info;
}





//----------------------------------------------------------------
//----------------------------------------------------------------



Image::Image(Bmp src) {
    this->bytesPerLine = src.getBytesPerLine();
    uint colors_n = pow(2, src.getInfoHeader().bits);
    this->colors = en_rgb;
    this->width = src.getWidth();
    this->height = src.getHeight();


    this->red_channel = std::make_shared<color_data_t>(colors_n);
    this->blue_channel = std::make_shared<color_data_t>(colors_n);
    this->green_channel = std::make_shared<color_data_t>(colors_n);


    unsigned char *data = src.getImage();
    for (int y = src.getHeight(); y > 0; y--) {
        for (int x = 0; x < src.getWidth() * 3; x += 3) {
            int pos = y * this->bytesPerLine + x;
            this->red_channel->push(data[pos]);
            this->green_channel->push(data[pos + 1]);
            this->blue_channel->push(data[pos + 2]);

        }
    }

}

uint Image::getHeight() { return this->height; }

uint Image::getWidth() { return this->width; }

/*

Image::Image(color_channel_data data, enum_colors colors){
    return Image();
}

Image::setHistogram(uint histogram[], uint color_deph, enum_colors color){

}

channel Image::getChannel(){
    return nullptr;
};

static Image Image::decompose(Image src, enum_colors out_channel){
    auto i = Image();
    return i;
    ;
};

uint Image::getColorsDepth(){
    return 0;
};

std::vector<uint> Image::getHistogram(enum_colors channel){
        return std::vector<uint>(0);
};
*/


uint Image::getBytesPerLyne() {
    return this->bytesPerLine;
}

std::shared_ptr<color_data_t> Image::get_channel_pointer(enum_colors color) {
    switch (color) {
        case en_redscale: {
            return this->red_channel;
        }
        case en_greenscale: {
            return this->green_channel;
        }
        case en_bluescale: {
            return this->blue_channel;
        }
        case en_grayscale: {
            return this->gray_channel;
        }
        default: {
            //FIXME throw an exception
            return nullptr;
        }

    }
}

void Image::setColor(enum_colors colors_) {
    this->colors = colors_;
}

void Image::render() {
    int pos;
    for (int y = this->height; y > 0; y--) {
        for (int x = 0; x < this->width; ++x) {
            pos = (x + y * this->width);

            switch (this->colors) {
                case en_redscale: {
                    CV::color(
                            red_channel->pixels[pos],
                            0,
                            0
                    );

                    break;
                }
                case en_greenscale: {
                    CV::color(
                            0,
                            blue_channel->pixels[pos],
                            0
                    );

                    break;
                }
                case en_bluescale: {
                    CV::color(
                            0,
                            0,
                            blue_channel->pixels[pos]
                    );

                    break;
                }
                case en_grayscale: {
                    CV::color(
                            gray_channel->pixels[pos],
                            gray_channel->pixels[pos],
                            gray_channel->pixels[pos]
                    );
                    break;
                }
                case en_rgb: {
                    CV::color(
                            red_channel->pixels[pos],
                            green_channel->pixels[pos],
                            blue_channel->pixels[pos]
                    );

                    break;
                }
                default: {
                    //FIXME throw an exception
                    // Exception improvisada
                    int i = 0;
                    i = 64 / i;
                }

            }

            CV::point(x, y);

        }
    }
}
