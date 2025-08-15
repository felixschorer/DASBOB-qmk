#include QMK_KEYBOARD_H

#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
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
        KC_HASH, KC_AMPR, KC_PLUS, KC_ASTR, KC_EQL,  KC_UNDS, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,
        XXXXXXX, KC_PIPE, KC_MINS, KC_SLSH, KC_PERC, KC_AT,   KC_BSLS, KC_EXLM, KC_QUES, XXXXXXX,
                          _______, _______, _______, _______, _______, _______
    ),

    [NAV] = LAYOUT_split_3x5_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,  KC_INS,  XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, XXXXXXX, KC_BSPC, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT,
        AU_TOGG, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, KC_DEL,  KC_HOME, KC_PGUP, KC_PGDN, KC_END,
                          _______, _______, _______, _______, _______, _______
    ),

    [NUM] = LAYOUT_split_3x5_3(
        KC_9,    KC_7,    KC_5,    KC_3,    KC_1,    KC_0,    KC_2,    KC_4,    KC_6,    KC_8,
        KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_F11,  KC_F12,  KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,
        KC_F9,   KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F10,  KC_F2,   KC_F4,   KC_F6,   KC_F8,
                          _______, _______, _______, _______, _______, _______
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}