/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

/* =========================
 * Custom Keycodes
 * ========================= */
enum custom_keycodes {
  NUBS_AT_GRV = SAFE_RANGE, // Non-US \ and |
};

/* =========================
 * Tap Dance Enum
 * ========================= */
enum {
  TD_TG1_TG3,
  TD_KANA_EN,
};

/* =========================
 * Tap Dance Functions
 * ========================= */
void tg1_tg3_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_invert(1); // 単押し → レイヤー1
  } else if (state->pressed) {
    layer_invert(3); // 長押し → レイヤー3
  }
}

void kana_en_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code(KC_LNG1); // かな
  } else if (state->count == 2) {
    tap_code(KC_LNG2); // 英数
  }
}

/* =========================
 * Tap Dance Actions
 * ========================= */
tap_dance_action_t tap_dance_actions[] = {
          [TD_TG1_TG3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tg1_tg3_finished, NULL),
          [TD_KANA_EN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, kana_en_finished, NULL),
        };

/* =========================
 * Keymaps
 * ========================= */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
          [0] = LAYOUT_universal(
            KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T,             KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL,
            KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_H, KC_J, KC_K, KC_L, KC_SCLN, NUBS_AT_GRV,
            KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,            KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_INT1,
            KC_LALT, KC_LGUI, TD(TD_TG1_TG3), LT(1, KC_SPC), TD(TD_KANA_EN),
            KC_BSPC, LT(2, KC_ENT), KC_RCTL, KC_RALT, KC_PSCR
            ),
          [1] = LAYOUT_universal(
            _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______
            ),
          [2] = LAYOUT_universal(
            _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______
            ),
          [3] = LAYOUT_universal(
            _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______
            ),
        };

/* =========================
 * NUBS カスタム処理
 * ========================= */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case NUBS_AT_GRV:
    if (record->event.pressed) {
      if (get_mods() & MOD_MASK_SHIFT) {
        tap_code(KC_LNG2); // Shift + NUBS → 半角/英数切替
      } else {
        tap_code16(S(KC_2)); // 単押し → Shift+2 (@)
      }
    }
    return false;
  }
  return true;
}

/* =========================
 * Optional COMBOs (簡易例)
 * ========================= */
#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_example[] = {KC_A, KC_B, COMBO_END};
combo_t key_combos[] = {
          [0] = COMBO_ACTION(combo_example),
        };
void process_combo_event(uint16_t combo_index, bool pressed) {
  if (!pressed) return;
  switch(combo_index) {
  case 0: tap_code(KC_C); break;
  }
}
#endif
