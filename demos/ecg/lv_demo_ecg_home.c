/**
 * @file lv_demo_ecg_home.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "lv_demo_ecg_private.h"
#if LV_USE_DEMO_ECG

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

void lv_demo_ecg_home(lv_obj_t * base_obj)
{
    lv_demo_ecg_ctx_t * c = lv_obj_get_user_data(base_obj);

    /* background */

    lv_obj_remove_style_all(base_obj);
    lv_obj_set_size(base_obj, LV_PCT(100), LV_PCT(100));

    lv_obj_t * bg_cont = lv_obj_create(base_obj);
    lv_obj_remove_style_all(bg_cont);
    lv_obj_set_size(bg_cont, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(bg_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_bg_color(bg_cont, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(bg_cont, LV_OPA_COVER, 0);

    /* top bar */

    lv_obj_t * top_bar = lv_obj_create(bg_cont);
    lv_obj_remove_style_all(top_bar);
    lv_obj_set_size(top_bar, LV_PCT(100), 58);
    lv_obj_set_style_bg_color(top_bar, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(top_bar, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_ver(top_bar, 10, 0);
    lv_obj_set_style_pad_hor(top_bar, 24, 0);
    lv_obj_set_flex_flow(top_bar, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(top_bar, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_shadow_color(top_bar, lv_color_white(), 0);
    lv_obj_set_style_shadow_opa(top_bar, LV_OPA_20, 0);
    lv_obj_set_style_shadow_width(top_bar, 106, 0);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /*LV_USE_DEMO_ECG*/
