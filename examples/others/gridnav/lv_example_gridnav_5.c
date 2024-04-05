#include "../../lv_examples.h"
#if LV_USE_GRIDNAV && LV_USE_FLEX && LV_BUILD_EXAMPLES

static const char * opts_0_to_9 = "0\n1\n2\n3\n4\n5\n6\n7\n8\n9";
static const char * opts_dist_units = "km\n"
                                      "mi\n"
                                      "m\n"
                                      "ft\n"
                                      "mm\n"
                                      "in";
static const char * opts_time_units = "s\n"
                                      "min\n"
                                      "h\n"
                                      "d\n"
                                      "mo\n"
                                      "yr";

static lv_obj_t * create_roller(lv_obj_t * parent, const char * opts)
{
    lv_obj_t * roller = lv_roller_create(parent);
    lv_roller_set_options(roller, opts, LV_ROLLER_MODE_INFINITE);
    lv_obj_set_height(roller, LV_PCT(100));
    return roller;
}

static lv_obj_t * create_roller_row(lv_obj_t * parent, const char ** opts)
{
    lv_obj_t * row = lv_obj_create(parent);
    lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(row, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    while(*opts) {
        create_roller(row, *opts);
        opts++;
    };
    return row;
}

/**
 * Simple navigation on a list widget
 */
void lv_example_gridnav_5(void)
{
    /*It's assumed that the default group is set and
     *there is a keyboard indev*/

    // static int32_t col_dsc[] = {LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST};
    // static int32_t row_dsc[] = {LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST};

    /*Create a container with grid*/
    lv_obj_t * cont = lv_obj_create(lv_screen_active());
    // lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(cont, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_center(cont);

    // lv_group_t * group = lv_group_get_default();
    lv_group_t * group = lv_group_create();
    extern lv_indev_t * keypad_indev;
    lv_indev_set_group(keypad_indev, group);

    lv_obj_t * obj;

    lv_obj_t * col1 = lv_obj_create(cont);
    lv_obj_set_flex_flow(col1, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_size(col1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_center(col1);

    obj = create_roller_row(col1, (const char * []) {
        opts_0_to_9, opts_0_to_9, opts_0_to_9, opts_dist_units, NULL
    });
    lv_obj_set_size(obj, LV_SIZE_CONTENT, 200);
    lv_gridnav_add(obj, LV_GRIDNAV_CTRL_ROLLOVER | LV_GRIDNAV_CTRL_SCROLL_FIRST);
    lv_group_add_obj(group, obj);

    obj = create_roller_row(col1, (const char * []) {
        opts_0_to_9, opts_0_to_9, opts_time_units, NULL
    });
    lv_obj_set_size(obj, LV_SIZE_CONTENT, 100);
    lv_gridnav_add(obj, LV_GRIDNAV_CTRL_ROLLOVER | LV_GRIDNAV_CTRL_SCROLL_FIRST);
    lv_group_add_obj(group, obj);

    lv_obj_t * col2 = lv_obj_create(cont);
    lv_obj_set_flex_flow(col2, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_size(col2, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_center(col2);

    obj = create_roller_row(col2, (const char * []) {
        opts_0_to_9, opts_0_to_9, opts_0_to_9, NULL
    });
    lv_obj_set_size(obj, LV_SIZE_CONTENT, 100);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_CENTER, 0, 1,
                         LV_GRID_ALIGN_CENTER, 1, 1);
    lv_gridnav_add(obj, LV_GRIDNAV_CTRL_ROLLOVER | LV_GRIDNAV_CTRL_SCROLL_FIRST);
    lv_group_add_obj(group, obj);
}

#endif
