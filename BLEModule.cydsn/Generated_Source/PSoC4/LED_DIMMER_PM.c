/*******************************************************************************
* File Name: LED_DIMMER_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LED_DIMMER.h"

static LED_DIMMER_backupStruct LED_DIMMER_backup;


/*******************************************************************************
* Function Name: LED_DIMMER_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LED_DIMMER_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void LED_DIMMER_SaveConfig(void) 
{

    #if(!LED_DIMMER_UsingFixedFunction)
        #if(!LED_DIMMER_PWMModeIsCenterAligned)
            LED_DIMMER_backup.PWMPeriod = LED_DIMMER_ReadPeriod();
        #endif /* (!LED_DIMMER_PWMModeIsCenterAligned) */
        LED_DIMMER_backup.PWMUdb = LED_DIMMER_ReadCounter();
        #if (LED_DIMMER_UseStatus)
            LED_DIMMER_backup.InterruptMaskValue = LED_DIMMER_STATUS_MASK;
        #endif /* (LED_DIMMER_UseStatus) */

        #if(LED_DIMMER_DeadBandMode == LED_DIMMER__B_PWM__DBM_256_CLOCKS || \
            LED_DIMMER_DeadBandMode == LED_DIMMER__B_PWM__DBM_2_4_CLOCKS)
            LED_DIMMER_backup.PWMdeadBandValue = LED_DIMMER_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(LED_DIMMER_KillModeMinTime)
             LED_DIMMER_backup.PWMKillCounterPeriod = LED_DIMMER_ReadKillTime();
        #endif /* (LED_DIMMER_KillModeMinTime) */

        #if(LED_DIMMER_UseControl)
            LED_DIMMER_backup.PWMControlRegister = LED_DIMMER_ReadControlRegister();
        #endif /* (LED_DIMMER_UseControl) */
    #endif  /* (!LED_DIMMER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LED_DIMMER_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LED_DIMMER_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void LED_DIMMER_RestoreConfig(void) 
{
        #if(!LED_DIMMER_UsingFixedFunction)
            #if(!LED_DIMMER_PWMModeIsCenterAligned)
                LED_DIMMER_WritePeriod(LED_DIMMER_backup.PWMPeriod);
            #endif /* (!LED_DIMMER_PWMModeIsCenterAligned) */

            LED_DIMMER_WriteCounter(LED_DIMMER_backup.PWMUdb);

            #if (LED_DIMMER_UseStatus)
                LED_DIMMER_STATUS_MASK = LED_DIMMER_backup.InterruptMaskValue;
            #endif /* (LED_DIMMER_UseStatus) */

            #if(LED_DIMMER_DeadBandMode == LED_DIMMER__B_PWM__DBM_256_CLOCKS || \
                LED_DIMMER_DeadBandMode == LED_DIMMER__B_PWM__DBM_2_4_CLOCKS)
                LED_DIMMER_WriteDeadTime(LED_DIMMER_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(LED_DIMMER_KillModeMinTime)
                LED_DIMMER_WriteKillTime(LED_DIMMER_backup.PWMKillCounterPeriod);
            #endif /* (LED_DIMMER_KillModeMinTime) */

            #if(LED_DIMMER_UseControl)
                LED_DIMMER_WriteControlRegister(LED_DIMMER_backup.PWMControlRegister);
            #endif /* (LED_DIMMER_UseControl) */
        #endif  /* (!LED_DIMMER_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: LED_DIMMER_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LED_DIMMER_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void LED_DIMMER_Sleep(void) 
{
    #if(LED_DIMMER_UseControl)
        if(LED_DIMMER_CTRL_ENABLE == (LED_DIMMER_CONTROL & LED_DIMMER_CTRL_ENABLE))
        {
            /*Component is enabled */
            LED_DIMMER_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            LED_DIMMER_backup.PWMEnableState = 0u;
        }
    #endif /* (LED_DIMMER_UseControl) */

    /* Stop component */
    LED_DIMMER_Stop();

    /* Save registers configuration */
    LED_DIMMER_SaveConfig();
}


/*******************************************************************************
* Function Name: LED_DIMMER_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LED_DIMMER_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void LED_DIMMER_Wakeup(void) 
{
     /* Restore registers values */
    LED_DIMMER_RestoreConfig();

    if(LED_DIMMER_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        LED_DIMMER_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
