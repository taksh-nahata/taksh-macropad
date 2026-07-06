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

bool oled_task_user(void) {
    
    if (timer_elapsed32(anim_timer) > 500) {
        anim_frame = (anim_frame + 1) % 2; 
        anim_timer = timer_read32();      
    }

    oled_set_cursor(0, 0);
    oled_write_P(PSTR("Nexus-4\n"), false);

    switch (current_keycode) {
        case KC_UP:
            oled_write_P(PSTR("  ^   ^  \n"), false);
            oled_write_P(PSTR("   owo   \n"), false);
            break;
        case KC_DOWN:
            oled_write_P(PSTR("  v   v  \n"), false);
            oled_write_P(PSTR("   >_<   \n"), false);
            break;
        case KC_LEFT:
            oled_write_P(PSTR("  <   <  \n"), false);
            oled_write_P(PSTR("   o_o   \n"), false);
            break;
        case KC_RIGHT:
            oled_write_P(PSTR("  >   >  \n"), false);
            oled_write_P(PSTR("   -w-   \n"), false);
            break;
        default:
            if (anim_frame == 0) {
                oled_write_P(PSTR("  -   -  \n"), false);
                oled_write_P(PSTR("   zZz   \n"), false);
            } else {
                oled_write_P(PSTR("  =   =  \n"), false);
                oled_write_P(PSTR("    zZz  \n"), false);
            }
            break;
    }
    
    return false;
}
#endif