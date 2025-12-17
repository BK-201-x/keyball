#include QMK_KEYBOARD_H
#include "quantum.h"

enum {
  TD_KANA_EISU,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
          [0] = LAYOUT_universal(
            KC_ESC , KC_Q , KC_W , KC_E , KC_R , KC_T ,                            KC_Y , KC_U , KC_I , KC_O , KC_P , KC_DEL ,
            KC_TAB , KC_A , KC_S , KC_D , KC_F , KC_G ,                            KC_H , KC_J , KC_K , KC_L , KC_SCLN , S(KC_7),
            KC_LSFT, KC_Z , KC_X , KC_C , KC_V , KC_B ,                            KC_N , KC_M , KC_COMM, KC_DOT , KC_SLSH , KC_INT1,
            KC_LALT, KC_LGUI, LCTL_T(KC_LNG2), LT(1,KC_SPC), LT(3,TD(TD_KANA_EISU)),
            KC_BSPC, LT(2,KC_ENT), RCTL_T(KC_LNG2), KC_RALT, KC_PSCR
            ),
          
          [1] = LAYOUT_universal(
            SSNP_FRE, KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                       KC_F6 , KC_F7 , KC_F8 , KC_F9 , KC_F10, KC_F11,
            SSNP_VRT, _______, _______, KC_UP , KC_ENT, KC_DEL,                   KC_PGUP, KC_BTN1, KC_UP , KC_BTN2, KC_BTN3, KC_F12,
            SSNP_HOR, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,                KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
            _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______
            ),
          
          [2] = LAYOUT_universal(
            _______, S(KC_QUOT), KC_7 , KC_8 , KC_9 , S(KC_8),                     S(KC_9), S(KC_1), S(KC_6), KC_LBRC, S(KC_4), _______,
            _______, S(KC_SCLN), KC_4 , KC_5 , KC_6 , KC_RBRC,                    KC_NUHS, KC_MINS, S(KC_EQL), S(KC_3), KC_QUOT, S(KC_2),
            _______, S(KC_MINS), KC_1 , KC_2 , KC_3 , S(KC_RBRC),                 S(KC_NUHS), S(KC_INT1), KC_EQL, S(KC_LBRC), S(KC_SLSH), S(KC_INT3),
            KC_0 , KC_DOT, _______, _______, _______,                  KC_DEL, _______, _______, _______, _______
            ),
          
          [3] = LAYOUT_universal(
            RGB_TOG, AML_TO , AML_I50, AML_D50, _______, _______,                  RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K,
            RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______, SCRL_DVI,                 RGB_M_X, RGB_M_G, RGB_M_T, RGB_M_TW, _______, _______,
            RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, SCRL_DVD,                CPI_D1K, CPI_D100, CPI_I100, CPI_I1K, _______, KBC_SAVE,
            QK_BOOT, KBC_RST, _______, _______, _______,                _______, _______, _______, KBC_RST, QK_BOOT
            ),
        };
// clang-format on

// ---------- Tap Dance ----------
void kana_eisu_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) tap_code(KC_LNG1);
  else if (state->count == 2) tap_code(KC_LNG2);
}

tap_dance_action_t tap_dance_actions[] = {
          [TD_KANA_EISU] = ACTION_TAP_DANCE_FN(kana_eisu_finished),
        };

// ---------- Scroll Control ----------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode == KC_BSPC) {
    if (layer_state_is(0) || layer_state_is(1)) {
      if (record->event.pressed) keyball_set_scroll_mode(true);
      else if (get_highest_layer(layer_state) != 3) keyball_set_scroll_mode(false);
    }
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  keyball_set_scroll_mode(get_highest_layer(state) == 3);
  return state;
}

// ---------- COMBO ----------
#ifdef COMBO_ENABLE

enum combo_events {
  IO_DRAG_BTN1,
  OP_DRAG_BTN2,
  
  MB1_KL, MB1_90, MB1_6SLSH,
  MB2_LSCLN, MB2_SLSHSCLN, MB2_0AST, MB2_0SCLN,
  
  F7_MINS7, F8_78,
  
  HOME_RBH, HOME_YENH, HOME_RB4,
  END_HJ, END_45,
  
  UP_AS, DOWN_ZX,
  PGUP_SD, PGUP_SLEFT, PGDN_XC,
};

const uint16_t PROGMEM combo_io[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_op[] = {KC_O, KC_P, COMBO_END};

const uint16_t PROGMEM combo_mb1_kl[]    = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_mb1_90[]    = {KC_9, KC_0, COMBO_END};
const uint16_t PROGMEM combo_mb1_6sl[]   = {KC_6, KC_SLSH, COMBO_END};

const uint16_t PROGMEM combo_mb2_ls[]    = {KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM combo_mb2_ss[]    = {KC_SLSH, KC_SCLN, COMBO_END};
const uint16_t PROGMEM combo_mb2_0a[]    = {KC_0, KC_8, COMBO_END};
const uint16_t PROGMEM combo_mb2_0s[]    = {KC_0, KC_SCLN, COMBO_END};

const uint16_t PROGMEM combo_f7[]        = {KC_MINS, KC_7, COMBO_END};
const uint16_t PROGMEM combo_f8[]        = {KC_7, KC_8, COMBO_END};

const uint16_t PROGMEM combo_home_rbh[]  = {KC_RBRC, KC_H, COMBO_END};
const uint16_t PROGMEM combo_home_yh[]   = {KC_BSLS, KC_H, COMBO_END};
const uint16_t PROGMEM combo_home_rb4[]  = {KC_RBRC, KC_4, COMBO_END};

const uint16_t PROGMEM combo_end_hj[]    = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM combo_end_45[]    = {KC_4, KC_5, COMBO_END};

const uint16_t PROGMEM combo_up_as[]     = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM combo_down_zx[]   = {KC_Z, KC_X, COMBO_END};

const uint16_t PROGMEM combo_pgup_sd[]   = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_pgup_sl[]   = {KC_S, KC_LEFT, COMBO_END};
const uint16_t PROGMEM combo_pgdn_xc[]   = {KC_X, KC_C, COMBO_END};

combo_t key_combos[] = {
          [IO_DRAG_BTN1] = COMBO_ACTION(combo_io),
          [OP_DRAG_BTN2] = COMBO_ACTION(combo_op),
          
          [MB1_KL] = COMBO_ACTION(combo_mb1_kl),
          [MB1_90] = COMBO_ACTION(combo_mb1_90),
          [MB1_6SLSH] = COMBO_ACTION(combo_mb1_6sl),
          
          [MB2_LSCLN] = COMBO_ACTION(combo_mb2_ls),
          [MB2_SLSHSCLN] = COMBO_ACTION(combo_mb2_ss),
          [MB2_0AST] = COMBO_ACTION(combo_mb2_0a),
          [MB2_0SCLN] = COMBO_ACTION(combo_mb2_0s),
          
          [F7_MINS7] = COMBO_ACTION(combo_f7),
          [F8_78] = COMBO_ACTION(combo_f8),
          
          [HOME_RBH] = COMBO_ACTION(combo_home_rbh),
          [HOME_YENH] = COMBO_ACTION(combo_home_yh),
          [HOME_RB4] = COMBO_ACTION(combo_home_rb4),
          
          [END_HJ] = COMBO_ACTION(combo_end_hj),
          [END_45] = COMBO_ACTION(combo_end_45),
          
          [UP_AS] = COMBO_ACTION(combo_up_as),
          [DOWN_ZX] = COMBO_ACTION(combo_down_zx),
          
          [PGUP_SD] = COMBO_ACTION(combo_pgup_sd),
          [PGUP_SLEFT] = COMBO_ACTION(combo_pgup_sl),
          [PGDN_XC] = COMBO_ACTION(combo_pgdn_xc),
        };

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch (combo_index) {
    
  case IO_DRAG_BTN1:
  case MB1_KL:
  case MB1_90:
  case MB1_6SLSH:
    pressed ? register_code(KC_MS_BTN1) : unregister_code(KC_MS_BTN1);
    break;
    
  case OP_DRAG_BTN2:
  case MB2_LSCLN:
  case MB2_SLSHSCLN:
  case MB2_0AST:
  case MB2_0SCLN:
    pressed ? register_code(KC_MS_BTN2) : unregister_code(KC_MS_BTN2);
    break;
    
  case F7_MINS7:
    if (pressed) tap_code(KC_F7);
    break;
  case F8_78:
    if (pressed) tap_code(KC_F8);
    break;
    
  case HOME_RBH:
  case HOME_YENH:
  case HOME_RB4:
    if (pressed) tap_code(KC_HOME);
    break;
    
  case END_HJ:
  case END_45:
    if (pressed) tap_code(KC_END);
    break;
    
  case UP_AS:
    if (pressed) tap_code(KC_UP);
    break;
  case DOWN_ZX:
    if (pressed) tap_code(KC_DOWN);
    break;
    
  case PGUP_SD:
  case PGUP_SLEFT:
    if (pressed) tap_code(KC_PGUP);
    break;
    
  case PGDN_XC:
    if (pressed) tap_code(KC_PGDN);
    break;
  }
}
#endif

// ---------- OLED ----------
#ifdef OLED_ENABLE
#include "lib/oledkit/oledkit.h"
void oledkit_render_info_user(void) {
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();
  keyball_oled_render_layerinfo();
}
#endif
