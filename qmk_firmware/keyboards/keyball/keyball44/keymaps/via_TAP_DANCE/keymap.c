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
            KC_ESC , KC_Q , KC_W , KC_E , KC_R , KC_T ,                         KC_Y , KC_U , KC_I , KC_O , KC_P , KC_DEL ,
            KC_TAB , KC_A , KC_S , KC_D , KC_F , KC_G ,                         KC_H , KC_J , KC_K , KC_L , KC_SCLN, S(KC_7),
            KC_LSFT, KC_Z , KC_X , KC_C , KC_V , KC_B ,                         KC_N , KC_M , KC_COMM, KC_DOT , KC_SLSH, KC_INT1,
            KC_LALT, TD(TD_KANA_EISU), LCTL_T(KC_LNG2), LT(1,KC_SPC),
            KC_BSPC, LT(2,KC_ENT), RCTL_T(KC_LNG2), KC_RALT, KC_PSCR, KC_NO
            ),
          
          [1] = LAYOUT_universal(
            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_Y , KC_U , KC_I , KC_O , KC_P , KC_DEL ,
            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_H , KC_J , KC_K , KC_L , KC_SCLN, S(KC_7),
            KC_NO, KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_N , KC_M , KC_COMM, KC_DOT , KC_SLSH, KC_INT1,
            KC_NO, TD(TD_KANA_EISU), KC_NO, KC_NO,
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
            ),
          [2] = LAYOUT_universal(
            KC_ESC , KC_Q , KC_W , KC_E , KC_R , KC_T ,                         KC_Y , KC_U , KC_I , KC_O , KC_P , KC_DEL ,
            KC_TAB , KC_A , KC_S , KC_D , KC_F , KC_G ,                         KC_H , KC_J , KC_K , KC_L , KC_SCLN, S(KC_7),
            KC_LSFT, KC_Z , KC_X , KC_C , KC_V , KC_B ,                         KC_N , KC_M , KC_COMM, KC_DOT , KC_SLSH, KC_INT1,
            KC_LALT, TD(TD_KANA_EISU), LCTL_T(KC_LNG2), LT(1,KC_SPC),
            KC_BSPC, LT(2,KC_ENT), RCTL_T(KC_LNG2), KC_RALT, KC_PSCR, KC_NO
            ),
          [3] = LAYOUT_universal(
            KC_ESC , KC_Q , KC_W , KC_E , KC_R , KC_T ,                         KC_Y , KC_U , KC_I , KC_O , KC_P , KC_DEL ,
            KC_TAB , KC_A , KC_S , KC_D , KC_F , KC_G ,                         KC_H , KC_J , KC_K , KC_L , KC_SCLN, S(KC_7),
            KC_LSFT, KC_Z , KC_X , KC_C , KC_V , KC_B ,                         KC_N , KC_M , KC_COMM, KC_DOT , KC_SLSH, KC_INT1,
            KC_LALT, TD(TD_KANA_EISU), LCTL_T(KC_LNG2), LT(1,KC_SPC),
            KC_BSPC, LT(2,KC_ENT), RCTL_T(KC_LNG2), KC_RALT, KC_PSCR, KC_NO
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
