#include QMK_KEYBOARD_H

/* ==============================
 * Layer definitions
 * ============================== */
enum layer_names {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
};

/* ==============================
 * Custom keycodes
 * ============================== */
enum custom_keycodes {
  KANA_EISU = SAFE_RANGE
};

/* ==============================
 * Variables for double tap
 * ============================== */
static uint16_t kana_timer = 0;
static uint8_t  kana_tap_count = 0;

/* ==============================
 * Keymaps
 * ============================== */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
          [_BASE] = LAYOUT(
            /* 左手 */                     /* 右手 */
            KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,     KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,
            KC_A,  KC_S,  KC_D,  KC_F,  KC_G,     KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN,
            KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,     KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH,
            KC_LCTL, KC_LALT,  KC_SPC,  KANA_EISU, KC_ENT
            ),
          
          [_LOWER] = LAYOUT(
            _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______
            ),
          
          [_RAISE] = LAYOUT(
            _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______
            ),
          
          [_ADJUST] = LAYOUT(
            _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______
            )
        };

/* ==============================
 * Key processing
 * ============================== */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KANA_EISU:
    if (record->event.pressed) {
      if (kana_tap_count == 0) {
        kana_timer = timer_read();
      }
      kana_tap_count++;
    }
    return false;
  }
  return true;
}

/* ==============================
 * Scan (for double tap decision)
 * ============================== */
void matrix_scan_user(void) {
  if (kana_tap_count > 0 && timer_elapsed(kana_timer) > 200) {
    if (kana_tap_count == 1) {
      tap_code(KC_LANG1); // かな
    } else {
      tap_code(KC_LANG2); // 英数
    }
    kana_tap_count = 0;
  }
}
