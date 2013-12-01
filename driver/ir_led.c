#include "../config/board_config.h"

/**
 * Initialize timer 2 for 38 kHz interrupt-frequency
 */
void init_ir_led()
{
    // timer 2 init (76kHz)
    PR2 = 233;
    TMR2 = 0;
    // 0, 0101 (postscaler 6), 0 (enable), 01 (prescaler 4)
    T2CON = 0b00101001;
    TMR2IF = 0;
    TMR2IE = 1;
    TMR2ON = 1;
}