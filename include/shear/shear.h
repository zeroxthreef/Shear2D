#ifndef SHEAR_H__
#define SHEAR_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"
#include "state.h"
#include "world.h"
#include "scene.h"
#include "command.h"
#include "gui.h"
#include "renderer.h"
#include "sound.h"


typedef struct
{
  unsigned short quit;
  size_t ARW;
  size_t ARH;
  char *title;
  float fps; /* never set this */
  unsigned short timestep;
  unsigned short frameskipMax;
  size_t tick;
} shear_engineGlobals_t;

shear_engineGlobals_t shear_var_engineGlobalSettings;


int Shear_Init(const char *windowTitle, size_t desiredWindowWidth, size_t desiredWindowHeight, size_t aspectRatioWidth, size_t aspectRatioHeight, unsigned short timestepSet, unsigned short frameskipMaxSet, unsigned int flags);

int Shear_Cleanup();

void Shear_Run();


#ifdef __cplusplus
}
#endif
#endif
