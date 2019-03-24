#include <shear.h>
#include <module.h>

int Res_init_module(void *game_struct, void *module_struct)
{
	shear_game_t *game = (shear_game_t *)game_struct;
	shear_module_t *module = (shear_module_t *)module_struct;
	
	
	return SHEAR_RETURN_OK;
}

int Res_post_init_module(void *game_struct, void *module_struct)
{
	shear_game_t *game = (shear_game_t *)game_struct;
	shear_module_t *module = (shear_module_t *)module_struct;
	
	
	return SHEAR_RETURN_OK;
}

int Res_deinit_module(void *game_struct, void *module_struct)
{
	shear_game_t *game = (shear_game_t *)game_struct;
	shear_module_t *module = (shear_module_t *)module_struct;
	
	
	return SHEAR_RETURN_OK;
}