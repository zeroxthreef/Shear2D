/*
#include <stdio.h>
#include <chipmunk/chipmunk.h>
#include <SDL2/SDL.h>

SDL_Window *window =NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;

int quit = 0;

int main(void){
  //stupid SDL init stuff.
  SDL_Init(SDL_INIT_EVERYTHING);
  window = SDL_CreateWindow("aaa", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

  // cpVect is a 2D vector and cpv() is a shortcut for initializing them.
  cpVect gravity = cpv(0, -100);

  // Create an empty space.
  cpSpace *space = cpSpaceNew();
  cpSpaceSetGravity(space, gravity);

  // Add a static line segment shape for the ground.
  // We'll make it slightly tilted so the ball will roll off.
  // We attach it to a static body to tell Chipmunk it shouldn't be movable.
  cpShape *ground = cpSegmentShapeNew(cpSpaceGetStaticBody(space), cpv(-50, 5), cpv(50, -5), 0);
  cpShapeSetFriction(ground, 1);
  cpSpaceAddShape(space, ground);

  // Now let's make a ball that falls onto the line and rolls off.
  // First we need to make a cpBody to hold the physical properties of the object.
  // These include the mass, position, velocity, angle, etc. of the object.
  // Then we attach collision shapes to the cpBody to give it a size and shape.

  cpFloat radius = 15;
  cpFloat mass = 1;

  // The moment of inertia is like mass for rotation
  // Use the cpMomentFor*() functions to help you approximate it.
  cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);

  // The cpSpaceAdd*() functions return the thing that you are adding.
  // It's convenient to create and add an object in one line.
  cpBody *ballBody = cpSpaceAddBody(space, cpBodyNew(mass, moment));
  cpBodySetPosition(ballBody, cpv(0, 15));

  // Now we create the collision shape for the ball.
  // You can create multiple collision shapes that point to the same body.
  // They will all be attached to the body and move around to follow it.
  cpShape *ballShape = cpSpaceAddShape(space, cpCircleShapeNew(ballBody, radius, cpvzero));
  cpShapeSetFriction(ballShape, 0.7);

  // Now that it's all set up, we simulate all the objects in the space by
  // stepping forward through time in small increments called steps.
  // It is *highly* recommended to use a fixed size time step.
  cpFloat timeStep = 1.0/60.0;
  //for(cpFloat time = 0; time < 2; time += timeStep){
  cpFloat time = 0;
  cpFloat xoff = 50;
  cpFloat yoff = 50;
  while(!quit)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
        quit++;
    }
    SDL_RenderClear(renderer);
    cpVect pos = cpBodyGetPosition(ballBody);
    cpVect vel = cpBodyGetVelocity(ballBody);
    printf(
      "Time is %5.2f. ballBody is at (%5.2f, %5.2f). It's velocity is (%5.2f, %5.2f)\n",
      time, pos.x, pos.y, vel.x, vel.y
    );
    SDL_Rect rect;
    rect.x = pos.x - (pos.x / 2) + xoff;
    rect.y = -pos.y - (-pos.y / 2) + yoff;
    rect.w = pos.x + (pos.x / 2) + xoff;
    rect.h = -pos.y + (-pos.y / 2) + yoff;
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderDrawLine(renderer, pos.x + xoff, -pos.y + yoff, vel.x + xoff, -vel.y + yoff);

    rect.x = 0 + xoff;
    rect.y = 0 + yoff;
    rect.w = 20 + xoff;
    rect.h = 5 + yoff;

    SDL_RenderDrawRect(renderer, &rect);

    cpSpaceStep(space, timeStep);
    time += timeStep;
    SDL_Delay(17);
    SDL_RenderPresent(renderer);
  }

  // Clean up our objects and exit!
  cpShapeFree(ballShape);
  cpBodyFree(ballBody);
  cpShapeFree(ground);
  cpSpaceFree(space);

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  return 0;
}
*/

#include <stdio.h>
#include <string.h>

#include <shear/shear.h> /* TODO fix it to be shear/shear.h */

#include "level0.h"
#include "level1.h"
#include "main.h"

static void HudInit();

static void HudCleanup();

static void HudLogic();

static void HudEvent(SDL_Event *event);

int main(int argc, char **argv)
{
  /* Game start */
  printf("launching How Confusing\n");

  /* Init the engine */
  Shear_Init("How Confusing - By 0x3F for Ludum Dare 41", 1280, 720, 16, 9, 60, 100, 0);


  /* Add States and further configure the engine */
  Shear_AddForegroundState(HudInit, HudLogic, HudEvent, HudCleanup);
  Shear_AddState("level_0", L0Init, L0Logic, L0Event, L0Destroy);
  Shear_AddState("level_1", L1Init, L1Logic, L1Event, L1Destroy);

  /*Finally hand off control to the engine */
  Shear_Run();

  /*When it is closing, say goodbyes */
  Shear_Cleanup();

  return 0;
}
/* BIG TODO: Give each state it's own scene */

static void HudInit()
{
  /* Just a foreground test */
  /* TODO gain abillity to touch renderer */
  /* TODO define strings for preset types */

  SDL_Texture *tex = NULL;
  Shear_UtilCreateTexFromPath(NULL, &tex, "res/wheel.png");

  //Shear_SceneAddObject("player", "entity", 1, void *object, size_t size, shear_objectPhysics_t *physics, size_t lifetime, ObjectDestroyCB CB_DestroyObjectf)

  //Shear_SceneAddObject("pictureThing", "image", 1, void *object, size_t size, shear_objectPhysics_t *physics, size_t lifetime, ObjectDestroyCB CB_DestroyObjectf)
}

static void HudCleanup()
{

}

static void HudLogic()
{

}

static void HudEvent(SDL_Event *event)
{

  if(event->type == SDL_QUIT)
    shear_var_engineGlobalSettings.quit++;
}
