#include QMK_KEYBOARD_H
#include "quantum.h"
#include "tap_dance.h"

enum {
  TD_KANA_EISU,
};

// --- ★追加: マウスロック状態管理フラグ ---
static bool is_btn1_locked = false;
static bool is_btn2_locked = false;

// --- ★追加: マウスボタンのトグル関数 ---
void toggle_mouse_btn1(void) {
  is_btn1_locked = !is_btn1_locked;
  if (is_btn1_locked) {
    register_code(KC_MS_BTN1);
  } else {
    unregister_code(KC_MS_BTN1);
  }
}

void toggle_mouse_btn2(void) {
  is_btn2_locked = !is_btn2_locked;
  if (is_btn2_locked) {
    register_code(KC_MS_BTN2);
  } else {
    unregister_code(KC_MS_BTN2);
  }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
          // keymap for default (VIA)
          [0] = LAYOUT_universal(
            KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                         KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
            KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                         KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
            KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                         KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
            KC_LALT,KC_LGUI,LCTL_T(KC_LNG2)     ,LT(1,KC_SPC),LT(3, TD(TD_KANA_EISU)),                  KC_BSPC,LT(2,KC_ENT), RCTL_T(KC_LNG2),     KC_RALT  , KC_PSCR
            ),
          [1] = LAYOUT_universal(
            SSNP_FRE ,  KC_F1   , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                          KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
            SSNP_VRT ,  _______ , _______  , KC_UP   , KC_ENT   , KC_DEL   ,                                          KC_PGUP  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_BTN3  , KC_F12   ,
            SSNP_HOR ,  _______ , KC_LEFT  , KC_DOWN , KC_RGHT  , KC_BSPC  ,                                          KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  , _______  ,
            _______  , _______ , _______  ,         _______  , _______  ,                  _______  , _______  , _______       , _______  , _______
            ),
          [2] = LAYOUT_universal(
            _______  ,S(KC_QUOT), KC_7     , KC_8    , KC_9     , S(KC_8)  ,                                          S(KC_9)  , S(KC_1)  , S(KC_6)  , KC_LBRC  , S(KC_4)  , _______  ,
            _______  ,S(KC_SCLN), KC_4     , KC_5    , KC_6     , KC_RBRC  ,                                          KC_NUHS  , KC_MINS  , S(KC_EQL), S(KC_3)  , KC_QUOT  , S(KC_2)  ,
            _______  ,S(KC_MINS), KC_1     , KC_2    , KC_3     ,S(KC_RBRC),                                         S(KC_NUHS),S(KC_INT1), KC_EQL   ,S(KC_LBRC),S(KC_SLSH),S(KC_INT3),
            KC_0     , KC_DOT  , _______  ,         _______  , _______  ,                  KC_DEL   , _______  , _______       , _______  , _______
            ),
          [3] = LAYOUT_universal(
            RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                          RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
            RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                                          RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
            RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                          CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
            QK_BOOT  , KBC_RST  , _______  ,        _______  , _______  ,                  _______  , _______  , _______       , KBC_RST  , QK_BOOT
            ),
        };
// clang-format on

void kana_eisu_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code(KC_LNG1); // かな
  } else if (state->count == 2) {
    tap_code(KC_LNG2); // 英数
  }
}

tap_dance_action_t tap_dance_actions[] = {
          [TD_KANA_EISU] = ACTION_TAP_DANCE_FN(kana_eisu_finished),
        };

// --- ★修正: process_record_user に特殊コンボロジックを追加 ---
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  
  // 1. 特殊コンボ処理（定義: 9/6 + Btn1, Btn1 + Btn2）
  if (record->event.pressed) {
    // • 9 + Btn1 -> Btn1 (トグル)
    if (keycode == KC_9) {
      // 9を押したとき、既にBtn1がロック中ならトグル（解除/再ロック）
      if (is_btn1_locked) {
        toggle_mouse_btn1();
        return true; // 9の移動機能はそのまま活かす
      }
    }
    
    // • 6 + Btn1 -> Btn1 (トグル)
    if (keycode == KC_6) {
      if (is_btn1_locked) {
        toggle_mouse_btn1();
        return true; 
      }
    }
    
    // • Btn1 + Btn2 -> Btn2 (トグル)
    // Btn2のキー(;)が押されたとき、Btn1がロック中ならBtn2をトグル
    if (keycode == KC_SCLN) { 
      if (is_btn1_locked) {
        toggle_mouse_btn2(); 
        return false; // ';' の入力を防ぐ
      }
    }
  }
  
  // 2. 既存のスクロール処理
  switch (keycode) {
  case KC_BSPC:
    if (layer_state_is(0) || layer_state_is(1)) {
      if (record->event.pressed) {
        keyball_set_scroll_mode(true);
      } else {
        // レイヤー3でなければ戻す
        if (get_highest_layer(layer_state) != 3) {
          keyball_set_scroll_mode(false);
        }
      }
    }
    return true;
  }
  return true;
}

#ifdef COMBO_ENABLE
// --- ★修正: コンボイベント定義 ---
enum combo_events {
  // ご要望のドラッグ・トグル用
  KL_BTN1, // K + L -> Btn1
  LS_BTN2, // L + ; -> Btn2 (L + : も兼ねる)
  
  // 既存の単発キー
  QW_ESC,
  MY_F7,
  YU_F8,
};

// コンボキーの組み合わせ定義
const uint16_t PROGMEM combo_kl[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_ls[] = {KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM combo_qw[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_my[] = {KC_MINS, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_yu[] = {KC_Y, KC_U, COMBO_END};

combo_t key_combos[] = {
          // ★修正: 新しいドラッグ用コンボを割り当て
          [KL_BTN1] = COMBO_ACTION(combo_kl),
          [LS_BTN2] = COMBO_ACTION(combo_ls),
          
          [QW_ESC] = COMBO_ACTION(combo_qw),
          [MY_F7]  = COMBO_ACTION(combo_my),
          [YU_F8]  = COMBO_ACTION(combo_yu),
        };
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  // Auto enable scroll mode when the highest layer is 3
  keyball_set_scroll_mode(get_highest_layer(state) == 3);
  return state;
}

#ifdef OLED_ENABLE
#    include "lib/oledkit/oledkit.h"
void oledkit_render_info_user(void) {
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();
  keyball_oled_render_layerinfo();
}
#endif

#ifdef COMBO_ENABLE
// --- ★修正: コンボ実行時の処理 ---
void process_combo_event(uint16_t combo_index, bool pressed) {
  // コンボは押下時のみトリガーし、あとはトグル関数に任せる
  if (pressed) {
    switch (combo_index) {
      
      // • K + L -> Btn1 (トグル)
    case KL_BTN1:
      toggle_mouse_btn1();
      break;
      
      // • L + ; -> Btn2 (トグル)
      // • L + : -> Btn2 (Shift押下時もここで反応)
    case LS_BTN2:
      toggle_mouse_btn2();
      break;
      
      // --- 単発キー系 ---
    case QW_ESC:
      tap_code(KC_ESC);
      break;
      
    case MY_F7:
      tap_code(KC_F7);
      break;
      
    case YU_F8:
      tap_code(KC_F8);
      break;
    }
  }
}
#endif