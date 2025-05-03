/**
 * @file lv_nuttx_keyboard.h
 *
 */

/*********************
 *      INCLUDES
 *********************/

#ifndef LV_NUTTX_KEYBOARD_H
#define LV_NUTTX_KEYBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "../../indev/lv_indev.h"

#if LV_USE_NUTTX

#if LV_USE_NUTTX_KEYBOARD

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize indev with specified input device.
 * @param dev_path      path of input device
 */
lv_indev_t * lv_nuttx_keyboard_create(const char * dev_path);

/**********************
 *      MACROS
 **********************/

#endif /* LV_USE_NUTTX_KEYBOARD */

#endif /* LV_USE_NUTTX*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_NUTTX_KEYBOARD_H */
