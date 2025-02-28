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
static void fill_chart_data(lv_obj_t * chart);
static lv_obj_t * create_labeled_big_number(lv_demo_ecg_ctx_t * c, lv_obj_t * parent, const char * big_text,
                                            lv_font_t * big_font, const char * upper_small_text,
                                            const char * lower_small_text, lv_color_t lower_small_text_color,
                                            int32_t small_label_box_pad_bottom);
static void create_no_graph_grid_cell(lv_demo_ecg_ctx_t * c,
                                      lv_obj_t * parent, int32_t col, int32_t row, lv_obj_t * icon_obj, const char * title_text,
                                      const char * big_text, lv_font_t * big_font_override, const char * upper_small_text,
                                      const char * lower_small_text, lv_color_t lower_small_text_color);
static void bottom_bar_create_line(lv_obj_t * bar);
static void popup_x_clicked_cb(lv_event_t * e);
static void create_lead(lv_demo_ecg_ctx_t * c, lv_obj_t * parent, lv_color_t symbol_color, const char * symbol_text, const char * main_text, const char * sub_text);
static void leads_placement_popup(lv_event_t * e);
static void show_patient_info(lv_event_t * e);
static void textarea_clicked_cb(lv_event_t * e);
static lv_obj_t * patient_info_input(lv_demo_ecg_ctx_t * c, lv_obj_t * grid, lv_obj_t * kb, int32_t col, int32_t row, const char * text, lv_obj_t * field_obj);

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
    lv_obj_set_style_opa(main_area, LV_OPA_TRANSP, LV_PART_SCROLLBAR);

    lv_obj_t * twelve_leads_box = lv_tileview_add_tile(main_area, 0, 0, LV_DIR_ALL);
    lv_obj_set_style_pad_hor(twelve_leads_box, 24, 0);
    lv_obj_set_style_pad_ver(twelve_leads_box, 8, 0);
    lv_obj_t * twelve_leads = lv_obj_create(twelve_leads_box);
    lv_obj_set_size(twelve_leads, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_border_opa(twelve_leads, LV_OPA_TRANSP, 0);
    lv_obj_set_style_radius(twelve_leads, 24, 0);
    lv_obj_set_style_pad_all(twelve_leads, 0, 0);
    lv_obj_add_style(twelve_leads, &c->styles[STYLE_CONTAINER_BG_PRIMARY], 0);
    lv_obj_remove_flag(twelve_leads, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t * twelve_leads_grid = lv_obj_create(twelve_leads);
    lv_obj_remove_style_all(twelve_leads_grid);
    lv_obj_set_size(twelve_leads_grid, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align(twelve_leads_grid, LV_ALIGN_LEFT_MID, 32, 0);
    static const int32_t col_dsc[] = {395, 395, LV_GRID_TEMPLATE_LAST};
    static const int32_t row_dsc[] = {61, 61, 61, 61, 61, 61, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_style_grid_column_dsc_array(twelve_leads_grid, col_dsc, 0);
    lv_obj_set_style_grid_row_dsc_array(twelve_leads_grid, row_dsc, 0);
    lv_obj_set_style_pad_gap(twelve_leads_grid, 32, 0);
    lv_obj_set_layout(twelve_leads_grid, LV_LAYOUT_GRID);

    for(int col = 0; col < 2; col++) {
        for(int row = 0; row < 6; row++) {
            // lv_obj_t * obj = lv_obj_create(twelve_leads_grid);
            lv_obj_t * obj = lv_chart_create(twelve_leads_grid);
            lv_obj_set_style_border_width(obj, 0, 0);
            lv_obj_set_style_pad_all(obj, 0, 0);
            lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, col, 1, LV_GRID_ALIGN_STRETCH, row, 1);
            lv_obj_set_style_size(obj, 0, 0, LV_PART_INDICATOR);
            fill_chart_data(obj);
        }
    }

    lv_obj_t * twelve_leads_upper_labaled_big_number = create_labeled_big_number(c, twelve_leads, "60", c->fonts[FONT_QUICKSAND_LIGHT_120], "120-50", "BPM", lv_color_hex(0x15803c), 25);
    lv_obj_align(twelve_leads_upper_labaled_big_number, LV_ALIGN_TOP_RIGHT, -64, 32);

    lv_obj_t * twelve_leads_lower_labaled_big_number = create_labeled_big_number(c, twelve_leads, "120/\n70", c->fonts[FONT_QUICKSAND_LIGHT_80], "120-50", "MAP: 90", lv_color_hex(0), 15);
    lv_obj_align(twelve_leads_lower_labaled_big_number, LV_ALIGN_TOP_RIGHT, -64, 180);

    lv_obj_t * twelve_leads_arc = lv_arc_create(twelve_leads);
    lv_obj_align(twelve_leads_arc, LV_ALIGN_BOTTOM_RIGHT, -50, -50);
    lv_obj_set_style_pad_all(twelve_leads_arc, 0, LV_PART_KNOB);
    lv_obj_add_style(twelve_leads_arc, &c->styles[STYLE_ICON_FILL_INVERT], LV_PART_KNOB);

    lv_obj_t * four_leads_box = lv_tileview_add_tile(main_area, 1, 0, LV_DIR_ALL);
    lv_obj_set_style_pad_hor(four_leads_box, 24, 0);
    lv_obj_set_style_pad_ver(four_leads_box, 8, 0);
    lv_obj_t * four_leads = lv_obj_create(four_leads_box);
    lv_obj_set_size(four_leads, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_border_opa(four_leads, LV_OPA_TRANSP, 0);
    lv_obj_set_style_radius(four_leads, 14, 0);
    lv_obj_set_style_pad_all(four_leads, 0, 0);
    lv_obj_add_style(four_leads, &c->styles[STYLE_CONTAINER_BG_PRIMARY], 0);
    lv_obj_remove_flag(four_leads, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t * four_leads_grid = lv_obj_create(four_leads);
    lv_obj_remove_style_all(four_leads_grid);
    lv_obj_set_size(four_leads_grid, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align(four_leads_grid, LV_ALIGN_LEFT_MID, 32, 0);
    static const int32_t four_leads_col_dsc[] = {684, LV_GRID_TEMPLATE_LAST};
    static const int32_t four_leads_row_dsc[] = {106, 106, 106, 106, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_style_grid_column_dsc_array(four_leads_grid, four_leads_col_dsc, 0);
    lv_obj_set_style_grid_row_dsc_array(four_leads_grid, four_leads_row_dsc, 0);
    lv_obj_set_style_pad_gap(four_leads_grid, 40, 0);
    lv_obj_set_layout(four_leads_grid, LV_LAYOUT_GRID);

    for(int row = 0; row < 4; row++) {
        // lv_obj_t * obj = lv_obj_create(four_leads_grid);
        lv_obj_t * obj = lv_chart_create(four_leads_grid);
        lv_obj_set_style_border_width(obj, 0, 0);
        lv_obj_set_style_pad_all(obj, 0, 0);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, row, 1);
        lv_obj_set_style_size(obj, 0, 0, LV_PART_INDICATOR);
        fill_chart_data(obj);
    }

    lv_obj_t * four_leads_labeled_big_number_1 = create_labeled_big_number(c, four_leads, "120", c->fonts[FONT_QUICKSAND_LIGHT_120], "120-50", "BPM", lv_color_hex(0), 25);
    lv_obj_align(four_leads_labeled_big_number_1, LV_ALIGN_TOP_RIGHT, -230, 32);

    lv_obj_t * four_leads_labeled_big_number_2 = create_labeled_big_number(c, four_leads, "160", c->fonts[FONT_QUICKSAND_LIGHT_120], "120-50", "SpO2", lv_color_hex(0), 25);
    lv_obj_align(four_leads_labeled_big_number_2, LV_ALIGN_TOP_RIGHT, -230, 150);

    lv_obj_t * four_leads_labeled_big_number_3 = create_labeled_big_number(c, four_leads, "120/\n70", c->fonts[FONT_QUICKSAND_LIGHT_80], "120-50", "MAP:90", lv_color_hex(0), 15);
    lv_obj_align(four_leads_labeled_big_number_3, LV_ALIGN_TOP_RIGHT, -230, 280);

    lv_obj_t * four_leads_labeled_big_number_4 = create_labeled_big_number(c, four_leads, "60", c->fonts[FONT_QUICKSAND_LIGHT_120], "120-50", "RPM", lv_color_hex(0), 25);
    lv_obj_align(four_leads_labeled_big_number_4, LV_ALIGN_TOP_RIGHT, -230, 450);

    lv_obj_t * no_graph_grid = lv_tileview_add_tile(main_area, 2, 0, LV_DIR_ALL);
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
    create_no_graph_grid_cell(c, no_graph_grid, 0, 1, NULL, "ARTERIAL PRESSURE", "120/\n70", c->fonts[FONT_QUICKSAND_LIGHT_140], "100-90", "MAP: 90", lv_color_hex(0xe55213));
    create_no_graph_grid_cell(c, no_graph_grid, 1, 1, NULL, "RESPIRATORY RATE",  "15", NULL,       "30-5", "RPM", lv_color_hex(0));

    lv_tileview_set_tile(main_area, four_leads_box, LV_ANIM_OFF);

    /* bottom bar */

    lv_obj_t * bottom_bar = lv_obj_create(bg_cont);
    lv_obj_remove_style_all(bottom_bar);
    lv_obj_set_size(bottom_bar, LV_PCT(100), 72);
    lv_obj_set_style_pad_hor(bottom_bar, 40, 0);
    lv_obj_set_style_pad_bottom(bottom_bar, 30, 0);
    lv_obj_set_flex_flow(bottom_bar, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(bottom_bar, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t * gear = lv_image_create(bottom_bar);
    lv_image_set_inner_align(gear, LV_IMAGE_ALIGN_CENTER);
    lv_image_set_src(gear, &img_lv_demo_ecg_gear);
    lv_obj_set_width(gear, 58);
    lv_obj_add_style(gear, &c->styles[STYLE_A8_IMG], 0);

    lv_obj_t * bottom_navbar = lv_demo_ecg_simple_container_create(bottom_bar, false, 24, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_flex_align(bottom_navbar, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_hor(bottom_navbar, 72, 0);

    lv_obj_t * electrodes_box = lv_demo_ecg_simple_container_create(bottom_navbar, false, 4, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_ver(electrodes_box, 17, 0);
    lv_obj_set_style_pad_hor(electrodes_box, 24, 0);
    lv_obj_set_style_radius(electrodes_box, 12, 0);
    lv_obj_set_style_bg_opa(electrodes_box, LV_OPA_COVER, 0);
    lv_obj_add_style(electrodes_box, &c->styles[STYLE_CONTAINER_BG_PRIMARY], 0);
    lv_obj_t * electrodes_image = lv_image_create(electrodes_box);
    lv_image_set_src(electrodes_image, &img_lv_demo_ecg_circuit);
    lv_obj_add_style(electrodes_image, &c->styles[STYLE_A8_IMG], 0);
    label = lv_label_create(electrodes_box);
    lv_label_set_text_static(label, "Electrodes");
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, c->fonts[FONT_INTER_MEDIUM_20], 0);
    lv_obj_add_event_cb(electrodes_box, leads_placement_popup, LV_EVENT_CLICKED, base_obj);

    lv_obj_t * record_box = lv_demo_ecg_simple_container_create(bottom_navbar, false, 8, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_ver(record_box, 17, 0);
    lv_obj_set_style_pad_hor(record_box, 24, 0);
    lv_obj_set_style_radius(record_box, 12, 0);
    lv_obj_set_style_bg_opa(record_box, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(record_box, lv_color_hex(0x34c759), 0);
    lv_obj_t * record_image = lv_image_create(record_box);
    lv_image_set_src(record_image, &img_lv_demo_ecg_record);
    lv_obj_set_style_image_recolor(record_image, lv_color_white(), 0);
    lv_image_set_inner_align(record_image, LV_IMAGE_ALIGN_CENTER);
    lv_obj_set_size(record_image, 24, 24);
    label = lv_label_create(record_box);
    lv_label_set_text_static(label, "Record");
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_set_style_text_font(label, c->fonts[FONT_INTER_MEDIUM_20], 0);

    lv_obj_t * patient_info_box = lv_demo_ecg_simple_container_create(bottom_navbar, false, 8, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_ver(patient_info_box, 17, 0);
    lv_obj_set_style_pad_hor(patient_info_box, 24, 0);
    lv_obj_set_style_radius(patient_info_box, 12, 0);
    lv_obj_set_style_bg_opa(patient_info_box, LV_OPA_COVER, 0);
    lv_obj_add_style(patient_info_box, &c->styles[STYLE_CONTAINER_BG_PRIMARY], 0);
    lv_obj_t * patient_info_image = lv_image_create(patient_info_box);
    lv_image_set_src(patient_info_image, &img_lv_demo_ecg_figure_lg);
    lv_obj_add_style(patient_info_image, &c->styles[STYLE_A8_IMG], 0);
    label = lv_label_create(patient_info_box);
    lv_label_set_text_static(label, "Patient Info.");
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, c->fonts[FONT_INTER_MEDIUM_20], 0);
    lv_obj_add_event_cb(patient_info_box, show_patient_info, LV_EVENT_CLICKED, base_obj);

    lv_obj_t * alarm_and_end_case_box = lv_demo_ecg_simple_container_create(bottom_bar, false, 64, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_hor(alarm_and_end_case_box, 24, 0);

    lv_obj_t * silence_box = lv_demo_ecg_simple_container_create(alarm_and_end_case_box, false, 8, LV_FLEX_ALIGN_CENTER);
    lv_obj_t * silence_image = lv_image_create(silence_box);
    lv_image_set_src(silence_image, &img_lv_demo_ecg_alarm_disabled);
    lv_obj_set_style_image_recolor(silence_image, lv_color_hex3(0x888), 0);
    label = lv_label_create(silence_box);
    lv_label_set_text_static(label, "Silence");
    lv_obj_set_style_text_color(label, lv_color_hex3(0x888), 0);
    lv_obj_set_style_text_font(label, c->fonts[FONT_INTER_MEDIUM_20], 0);

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

static void fill_chart_data(lv_obj_t * chart)
{
    lv_obj_update_layout(chart);
    int32_t w = lv_obj_get_width(chart);
    int32_t pt_count = w - 1;
    lv_chart_set_point_count(chart, pt_count);
    lv_chart_series_t * ser1 = lv_chart_add_series(chart, lv_color_black(), LV_CHART_AXIS_PRIMARY_Y);
    for(int32_t i = 0; i < pt_count; i++) {
        lv_chart_set_next_value(chart, ser1, lv_trigo_sin(i * 2) * 100 / 70000 + 50);
    }
}

static lv_obj_t * create_labeled_big_number(lv_demo_ecg_ctx_t * c, lv_obj_t * parent, const char * big_text,
                                            lv_font_t * big_font, const char * upper_small_text,
                                            const char * lower_small_text, lv_color_t lower_small_text_color,
                                            int32_t small_label_box_pad_bottom)
{
    lv_obj_t * all_middle_labels = lv_demo_ecg_simple_container_create(parent, false, 0, LV_FLEX_ALIGN_END);

    lv_obj_t * big_label = lv_label_create(all_middle_labels);
    lv_label_set_text_static(big_label, big_text);
    lv_obj_add_style(big_label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(big_label, big_font, 0);
    lv_obj_set_style_text_align(big_label, LV_TEXT_ALIGN_RIGHT, 0);

    lv_obj_t * small_label_box = lv_demo_ecg_simple_container_create(all_middle_labels, true, 4, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_bottom(small_label_box, small_label_box_pad_bottom, 0);

    lv_obj_t * label = lv_label_create(small_label_box);
    lv_label_set_text_static(label, upper_small_text);
    lv_obj_set_style_text_font(label, c->fonts[FONT_QUICKSAND_MEDIUM_24], 0);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_opa(label, LV_OPA_50, 0);

    label = lv_label_create(small_label_box);
    lv_label_set_text_static(label, lower_small_text);
    lv_obj_set_style_text_font(label, c->fonts[FONT_QUICKSAND_BOLD_27], 0);
    if(!lv_color_eq(lower_small_text_color, lv_color_hex(0))) {
        lv_obj_set_style_text_color(label, lower_small_text_color, 0);
    }
    else {
        lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    }

    return all_middle_labels;
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
    lv_obj_remove_flag(cell, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t * title_box = lv_demo_ecg_simple_container_create(cell, false, 16, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_hor(title_box, 27, 0);
    if(icon_obj) lv_obj_set_parent(icon_obj, title_box);
    lv_obj_align(title_box, LV_ALIGN_TOP_LEFT, 0, LV_PCT(5));
    lv_obj_t * label = lv_label_create(title_box);
    lv_label_set_text_static(label, title_text);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    lv_obj_set_style_text_font(label, c->fonts[FONT_QUICKSAND_MEDIUM_22], 0);

    lv_obj_t * all_middle_labels = create_labeled_big_number(c, cell, big_text,
                                                             big_font_override ? big_font_override : c->fonts[FONT_QUICKSAND_LIGHT_290],
                                                             upper_small_text, lower_small_text, lower_small_text_color, 65);

    lv_obj_align(all_middle_labels, LV_ALIGN_BOTTOM_RIGHT, -50, 50);
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

static void popup_x_clicked_cb(lv_event_t * e)
{
    lv_obj_t * base_obj = lv_event_get_user_data(e);
    uint32_t child_count = lv_obj_get_child_count(base_obj);
    for(uint32_t i = 0; i < child_count - 1; i++) {
        lv_obj_delete(lv_obj_get_child(base_obj, -1));
    }
}

static void create_lead(lv_demo_ecg_ctx_t * c, lv_obj_t * parent, lv_color_t symbol_color, const char * symbol_text, const char * main_text, const char * sub_text)
{
    lv_obj_t * box = lv_obj_create(parent);
    lv_obj_remove_style_all(box);
    lv_obj_set_size(box, 274, 80);
    lv_obj_set_style_pad_all(box, 16, 0);
    lv_obj_t * symbol = lv_obj_create(box);
    lv_obj_remove_style_all(symbol);
    lv_obj_set_size(symbol, 48, 48);
    lv_obj_set_style_bg_opa(symbol, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(symbol, symbol_color, 0);
    lv_obj_set_style_radius(symbol, LV_COORD_MAX, 0);
    lv_obj_t * label = lv_label_create(symbol);
    lv_label_set_text(label, symbol_text);
    lv_obj_center(label);
    label = lv_label_create(box);
    lv_label_set_text(label, main_text);
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 64, 0);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    label = lv_label_create(box);
    lv_label_set_text(label, sub_text);
    lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 64, 0);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
}

static void leads_placement_popup(lv_event_t * e)
{
    lv_obj_t * base_obj = lv_event_get_user_data(e);
    if(lv_obj_get_child_count(base_obj) > 1) return;
    lv_demo_ecg_ctx_t * c = lv_obj_get_user_data(base_obj);

    lv_obj_t * popup_bg = lv_obj_create(base_obj);
    lv_obj_remove_style_all(popup_bg);
    lv_obj_set_size(popup_bg, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_opa(popup_bg, LV_OPA_50, 0);
    lv_obj_set_style_bg_color(popup_bg, lv_color_black(), 0);

    lv_obj_t * popup = lv_obj_create(base_obj);
    lv_obj_center(popup);
    lv_obj_set_size(popup, 1203, 606);
    lv_obj_set_style_pad_all(popup, 40, 0);
    lv_obj_set_style_border_width(popup, 0, 0);
    lv_obj_set_style_radius(popup, 24, 0);
    lv_obj_add_style(popup, &c->styles[STYLE_CONTAINER_BG_PRIMARY], 0);

    lv_obj_t * x_btn = lv_image_create(base_obj);
    lv_image_set_src(x_btn, &img_lv_demo_ecg_x);
    lv_obj_add_style(x_btn, &c->styles[STYLE_A8_IMG], 0);
    lv_obj_add_style(x_btn, &c->styles[STYLE_CONTAINER_BG_PRIMARY], 0);
    lv_image_set_inner_align(x_btn, LV_IMAGE_ALIGN_CENTER);
    lv_obj_set_size(x_btn, 70, 70);
    lv_obj_set_style_radius(x_btn, LV_COORD_MAX, 0);
    lv_obj_set_style_bg_opa(x_btn, LV_OPA_COVER, 0);
    lv_obj_align_to(x_btn, popup, LV_ALIGN_OUT_TOP_RIGHT, 35, 35);
    lv_obj_add_flag(x_btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(x_btn, popup_x_clicked_cb, LV_EVENT_CLICKED, base_obj);

    lv_obj_t * col = lv_demo_ecg_simple_container_create(popup, true, 0, LV_FLEX_ALIGN_CENTER);

    lv_obj_t * title = lv_label_create(col);
    lv_label_set_text_static(title, "12 Leads Placement");
    lv_obj_add_style(title, &c->styles[STYLE_LABEL], 0);

    lv_obj_t * xray = lv_image_create(col);
    lv_image_set_src(xray, &img_lv_demo_ecg_xray);
    lv_obj_set_style_pad_ver(xray, 24, 0);

    create_lead(c, col, lv_color_hex(0xef4444), "V1", "Right sternal margin", "4th intercostal space");
    create_lead(c, col, lv_color_hex(0xeab308), "V2", "Left sternal margin", "4th intercostal space");
    create_lead(c, col, lv_color_hex(0x22c55e), "V3", "Between V2 and V4", "5th intercostal space");

    lv_obj_t * video = lv_ffmpeg_player_create(popup);
    lv_obj_set_align(video, LV_ALIGN_RIGHT_MID);
    lv_obj_set_style_radius(video, 16, 0);
    lv_ffmpeg_player_set_src(video, "/home/liam/Downloads/ecg_video.mp4");
    lv_ffmpeg_player_set_auto_restart(video, true);
    lv_ffmpeg_player_set_cmd(video, LV_FFMPEG_PLAYER_CMD_START);
}

static void textarea_clicked_cb(lv_event_t * e)
{
    lv_obj_t * ta = lv_event_get_target_obj(e);
    lv_obj_t * kb = lv_event_get_user_data(e);
    lv_keyboard_set_textarea(kb, ta);
}

static lv_obj_t * patient_info_input(lv_demo_ecg_ctx_t * c, lv_obj_t * grid, lv_obj_t * kb, int32_t col, int32_t row, const char * text, lv_obj_t * field_obj)
{
    lv_obj_t * label = lv_label_create(grid);
    lv_label_set_text(label, text);
    lv_obj_set_grid_cell(label, LV_GRID_ALIGN_START, col, 1, LV_GRID_ALIGN_START, row, 1);
    lv_obj_add_style(label, &c->styles[STYLE_LABEL], 0);
    if(field_obj == NULL) {
        field_obj = lv_textarea_create(grid);
        lv_obj_set_height(field_obj, LV_SIZE_CONTENT);
        lv_obj_add_event_cb(field_obj, textarea_clicked_cb, LV_EVENT_CLICKED, kb);
    }
    lv_obj_set_style_pad_all(field_obj, 8, 0);
    lv_obj_set_grid_cell(field_obj, LV_GRID_ALIGN_STRETCH, col, 1, LV_GRID_ALIGN_END, row, 1);
    lv_obj_set_style_radius(field_obj, 6, 0);
    return field_obj;
}

static void show_patient_info(lv_event_t * e)
{
    lv_obj_t * label;

    lv_obj_t * base_obj = lv_event_get_user_data(e);
    if(lv_obj_get_child_count(base_obj) > 1) return;
    lv_demo_ecg_ctx_t * c = lv_obj_get_user_data(base_obj);

    lv_obj_t * popup_bg = lv_obj_create(base_obj);
    lv_obj_remove_style_all(popup_bg);
    lv_obj_set_size(popup_bg, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_opa(popup_bg, LV_OPA_50, 0);
    lv_obj_set_style_bg_color(popup_bg, lv_color_black(), 0);

    lv_obj_t * kb = lv_keyboard_create(base_obj);
    lv_obj_set_height(kb, 334);

    lv_obj_t * popup = lv_obj_create(base_obj);
    lv_obj_align(popup, LV_ALIGN_TOP_MID, 0, 49);
    lv_obj_set_size(popup, 713, 403);
    lv_obj_set_style_pad_hor(popup, 64, 0);
    lv_obj_set_style_pad_ver(popup, 24, 0);
    lv_obj_set_style_border_width(popup, 0, 0);
    lv_obj_set_style_radius(popup, 8, 0);
    lv_obj_add_style(popup, &c->styles[STYLE_CONTAINER_BG_PRIMARY], 0);

    lv_obj_t * title = lv_label_create(popup);
    lv_label_set_text_static(title, "Enter Patient Demographics");
    lv_obj_set_style_text_align(title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(title, LV_PCT(100));
    lv_obj_add_style(title, &c->styles[STYLE_LABEL], 0);

    lv_obj_t * inner_1 = lv_demo_ecg_simple_container_create(popup, true, 24, LV_FLEX_ALIGN_END);
    lv_obj_set_width(inner_1, LV_PCT(100));
    lv_obj_set_align(inner_1, LV_ALIGN_BOTTOM_MID);

    static const int32_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static const int32_t row_dsc[] = {67, 67, 67, LV_GRID_TEMPLATE_LAST};
    lv_obj_t * grid = lv_obj_create(inner_1);
    lv_obj_remove_style_all(grid);
    lv_obj_set_style_grid_column_dsc_array(grid, col_dsc, 0);
    lv_obj_set_style_grid_row_dsc_array(grid, row_dsc, 0);
    lv_obj_set_style_pad_gap(grid, 20, 0);
    lv_obj_set_size(grid, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_layout(grid, LV_LAYOUT_GRID);

    patient_info_input(c, grid, kb, 0, 0, "Last Name *", NULL);
    patient_info_input(c, grid, kb, 1, 0, "First Name", NULL);
    patient_info_input(c, grid, kb, 0, 1, "MRN", NULL);
    patient_info_input(c, grid, kb, 1, 1, "Visit Number", NULL);
    lv_obj_t * dropdown = patient_info_input(c, grid, kb, 0, 2, "Gender", lv_dropdown_create(grid));
    lv_dropdown_set_options_static(dropdown, "Select Gender\nMale\nFemale");
    lv_obj_t * ta = patient_info_input(c, grid, kb, 1, 2, "Date of Birth", NULL);
    lv_textarea_set_placeholder_text(ta, "Pick a date");

    lv_obj_t * button_row = lv_demo_ecg_simple_container_create(inner_1, false, 16, LV_FLEX_ALIGN_CENTER);

    lv_obj_t * cancel = lv_obj_create(button_row);
    lv_obj_set_size(cancel, 79, 40);
    lv_obj_remove_flag(cancel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(cancel, 6, 0);
    label = lv_label_create(cancel);
    lv_obj_center(label);
    lv_label_set_text_static(label, "Cancel");

    lv_obj_t * save = lv_obj_create(button_row);
    lv_obj_set_size(save, 64, 40);
    lv_obj_remove_flag(save, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(save, lv_color_black(), 0);
    lv_obj_set_style_border_width(save, 0, 0);
    lv_obj_set_style_radius(save, 6, 0);
    label = lv_label_create(save);
    lv_obj_center(label);
    lv_label_set_text_static(label, "Save");
    lv_obj_set_style_text_color(label, lv_color_white(), 0);

    lv_obj_t * x_btn = lv_image_create(base_obj);
    lv_image_set_src(x_btn, &img_lv_demo_ecg_x);
    lv_obj_add_style(x_btn, &c->styles[STYLE_A8_IMG], 0);
    lv_obj_add_style(x_btn, &c->styles[STYLE_CONTAINER_BG_PRIMARY], 0);
    lv_image_set_inner_align(x_btn, LV_IMAGE_ALIGN_CENTER);
    lv_obj_set_size(x_btn, 70, 70);
    lv_obj_set_style_radius(x_btn, LV_COORD_MAX, 0);
    lv_obj_set_style_bg_opa(x_btn, LV_OPA_COVER, 0);
    lv_obj_align_to(x_btn, popup, LV_ALIGN_OUT_TOP_RIGHT, 35, 35);
    lv_obj_add_flag(x_btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(x_btn, popup_x_clicked_cb, LV_EVENT_CLICKED, base_obj);
}

#endif /*LV_USE_DEMO_ECG*/
