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

const int32_t lv_demo_ecg_sizes[DISP_SIZE_COUNT][SIZE_COUNT] = {
    [DISP_SIZE_SM] = {
        [SIZE_FONT_DISPLAY_BIG_NUMERIC_XL] = 280,
        [SIZE_FONT_DISPLAY_BIG_NUMERIC_M] = 124,
        [SIZE_FONT_DISPLAY_BIG_NUMERIC_S] = 94,
        [SIZE_FONT_DISPLAY_STANDARD_XL] = 128,
        [SIZE_FONT_DISPLAY_STANDARD_L] = 90,
        [SIZE_FONT_DISPLAY_STANDARD_M] = 64,
        [SIZE_FONT_DISPLAY_STANDARD_S] = 48,
        [SIZE_FONT_HEADER_H4] = 12,
        [SIZE_FONT_BODY_L] = 18,
        [SIZE_FONT_BODY_S] = 12,
        [SIZE_FONT_LABEL_STANDARD] = 18,
        [SIZE_FONT_LABEL_BIG_NUMERIC] = 24
    },
    [DISP_SIZE_LG] = {
        [SIZE_FONT_DISPLAY_BIG_NUMERIC_XL] = 367,
        [SIZE_FONT_DISPLAY_BIG_NUMERIC_M] = 168,
        [SIZE_FONT_DISPLAY_BIG_NUMERIC_S] = 128,
        [SIZE_FONT_DISPLAY_STANDARD_XL] = 186,
        [SIZE_FONT_DISPLAY_STANDARD_L] = 114,
        [SIZE_FONT_DISPLAY_STANDARD_M] = 82,
        [SIZE_FONT_DISPLAY_STANDARD_S] = 64,
        [SIZE_FONT_HEADER_H4] = 16,
        [SIZE_FONT_BODY_L] = 22,
        [SIZE_FONT_BODY_S] = 16,
        [SIZE_FONT_LABEL_STANDARD] = 22,
        [SIZE_FONT_LABEL_BIG_NUMERIC] = 34
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
        c->sz = DISP_SIZE_SM;
    }
    else {
        is_exact = hres == 1920 && vres == 1080;
        c->sz = DISP_SIZE_LG;
    }
    if(!is_exact) {
        LV_LOG_WARN("a display size of exactly 1280x800 or 1920x1080 is recommended for the ECG demo");
    }

    c->fonts[FONT_DISPLAY_BIG_NUMERIC_XL] = lv_tiny_ttf_create_file("Quicksand-Bold.ttf", lv_demo_ecg_sizes[c->sz][SIZE_FONT_DISPLAY_BIG_NUMERIC_XL]);
    c->fonts[FONT_DISPLAY_BIG_NUMERIC_M] = lv_tiny_ttf_create_file("Quicksand-Bold.ttf", lv_demo_ecg_sizes[c->sz][SIZE_FONT_DISPLAY_BIG_NUMERIC_M]);
    c->fonts[FONT_DISPLAY_BIG_NUMERIC_S] = lv_tiny_ttf_create_file("Quicksand-Light.ttf", lv_demo_ecg_sizes[c->sz][SIZE_FONT_DISPLAY_BIG_NUMERIC_S]);
    c->fonts[FONT_DISPLAY_STANDARD_XL] = lv_tiny_ttf_create_file("Quicksand-Regular.ttf", lv_demo_ecg_sizes[c->sz][SIZE_FONT_DISPLAY_STANDARD_XL]);
    c->fonts[FONT_DISPLAY_STANDARD_L] = lv_tiny_ttf_create_file("Quicksand-Light.ttf", lv_demo_ecg_sizes[c->sz][SIZE_FONT_DISPLAY_STANDARD_L]);
    c->fonts[FONT_DISPLAY_STANDARD_M] = lv_tiny_ttf_create_file("Quicksand-SemiBold.ttf", lv_demo_ecg_sizes[c->sz][SIZE_FONT_DISPLAY_STANDARD_M]);
    c->fonts[FONT_DISPLAY_STANDARD_S] = lv_tiny_ttf_create_file("Quicksand-Light.ttf", lv_demo_ecg_sizes[c->sz][SIZE_FONT_DISPLAY_STANDARD_S]);
    c->fonts[FONT_HEADER_H4] = lv_tiny_ttf_create_file("Quicksand-Medium.ttf", lv_demo_ecg_sizes[c->sz][SIZE_FONT_HEADER_H4]);
    c->fonts[FONT_BODY_L] = lv_tiny_ttf_create_file("Inter_18pt-Regular.ttf", lv_demo_ecg_sizes[c->sz][SIZE_FONT_BODY_L]);
    c->fonts[FONT_BODY_S] = lv_tiny_ttf_create_file("Inter_18pt-Medium.ttf", lv_demo_ecg_sizes[c->sz][SIZE_FONT_BODY_S]);
    c->fonts[FONT_LABEL_STANDARD_LARGE] = lv_tiny_ttf_create_file("Quicksand-SemiBold.ttf", lv_demo_ecg_sizes[c->sz][SIZE_FONT_LABEL_STANDARD]);
    c->fonts[FONT_LABEL_STANDARD_SMALL] = lv_tiny_ttf_create_file("Quicksand-Medium.ttf", lv_demo_ecg_sizes[c->sz][SIZE_FONT_LABEL_STANDARD]);
    c->fonts[FONT_LABEL_BIG_NUMERIC_LARGE] = lv_tiny_ttf_create_file("Quicksand-SemiBold.ttf", lv_demo_ecg_sizes[c->sz][SIZE_FONT_LABEL_BIG_NUMERIC]);
    c->fonts[FONT_LABEL_BIG_NUMERIC_SMALL] = lv_tiny_ttf_create_file("Quicksand-Medium.ttf", lv_demo_ecg_sizes[c->sz][SIZE_FONT_LABEL_BIG_NUMERIC]);

    c->fonts[FONT_QUICKSAND_LIGHT_290] = lv_tiny_ttf_create_file("Quicksand-Light.ttf", 290);
    c->fonts[FONT_QUICKSAND_LIGHT_140] = lv_tiny_ttf_create_file("Quicksand-Light.ttf", 140);
    c->fonts[FONT_QUICKSAND_LIGHT_120] = lv_tiny_ttf_create_file("Quicksand-Light.ttf", 120);
    c->fonts[FONT_QUICKSAND_LIGHT_80] = lv_tiny_ttf_create_file("Quicksand-Light.ttf", 80);
    c->fonts[FONT_QUICKSAND_BOLD_27] = lv_tiny_ttf_create_file("Quicksand-Bold.ttf", 27);
    c->fonts[FONT_QUICKSAND_MEDIUM_24] = lv_tiny_ttf_create_file("Quicksand-Medium.ttf", 24);
    c->fonts[FONT_QUICKSAND_MEDIUM_22] = lv_tiny_ttf_create_file("Quicksand-Medium.ttf", 22);
    c->fonts[FONT_INTER_MEDIUM_20] = lv_tiny_ttf_create_file("Inter_18pt-Medium.ttf", 20);
    c->fonts[FONT_INTER_MEDIUM_16] = lv_tiny_ttf_create_file("Inter_18pt-Medium.ttf", 16);

    for(int32_t i = 0; i < FONT_COUNT; i++) {
        LV_ASSERT_NULL(c->fonts[i]);
    }

    for(int32_t i = 0; i < STYLE_COUNT; i++) {
        lv_style_init(&c->styles[i]);
    }

    lv_subject_init_int(&c->th, THEME_LIGHT);
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

    for(uint32_t i = 0; i < FONT_COUNT; i++) {
        lv_tiny_ttf_destroy(c->fonts[i]);
    }

    lv_free(c);
}

static void theme_observer_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    lv_demo_ecg_ctx_t * c = lv_observer_get_user_data(observer);

    int32_t theme = lv_subject_get_int(subject);
    switch(theme) {
        case THEME_LIGHT:
            lv_style_set_bg_color(&c->styles[STYLE_CONTAINER_BG_MAIN_FRAME], lv_color_hex(0xd8d9da));
            lv_style_set_text_color(&c->styles[STYLE_LABEL], lv_color_hex(0x000000));
            lv_style_set_image_recolor(&c->styles[STYLE_A8_IMG], lv_color_hex(0x000000));
            lv_style_set_border_color(&c->styles[STYLE_BUTTON_BORDER_SOFT], lv_color_hex(0xb8b8b8));
            lv_style_set_bg_color(&c->styles[STYLE_CONTAINER_FILL_INVERT], lv_color_hex(0x292929));
            lv_style_set_bg_color(&c->styles[STYLE_CONTAINER_BG_PRIMARY], lv_color_hex(0xf6f6f6));
            lv_style_set_bg_color(&c->styles[STYLE_ICON_FILL_INVERT], lv_color_hex(0x808080));
            break;
        case THEME_DARK:
            lv_style_set_bg_color(&c->styles[STYLE_CONTAINER_BG_MAIN_FRAME], lv_color_hex(0x000000));
            lv_style_set_text_color(&c->styles[STYLE_LABEL], lv_color_hex(0xffffff));
            lv_style_set_image_recolor(&c->styles[STYLE_A8_IMG], lv_color_hex(0xf6f6f6));
            lv_style_set_border_color(&c->styles[STYLE_BUTTON_BORDER_SOFT], lv_color_hex(0xd6d6d6));
            lv_style_set_bg_color(&c->styles[STYLE_CONTAINER_FILL_INVERT], lv_color_hex(0xf6f6f6));
            lv_style_set_bg_color(&c->styles[STYLE_CONTAINER_BG_PRIMARY], lv_color_hex(0x292929));
            lv_style_set_bg_color(&c->styles[STYLE_ICON_FILL_INVERT], lv_color_hex(0xd1d1d1));
            break;
    }

    for(int32_t i = 0; i < STYLE_COUNT; i++) {
        lv_obj_report_style_change(&c->styles[i]);
    }
}

#endif /*LV_USE_DEMO_ECG*/
