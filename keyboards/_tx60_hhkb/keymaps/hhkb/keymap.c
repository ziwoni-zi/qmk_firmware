 #include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _FNC,
    _NUM,
    _EXTRA,
    _RE_SET,
    _RE_SETF
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    FLIP,
    SCRS, SCRS_PT, SCRS_SLT,
    COPY, PASTE, CUT, SLCT_A
};

#define QWERTY DF(_QWERTY)
#define FNC MO(_FNC)
#define RE_SET MO(_RE_SET)
#define RE_SETF MO(_RE_SETF)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = {
    {
    FLIP
    }
},
    
[1] = {
    {
    SCRS, SCRS_PT, SCRS_SLT
    }
},
    
[2] = {
    {
    COPY, PASTE, CUT, SLCT_A
    }
},

[_QWERTY] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
    KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
    KC_LCMD,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, FNC,
    _______, KC_LCTL, KC_LOPT,                   KC_SPC,  KC_SPC,  KC_SPC,                    _______, KC_RCMD, _______, KC_ROPT, _______
),

// KC_RCMD, KC_ROPT, _______, KC_RCTL,

[_FNC] = LAYOUT(
    _______, KC_F5,   KC_F12,  RGB_TOG, _______, _______, _______, _______, _______, KC_MRWD, KC_MFFD, KC_VOLD, KC_VOLU,  KC_MPLY, KC_MUTE,
    _______,          RGB_VAI, RGB_HUI, RGB_SAI, RE_SET,  _______, _______, _______, _______, CUT,     COPY,    KC_UP,    PASTE,   _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_LEFT, KC_RIGHT, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_DOWN,           KC_HOME, _______,
    _______, _______, _______,                   _______, _______, _______,                   _______, KC_END,  _______,  KC_CAPS, _______
),

[_RE_SET] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,          _______, RE_SETF, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______,                   _______, _______, _______,                   _______, _______, _______, _______, _______
),
    
[_RE_SETF] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,          _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______,                   _______, _______, _______,                   _______, _______, _______, _______, _______
)
    
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FLIP:
            if (record->event.pressed) {
                //send_unicode_string("(ノಠ痊ಠ)ノ彡┻━┻");
            }
            
            break;
        case COPY:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCMD));
                SEND_STRING(SS_DOWN(X_C));
            } else {
                SEND_STRING(SS_UP(X_C));
                SEND_STRING(SS_UP(X_LCMD));
            }
            
            break;
        case PASTE:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCMD));
                SEND_STRING(SS_DOWN(X_V));
            } else {
                SEND_STRING(SS_UP(X_V));
                SEND_STRING(SS_UP(X_LCMD));
            }
            
            break;
        case CUT:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCMD));
                SEND_STRING(SS_DOWN(X_X));
            } else {
                SEND_STRING(SS_UP(X_X));
                SEND_STRING(SS_UP(X_LCMD));
            }
            
            break;
        case SLCT_A:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCMD));
                SEND_STRING(SS_DOWN(X_A));
            } else {
                SEND_STRING(SS_UP(X_A));
                SEND_STRING(SS_UP(X_LCMD));
            }
            
            break;
        case SCRS:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LSFT));
                SEND_STRING(SS_DOWN(X_LCMD));
                SEND_STRING(SS_DOWN(X_3));
            } else {
                SEND_STRING(SS_UP(X_3));
                SEND_STRING(SS_UP(X_LCMD));
                SEND_STRING(SS_UP(X_LSFT));
            }
            
            break;
        case SCRS_PT:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LSFT));
                SEND_STRING(SS_DOWN(X_LCMD));
                SEND_STRING(SS_DOWN(X_5));
            } else {
                SEND_STRING(SS_UP(X_5));
                SEND_STRING(SS_UP(X_LCMD));
                SEND_STRING(SS_UP(X_LSFT));
            }
            
            break;
        case SCRS_SLT:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LSFT));
                SEND_STRING(SS_DOWN(X_LCMD));
                SEND_STRING(SS_DOWN(X_4));
            } else {
                SEND_STRING(SS_UP(X_4));
                SEND_STRING(SS_UP(X_LCMD));
                SEND_STRING(SS_UP(X_LSFT));
            }
            
            break;
        default:
            break;
    }
    
    return true;
}
