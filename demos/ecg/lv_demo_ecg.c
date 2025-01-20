/**
 * @file lv_demo_ecg.c
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

/*This typedef exists purely to keep -Wpedantic happy when the file is empty.*/
/*It can be removed.*/
typedef int _keep_pedantic_happy;

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

lv_obj_t * lv_demo_ecg(void)
{
    lv_obj_t * base_obj = lv_demo_ecg_base_obj_create();
    lv_demo_ecg_home(base_obj);
    return base_obj;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /*LV_USE_DEMO_ECG*/
