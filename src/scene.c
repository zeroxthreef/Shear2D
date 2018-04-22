#include "shear/scene.h"

#include <string.h>

#include <chipmunk/chipmunk.h>

int Shear_InitSceneManager()
{
  /* TODO init chipmunk too with settings */
  shear_var_engineSceneSettings.objectNum = 0;
  shear_var_engineSceneSettings.objects = NULL;
  shear_var_engineSceneSettings.space = cpSpaceNew();
  shear_var_engineSceneSettings.physicsTimestep = 0.3;

  return 0;
}

void Shear_SceneUpdatePhysics(shear_physicsSettings_t physics)
{
  cpSpaceSetIterations(shear_var_engineSceneSettings.space, physics.iterations);
  cpSpaceSetGravity(shear_var_engineSceneSettings.space, physics.gravityDirection);
  cpSpaceSetSleepTimeThreshold(shear_var_engineSceneSettings.space, physics.sleepThreshold);
  cpSpaceSetCollisionSlop(shear_var_engineSceneSettings.space, physics.collisionSlop);
}

int Shear_DestroySceneManager()
{
  cpSpaceFree(shear_var_engineSceneSettings.space);
  /* TODO free all physics objects and regular objects */
  return 0;
}

void *Shear_SceneAddObject(char *name, char *type, short visible, void *object, size_t size, shear_objectPhysics_t *physics, size_t lifetime, ObjectDestroyCB CB_DestroyObjectf) /* TODO make a buffer to wait until its free to add the objects passed */
{
  /* TODO put the object data into a temp object */
  shear_object_t tempObj;

  tempObj.name = malloc(strlen(name) + 1);
  tempObj.name[0] = 0x00;
  strcat(tempObj.name, name);

  tempObj.type = malloc(strlen(type) + 1);
  tempObj.type[0] = 0x00;
  strcat(tempObj.type, type);

  tempObj.lifetime = lifetime;
  tempObj.lifetimeBegin = SDL_GetTicks();

  tempObj.CB_DestroyObject = CB_DestroyObjectf;

  tempObj.physics = physics;

  tempObj.visible = visible;

  tempObj.data = object;

  if(Shear_UtilAddArrayEntry(&shear_var_engineSceneSettings.objects, shear_var_engineSceneSettings.objectNum, &tempObj, sizeof(shear_object_t)))
    printf("Huge error. Not going to do anything about it though because I don't have time\n");

  /* Add objects or whatever to the physics system. TODO wait and add them until it gets that callback and set a var as not initted in the list */


  shear_var_engineSceneSettings.objectNum++;

  return NULL;
}

shear_object_t *Shear_SceneGetObject(char *name, char *type, size_t *optionalArrayPos) /* optionalArrayPos is used internally. Didnt feel like writing a seperate function for it */
{
  size_t i;

  for(i = 0; i < shear_var_engineSceneSettings.objectNum; i++)
  {
    if(strncmp(shear_var_engineSceneSettings.objects[i].name, name, strlen(name)) == 0 && strncmp(shear_var_engineSceneSettings.objects[i].type, type, strlen(type)) == 0)
    {
      if(optionalArrayPos != NULL)
        *optionalArrayPos = i;
      return &shear_var_engineSceneSettings.objects[i];
    }
  }
  return NULL;
}

cpSpace *Shear_SceneGetSpace()
{
  return shear_var_engineSceneSettings.space;
}

int Shear_SceneRemoveObject(char *name, char *type) /* TODO remove all of certain type and its inverse of removing all but type */
{
  size_t position;
  shear_object_t *object = NULL;

  object = Shear_SceneGetObject(name, type, &position);

  if(object == NULL)
    return 1;

  /* call the objects destructor */

  object->CB_DestroyObject(name, type, object->data);
  free(object->name);
  free(object->type);


  /* TODO loop throught the physics things and remove it all */

  Shear_UtilRemoveArrayEntry(&shear_var_engineSceneSettings.objects, shear_var_engineSceneSettings.objectNum, position, sizeof(shear_object_t));

  return 0;
}

void Shear_SceneTick() /* for managing objects with lifetimes and updating physics*/
{
  //SDL_GetTicks();
  cpSpaceStep(shear_var_engineSceneSettings.space, shear_var_engineSceneSettings.physicsTimestep);
}
