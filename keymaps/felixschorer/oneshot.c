#include QMK_KEYBOARD_H
#include "oneshot.h"

void queue_oneshot(oneshot_t *oneshot) {
    if (!oneshot->trigger_down && !oneshot->modifier_queued) {
        register_code(oneshot->modifier);
    }
    oneshot->trigger_down = true;
    oneshot->modifier_queued = true;
}

void release_oneshot(oneshot_t *oneshot) {
    if (!oneshot->modifier_queued) {
        unregister_code(oneshot->modifier);
    }
    oneshot->trigger_down = false;
}

void cancel_oneshot(oneshot_t *oneshot) {
    unregister_code(oneshot->modifier);
    oneshot->trigger_down = false;
    oneshot->modifier_queued = false;
}

void consume_oneshot(oneshot_t *oneshot) {
    if (!oneshot->trigger_down) {
        unregister_code(oneshot->modifier);
    }
    oneshot->modifier_queued = false;
}

void update_oneshot(oneshot_t *oneshot, uint16_t keycode, keyrecord_t *record) {
    bool key_down = record->event.pressed;
    
    if (keycode == oneshot->trigger) {
        if (key_down) {
            queue_oneshot(oneshot);
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