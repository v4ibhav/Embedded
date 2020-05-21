#include <Reg52.h>
sbit Switch_pin = P1^0;
// Display switch status on this port
#define Output_port P3
// Return values from Switch_Get_Input()
#define SWITCH_NOT_PRESSED (bit) 0
#define SWITCH_PRESSED (bit) 1
// Function prototypes
void SWITCH_Init(void);
bit SWITCH_Get_Input(const unsigned char DEBOUNCE_PERIOD);
void DISPLAY_SWITCH_STATUS_Init(void);
void DISPLAY_SWITCH_STATUS_Update(const bit);
void DELAY_LOOP_Wait(const unsigned int DELAY_MS);
/* --------------------------------------------------------- */
void main(void)
{
bit Sw_state;
// Init functions
SWITCH_Init();
DISPLAY_SWITCH_STATUS_Init();
while(1)
{
Sw_state = SWITCH_Get_Input(30);
DISPLAY_SWITCH_STATUS_Update(Sw_state);
}
}
/*------------------------------------------------------------*-
SWITCH_Init()
Initialisation function for the switch library.
-*------------------------------------------------------------*/
void SWITCH_Init(void)
{
Switch_pin = 1; // Use this pin for input
}
/*------------------------------------------------------------*-
SWITCH_Get_Input()
Reads and debounces a mechanical switch as follows:
. If switch is not pressed, return SWITCH_NOT_PRESSED.
2. If switch is pressed, wait for DEBOUNCE_PERIOD (in ms),
then:
a. If switch is still pressed, return SWITCH_PRESSED.
b. If switch is not pressed, return SWITCH_NOT_PRESSED
See Switch_Wait.H for details of return values.
-*------------------------------------------------------------*/
bit SWITCH_Get_Input(const unsigned char DEBOUNCE_PERIOD)
{
bit Return_value = SWITCH_NOT_PRESSED;
if (Switch_pin == 0)
{
// Switch is pressed
// Debounce – just wait...
DELAY_LOOP_Wait(DEBOUNCE_PERIOD);
// Check switch again
if (Switch_pin == 0)
{
Return_value = SWITCH_PRESSED;
}
}
// Now return switch value
return Return_value;
}
/*------------------------------------------------------------*-
DISPLAY_SWITCH_STATUS_Init()
Initialization function for the DISPLAY_SWITCH_STATUS library.
-*------------------------------------------------------------*/
void DISPLAY_SWITCH_STATUS_Init(void)
{
Output_port = 0xF0;
}
/*------------------------------------------------------------*-
DISPLAY_SWITCH_STATUS_Update()
Simple function to display data (SWITCH_STATUS)
on LEDs connected to port (Output_Port)
-*------------------------------------------------------------*/
void DISPLAY_SWITCH_STATUS_Update(const bit SWITCH_STATUS)
{
if (SWITCH_STATUS == SWITCH_PRESSED)
{
Output_port = 0x0F;
}
else
{
Output_port = 0xF0;
}
}
/*------------------------------------------------------------*-
DELAY_LOOP_Wait()
Delay duration varies with parameter.
Parameter is, *ROUGHLY*, the delay, in milliseconds,
on 12MHz 8051 (12 osc cycles).
You need to adjust the timing for your application!
-*------------------------------------------------------------*/
void DELAY_LOOP_Wait(const unsigned int DELAY_MS)
{
unsigned int x, y;
for (x = 0; x <= DELAY_MS; x++)
{
for (y = 0; y <= 120; y++);
}
}
/*------------------------------------------------------------*-
---- END OF FILE --------------------------------------------
-*------------------------------------------------------------*/