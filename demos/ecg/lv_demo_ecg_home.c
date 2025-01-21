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

void bottom_bar_create_line(lv_obj_t * bar);

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
    lv_obj_add_style(bg_cont, &c->styles[STYLE_OBJ], 0);
    lv_obj_set_size(bg_cont, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(bg_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(bg_cont, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(bg_cont, 24, 0);
    lv_obj_set_style_bg_opa(bg_cont, LV_OPA_COVER, 0);

    /* top bar */

    lv_obj_t * top_bar = lv_obj_create(bg_cont);
    lv_obj_remove_style_all(top_bar);
    lv_obj_add_style(top_bar, &c->styles[STYLE_OBJ], 0);
    lv_obj_set_size(top_bar, LV_PCT(100), 58);
    lv_obj_set_style_bg_opa(top_bar, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_hor(top_bar, 24, 0);
    lv_obj_set_flex_flow(top_bar, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(top_bar, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_shadow_color(top_bar, lv_color_white(), 0);
    lv_obj_set_style_shadow_width(top_bar, 106, 0);

    lv_obj_t * tb_left_cluster = lv_demo_ecg_simple_container_create(top_bar, false, 40, LV_FLEX_ALIGN_CENTER);
    lv_obj_t * label = lv_label_create(tb_left_cluster);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_sm, 0);
    lv_label_set_text_static(label, "Patient: John Doe | ID: 12345678");
    label = lv_label_create(tb_left_cluster);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_sm, 0);
    lv_label_set_text_static(label, "Not Admitted");
    label = lv_label_create(tb_left_cluster);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_sm, 0);
    lv_label_set_text_static(label, "ADULT");

    lv_obj_t * tb_mid_cluster = lv_demo_ecg_simple_container_create(top_bar, false, 24, LV_FLEX_ALIGN_CENTER);
    label = lv_label_create(tb_mid_cluster);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_sm, 0);
    lv_label_set_text_static(label, "Standard View");

    lv_obj_t * theme_selector_cluster = lv_demo_ecg_simple_container_create(tb_mid_cluster, false, 0, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_all(theme_selector_cluster, 5, 0);
    lv_obj_set_style_radius(theme_selector_cluster, 8, 0);
    lv_obj_set_style_border_width(theme_selector_cluster, 1, 0);
    lv_obj_set_style_border_color(theme_selector_cluster, lv_color_hex(0x7b7b7b), 0);

    lv_obj_t * light_button = lv_image_create(theme_selector_cluster);
    lv_image_set_src(light_button, &img_lv_demo_ecg_sun);
    lv_obj_set_style_image_recolor(light_button, lv_color_hex(0x919196), 0);
    lv_obj_set_size(light_button, 32, 32);
    lv_image_set_inner_align(light_button, LV_IMAGE_ALIGN_CENTER);

    lv_obj_t * dark_button = lv_image_create(theme_selector_cluster);
    lv_image_set_src(dark_button, &img_lv_demo_ecg_moon);
    lv_obj_set_style_image_recolor(dark_button, lv_color_hex(0x919196), 0);
    lv_obj_set_size(dark_button, 32, 32);
    lv_image_set_inner_align(dark_button, LV_IMAGE_ALIGN_CENTER);

    lv_obj_set_style_bg_color(dark_button, lv_color_hex(0xefefef), 0);
    lv_obj_set_style_bg_opa(dark_button, 255, 0);
    lv_obj_set_style_radius(dark_button, 6, 0);

    label = lv_label_create(theme_selector_cluster);
    lv_obj_set_style_text_color(label, lv_color_hex(0x71717a), 0);
    lv_obj_set_style_text_font(label, &font_lv_demo_ecg_roboto_slab_16, 0);
    lv_label_set_text_static(label, "Auto");
    lv_obj_set_style_pad_hor(label, 8, 0);

    lv_obj_t * tb_right_cluster = lv_demo_ecg_simple_container_create(top_bar, false, 8, LV_FLEX_ALIGN_CENTER);
    label = lv_label_create(tb_right_cluster);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_sm, 0);
    lv_label_set_text_static(label, "18 Jul 2024 10:56");

    lv_obj_t * battery = lv_image_create(tb_right_cluster);
    lv_image_set_src(battery, &img_lv_demo_ecg_battery);
    lv_obj_set_style_image_recolor(battery, lv_color_hex(0xffffff), 0);
    lv_obj_set_size(battery, 46, 38);
    lv_image_set_inner_align(battery, LV_IMAGE_ALIGN_CENTER);

    /* bottom bar */

    lv_obj_t * bottom_bar = lv_obj_create(bg_cont);
    lv_obj_remove_style_all(bottom_bar);
    lv_obj_add_style(bottom_bar, &c->styles[STYLE_OBJ], 0);
    lv_obj_set_size(bottom_bar, LV_PCT(100), 100);
    lv_obj_set_style_bg_opa(bottom_bar, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_hor(bottom_bar, 80, 0);
    lv_obj_set_flex_flow(bottom_bar, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(bottom_bar, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_shadow_color(bottom_bar, lv_color_white(), 0);
    lv_obj_set_style_shadow_width(bottom_bar, 106, 0);

    lv_obj_t * gear = lv_image_create(bottom_bar);
    lv_image_set_src(gear, &img_lv_demo_ecg_gear);
    lv_obj_set_style_image_recolor(gear, lv_color_hex(0xffffff), 0);
    lv_obj_set_size(gear, 88, 88);
    lv_image_set_inner_align(gear, LV_IMAGE_ALIGN_CENTER);

    bottom_bar_create_line(bottom_bar);

    lv_obj_t * electrodes_position = lv_demo_ecg_simple_container_create(bottom_bar, false, 24, LV_FLEX_ALIGN_CENTER);
    lv_obj_t * image = lv_image_create(electrodes_position);
    lv_image_set_src(image, &img_lv_demo_ecg_circuit);
    lv_obj_set_style_image_recolor(image, lv_color_hex(0xffffff), 0);
    label = lv_label_create(electrodes_position);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_md, 0);
    lv_label_set_text_static(label, "Electrodes\nPosition");

    bottom_bar_create_line(bottom_bar);

    lv_obj_t * patient_info = lv_demo_ecg_simple_container_create(bottom_bar, false, 24, LV_FLEX_ALIGN_CENTER);
    image = lv_image_create(patient_info);
    lv_image_set_src(image, &img_lv_demo_ecg_figure);
    lv_obj_set_style_image_recolor(image, lv_color_hex(0xffffff), 0);
    label = lv_label_create(patient_info);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_md, 0);
    lv_label_set_text_static(label, "Patient\nInfo.");

    bottom_bar_create_line(bottom_bar);

    lv_obj_t * change_view = lv_demo_ecg_simple_container_create(bottom_bar, false, 24, LV_FLEX_ALIGN_CENTER);
    image = lv_image_create(change_view);
    lv_image_set_src(image, &img_lv_demo_ecg_eye);
    lv_obj_set_style_image_recolor(image, lv_color_hex(0xffffff), 0);
    label = lv_label_create(change_view);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_md, 0);
    lv_label_set_text_static(label, "Change\nView");

    bottom_bar_create_line(bottom_bar);

    lv_obj_t * silence_alarm = lv_demo_ecg_simple_container_create(bottom_bar, false, 24, LV_FLEX_ALIGN_CENTER);
    image = lv_image_create(silence_alarm);
    lv_image_set_src(image, &img_lv_demo_ecg_alarm_disabled);
    lv_obj_set_style_image_recolor(image, lv_color_hex(0xffffff), 0);
    label = lv_label_create(silence_alarm);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_md, 0);
    lv_label_set_text_static(label, "Silence\nAlarm");
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

void bottom_bar_create_line(lv_obj_t * bar)
{
    lv_obj_t * divider = lv_line_create(bar);
    lv_obj_set_height(divider, LV_PCT(100));
    lv_obj_set_flex_grow(divider, 1);
    static const lv_point_precise_t points[] = {{LV_PCT(50), LV_PCT(19)}, {LV_PCT(50), LV_PCT(81)}};
    lv_line_set_points(divider, points, 2);
    lv_obj_set_style_line_width(divider, 2, 0);
    lv_obj_set_style_line_color(divider, lv_color_hex(0xb3b3b3), 0);
}

#endif /*LV_USE_DEMO_ECG*/
