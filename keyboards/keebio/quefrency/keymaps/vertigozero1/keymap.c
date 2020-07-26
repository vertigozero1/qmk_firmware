#include QMK_KEYBOARD_H

enum unicode_names {
    DEGREE,
    INTERROBANG,
    IRONY,
    INVBANG,
    PREGUNTA,
    SNEK
};

const uint32_t PROGMEM unicode_map[] = {
    [DEGREE] = 0x00B0,   // °
    [INTERROBANG]  = 0x203D,  // ‽
    [IRONY] = 0x2E2E,    // ⸮
    [INVBANG] = 0x00A1,  // ¡
    [PREGUNTA] = 0x00BF, // ¿
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
            if (record->event.pressed) { SEND_STRING(SS_DOWN(X_LSHIFT)SS_TAP(X_TAB)SS_UP(X_LSHIFT)); } // pressed
            else { } // released
            break;
		case SHRUG:
            if (record->event.pressed) { SEND_STRING("\¯\\_(-.-)_/\¯"); } // pressed
            else { } // released
            break;
    }
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Left encoder
        switch (biton32(layer_state)) {
			/*case 2:
				if (clockwise) { tap_code(RGB_MOD); }
                else { tap_code(RGB_RMOD); }
                break;*/
			case 1:
				if (clockwise) { tap_code(KC_MS_WH_RIGHT); }
                else { tap_code(KC_MS_WH_LEFT); }
                break;
            default:
                if (clockwise) { tap_code(KC_MS_WH_DOWN); }
                else { tap_code(KC_MS_WH_UP); }
                break;
            }
    }
    else if (index == 1) {
        // Right encoder
        switch (biton32(layer_state)) {
			/*case 2:
				if (clockwise) { tap_code(RGB_HUI); }
                else { tap_code(RGB_HUD); }
                break;*/
			/*case 1:
				if (clockwise) { tap_code(KC_TAB); }
                else { 
					register_code(SHIFTTAB);
					unregister_code(SHIFTTAB); 
				}
                break;*/
            default:
				if (clockwise) { tap_code(KC_VOLU); } 
				else { tap_code(KC_VOLD); }
				break;
    	}
	}
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_65_with_macro(SHRUG,  KC_CALC, KC_GESC, KC_1,    KC_2,    KC_3,  KC_4,   KC_5,  KC_6,   KC_7,     KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_MUTE, 
							   KC_F1,  KC_F2,   KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,   KC_T,  KC_Y,   KC_U,     KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PAUS, 
							   KC_F4,  KC_F5,   MO(2),   KC_A,    KC_S,    KC_D,  KC_F,   KC_G,  KC_H,   KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PSCR, 
							   KC_F7,  KC_F8,   KC_LSFT, KC_Z,    KC_X,    KC_C,  KC_V,   KC_B,  KC_N,   KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT, KC_UP,   KC_INS, 
							   KC_F11, KC_F12,  KC_LCTL, KC_LGUI, KC_LALT, MO(1), KC_SPC, KC_APP, KC_SPC, KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
	[1] = LAYOUT_65_with_macro(BL_STEP, BL_TOGG, KC_GRV,  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_DEL, _______, 
							   BL_ON,   BL_INC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
							   BL_OFF,  BL_DEC,  KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
							   KC_BRIU, KC_BRID, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, _______, 
							   KC_DEL,  OSM(MOD_LCTL|MOD_LALT), _______, GUI_ON, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END),
//	[2] = LAYOUT_65_with_macro(RGB_MOD, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
//							   RGB_SPI, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
//							   RGB_SPD, RGB_VAD, MO(2), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
//							   RGB_SAI, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
//							   RGB_SAD, RGB_HUD, _______, GUI_OFF, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)
	[2] = LAYOUT_65_with_macro(RGB_MOD, RGB_TOG, _______, INVBANG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
							   RGB_SPI, RGB_VAI, _______, _______, SNEK, DEGREE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
							   RGB_SPD, RGB_VAD, MO(2), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
							   RGB_SAI, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______, IRONY, INTERROBANG, PREGUNTA, _______, _______, _______, 
							   RGB_SAD, RGB_HUD, _______, GUI_OFF, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)
};
