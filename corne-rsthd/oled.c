#pragma once

#include "progmem.h"

extern uint8_t is_master;

static const char PROGMEM base_layer[] = {
  0x62, 0x63, 0x64, 0x65, 0x66,
  0x82, 0x83, 0x84, 0x85, 0x86, 0
};

static const char PROGMEM num_layer[] = {
  0x67, 0x68, 0x69, 0x6A, 0x6B,
  0x87, 0x88, 0x89, 0x8A, 0x8B, 0
};

static const char PROGMEM media_layer[] = {
  0x6C, 0x6D, 0x6E, 0x6F, 0x70,
  0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0
};

static const char PROGMEM numpad_layer[] = {
  0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
  0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0
};

static const char PROGMEM settings_layer[] = {
  0x71, 0x72, 0x73, 0x74, 0x75,
  0x91, 0x92, 0x93, 0x94, 0x95, 0
};

static const char PROGMEM qwerty_layer[] = {
  0x76, 0x77, 0x78, 0x79, 0x7A,
  0x96, 0x97, 0x98, 0x99, 0x9A, 0
};

static const char PROGMEM blank_line[] = {
  0x61, 0x61, 0x61, 0x61, 0x61, 0
};

static const char PROGMEM space_char[] = {
  0x61, 0
};

static const char PROGMEM os_mod1[] = {
  0xAC, 0xAD, 0
};

static const char PROGMEM os_mod2[] = {
  0xCC, 0xCD, 0
};

static const char PROGMEM alt_mod1[] = {
  0xAE, 0xAF, 0xB0, 0
};

static const char PROGMEM alt_mod2[] = {
  0xCE, 0xCF, 0xD0, 0
};

static const char PROGMEM ctrl_mod1[] = {
  0xA7, 0xA8, 0xA9, 0
};

static const char PROGMEM ctrl_mod2[] = {
  0xC7, 0xC8, 0xC9, 0
};

static const char PROGMEM shift_mod1[] = {
  0xAA, 0xAB, 0
};

static const char PROGMEM shift_mod2[] = {
  0xCA, 0xCB, 0
};

static const char PROGMEM star0[] = {
  0x1F, 0
};

static const char PROGMEM star1[] = {
  0x3F, 0
};

static const char PROGMEM star2[] = {
  0x1D, 0
};

static const char PROGMEM moon0[] = {
  0x1E, 0
};

static const char PROGMEM moon1[] = {
  0x3E, 0
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_270;
    }
}
