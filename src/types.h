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


typedef vec_t(void *) shear_voidptr_vec_t;

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
	void *function;
	uint8_t return_type;
} shear_module_function_t;

typedef map_t(shear_module_function_t) shear_module_funtion_map_t;

typedef struct
{
	char *name, *prefix;
	uint8_t *modin, *modout, *moderr; /* basically stdin/out/err for modules. Made their own here because it will be eventually rendered by the ingame console if attached to the module */
	int (* module_init)(void *game_struct, void *module_struct);
	int (* module_post_init)(void *game_struct, void *module_struct); /* called after every module has run initially */
	int (* module_deinit)(void *game_struct, void *module_struct);
	shear_module_funtion_map_t functions;
} shear_module_t;

typedef vec_t(shear_module_t) shear_module_vec_t;

typedef struct
{
	float hz;
	uint8_t active;
	void (* timer_callback)(void *game_struct, float delta);
	/* TODO make a platform module thread context member */
} shear_timer_callback_t;

typedef vec_t(shear_timer_callback_t) shear_timer_callback_vec_t;


typedef struct
{
	char *name;
	void *data;
	size_t data_size;
	uint32_t type;
	void *parent;
	shear_voidptr_vec_t children;
} shear_scene_node;

typedef struct
{
	union
	{
		double real;
		int64_t integer;
		uint8_t *string;
	} value;
	uint8_t type;
} shear_gamevar_t;

typedef map_t(shear_gamevar_t) shear_gamevar_map_t;


typedef struct
{
	shear_state_vec_t *states;
	shear_event_vec_t *events;
	shear_module_vec_t *modules;
	shear_timer_callback_vec_t *timers;
	shear_gamevar_map_t gamevars;
} shear_game_t;


#ifdef __cplusplus
}
#endif

#endif