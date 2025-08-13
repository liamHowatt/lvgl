/**
 * @file lv_opengles_raw.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "lv_opengles_raw.h"
#if LV_USE_OPENGLES && LV_USE_OPENGLES_API == LV_OPENGLES_API_RAW

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_opengles_window_t * lv_opengles_raw_window_create(void)
{
    lv_opengles_init();

    lv_timer_create(window_update_handler, LV_DEF_REFR_PERIOD, NULL);

    return NULL;
}

void lv_opengles_window_delete(lv_opengles_window_t * window)
{

}

lv_opengles_window_texture_t * lv_opengles_window_add_texture(lv_opengles_window_t * window, unsigned int texture_id,
                                                              int32_t w, int32_t h);

lv_display_t * lv_opengles_window_display_create(lv_opengles_window_t * window, int32_t w, int32_t h);

lv_opengles_window_texture_t * lv_opengles_window_display_get_window_texture(lv_display_t * window_display);

void lv_opengles_window_texture_remove(lv_opengles_window_texture_t * texture);

void lv_opengles_window_texture_set_x(lv_opengles_window_texture_t * texture, int32_t x);

void lv_opengles_window_texture_set_y(lv_opengles_window_texture_t * texture, int32_t y);

void lv_opengles_window_texture_set_opa(lv_opengles_window_texture_t * texture, lv_opa_t opa);

lv_indev_t * lv_opengles_window_texture_get_mouse_indev(lv_opengles_window_texture_t * texture);

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /*LV_USE_OPENGLES && LV_USE_OPENGLES_API == LV_OPENGLES_API_RAW*/
