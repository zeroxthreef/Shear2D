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
	
} shear_state_t;

typedef struct
{
	void *data;
	size_t data_size;
	uint64_t event_type;
	char *event_str; /* used for commands */
} shear_event_t;

typedef struct
{
	char *name;
	
} shear_module_t;


#ifdef __cplusplus
}
#endif

#endif