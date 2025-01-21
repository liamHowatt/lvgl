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

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void free_ctx_event_cb(lv_event_t * e);
static void theme_observer_cb(lv_observer_t * observer, lv_subject_t * subject);

/**********************
 *  STATIC VARIABLES
 **********************/

const lv_demo_ecg_sizes_t lv_demo_ecg_sizes[SIZE_COUNT] = {
    {
        .font_disp_1 = &font_lv_demo_ecg_roboto_slab_110,
        .font_disp_2 = &font_lv_demo_ecg_roboto_slab_88,
        .font_disp_3 = &font_lv_demo_ecg_roboto_slab_64,
        .font_body_lg = &font_lv_demo_ecg_roboto_slab_20,
        .font_body_md = &font_lv_demo_ecg_roboto_slab_18,
        .font_body_sm = &font_lv_demo_ecg_roboto_slab_14,
        .font_caption = &font_lv_demo_ecg_roboto_slab_28
    },
    {
        .font_disp_1 = &font_lv_demo_ecg_roboto_slab_174,
        .font_disp_2 = &font_lv_demo_ecg_roboto_slab_114,
        .font_disp_3 = &font_lv_demo_ecg_roboto_slab_84,
        .font_body_lg = &font_lv_demo_ecg_roboto_slab_24,
        .font_body_md = &font_lv_demo_ecg_roboto_slab_22,
        .font_body_sm = &font_lv_demo_ecg_roboto_slab_16,
        .font_caption = &font_lv_demo_ecg_roboto_slab_34
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
    if(hres < 1920 && vres < 1080) {
        is_exact = hres == 1280 && vres == 800;
        c->sz = SIZE_SM;
    }
    else {
        is_exact = hres == 1920 && vres == 1080;
        c->sz = SIZE_LG;
    }
    if(!is_exact) {
        LV_LOG_WARN("a display size of exactly 1280x800 or 1920x1080 is recommended for the ECG demo");
    }

    for(int32_t i = 0; i < STYLE_COUNT; i++) {
        lv_style_init(&c->styles[i]);
    }

    lv_subject_init_int(&c->th, THEME_DARK);
    lv_subject_add_observer(&c->th, theme_observer_cb, c);

    return base_obj;
}

lv_obj_t * lv_demo_ecg_simple_container_create(lv_obj_t * parent, bool vertical, int32_t pad,
                                               lv_flex_align_t align_cross_place)
{
    lv_obj_t * obj = lv_obj_create(parent);
    lv_obj_remove_style_all(obj);
    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    if(vertical) {
        lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_row(obj, pad, 0);
    }
    else {
        lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_column(obj, pad, 0);
    }
    lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_START, align_cross_place, align_cross_place);
    return obj;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void free_ctx_event_cb(lv_event_t * e)
{
    lv_obj_t * base_obj = lv_event_get_target_obj(e);
    lv_demo_ecg_ctx_t * c = lv_obj_get_user_data(base_obj);

    lv_subject_deinit(&c->th);

    for(int32_t i = 0; i < STYLE_COUNT; i++) {
        lv_style_reset(&c->styles[i]);
    }

    lv_free(c);
}

static void theme_observer_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    lv_demo_ecg_ctx_t * c = lv_observer_get_user_data(observer);

    int32_t theme = lv_subject_get_int(subject);
    switch(theme) {
        case THEME_DARK:
            lv_style_set_bg_color(&c->styles[STYLE_OBJ], lv_color_hex(0x000000));
            lv_style_set_text_color(&c->styles[STYLE_LABEL], lv_color_hex(0xffffff));
            break;
    }

    for(int32_t i = 0; i < STYLE_COUNT; i++) {
        lv_obj_report_style_change(&c->styles[i]);
    }
}

#endif /*LV_USE_DEMO_ECG*/
