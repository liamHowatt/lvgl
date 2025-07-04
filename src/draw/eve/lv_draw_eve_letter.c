/**
 * @file lv_draw_eve_letter.c
 *
 */

/*  Author: juanj
 *
 *  Modified by LVGL
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_draw_eve_private.h"
#if LV_USE_DRAW_EVE

#include "../lv_draw_private.h"
#include "../lv_draw_label_private.h"
#include "../lv_draw_rect.h"
#include "lv_eve.h"
#include "lv_draw_eve_ram_g.h"
#include "../../font/lv_font_fmt_txt.h"
#include "../../misc/lv_area_private.h"

/*********************
 *      DEFINES
 *********************/

#define SNAPSHOT_FMT EVE_RGB565

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void lv_draw_eve_letter_cb(lv_draw_task_t * t, lv_draw_glyph_dsc_t * glyph_draw_dsc,
                                  lv_draw_fill_dsc_t * fill_draw_dsc, const lv_area_t * fill_area);
static void font_bitmap_to_ramg(uint32_t addr, const uint8_t * src, uint32_t width,
                                uint32_t height);

/**********************
 *  STATIC VARIABLES
 **********************/

static lv_area_t label_extents;

/**********************
 *      MACROS
 **********************/

#define GET_NIBBLE_1(w) ((uint8_t) ((w) >> 4))
#define GET_NIBBLE_2(w) ((uint8_t) ((w) & 0xf))

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_draw_eve_label(lv_draw_task_t * t, const lv_draw_label_dsc_t * dsc, const lv_area_t * coords)
{
    if(dsc->opa <= LV_OPA_MIN) return;
    
    EVE_end_cmd_burst();
    EVE_execute_cmd();
    /* get the display list offset */
    uint16_t dl_save = EVE_memRead16(REG_CMD_DL);
    EVE_start_cmd_burst();

    lv_eve_save_context();

    lv_eve_scissor(t->clip_area.x1, t->clip_area.y1, t->clip_area.x2, t->clip_area.y2);

    lv_eve_primitive(LV_EVE_PRIMITIVE_BITMAPS);

    label_extents.x1 = INT32_MAX;
    label_extents.y1 = INT32_MAX;
    label_extents.x2 = INT32_MIN;
    label_extents.y2 = INT32_MIN;

    lv_draw_label_iterate_characters(t, dsc, coords, lv_draw_eve_letter_cb);

    lv_area_t snapshot_area;
    if(!lv_area_intersect(&snapshot_area, &label_extents, &t->clip_area)) {
        lv_area_set(&snapshot_area, 0, 0, -1, -1);
    }

    lv_eve_restore_context();

    EVE_cmd_dl_burst(DL_DISPLAY); /* instruct the co-processor to show the list */
    EVE_cmd_dl_burst(CMD_SWAP);   /* make this list active */

    EVE_end_cmd_burst();
    EVE_execute_cmd();


    EVE_cmd_memcpy(LV_DRAW_EVE_RAMG_DL_CLONE_ADDR, EVE_RAM_DL, dl_save);


    uint32_t snapshot_ramg_location = lv_draw_eve_ramg_temp_stack_alloc(lv_area_get_size(&snapshot_area) * 2, 2);
    int32_t snapshot_w = lv_area_get_width(&snapshot_area);
    int32_t snapshot_h = lv_area_get_height(&snapshot_area);

    // LV_LOG_USER("%u %d %d", (unsigned) snapshot_ramg_location, (int) snapshot_w, (int) snapshot_h);

    // EVE_memWrite8(REG_PCLK, 0);
    EVE_cmd_snapshot2(
        SNAPSHOT_FMT,
        snapshot_ramg_location,
        snapshot_area.x1,
        snapshot_area.y1,
        snapshot_w,
        snapshot_h
    );
    /* EVE_cmd_snapshot2 waits for the coprocessor to finish */
    // EVE_memWrite8(REG_PCLK, EVE_PCLK);

    EVE_start_cmd_burst();
    EVE_cmd_dl_burst(CMD_DLSTART);
    EVE_cmd_append(LV_DRAW_EVE_RAMG_DL_CLONE_ADDR, dl_save);

    lv_eve_save_context();

    lv_eve_scissor(t->clip_area.x1, t->clip_area.y1, t->clip_area.x2, t->clip_area.y2);

    lv_eve_primitive(LV_EVE_PRIMITIVE_BITMAPS);
    EVE_cmd_dl_burst(BITMAP_SOURCE(snapshot_ramg_location));
    // EVE_cmd_dl_burst(BITMAP_SIZE_H(snapshot_w, snapshot_h));
    EVE_cmd_dl_burst(BITMAP_SIZE(EVE_NEAREST, EVE_BORDER, EVE_BORDER, snapshot_w, snapshot_h));
    // EVE_cmd_dl_burst(BITMAP_LAYOUT_H(snapshot_w * 2, snapshot_h));
    EVE_cmd_dl_burst(BITMAP_LAYOUT(SNAPSHOT_FMT, snapshot_w * 2, snapshot_h));
    lv_eve_vertex_2f(snapshot_area.x1, snapshot_area.y1);

    lv_eve_restore_context();

    LV_LOG_WARN("%"LV_PRId32" %"LV_PRId32" %"LV_PRId32" %"LV_PRId32"      %"LV_PRId32" %"LV_PRId32"  %s",
        snapshot_area.x1, snapshot_area.y1, snapshot_area.x2, snapshot_area.y2,
        snapshot_w, snapshot_h,
        dsc->text);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_draw_eve_letter_cb(lv_draw_task_t * t, lv_draw_glyph_dsc_t * glyph_draw_dsc,
                                  lv_draw_fill_dsc_t * fill_draw_dsc, const lv_area_t * fill_area)
{

    if(fill_draw_dsc && fill_area) {
        /* draw UNDERLINE and STRIKETHROUGH */
        lv_eve_draw_rect_simple(fill_area->x1, fill_area->y1, fill_area->x2, fill_area->y2, 0);

        label_extents.x1 = LV_MIN(label_extents.x1, fill_area->x1);
        label_extents.y1 = LV_MIN(label_extents.y1, fill_area->y1);
        label_extents.x2 = LV_MAX(label_extents.x2, fill_area->x2);
        label_extents.y2 = LV_MAX(label_extents.y2, fill_area->y2);
    }

    if(glyph_draw_dsc == NULL)
        return;  /* Important */

    const lv_font_t * font = glyph_draw_dsc->g->resolved_font;

    if(font->get_glyph_bitmap != lv_font_get_bitmap_fmt_txt) {
        LV_LOG_WARN("lv_draw_eve can only render static fonts for now.");
        return;
    }

    if(glyph_draw_dsc->format != LV_FONT_GLYPH_FORMAT_A4) {
        LV_LOG_WARN("lv_draw_eve can only render 4 BPP fonts for now.");
        return;
    }

    const lv_font_fmt_txt_dsc_t * font_dsc = (lv_font_fmt_txt_dsc_t *) font->dsc;
    uint32_t gid_index = glyph_draw_dsc->g->gid.index;
    const lv_font_fmt_txt_glyph_dsc_t * glyph_dsc = &font_dsc->glyph_dsc[gid_index];
    const uint8_t * glyph_bitmap = &font_dsc->glyph_bitmap[glyph_dsc->bitmap_index];

    uint16_t g_box_w = glyph_dsc->box_w;
    uint16_t g_box_h = glyph_dsc->box_h;

    uint16_t g_aligned_stride = (g_box_w + 1) / 2;

    /* Only 4 bpp is supported for now. Support for 1 and 8 bpp can be added. (EVE_L1, EVE_L8) */
    uint8_t bpp_eve = EVE_L4;

    uint32_t glyph_ramg_size = g_aligned_stride * g_box_h;

    uint32_t ramg_addr;
    uintptr_t glyph_ramg_key = (uintptr_t) glyph_bitmap;
    bool font_is_loaded = lv_draw_eve_ramg_get_addr(&ramg_addr, glyph_ramg_key, glyph_ramg_size, 1);

    if(!font_is_loaded) { /* If the font is not yet loaded in ramG, load it */
        if(ramg_addr == LV_DRAW_EVE_RAMG_OUT_OF_RAMG) {
            LV_LOG_WARN("Could not load glyph because space could not be allocated in RAM_G.");
            return;
        }

        font_bitmap_to_ramg(ramg_addr, glyph_bitmap, g_box_w, g_box_h);
    }

    lv_eve_color_opa(glyph_draw_dsc->opa);
    lv_eve_color(glyph_draw_dsc->color);

    EVE_cmd_dl_burst(BITMAP_SOURCE(ramg_addr));

    EVE_cmd_dl_burst(BITMAP_SIZE(EVE_NEAREST, EVE_BORDER, EVE_BORDER, g_box_w, g_box_h));
    EVE_cmd_dl_burst(BITMAP_LAYOUT(bpp_eve, g_aligned_stride, g_box_h));

    lv_eve_vertex_2f(glyph_draw_dsc->letter_coords->x1, glyph_draw_dsc->letter_coords->y1);

    label_extents.x1 = LV_MIN(label_extents.x1, glyph_draw_dsc->letter_coords->x1);
    label_extents.y1 = LV_MIN(label_extents.y1, glyph_draw_dsc->letter_coords->y1);
    label_extents.x2 = LV_MAX(label_extents.x2, glyph_draw_dsc->letter_coords->x2);
    label_extents.y2 = LV_MAX(label_extents.y2, glyph_draw_dsc->letter_coords->y2);
}

static void font_bitmap_to_ramg(uint32_t addr, const uint8_t * src, uint32_t width,
                                uint32_t height)
{
    EVE_end_cmd_burst();

    uint32_t stride = (width + 1) / 2;

    if(width % 2 == 0) {
        uint32_t size = stride * height;
        EVE_memWrite_flash_buffer(addr, src, size);

        EVE_start_cmd_burst();
        return;
    }

    uint8_t * row_buf = lv_malloc(stride);
    LV_ASSERT_MALLOC(row_buf);

    uint32_t src_i = 0;
    uint8_t nibble_1;
    uint8_t nibble_2;
    uint8_t key = 0;

    /* Iterate through each row of the bitmap*/
    for(uint32_t y = 0; y < height; y++) {
        /* Iterate through each byte of the row*/
        uint32_t row_i;
        for(row_i = 0; row_i < (width / 2); ++row_i) {
            /*Get the two nibbles from the current byte*/
            if(key == 0) {
                nibble_1 = GET_NIBBLE_1(src[src_i]);
                nibble_2 = GET_NIBBLE_2(src[src_i]);
            }
            else {
                nibble_1 = GET_NIBBLE_2(src[src_i - 1]);
                nibble_2 = GET_NIBBLE_1(src[src_i]);
            }

            /*Combine the nibbles and assign the result to the output byte*/
            row_buf[row_i] = (nibble_1 << 4) | nibble_2;

            src_i++;
        }

        /*process the last remaining nibble*/
        row_buf[row_i] =
            (key == 0) ?
            (GET_NIBBLE_1(src[src_i])) << 4 | 0x0 : (GET_NIBBLE_2(src[src_i - 1])) << 4 | 0x0;
        key = (key == 0) ? 1 : 0;
        src_i += (key == 1) ? 1 : 0;

        EVE_memWrite_sram_buffer(addr, row_buf, stride);
        addr += stride;
    }

    lv_free(row_buf);

    EVE_start_cmd_burst();
}


#endif /*LV_USE_DRAW_EVE*/

