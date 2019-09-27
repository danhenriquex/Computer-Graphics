#include "SDLImage.h"

#include <iostream>         //std::cerr, std::endl
#include <cstdlib>          //std::exit()
#include <SDL2/SDL_image.h> //IMG_Load(), IMG_GetError()

#define IMG_CHECK(err){                                             \
    if (err < 0) {                                                  \
        std::cerr << "[" << __FILE__ << ", " << __LINE__ << "] " << \
        "IMG error " << err << ": " << IMG_GetError() << std::endl; \
        std::exit(err);                                             \
    }                                                               \
}

#define IMG_CHECK_RET(_ret, _expr){                                 \
    _ret = _expr;                                                   \
    if (!_ret) {                                                    \
        std::cerr << "[" << __FILE__ << ", " << __LINE__ << "] " << \
        "IMG error: " << IMG_GetError() << std::endl;               \
        std::exit(-1);                                              \
    }                                                               \
}

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    #define RMASK 0xff000000
    #define GMASK 0x00ff0000
    #define BMASK 0x0000ff00
    #define AMASK 0x000000ff
#else
    #define RMASK 0x000000ff
    #define GMASK 0x0000ff00
    #define BMASK 0x00ff0000
    #define AMASK 0xff000000
#endif

SDLImage::SDLImage(const std::string& filename) : data{nullptr}, filename{filename} {

    SDL_Surface* original;
    IMG_CHECK_RET(original, IMG_Load(filename.c_str()));

    SDL_PixelFormat format;
    format.format = SDL_PIXELFORMAT_RGBA8888;
    format.palette = NULL;
    format.BitsPerPixel = (Uint8)(32);
    format.BytesPerPixel = (Uint8)(4);
    format.Rmask = RMASK;
    format.Gmask = GMASK;
    format.Bmask = BMASK;
    format.Amask = AMASK;

    SDL_CHECK_RET(data, SDL_ConvertSurface(original, &format, 0));

    SDL_FreeSurface(original);

}

SDLImage::SDLImage(void* pixels, int width, int height) : data{nullptr}, filename{""} {
    SDL_CHECK_RET(data, SDL_CreateRGBSurfaceFrom(pixels, width, height, 32, 4 * width, RMASK, GMASK, BMASK, AMASK));
}

SDLImage::SDLImage(const SDLImage& other) : data{nullptr}, filename{other.filename} {
    SDL_CHECK_RET(data, SDL_ConvertSurface(other.data, other.data->format, 0));
}

SDLImage::SDLImage(const SDLImage& other, int w, int h) : data{nullptr}, filename{other.filename} {

    SDL_CHECK_RET(data, SDL_CreateRGBSurface(other.data->flags, w, h, 32, RMASK, GMASK, BMASK, AMASK));

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = other.data->w;
    rect.h = other.data->h;

    SDL_CHECK(SDL_BlitScaled(other.data, NULL, data, NULL));

}

SDLImage::~SDLImage(void) {
    SDL_FreeSurface(data);
}

const void* SDLImage::getData(void) const {
    return data->pixels;
}

std::size_t SDLImage::getSize(void) const {
    return (std::size_t)(data->w) * (std::size_t)(data->h) * sizeof(char) * 4;
}

int SDLImage::getWidth(void) const {
    return data->w;
}

int SDLImage::getHeight(void) const {
    return data->h;
}

const std::string& SDLImage::getSourceFile(void) const {
    return filename;
}

void SDLImage::savePNG(const std::string& filename) const {
    IMG_CHECK(IMG_SavePNG(data, filename.c_str()));
}
