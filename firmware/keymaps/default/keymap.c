// Copyright 2026 Taksh Nahata
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

static uint16_t current_keycode = KC_NO;

static uint32_t anim_timer = 0;
static uint8_t anim_frame = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *     ┌───┐
     *     │ ↑ │
     * ┌───┼───┼───┐
     * │ ← │ ↓ │ → │
     * └───┴───┴───┘
     */
    [0] = LAYOUT(
                 KC_UP,
        KC_LEFT, KC_DOWN, KC_RIGHT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        current_keycode = keycode;
    } else {
        current_keycode = KC_NO; 
    }
    return true; 
}

#ifdef OLED_ENABLE

// This function flips the screen 180 degrees!
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    
    if (timer_elapsed32(anim_timer) > 500) {
        anim_frame = (anim_frame + 1) % 2; 
        anim_timer = timer_read32();      
    }

    // A 128x32 OLED fits 21 characters across. 
    // We pad with spaces to center everything perfectly.
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("       Nexus-4      \n"), false);
    oled_write_P(PSTR("                    \n"), false); // Blank line to space things out

    switch (current_keycode) {
        case KC_UP:
            oled_write_P(PSTR("      ^   ^      \n"), false);
            oled_write_P(PSTR("       owo       \n"), false);
            break;
        case KC_DOWN:
            oled_write_P(PSTR("      v   v      \n"), false);
            oled_write_P(PSTR("       >_<       \n"), false);
            break;
        case KC_LEFT:
            oled_write_P(PSTR("      <   <      \n"), false);
            oled_write_P(PSTR("       o_o       \n"), false);
            break;
        case KC_RIGHT:
            oled_write_P(PSTR("      >   >      \n"), false);
            oled_write_P(PSTR("       -w-       \n"), false);
            break;
        default:
            if (anim_frame == 0) {
                oled_write_P(PSTR("      -   -      \n"), false);
                oled_write_P(PSTR("       zZz       \n"), false);
            } else {
                oled_write_P(PSTR("      =   =      \n"), false);
                oled_write_P(PSTR("        zZz      \n"), false); // Shifted slightly for the breathing effect
            }
            break;
    }
    
    return false;
}
#endif