#pragma once

// 定義するコンボの数（K+L と L+; の2つ）
#define COMBO_COUNT 2

// 同時押しの判定時間（ミリ秒）。うまくいかない場合はここを長めに（50〜100）調整してください。
#define COMBO_TERM 40

// コンボ実行中に修飾キー（Shiftなど）や他のキー入力を許可する設定
// これにより 9+Btn1 のような「移動しながらの操作」がスムーズになります
#define COMBO_ALLOW_ACTION_KEYS

#ifdef RGBLIGHT_ENABLE
//#    define RGBLIGHT_EFFECT_BREATHING
//#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#    define RGBLIGHT_EFFECT_SNAKE
//#    define RGBLIGHT_EFFECT_KNIGHT
//#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#    define RGBLIGHT_EFFECT_RGB_TEST
//#    define RGBLIGHT_EFFECT_ALTERNATING
//#    define RGBLIGHT_EFFECT_TWINKLE
#endif

#define TAP_CODE_DELAY 5

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 1
