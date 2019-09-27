#ifndef __SDL_H__
#define __SDL_H__

#include <iostream>     //std::cerr, std::endl
#include <cstdlib>      //std::exit()
#include <SDL2/SDL.h>   //SDL types, functions and macros

#define SDL_CHECK(err){                                             \
    if (err < 0) {                                                  \
        std::cerr << "[" << __FILE__ << ", " << __LINE__ << "] " << \
        "SDL error " << err << ": " << SDL_GetError() << std::endl; \
        std::exit(err);                                             \
    }                                                               \
}

#define SDL_CHECK_RET(_ret, _expr){                                 \
    _ret = _expr;                                                   \
    if (!_ret) {                                                    \
        std::cerr << "[" << __FILE__ << ", " << __LINE__ << "] " << \
        "SDL error: " << SDL_GetError() << std::endl;               \
        std::exit(-1);                                              \
    }                                                               \
}

#endif // __SDL_H__
