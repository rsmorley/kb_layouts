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

#pragma once

#define OLED_TIMEOUT 50000
#define OLED_FADE_OUT
#define OLED_FADE_INTERVAL 15
#define OLED_DISPLAY_128X64

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
#endif

#define ENCODER_DIRECTION_FLIP
#define ENCODER_RESOLUTION 2
// If you are using an Elite C rev3 on the slave side, uncomment the lines below
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK

// requires caps word enabled in rules.mk
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_INVERT_ON_SHIFT

// does nothing if REPEAT_KEY_ENABLE is not == yes in rules.mk
// #define NO_ALT_REPEAT_KEY

// set default tapping term
//#define TAPPING_TERM 200

// set custom tap terms per key
#define TAPPING_TERM_PER_KEY

// save space
#define NO_MUSIC_MODE
#define LAYER_STATE_8BIT
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT
