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

#ifdef OLED_DRIVER_ENABLE
#include "oled.c"
#endif

// send string Declarations
enum {
    SS_SUDO = 0
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
    _ADJUST,
    _QWERTY
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: BASE - home row mods - GACS
 *
 * ,-------------------------------------------.    ,-------------------------------------------.
 * | Tab    |   J  |   C  |   Y  |   F  |   K  |    |   Z  |   L  |   ,  |   U  |   Q  |    \   |
 * |--------+------+------+------+------+------|    |------+------+------+------+------+--------|
 * | Esc    |   R  |   S  |  T   |   H  |   D  |    |   M  |   N  |   A  |   I  |   O  |    =   |
 * |        |  CMD |  ALT | CTL  |  SFT |      |    |      |  SFT |  CTL |  ALT |  CMD |        |
 * |--------+------+------+------+------+------|    |------+------+------+------+------+--------|
 * |   `    |   /  |   V  |   G  |   P  |   B  |    |   X  |   W  |   .  |   ;  |   -  |    ;   |
 * `----------------------+------+------+------|    |------+------+------+----------------------'
 *                        |  [   |   E  | BKSPC|    | Enter| SPC  |   ]  |
 *                        | LFM  | LNN  | LNN  |    | LFM  | LNN  |      |
 *                        `---------------------    ---------------------'
 */
    [_BASE] = LAYOUT(
      KC_TAB,   KC_J,        KC_C,        KC_Y,        KC_F,        KC_K,               KC_Z,  KC_L,        KC_COMM,     KC_U,        KC_Q,        KC_BSLS,
      KC_ESC,      LGUI_T(KC_R),LALT_T(KC_S),LCTL_T(KC_T),LSFT_T(KC_H),KC_D,            KC_M,  RSFT_T(KC_N),RCTL_T(KC_A),RALT_T(KC_I),RGUI_T(KC_O),KC_EQL,
      KC_GRV, KC_SLSH,     KC_V,        KC_G,        KC_P,        KC_B, 		KC_X,  KC_W,        KC_DOT,      KC_SCLN,     KC_MINS,     KC_QUOT,
                           LT(_FUNC_MED, KC_LBRC), LT(_NUM_NAV, KC_E), KC_BSPC, 	LT(_FUNC_MED, KC_ENT), LT(_NUM_NAV, KC_SPC),  KC_RBRC
    ),
/*
 * Raise Layer: Number keys, special keys
 * ,-------------------------------------------.    ,-------------------------------------------.
 * |        |  7   |  8   |  9   |  0   |  5   |    |   6  |  1   |  2   |  3   |  4   |        |
 * |--------+------+------+------+------+------|    |------+------+------+------+------+--------|
 * |    <-  | DOWN |  UP  |  ->  |      |      |    |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+    +------+------+------+------+------+--------|
 * |        |      |      |      |      |      |    |      |      |      |      |      |        |
 * `----------------------+------+------+------+    +------+------+------+----------------------'
 *                        |      |      |      |    |      |      |      |
 *                        |      |      |      |    |      |      |      |
 *                        `---------------------    ---------------------'
 */
    [_NUM_NAV] = LAYOUT(
      _______, KC_7, 	  KC_8,    KC_9,  KC_0,     KC_5,		KC_6,    KC_1,    KC_2,    KC_3,    KC_4,    _______,
      _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______,		_______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,		_______, _______, _______, _______, _______, _______,
                                 _______, _______, _______,		_______, _______, _______
    ),
/*
 * Lower Layer: Navigation and Media Controls
 *
 * ,-------------------------------------------.    ,-------------------------------------------.
 * |        | F1   |  F2  | F3   | F4   | F5   |    | F6   | F7   |  F8  | F9   | F10  |        |
 * |--------+------+------+------+------+------|    |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |    |      | SUDO | CP/PT| F11  | F12  |        |
 * |--------+------+------+------+------+------+    +------+------+------+------+------+--------|
 * |        |      |      |      |      |      |    |      | MPRV | MPLY | MNXT |      |        |
 * `----------------------+------+------+------+    +------+------+------+----------------------'
 *                        |      |      |      |    |      |      |      |
 *                        |      |      |      |    |      |      |      |
 *                        `---------------------    ---------------------'
 */
    [_FUNC_MED] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,		KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, _______, _______, _______,  _______, _______,		TG(_QWERTY), SS_SUDO, TD_CP_PT, KC_F11,  KC_F12,  _______,
      _______, _______, _______, _______,  _______, _______,		_______, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, _______, _______,
                                 _______,  _______, _______,		_______, _______, _______
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
      _______, _______, _______, _______,  _______, _______,    _______, _______, _______, _______, _______, _______,
      RGB_TOG, RGB_SPI, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,     _______, _______, _______, _______, _______, _______,
      _______, RGB_SPD, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,    _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______,     _______, _______, _______
    ),
/*
 * Base Layer: qwerty
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |RAIS/ESC|   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/BS |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |LShift|LShift|  |LShift|LShift|   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | GUI  | Del  | Enter| Space| Esc  |  | Enter| Space| Tab  | Bksp | AltGr|
 *                        |      |      | Alt  | Lower| Raise|  | Lower| Raise|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
      QK_GESC,        KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      LSFT_T(KC_TAB), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, SC_RSPC,
      SC_LCPO,        KC_Z,     KC_X,   KC_C,   KC_V,   KC_B,       KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_RCTL, KC_RCTL,
              KC_LCMD , LT(_NUM_NAV, KC_E), LT(_FUNC_MED, KC_BSPC), LT(_FUNC_MED, KC_ENT), LT(_NUM_NAV, KC_SPC),  KC_RALT
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
  //rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 4);
}

void suspend_power_down_user(void) { is_asleep = true; }

void suspend_wakeup_init_user(void) { is_asleep = false; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    oled_timer = timer_read();
  }
  switch (keycode) {
    case SS_SUDO:
      if (record->event.pressed) {
        SEND_STRING("sudo !!");
      }
      return false;
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _FUNC_MED, _NUM_NAV, _ADJUST);
}

/*
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_TAB):
            return 125;
        default:
            return TAPPING_TERM;
    }
}
*/

#ifdef OLED_ENABLE

static void render_status(void) {
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
        case _QWERTY:
            oled_write_P(PSTR("Qwerty\n"), false);
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
/*
    uint8_t mode = rgb_matrix_get_mode();
    oled_write_P(PSTR("RGB: "), false);
    oled_write_char('0' + mode, false);
    oled_write_P(PSTR(" "), false);
    oled_write_char(mode, false);
    oled_write_P(PSTR("\n"), false);
  */
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
    }
    else {
        render_animation((timer_read() / 60) % 8);
    }
    return false;
}

#endif
