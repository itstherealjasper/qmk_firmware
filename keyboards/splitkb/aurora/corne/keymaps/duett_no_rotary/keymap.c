/* Copyright 2022 splitkb.com <support@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

enum layers {
    _QWERTY     = 0,
    _CHARACTER  = 1,
    _NAVIGATION = 2,
};

enum custom_keycodes { layer = SAFE_RANGE, comment, uncomment };

// Tap Dance Declarations
enum {
    TD_BKSP = 0,
    TD_DEL = 1,
    TD_GUI = 2,
};

// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_BKSP] = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, C(KC_BSPC)),
    [TD_DEL] = ACTION_TAP_DANCE_DOUBLE(KC_DEL, C(KC_DEL)),
    [TD_GUI] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LWIN(KC_SPC)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY]    = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q, KC_W, KC_E, KC_R, KC_T,                          KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSLS,
        KC_TAB,  KC_A, KC_S, KC_D, KC_F, KC_G,                          KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                          KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
            TD(TD_GUI), TD(TD_BKSP), CTL_T(KC_SPC),                 ALT_T(KC_ENT), MO(_CHARACTER), MO(_NAVIGATION)
    ),
    [_CHARACTER] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_NO,   NO_AE,   NO_OSTR, NO_ARNG, KC_NO,             KC_NO, KC_7, KC_8, KC_9, KC_NO,   TD(TD_DEL),
        KC_TAB,  KC_GRV,  KC_LCBR, KC_RCBR, KC_NO,   uncomment,         KC_NO, KC_4, KC_5, KC_6, KC_NO,   KC_EQL,
        KC_LSFT, KC_LBRC, KC_LPRN, KC_RPRN, KC_RBRC, comment,           KC_0,  KC_1, KC_2, KC_3, KC_SLSH, KC_MINS,
                        TD(TD_GUI), TD(TD_BKSP), CTL_T(KC_SPC),     ALT_T(KC_ENT), KC_TRNS, KC_TRNS
    ),
    [_NAVIGATION] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_F1, KC_F2,  KC_F3,  KC_F4,  KC_NO,                  KC_WFWD,   KC_NO,   KC_UP,   KC_NO,    KC_NO,  KC_MPLY,
        KC_TAB,  KC_F5, KC_F6,  KC_F7,  KC_F8,  KC_NO,                  KC_WBAK,   KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO,  KC_MNXT,
        KC_LSFT, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO,                  C(KC_Y),   C(KC_V), C(KC_C), C(KC_X), C(KC_Z), KC_MPRV,
                    TD(TD_GUI), TD(TD_BKSP), CTL_T(KC_SPC),         ALT_T(KC_ENT), KC_TRNS, KC_TRNS
    ),
};

void keyboard_pre_init_user(void) {
    setPinOutput(24);
    writePinHigh(24);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case comment:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_K);
                tap_code(KC_C);
                unregister_code(KC_LCTL);
            }
            break;
        case uncomment:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_K);
                tap_code(KC_U);
                unregister_code(KC_LCTL);
            }
            break;
    }
    return true;
};
