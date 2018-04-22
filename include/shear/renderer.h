#ifndef RENDERER_H__
#define RENDERER_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *target;
} shear_rendererGlobals_t;

shear_rendererGlobals_t shear_var_engineRenderSettings;


int Shear_InitRenderer(const char *title, size_t ARW, size_t ARH, size_t desW, size_t desH);

int Shear_RenderScene();

int Shear_DestroyRenderer();


#ifdef __cplusplus
}
#endif
#endif
