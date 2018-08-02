/*******************************************************************************
* File Name: ledDimmer_PM.c
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

#include "ledDimmer.h"

static ledDimmer_backupStruct ledDimmer_backup;


/*******************************************************************************
* Function Name: ledDimmer_SaveConfig
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
*  ledDimmer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void ledDimmer_SaveConfig(void) 
{

    #if(!ledDimmer_UsingFixedFunction)
        #if(!ledDimmer_PWMModeIsCenterAligned)
            ledDimmer_backup.PWMPeriod = ledDimmer_ReadPeriod();
        #endif /* (!ledDimmer_PWMModeIsCenterAligned) */
        ledDimmer_backup.PWMUdb = ledDimmer_ReadCounter();
        #if (ledDimmer_UseStatus)
            ledDimmer_backup.InterruptMaskValue = ledDimmer_STATUS_MASK;
        #endif /* (ledDimmer_UseStatus) */

        #if(ledDimmer_DeadBandMode == ledDimmer__B_PWM__DBM_256_CLOCKS || \
            ledDimmer_DeadBandMode == ledDimmer__B_PWM__DBM_2_4_CLOCKS)
            ledDimmer_backup.PWMdeadBandValue = ledDimmer_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(ledDimmer_KillModeMinTime)
             ledDimmer_backup.PWMKillCounterPeriod = ledDimmer_ReadKillTime();
        #endif /* (ledDimmer_KillModeMinTime) */

        #if(ledDimmer_UseControl)
            ledDimmer_backup.PWMControlRegister = ledDimmer_ReadControlRegister();
        #endif /* (ledDimmer_UseControl) */
    #endif  /* (!ledDimmer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ledDimmer_RestoreConfig
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
*  ledDimmer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ledDimmer_RestoreConfig(void) 
{
        #if(!ledDimmer_UsingFixedFunction)
            #if(!ledDimmer_PWMModeIsCenterAligned)
                ledDimmer_WritePeriod(ledDimmer_backup.PWMPeriod);
            #endif /* (!ledDimmer_PWMModeIsCenterAligned) */

            ledDimmer_WriteCounter(ledDimmer_backup.PWMUdb);

            #if (ledDimmer_UseStatus)
                ledDimmer_STATUS_MASK = ledDimmer_backup.InterruptMaskValue;
            #endif /* (ledDimmer_UseStatus) */

            #if(ledDimmer_DeadBandMode == ledDimmer__B_PWM__DBM_256_CLOCKS || \
                ledDimmer_DeadBandMode == ledDimmer__B_PWM__DBM_2_4_CLOCKS)
                ledDimmer_WriteDeadTime(ledDimmer_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(ledDimmer_KillModeMinTime)
                ledDimmer_WriteKillTime(ledDimmer_backup.PWMKillCounterPeriod);
            #endif /* (ledDimmer_KillModeMinTime) */

            #if(ledDimmer_UseControl)
                ledDimmer_WriteControlRegister(ledDimmer_backup.PWMControlRegister);
            #endif /* (ledDimmer_UseControl) */
        #endif  /* (!ledDimmer_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: ledDimmer_Sleep
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
*  ledDimmer_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ledDimmer_Sleep(void) 
{
    #if(ledDimmer_UseControl)
        if(ledDimmer_CTRL_ENABLE == (ledDimmer_CONTROL & ledDimmer_CTRL_ENABLE))
        {
            /*Component is enabled */
            ledDimmer_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            ledDimmer_backup.PWMEnableState = 0u;
        }
    #endif /* (ledDimmer_UseControl) */

    /* Stop component */
    ledDimmer_Stop();

    /* Save registers configuration */
    ledDimmer_SaveConfig();
}


/*******************************************************************************
* Function Name: ledDimmer_Wakeup
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
*  ledDimmer_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ledDimmer_Wakeup(void) 
{
     /* Restore registers values */
    ledDimmer_RestoreConfig();

    if(ledDimmer_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        ledDimmer_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
