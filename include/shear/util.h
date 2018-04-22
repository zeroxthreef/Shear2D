#ifndef UTIL_H__
#define UTIL_H__


#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <SDL2/SDL.h>

int Shear_UtilReallocArray(void **ptr, size_t currentNum, size_t wantNum, size_t sizeOfIndividualObject);

int Shear_UtilRemoveArrayEntry(void **ptr, size_t currentNum, size_t positionToRemove, size_t sizeOfIndividualObject);

int Shear_UtilAddArrayEntry(void **ptr, size_t currentNum, void *objectPtr, size_t sizeOfIndividualObject);

int Shear_UtilCreateTexFromPath(SDL_Renderer *renderer, SDL_Texture **tex, const char *URL);

int Shear_UtilCreateTexFrombuffer(SDL_Renderer *renderer, SDL_Texture **tex, unsigned char *data, unsigned int length);

SDL_Rect Shear_UtilSelectionFromNumber(unsigned int number, unsigned int rows, unsigned int columns, unsigned int selectableWidth, unsigned int selectableHight);


#ifdef __cplusplus
}
#endif
#endif
