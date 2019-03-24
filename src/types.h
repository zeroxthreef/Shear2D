#ifndef TYPES_H__
#define TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

/* every public data structure and typedef */

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
	void (* module_event)(void *game_struct, void *module_struct);
	void (* module_render)(void *game_struct, void *module_struct);
	/* TODO make a way to make module stdin/out */
} shear_module_t;

typedef vec_t(shear_module_t) shear_module_vec_t;




typedef struct
{
	
} shear_game_t;


#ifdef __cplusplus
}
#endif

#endif