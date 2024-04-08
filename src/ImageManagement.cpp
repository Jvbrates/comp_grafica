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
#include <stdexcept>


Bmp::Bmp(const char *fileName) {
    width = height = 0;
    data = NULL;
    if (fileName != NULL && strlen(fileName) > 0) {
        load(fileName);
    } else {
        //printf("Error: Invalid BMP filename");
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
        //printf("\nErro ao abrir arquivo %s para leitura", fileName);
        return;
    }

    //printf("\n\nCarregando arquivo %s", fileName);

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

    //printf("\nImagem: %dx%d - Bits: %d", width, height, bits);
    //printf("\nbytesPerLine: %d", bytesPerLine);
    //printf("\nbytesPerLine: %d", width * 3);
    //printf("\ndelta: %d", delta);
    //printf("\nimagesize: %d %d", imagesize, info.imagesize);


    //realiza diversas verificacoes de erro e compatibilidade
    if (header.type != 19778) {
        //printf("\nError: Arquivo BMP invalido");
        getchar();
        exit(0);
    }

    if (width * height * 3 != imagesize) {
        //printf("\nWarning: Arquivo BMP nao tem largura multipla de 4\n");
        //getchar();
    }

    if (info.compression != 0) {
        //printf("\nError: Formato BMP comprimido nao suportado");
        getchar();
        return;
    }
    if (bits != 24) {
        //printf("\nError: Formato BMP com %d bits/pixel nao suportado", bits);
        getchar();
        return;
    }

    if (info.planes != 1) {
        //printf("\nError: Numero de Planes nao suportado: %d", info.planes);
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


Image::Image(std::string path){
    Bmp src = Bmp(path.c_str());

    src.convertBGRtoRGB();

    this->bytesPerLine = src.getBytesPerLine();
    uint colors_n = pow(2, (src.getInfoHeader().bits)/3);
    this->colors = en_rgb;
    this->width = src.getWidth();
    this->height = src.getHeight();
    this->size = {(float)width, (float)height};

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


Image::Image(Bmp src) {
    this->bytesPerLine = src.getBytesPerLine();
    uint colors_n = pow(2, src.getInfoHeader().bits);
    this->colors = en_rgb;
    this->width = src.getWidth();
    this->height = src.getHeight();
    this->size = {(float)width, (float)height};

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

template<class T>
Vector2<T> rotate(Vector2<T> pos, double rot){
    return Vector2<T>{
            static_cast<T>(pos.x * cos(rot) - pos.y * sin(rot)),
            static_cast<T>(pos.x* sin(rot) + pos.y * cos(rot))};
}


void Image::render() {

    //Rotações
    CV::relative_translate(rotate_diff.x, rotate_diff.y);




    int pos;
    for (int y = this->height - 1; y >= 0; y--) {
        for (int x = 0; x < this->width; ++x) {

            //Espelhamentos
            if(this->horizontal_flip){
                pos = width - x;
            } else {
                pos = x;
            }

            if(this->vertical_flip){
                pos += (this->height - y)*this->width;
            } else {
                pos += y * this->width;
            }
            //pos = (x + y * this->width);

            switch (this->colors) {
                case en_redscale: {
                    CV::color(
                            red_channel->pixels[pos] + brightness_mod,
                            0,
                            0
                    );

                    break;
                }
                case en_greenscale: {
                    CV::color(
                            0,
                            green_channel->pixels[pos] + brightness_mod,
                            0
                    );

                    break;
                }
                case en_bluescale: {
                    CV::color(
                            0,
                            0,
                            blue_channel->pixels[pos] + brightness_mod
                    );

                    break;
                }
                case en_grayscale: {
                    CV::color(
                            gray_channel->pixels[pos] + brightness_mod,
                            gray_channel->pixels[pos] + brightness_mod,
                            gray_channel->pixels[pos] + brightness_mod
                    );
                    break;
                }
                case en_rgb: {
                    CV::color(
                            red_channel->pixels[pos] + brightness_mod,
                            green_channel->pixels[pos] + brightness_mod,
                            blue_channel->pixels[pos] + + brightness_mod
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



            if(rotation) {
                auto pixel_rot = rotate(Vector2<float>(x, y), this->rotation);

                CV::rectFill(pixel_rot.x, pixel_rot.y,pixel_rot.x+1, pixel_rot.y+1);
            } else {
                //CV::point(x, y);
                CV::rectFill(x, y, x+1, y+1);
            }

        }
    }


    /*WHY: Como rotacionar necessita mover a tranlação, ela precisa retornar para nao alterar as demais imagens
     * Para manter o posicionamento relativo funcionando, este comportamento relative(move) seguido de relative(move*-1)
     * sempre será visto */
    CV::relative_translate(rotate_diff.x*-1, rotate_diff.y*-1);
}

void Image::setRotation(float rads) {
    this->rotation = rads;
    Vector2<float> pontoCentral(width/2.f, height/2.f);
    //TODO: Troque por relative translate
    auto pontoCentral_r = rotate(pontoCentral, this->rotation);
    rotate_diff =  pontoCentral - pontoCentral_r;


}

float Image::getRotation() {
    return this->rotation;
}

void Image::setBrightnessMod(int b) {
    this->brightness_mod = b;

}

int Image::getBrightnessMod() {
    return this->brightness_mod;
}

void Image::setHorizontalFlip(bool flip) {
    this->horizontal_flip = flip;

}

void Image::setVerticalFlip(bool flip) {
    this->vertical_flip = flip;
}

enum_colors Image::getColor(){
    return this->colors;
}


Image::Image(const Image &src, enum_colors color) {
    this->brightness_mod = src.brightness_mod;
    this->width = src.width;
    this->height = src.height;
    this->rotation = src.rotation;
    this->rotate_diff = src.rotate_diff;
    this->bytesPerLine = src.bytesPerLine; // TODO: Por enquanto, inútil;
    this->size = src.size;

    this->colors = color;

    switch (color) {
        case en_rgb:{
            if(src.colors != en_rgb){// ????????
                throw std::invalid_argument("Object source colors need to be en_rgb");
            }

            this->red_channel = src.red_channel;
            this->blue_channel = src.blue_channel;
            this->green_channel = src.green_channel;
            this->gray_channel = src.gray_channel;
            break;
        }
        case en_grayscale:{
            if(src.gray_channel != nullptr){

                //Adicionado para manter coerência
                this->red_channel = src.red_channel;
                this->blue_channel = src.blue_channel;
                this->green_channel = src.green_channel;


                this->gray_channel = src.gray_channel;
            } else
            {
                throw std::invalid_argument("Object source colors need to have en_grayscale");
            }
            
            break;

        }
        case en_redscale:{
            if(src.colors != en_rgb && src.colors != en_redscale){
                throw std::invalid_argument("Object source colors need to be en_rgb or en_redscale");
            }
            this->red_channel = src.red_channel;
            break;
        }
        case en_greenscale:{
            if(src.colors != en_rgb && src.colors != en_greenscale){
                throw std::invalid_argument("Object source colors need to be en_rgb or en_greenscale");
            }
            this->green_channel = src.green_channel;
            break;
        }
        case en_bluescale:{
            if(src.colors != en_rgb && src.colors != en_bluescale){
                throw std::invalid_argument("Object source colors need to be en_rgb or en_bluescale");
            }
            this->blue_channel = src.blue_channel;
            break;
        }
    }


}

void
Image::grayChannel() {
    if(this->gray_channel)
        std::runtime_error("gray_channel isn't null");

    this->gray_channel = std::make_shared<color_data_t>(this->red_channel->histogram.colors);


    switch (colors) {

        case en_rgb:
        {
            for (uint i = 0; i < this->red_channel->pixels.size(); i++) {
                this->gray_channel->push(
                        this->red_channel->pixels[i] * 0.299
                        + this->green_channel->pixels[i] * 0.587
                        + this->blue_channel->pixels[i] * 0.114

                );

            }
            break;
        }
            default:
                throw std::runtime_error("Só imagens com rgb podem ser decompostas");
        }
    }

void Image::setPriority(int prio_) {
    this->priority = prio_;
}

int Image::getPriority() {
    return this->priority;
}

bool Image::getHorizontalFlip() {
    return horizontal_flip;
}

bool Image::getVerticalFlip() {
    return vertical_flip;
}
