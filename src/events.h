#ifndef EVENTS_H__
#define EVENTS_H__

#ifdef __cplusplus
extern "C" {
#endif

enum shear_event_types
{
	SHEAR_EVENT_MOUSEMOVE,
	SHEAR_EVENT_MOUSECLICKED,
	SHEAR_EVENT_MOUSEDOWN,
	SHEAR_EVENT_MOUSEUP,
	SHEAR_EVENT_KEYTYPED,
	SHEAR_EVENT_KEYDOWN,
	SHEAR_EVENT_KEYUP,
	SHEAR_EVENT_WINDOWCHANGE,
	SHEAR_EVENT_MODULE_WARNING,
	SHEAR_EVENT_MODULE_ERROR,
	SHEAR_EVENT_COMMAND,
	SHEAR_EVENT_BROADCAST, /* used by in game elements like hitboxes. While they can also call commands, but this is easier */
	SHEAR_EVENT_CUSTOM /* basically broadcast, but things that are looking for simple data structures wont read this */
};


#ifdef __cplusplus
}
#endif

#endif