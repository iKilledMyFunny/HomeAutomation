/***************************************************************************//**
* \file console_PM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "console.h"
#include "console_PVT.h"

#if(console_SCB_MODE_I2C_INC)
    #include "console_I2C_PVT.h"
#endif /* (console_SCB_MODE_I2C_INC) */

#if(console_SCB_MODE_EZI2C_INC)
    #include "console_EZI2C_PVT.h"
#endif /* (console_SCB_MODE_EZI2C_INC) */

#if(console_SCB_MODE_SPI_INC || console_SCB_MODE_UART_INC)
    #include "console_SPI_UART_PVT.h"
#endif /* (console_SCB_MODE_SPI_INC || console_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(console_SCB_MODE_UNCONFIG_CONST_CFG || \
   (console_SCB_MODE_I2C_CONST_CFG   && (!console_I2C_WAKE_ENABLE_CONST))   || \
   (console_SCB_MODE_EZI2C_CONST_CFG && (!console_EZI2C_WAKE_ENABLE_CONST)) || \
   (console_SCB_MODE_SPI_CONST_CFG   && (!console_SPI_WAKE_ENABLE_CONST))   || \
   (console_SCB_MODE_UART_CONST_CFG  && (!console_UART_WAKE_ENABLE_CONST)))

    console_BACKUP_STRUCT console_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: console_Sleep
****************************************************************************//**
*
*  Prepares the console component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the console_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void console_Sleep(void)
{
#if(console_SCB_MODE_UNCONFIG_CONST_CFG)

    if(console_SCB_WAKE_ENABLE_CHECK)
    {
        if(console_SCB_MODE_I2C_RUNTM_CFG)
        {
            console_I2CSaveConfig();
        }
        else if(console_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            console_EzI2CSaveConfig();
        }
    #if(!console_CY_SCBIP_V1)
        else if(console_SCB_MODE_SPI_RUNTM_CFG)
        {
            console_SpiSaveConfig();
        }
        else if(console_SCB_MODE_UART_RUNTM_CFG)
        {
            console_UartSaveConfig();
        }
    #endif /* (!console_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        console_backup.enableState = (uint8) console_GET_CTRL_ENABLED;

        if(0u != console_backup.enableState)
        {
            console_Stop();
        }
    }

#else

    #if (console_SCB_MODE_I2C_CONST_CFG && console_I2C_WAKE_ENABLE_CONST)
        console_I2CSaveConfig();

    #elif (console_SCB_MODE_EZI2C_CONST_CFG && console_EZI2C_WAKE_ENABLE_CONST)
        console_EzI2CSaveConfig();

    #elif (console_SCB_MODE_SPI_CONST_CFG && console_SPI_WAKE_ENABLE_CONST)
        console_SpiSaveConfig();

    #elif (console_SCB_MODE_UART_CONST_CFG && console_UART_WAKE_ENABLE_CONST)
        console_UartSaveConfig();

    #else

        console_backup.enableState = (uint8) console_GET_CTRL_ENABLED;

        if(0u != console_backup.enableState)
        {
            console_Stop();
        }

    #endif /* defined (console_SCB_MODE_I2C_CONST_CFG) && (console_I2C_WAKE_ENABLE_CONST) */

#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: console_Wakeup
****************************************************************************//**
*
*  Prepares the console component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the console_Wakeup() function without first calling the 
*   console_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void console_Wakeup(void)
{
#if(console_SCB_MODE_UNCONFIG_CONST_CFG)

    if(console_SCB_WAKE_ENABLE_CHECK)
    {
        if(console_SCB_MODE_I2C_RUNTM_CFG)
        {
            console_I2CRestoreConfig();
        }
        else if(console_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            console_EzI2CRestoreConfig();
        }
    #if(!console_CY_SCBIP_V1)
        else if(console_SCB_MODE_SPI_RUNTM_CFG)
        {
            console_SpiRestoreConfig();
        }
        else if(console_SCB_MODE_UART_RUNTM_CFG)
        {
            console_UartRestoreConfig();
        }
    #endif /* (!console_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != console_backup.enableState)
        {
            console_Enable();
        }
    }

#else

    #if (console_SCB_MODE_I2C_CONST_CFG  && console_I2C_WAKE_ENABLE_CONST)
        console_I2CRestoreConfig();

    #elif (console_SCB_MODE_EZI2C_CONST_CFG && console_EZI2C_WAKE_ENABLE_CONST)
        console_EzI2CRestoreConfig();

    #elif (console_SCB_MODE_SPI_CONST_CFG && console_SPI_WAKE_ENABLE_CONST)
        console_SpiRestoreConfig();

    #elif (console_SCB_MODE_UART_CONST_CFG && console_UART_WAKE_ENABLE_CONST)
        console_UartRestoreConfig();

    #else

        if(0u != console_backup.enableState)
        {
            console_Enable();
        }

    #endif /* (console_I2C_WAKE_ENABLE_CONST) */

#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
