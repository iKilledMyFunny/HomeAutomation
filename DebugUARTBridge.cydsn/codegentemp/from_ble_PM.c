/***************************************************************************//**
* \file from_ble_PM.c
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

#include "from_ble.h"
#include "from_ble_PVT.h"

#if(from_ble_SCB_MODE_I2C_INC)
    #include "from_ble_I2C_PVT.h"
#endif /* (from_ble_SCB_MODE_I2C_INC) */

#if(from_ble_SCB_MODE_EZI2C_INC)
    #include "from_ble_EZI2C_PVT.h"
#endif /* (from_ble_SCB_MODE_EZI2C_INC) */

#if(from_ble_SCB_MODE_SPI_INC || from_ble_SCB_MODE_UART_INC)
    #include "from_ble_SPI_UART_PVT.h"
#endif /* (from_ble_SCB_MODE_SPI_INC || from_ble_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(from_ble_SCB_MODE_UNCONFIG_CONST_CFG || \
   (from_ble_SCB_MODE_I2C_CONST_CFG   && (!from_ble_I2C_WAKE_ENABLE_CONST))   || \
   (from_ble_SCB_MODE_EZI2C_CONST_CFG && (!from_ble_EZI2C_WAKE_ENABLE_CONST)) || \
   (from_ble_SCB_MODE_SPI_CONST_CFG   && (!from_ble_SPI_WAKE_ENABLE_CONST))   || \
   (from_ble_SCB_MODE_UART_CONST_CFG  && (!from_ble_UART_WAKE_ENABLE_CONST)))

    from_ble_BACKUP_STRUCT from_ble_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: from_ble_Sleep
****************************************************************************//**
*
*  Prepares the from_ble component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the from_ble_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void from_ble_Sleep(void)
{
#if(from_ble_SCB_MODE_UNCONFIG_CONST_CFG)

    if(from_ble_SCB_WAKE_ENABLE_CHECK)
    {
        if(from_ble_SCB_MODE_I2C_RUNTM_CFG)
        {
            from_ble_I2CSaveConfig();
        }
        else if(from_ble_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            from_ble_EzI2CSaveConfig();
        }
    #if(!from_ble_CY_SCBIP_V1)
        else if(from_ble_SCB_MODE_SPI_RUNTM_CFG)
        {
            from_ble_SpiSaveConfig();
        }
        else if(from_ble_SCB_MODE_UART_RUNTM_CFG)
        {
            from_ble_UartSaveConfig();
        }
    #endif /* (!from_ble_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        from_ble_backup.enableState = (uint8) from_ble_GET_CTRL_ENABLED;

        if(0u != from_ble_backup.enableState)
        {
            from_ble_Stop();
        }
    }

#else

    #if (from_ble_SCB_MODE_I2C_CONST_CFG && from_ble_I2C_WAKE_ENABLE_CONST)
        from_ble_I2CSaveConfig();

    #elif (from_ble_SCB_MODE_EZI2C_CONST_CFG && from_ble_EZI2C_WAKE_ENABLE_CONST)
        from_ble_EzI2CSaveConfig();

    #elif (from_ble_SCB_MODE_SPI_CONST_CFG && from_ble_SPI_WAKE_ENABLE_CONST)
        from_ble_SpiSaveConfig();

    #elif (from_ble_SCB_MODE_UART_CONST_CFG && from_ble_UART_WAKE_ENABLE_CONST)
        from_ble_UartSaveConfig();

    #else

        from_ble_backup.enableState = (uint8) from_ble_GET_CTRL_ENABLED;

        if(0u != from_ble_backup.enableState)
        {
            from_ble_Stop();
        }

    #endif /* defined (from_ble_SCB_MODE_I2C_CONST_CFG) && (from_ble_I2C_WAKE_ENABLE_CONST) */

#endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: from_ble_Wakeup
****************************************************************************//**
*
*  Prepares the from_ble component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the from_ble_Wakeup() function without first calling the 
*   from_ble_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void from_ble_Wakeup(void)
{
#if(from_ble_SCB_MODE_UNCONFIG_CONST_CFG)

    if(from_ble_SCB_WAKE_ENABLE_CHECK)
    {
        if(from_ble_SCB_MODE_I2C_RUNTM_CFG)
        {
            from_ble_I2CRestoreConfig();
        }
        else if(from_ble_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            from_ble_EzI2CRestoreConfig();
        }
    #if(!from_ble_CY_SCBIP_V1)
        else if(from_ble_SCB_MODE_SPI_RUNTM_CFG)
        {
            from_ble_SpiRestoreConfig();
        }
        else if(from_ble_SCB_MODE_UART_RUNTM_CFG)
        {
            from_ble_UartRestoreConfig();
        }
    #endif /* (!from_ble_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != from_ble_backup.enableState)
        {
            from_ble_Enable();
        }
    }

#else

    #if (from_ble_SCB_MODE_I2C_CONST_CFG  && from_ble_I2C_WAKE_ENABLE_CONST)
        from_ble_I2CRestoreConfig();

    #elif (from_ble_SCB_MODE_EZI2C_CONST_CFG && from_ble_EZI2C_WAKE_ENABLE_CONST)
        from_ble_EzI2CRestoreConfig();

    #elif (from_ble_SCB_MODE_SPI_CONST_CFG && from_ble_SPI_WAKE_ENABLE_CONST)
        from_ble_SpiRestoreConfig();

    #elif (from_ble_SCB_MODE_UART_CONST_CFG && from_ble_UART_WAKE_ENABLE_CONST)
        from_ble_UartRestoreConfig();

    #else

        if(0u != from_ble_backup.enableState)
        {
            from_ble_Enable();
        }

    #endif /* (from_ble_I2C_WAKE_ENABLE_CONST) */

#endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
