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

void create_chart(lv_obj_t * parent, lv_draw_buf_t * draw_buf, const lv_demo_ecg_point_t * pts,
                  lv_color_t stroke_color);
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

    /* main area */

    lv_obj_t * main_area = lv_obj_create(bg_cont);
    lv_obj_remove_style_all(main_area);
    lv_obj_set_width(main_area, LV_PCT(100));
    lv_obj_set_flex_grow(main_area, 1);
    lv_obj_set_style_pad_left(main_area, FIXED_L, 0);
    lv_obj_set_style_pad_right(main_area, FIXED_XL, 0);
    lv_obj_set_style_pad_column(main_area, FIXED_L, 0);
    lv_obj_set_flex_flow(main_area, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(main_area, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    lv_obj_t * charts = lv_obj_create(main_area);
    lv_obj_remove_style_all(charts);
    lv_obj_set_size(charts, LV_SIZE_CONTENT, LV_PCT(100));
    lv_obj_set_flex_flow(charts, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(charts, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    static const lv_demo_ecg_point_t pts1[] = {
        {LV_DEMO_ECG_POINT_TYPE_L, {0, 40.5}},
        {LV_DEMO_ECG_POINT_TYPE_L, {40.3986, 40.5}},
        {LV_DEMO_ECG_POINT_TYPE_L, {54.611, 0}},
        {LV_DEMO_ECG_POINT_TYPE_L, {64.5735, 81}},
        {LV_DEMO_ECG_POINT_TYPE_L, {82.3275, 40.5}},
        {LV_DEMO_ECG_POINT_TYPE_L, {112.453, 40.5}},
        {LV_DEMO_ECG_POINT_TYPE_L, {126.666, 0}},
        {LV_DEMO_ECG_POINT_TYPE_L, {136.628, 81}},
        {LV_DEMO_ECG_POINT_TYPE_L, {154.382, 40.5}},
        {LV_DEMO_ECG_POINT_TYPE_L, {184.738, 40.5}},
        {LV_DEMO_ECG_POINT_TYPE_L, {198.95, 0}},
        {LV_DEMO_ECG_POINT_TYPE_L, {208.913, 81}},
        {LV_DEMO_ECG_POINT_TYPE_L, {226.667, 40.5}},
        {LV_DEMO_ECG_POINT_TYPE_L, {252.899, 40.5}},
        {LV_DEMO_ECG_POINT_TYPE_L, {267.111, 0}},
        {LV_DEMO_ECG_POINT_TYPE_L, {277.073, 81}},
        {LV_DEMO_ECG_POINT_TYPE_L, {294.828, 40.5}},
        {LV_DEMO_ECG_POINT_TYPE_L, {324.953, 40.5}},
        {LV_DEMO_ECG_POINT_TYPE_L, {339.166, 0}},
        {LV_DEMO_ECG_POINT_TYPE_L, {349.128, 81}},
        {LV_DEMO_ECG_POINT_TYPE_L, {366.882, 40.5}},
        {LV_DEMO_ECG_POINT_TYPE_L, {406.092, 40.5}},
        {LV_DEMO_ECG_POINT_TYPE_L, {411.45, 0}},
        {LV_DEMO_ECG_POINT_TYPE_L, {421.413, 81}},
        {LV_DEMO_ECG_POINT_TYPE_L, {425, 40.5}},
        {LV_DEMO_ECG_POINT_TYPE_END, {0, 0}}
    };
    LV_DRAW_BUF_DEFINE_STATIC(draw_buf1, 425, 81, LV_COLOR_FORMAT_ARGB8888);
    LV_DRAW_BUF_INIT_STATIC(draw_buf1);
    create_chart(charts, &draw_buf1, pts1, lv_color_hex(0x4ADE80));

    static const lv_demo_ecg_point_t pts2[] = {
        {LV_DEMO_ECG_POINT_TYPE_L, {0, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {14.0906, -2.79407}},
        {0,                    {21.1359, -2.79407}},
        {0,                    {35.2265, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {49.3171, 29.4409}},
        {0,                    {56.3624, 29.4409}},
        {0,                    {70.453, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {84.5436, -2.79407}},
        {0,                    {91.589, -2.79407}},
        {0,                    {105.68, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {119.77, 29.4409}},
        {0,                    {126.815, 29.4409}},
        {0,                    {140.906, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {154.997, -2.79407}},
        {0,                    {162.042, -2.79407}},
        {0,                    {176.133, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {190.223, 29.4409}},
        {0,                    {197.269, 29.4409}},
        {0,                    {211.359, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {225.45, -2.79407}},
        {0,                    {232.495, -2.79407}},
        {0,                    {246.586, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {260.676, 29.4409}},
        {0,                    {267.722, 29.4409}},
        {0,                    {281.812, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {295.903, -2.79407}},
        {0,                    {303.324, -2.79407}},
        {0,                    {317.414, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {331.505, 29.4409}},
        {0,                    {338.55, 29.4409}},
        {0,                    {352.641, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {366.731, -2.79407}},
        {0,                    {373.777, -2.79407}},
        {0,                    {387.867, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {401.958, 29.4409}},
        {0,                    {409.003, 29.4409}},
        {0,                    {423.094, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {437.184, -2.79407}},
        {0,                    {444.23, -2.79407}},
        {0,                    {458.32, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {472.411, 29.4409}},
        {0,                    {479.456, 29.4409}},
        {0,                    {493.547, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {507.638, -2.79407}},
        {0,                    {514.683, -2.79407}},
        {0,                    {528.773, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_C, {542.864, 29.4409}},
        {0,                    {549.909, 34.1467}},
        {0,                    {564, 14.3822}},
        {LV_DEMO_ECG_POINT_TYPE_END, {0, 0}}
    };
    LV_DRAW_BUF_DEFINE_STATIC(draw_buf2, 425, 81, LV_COLOR_FORMAT_ARGB8888);
    LV_DRAW_BUF_INIT_STATIC(draw_buf2);
    create_chart(charts, &draw_buf2, pts2, lv_color_hex(0x67E8F9));

    static const lv_demo_ecg_point_t pts3[] = {
        {LV_DEMO_ECG_POINT_TYPE_L, {0, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_L, {35.8933, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {41.5335, 25.3738}},
        {0,                        {44.3536, 34.1869}},
        {0,                        {47.1738, 34.1869}},
        {LV_DEMO_ECG_POINT_TYPE_C, {49.9939, 34.1869}},
        {0,                        {52.814, 25.3738}},
        {0,                        {58.4542, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {64.0944, 25.3738}},
        {0,                        {66.9145, 43}},
        {0,                        {69.7346, 43}},
        {LV_DEMO_ECG_POINT_TYPE_C, {72.5547, 43}},
        {0,                        {75.3749, 25.3738}},
        {0,                        {81.0151, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_L, {98.0835, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {103.724, 25.3738}},
        {0,                        {106.544, 2}},
        {0,                        {109.364, 2}},
        {LV_DEMO_ECG_POINT_TYPE_C, {112.184, 2}},
        {0,                        {115.004, 25.3738}},
        {0,                        {120.644, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {126.285, 25.3738}},
        {0,                        {129.105, 10.8131}},
        {0,                        {131.925, 10.8131}},
        {LV_DEMO_ECG_POINT_TYPE_C, {134.745, 10.8131}},
        {0,                        {137.565, 25.3738}},
        {0,                        {143.205, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_L, {164.326, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {169.966, 25.3738}},
        {0,                        {172.786, 34.1869}},
        {0,                        {175.606, 34.1869}},
        {LV_DEMO_ECG_POINT_TYPE_C, {178.426, 34.1869}},
        {0,                        {181.246, 25.3738}},
        {0,                        {186.886, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {192.527, 25.3738}},
        {0,                        {195.347, 43}},
        {0,                        {198.167, 43}},
        {LV_DEMO_ECG_POINT_TYPE_C, {200.987, 43}},
        {0,                        {203.807, 25.3738}},
        {0,                        {209.447, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_L, {222.53, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_L, {222.582, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_L, {236.63, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {242.27, 25.3738}},
        {0,                        {245.428, 2}},
        {0,                        {248.248, 2}},
        {LV_DEMO_ECG_POINT_TYPE_C, {251.068, 2}},
        {0,                        {253.551, 25.3738}},
        {0,                        {259.191, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {264.831, 25.3738}},
        {0,                        {267.989, 10.8131}},
        {0,                        {270.809, 10.8131}},
        {LV_DEMO_ECG_POINT_TYPE_C, {273.629, 10.8131}},
        {0,                        {276.112, 25.3738}},
        {0,                        {281.752, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_L, {318.142, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {323.782, 25.3738}},
        {0,                        {326.602, 34.1869}},
        {0,                        {329.422, 34.1869}},
        {LV_DEMO_ECG_POINT_TYPE_C, {332.242, 34.1869}},
        {0,                        {335.062, 25.3738}},
        {0,                        {340.702, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {346.343, 25.3738}},
        {0,                        {349.163, 43}},
        {0,                        {351.983, 43}},
        {LV_DEMO_ECG_POINT_TYPE_C, {354.803, 43}},
        {0,                        {357.623, 25.3738}},
        {0,                        {363.263, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_L, {380.332, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {385.972, 25.3738}},
        {0,                        {388.792, 2}},
        {0,                        {391.612, 2}},
        {LV_DEMO_ECG_POINT_TYPE_C, {394.432, 2}},
        {0,                        {397.252, 25.3738}},
        {0,                        {402.893, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {408.533, 25.3738}},
        {0,                        {411.353, 10.8131}},
        {0,                        {414.173, 10.8131}},
        {LV_DEMO_ECG_POINT_TYPE_C, {416.993, 10.8131}},
        {0,                        {419.813, 25.3738}},
        {0,                        {425.453, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_L, {446.574, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {452.214, 25.3738}},
        {0,                        {455.034, 34.1869}},
        {0,                        {457.854, 34.1869}},
        {LV_DEMO_ECG_POINT_TYPE_C, {460.674, 34.1869}},
        {0,                        {463.495, 25.3738}},
        {0,                        {469.135, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {474.775, 25.3738}},
        {0,                        {477.595, 43}},
        {0,                        {480.415, 43}},
        {LV_DEMO_ECG_POINT_TYPE_C, {483.235, 43}},
        {0,                        {486.055, 25.3738}},
        {0,                        {491.696, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_L, {504.778, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_L, {504.83, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_L, {518.878, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {524.518, 25.3738}},
        {0,                        {527.676, 2}},
        {0,                        {530.496, 2}},
        {LV_DEMO_ECG_POINT_TYPE_C, {533.317, 2}},
        {0,                        {535.799, 25.3738}},
        {0,                        {541.439, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_C, {547.079, 25.3738}},
        {0,                        {550.237, 10.8131}},
        {0,                        {553.057, 10.8131}},
        {LV_DEMO_ECG_POINT_TYPE_C, {555.877, 10.8131}},
        {0,                        {558.36, 25.3738}},
        {0,                        {564, 25.3738}},
        {LV_DEMO_ECG_POINT_TYPE_END, {0, 0}}
    };
    LV_DRAW_BUF_DEFINE_STATIC(draw_buf3, 425, 81, LV_COLOR_FORMAT_ARGB8888);
    LV_DRAW_BUF_INIT_STATIC(draw_buf3);
    create_chart(charts, &draw_buf3, pts3, lv_color_hex(0xFF733B));

    static const lv_demo_ecg_point_t pts4[] = {
        {LV_DEMO_ECG_POINT_TYPE_L, {0, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_L, {27.0473, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {31.2974, 16.5467}},
        {0,                        {33.4225, 9.02336}},
        {0,                        {35.5476, 9.02336}},
        {LV_DEMO_ECG_POINT_TYPE_C, {37.6727, 9.02336}},
        {0,                        {39.7978, 16.5467}},
        {0,                        {44.0479, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {48.2981, 16.5467}},
        {0,                        {50.4232, 1.5}},
        {0,                        {52.5483, 1.5}},
        {LV_DEMO_ECG_POINT_TYPE_C, {54.6733, 1.5}},
        {0,                        {56.7984, 16.5467}},
        {0,                        {61.0486, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_L, {73.9104, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {78.1606, 16.5467}},
        {0,                        {80.2857, 36.5}},
        {0,                        {82.4108, 36.5}},
        {LV_DEMO_ECG_POINT_TYPE_C, {84.5358, 36.5}},
        {0,                        {86.6609, 16.5467}},
        {0,                        {90.9111, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {95.1613, 16.5467}},
        {0,                        {97.2863, 28.9766}},
        {0,                        {99.4114, 28.9766}},
        {LV_DEMO_ECG_POINT_TYPE_C, {101.536, 28.9766}},
        {0,                        {103.662, 16.5467}},
        {0,                        {107.912, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_L, {123.827, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {128.077, 16.5467}},
        {0,                        {130.202, 9.02336}},
        {0,                        {132.327, 9.02336}},
        {LV_DEMO_ECG_POINT_TYPE_C, {134.452, 9.02336}},
        {0,                        {136.577, 16.5467}},
        {0,                        {140.828, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {145.078, 16.5467}},
        {0,                        {147.203, 1.5}},
        {0,                        {149.328, 1.5}},
        {LV_DEMO_ECG_POINT_TYPE_C, {151.453, 1.5}},
        {0,                        {153.578, 16.5467}},
        {0,                        {157.828, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_L, {167.687, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_L, {167.726, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_L, {178.312, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {182.562, 16.5467}},
        {0,                        {184.941, 36.5}},
        {0,                        {187.066, 36.5}},
        {LV_DEMO_ECG_POINT_TYPE_C, {189.192, 36.5}},
        {0,                        {191.062, 16.5467}},
        {0,                        {195.312, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {199.562, 16.5467}},
        {0,                        {201.942, 28.9766}},
        {0,                        {204.067, 28.9766}},
        {LV_DEMO_ECG_POINT_TYPE_C, {206.192, 28.9766}},
        {0,                        {208.063, 16.5467}},
        {0,                        {212.313, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_L, {239.734, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {243.985, 16.5467}},
        {0,                        {246.11, 9.02336}},
        {0,                        {248.235, 9.02336}},
        {LV_DEMO_ECG_POINT_TYPE_C, {250.36, 9.02336}},
        {0,                        {252.485, 16.5467}},
        {0,                        {256.735, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {260.985, 16.5467}},
        {0,                        {263.11, 1.5}},
        {0,                        {265.235, 1.5}},
        {LV_DEMO_ECG_POINT_TYPE_C, {267.36, 1.5}},
        {0,                        {269.486, 16.5467}},
        {0,                        {273.736, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_L, {286.597, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {290.848, 16.5467}},
        {0,                        {292.973, 36.5}},
        {0,                        {295.098, 36.5}},
        {LV_DEMO_ECG_POINT_TYPE_C, {297.223, 36.5}},
        {0,                        {299.348, 16.5467}},
        {0,                        {303.598, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {307.848, 16.5467}},
        {0,                        {309.973, 28.9766}},
        {0,                        {312.098, 28.9766}},
        {LV_DEMO_ECG_POINT_TYPE_C, {314.224, 28.9766}},
        {0,                        {316.349, 16.5467}},
        {0,                        {320.599, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_L, {336.514, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {340.764, 16.5467}},
        {0,                        {342.889, 9.02336}},
        {0,                        {345.014, 9.02336}},
        {LV_DEMO_ECG_POINT_TYPE_C, {347.139, 9.02336}},
        {0,                        {349.264, 16.5467}},
        {0,                        {353.515, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {357.765, 16.5467}},
        {0,                        {359.89, 1.5}},
        {0,                        {362.015, 1.5}},
        {LV_DEMO_ECG_POINT_TYPE_C, {364.14, 1.5}},
        {0,                        {366.265, 16.5467}},
        {0,                        {370.515, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_L, {380.374, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_L, {380.413, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_L, {390.999, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {395.249, 16.5467}},
        {0,                        {397.628, 36.5}},
        {0,                        {399.754, 36.5}},
        {LV_DEMO_ECG_POINT_TYPE_C, {401.879, 36.5}},
        {0,                        {403.749, 16.5467}},
        {0,                        {407.999, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_C, {412.25, 16.5467}},
        {0,                        {414.629, 28.9766}},
        {0,                        {416.754, 28.9766}},
        {LV_DEMO_ECG_POINT_TYPE_C, {418.879, 28.9766}},
        {0,                        {420.75, 16.5467}},
        {0,                        {425, 16.5467}},
        {LV_DEMO_ECG_POINT_TYPE_END, {0, 0}}
    };
    LV_DRAW_BUF_DEFINE_STATIC(draw_buf4, 425, 81, LV_COLOR_FORMAT_ARGB8888);
    LV_DRAW_BUF_INIT_STATIC(draw_buf4);
    create_chart(charts, &draw_buf4, pts4, lv_color_hex(0xF8E671));

    lv_obj_t * right_col_1 = lv_obj_create(main_area);
    lv_obj_remove_style_all(right_col_1);
    lv_obj_set_size(right_col_1, 340, LV_PCT(100));
    lv_obj_set_flex_flow(right_col_1, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(right_col_1, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    lv_obj_t * cont = lv_obj_create(right_col_1);
    lv_obj_remove_style_all(cont);
    lv_obj_set_width(cont, LV_PCT(100));
    lv_obj_set_flex_grow(cont, 1);
    label = lv_label_create(cont);
    lv_label_set_text_static(label, "HR");
    lv_obj_set_align(label, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x4ade80), 0);
    label = lv_label_create(cont);
    lv_label_set_text_static(label, "120\n60");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 0, LV_PCT(-7));
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x67e8f9), 0);
    label = lv_label_create(cont);
    lv_label_set_text_static(label, "60");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_disp_1, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x4ade80), 0);
    lv_obj_set_width(label, LV_PCT(86));

    cont = lv_obj_create(right_col_1);
    lv_obj_remove_style_all(cont);
    lv_obj_set_width(cont, LV_PCT(100));
    lv_obj_set_flex_grow(cont, 1);
    label = lv_label_create(cont);
    lv_label_set_text_static(label, "SpO2");
    lv_obj_set_align(label, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x67e8f9), 0);
    label = lv_label_create(cont);
    lv_label_set_text_static(label, "120\n60");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 0, LV_PCT(-7));
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x67e8f9), 0);
    label = lv_label_create(cont);
    lv_label_set_text_static(label, "95");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_disp_1, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x67e8f9), 0);
    lv_obj_set_width(label, LV_PCT(86));

    cont = lv_obj_create(right_col_1);
    lv_obj_remove_style_all(cont);
    lv_obj_set_width(cont, LV_PCT(100));
    lv_obj_set_flex_grow(cont, 1);
    label = lv_label_create(cont);
    lv_label_set_text_static(label, "ART");
    lv_obj_set_align(label, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFF733B), 0);
    lv_obj_t * lab_cont = lv_demo_ecg_simple_container_create(cont, false, 0, LV_FLEX_ALIGN_CENTER);
    lv_obj_align(lab_cont, LV_ALIGN_BOTTOM_LEFT, 0, LV_PCT(-7));
    label = lv_label_create(lab_cont);
    lv_label_set_text_static(label, "120\n60");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFF733B), 0);
    // label = lv_label_create(lab_cont);
    // lv_label_set_text_static(label, "(90)");
    // lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_disp_3, 0);
    // lv_obj_set_style_text_color(label, lv_color_hex(0xFF733B), 0);
    label = lv_label_create(cont);
    lv_label_set_text_static(label, "120/\n70");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_disp_3, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFF733B), 0);
    lv_obj_set_width(label, LV_PCT(86));

    cont = lv_obj_create(right_col_1);
    lv_obj_remove_style_all(cont);
    lv_obj_set_width(cont, LV_PCT(100));
    lv_obj_set_flex_grow(cont, 1);
    label = lv_label_create(cont);
    lv_label_set_text_static(label, "RR");
    lv_obj_set_align(label, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xF8E671), 0);
    label = lv_label_create(cont);
    lv_label_set_text_static(label, "120\n60");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 0, LV_PCT(-7));
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_body_lg, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x67e8f9), 0);
    label = lv_label_create(cont);
    lv_label_set_text_static(label, "15");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_text_font(label, lv_demo_ecg_sizes[c->sz].font_disp_1, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xF8E671), 0);
    lv_obj_set_width(label, LV_PCT(86));

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

void create_chart(lv_obj_t * parent, lv_draw_buf_t * draw_buf, const lv_demo_ecg_point_t * pts, lv_color_t stroke_color)
{
    lv_obj_t * ch = lv_canvas_create(parent);
    lv_canvas_set_draw_buf(ch, draw_buf);
    lv_canvas_fill_bg(ch, lv_color_black(), LV_OPA_TRANSP);

    lv_layer_t layer;
    lv_canvas_init_layer(ch, &layer);
    lv_vector_dsc_t * dsc = lv_vector_dsc_create(&layer);
    lv_vector_path_t * path = lv_vector_path_create(LV_VECTOR_PATH_QUALITY_HIGH);
    lv_vector_path_move_to(path, &pts[0].pt);
    for(uint32_t i = 1; ; i++) {
        if(pts[i].type == LV_DEMO_ECG_POINT_TYPE_L) {
            lv_vector_path_line_to(path, &pts[i].pt);
        }
        else if(pts[i].type == LV_DEMO_ECG_POINT_TYPE_C) {
            lv_vector_path_cubic_to(path, &pts[i].pt, &pts[i + 1].pt, &pts[i + 2].pt);
            i += 2;
        }
        else if(pts[i].type == LV_DEMO_ECG_POINT_TYPE_END) {
            break;
        }
        else {
            LV_ASSERT(0);
        }
    }

    lv_vector_dsc_set_stroke_color(dsc, stroke_color);
    lv_vector_dsc_set_stroke_opa(dsc, LV_OPA_COVER);
    lv_vector_dsc_set_fill_opa(dsc, LV_OPA_TRANSP);
    lv_vector_dsc_set_stroke_width(dsc, 3);
    lv_vector_dsc_add_path(dsc, path);
    lv_draw_vector(dsc);
    lv_vector_path_delete(path);
    lv_vector_dsc_delete(dsc);
    lv_canvas_finish_layer(ch, &layer);
}

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
