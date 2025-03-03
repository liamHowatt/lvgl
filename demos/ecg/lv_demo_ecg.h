/**
 * @file lv_demo_ecg.h
 *
 */

#ifndef LV_DEMO_ECG_H
#define LV_DEMO_ECG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../src/lv_conf_internal.h"
#if LV_USE_DEMO_ECG

#include "../../src/core/lv_obj.h"

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t * lv_demo_ecg(void);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_DEMO_ECG*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_DEMO_ECG_H*/
