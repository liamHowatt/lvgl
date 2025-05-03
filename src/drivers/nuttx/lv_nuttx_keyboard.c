/**
 * @file lv_nuttx_keyboard.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "lv_nuttx_keyboard.h"

#if LV_USE_NUTTX

#if LV_USE_NUTTX_KEYBOARD

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <debug.h>
#include <errno.h>
#include <fcntl.h>
#include <nuttx/input/keyboard.h>
#include "../../lvgl_private.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    /* fd should be defined at the beginning */
    int fd;
    struct keyboard_event_s last_key_event;
    bool has_last_key_event;
    lv_indev_state_t last_state;
} lv_nuttx_keyboard_t;

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

lv_indev_t * lv_nuttx_keyboard_create(const char * dev_path)
{
    lv_indev_t * indev;
    int fd;

    LV_ASSERT_NULL(dev_path);
    LV_LOG_USER("keyboard %s opening", dev_path);
    fd = open(dev_path, O_RDONLY | O_NONBLOCK);
    if(fd < 0) {
        perror("Error: cannot open keyboard device");
        return NULL;
    }

    LV_LOG_USER("keyboard %s open success", dev_path);

    indev = keyboard_init(fd);

    if(indev == NULL) {
        close(fd);
    }

    return indev;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static uint32_t convert_keycode(uint32_t keycode)
{
    /* TODO */

    return 0;
}

static bool keyboard_read_key(int fd, struct keyboard_event_s * key_event)
{
    ssize_t nbytes = read(fd, key_event, sizeof(struct keyboard_event_s));
    return nbytes == sizeof(struct keyboard_event_s);
}

static void keyboard_read(lv_indev_t * drv, lv_indev_data_t * data)
{
    lv_nuttx_keyboard_t * keyboard = drv->driver_data;

    if(keyboard->has_last_key_event || keyboard_read_key(keyboard->fd, &keyboard->last_key_event)) {
        data->key = convert_keycode(keyboard->last_key_event.code);
        keyboard->last_state = keyboard->last_key_event.type == KEYBOARD_PRESS
                               ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;

        bool another_key_was_read = keyboard_read_key(keyboard->fd, &keyboard->last_key_event);
        keyboard->has_last_key_event = another_key_was_read;
        data->continue_reading       = another_key_was_read;
    }

    data->state = keyboard->last_state;
}

static void keyboard_delete_cb(lv_event_t * e)
{
    lv_indev_t * indev = (lv_indev_t *) lv_event_get_user_data(e);
    lv_nuttx_keyboard_t * keyboard = lv_indev_get_driver_data(indev);
    if(keyboard) {
        lv_indev_set_driver_data(indev, NULL);
        lv_indev_set_read_cb(indev, NULL);
        if(keyboard->fd >= 0) {
            close(keyboard->fd);
            keyboard->fd = -1;
        }
        lv_free(keyboard);
        LV_LOG_USER("done");
    }
}

static lv_indev_t * keyboard_init(int fd)
{
    lv_nuttx_keyboard_t * keyboard;
    lv_indev_t * indev = NULL;

    keyboard = lv_malloc_zeroed(sizeof(lv_nuttx_keyboard_t));
    if(keyboard == NULL) {
        LV_LOG_ERROR("keyboard_s malloc failed");
        return NULL;
    }

    keyboard->fd = fd;
    touchscreen->last_state = LV_INDEV_STATE_RELEASED;
    keyboard->indev_drv = indev = lv_indev_create();

    lv_indev_set_type(indev, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev, keyboard_read);
    lv_indev_set_driver_data(indev, keyboard);
    lv_indev_add_event_cb(indev, keyboard_delete_cb, LV_EVENT_DELETE, indev);
    return indev;
}

#endif /*LV_USE_NUTTX_KEYBOARD*/

#endif /* LV_USE_NUTTX*/
