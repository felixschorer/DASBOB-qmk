#include QMK_KEYBOARD_H
#include "oneshot.h"

#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
};

enum keycodes {
    CM_LCTL = SAFE_RANGE,
    CM_LALT,
    CM_LGUI,
    CM_LSFT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SCLN,
                          LA_NAV,  KC_LSFT, KC_TAB,  KC_ENT,  KC_SPC,  LA_SYM
    ),

    [SYM] = LAYOUT_split_3x5_3(
        KC_TILD, KC_LBRC, KC_LCBR, KC_LPRN, KC_CIRC, KC_DLR,  KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,
        KC_HASH, KC_AMPR, KC_PLUS, KC_ASTR, KC_EQL,  KC_UNDS, CM_LCTL, CM_LALT, CM_LGUI, CM_LSFT,
        XXXXXXX, KC_PIPE, KC_MINS, KC_SLSH, KC_PERC, KC_AT,   KC_BSLS, KC_EXLM, KC_QUES, XXXXXXX,
                          _______, _______, _______, _______, _______, _______
    ),

    [NAV] = LAYOUT_split_3x5_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,  KC_INS,  XXXXXXX, XXXXXXX, XXXXXXX,
        CM_LSFT, CM_LGUI, CM_LALT, CM_LCTL, XXXXXXX, KC_BSPC, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT,
        AU_TOGG, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, KC_DEL,  KC_HOME, KC_PGUP, KC_PGDN, KC_END,
                          _______, _______, _______, _______, _______, _______
    ),

    [NUM] = LAYOUT_split_3x5_3(
        KC_9,    KC_7,    KC_5,    KC_3,    KC_1,    KC_0,    KC_2,    KC_4,    KC_6,    KC_8,
        CM_LSFT, CM_LGUI, CM_LALT, CM_LCTL, KC_F11,  KC_F12,  CM_LCTL, CM_LALT, CM_LGUI, CM_LSFT,
        KC_F9,   KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F10,  KC_F2,   KC_F4,   KC_F6,   KC_F8,
                          _______, _______, _______, _______, _______, _______
    ),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    return keycode == LA_SYM 
        || keycode == LA_NAV;
}

bool is_oneshot_consuming_key(uint16_t keycode) {
    return keycode != LA_SYM 
        && keycode != LA_NAV
        && keycode != KC_LSFT
        && keycode != CM_LSFT
        && keycode != CM_LCTL
        && keycode != CM_LALT
        && keycode != CM_LGUI;
}

oneshot_t cm_lctl = ONESHOT(CM_LCTL, KC_LCTL);
oneshot_t cm_lalt = ONESHOT(CM_LALT, KC_LALT);
oneshot_t cm_lgui = ONESHOT(CM_LGUI, KC_LGUI);
oneshot_t cm_lsft = ONESHOT(CM_LSFT, KC_LSFT);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(&cm_lctl, keycode, record);
    update_oneshot(&cm_lalt, keycode, record);
    update_oneshot(&cm_lgui, keycode, record);
    update_oneshot(&cm_lsft, keycode, record);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
