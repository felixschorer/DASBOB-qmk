#include QMK_KEYBOARD_H
#include "oneshot.h"

#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)

#define TD_ALT TD(LALT_RALT)

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
};

enum keycodes {
    CM_LCTL = SAFE_RANGE,
    CM_LALT,
    CM_RALT,
    CM_LGUI,
    CM_LSFT,
};

enum tapdances {
    LALT_RALT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SCLN,
                          KC_TAB,  KC_LSFT, LA_NAV,  LA_SYM,  KC_SPC,  KC_ENT
    ),

    [SYM] = LAYOUT_split_3x5_3(
        KC_TILD, KC_LBRC, KC_LCBR, KC_LPRN, KC_CIRC, KC_DLR,  KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,
        KC_HASH, KC_AMPR, KC_PLUS, KC_ASTR, KC_EQL,  KC_UNDS, KC_LSFT, KC_LCTL, TD_ALT,  KC_LGUI,
        XXXXXXX, KC_PIPE, KC_MINS, KC_SLSH, KC_PERC, KC_AT,   KC_BSLS, KC_QUES, KC_EXLM, XXXXXXX,
                          _______, _______, _______, _______, _______, _______
    ),

    [NAV] = LAYOUT_split_3x5_3(
        KC_ESC,  XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, XXXXXXX, KC_BSPC, KC_DEL,  XXXXXXX, KC_INS,
        KC_LGUI, TD_ALT,  KC_LCTL, KC_LSFT, XXXXXXX, XXXXXXX, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT,
        AU_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END,
                          _______, _______, _______, _______, _______, _______
    ),

    [NUM] = LAYOUT_split_3x5_3(
        KC_9,    KC_7,    KC_5,    KC_3,    KC_1,    KC_0,    KC_2,    KC_4,    KC_6,    KC_8,
        KC_LGUI, TD_ALT,  KC_LCTL, KC_LSFT, KC_F11,  KC_F12,  KC_LSFT, KC_LCTL, TD_ALT,  KC_LGUI,
        KC_F9,   KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F10,  KC_F2,   KC_F4,   KC_F6,   KC_F8,
                          _______, _______, _______, _______, _______, _______
    ),
};


bool cancels_oneshot(uint16_t keycode) {
    return keycode == LA_SYM || keycode == LA_NAV;
}

bool consumes_oneshot(uint16_t keycode) {
    return IS_BASIC_KEYCODE(keycode);
}

oneshot_t cm_lctl = ONESHOT(CM_LCTL, KC_LCTL);
oneshot_t cm_lalt = ONESHOT(CM_LALT, KC_LALT);
oneshot_t cm_ralt = ONESHOT(CM_RALT, KC_RALT);
oneshot_t cm_lgui = ONESHOT(CM_LGUI, KC_LGUI);
oneshot_t cm_lsft = ONESHOT(CM_LSFT, KC_LSFT);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool key_down = record->event.pressed;

    update_oneshot(&cm_lctl, keycode, key_down);
    update_oneshot(&cm_lalt, keycode, key_down);
    update_oneshot(&cm_ralt, keycode, key_down);
    update_oneshot(&cm_lgui, keycode, key_down);
    update_oneshot(&cm_lsft, keycode, key_down);

    //if (keycode == TD_ALT && !key_down) {
    //    release_oneshot(&cm_lalt);
    //    release_oneshot(&cm_ralt);
    //}

    return true;
}

void handle_alt_tapdance(tap_dance_state_t *state, void *user_data) {
    oneshot_t *oneshot;

    if (state->count == 1) {
        oneshot = &cm_lalt;
        consume_oneshot(&cm_ralt);
    } else {
        oneshot = &cm_ralt;
        consume_oneshot(&cm_lalt);
    }
    
    if (state->pressed) {
        hold_oneshot(oneshot);
    } else {
        tap_oneshot(oneshot);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    //[LALT_RALT] = ACTION_TAP_DANCE_FN(handle_alt_tapdance),
    [LALT_RALT] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_RALT),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
