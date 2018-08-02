/***************************************************************************//**
* \file to_comp_PM.c
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

#include "to_comp.h"
#include "to_comp_PVT.h"

#if(to_comp_SCB_MODE_I2C_INC)
    #include "to_comp_I2C_PVT.h"
#endif /* (to_comp_SCB_MODE_I2C_INC) */

#if(to_comp_SCB_MODE_EZI2C_INC)
    #include "to_comp_EZI2C_PVT.h"
#endif /* (to_comp_SCB_MODE_EZI2C_INC) */

#if(to_comp_SCB_MODE_SPI_INC || to_comp_SCB_MODE_UART_INC)
    #include "to_comp_SPI_UART_PVT.h"
#endif /* (to_comp_SCB_MODE_SPI_INC || to_comp_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(to_comp_SCB_MODE_UNCONFIG_CONST_CFG || \
   (to_comp_SCB_MODE_I2C_CONST_CFG   && (!to_comp_I2C_WAKE_ENABLE_CONST))   || \
   (to_comp_SCB_MODE_EZI2C_CONST_CFG && (!to_comp_EZI2C_WAKE_ENABLE_CONST)) || \
   (to_comp_SCB_MODE_SPI_CONST_CFG   && (!to_comp_SPI_WAKE_ENABLE_CONST))   || \
   (to_comp_SCB_MODE_UART_CONST_CFG  && (!to_comp_UART_WAKE_ENABLE_CONST)))

    to_comp_BACKUP_STRUCT to_comp_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: to_comp_Sleep
****************************************************************************//**
*
*  Prepares the to_comp component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the to_comp_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void to_comp_Sleep(void)
{
#if(to_comp_SCB_MODE_UNCONFIG_CONST_CFG)

    if(to_comp_SCB_WAKE_ENABLE_CHECK)
    {
        if(to_comp_SCB_MODE_I2C_RUNTM_CFG)
        {
            to_comp_I2CSaveConfig();
        }
        else if(to_comp_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            to_comp_EzI2CSaveConfig();
        }
    #if(!to_comp_CY_SCBIP_V1)
        else if(to_comp_SCB_MODE_SPI_RUNTM_CFG)
        {
            to_comp_SpiSaveConfig();
        }
        else if(to_comp_SCB_MODE_UART_RUNTM_CFG)
        {
            to_comp_UartSaveConfig();
        }
    #endif /* (!to_comp_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        to_comp_backup.enableState = (uint8) to_comp_GET_CTRL_ENABLED;

        if(0u != to_comp_backup.enableState)
        {
            to_comp_Stop();
        }
    }

#else

    #if (to_comp_SCB_MODE_I2C_CONST_CFG && to_comp_I2C_WAKE_ENABLE_CONST)
        to_comp_I2CSaveConfig();

    #elif (to_comp_SCB_MODE_EZI2C_CONST_CFG && to_comp_EZI2C_WAKE_ENABLE_CONST)
        to_comp_EzI2CSaveConfig();

    #elif (to_comp_SCB_MODE_SPI_CONST_CFG && to_comp_SPI_WAKE_ENABLE_CONST)
        to_comp_SpiSaveConfig();

    #elif (to_comp_SCB_MODE_UART_CONST_CFG && to_comp_UART_WAKE_ENABLE_CONST)
        to_comp_UartSaveConfig();

    #else

        to_comp_backup.enableState = (uint8) to_comp_GET_CTRL_ENABLED;

        if(0u != to_comp_backup.enableState)
        {
            to_comp_Stop();
        }

    #endif /* defined (to_comp_SCB_MODE_I2C_CONST_CFG) && (to_comp_I2C_WAKE_ENABLE_CONST) */

#endif /* (to_comp_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: to_comp_Wakeup
****************************************************************************//**
*
*  Prepares the to_comp component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the to_comp_Wakeup() function without first calling the 
*   to_comp_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void to_comp_Wakeup(void)
{
#if(to_comp_SCB_MODE_UNCONFIG_CONST_CFG)

    if(to_comp_SCB_WAKE_ENABLE_CHECK)
    {
        if(to_comp_SCB_MODE_I2C_RUNTM_CFG)
        {
            to_comp_I2CRestoreConfig();
        }
        else if(to_comp_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            to_comp_EzI2CRestoreConfig();
        }
    #if(!to_comp_CY_SCBIP_V1)
        else if(to_comp_SCB_MODE_SPI_RUNTM_CFG)
        {
            to_comp_SpiRestoreConfig();
        }
        else if(to_comp_SCB_MODE_UART_RUNTM_CFG)
        {
            to_comp_UartRestoreConfig();
        }
    #endif /* (!to_comp_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != to_comp_backup.enableState)
        {
            to_comp_Enable();
        }
    }

#else

    #if (to_comp_SCB_MODE_I2C_CONST_CFG  && to_comp_I2C_WAKE_ENABLE_CONST)
        to_comp_I2CRestoreConfig();

    #elif (to_comp_SCB_MODE_EZI2C_CONST_CFG && to_comp_EZI2C_WAKE_ENABLE_CONST)
        to_comp_EzI2CRestoreConfig();

    #elif (to_comp_SCB_MODE_SPI_CONST_CFG && to_comp_SPI_WAKE_ENABLE_CONST)
        to_comp_SpiRestoreConfig();

    #elif (to_comp_SCB_MODE_UART_CONST_CFG && to_comp_UART_WAKE_ENABLE_CONST)
        to_comp_UartRestoreConfig();

    #else

        if(0u != to_comp_backup.enableState)
        {
            to_comp_Enable();
        }

    #endif /* (to_comp_I2C_WAKE_ENABLE_CONST) */

#endif /* (to_comp_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
