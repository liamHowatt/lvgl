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
#include "../../src/libs/tiny_ttf/lv_tiny_ttf.h"
#include "../../src/widgets/tileview/lv_tileview.h"

/*********************
 *      DEFINES
 *********************/

/* size primitives */
#define PRIM_L    40
#define PRIM_XL   80

/**********************
 *      TYPEDEFS
 **********************/

enum {
    DISP_SIZE_SM = 0,
    DISP_SIZE_LG,
    DISP_SIZE_COUNT
};

enum {
    SIZE_FONT_DISPLAY_BIG_NUMERIC_XL = 0,
    SIZE_FONT_DISPLAY_BIG_NUMERIC_M,
    SIZE_FONT_DISPLAY_BIG_NUMERIC_S,
    SIZE_FONT_DISPLAY_STANDARD_XL,
    SIZE_FONT_DISPLAY_STANDARD_L,
    SIZE_FONT_DISPLAY_STANDARD_M,
    SIZE_FONT_DISPLAY_STANDARD_S,
    SIZE_FONT_HEADER_H4,
    SIZE_FONT_BODY_L,
    SIZE_FONT_BODY_S,
    SIZE_FONT_LABEL_STANDARD,
    SIZE_FONT_LABEL_BIG_NUMERIC,
    SIZE_COUNT
};

enum {
    FONT_DISPLAY_BIG_NUMERIC_XL = 0,
    FONT_DISPLAY_BIG_NUMERIC_M,
    FONT_DISPLAY_BIG_NUMERIC_S,
    FONT_DISPLAY_STANDARD_XL,
    FONT_DISPLAY_STANDARD_L,
    FONT_DISPLAY_STANDARD_M,
    FONT_DISPLAY_STANDARD_S,
    FONT_HEADER_H4,
    FONT_BODY_L,
    FONT_BODY_S,
    FONT_LABEL_STANDARD_LARGE,
    FONT_LABEL_STANDARD_SMALL,
    FONT_LABEL_BIG_NUMERIC_LARGE,
    FONT_LABEL_BIG_NUMERIC_SMALL,

    FONT_QUICKSAND_LIGHT_290,
    FONT_QUICKSAND_LIGHT_140,
    FONT_QUICKSAND_BOLD_27,
    FONT_QUICKSAND_MEDIUM_24,
    FONT_QUICKSAND_MEDIUM_22,
    FONT_INTER_MEDIUM_16,
    FONT_COUNT
};

enum {
    STYLE_CONTAINER_BG_MAIN_FRAME = 0,
    STYLE_LABEL,
    STYLE_A8_IMG,
    STYLE_BUTTON_BORDER_SOFT,
    STYLE_CONTAINER_FILL_INVERT,
    STYLE_CONTAINER_BG_PRIMARY,
    STYLE_COUNT
};

enum {
    THEME_LIGHT = 0,
    THEME_DARK
};

typedef struct {
    int32_t sz;                      /* sizes */
    lv_font_t * fonts[FONT_COUNT];
    lv_style_t styles[STYLE_COUNT];
    lv_subject_t th;                 /* theme int */
} lv_demo_ecg_ctx_t;

LV_IMAGE_DECLARE(img_lv_demo_ecg_alarm_disabled);
LV_IMAGE_DECLARE(img_lv_demo_ecg_battery);
LV_IMAGE_DECLARE(img_lv_demo_ecg_circuit);
LV_IMAGE_DECLARE(img_lv_demo_ecg_figure_lg);
LV_IMAGE_DECLARE(img_lv_demo_ecg_figure_sm);
LV_IMAGE_DECLARE(img_lv_demo_ecg_gear);
LV_IMAGE_DECLARE(img_lv_demo_ecg_heart);
LV_IMAGE_DECLARE(img_lv_demo_ecg_logo);
LV_IMAGE_DECLARE(img_lv_demo_ecg_monitor);
LV_IMAGE_DECLARE(img_lv_demo_ecg_moon);
LV_IMAGE_DECLARE(img_lv_demo_ecg_sun);
LV_IMAGE_DECLARE(img_lv_demo_ecg_view);

LV_ATTRIBUTE_EXTERN_DATA extern const int32_t lv_demo_ecg_sizes[DISP_SIZE_COUNT][SIZE_COUNT];

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
