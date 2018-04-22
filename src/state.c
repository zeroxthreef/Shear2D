#include <SDL2/SDL.h>

#include "shear/state.h"


int Shear_InitStateManager()
{
  shear_var_engineStateSettings.stateNum = 0;
  shear_var_engineStateSettings.states = NULL;
  shear_var_engineStateSettings.currentStateName = "";
  shear_var_engineStateSettings.cacheStateNum = 0;

  return 0;
}

int Shear_AddState(const char *name, StateInitCB CB_Initf, StateLogicCB CB_Logicf, StateEventCB CB_Eventf, StateDestroyCB CB_Destroyf)
{
  shear_state_t tempState;
  tempState.name = name;
  tempState.CB_Init = CB_Initf;
  tempState.CB_Logic = CB_Logicf;
  tempState.CB_Event = CB_Eventf;
  tempState.CB_Destroy = CB_Destroyf;
  if(Shear_UtilAddArrayEntry(&shear_var_engineStateSettings.states, shear_var_engineStateSettings.stateNum, &tempState, sizeof(shear_state_t)))
    printf("Huge error. Not going to do anything about it though because I don't have time\n");

  tempState.CB_Init();
  shear_var_engineStateSettings.stateNum++;
  return 0;
}

int Shear_AddForegroundState(StateInitCB CB_ForegroundInitf, StateLogicCB CB_ForegroundLogicf, StateEventCB CB_ForegroundEventf, StateDestroyCB CB_ForegroundDestroyf)
{
  /* TODO add error checking */
  CB_ForegroundInit = CB_ForegroundInitf;
  CB_ForegroundLogic = CB_ForegroundLogicf;
  CB_ForegroundEvent = CB_ForegroundEventf;
  CB_ForegroundDestroy = CB_ForegroundDestroyf;

  CB_ForegroundInit();

  return 0;
}

int Shear_DestroyStateManager()
{
  CB_ForegroundDestroy();
  free(shear_var_engineStateSettings.states);
  return 0;
}

int Shear_ResetStateManager()
{
  Shear_DestroyStateManager();
  Shear_InitStateManager();
}

int Shear_ChangeState(const char *name)
{
  size_t i;
  /* clear last state, scan for state names, then cache its number */
  shear_var_engineStateSettings.states[shear_var_engineStateSettings.cacheStateNum].CB_Destroy();

  for(i = 0; i < shear_var_engineStateSettings.stateNum; i++)
  {
    if(strncmp(shear_var_engineStateSettings.states[i].name, name, strlen(shear_var_engineStateSettings.states[i].name)) == 0)
    {
      shear_var_engineStateSettings.states[i].CB_Init();
      shear_var_engineStateSettings.cacheStateNum = i;

      return 0;
    }
  }


  return 1; /* return error only if it cannot find the state */
}

void Shear_TickState()
{
  while(SDL_PollEvent(&shear_var_engineStateSettings.event))
  {
    /* Call all event callbacks */
    if(shear_var_engineStateSettings.stateNum > 0)
      shear_var_engineStateSettings.states[shear_var_engineStateSettings.cacheStateNum].CB_Event(&shear_var_engineStateSettings.event);
    CB_ForegroundEvent(&shear_var_engineStateSettings.event);
  }

  /* call logic functions */
  if(shear_var_engineStateSettings.stateNum > 0)
    shear_var_engineStateSettings.states[shear_var_engineStateSettings.cacheStateNum].CB_Logic();
  CB_ForegroundLogic();

}
