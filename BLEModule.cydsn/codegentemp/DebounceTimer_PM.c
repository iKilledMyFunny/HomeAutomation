/*******************************************************************************
* File Name: DebounceTimer_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DebounceTimer.h"

static DebounceTimer_BACKUP_STRUCT DebounceTimer_backup;


/*******************************************************************************
* Function Name: DebounceTimer_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: DebounceTimer_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_Sleep(void)
{
    if(0u != (DebounceTimer_BLOCK_CONTROL_REG & DebounceTimer_MASK))
    {
        DebounceTimer_backup.enableState = 1u;
    }
    else
    {
        DebounceTimer_backup.enableState = 0u;
    }

    DebounceTimer_Stop();
    DebounceTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: DebounceTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: DebounceTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_Wakeup(void)
{
    DebounceTimer_RestoreConfig();

    if(0u != DebounceTimer_backup.enableState)
    {
        DebounceTimer_Enable();
    }
}


/* [] END OF FILE */
