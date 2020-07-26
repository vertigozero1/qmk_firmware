#include "quefrency.h"

enum unicode_names {
    DEGREE,
    INTERROBANG,
    IRONY,
    INVBANG,
    PREGUNTA,
    SNEK
};

const uint32_t PROGMEM unicode_map[] = {
    [COPYRIGHT] = 0x00A9,// ©
    [DEGREE] = 0x00B0,   // °
    [INTERROBANG]  = 0x203D,  // ‽
    [IRONY] = 0x2E2E,    // ⸮
    [INVBANG] = 0x00A1,  // ¡
    [PREGUNTA] = 0x00BF, // ¿
    [REGIST] = 0x00AE,   // ®
    [SNEK]  = 0x1F40D,   // 🐍
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SHIFTTAB,
  SHRUG
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SHIFTTAB:
            if (record->event.pressed) { SEND_STRING(SS_LSFT(SS_TAP(KC_TAB))); } // pressed
            else { } // released
            break;

        case SHRUG:
            if (record->event.pressed) { SEND_STRING("¯\\_(ツ)_/¯"); } // pressed
            else { } // released
            break;
    }
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Left encoder
        switch (biton32(layer_state)) {
            case 1:
                if (clockwise) { tap_code(KC_TAB); }
                else { tap_code(SHIFTTAB); }
                break;
        
            default:
                if (clockwise) { tap_code(KC_MS_WH_DOWN); }
                else { tap_code(KC_MS_WH_UP); }
                break;
            }
    }
    else if (index == 1) {
        // Right encoder
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}