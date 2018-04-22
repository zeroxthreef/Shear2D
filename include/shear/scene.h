#ifndef SCENE_H__
#define SCENE_H__


#ifdef __cplusplus
extern "C" {
#endif

#include <chipmunk/chipmunk.h>

/* TODO make a physics running flag so it can be paused */
/* TODO make a variable to change the physics timestep for slowmo */

/* TODO make destroy callback for object */
/* TODO make life length management */

typedef void(*ObjectDestroyCB)(char *name, char *type, void *data);


enum
{
  SHEAR_PHYSTYPE_WORLD,
  SHEAR_PHYSTYPE_ENTITY,
  SHEAR_PHYSTYPE_PARTICLE,
  SHEAR_PHYSTYPE_CODECONTROLLEDOBJECT
};


typedef struct
{
  unsigned short type;
  cpBB AABB; /* generate this by getting area of entire thing */
  cpBody *body;
  cpShape *shapes;
  size_t shapeNum;
} shear_objectPhysics_t;

typedef struct
{
  void *data;
  char *name; /* NOTE don't send any non malloced strings here */
  char *type; /* NOTE don't send any non malloced strings here */
  short visible;
  size_t lifetime;
  size_t lifetimeBegin;
  ObjectDestroyCB CB_DestroyObject;
  /*User settable scene data */
  shear_objectPhysics_t *physics;
} shear_object_t;

typedef struct
{
  cpSpace *space;
  float physicsTimestep;
  size_t objectNum;
  shear_object_t *objects;
} shear_sceneGlobals_t;

typedef struct
{
  size_t iterations;
  cpVect gravityDirection;
  float sleepThreshold;
  float collisionSlop;
} shear_physicsSettings_t;

shear_sceneGlobals_t shear_var_engineSceneSettings;



int Shear_InitSceneManager();

void Shear_SceneUpdatePhysics(shear_physicsSettings_t physics);

int Shear_DestroySceneManager();

void *Shear_SceneAddObject(char *name, char *type, short visible, void *object, size_t size, shear_objectPhysics_t *physics, size_t lifetime, ObjectDestroyCB CB_DestroyObjectf);

shear_object_t *Shear_SceneGetObject(char *name, char *type, size_t *optionalArrayPos);

cpSpace *Shear_SceneGetSpace();

int Shear_SceneRemoveObject(char *name, char *type);

void Shear_SceneTick();


#ifdef __cplusplus
}
#endif
#endif
