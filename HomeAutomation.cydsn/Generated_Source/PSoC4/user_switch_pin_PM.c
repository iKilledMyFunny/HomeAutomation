/*******************************************************************************
* File Name: user_switch_pin.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "user_switch_pin.h"

static user_switch_pin_BACKUP_STRUCT  user_switch_pin_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: user_switch_pin_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet user_switch_pin_SUT.c usage_user_switch_pin_Sleep_Wakeup
*******************************************************************************/
void user_switch_pin_Sleep(void)
{
    #if defined(user_switch_pin__PC)
        user_switch_pin_backup.pcState = user_switch_pin_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            user_switch_pin_backup.usbState = user_switch_pin_CR1_REG;
            user_switch_pin_USB_POWER_REG |= user_switch_pin_USBIO_ENTER_SLEEP;
            user_switch_pin_CR1_REG &= user_switch_pin_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(user_switch_pin__SIO)
        user_switch_pin_backup.sioState = user_switch_pin_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        user_switch_pin_SIO_REG &= (uint32)(~user_switch_pin_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: user_switch_pin_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to user_switch_pin_Sleep() for an example usage.
*******************************************************************************/
void user_switch_pin_Wakeup(void)
{
    #if defined(user_switch_pin__PC)
        user_switch_pin_PC = user_switch_pin_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            user_switch_pin_USB_POWER_REG &= user_switch_pin_USBIO_EXIT_SLEEP_PH1;
            user_switch_pin_CR1_REG = user_switch_pin_backup.usbState;
            user_switch_pin_USB_POWER_REG &= user_switch_pin_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(user_switch_pin__SIO)
        user_switch_pin_SIO_REG = user_switch_pin_backup.sioState;
    #endif
}


/* [] END OF FILE */
