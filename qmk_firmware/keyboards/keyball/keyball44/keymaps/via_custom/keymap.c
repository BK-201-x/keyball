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
#include "quantum.h"

/* =========================
 * Custom Keycodes
 * ========================= */
enum custom_keycodes {
  NUBS_AT_GRV = SAFE_RANGE,
  KANA_EN,
};

/* =========================
 * Tap Dance Enum
 * ========================= */
enum {
  TD_TG1_TG3,
  TD_KANA_EN,
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
            _______, _______, _______, _______, _______, _______,            _______, KC_F7, KC_F8, _______, _______, _______,
            _______, _______, _______, KC_UP, _______, _______,             _______, _______, KC_UP, _______, _______, _______,
            _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,           _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
            _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______
            ),
          [2] = LAYOUT_universal(
            _______, _______, KC_7, KC_8, KC_9, _______,            _______, _______, _______, _______, _______, _______,
            _______, _______, KC_4, KC_5, KC_6, _______,            _______, _______, _______, _______, _______, _______,
            _______, _______, KC_1, KC_2, KC_3, _______,            _______, _______, _______, _______, _______, _______,
            KC_0, KC_DOT, _______, _______, _______,              KC_DEL, _______, _______, _______, _______
            ),
          [3] = LAYOUT_universal(
            RGB_TOG, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
            RGB_MOD, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
            RGB_RMOD, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
            QK_BOOT, KBC_RST, _______, _______, _______,             _______, _______, _______, KBC_RST, QK_BOOT
            ),
        };

/* =========================
 * Tap Dance Functions
 * ========================= */
void tg1_tg3_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
      layer_invert(1);  // 1回タップ
    } else {
      layer_invert(3);  // 長押し
    }
  } else if (state->count == 2) {
    layer_invert(1);
    layer_invert(3);
  }
}

void kana_en_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    // 1回タップ：かな
    tap_code(KC_LANG1);
  } else if (state->count == 2) {
    // 2回タップ：英数
    tap_code(KC_LNG2);
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
 * process_record_user
 * ========================= */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case NUBS_AT_GRV:
    if (record->event.pressed) {
      if (get_mods() & MOD_MASK_SHIFT) {
        tap_code(KC_GRV);        // 半角/全角
      } else {
        tap_code16(S(KC_2));    // @
      }
    }
    return false;
  }
  return true;
}

/* =========================
 * COMBO
 * ========================= */
#ifdef COMBO_ENABLE

enum combo_events {
  // Mouse
  KL_BTN1,
  LS_BTN2,
  // F keys
  TO7_F7,
  SE_F8,
  // Home / End
  RH_HOME,
  YH_HOME,
  HJ_END,
  F45_END,
};

const uint16_t PROGMEM combo_kl[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_ls[] = {KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM combo_to7[] = {TO(0), KC_7, COMBO_END};
const uint16_t PROGMEM combo_se[] = {KC_7, KC_8, COMBO_END};
const uint16_t PROGMEM combo_rh[] = {KC_RBRC, KC_H, COMBO_END};
const uint16_t PROGMEM combo_yh[] = {KC_NUHS, KC_H, COMBO_END};
const uint16_t PROGMEM combo_hj[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM combo_f45[] = {KC_4, KC_5, COMBO_END};

combo_t key_combos[] = {
          [KL_BTN1]  = COMBO_ACTION(combo_kl),
          [LS_BTN2]  = COMBO_ACTION(combo_ls),
          [TO7_F7]   = COMBO_ACTION(combo_to7),
          [SE_F8]    = COMBO_ACTION(combo_se),
          [RH_HOME]  = COMBO_ACTION(combo_rh),
          [YH_HOME]  = COMBO_ACTION(combo_yh),
          [HJ_END]   = COMBO_ACTION(combo_hj),
          [F45_END]  = COMBO_ACTION(combo_f45),
        };

void process_combo_event(uint16_t combo_index, bool pressed) {
  if (!pressed) return;
  
  switch (combo_index) {
  case KL_BTN1: tap_code(KC_MS_BTN1); break;
  case LS_BTN2: tap_code(KC_MS_BTN2); break;
  case TO7_F7:  tap_code(KC_F7); break;
  case SE_F8:   tap_code(KC_F8); break;
  case RH_HOME:
  case YH_HOME: tap_code(KC_HOME); break;
  case HJ_END:
  case F45_END: tap_code(KC_END); break;
  }
}

#endif
