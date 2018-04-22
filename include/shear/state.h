#ifndef STATE_H__
#define STATE_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef void(*StateInitCB)(void);
typedef void(*StateLogicCB)(void);
typedef void(*StateEventCB)(SDL_Event *);
typedef void(*StateDestroyCB)(void);

StateInitCB CB_ForegroundInit;
StateLogicCB CB_ForegroundLogic;
StateEventCB CB_ForegroundEvent;
StateDestroyCB CB_ForegroundDestroy;

typedef struct
{
  const char *name;
  StateInitCB CB_Init;
  StateLogicCB CB_Logic;
  StateEventCB CB_Event;
  StateDestroyCB CB_Destroy;
} shear_state_t;

typedef struct
{
  size_t stateNum;
  shear_state_t *states;
  const char *currentStateName;
  size_t cacheStateNum; /* this is only used internally */
  SDL_Event event;
} shear_stateGlobals_t;

shear_stateGlobals_t shear_var_engineStateSettings;



int Shear_InitStateManager();

int Shear_AddState(const char *name, StateInitCB CB_Initf, StateLogicCB CB_Logicf, StateEventCB CB_Eventf, StateDestroyCB CB_Destroyf);

int Shear_AddForegroundState(StateInitCB CB_ForegroundInitf, StateLogicCB CB_ForegroundLogicf, StateEventCB CB_ForegroundEventf, StateDestroyCB CB_ForegroundDestroyf);

int Shear_DestroyStateManager();

int Shear_ResetStateManager();

int Shear_ChangeState(const char *name);

void Shear_TickState();



#ifdef __cplusplus
}
#endif
#endif
