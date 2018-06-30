#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // Thumb Shift
#define QWER 1 // QWERTY (not made yet)


enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = KEYMAP(
// layer 0: Thumb Shift
// left hand
KC_ESC,  M(0),  M(1) , M(2),  M(3),  M(4),  KC_NO,
KC_TAB,  M(10), M(11), M(12), M(13), M(14), KC_NO,
KC_TAB,  M(20), M(21), M(22), M(23), M(24),
KC_LSFT, M(30), M(31), M(32), M(33), M(34), KC_NO,
LT(1),   KC_NO, KC_NO, KC_NO, KC_NO,

/*   */ KC_NO,    KC_NO,
/*           */   KC_NO,
M(100), KC_SPACE, KC_NO,

// right hand
KC_NO,   M(5),  M(6),  M(7),  M(8),  M(9),  KC_BSPACE,
KC_NO,   M(15), M(16), M(17), M(18), M(19), KC_NO,
/*    */ M(25), M(26), M(27), M(28), M(29), KC_NO,
KC_NO,   M(35), M(36), M(37), M(38), M(39), KC_NO,
/*           */ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

KC_NO, KC_NO,
KC_NO,
KC_NO, KC_ENTER, M(101)
),



[QWER] = KEYMAP(
// layer 1: QWERTY (not made yet)
// left hand
KC_ESC,   KC_1,         KC_2,           KC_3,    KC_4,    KC_5,   RESET,
KC_TAB,   KC_Q,         KC_W,           KC_E,    KC_R,    KC_T,   KC_UP,
KC_TAB,   KC_A,         KC_S,           KC_D,    KC_F,    KC_G,
KC_LSFT,  KC_Z,         KC_X,           KC_C,    KC_V,    KC_B,  KC_DOWN,
LT(0),    KC_QUOT,      LALT(KC_LSFT),  KC_LEFT, KC_RGHT,

ALT_T(KC_APP),  KC_LGUI,
/*          */  KC_HOME,
KC_MHEN,KC_SPC,KC_END,

// right hand
KC_RGHT,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_BSPACE,
KC_NO,    KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_BSLS,
KC_H,   KC_J,  KC_K,   KC_L,   KC_SCLN,  KC_QUOT,
MEH_T(KC_NO),KC_N,   KC_M,  KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
KC_UP, KC_DOWN,KC_LBRC,KC_RBRC,          KC_FN1,

KC_LALT,        CTL_T(KC_ESC),
KC_PGUP,
KC_PGDN, KC_ENT, KC_HENK
    ),

};

const uint16_t PROGMEM fn_actions[] = {
//    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)
// FN1 - Momentary Layer 1 (Symbols)
};

bool isLeftShiftPressed = false;
bool isRightShiftPressed = false;

typedef struct {
  uint8_t macro_id;
  uint16_t base[3];
  uint16_t lshift[3];
  uint16_t rshift[3];
} macro_to_sequence_t;

const macro_to_sequence_t macro_to_sequence[] = {
/*M(0):  1 ? ?       */ {.base={KC_1}, .lshift={KC_NO, 1}, .rshift={KC_NO, 2}},
/*M(1):  2 ? ?       */ {.base={KC_2}, .lshift={KC_NO, 3}, .rshift={KC_NO, 4}},
/*M(2):  3 ? ?       */ {.base={KC_3}, .lshift={KC_NO, 5}, .rshift={KC_NO, 6}},
/*M(3):  4 ? ?       */ {.base={KC_4}, .lshift={KC_NO, 7}, .rshift={KC_NO, 8}},
/*M(4):  5 ? ?       */ {.base={KC_5}, .lshift={KC_NO, 9}, .rshift={KC_NO, 10}},
/*M(5):  6 ? ?       */ {.base={KC_6}, .lshift={KC_NO, 11}, .rshift={KC_NO, 12}},
/*M(6):  7 ? ?       */ {.base={KC_7}, .lshift={KC_NO, 13}, .rshift={KC_NO, 14}},
/*M(7):  8 ? ?       */ {.base={KC_8}, .lshift={KC_NO, 15}, .rshift={KC_NO, 16}},
/*M(8):  9 ? ?       */ {.base={KC_9}, .lshift={KC_NO, 17}, .rshift={KC_NO, 18}},
/*M(9):  0 ? ?       */ {.base={KC_0}, .lshift={KC_NO, 19}, .rshift={KC_NO, 20}},
/*M(10): ? xa ?      */ {.base={KC_NO, 21}, .lshift={KC_X, KC_A}, .rshift={KC_NO, 22}},
/*M(11): ka e ga     */ {.base={KC_K, KC_A}, .lshift={KC_E}, .rshift={KC_G, KC_A}},
/*M(12): ta ri da    */ {.base={KC_T, KC_A}, .lshift={KC_R, KC_I}, .rshift={KC_D, KC_A}},
/*M(13): ko xya go   */ {.base={KC_K, KC_O}, .lshift={KC_X, KC_Y, KC_A}, .rshift={KC_G, KC_O}},
/*M(14): sa re za    */ {.base={KC_S, KC_A}, .lshift={KC_R, KC_E}, .rshift={KC_Z, KC_A}},
/*M(15): ra pa yo    */ {.base={KC_R, KC_A}, .lshift={KC_P, KC_A}, .rshift={KC_Y, KC_O}},
/*M(16): ti di ni    */ {.base={KC_T, KC_I}, .lshift={KC_D, KC_I}, .rshift={KC_N, KC_I}},
/*M(17): ku gu ru    */ {.base={KC_K, KC_U}, .lshift={KC_G, KC_U}, .rshift={KC_R, KC_U}},
/*M(18): tu du ma    */ {.base={KC_T, KC_U}, .lshift={KC_D, KC_U}, .rshift={KC_M, KC_A}},
/*M(19): ? pi xe     */ {.base={KC_NO, 23}, .lshift={KC_P, KC_I}, .rshift={KC_X, KC_E}},
/*M(20): u wo vu     */ {.base={KC_U}, .lshift={KC_W, KC_O}, .rshift={KC_V, KC_U}},
/*M(21): si a ji     */ {.base={KC_S, KC_I}, .lshift={KC_A}, .rshift={KC_J, KC_I}},
/*M(22): te na de    */ {.base={KC_T, KC_E}, .lshift={KC_N, KC_A}, .rshift={KC_D, KC_E}},
/*M(23): ke xyu ge   */ {.base={KC_K, KC_E}, .lshift={KC_X, KC_Y, KC_U}, .rshift={KC_G, KC_E}},
/*M(24): se mo ze    */ {.base={KC_S, KC_E}, .lshift={KC_M, KC_O}, .rshift={KC_Z, KC_E}},
/*M(25): ha ba mi    */ {.base={KC_H, KC_A}, .lshift={KC_B, KC_A}, .rshift={KC_M, KC_I}},
/*M(26): to do o     */ {.base={KC_T, KC_O}, .lshift={KC_D, KC_O}, .rshift={KC_O}},
/*M(27): ki gi no    */ {.base={KC_K, KC_I}, .lshift={KC_G, KC_I}, .rshift={KC_N, KC_O}},
/*M(28): i po xyo    */ {.base={KC_I}, .lshift={KC_P, KC_O}, .rshift={KC_X, KC_Y, KC_O}},
/*M(29): nn ? xtu    */ {.base={KC_N, KC_N}, .lshift={KC_NO, 24}, .rshift={KC_X, KC_T, KC_U}},
/*M(30): ? xu ?     */ {.base={KC_NO, 25}, .lshift={KC_X, KC_U}, .rshift={KC_NO, 26}},
/*M(31): hi - bi     */ {.base={KC_H, KC_I}, .lshift={KC_MINUS}, .rshift={KC_B, KC_I}},
/*M(32): su ro zu    */ {.base={KC_S, KC_U}, .lshift={KC_R, KC_O}, .rshift={KC_Z, KC_U}},
/*M(33): fu ya bu    */ {.base={KC_F, KC_U}, .lshift={KC_Y, KC_A}, .rshift={KC_B, KC_U}},
/*M(34): he xi be    */ {.base={KC_H, KC_E}, .lshift={KC_X, KC_I}, .rshift={KC_B, KC_E}},
/*M(35): me pu nu    */ {.base={KC_M, KC_E}, .lshift={KC_P, KC_U}, .rshift={KC_N, KC_U}},
/*M(36): so zo yu    */ {.base={KC_S, KC_O}, .lshift={KC_Z, KC_O}, .rshift={KC_Y, KC_U}},
/*M(37): ne pe mu    */ {.base={KC_N, KC_E}, .lshift={KC_P, KC_E}, .rshift={KC_M, KC_U}},
/*M(38): ho bo wa    */ {.base={KC_H, KC_O}, .lshift={KC_B, KC_O}, .rshift={KC_W, KC_A}},
/*M(39): ? ? xo      */ {.base={KC_NO, 27}, .lshift={KC_NO, 28}, .rshift={KC_X, KC_O}},
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  if(id < 40){
    if (record->event.pressed) {
      const uint16_t* seq;
      if(isLeftShiftPressed){
        seq = macro_to_sequence[id].lshift;
      }else if(isRightShiftPressed){
        seq = macro_to_sequence[id].rshift;
      }else{
        seq = macro_to_sequence[id].base;
      }
      // special commands
      if(seq[0] == KC_NO && seq[1] > 0){
        switch(seq[1]){
        case 1: // "？?"
          register_code(KC_LSHIFT);
          register_code(KC_SLASH);
          unregister_code(KC_SLASH);
          unregister_code(KC_LSHIFT);
          break;
        case 21: // "・/"
          register_code(KC_SLASH);
          unregister_code(KC_SLASH);
          break;
        case 23: // "、,"
          register_code(KC_COMMA);
          unregister_code(KC_COMMA);
          break;
        case 27: // "。."
          register_code(KC_DOT);
          unregister_code(KC_DOT);
          break;
        case 7: // "「["
          register_code(KC_LBRACKET);
          unregister_code(KC_LBRACKET);
          register_code(KC_ENTER);
          unregister_code(KC_ENTER);
          break;
        case 8: // "『"
          register_code(KC_LBRACKET);
          unregister_code(KC_LBRACKET);
          register_code(KC_SPACE);
          unregister_code(KC_SPACE);
          register_code(KC_ENTER);
          unregister_code(KC_ENTER);
          break;
        case 9: // "」]"
          register_code(KC_RBRACKET);
          unregister_code(KC_RBRACKET);
          register_code(KC_ENTER);
          unregister_code(KC_ENTER);
          break;
        case 10: // "』"
          register_code(KC_RBRACKET);
          unregister_code(KC_RBRACKET);
          register_code(KC_SPACE);
          unregister_code(KC_SPACE);
          register_code(KC_ENTER);
          unregister_code(KC_ENTER);
          break;
        case 11: // "["
          register_code(KC_LBRACKET);
          unregister_code(KC_LBRACKET);
          register_code(KC_F10);
          unregister_code(KC_F10);
          break;
        case 12: // "("
          register_code(KC_LSHIFT);
          register_code(KC_9);
          unregister_code(KC_9);
          unregister_code(KC_LSHIFT);
          break;
        case 13: // "]"
          register_code(KC_RBRACKET);
          unregister_code(KC_RBRACKET);
          register_code(KC_F10);
          unregister_code(KC_F10);
          break;
        case 14: // ")"
          register_code(KC_LSHIFT);
          register_code(KC_0);
          unregister_code(KC_0);
          unregister_code(KC_LSHIFT);
          break;
        case 20: // F10
          register_code(KC_F10);
          unregister_code(KC_F10);
          break;
        case 25: // Undo: Ctrl-Z
          register_code(KC_LCTRL);
          register_code(KC_Z);
          unregister_code(KC_Z);
          unregister_code(KC_LCTRL);
          break;
        case 26: // Redo: Ctrl-Y
          register_code(KC_LCTRL);
          register_code(KC_Y);
          unregister_code(KC_Y);
          unregister_code(KC_LCTRL);
          break;
        }
        return MACRO_NONE;
      }
      // finish special commands

      // send normal sequence
      for (int i = 0; i < 3; i++) {
        if (seq[i] == KC_NO) {
          break;
        }
        register_code(seq[i]);
        unregister_code(seq[i]);
      }
    }
    return MACRO_NONE;
  }

  // update thumb shift status
  switch(id) {
  case 100:
    if(record->event.pressed){
      isLeftShiftPressed = true;
    }else{
      isLeftShiftPressed = false;
    }
    break;
  case 101:
    if(record->event.pressed){
      isRightShiftPressed = true;
    }else{
      isRightShiftPressed = false;
    }
    break;
  }

  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // not used now
  // it may be useful when you use thumb shifts as modifiers for ordinal keys
  // such as modifing LeftArrow to Home etc.
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    if(isLeftShiftPressed){
      ergodox_right_led_1_on();
    }
    if(isRightShiftPressed){
      ergodox_right_led_2_on();
    }
    if(layer == 0){ // Thumb shift mode
      ergodox_right_led_3_on();
    }
};
