/**
 * @file lv_demo_ecg_private.h
 *
 */

#ifndef LV_DEMO_ECG_PRIVATE_H
#define LV_DEMO_ECG_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lv_demo_ecg.h"
#if LV_USE_DEMO_ECG

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

enum {
    SIZE_SM = 0,
    SIZE_LG,
    SIZE_COUNT
};

typedef struct {
} lv_demo_ecg_sizes_t;

typedef struct {
    const lv_demo_ecg_sizes_t * sz;
} lv_demo_ecg_ctx_t;

LV_ATTRIBUTE_EXTERN_DATA extern const lv_demo_ecg_sizes_t lv_demo_ecg_sizes_all[SIZE_COUNT];

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/* lv_demo_ecg_util.c */
lv_obj_t * lv_demo_ecg_base_obj_create(void);

/* lv_demo_ecg_home.c */
void lv_demo_ecg_home(lv_obj_t * base_obj);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_DEMO_ECG*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_DEMO_ECG_PRIVATE_H*/
