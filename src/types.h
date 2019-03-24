#ifndef TYPES_H__
#define TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

/* necessary libraries */
#include "../lib/vec/src/vec.h"
#include "../lib/map/src/map.h"
#include "../lib/wren/src/include/wren.h"

#include <stdint.h>
#include <stddef.h>

/* every public data structure and typedef */

enum shear_responses
{
	SHEAR_RETURN_OK,
	SHEAR_RETURN_GENERIC_WARNING,
	SHEAR_RETURN_GENERIC_ERROR,
	SHEAR_RETURN_MEMMORY,
	SHEAR_RETURN_MISSING_DEPENDENCY
};


typedef map_t(void *) shear_voidptr_map_t;

typedef struct
{
	char *name;
	int (* state_init)(void *game_struct);
	int (* state_deinit)(void *game_struct);
	void (* state_event)(void *game_struct);
	void (* state_render)(void *game_struct);
} shear_state_t; /* mostly for defining levels */

typedef vec_t(shear_state_t) shear_state_vec_t;

typedef struct
{
	void *data;
	size_t data_size;
	uint64_t event_type;
	char *event_str; /* used for commands/broadcasts */
} shear_event_t;

typedef vec_t(shear_event_t) shear_event_vec_t;

typedef struct
{
	char *name;
	uint8_t *modin, *modout;
	int (* module_init)(void *game_struct, void *module_struct);
	int (* module_post_init)(void *game_struct, void *module_struct); /* called after every module has run initially */
	int (* module_deinit)(void *game_struct, void *module_struct);
	shear_voidptr_map_t functions;
	/*
	void (* module_event)(void *game_struct, void *module_struct);
	void (* module_render)(void *game_struct, void *module_struct);
	 * */
	/* TODO make a way to make module stdin/out */
} shear_module_t;

typedef vec_t(shear_module_t) shear_module_vec_t;

typedef struct
{
	float hz;
	uint8_t active;
	void (* timer_callback)(void *game_struct);
	/* TODO make a platform module thread context member */
} shear_timer_callback_t;

typedef vec_t(shear_timer_callback_t) shear_timer_callback_vec_t;


typedef struct
{
	
} shear_scene_node;




typedef struct
{
	shear_state_vec_t *states;
	shear_event_vec_t *events;
	shear_module_vec_t *modules;
	shear_timer_callback_vec_t *timers;
} shear_game_t;


#ifdef __cplusplus
}
#endif

#endif