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
        CAPS, A,   S,   D,   F,   G,
        LSFT,Z,   X,   C,   V,   B,   FN1,
        RGUI,GRV, BSLS,RGUI,LALT,
                                      LCTL,LALT,
                                           HOME,
                                 BSPC,DEL, END,
        // right hand
             FN3, 6,   7,   8,   9,   0,   MINS,
             RBRC, Y,   U,   I,   O,   P,   LBRC,
                  H,   J,   K,   L,   SCLN,QUOT,
              FN9, N,   M,   COMM,DOT, SLSH,RSFT,
                       FN5,DOWN,UP,  RGHT,LGUI,
        RALT,RCTL,
        PGUP,
        PGDN,ENT, SPC
    ),

    KEYMAP(  // layer 1 : function and symbol keys
        // left hand
        TRNS,F1,  F2,  F3,  F4,  F5,  F11,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN4,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             F12, F6,  F7,  F8,  F9,  F10, TRNS,
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
        FN0, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
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
        TRNS,FN10,FN11,FN12,FN13,FN14,TRNS,
        TRNS,TRNS,F15,F16,TRNS,TRNS,TRNS,
        TRNS,HOME,F14,END,TRNS,TRNS,
        FN22,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,FN26,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS, FN15, FN16, FN17,FN18,FN19,FN30,
             TRNS,TRNS, TRNS, TRNS, TRNS, BSPC, TRNS,
             LEFT, DOWN, UP, RGHT, F13, ENT,
             TRNS, TRNS, FN20, FN21, TRNS, TRNS, TRNS,
                       FN31, TRNS, TRNS, TRNS, TRNS,
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

    KEYMAP(  // layer6: helpful layer for the home-row navigation
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
             TRNS, FN24, FN23, TRNS, TRNS, TRNS,
             TRNS, TRNS,  TRNS, TRNS, TRNS, TRNS, TRNS,
                          FN25, TRNS, TRNS, TRNS, TRNS,
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
             TRNS,TRNS, TRNS, TRNS, TRNS, FN29, TRNS, // FN29 to not break alt+backspace
             TRNS, FN27, FN28, TRNS, TRNS, TRNS,
             TRNS, FN20, FN21, TRNS, TRNS, TRNS, TRNS,
                          FN31, TRNS, TRNS, TRNS, TRNS,
        TRNS,7,
        TRNS,
        TRNS,TRNS,TRNS
    ),
};

/* id for user defined functions */
enum function_id {
    TEENSY_KEY,
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

    // actions for i3
    ACTION_MODS_KEY(MOD_RGUI, KC_1),                // FN10
    ACTION_MODS_KEY(MOD_RGUI, KC_2),                // FN11
    ACTION_MODS_KEY(MOD_RGUI, KC_3),                // FN12
    ACTION_MODS_KEY(MOD_RGUI, KC_4),                // FN13
    ACTION_MODS_KEY(MOD_RGUI, KC_5),                // FN14
    ACTION_MODS_KEY(MOD_RGUI, KC_6),                // FN15
    ACTION_MODS_KEY(MOD_RGUI, KC_7),                // FN16
    ACTION_MODS_KEY(MOD_RGUI, KC_8),                // FN17
    ACTION_MODS_KEY(MOD_RGUI, KC_9),                // FN18
    ACTION_MODS_KEY(MOD_RGUI, KC_0),                // FN19

    // navigation actions
    ACTION_MODS_KEY(MOD_LALT, KC_N),                // FN20, WORD BACKWARD
    ACTION_MODS_KEY(MOD_LALT, KC_Y),                // FN21, WORD FORWARD
    // ACTION_LAYER_MOMENTARY(6),                   // FN22
    ACTION_LAYER_SET_CLEAR(6),                      // FN22
    ACTION_MODS_KEY(MOD_RSFT, KC_PGUP),             // FN23
    ACTION_MODS_KEY(MOD_RSFT, KC_PGDN),             // FN24
    ACTION_LAYER_SET(4, ON_BOTH),                   // FN25, deactivate layer #6
    // ACTION_LAYER_TAP_KEY(7, KC_LALT),
    // ACTION_LAYER_MOMENTARY(7),                   // FN26
    ACTION_LAYER_SET_CLEAR(7),                      // FN26
    ACTION_MODS_KEY(MOD_RGUI, KC_DOWN),             // FN27
    ACTION_MODS_KEY(MOD_RGUI, KC_UP),               // FN28
    ACTION_MODS_KEY(MOD_LALT, KC_BSPC),             // FN29
    ACTION_MODS_KEY(MOD_RSFT, KC_INS),              // FN30
    ACTION_LAYER_ON_OFF(4),                      // FN31
    // ACTION_LAYER_OFF(4, on),                        // FN31
};

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(250);
        bootloader_jump(); // should not return
        print("not supported.\n");
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
