#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "shear/shear.h"

int Shear_Init(const char *windowTitle, size_t desiredWindowWidth, size_t desiredWindowHeight, size_t aspectRatioWidth, size_t aspectRatioHeight, unsigned short timestepSet, unsigned short frameskipMaxSet, unsigned int flags)
{

  shear_var_engineGlobalSettings.quit = 0;
  shear_var_engineGlobalSettings.title = windowTitle;
  shear_var_engineGlobalSettings.ARW = aspectRatioWidth;
  shear_var_engineGlobalSettings.ARH = aspectRatioHeight;
  shear_var_engineGlobalSettings.timestep = 1000/timestepSet;
  shear_var_engineGlobalSettings.frameskipMax = frameskipMaxSet;

  /* init libraries */
  SDL_Init(SDL_INIT_EVERYTHING);


  /* init components */
  Shear_InitRenderer(windowTitle, aspectRatioWidth, aspectRatioHeight, desiredWindowWidth, desiredWindowHeight);
  Shear_InitStateManager();
  Shear_InitSceneManager();


  return 0;
}

int Shear_Cleanup()
{
  /* destroy components in the reverse order*/
  Shear_DestroySceneManager();
  Shear_DestroyStateManager();
  Shear_DestroyRenderer();
  return 0;
}

void Shear_Run()
{
  int skipTime = 0, lastframeLag = 0, frameskipCount = 0;


  shear_var_engineGlobalSettings.tick = SDL_GetTicks();
  /* enter gameloop with fixed timestep and call functions callbacks through the state manager */
  while(!shear_var_engineGlobalSettings.quit)
  {
    /* call state event functions */
    /* call state logic functions */
    Shear_TickState();

    if(!lastframeLag)
    {
      frameskipCount = 0;
      /* render */
      Shear_RenderScene();
    }
    else
    {
      lastframeLag = 0;
      if(frameskipCount >= shear_var_engineGlobalSettings.frameskipMax)
      {
        /* render */
        Shear_RenderScene();
      }
    }

    Shear_SceneTick(); /* deciding where in the proccess to put this */

    /* timestep control code */


    shear_var_engineGlobalSettings.tick += shear_var_engineGlobalSettings.timestep;


    skipTime = shear_var_engineGlobalSettings.tick - SDL_GetTicks();

    if(skipTime >= 0)
    {
      SDL_Delay(skipTime);
    } else{
      lastframeLag = 1;
    }
  }
}
