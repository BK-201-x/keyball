#include QMK_KEYBOARD_H

// --------------------------------------------------
// Tap Dance 定義
// --------------------------------------------------

enum {
  TD_KANA_EISU = 0,
};

// 1回: かな / 2回以上: 英数
void kana_eisu_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code(KC_LNG1);   // かな
  } else {
    tap_code(KC_LNG2);   // 英数（安全側）
  }
}

tap_dance_action_t tap_dance_actions[] = {
          [TD_KANA_EISU] = ACTION_TAP_DANCE_FN(kana_eisu_finished),
        };

// --------------------------------------------------
// Keymaps
// --------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
          
          [0] = LAYOUT(
            // ---------------- Left ----------------
            KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
            KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
            TD(TD_KANA_EISU), KC_LALT,   // ★ここが かな／英数
            
            // ---------------- Right ----------------
            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
            KC_SPC,  KC_RALT
            ),
        };
