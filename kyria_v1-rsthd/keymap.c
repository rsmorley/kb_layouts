/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// used by encoders
uint16_t encoder_timeout = 1000;
bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;

static bool     is_asleep = false;

// send string Declarations
enum {
    SS_EMAIL = 0,
    SS_SUDO
};


//Tap Dance Declarations
enum {
  // TD_GRAVE_ESCAPE = 0,
  TD_CP_PT = 0,
  TD_SNST
};

#define KC_COPY LCMD(KC_C)
#define KC_PASTE LCMD(KC_V)
tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Grave, twice for ESC
  // [TD_GRAVE_ESCAPE]  = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_ESC),
  //Tap once for Copy, twice for Paste
  [TD_CP_PT]  = ACTION_TAP_DANCE_DOUBLE(KC_COPY, KC_PASTE),
  //Tap once for screenshot w/ crosshairs, twice for screenshot menu
  [TD_SNST]  = ACTION_TAP_DANCE_DOUBLE(G(S(KC_4)), G(S(KC_5)))
};

enum layers {
    _BASE = 0,
    _NUM_NAV,
    _FUNC_MED,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: BASE - home row mods - GACS
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | Tab    |   J  |   C  |   Y  |   F  |   K  |                              |   Z  |   L  |   ,  |   U  |   Q  |    \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | Esc    |   R  |   S  |  T   |   H  |   D  |                              |   M  |   N  |   A  |   I  |   O  |    =   |
 * |        |  CMD |  ALT | CTL  |  SFT |      |                              |      |  SFT |  CTL |  ALT |  CMD |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | EMAIL  |   /  |   V  |   G  |   P  |   B  | SNST | Null |  | Null |CP/PT |   X  |   W  |   .  |   ;  |   -  |    ;   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Knob |   [  |   E  | Bksp |  `   |  | SUDO |
 *                        |      |      | LNS  | LNM  |      |  |      | LNM  | LNS  |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_BASE] = LAYOUT(
      KC_TAB,   KC_J,        KC_C,        KC_Y,        KC_F,        KC_K,                                             KC_Z,  KC_L,        KC_COMM,     KC_U,        KC_Q,        KC_BSLS,
      KC_ESC,      LGUI_T(KC_R),LALT_T(KC_S),LCTL_T(KC_T),LSFT_T(KC_H),KC_D,                                             KC_M,  RSFT_T(KC_N),RCTL_T(KC_A),RALT_T(KC_I),RGUI_T(KC_O),KC_EQL,
      SS_EMAIL, KC_SLSH,     KC_V,        KC_G,        KC_P,        KC_B, TD(TD_SNST),  KC_NO,   KC_NO, TD(TD_CP_PT), KC_X,  KC_W,        KC_DOT,      KC_SCLN,     KC_MINS,     KC_QUOT,
                KC_MUTE, LT(_FUNC_MED, KC_LBRC), LT(_NUM_NAV, KC_E), KC_BSPC, KC_GRV, SS_SUDO, LT(_FUNC_MED, KC_ENT), LT(_NUM_NAV, KC_SPC),  KC_RBRC, KC_MPLY
    ),
/*
 * Raise Layer: Number keys, special keys
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  7   |  8   |  9   |  0   |  5   |                              |   6  |  1   |  2   |  3   |  4   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    <-  | DOWN |  UP  |  ->  |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      | MPRV | MPLY | MNXT |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUM_NAV] = LAYOUT(
      _______, KC_7, 	  KC_8,    KC_9,  KC_0,     KC_5,                                       KC_6,    KC_1,    KC_2,    KC_3,    KC_4,    _______,
      _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______,                                    _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, QK_REP, _______,   _______, _______, _______
    ),
/*
 * Lower Layer: Navigation and Media Controls
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F1   |  F2  | F3   | F4   | F5   |                              | F6   | F7   |  F8  | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  <-  | DOWN |  UP  |  ->  |      |                              |      |      |      | F11  | F12  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      | MLeft| Mdown| MUp  |MRight|      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNC_MED] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, _______, _______, _______,  _______, _______,                                     _______, _______, _______, KC_F11,  KC_F12,  _______,
      _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, _______, _______,
                                 _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Adjust Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______,  _______, _______,                                    _______, _______, _______, _______, _______, _______,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

void keyboard_post_init_user(void) {
  //rainbow_swirl supports additional numbers 0-5
  rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 4);
}

void suspend_power_down_user(void) { is_asleep = true; }

void suspend_wakeup_init_user(void) { is_asleep = false; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SS_EMAIL:
      if (record->event.pressed) {
        SEND_STRING("morley.rs@gmail.com");
      }
      return false;
    case SS_SUDO:
      if (record->event.pressed) {
        SEND_STRING("sudo !!");
      }
      return false;
  }
  return true;
}

void matrix_scan_user(void) {
  // release CMD button after encoder_timeout ms
  // used by encoder app switcher
  if (is_cmd_tab_active) {
    if (timer_elapsed(cmd_tab_timer) > encoder_timeout) {
      unregister_code(KC_LGUI);
      is_cmd_tab_active = false;
    }
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _FUNC_MED, _NUM_NAV, _ADJUST);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_TAB):
            return 125;
        default:
            return TAPPING_TERM;
    }
}

#ifdef OLED_ENABLE

// Animation parameters
#define FRAME_DURATION 333 // How long each frame lasts in milliseconds

// Animation variables
uint32_t timer = 0;
uint8_t current_frame = 0;

// Render animation
static void render_animation(void) {
    // 'totoro-animated-frame-0', 128x64px
    static const char PROGMEM totoro_frame_0[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x07, 0xc3, 0xcf, 0x3f, 0x07, 0x43, 0x0f, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xf8, 0xe0, 0x03, 0x3f, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x01, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0x78, 0x30, 0x93, 0x87, 0x0f, 0x4f, 0x9f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0xef, 0xf3, 0xff, 0xfd, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
                                                  0xfe, 0xfe, 0xfe, 0xfc, 0xfc, 0xf8, 0xf8, 0xf0, 0xf3, 0xe3, 0xe7, 0xcf, 0x8f, 0x1f, 0x38, 0x73, 0xf7, 0xf5, 0xf1, 0x78, 0x3f, 0x1f, 0x9c, 0xc1, 0xc1, 0xcf, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x9f, 0x8f, 0xcf, 0xcf, 0xcf, 0xc7, 0xe7, 0xf7, 0xf6, 0x04, 0x01, 0xc1, 0xf0,
                                                  0xf4, 0xfe, 0xef, 0xd3, 0xb3, 0x73, 0xe7, 0xff, 0xe1, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0x8f, 0x0f, 0x0f, 0x0f, 0x6f, 0x64, 0x01, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x83, 0xe3, 0xf1, 0xf9, 0xf9, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0x8f, 0xcf, 0x03, 0xf0, 0xfc, 0xfb, 0xfb, 0xf7, 0xf7, 0xf3, 0xf3, 0xfd, 0xfe, 0xff, 0xff, 0x7f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xf8, 0xf0, 0xf0, 0xe0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x87, 0xc7, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xdf, 0xef, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x81, 0x81, 0x83, 0xc3, 0xe7, 0xe3, 0xe1, 0xe0, 0xe7, 0xe7, 0xc7, 0xcf, 0xc7, 0xc7, 0xc7, 0xc3, 0xc3, 0xc1, 0xc1, 0xc0, 0xc0, 0xc0, 0xc3, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    // 'totoro-animated-frame-1', 128x64px
    static const char PROGMEM totoro_frame_1[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x01, 0xc3, 0xc7, 0x07, 0x01, 0x73, 0x0f, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0xff, 0xff, 0xff, 0xf8, 0xe0, 0x00, 0x1e, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x9f, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x18, 0xd9, 0xd3, 0x87, 0x67, 0xcf, 0x1f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x0f, 0xc7, 0xf9, 0xfd, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xf9, 0xf9, 0xf3, 0xe7, 0xc7, 0x8f, 0x1c, 0x39, 0xf3, 0xf0, 0x70, 0x3c, 0x1f, 0x8f, 0xce, 0xe8, 0xe0, 0xe7, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x1f, 0x8f, 0xcf, 0xcf, 0xe7, 0xf7, 0xf7, 0xf3, 0xf3, 0xf3, 0xf3, 0x02, 0x00, 0xe0, 0xf8,
                                                  0xfa, 0xfb, 0xf3, 0xf1, 0xc9, 0x11, 0xf3, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x87, 0x07, 0x17, 0x17, 0x17, 0x13, 0x1a, 0x19, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x61, 0xf0, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xc7, 0xe7, 0x03, 0xf8, 0xfe, 0xfd, 0xf9, 0xf3, 0xf3, 0xfb, 0xf9, 0xfc, 0xff, 0xff, 0xff, 0x7f, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xf8, 0xf8, 0xf0, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x07, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xef, 0xe7, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xf8, 0xf0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc1, 0xc1, 0xc1, 0xc1, 0x81, 0x83, 0x83, 0x80, 0x84, 0xc7, 0xc3, 0xc3, 0xfb, 0xf9, 0xfd, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    // 'totoro-animated-frame-2', 128x64px
    static const char PROGMEM totoro_frame_2[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x03, 0xc7, 0x0f, 0x07, 0x03, 0xc7, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0xff, 0xff, 0xfe, 0xf8, 0xe0, 0x00, 0x38, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x9f, 0x01, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0x78, 0x30, 0x93, 0x87, 0x0f, 0x4f, 0x9f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x0f, 0xf7, 0xfd, 0xfd, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xf9, 0xf1, 0xf3, 0xe7, 0xcf, 0x18, 0x33, 0x77, 0xf5, 0xf1, 0x78, 0x3f, 0x1f, 0x9c, 0xc1, 0xc1, 0xcf, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x3f, 0x1f, 0x8f, 0xcf, 0xcf, 0xcf, 0xcf, 0xe7, 0xf7, 0xf7, 0x06, 0x00, 0xc1, 0xf0,
                                                  0xf4, 0xf7, 0xe7, 0xe3, 0x93, 0x33, 0xe7, 0xff, 0xe1, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0x0f, 0x0f, 0x0f, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x06, 0x05, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x83, 0xe3, 0xf3, 0xf9, 0xf8, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xcf, 0xc3, 0xe0, 0xe0, 0xe3, 0x07, 0x07, 0xf7, 0xf7, 0xf3, 0xf9, 0xfe, 0xff, 0xff, 0x7f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf8, 0xf8, 0xf0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf0, 0xe3, 0x0f, 0x7f, 0x7f, 0xff, 0xdf, 0xef, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe1, 0xe1, 0xe1, 0xc1, 0xc3, 0xc3, 0x83, 0x87, 0x87, 0x87, 0x87, 0x8f, 0x8f, 0x9f, 0xbf, 0xbf, 0xbf, 0xbf, 0x9f, 0xdc, 0xc3, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    // Animation frames array
    const char* bitmap_allArray [] = {
        totoro_frame_0,
        totoro_frame_1,
        totoro_frame_2
    };

    // Frame sizes array
    uint16_t frame_sizes[3] = {
        sizeof(totoro_frame_0),
        sizeof(totoro_frame_1),
        sizeof(totoro_frame_2)
    };

    // Run animation
    if (timer_elapsed(timer) > FRAME_DURATION) {
        // Set timer to updated time
        timer = timer_read();

        // Increment frame
        current_frame = (current_frame + 1) % (sizeof(bitmap_allArray) / sizeof(bitmap_allArray[0]));

        // Draw frame to OLED
        oled_write_raw_P(bitmap_allArray[current_frame], frame_sizes[current_frame]);
    }
}


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _FUNC_MED:
            oled_write_P(PSTR("Media & Fs\n"), false);
            break;
        case _NUM_NAV:
            oled_write_P(PSTR("Nav & Nums\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Modifier Statuses
    uint8_t modifiers = get_mods();
    oled_write_P(PSTR("Mods: "), false);
    oled_write_P(PSTR("SHT"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("CTL"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("CMD"), (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR("\n"), false);

    // Host Keyboard LED Status
    // uint8_t led_usb_state = host_keyboard_leds();
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
}

bool oled_task_user(void) {
    if (is_asleep) {
        oled_off();
        return false;
    }
    if (is_keyboard_master()) {
        render_status();
    }
    else {
        render_animation();
        //oled_scroll_left();
    }
    return false;

}

#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _FUNC_MED:
            if (index == 0) {
                // Undo/Redo
                if (clockwise) {
                    tap_code16(G(KC_Y));
                } else {
                    tap_code16(G(S(KC_Z)));
                }
            } else if (index == 1) {
                // Page up/Page down
                if (clockwise) {
                    tap_code(KC_PGUP);
                } else {
                    tap_code(KC_PGDN);
                }
            }
            break;
        case _NUM_NAV:
            if (index == 0) {
                // scroll by word
                if (clockwise) {
                    tap_code16(A(KC_RIGHT));
                } else {
                    tap_code16(A(KC_LEFT));
                }
            } else if (index == 1) {
                // Tabbing between apps
                if (clockwise) {
                    if (!is_cmd_tab_active) {
                        is_cmd_tab_active = true;
                        register_code(KC_LGUI);
                    }
                    cmd_tab_timer = timer_read();
                    tap_code16(KC_TAB);
                } else {
                    cmd_tab_timer = timer_read();
                    tap_code16(S(KC_TAB));
                }
            }
            break;
        default:
            if (index == 0) {
                // Volume control
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            }
            else if (index == 1) {
                // Page up/Page down
                if (clockwise) {
                    tap_code(KC_PGUP);
                } else {
                    tap_code(KC_PGDN);
                }
            }
    }
    return false;
}
#endif
