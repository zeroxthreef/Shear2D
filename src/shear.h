#ifndef SHEAR_H__
#define SHEAR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/*
enum shear_initflags
{
	SHEAR_ENGINE_PLACEHOLDER = 1 << 0
};
*/
/* base engine functions */
int shear_engine_init(shear_game_t *game, uint32_t flags);

int shear_engine_run(shear_game_t *game, uint32_t flags);

int shear_engine_cleanup(shear_game_t *game);


#ifdef __cplusplus
}
#endif

#endif