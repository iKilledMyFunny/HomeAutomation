/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "tiny_printf.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    console_Start();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        uint8_t switchState = ~user_sw1_Read();
        if (switchState == 0xFF)
        {
            tiny_printf("Just testing\n");
        }
        
        user_pin_blue_Write(switchState);
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
