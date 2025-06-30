/**
 * @file lv_linux_drm.h
 *
 */

#ifndef LV_LINUX_DRM_H
#define LV_LINUX_DRM_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "../../../draw/lv_draw_buf.h"
#include "../../../display/lv_display.h"

#if LV_USE_LINUX_DRM

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_display_t * lv_linux_drm_create(void);

void lv_linux_drm_set_file(lv_display_t * disp, const char * file, int64_t connector_id,
    lv_display_t ** out_display_texture, lv_opengles_window_t ** out_window, lv_opengles_window_texture_t ** out_window_texture);

/* TEMP */
#if LV_LINUX_DRM_USE_EGL
    int lv_linux_get_current_texture_id(void);
    uint8_t * lv_linux_get_current_fb(void);
#endif

/**********************
 *      MACROS
 **********************/

#endif /* LV_USE_LINUX_DRM */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_LINUX_DRM_H */
