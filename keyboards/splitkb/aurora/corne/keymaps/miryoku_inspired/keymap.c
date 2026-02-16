#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LSFT_T(KC_D)
#define HOME_F LCTL_T(KC_F)

// Right-hand home row mods
#define HOME_J RCTL_T(KC_J)
#define HOME_K RSFT_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_QUOT RGUI_T(KC_QUOT)

enum layers {
    _BASE = 0,
    _NAV  = 1,
    _NUM  = 2,
    _SYM  = 3,
    _FUN  = 4,
    _ALT  = 5,
};

enum custom_keycodes { layer = SAFE_RANGE, T_NO_AE, T_NO_OSTR, T_NO_ARNG };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        KC_NO, KC_Q, KC_W, KC_E, KC_R, KC_T,                                   KC_Y, KC_U, KC_I, KC_O, KC_P, KC_NO,

        KC_NO, HOME_A, HOME_S, HOME_D, HOME_F, KC_G,                           KC_H, HOME_J, HOME_K, HOME_L, HOME_QUOT, KC_NO,

        KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B,                                   KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_NO,

                        KC_NO, LT(_NUM, KC_TAB), LT(_NAV, KC_SPC),         LT(_FUN, KC_ENT), LT(_ALT, KC_BSPC), KC_NO
    ),

    [_NUM] = LAYOUT_split_3x6_3
    (
        KC_NO, KC_NO, KC_NO, KC_NO, C(KC_R), C(KC_T),                           KC_GRV, KC_7, KC_8, KC_9, KC_MINS, KC_NO,

        KC_NO, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_NO,                       KC_SCLN, KC_4, KC_5, KC_6, KC_EQL, KC_NO,

        KC_NO, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_Y),                     KC_0, KC_1, KC_2, KC_3, KC_BSLS, KC_NO,

                                            KC_NO, KC_TRNS, KC_NO,          KC_ENT, KC_DEL, KC_NO
    ),

    [_NAV] = LAYOUT_split_3x6_3
    (
        KC_NO, KC_NO, KC_NO, KC_NO, C(KC_R), C(KC_T),                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_NO,                       KC_LCAP, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_NO,

        KC_NO, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_Y),                     KC_INS, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO,

                                            KC_NO, KC_NO, KC_TRNS,          KC_ENT, KC_DEL, KC_NO
    ),

    [_ALT] = LAYOUT_split_3x6_3
    (
        KC_NO, KC_ESC, T_NO_AE, T_NO_OSTR, T_NO_ARNG, KC_NO,                    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_LCBR, KC_RCBR, KC_NO, KC_NO,                           KC_NO, KC_RCTL, KC_RSFT, KC_LALT, KC_RGUI, KC_NO,

        KC_NO, KC_LBRC, KC_LPRN, KC_RPRN, KC_RBRC, KC_NO,                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

                                            KC_NO, KC_TAB, KC_SPC,          KC_NO, KC_TRNS, KC_NO
    ),

    [_FUN] = LAYOUT_split_3x6_3
    (
        KC_NO, KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR,                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_F11, KC_F4, KC_F5, KC_F6, KC_SCRL,                            KC_NO, KC_RCTL, KC_RSFT, KC_LALT, KC_RGUI, KC_NO,

        KC_NO, KC_F10, KC_F1, KC_F2, KC_F3, KC_PAUS,                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

                                    KC_NO, KC_TAB, KC_SPC,                  KC_TRNS, KC_NO, KC_NO
    ),
};

void keyboard_pre_init_user(void) {
    // setPinOutput(24);
    // writePinHigh(24);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case T_NO_AE:
        case T_NO_OSTR:
        case T_NO_ARNG:
            if (record->event.pressed) {
                tap_code16(LGUI(KC_SPC));
            } else {
                switch (keycode) {
                    case T_NO_AE:
                        tap_code(NO_AE);
                        break;
                    case T_NO_OSTR:
                        tap_code(NO_OSTR);
                        break;
                    case T_NO_ARNG:
                        tap_code(NO_ARNG);
                        break;
                    default:
                        break;
                }
                tap_code16(LGUI(KC_SPC));
            }
            return false;
    }
    return true;
}
