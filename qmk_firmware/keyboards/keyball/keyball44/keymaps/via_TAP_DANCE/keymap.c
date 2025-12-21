#include QMK_KEYBOARD_H

// =====================================================
// Tap Dance 定義
// =====================================================
enum {
  TD_KANA_EISU,
};

void kana_eisu_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code(KC_LNG1); // かな
  } else {
    tap_code(KC_LNG2); // 英数
  }
}

tap_dance_action_t tap_dance_actions[] = {
          [TD_KANA_EISU] = ACTION_TAP_DANCE_FN(kana_eisu_finished),
        };

// =====================================================
// Keymaps
// =====================================================
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
          
          [0] = LAYOUT_universal(
            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO , KC_NO , KC_NO, KC_NO,
            KC_NO, KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO, KC_NO , KC_NO, KC_NO,
            KC_NO, TD(TD_KANA_EISU), KC_NO, KC_NO,
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NUBS
            ),
          
          [1] = LAYOUT_universal(
            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO , KC_NO , KC_NO, KC_NO,
            KC_NO, KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO, KC_NO , KC_NO, KC_NO,
            KC_NO, TD(TD_KANA_EISU), KC_NO, KC_NO,
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NUBS
            ),
          [2] = LAYOUT_universal(
            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO , KC_NO , KC_NO, KC_NO,
            KC_NO, KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO, KC_NO , KC_NO, KC_NO,
            KC_NO, TD(TD_KANA_EISU), KC_NO, KC_NO,
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
            ),
          [3] = LAYOUT_universal(
            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO , KC_NO , KC_NO, KC_NO,
            KC_NO, KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO, KC_NO , KC_NO, KC_NO,
            KC_NO, TD(TD_KANA_EISU), KC_NO, KC_NO,
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
            ),
        };
// clang-format on

// =====================================================
// Layer hook
// =====================================================
layer_state_t layer_state_set_user(layer_state_t state) {
  keyball_set_scroll_mode(get_highest_layer(state) == 3);
  return state;
}

// =====================================================
// OLED
// =====================================================
#ifdef OLED_ENABLE
#include "lib/oledkit/oledkit.h"
void oledkit_render_info_user(void) {
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();
  keyball_oled_render_layerinfo();
}
#endif
