#include "shear/util.h"
#include "shear/renderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

/* TODO void type array maker for scene manager and commands then array cleaner */

int Shear_UtilReallocArray(void **ptr, size_t currentNum, size_t wantNum, size_t sizeOfIndividualObject) /* NOTE can just pass it a NULL pointer and it allocates it and stuff */
{
  void *tempPtr = NULL;

  /* printf("pointer0 %p pointer1 %p\n", ptr, *ptr); */
  if(*ptr == NULL)
  {
    tempPtr = calloc(wantNum, sizeOfIndividualObject);

    if(tempPtr == NULL)
      return 1;
    else
      *ptr = tempPtr;
  }
  else
  {
    tempPtr = realloc(*ptr, sizeOfIndividualObject * wantNum);
    if(tempPtr == NULL)
      return 1;
    else
      *ptr = tempPtr;
  }
  return 0;
}

int Shear_UtilRemoveArrayEntry(void **ptr, size_t currentNum, size_t positionToRemove, size_t sizeOfIndividualObject)
{
  void *destPtr = *ptr + (positionToRemove * sizeOfIndividualObject);
  void *selectptr = *ptr + ((positionToRemove + 1) * sizeOfIndividualObject);


  /* TODO check if it is the last item because there is nothing to copy after that */

  if(positionToRemove == currentNum)
  {
    if(!Shear_UtilReallocArray(ptr, currentNum - 1, currentNum - 1, sizeOfIndividualObject))
      return 0;
    else
      return 1;
  }
  else
  {
    memmove(destPtr, selectptr, sizeOfIndividualObject * (currentNum - positionToRemove));
    if(!Shear_UtilReallocArray(ptr, currentNum - 1, currentNum - 1, sizeOfIndividualObject))
    {
      return 0;
    }
    else
      return 1;
  }

  return 0;
}

int Shear_UtilAddArrayEntry(void **ptr, size_t currentNum, void *objectPtr, size_t sizeOfIndividualObject)
{
  if(!Shear_UtilReallocArray(ptr, currentNum, currentNum + 1, sizeOfIndividualObject))
  {
    /* ptr[currentNum + 1] = *objectPtr; */
    void *tempPtr = *ptr + (currentNum) * sizeOfIndividualObject;
    /* tempPtr = *objectPtr; */
    memcpy(tempPtr, objectPtr, sizeOfIndividualObject);
    /* printf("[%c] [%c]\n", *((char *)tempPtr), *((char *)tempPtr)); */
  }
  else
  {
    return 1;
  }

  return 0;
}

int Shear_UtilCreateTexFromPath(SDL_Renderer *renderer, SDL_Texture **tex, const char *URL)
{
  int pass = 1;
  SDL_Surface *loadSurface = NULL;

  loadSurface = IMG_Load(URL);
  if(loadSurface == NULL){
    pass--;
  }
  if(renderer != NULL)
    *tex = SDL_CreateTextureFromSurface(renderer, loadSurface);
  else
    *tex = SDL_CreateTextureFromSurface(shear_var_engineRenderSettings.renderer, loadSurface);
  SDL_SetTextureBlendMode(*tex, SDL_BLENDMODE_BLEND);
  SDL_FreeSurface(loadSurface);
  return pass;
}

int Shear_UtilCreateTexFrombuffer(SDL_Renderer *renderer, SDL_Texture **tex, unsigned char *data, unsigned int length)
{
  SDL_Surface *loadSurface = NULL;
  int pass = 1;

  loadSurface = IMG_Load_RW(SDL_RWFromMem(data, length), 0);
  if(loadSurface == NULL){
    pass--;
  }
  if(renderer != NULL)
    *tex = SDL_CreateTextureFromSurface(renderer, loadSurface);
  else
    *tex = SDL_CreateTextureFromSurface(shear_var_engineRenderSettings.renderer, loadSurface);
  SDL_SetTextureBlendMode(*tex, SDL_BLENDMODE_BLEND);
  SDL_FreeSurface(loadSurface);
  return pass;
}

SDL_Rect Shear_UtilSelectionFromNumber(unsigned int number, unsigned int rows, unsigned int columns, unsigned int selectableWidth, unsigned int selectableHight)
{
  //return 0;
}
