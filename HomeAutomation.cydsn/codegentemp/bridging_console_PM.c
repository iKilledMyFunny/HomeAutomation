/***************************************************************************//**
* \file bridging_console_PM.c
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

#include "bridging_console.h"
#include "bridging_console_PVT.h"

#if(bridging_console_SCB_MODE_I2C_INC)
    #include "bridging_console_I2C_PVT.h"
#endif /* (bridging_console_SCB_MODE_I2C_INC) */

#if(bridging_console_SCB_MODE_EZI2C_INC)
    #include "bridging_console_EZI2C_PVT.h"
#endif /* (bridging_console_SCB_MODE_EZI2C_INC) */

#if(bridging_console_SCB_MODE_SPI_INC || bridging_console_SCB_MODE_UART_INC)
    #include "bridging_console_SPI_UART_PVT.h"
#endif /* (bridging_console_SCB_MODE_SPI_INC || bridging_console_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(bridging_console_SCB_MODE_UNCONFIG_CONST_CFG || \
   (bridging_console_SCB_MODE_I2C_CONST_CFG   && (!bridging_console_I2C_WAKE_ENABLE_CONST))   || \
   (bridging_console_SCB_MODE_EZI2C_CONST_CFG && (!bridging_console_EZI2C_WAKE_ENABLE_CONST)) || \
   (bridging_console_SCB_MODE_SPI_CONST_CFG   && (!bridging_console_SPI_WAKE_ENABLE_CONST))   || \
   (bridging_console_SCB_MODE_UART_CONST_CFG  && (!bridging_console_UART_WAKE_ENABLE_CONST)))

    bridging_console_BACKUP_STRUCT bridging_console_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: bridging_console_Sleep
****************************************************************************//**
*
*  Prepares the bridging_console component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the bridging_console_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void bridging_console_Sleep(void)
{
#if(bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)

    if(bridging_console_SCB_WAKE_ENABLE_CHECK)
    {
        if(bridging_console_SCB_MODE_I2C_RUNTM_CFG)
        {
            bridging_console_I2CSaveConfig();
        }
        else if(bridging_console_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            bridging_console_EzI2CSaveConfig();
        }
    #if(!bridging_console_CY_SCBIP_V1)
        else if(bridging_console_SCB_MODE_SPI_RUNTM_CFG)
        {
            bridging_console_SpiSaveConfig();
        }
        else if(bridging_console_SCB_MODE_UART_RUNTM_CFG)
        {
            bridging_console_UartSaveConfig();
        }
    #endif /* (!bridging_console_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        bridging_console_backup.enableState = (uint8) bridging_console_GET_CTRL_ENABLED;

        if(0u != bridging_console_backup.enableState)
        {
            bridging_console_Stop();
        }
    }

#else

    #if (bridging_console_SCB_MODE_I2C_CONST_CFG && bridging_console_I2C_WAKE_ENABLE_CONST)
        bridging_console_I2CSaveConfig();

    #elif (bridging_console_SCB_MODE_EZI2C_CONST_CFG && bridging_console_EZI2C_WAKE_ENABLE_CONST)
        bridging_console_EzI2CSaveConfig();

    #elif (bridging_console_SCB_MODE_SPI_CONST_CFG && bridging_console_SPI_WAKE_ENABLE_CONST)
        bridging_console_SpiSaveConfig();

    #elif (bridging_console_SCB_MODE_UART_CONST_CFG && bridging_console_UART_WAKE_ENABLE_CONST)
        bridging_console_UartSaveConfig();

    #else

        bridging_console_backup.enableState = (uint8) bridging_console_GET_CTRL_ENABLED;

        if(0u != bridging_console_backup.enableState)
        {
            bridging_console_Stop();
        }

    #endif /* defined (bridging_console_SCB_MODE_I2C_CONST_CFG) && (bridging_console_I2C_WAKE_ENABLE_CONST) */

#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: bridging_console_Wakeup
****************************************************************************//**
*
*  Prepares the bridging_console component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the bridging_console_Wakeup() function without first calling the 
*   bridging_console_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void bridging_console_Wakeup(void)
{
#if(bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)

    if(bridging_console_SCB_WAKE_ENABLE_CHECK)
    {
        if(bridging_console_SCB_MODE_I2C_RUNTM_CFG)
        {
            bridging_console_I2CRestoreConfig();
        }
        else if(bridging_console_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            bridging_console_EzI2CRestoreConfig();
        }
    #if(!bridging_console_CY_SCBIP_V1)
        else if(bridging_console_SCB_MODE_SPI_RUNTM_CFG)
        {
            bridging_console_SpiRestoreConfig();
        }
        else if(bridging_console_SCB_MODE_UART_RUNTM_CFG)
        {
            bridging_console_UartRestoreConfig();
        }
    #endif /* (!bridging_console_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != bridging_console_backup.enableState)
        {
            bridging_console_Enable();
        }
    }

#else

    #if (bridging_console_SCB_MODE_I2C_CONST_CFG  && bridging_console_I2C_WAKE_ENABLE_CONST)
        bridging_console_I2CRestoreConfig();

    #elif (bridging_console_SCB_MODE_EZI2C_CONST_CFG && bridging_console_EZI2C_WAKE_ENABLE_CONST)
        bridging_console_EzI2CRestoreConfig();

    #elif (bridging_console_SCB_MODE_SPI_CONST_CFG && bridging_console_SPI_WAKE_ENABLE_CONST)
        bridging_console_SpiRestoreConfig();

    #elif (bridging_console_SCB_MODE_UART_CONST_CFG && bridging_console_UART_WAKE_ENABLE_CONST)
        bridging_console_UartRestoreConfig();

    #else

        if(0u != bridging_console_backup.enableState)
        {
            bridging_console_Enable();
        }

    #endif /* (bridging_console_I2C_WAKE_ENABLE_CONST) */

#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
