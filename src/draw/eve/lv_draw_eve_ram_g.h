/**
 * @file lv_draw_eve_ram_g.h
 *
 */

/*  Created on: 19 nov 2023
 *      Author: juanj
 *
 *  Modified by LVGL
 */

#ifndef LV_DRAW_EVE_RAM_G_H
#define LV_DRAW_EVE_RAM_G_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_draw_eve.h"
#if LV_USE_DRAW_EVE

/*********************
 *      DEFINES
 *********************/

#define LV_DRAW_EVE_RAMG_OUT_OF_RAMG UINT32_MAX

#define LV_DRAW_EVE_RAMG_DL_CLONE_ADDR 0
#define LV_DRAW_EVE_RAMG_DL_CLONE_SIZE EVE_RAM_DL_SIZE

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    uintptr_t key;
    uint32_t addr;
} lv_draw_eve_ramg_hash_table_cell_t;

typedef struct {
    uint32_t ramg_addr_end;
    uint32_t hash_table_cell_count;
    uint32_t hash_table_cells_occupied;
    lv_draw_eve_ramg_hash_table_cell_t * hash_table;
    uint32_t ramg_stack_pointer;
} lv_draw_eve_ramg_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

bool lv_draw_eve_ramg_get_addr(uint32_t * addr_dst, uintptr_t key,
                               uint32_t addr_size, uint32_t addr_align);

uint32_t lv_draw_eve_ramg_temp_stack_alloc(uint32_t addr_size, uint32_t addr_align);
void lv_draw_eve_ramg_temp_stack_clear(void);

#endif/*LV_USE_DRAW_EVE*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* LV_DRAW_EVE_RAM_G_H */
