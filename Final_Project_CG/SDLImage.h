#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <string>   //std::string
#include "SDL.h"    //SDL types, functions and macros

class SDLImage {

private:

    SDL_Surface* data;
    std::string filename;

public:

    SDLImage(const std::string& filename);

    SDLImage(void* pixels, int width, int height);

    SDLImage(const SDLImage& other);

    SDLImage(const SDLImage& other, int width, int height);

   ~SDLImage(void);

    const void* getData(void) const;

    std::size_t getSize(void) const;

    int getWidth(void) const;

    int getHeight(void) const;

    const std::string& getSourceFile(void) const;

    void savePNG(const std::string& filename) const;

};

#endif // __IMAGE_H__
