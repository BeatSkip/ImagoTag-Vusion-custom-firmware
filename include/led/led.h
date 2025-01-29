#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <ax8051f143.h>
#include "board.h"

// RGB Color definitions
typedef enum {
    LED_OFF = 0,
    LED_RED,
    LED_GREEN,
    LED_BLUE,
    LED_YELLOW,
    LED_CYAN,
    LED_MAGENTA,
    LED_WHITE
} rgb_color_t;

// LED states
typedef enum {
    SOLID = 0,
    BLINK_SLOW,    // 1Hz
    BLINK_MEDIUM,  // 2Hz
    BLINK_FAST     // 4Hz
} led_state_t;

// Function prototypes
void led_init(void);
void rgb_led_set_color(rgb_color_t color);
void white_led_set_state(uint8_t state);
void led_set_blink(uint8_t led_select, led_state_t blink_state);
void led_update(void); // Call this in main loop or timer ISR

// LED selection for blink control
#define LED_RGB  0x01
#define LED_WHITE 0x02
#define LED_ALL  (LED_RGB | LED_WHITE)

#endif // LED_CONTROL_H