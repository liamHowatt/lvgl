/**
 * @file lv_demo_ecg_util.c
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

LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_14);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_16);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_20);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_24);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_28);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_34);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_64);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_84);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_88);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_110);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_114);
LV_FONT_DECLARE(font_lv_demo_ecg_roboto_slab_174);

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void free_ctx_event_cb(lv_event_t * e);

/**********************
 *  STATIC VARIABLES
 **********************/

const lv_demo_ecg_sizes_t lv_demo_ecg_sizes_all[SIZE_COUNT] = {
    {
    },
    {
    }
};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_demo_ecg_base_obj_create(void)
{
    lv_demo_ecg_ctx_t * c = lv_malloc_zeroed(sizeof(lv_demo_ecg_ctx_t));
    LV_ASSERT_MALLOC(c);
    lv_obj_t * base_obj = lv_obj_create(lv_screen_active());
    lv_obj_set_user_data(base_obj, c);
    lv_obj_add_event_cb(base_obj, free_ctx_event_cb, LV_EVENT_DELETE, NULL);

    lv_display_t * disp = lv_display_get_default();
    int32_t hres = lv_display_get_horizontal_resolution(disp);
    int32_t vres = lv_display_get_vertical_resolution(disp);
    bool is_exact;
    int32_t size;
    if(hres < 1920 && vres < 1080) {
        is_exact = hres == 1280 && vres == 800;
        size = SIZE_SM;
    }
    else {
        is_exact = hres == 1920 && vres == 1080;
        size = SIZE_LG;
    }
    if(!is_exact) {
        LV_LOG_WARN("a display size of exactly 1280x800 or 1920x1080 is recommended for the ECG demo");
    }
    c->sz = &lv_demo_ecg_sizes_all[size];

    return base_obj;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void free_ctx_event_cb(lv_event_t * e)
{
    lv_obj_t * base_obj = lv_event_get_target_obj(e);
    lv_demo_ecg_ctx_t * c = lv_obj_get_user_data(base_obj);

    lv_free(c);
}

#endif /*LV_USE_DEMO_ECG*/
