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

#ifdef OLED_ENABLE
#    include "transactions.h"
#    include "lightning.c"
static bool requires_oled_sync = false;
#endif

enum layers {
    _QWERTY    = 0,
    _CHARACTER = 1,
};

enum custom_keycodes { layer = SAFE_RANGE, comment, uncomment };

// Tap Dance Declarations
enum {
    TD_LAYER = 0,
    TD_BKSP  = 1,
};

void dance_layer_switch(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        layer_move(1);
        reset_tap_dance(state);
    } else {
        layer_move(0);
    }
}

// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LAYER] = ACTION_TAP_DANCE_FN(dance_layer_switch),
    [TD_BKSP]  = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, C(KC_BSPC)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // [_QWERTY]    = LAYOUT_split_3x6_3(
    //         KC_ESC,  KC_Q, KC_W, KC_E, KC_R, KC_T,          KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSLS,
    //         KC_TAB,  KC_A, KC_S, KC_D, KC_F, KC_G,          KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    //         KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,          KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
    //             KC_LGUI, TD(TD_BKSP), CTL_T(KC_SPC),    ALT_T(KC_ENT), TD(TD_LAYER), LWIN(KC_SPC)
    //     ),
    // [_CHARACTER] = LAYOUT_split_3x6_3(
    //         KC_ESC,  KC_HOME, KC_F2,   NO_AE,   NO_OSTR, NO_ARNG,      KC_PAST, KC_7, KC_8, KC_9, KC_PPLS,  KC_DEL,
    //         KC_TAB,  KC_GRV,  KC_LCBR, KC_RCBR, KC_QUOT, uncomment,    KC_PSLS, KC_4, KC_5, KC_6, KC_PMNS, KC_EQL,
    //         KC_LSFT, KC_LBRC, KC_LPRN, KC_RPRN, KC_RBRC, comment,      KC_0,    KC_1, KC_2, KC_3, KC_DOT,  KC_MINS,
    //                         KC_LGUI, TD(TD_BKSP), CTL_T(KC_SPC),    ALT_T(KC_ENT), TD(TD_LAYER), LWIN(KC_SPC)
    //     ),

    [_QWERTY]    = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q, KC_W, KC_E, KC_R, KC_T,          KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSLS,
        KC_TAB,  KC_A, KC_S, KC_D, KC_F, KC_G,          KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,          KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
            KC_LGUI, TD(TD_BKSP), CTL_T(KC_SPC),    ALT_T(KC_ENT), TT(_CHARACTER), LWIN(KC_SPC)
    ),
    [_CHARACTER] = LAYOUT_split_3x6_3(
            KC_ESC,  KC_HOME, KC_F2,   NO_AE,   NO_OSTR, NO_ARNG,      KC_PAST, KC_7, KC_8, KC_9, KC_PPLS,  KC_DEL,
            KC_TAB,  KC_GRV,  KC_LCBR, KC_RCBR, KC_QUOT, uncomment,    KC_PSLS, KC_4, KC_5, KC_6, KC_PMNS, KC_EQL,
            KC_LSFT, KC_LBRC, KC_LPRN, KC_RPRN, KC_RBRC, comment,      KC_0,    KC_1, KC_2, KC_3, KC_DOT,  KC_MINS,
                            KC_LGUI, TD(TD_BKSP), CTL_T(KC_SPC),    ALT_T(KC_ENT), TO(_QWERTY), LWIN(KC_SPC)
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
#ifdef OLED_ENABLE
        case CTL_T(KC_SPC):
            if (record->tap.count && record->event.pressed) {
                if (is_keyboard_left()) {
                    activate_animation();
                } else {
                    requires_oled_sync = true;
                }
            }
            return true;
        case ALT_T(KC_ENT):
            if (record->tap.count && record->event.pressed) {
                if (!is_keyboard_left()) {
                    activate_animation();
                } else {
                    requires_oled_sync = true;
                }
            }
            return true;
#endif
    }
    return true;
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // 0 is left-half encoder,
    // 1 is right-half encoder
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_UP);
        } else {
            tap_code(KC_DOWN);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_LEFT);
        } else {
            tap_code(KC_RIGHT);
        }
    }

    return false;
}
#endif

#ifdef OLED_ENABLE
void oled_sync_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    activate_animation();
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(RPC_OLED_SYNC, oled_sync_handler);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master() && requires_oled_sync) {
        // Interact with slave every 50ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 50) {
            if (transaction_rpc_send(RPC_OLED_SYNC, 0, NULL)) {
                requires_oled_sync = false;
                last_sync          = timer_read32();
            }
        }
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_anim();
    } else {
        oled_render_anim();
    }
    return false;
}
#endif
