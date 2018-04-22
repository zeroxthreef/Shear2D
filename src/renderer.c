#include <SDL2/SDL.h>

#include "shear/renderer.h"
#include "shear/scene.h"

#include <stdio.h>

int Shear_InitRenderer(const char *title, size_t ARW, size_t ARH, size_t desW, size_t desH)
{
  /* setup the window and renderer */
  shear_var_engineRenderSettings.window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, desW, desH, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED);
  shear_var_engineRenderSettings.renderer = SDL_CreateRenderer(shear_var_engineRenderSettings.window, 0, SDL_RENDERER_ACCELERATED);


  return 0;
}

int Shear_RenderScene() /* TODO in the future, pass it the scene instead of using the global one */
{
  SDL_RenderClear(shear_var_engineRenderSettings.renderer);

  SDL_RenderDrawLine(shear_var_engineRenderSettings.renderer, 0, 0, 50, 50);


  SDL_RenderPresent(shear_var_engineRenderSettings.renderer);
  return 0;
}

int Shear_DestroyRenderer()
{
  SDL_DestroyRenderer(shear_var_engineRenderSettings.renderer);
  SDL_DestroyWindow(shear_var_engineRenderSettings.window);
  return 0;
}
