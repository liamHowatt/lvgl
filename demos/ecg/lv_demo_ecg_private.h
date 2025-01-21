/**
 * @file lv_demo_ecg_private.h
 *
 */

#ifndef LV_DEMO_ECG_PRIVATE_H
#define LV_DEMO_ECG_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lv_demo_ecg.h"
#if LV_USE_DEMO_ECG

#include "../../src/others/observer/lv_observer.h"
#include "../../src/widgets/label/lv_label.h"
#include "../../src/widgets/image/lv_image.h"
#include "../../src/widgets/line/lv_line.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

enum {
    SIZE_SM = 0,
    SIZE_LG,
    SIZE_COUNT
};

typedef struct {
    const lv_font_t * font_disp_1;
    const lv_font_t * font_disp_2;
    const lv_font_t * font_disp_3;
    const lv_font_t * font_body_lg;
    const lv_font_t * font_body_md;
    const lv_font_t * font_body_sm;
    const lv_font_t * font_caption;
} lv_demo_ecg_sizes_t;

enum {
    STYLE_OBJ = 0,
    STYLE_LABEL,
    STYLE_COUNT
};

enum {
    THEME_DARK = 0
};

typedef struct {
    int32_t sz;                      /* sizes */
    lv_style_t styles[STYLE_COUNT];
    lv_subject_t th;                 /* theme int */
} lv_demo_ecg_ctx_t;

LV_IMAGE_DECLARE(img_lv_demo_ecg_battery);
LV_IMAGE_DECLARE(img_lv_demo_ecg_alarm_disabled);
LV_IMAGE_DECLARE(img_lv_demo_ecg_circuit);
LV_IMAGE_DECLARE(img_lv_demo_ecg_eye);
LV_IMAGE_DECLARE(img_lv_demo_ecg_figure);
LV_IMAGE_DECLARE(img_lv_demo_ecg_gear);
LV_IMAGE_DECLARE(img_lv_demo_ecg_moon);
LV_IMAGE_DECLARE(img_lv_demo_ecg_sun);

LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_14);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_16);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_18);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_20);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_22);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_24);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_28);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_34);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_64);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_84);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_88);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_110);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_114);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_174);

LV_ATTRIBUTE_EXTERN_DATA extern const lv_demo_ecg_sizes_t lv_demo_ecg_sizes[SIZE_COUNT];

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/* lv_demo_ecg_util.c */
lv_obj_t * lv_demo_ecg_base_obj_create(void);
lv_obj_t * lv_demo_ecg_simple_container_create(lv_obj_t * parent, bool vertical, int32_t pad,
                                               lv_flex_align_t align_cross_place);

/* lv_demo_ecg_home.c */
void lv_demo_ecg_home(lv_obj_t * base_obj);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_DEMO_ECG*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_DEMO_ECG_PRIVATE_H*/
