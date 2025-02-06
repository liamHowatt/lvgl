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

static void theme_button_click_cb(lv_event_t * e);
static void theme_button_observer_cb(lv_observer_t * observer, lv_subject_t * subject);
static void create_no_graph_grid_cell(lv_demo_ecg_ctx_t * c,
                                      lv_obj_t * parent, int32_t col, int32_t row, lv_obj_t * icon_obj, const char * title_text,
                                      const char * big_text, lv_font_t * big_font_override, const char * upper_small_text,
                                      const char * lower_small_text, lv_color_t lower_small_text_color);
static void bottom_bar_create_line(lv_obj_t * bar);

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
    lv_obj_add_style(bg_cont, &c->styles[STYLE_CONTAINER_BG_MAIN_FRAME], 0);
    lv_obj_set_size(bg_cont, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(bg_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(bg_cont, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_top(bg_cont, 18, 0);
    lv_obj_set_style_pad_bottom(bg_cont, 30, 0);
    lv_obj_set_style_bg_opa(bg_cont, LV_OPA_COVER, 0);

    /* top bar */

    lv_obj_t * top_bar = lv_obj_create(bg_cont);
    lv_obj_remove_style_all(top_bar);
    lv_obj_set_size(top_bar, LV_PCT(100), 58);
    lv_obj_set_style_pad_hor(top_bar, 24, 0);
    lv_obj_set_flex_flow(top_bar, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(top_bar, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t * tb_left_cluster = lv_demo_ecg_simple_container_create(top_bar, false, 16, LV_FLEX_ALIGN_CENTER);

    lv_obj_t * logo = lv_image_create(tb_left_cluster);
    lv_image_set_src(logo, &img_lv_demo_ecg_logo);
    lv_obj_add_style(logo, &c->styles[STYLE_A8_IMG], 0);

    lv_obj_t * label = lv_label_create(tb_left_cluster);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, c->fonts[FONT_INTER_MEDIUM_16], 0);
    lv_label_set_text_static(label, "Patient: John Doe | ID: 12345678");
    lv_obj_set_style_pad_hor(label, 13, 0);

    lv_obj_t * figure_box = lv_demo_ecg_simple_container_create(tb_left_cluster, false, 6, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_hor(figure_box, 13, 0);
    lv_obj_t * figure_sm = lv_image_create(figure_box);
    lv_image_set_src(figure_sm, &img_lv_demo_ecg_figure_sm);
    lv_obj_add_style(figure_sm, &c->styles[STYLE_A8_IMG], 0);
    label = lv_label_create(figure_box);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, c->fonts[FONT_INTER_MEDIUM_16], 0);
    lv_label_set_text_static(label, "Adult");

    lv_obj_t * monitor_box = lv_demo_ecg_simple_container_create(tb_left_cluster, false, 6, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_hor(monitor_box, 13, 0);
    lv_obj_t * monitor = lv_image_create(monitor_box);
    lv_image_set_src(monitor, &img_lv_demo_ecg_monitor);
    lv_obj_add_style(monitor, &c->styles[STYLE_A8_IMG], 0);
    label = lv_label_create(monitor_box);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, c->fonts[FONT_INTER_MEDIUM_16], 0);
    lv_label_set_text_static(label, "4-Leads");

    lv_obj_t * theme_selector_cluster = lv_demo_ecg_simple_container_create(top_bar, false, 0, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_all(theme_selector_cluster, 5, 0);
    lv_obj_set_style_pad_column(theme_selector_cluster, 2, 0);
    lv_obj_set_style_radius(theme_selector_cluster, 8, 0);
    lv_obj_set_style_border_width(theme_selector_cluster, 1, 0);
    lv_obj_add_style(theme_selector_cluster, &c->styles[STYLE_BUTTON_BORDER_SOFT], 0);

    lv_obj_t * light_button = lv_image_create(theme_selector_cluster);
    lv_image_set_src(light_button, &img_lv_demo_ecg_sun);
    lv_obj_set_size(light_button, 32, 32);
    lv_image_set_inner_align(light_button, LV_IMAGE_ALIGN_CENTER);
    lv_obj_set_style_radius(light_button, 6, 0);
    lv_obj_add_flag(light_button, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(light_button, theme_button_click_cb, LV_EVENT_CLICKED, c);
    lv_obj_add_style(light_button, &c->styles[STYLE_CONTAINER_FILL_INVERT], 0);

    lv_obj_t * dark_button = lv_image_create(theme_selector_cluster);
    lv_image_set_src(dark_button, &img_lv_demo_ecg_moon);
    lv_obj_set_size(dark_button, 32, 32);
    lv_image_set_inner_align(dark_button, LV_IMAGE_ALIGN_CENTER);
    lv_obj_set_style_radius(dark_button, 6, 0);
    lv_obj_add_flag(dark_button, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(dark_button, theme_button_click_cb, LV_EVENT_CLICKED, c);
    lv_obj_add_style(dark_button, &c->styles[STYLE_CONTAINER_FILL_INVERT], 0);

    lv_subject_add_observer_obj(&c->th, theme_button_observer_cb, theme_selector_cluster, NULL);

    lv_obj_t * tb_right_cluster = lv_demo_ecg_simple_container_create(top_bar, false, 8, LV_FLEX_ALIGN_CENTER);

    label = lv_label_create(tb_right_cluster);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, c->fonts[FONT_INTER_MEDIUM_16], 0);
    lv_label_set_text_static(label, "18 Jul 2024 10:56");
    lv_obj_set_style_pad_hor(label, 13, 0);

    lv_obj_t * battery = lv_image_create(tb_right_cluster);
    lv_image_set_src(battery, &img_lv_demo_ecg_battery);
    lv_obj_add_style(battery, &c->styles[STYLE_A8_IMG], 0);
    lv_obj_set_size(battery, 46, 38);
    lv_image_set_inner_align(battery, LV_IMAGE_ALIGN_CENTER);

    /* main area */

    lv_obj_t * main_area = lv_tileview_create(bg_cont);
    lv_obj_set_style_bg_opa(main_area, LV_OPA_TRANSP, 0);
    lv_obj_set_width(main_area, LV_PCT(100));
    lv_obj_set_flex_grow(main_area, 1);

    lv_obj_t * no_graph_grid = lv_tileview_add_tile(main_area, 0, 0, LV_DIR_ALL);
    lv_obj_set_style_pad_hor(no_graph_grid, 24, 0);
    lv_obj_set_style_pad_ver(no_graph_grid, 8, 0);
    static const int32_t col_row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    lv_obj_set_style_grid_column_dsc_array(no_graph_grid, col_row_dsc, 0);
    lv_obj_set_style_grid_row_dsc_array(no_graph_grid, col_row_dsc, 0);
    lv_obj_set_style_pad_gap(no_graph_grid, 11, 0);
    lv_obj_set_layout(no_graph_grid, LV_LAYOUT_GRID);

    lv_obj_t * heart = lv_image_create(lv_screen_active());
    lv_image_set_src(heart, &img_lv_demo_ecg_heart);
    lv_obj_set_style_image_recolor(heart, lv_color_hex(0x00a53d), 0);
    create_no_graph_grid_cell(c, no_graph_grid, 0, 0, heart, "HEART RATE",        "122", NULL,      "120-50", "BPM", lv_color_hex(0x00a53d));
    heart = lv_image_create(lv_screen_active());
    lv_image_set_src(heart, &img_lv_demo_ecg_heart);
    lv_obj_set_style_image_recolor(heart, lv_color_hex(0x00b3ca), 0);
    create_no_graph_grid_cell(c, no_graph_grid, 1, 0, heart, "PLETH %",           "95", NULL,       "100-90", "SpO2", lv_color_hex(0x00b3ca));
    // create_no_graph_grid_cell(c, no_graph_grid, 0, 1, NULL, "ARTERIAL PRESSURE", "120/\n70", NULL, "100-90", "MAP: 90", lv_color_hex(0xe55213));
    // create_no_graph_grid_cell(c, no_graph_grid, 1, 1, NULL, "RESPIRATORY RATE",  "15", NULL,       "30-5", "RPM", lv_color_hex(0));

    // for(int i = 0; i < 2; i++) {
    //     for(int j = 0; j < 2; j++) {
    //         lv_obj_t * cell = lv_obj_create(no_graph_grid);
    //         lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, i, 1,
    //                              LV_GRID_ALIGN_STRETCH, j, 1);
    //     }
    // }

    // lv_obj_set_style_pad_left(main_area, PRIM_L, 0);
    // lv_obj_set_style_pad_right(main_area, PRIM_XL, 0);
    // lv_obj_set_style_pad_column(main_area, PRIM_L, 0);
    // lv_obj_set_flex_flow(main_area, LV_FLEX_FLOW_ROW);
    // lv_obj_set_flex_align(main_area, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    // lv_obj_t * right_col_1 = lv_obj_create(main_area);
    // lv_obj_remove_style_all(right_col_1);
    // lv_obj_set_size(right_col_1, 340, LV_PCT(100));
    // lv_obj_set_flex_flow(right_col_1, LV_FLEX_FLOW_COLUMN);
    // lv_obj_set_flex_align(right_col_1, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    // lv_obj_t * cont = lv_obj_create(right_col_1);
    // lv_obj_remove_style_all(cont);
    // lv_obj_set_width(cont, LV_PCT(100));
    // lv_obj_set_flex_grow(cont, 1);
    // label = lv_label_create(cont);
    // lv_label_set_text_static(label, "HR");
    // lv_obj_set_align(label, LV_ALIGN_TOP_LEFT);
    // lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    // lv_obj_set_style_text_color(label, lv_color_hex(0x4ade80), 0);
    // label = lv_label_create(cont);
    // lv_label_set_text_static(label, "120\n60");
    // lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, 0);
    // lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 0, LV_PCT(-7));
    // lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    // lv_obj_set_style_text_color(label, lv_color_hex(0x67e8f9), 0);
    // label = lv_label_create(cont);
    // lv_label_set_text_static(label, "60");
    // lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    // lv_obj_align(label, LV_ALIGN_RIGHT_MID, 0, 0);
    // lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_disp_1, 0);
    // lv_obj_set_style_text_color(label, lv_color_hex(0x4ade80), 0);
    // lv_obj_set_width(label, LV_PCT(86));

    // cont = lv_obj_create(right_col_1);
    // lv_obj_remove_style_all(cont);
    // lv_obj_set_width(cont, LV_PCT(100));
    // lv_obj_set_flex_grow(cont, 1);
    // label = lv_label_create(cont);
    // lv_label_set_text_static(label, "SpO2");
    // lv_obj_set_align(label, LV_ALIGN_TOP_LEFT);
    // lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    // lv_obj_set_style_text_color(label, lv_color_hex(0x67e8f9), 0);
    // label = lv_label_create(cont);
    // lv_label_set_text_static(label, "120\n60");
    // lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, 0);
    // lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 0, LV_PCT(-7));
    // lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    // lv_obj_set_style_text_color(label, lv_color_hex(0x67e8f9), 0);
    // label = lv_label_create(cont);
    // lv_label_set_text_static(label, "95");
    // lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    // lv_obj_align(label, LV_ALIGN_RIGHT_MID, 0, 0);
    // lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_disp_1, 0);
    // lv_obj_set_style_text_color(label, lv_color_hex(0x67e8f9), 0);
    // lv_obj_set_width(label, LV_PCT(86));

    // cont = lv_obj_create(right_col_1);
    // lv_obj_remove_style_all(cont);
    // lv_obj_set_width(cont, LV_PCT(100));
    // lv_obj_set_flex_grow(cont, 1);
    // label = lv_label_create(cont);
    // lv_label_set_text_static(label, "ART");
    // lv_obj_set_align(label, LV_ALIGN_TOP_LEFT);
    // lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    // lv_obj_set_style_text_color(label, lv_color_hex(0xFF733B), 0);
    // lv_obj_t * lab_cont = lv_demo_ecg_simple_container_create(cont, false, 0, LV_FLEX_ALIGN_CENTER);
    // lv_obj_align(lab_cont, LV_ALIGN_BOTTOM_LEFT, 0, LV_PCT(-7));
    // label = lv_label_create(lab_cont);
    // lv_label_set_text_static(label, "120\n60");
    // lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, 0);
    // lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    // lv_obj_set_style_text_color(label, lv_color_hex(0xFF733B), 0);
    // // label = lv_label_create(lab_cont);
    // // lv_label_set_text_static(label, "(90)");
    // // lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_disp_3, 0);
    // // lv_obj_set_style_text_color(label, lv_color_hex(0xFF733B), 0);
    // label = lv_label_create(cont);
    // lv_label_set_text_static(label, "120/\n70");
    // lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    // lv_obj_align(label, LV_ALIGN_RIGHT_MID, 0, 0);
    // lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_disp_3, 0);
    // lv_obj_set_style_text_color(label, lv_color_hex(0xFF733B), 0);
    // lv_obj_set_width(label, LV_PCT(86));

    // cont = lv_obj_create(right_col_1);
    // lv_obj_remove_style_all(cont);
    // lv_obj_set_width(cont, LV_PCT(100));
    // lv_obj_set_flex_grow(cont, 1);
    // label = lv_label_create(cont);
    // lv_label_set_text_static(label, "RR");
    // lv_obj_set_align(label, LV_ALIGN_TOP_LEFT);
    // lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    // lv_obj_set_style_text_color(label, lv_color_hex(0xF8E671), 0);
    // label = lv_label_create(cont);
    // lv_label_set_text_static(label, "120\n60");
    // lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, 0);
    // lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 0, LV_PCT(-7));
    // lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    // lv_obj_set_style_text_color(label, lv_color_hex(0x67e8f9), 0);
    // label = lv_label_create(cont);
    // lv_label_set_text_static(label, "15");
    // lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    // lv_obj_align(label, LV_ALIGN_RIGHT_MID, 0, 0);
    // lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_disp_1, 0);
    // lv_obj_set_style_text_color(label, lv_color_hex(0xF8E671), 0);
    // lv_obj_set_width(label, LV_PCT(86));

    /* bottom bar */

    lv_obj_t * bottom_bar = lv_obj_create(bg_cont);
    lv_obj_remove_style_all(bottom_bar);
    lv_obj_set_size(bottom_bar, LV_PCT(100), 72);
    lv_obj_set_style_pad_hor(bottom_bar, 40, 0);
    lv_obj_set_flex_flow(bottom_bar, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(bottom_bar, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // lv_obj_t * gear = lv_image_create(bottom_bar);
    // lv_image_set_src(gear, &img_lv_demo_ecg_gear);
    // lv_obj_add_style(gear, &c->styles[STYLE_A8_IMG], 0);
    // lv_obj_set_size(gear, 88, 88);
    // lv_image_set_inner_align(gear, LV_IMAGE_ALIGN_CENTER);

    // bottom_bar_create_line(bottom_bar);

    // lv_obj_t * electrodes_position = lv_demo_ecg_simple_container_create(bottom_bar, false, 24, LV_FLEX_ALIGN_CENTER);
    // lv_obj_t * image = lv_image_create(electrodes_position);
    // lv_image_set_src(image, &img_lv_demo_ecg_circuit);
    // lv_obj_add_style(image, &c->styles[STYLE_A8_IMG], 0);
    // label = lv_label_create(electrodes_position);
    // lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    // lv_obj_set_style_text_font(label, c->fonts[FONT_INTER_MEDIUM_16], 0);
    // lv_label_set_text_static(label, "Electrodes\nPosition");

    // bottom_bar_create_line(bottom_bar);

    // lv_obj_t * patient_info = lv_demo_ecg_simple_container_create(bottom_bar, false, 24, LV_FLEX_ALIGN_CENTER);
    // image = lv_image_create(patient_info);
    // lv_image_set_src(image, &img_lv_demo_ecg_figure);
    // lv_obj_add_style(image, &c->styles[STYLE_A8_IMG], 0);
    // label = lv_label_create(patient_info);
    // lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    // lv_obj_set_style_text_font(label, c->fonts[FONT_INTER_MEDIUM_16], 0);
    // lv_label_set_text_static(label, "Patient\nInfo.");

    // bottom_bar_create_line(bottom_bar);

    // lv_obj_t * change_view = lv_demo_ecg_simple_container_create(bottom_bar, false, 24, LV_FLEX_ALIGN_CENTER);
    // image = lv_image_create(change_view);
    // lv_image_set_src(image, &img_lv_demo_ecg_eye);
    // lv_obj_add_style(image, &c->styles[STYLE_A8_IMG], 0);
    // label = lv_label_create(change_view);
    // lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    // lv_obj_set_style_text_font(label, c->fonts[FONT_INTER_MEDIUM_16], 0);
    // lv_label_set_text_static(label, "Change\nView");

    // bottom_bar_create_line(bottom_bar);

    // lv_obj_t * silence_alarm = lv_demo_ecg_simple_container_create(bottom_bar, false, 24, LV_FLEX_ALIGN_CENTER);
    // image = lv_image_create(silence_alarm);
    // lv_image_set_src(image, &img_lv_demo_ecg_alarm_disabled);
    // lv_obj_add_style(image, &c->styles[STYLE_A8_IMG], 0);
    // label = lv_label_create(silence_alarm);
    // lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    // lv_obj_set_style_text_font(label, c->fonts[FONT_INTER_MEDIUM_16], 0);
    // lv_label_set_text_static(label, "Silence\nAlarm");
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void theme_button_click_cb(lv_event_t * e)
{
    lv_demo_ecg_ctx_t * c = lv_event_get_user_data(e);
    lv_obj_t * clicked_button = lv_event_get_target_obj(e);
    lv_obj_t * cluster = lv_obj_get_parent(clicked_button);
    lv_obj_t * light_button = lv_obj_get_child(cluster, 0);
    lv_subject_set_int(&c->th, clicked_button == light_button ? THEME_LIGHT : THEME_DARK);
}

static void theme_button_observer_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    lv_obj_t * cluster = lv_observer_get_target_obj(observer);
    int32_t active_theme = lv_subject_get_int(subject);
    lv_obj_t * light_button = lv_obj_get_child(cluster, 0);
    lv_obj_t * dark_button = lv_obj_get_child(cluster, 1);

    if(active_theme == THEME_LIGHT) {
        lv_obj_set_style_bg_opa(light_button, LV_OPA_COVER, 0);
        lv_obj_set_style_bg_opa(dark_button, LV_OPA_TRANSP, 0);
        lv_obj_set_style_image_recolor(light_button, lv_color_hex(0xf6f6f6), 0);
        lv_obj_set_style_image_recolor(dark_button, lv_color_hex3(0x888), 0);
    }
    else {
        lv_obj_set_style_bg_opa(light_button, LV_OPA_TRANSP, 0);
        lv_obj_set_style_bg_opa(dark_button, LV_OPA_COVER, 0);
        lv_obj_set_style_image_recolor(light_button, lv_color_hex3(0x888), 0);
        lv_obj_set_style_image_recolor(dark_button, lv_color_hex3(0x000), 0);
    }
}

static void create_no_graph_grid_cell(lv_demo_ecg_ctx_t * c,
                                      lv_obj_t * parent, int32_t col, int32_t row, lv_obj_t * icon_obj, const char * title_text,
                                      const char * big_text, lv_font_t * big_font_override, const char * upper_small_text,
                                      const char * lower_small_text, lv_color_t lower_small_text_color)
{
    lv_obj_t * cell = lv_obj_create(parent);
    lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, col, 1, LV_GRID_ALIGN_STRETCH, row, 1);
    lv_obj_set_style_border_opa(cell, LV_OPA_TRANSP, 0);
    lv_obj_set_style_radius(cell, 8, 0);
    lv_obj_set_style_pad_all(cell, 0, 0);
    lv_obj_add_style(cell, &c->styles[STYLE_CONTAINER_BG_PRIMARY], 0);

    lv_obj_t * title_box = lv_demo_ecg_simple_container_create(cell, false, 16, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_hor(title_box, 27, 0);
    lv_obj_set_parent(icon_obj, title_box);
    lv_obj_align(title_box, LV_ALIGN_TOP_LEFT, 0, LV_PCT(5));
    lv_obj_t * label = lv_label_create(title_box);
    lv_label_set_text_static(label, title_text);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, c->fonts[FONT_QUICKSAND_MEDIUM_22], 0);

    lv_obj_t * grid = lv_obj_create(cell);
    lv_obj_remove_style_all(grid);
    lv_obj_set_size(grid, LV_PCT(100), LV_PCT(100));
    static const int32_t col_dsc[] = {LV_GRID_FR(71), LV_GRID_FR(29), LV_GRID_TEMPLATE_LAST};
    static const int32_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    lv_obj_set_style_grid_column_dsc_array(grid, col_dsc, 0);
    lv_obj_set_style_grid_column_dsc_array(grid, row_dsc, 0);
    lv_obj_set_style_pad_gap(grid, 0, 0);
    lv_obj_set_layout(grid, LV_LAYOUT_GRID);

    lv_obj_t * big_label = lv_label_create(grid);
    // lv_obj_add_style(big_label, &c->styles[STYLE_LABEL], 0);
    // lv_obj_set_style_text_font(big_label, big_font_override ? big_font_override : c->fonts[FONT_QUICKSAND_LIGHT_290], 0);
    // lv_label_set_text_static(big_label, big_text);
    // lv_obj_set_style_text_align(big_label, LV_TEXT_ALIGN_RIGHT, 0);
    // lv_obj_set_grid_cell(big_label, LV_GRID_ALIGN_END, 0, 1, LV_GRID_ALIGN_END, 0, 1);
}

static void bottom_bar_create_line(lv_obj_t * bar)
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
