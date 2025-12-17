#include QMK_KEYBOARD_H

enum layer_names {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum custom_keycodes {
  KANA_EISU = SAFE_RANGE,
};

static uint16_t kana_timer;
static bool kana_waiting = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
          
          [_BASE] = LAYOUT_no_ball(
            KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
            KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
            KC_LCTL, KC_LALT, KC_LGUI, LT(_LOWER, KC_SPC), LT(_RAISE, KANA_EISU),
            KC_RALT, KC_NO,   KC_NO,   KC_NO,   KC_RCTL
            ),
          
          [_LOWER] = LAYOUT_no_ball(
            KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
            KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
            KC_LCTL, KC_LALT, KC_LGUI, _______, _______, 
            KC_RALT, KC_NO,   KC_NO,   KC_NO,   KC_RCTL
            ),
          
          [_RAISE] = LAYOUT_no_ball(
            KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
            KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
            KC_LCTL, KC_LALT, KC_LGUI, _______, _______, 
            KC_RALT, KC_NO,   KC_NO,   KC_NO,   KC_RCTL
            ),
          
          [_ADJUST] = LAYOUT_no_ball(
            KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
            KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
            KC_LCTL, KC_LALT, KC_LGUI, _______, _______, 
            KC_RALT, KC_NO,   KC_NO,   KC_NO,   KC_RCTL
            ),
        };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode == KANA_EISU && record->event.pressed) {
    if (kana_waiting && timer_elapsed(kana_timer) < TAPPING_TERM) {
      kana_waiting = false;
      tap_code(KC_LNG2); // 英数
    } else {
      kana_waiting = true;
      kana_timer = timer_read();
    }
    return false;
  }
  return true;
}

void matrix_scan_user(void) {
  if (kana_waiting && timer_elapsed(kana_timer) > TAPPING_TERM) {
    kana_waiting = false;
    tap_code(KC_LNG1); // かな
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  keyball_set_scroll_mode(get_highest_layer(state) == _ADJUST);
  return state;
}

#ifdef OLED_ENABLE
#  include "lib/oledkit/oledkit.h"
void oledkit_render_info_user(void) {
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();
  keyball_oled_render_layerinfo();
}
#endif
