#pragma once
#include QMK_KEYBOARD_H

typedef struct {
    uint16_t trigger;
    uint16_t modifier;
    bool trigger_down;
    bool modifier_queued;
} oneshot_t;

#define ONESHOT(TRIGGER, MODIFIER) \
    (oneshot_t){ .trigger = TRIGGER, .modifier = MODIFIER, .trigger_down = false, .modifier_queued = false }

void update_oneshot(oneshot_t *modifier, uint16_t keycode, keyrecord_t *record);

bool is_oneshot_cancel_key(uint16_t keycode);

bool is_oneshot_consuming_key(uint16_t keycode);