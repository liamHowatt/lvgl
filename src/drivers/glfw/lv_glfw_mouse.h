/**
 * @file lv_glfw_mouse.h
 *
 */

#ifndef LV_GLFW_MOUSE_H
#define LV_GLFW_MOUSE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf_internal.h"
#if LV_USE_OPENGLES

#include "../../indev/lv_indev.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_indev_t * lv_glfw_mouse_create(void);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_OPENGLES*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_GLFW_MOUSE_H */
