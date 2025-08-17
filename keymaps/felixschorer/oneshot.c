#include QMK_KEYBOARD_H
#include "oneshot.h"

void tap_oneshot(oneshot_t *oneshot) {
    if (!oneshot->modifier_consumed) {
        return;
    }
    if (!oneshot->trigger_down) {
        register_code(oneshot->modifier);
    }
    oneshot->modifier_consumed = false;
}

void hold_oneshot(oneshot_t *oneshot) {
    tap_oneshot(oneshot);
    oneshot->trigger_down = true;
}

void release_oneshot(oneshot_t *oneshot) {
    if (!oneshot->trigger_down) {
        return;
    }
    if (oneshot->modifier_consumed) {
        unregister_code(oneshot->modifier);
    }
    oneshot->trigger_down = false;
}

void consume_oneshot(oneshot_t *oneshot) {
    if (oneshot->modifier_consumed) {
        return;
    }
    if (!oneshot->trigger_down) {
        unregister_code(oneshot->modifier);
    }
    oneshot->modifier_consumed = true;
}

void update_oneshot(oneshot_t *oneshot, uint16_t keycode, bool key_down) {
    if (keycode == oneshot->trigger) {
        if (key_down) {
            hold_oneshot(oneshot);
        } else {
            release_oneshot(oneshot);
        }
    } else if (cancels_oneshot(keycode) && key_down) {
        consume_oneshot(oneshot);
    } else if (consumes_oneshot(keycode) && !key_down) {
        consume_oneshot(oneshot);
    }
}