/* This module is special because the default way of interracting with the system the game will be running on is SDL, but that can be
statically compiled using the files in lib/ or use the system one and properly use sdl with a DLL. THis engine was written with game jams
in mind. People want easy downloads, so in my mind I wanted this to have the possibility of compiling to a single executable with zero
dlls or shared objects necessary to install.*/

#include <module.h>

int System_init_module(void *game_struct, void *module_struct)
{
	shear_game_t *game = (shear_game_t *)game_struct;
	shear_module_t *module = (shear_module_t *)module_struct;
	
	
	return SHEAR_RETURN_OK;
}

int System_post_init_module(void *game_struct, void *module_struct)
{
	shear_game_t *game = (shear_game_t *)game_struct;
	shear_module_t *module = (shear_module_t *)module_struct;
	
	
	return SHEAR_RETURN_OK;
}

int System_deinit_module(void *game_struct, void *module_struct)
{
	shear_game_t *game = (shear_game_t *)game_struct;
	shear_module_t *module = (shear_module_t *)module_struct;
	
	
	return SHEAR_RETURN_OK;
}