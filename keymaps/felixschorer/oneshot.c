#include QMK_KEYBOARD_H
#include "oneshot.h"

bool is_modifier_registered(oneshot_t *oneshot) {
    return oneshot->trigger_down || oneshot->modifier_queued;
}

void queue_oneshot(oneshot_t *oneshot) {
    if (!is_modifier_registered(oneshot)) {
        register_code(oneshot->modifier);
    }
    oneshot->modifier_queued = true;
}

void hold_oneshot(oneshot_t *oneshot) {
    queue_oneshot(oneshot);
    oneshot->trigger_down = true;
}

void release_oneshot(oneshot_t *oneshot) {
    if (!oneshot->modifier_queued && is_modifier_registered(oneshot)) {
        unregister_code(oneshot->modifier);
    }
    oneshot->trigger_down = false;
}

void cancel_oneshot(oneshot_t *oneshot) {
    if (is_modifier_registered(oneshot)) {
        unregister_code(oneshot->modifier);
    }
    oneshot->trigger_down = false;
    oneshot->modifier_queued = false;
}

void consume_oneshot(oneshot_t *oneshot) {
    if (!oneshot->trigger_down && is_modifier_registered(oneshot)) {
        unregister_code(oneshot->modifier);
    }
    oneshot->modifier_queued = false;
}

void update_oneshot(oneshot_t *oneshot, uint16_t keycode, bool key_down) {    
    if (keycode == oneshot->trigger && keycode != KC_NO) {
        if (key_down) {
            hold_oneshot(oneshot);
        } else {
            release_oneshot(oneshot);
        }
    }
    
    else if (key_down && is_oneshot_cancel_key(keycode)) {
        cancel_oneshot(oneshot);
    }
    
    else if (!key_down && is_oneshot_consuming_key(keycode)) {
        consume_oneshot(oneshot);
    }
}