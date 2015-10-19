/*
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "keycode.h"
#include "action.h"
#include "action_util.h"
#include "action_code.h"
#include "action_macro.h"
#include "action_layer.h"
#include "bootloader.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"
#include "ergodox.h"


/* ErgoDox keymap definition macro */
#define KEYMAP(                                                 \
                                                                \
    /* left hand, spatial positions */                          \
    k00,k01,k02,k03,k04,k05,k06,                                \
    k10,k11,k12,k13,k14,k15,k16,                                \
    k20,k21,k22,k23,k24,k25,                                    \
    k30,k31,k32,k33,k34,k35,k36,                                \
    k40,k41,k42,k43,k44,                                        \
                            k55,k56,                            \
                                k54,                            \
                        k53,k52,k51,                            \
                                                                \
    /* right hand, spatial positions */                         \
        k07,k08,k09,k0A,k0B,k0C,k0D,                            \
        k17,k18,k19,k1A,k1B,k1C,k1D,                            \
            k28,k29,k2A,k2B,k2C,k2D,                            \
        k37,k38,k39,k3A,k3B,k3C,k3D,                            \
                k49,k4A,k4B,k4C,k4D,                            \
    k57,k58,                                                    \
    k59,                                                        \
    k5C,k5B,k5A )                                               \
                                                                \
   /* matrix positions */                                       \
   {                                                            \
    { KC_##k00,KC_##k10,KC_##k20,KC_##k30,KC_##k40,KC_NO   },   \
    { KC_##k01,KC_##k11,KC_##k21,KC_##k31,KC_##k41,KC_##k51},   \
    { KC_##k02,KC_##k12,KC_##k22,KC_##k32,KC_##k42,KC_##k52},   \
    { KC_##k03,KC_##k13,KC_##k23,KC_##k33,KC_##k43,KC_##k53},   \
    { KC_##k04,KC_##k14,KC_##k24,KC_##k34,KC_##k44,KC_##k54},   \
    { KC_##k05,KC_##k15,KC_##k25,KC_##k35,KC_NO,   KC_##k55},   \
    { KC_##k06,KC_##k16,KC_NO,   KC_##k36,KC_NO,   KC_##k56},   \
                                                                \
    { KC_##k07,KC_##k17,KC_NO,   KC_##k37,KC_NO,   KC_##k57},   \
    { KC_##k08,KC_##k18,KC_##k28,KC_##k38,KC_NO,   KC_##k58},   \
    { KC_##k09,KC_##k19,KC_##k29,KC_##k39,KC_##k49,KC_##k59},   \
    { KC_##k0A,KC_##k1A,KC_##k2A,KC_##k3A,KC_##k4A,KC_##k5A},   \
    { KC_##k0B,KC_##k1B,KC_##k2B,KC_##k3B,KC_##k4B,KC_##k5B},   \
    { KC_##k0C,KC_##k1C,KC_##k2C,KC_##k3C,KC_##k4C,KC_##k5C},   \
    { KC_##k0D,KC_##k1D,KC_##k2D,KC_##k3D,KC_##k4D,KC_NO   }    \
   }

#if defined(KEYMAP_DVORAK)
#include "keymap_dvorak.h"
#elif defined(KEYMAP_COLEMAK)
#include "keymap_colemak.h"
#elif defined(KEYMAP_WORKMAN)
#include "keymap_workman.h"
#elif defined(KEYMAP_MICRO)
#include "keymap_micro.h"
#elif defined(KEYMAP_CUB)
#include "keymap_cub.h"
#else

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KEYMAP(  // layer 0 : default
        // left hand
        EQL, 1,   2,   3,   4,   5,   ESC,
        TAB,Q,   W,   E,   R,   T,   FN2,
        FN16, A,   S,   D,   F,   G,
        LSFT,Z,   X,   C,   V,   B,   FN1,
        RGUI,GRV, BSLS,FN18,FN14,
        LCTL,LALT,
        HOME,
        BSPC,DEL, END,
        // right hand
        FN9, 6,   7,   8,   9,   0,   MINS,
        RBRC, Y,   U,   I,   O,   FN15,   LBRC,
        H,   J,   K,   L,   SCLN,QUOT,
        FN9, N,   M,   COMM,DOT, SLSH,RSFT,
        FN5,DOWN,UP,RCTL,LGUI,
        RALT,RCTL,
        PGUP,
        PGDN,ENT, RGUI
        ),

    KEYMAP(  // layer 1 : function and symbol keys
        // left hand
        TRNS,F1,  F2,  F3,  F4,  F5,  F6,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN4,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS,
        // right hand
        F6,  F7,  F8,  F9,  F10, F11, F12,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
        ),

    KEYMAP(  // layer 2 : keyboard functions
        // left hand
        TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS,
        // right hand
        FN4, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
        ),

    KEYMAP(  // layer 3: numpad
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS,
        // right hand
        SLCK,NLCK,PSLS,PAST,PAST,PMNS,BSPC,
        TRNS,NO,  P7,  P8,  P9,  PMNS,BSPC,
        NO,  P4,  P5,  P6,  PPLS,PENT,
        TRNS,NO,  P1,  P2,  P3,  PPLS,PENT,
        P0,  PDOT,SLSH,PENT,PENT,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
        ),

    KEYMAP(  // layer 4: navigation layer
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,F15,F16,TRNS,TRNS,TRNS,
        TRNS,HOME,F14,END,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS,
        // right hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN17,
        TRNS,TRNS, TRNS, TRNS, F17, TRNS, TRNS,
        LEFT, DOWN, UP, RGHT, F13, ENT,
        TRNS, TRNS, FN10, FN11, TRNS, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS,4,
        TRNS,
        TRNS,TRNS,TRNS
        ),

    KEYMAP(  // Layer5: mouse and navigation, leftled:mid/blue+bot/green
        // left hand
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  ACL0,NO,  TRNS,
        TRNS,NO,  NO,  TRNS,ACL1,NO,
        TRNS,NO,  NO,  TRNS,ACL2,NO,  TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS,

        // right hand
        F16, MPLY,MPRV,MNXT,VOLD,VOLU,MUTE,
        F14, BTN2,WH_L,WH_U,WH_D,WH_R,PGUP,
        BTN1,MS_L,MS_U,MS_D,MS_R,PGDN,
        F15, BTN3,HOME,END, DEL, INS, NO,
        TRNS,TRNS,TRNS,TRNS,FN4,
        TRNS,5,
        TRNS,
        TRNS,TRNS,TRNS
        ),

    KEYMAP(  // Layer6: layer with PGUP and PGDOWN on home row
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS,
        // right hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, PGDN, PGUP, TRNS, TRNS, TRNS,
        TRNS, TRNS,  TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS,6,
        TRNS,
        TRNS,TRNS,TRNS
        ),

    KEYMAP(  // layer7: layer navigation for i3
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,FN8,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS,
        // right hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, // FN29 to not break alt+backspace
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, FN10, FN11, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS,7,
        TRNS,
        TRNS,TRNS,TRNS
        ),

    KEYMAP(  // Layer8: transparent for correct layers deactivation
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,RGUI,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS,
        // right hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        FN5,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
        ),

    KEYMAP(  // Layer9: transparent for correct layer deactivation
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,FN12,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS,
        // right hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
        ),

    KEYMAP(  // Layer10: transparent
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS,
        // right hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
        ),
/*
// templates to copy from
KEYMAP(  // LayerN: fully transparent
// left hand
TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
TRNS,TRNS,TRNS,TRNS,RGUI,
TRNS,TRNS,
TRNS,
TRNS,TRNS,TRNS,
// right hand
TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
TRNS,TRNS,TRNS,TRNS,TRNS,
TRNS,TRNS,
TRNS,
TRNS,TRNS,TRNS
),
*/
};

/* id for user defined functions */
enum function_id {
    TEENSY_KEY,
    META,
    ALT_OR_GUI,
    ALT_BACKSPACE,
    CTL_OR_SET_MARK,
};

enum macro_id {
    SAVE,
    HELLO,
    VOLUP,
    ALT_TAB,

};
/*
 * Fn action definition

 */
static const uint16_t PROGMEM fn_actions[] = {
    ACTION_FUNCTION(TEENSY_KEY),                    // FN0 - Teensy key
    ACTION_LAYER_MOMENTARY(1),                      // FN1 - switch to Layer1
    ACTION_LAYER_SET(2, ON_PRESS),                  // FN2 - push Layer2
    ACTION_LAYER_SET(3, ON_PRESS),                  // FN3 - push Layer3
    ACTION_LAYER_SET(0, ON_PRESS),                  // FN4 - push Layer0
    ACTION_LAYER_TAP_KEY(4, KC_SPC),                // FN5 - puhs Layer5, Navigation Layer
    ACTION_MODS_KEY(MOD_RCTL, KC_LBRC),             // FN6 - undo
    // ACTION_MACRO(SAVE),
    ACTION_MODS_KEY(MOD_RGUI, KC_F10),
    // ACTION_MACRO(HELLO),
    ACTION_LAYER_ON_OFF(7),                         // FN8
    ACTION_LAYER_SET(5, ON_PRESS),                  // FN9

    // navigation actions
    ACTION_MODS_KEY(MOD_LALT, KC_N),                // FN10, WORD BACKWARD
    ACTION_MODS_KEY(MOD_LALT, KC_Y),                // FN11, WORD FORWARD

    ACTION_LAYER_MOMENTARY(8),                      // FN12 - pushs Layer8, is used for correct LGUI releasing
    ACTION_LAYER_TAP_KEY(10, KC_RGUI),              // FN13 - pushs Layer8, is used for correct LALT releasing
    ACTION_FUNCTION(ALT_OR_GUI),                    // FN14 - action for the function
    ACTION_FUNCTION(ALT_BACKSPACE),                 // FN15 - Alt + Backspace
    ACTION_FUNCTION_TAP(CTL_OR_SET_MARK),           // FN16 - control or set mark on tap
    ACTION_MODS_KEY(MOD_RSFT, KC_INS),              // FN17 - Shift insert
    ACTION_LAYER_MOMENTARY(6),                      // FN18 - Activate Layer6
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    print("action_function called\n");
    print("id  = "); phex(id); print("\n");
    print("opt = "); phex(opt); print("\n");
  
    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(250);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }

    uint8_t layer = biton32(layer_state);

    uint8_t alt_weak_mods, gui_weak_mods;
    alt_weak_mods = MOD_BIT(KC_LALT);
    gui_weak_mods = MOD_BIT(KC_RGUI);

# define MODS_ALT_MASK (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
    static uint8_t alt_mod;
# define MODS_GUI_MASK (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))
    static uint8_t gui_mod;

    if (id == CTL_OR_SET_MARK) {

        if (record->event.pressed) {
            if (record->tap.count > 0 && !record->tap.interrupted) {
                if (record->tap.interrupted) {
                    dprint("tap interrupted\n");
                    register_mods(MOD_BIT(KC_RCTL));
                }
            } else {
                register_mods(MOD_BIT(KC_RCTL));
            }
        } else {
            if (record->tap.count > 0 && !(record->tap.interrupted)) {
                add_weak_mods(MOD_BIT(KC_RCTL));
                send_keyboard_report();
                register_code(KC_SPC);
                unregister_code(KC_SPC);
                del_weak_mods(MOD_BIT(KC_RCTL));
                send_keyboard_report();
                record->tap.count = 0;  // ad hoc: cancel tap
            } else {
                unregister_mods(MOD_BIT(KC_RCTL));
            }
        }

        /* if (record->tap.count == 0 || record->tap.interrupted) { */
        /*     add_mods(MOD_BIT(KC_RCTL)); */
        /*     add_key(KC_SPC); */
        /*     send_keyboard_report(); */
        /* } else { */
        /*     del_mods(MOD_BIT(KC_RCTL)); */
        /*     del_key(KC_SPC); */
        /*     send_keyboard_report(); */
        /* } */
    }

    if (id == ALT_BACKSPACE) {
        if (record->tap.count == 0 || record->tap.interrupted) {
            if (layer == 4) {
                gui_mod = get_mods() & MODS_GUI_MASK;
                alt_mod = get_mods() & MODS_ALT_MASK;
                if (record->event.pressed) {
                    if (gui_mod || alt_mod) {
                        del_mods(MOD_BIT(KC_RGUI));
                        add_mods(MOD_BIT(KC_LALT));
                        add_key(KC_BSPC);
                        send_keyboard_report();
                        del_mods(MOD_BIT(KC_LALT));
                        add_mods(MOD_BIT(KC_RGUI));
                    } else {
                        add_key(KC_BSPC);
                        send_keyboard_report();
                    }
                } else {
                    /* if (gui_mod && alt_mod) { */
                    /*     del_weak_mods(alt_weak_mods); */
                    /* } */
                    // del_mods(MOD_BIT(KC_LALT));
                    // del_mods(MOD_BIT(KC_RGUI));
                    del_key(KC_BSPC);
                    send_keyboard_report();
                }
            } else {
                del_mods(MOD_BIT(KC_LALT));
                send_keyboard_report();
                if (record->event.pressed) {
                    add_key(KC_P);
                    send_keyboard_report();
                } else {
                    del_key(KC_P);
                    send_keyboard_report();
                }
            }
        }
    }

    if (id == ALT_OR_GUI) {
        if (record->tap.count == 0 || record->tap.interrupted) {
            if (layer == 0) {
                if (record->event.pressed) {
                    add_mods(MOD_BIT(KC_LALT));
                    send_keyboard_report();
                } else {
                    del_mods(MOD_BIT(KC_LALT));
                    del_mods(MOD_BIT(KC_RGUI));
                    send_keyboard_report();
                }
            } else if (layer == 4) {
                uint8_t gui_weak_mods;
                gui_weak_mods = MOD_BIT(KC_RGUI);
                if (record->event.pressed) {
                    add_mods(MOD_BIT(KC_RGUI));
                    send_keyboard_report();
                } else {
                    del_mods(MOD_BIT(KC_LALT));
                    del_mods(MOD_BIT(KC_RGUI));
                    send_keyboard_report();
                }
            }
            /*
            uint8_t weak_mods;
            uint8_t layer;

            if (id == ALT_OR_GUI) {
                weak_mods = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT);
                layer     = 5;
            } else {
                weak_mods = MOD_BIT(KC_RCTL) | MOD_BIT(KC_RALT);
                layer     = 6;
            }

            if (record->event.pressed) {
                layer_on(layer);
                add_weak_mods(weak_mods);
            } else {
                del_weak_mods(weak_mods);
                layer_off(layer);
            }
        } else {
            if (record->event.pressed) {
                add_key(KC_ENT);
                send_keyboard_report();
            } else {
                del_key(KC_ENT);
                send_keyboard_report();
            }
        }
            */
        }
    }
}

#endif


#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
#define FN_ACTIONS_SIZE (sizeof(fn_actions) / sizeof(fn_actions[0]))

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, key_t key)
{
    if (layer < KEYMAPS_SIZE) {
        return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
    } else {
        // fall back to layer 0
        return pgm_read_byte(&keymaps[0][(key.row)][(key.col)]);
    }
}

#if defined(KEYMAP_CUB)

// function keymap_fn_to_action will be defined in keymap_cub.h

#else
/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    if (FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    } else {
        action.code = ACTION_NO;
    }
    return action;
}
#endif

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case HELLO:
            return (record->event.pressed ?
                    MACRO( I(0), T(H), T(E), T(L), T(L), W(255), T(O), END ) :
                    MACRO_NONE );
        case SAVE:
            return (record->event.pressed ?
                    MACRO( I(0), D(LCTL), D(B), U(B), U(LCTL), D(RCTL), D(SCLN), U(SCLN), U(RCTL), END ) :
                    // MACRO( I(0), T(H), T(E), T(L), T(L), W(255), T(O), END ) :
                    MACRO_NONE );
        case VOLUP:
            return (record->event.pressed ?
                    MACRO( D(VOLU), U(VOLU), END ) :
                    MACRO_NONE );
        case ALT_TAB:
            return (record->event.pressed ?
                    MACRO( D(LALT), D(TAB), END ) :
                    MACRO( U(TAB), END ));
    }
    return MACRO_NONE;
}
