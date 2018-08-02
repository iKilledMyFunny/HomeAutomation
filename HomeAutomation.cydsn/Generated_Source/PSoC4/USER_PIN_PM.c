/*******************************************************************************
* File Name: USER_PIN.c  
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
#include "USER_PIN.h"

static USER_PIN_BACKUP_STRUCT  USER_PIN_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: USER_PIN_Sleep
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
*  \snippet USER_PIN_SUT.c usage_USER_PIN_Sleep_Wakeup
*******************************************************************************/
void USER_PIN_Sleep(void)
{
    #if defined(USER_PIN__PC)
        USER_PIN_backup.pcState = USER_PIN_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            USER_PIN_backup.usbState = USER_PIN_CR1_REG;
            USER_PIN_USB_POWER_REG |= USER_PIN_USBIO_ENTER_SLEEP;
            USER_PIN_CR1_REG &= USER_PIN_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(USER_PIN__SIO)
        USER_PIN_backup.sioState = USER_PIN_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        USER_PIN_SIO_REG &= (uint32)(~USER_PIN_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: USER_PIN_Wakeup
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
*  Refer to USER_PIN_Sleep() for an example usage.
*******************************************************************************/
void USER_PIN_Wakeup(void)
{
    #if defined(USER_PIN__PC)
        USER_PIN_PC = USER_PIN_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            USER_PIN_USB_POWER_REG &= USER_PIN_USBIO_EXIT_SLEEP_PH1;
            USER_PIN_CR1_REG = USER_PIN_backup.usbState;
            USER_PIN_USB_POWER_REG &= USER_PIN_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(USER_PIN__SIO)
        USER_PIN_SIO_REG = USER_PIN_backup.sioState;
    #endif
}


/* [] END OF FILE */
