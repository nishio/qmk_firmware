#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "process_unicode.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  TEST,
  TMUX_LAST,
  EMACS_DABBREV
};
#define DAB EMACS_DABBREV

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = KEYMAP(  // layer 0 : default
// left hand
KC_ESC,  KC_1,  KC_2,   KC_3,   KC_4,   KC_5,   KC_6,
KC_TAB,  KC_Q,  KC_W,   KC_E,   KC_R,   KC_T,   KC_NO,
KC_LCTL, KC_A,  KC_S,   KC_D,   KC_F,   KC_G,
KC_LSFT, KC_Z,  KC_X,   KC_C,   KC_V,   KC_B,   KC_NO,
TG(1),   TEST, KC_NO,  KC_NO,  KC_NO,

KC_NO,  KC_NO,
/* */   KC_LALT,
SFT_T(KC_SPC),KC_LCTL,KC_LGUI,

// right hand
KC_7,     KC_8,   KC_9,  KC_0,   KC_MINUS, KC_EQL,  KC_BSPACE,
DAB,      KC_Y,   KC_U,  KC_I,   KC_O,     KC_P,    KC_BSLS,
/* */     KC_H,   KC_J,  KC_K,   KC_L,     KC_QUOT, KC_ENTER,
KC_NO,    KC_N,   KC_M,  KC_COMM,KC_DOT,   KC_SCLN, KC_SLSH,
/*         */  KC_LBRC,  KC_RBRC,KC_GRAVE, KC_NO,   KC_NO,

KC_RALT, KC_RCTL,
KC_NO,
KC_NO,   MO(1),   SFT_T(KC_SPACE)
),

// SYMBOLS
[SYMB] = KEYMAP(
// left hand
RESET,  KC_F1,  KC_F2,  KC_F3,  KC_F4,    KC_F5,  KC_F6,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,TMUX_LAST,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,

KC_TRNS, KC_TRNS,
/* */    KC_TRNS,
KC_TRNS, KC_TRNS, KC_TRNS,

// right hand
KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_TRNS,
KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_TRNS, KC_TRNS,
/* */    KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_TRNS, KC_TRNS,
KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,  KC_UP,   KC_TRNS,
/*             */ KC_BTN1, KC_BTN2, KC_LEFT,  KC_DOWN, KC_RIGHT,

KC_TRNS, KC_TRNS,
KC_TRNS,
KC_TRNS, KC_TRNS,  KC_TRNS
),

// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;

    case TEST:
      if (record->event.pressed) {
        SEND_STRING ("UNICODE TEST");
        set_unicode_input_mode(UC_WINC);

        // my name: u'\u897f\u5c3e\u6cf0\u548c'
        unicode_input_start();
        register_hex(0x897f);
        unicode_input_finish();
        SEND_STRING (" ");

        unicode_input_start();
        register_hex(0x5c3e);
        unicode_input_finish();
        SEND_STRING (" ");

        unicode_input_start();
        register_hex(0x6cf0);
        unicode_input_finish();
        //SEND_STRING (" ");

        unicode_input_start();
        register_hex(0x548c);  // fails
        unicode_input_finish();
        SEND_STRING (" ");
      }
      return false;
      break;

    case TMUX_LAST:
      // C-b l
      if (record->event.pressed) {
        register_code(KC_LCTL);
        register_code(KC_B);
        unregister_code(KC_B);
        unregister_code(KC_LCTL);
        register_code(KC_L);
        unregister_code(KC_L);
      }

      return false;
      break;

    case EMACS_DABBREV:
      // Esc /
      if (record->event.pressed) {
        register_code(KC_ESC);
        unregister_code(KC_ESC);
        register_code(KC_SLSH);
        unregister_code(KC_SLSH);
      }

      return false;
      break;


  }
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
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
