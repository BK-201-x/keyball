#include QMK_KEYBOARD_H
#include "quantum.h"

// =====================================================
// Tap Dance 定義
// Re map配列変更不可
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
// キー追加
// layer切り替え
// : * Mac OS
// @ "
// Re map配列変更不可
// =====================================================
enum custom_keycodes {
  LT_1_3 = SAFE_RANGE,
  KC_SCLN_STAR,
  KC_S2_SQUOT,
};

static uint16_t lt13_timer;
// =====================================================
//layer切り替え
// =====================================================
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
  case LT_1_3:
    if (record->event.pressed) {
      lt13_timer = timer_read();
    } else {
      if (timer_elapsed(lt13_timer) < TAPPING_TERM) {
        layer_move(1);  // タップ
      } else {
        layer_move(3);  // 長押し
      }
    }
    return false;
  }
  return true;
}

// =====================================================
//特殊キー
// =====================================================
  switch (keycode) {
    
  case KC_SCLN_STAR:
    if (record->event.pressed) {
      uint8_t mods = get_mods() | get_oneshot_mods();
      clear_mods();
      clear_oneshot_mods();
      
      if (mods & MOD_MASK_SHIFT) {
        tap_code16(S(KC_8));      // Shift + 8
      } else {
        tap_code16(S(KC_SCLN));   // Shift + ;
      }
      
      set_mods(mods);
    }
    return false;
    
  case KC_2_ZEN:
    if (record->event.pressed) {
      uint8_t mods = get_mods() | get_oneshot_mods();
      clear_mods();
      clear_oneshot_mods();
      
    if (mods & MOD_MASK_SHIFT) {
      tap_code16(S(KC_QUOT));  // Shift＋タップ → Shift + KC_QUOT
    } else {
      tap_code16(S(KC_2));     // タップ → Shift + 2
    }
      
      set_mods(mods);
    }
    return false;
  }
  
  return true;
}

// =====================================================
// Keymaps
// =====================================================
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
          
          [0] = LAYOUT_universal(
            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
          KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO , KC_NO , KC_NO, KC_SCLN_STAR,
            KC_NO, KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO, KC_NO , KC_NO, KC_NO,
            KC_NO, TD(TD_KANA_EISU), KC_NO, KC_NO,
          LT_1_3, KC_NO, KC_NO, KC_NO, KC_NO, KC_S2_SQUOT
            ),
          
          [1] = LAYOUT_universal(
            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO , KC_NO , KC_NO, KC_NO,
            KC_NO, KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,                         KC_NO , KC_NO , KC_NO, KC_NO , KC_NO, KC_NO,
            KC_NO, TD(TD_KANA_EISU), KC_NO, KC_NO,
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
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
#ifdef COMBO_ENABLE
enum combo_events {
  IO_DRAG_BTN1,
  OP_DRAG_BTN2,
  
  QW_ESC,
  MY_F7,
  YU_F8,
  
  // ---- 追加分 ----
  
  // Mouse Btn1
  MB1_KL,
  MB1_90,
  MB1_6SLSH,
  
  // Mouse Btn2
  MB2_LSCLN,
  MB2_SLSHSCLN,
  MB2_0AST,
  MB2_0SCLN,
  
  // F
  F7_MINS7,
  F8_78,
  
  // Home
  HOME_RBH,
  HOME_YENH,
  HOME_RB4,
  
  // End
  END_HJ,
  END_45,
  
  // Arrow
  UP_AS,
  DOWN_ZX,
  
  // Page
  PGUP_SD,
  PGUP_SLEFT,
  PGDN_XC,
};

// --- 既存 ---
const uint16_t PROGMEM combo_io[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_op[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_qw[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_my[] = {KC_MINS, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_yu[] = {KC_Y, KC_U, COMBO_END};
// --- Mouse Btn1 ---
const uint16_t PROGMEM combo_mb1_kl[]     = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_mb1_90[]     = {KC_9, KC_0, COMBO_END};
const uint16_t PROGMEM combo_mb1_6slsh[]  = {KC_6, KC_SLSH, COMBO_END};

// --- Mouse Btn2 ---
const uint16_t PROGMEM combo_mb2_lscln[]  = {KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM combo_mb2_slshsc[] = {KC_SLSH, KC_SCLN, COMBO_END};
const uint16_t PROGMEM combo_mb2_0ast[]   = {KC_0, KC_8, COMBO_END};   // shift+8 = *
const uint16_t PROGMEM combo_mb2_0scln[]  = {KC_0, KC_SCLN, COMBO_END};

// --- F ---
const uint16_t PROGMEM combo_f7_m7[]      = {KC_MINS, KC_7, COMBO_END};
const uint16_t PROGMEM combo_f8_78[]      = {KC_7, KC_8, COMBO_END};

// --- Home ---
const uint16_t PROGMEM combo_home_rbh[]   = {KC_RBRC, KC_H, COMBO_END};
const uint16_t PROGMEM combo_home_yenh[]  = {KC_BSLS, KC_H, COMBO_END}; // ¥
const uint16_t PROGMEM combo_home_rb4[]   = {KC_RBRC, KC_4, COMBO_END};

// --- End ---
const uint16_t PROGMEM combo_end_hj[]     = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM combo_end_45[]     = {KC_4, KC_5, COMBO_END};

// --- Arrow ---
const uint16_t PROGMEM combo_up_as[]      = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM combo_down_zx[]    = {KC_Z, KC_X, COMBO_END};

// --- Page ---
const uint16_t PROGMEM combo_pgup_sd[]    = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_pgup_sleft[] = {KC_S, KC_LEFT, COMBO_END};
const uint16_t PROGMEM combo_pgdn_xc[]    = {KC_X, KC_C, COMBO_END};

combo_t key_combos[] = {
          [IO_DRAG_BTN1] = COMBO_ACTION(combo_io),
          [OP_DRAG_BTN2] = COMBO_ACTION(combo_op),
          
          [QW_ESC] = COMBO_ACTION(combo_qw),
          [MY_F7]  = COMBO_ACTION(combo_my),
          [YU_F8]  = COMBO_ACTION(combo_yu),
          
          // --- Mouse Btn1 ---
          [MB1_KL]     = COMBO_ACTION(combo_mb1_kl),
          [MB1_90]     = COMBO_ACTION(combo_mb1_90),
          [MB1_6SLSH]  = COMBO_ACTION(combo_mb1_6slsh),
          
          // --- Mouse Btn2 ---
          [MB2_LSCLN]  = COMBO_ACTION(combo_mb2_lscln),
          [MB2_SLSHSCLN]= COMBO_ACTION(combo_mb2_slshsc),
          [MB2_0AST]   = COMBO_ACTION(combo_mb2_0ast),
          [MB2_0SCLN]  = COMBO_ACTION(combo_mb2_0scln),
          
          // --- F ---
          [F7_MINS7]   = COMBO_ACTION(combo_f7_m7),
          [F8_78]      = COMBO_ACTION(combo_f8_78),
          
          // --- Home / End ---
          [HOME_RBH]   = COMBO_ACTION(combo_home_rbh),
          [HOME_YENH]  = COMBO_ACTION(combo_home_yenh),
          [HOME_RB4]   = COMBO_ACTION(combo_home_rb4),
          [END_HJ]     = COMBO_ACTION(combo_end_hj),
          [END_45]     = COMBO_ACTION(combo_end_45),
          
          // --- Arrow / Page ---
          [UP_AS]      = COMBO_ACTION(combo_up_as),
          [DOWN_ZX]    = COMBO_ACTION(combo_down_zx),
          [PGUP_SD]    = COMBO_ACTION(combo_pgup_sd),
          [PGUP_SLEFT] = COMBO_ACTION(combo_pgup_sleft),
          [PGDN_XC]    = COMBO_ACTION(combo_pgdn_xc),
        };


#endif

// =====================================================
// Layer hook
// =====================================================

layer_state_t layer_state_set_user(layer_state_t state) {
  // Auto enable scroll mode when the highest layer is 3
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

// =====================================================
// COMBO
// =====================================================

#ifdef COMBO_ENABLE
void process_combo_event(uint16_t combo_index, bool pressed) {
  switch (combo_index) {
    
    // --- ドラッグ系（押下／解放 両方処理） ---
  case IO_DRAG_BTN1:
    if (pressed) {
      register_code(KC_MS_BTN1);
    } else {
      unregister_code(KC_MS_BTN1);
    }
    break;
    
  case OP_DRAG_BTN2:
    if (pressed) {
      register_code(KC_MS_BTN2);
    } else {
      unregister_code(KC_MS_BTN2);
    }
    break;
    
    // --- 単発キー系（押下時のみ） ---
  case QW_ESC:
    if (pressed) tap_code(KC_ESC);
    break;
    
  case MY_F7:
    if (pressed) tap_code(KC_F7);
    break;
    
  case YU_F8:
    if (pressed) tap_code(KC_F8);
    break;
    
    // --- Mouse Btn1（ドラッグ対応） ---
  case MB1_KL:
  case MB1_90:
  case MB1_6SLSH:
    if (pressed) register_code(KC_MS_BTN1);
    else         unregister_code(KC_MS_BTN1);
    break;
    
    // --- Mouse Btn2（ドラッグ対応） ---
  case MB2_LSCLN:
  case MB2_SLSHSCLN:
  case MB2_0AST:
  case MB2_0SCLN:
    if (pressed) register_code(KC_MS_BTN2);
    else         unregister_code(KC_MS_BTN2);
    break;
    
    // --- F ---
  case F7_MINS7:
    if (pressed) tap_code(KC_F7);
    break;
  case F8_78:
    if (pressed) tap_code(KC_F8);
    break;
    
    // --- Home / End ---
  case HOME_RBH:
  case HOME_YENH:
  case HOME_RB4:
    if (pressed) tap_code(KC_HOME);
    break;
    
  case END_HJ:
  case END_45:
    if (pressed) tap_code(KC_END);
    break;
    
    // --- Arrow ---
  case UP_AS:
    if (pressed) tap_code(KC_UP);
    break;
  case DOWN_ZX:
    if (pressed) tap_code(KC_DOWN);
    break;
    
    // --- Page ---
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
