/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_bridging_console_H)
#define CY_SCB_PVT_bridging_console_H

#include "bridging_console.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define bridging_console_SetI2CExtClkInterruptMode(interruptMask) bridging_console_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define bridging_console_ClearI2CExtClkInterruptSource(interruptMask) bridging_console_CLEAR_INTR_I2C_EC(interruptMask)
#define bridging_console_GetI2CExtClkInterruptSource()                (bridging_console_INTR_I2C_EC_REG)
#define bridging_console_GetI2CExtClkInterruptMode()                  (bridging_console_INTR_I2C_EC_MASK_REG)
#define bridging_console_GetI2CExtClkInterruptSourceMasked()          (bridging_console_INTR_I2C_EC_MASKED_REG)

#if (!bridging_console_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define bridging_console_SetSpiExtClkInterruptMode(interruptMask) \
                                                                bridging_console_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define bridging_console_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                bridging_console_CLEAR_INTR_SPI_EC(interruptMask)
    #define bridging_console_GetExtSpiClkInterruptSource()                 (bridging_console_INTR_SPI_EC_REG)
    #define bridging_console_GetExtSpiClkInterruptMode()                   (bridging_console_INTR_SPI_EC_MASK_REG)
    #define bridging_console_GetExtSpiClkInterruptSourceMasked()           (bridging_console_INTR_SPI_EC_MASKED_REG)
#endif /* (!bridging_console_CY_SCBIP_V1) */

#if(bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void bridging_console_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (bridging_console_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_bridging_console_CUSTOM_INTR_HANDLER)
    extern cyisraddress bridging_console_customIntrHandler;
#endif /* !defined (CY_REMOVE_bridging_console_CUSTOM_INTR_HANDLER) */
#endif /* (bridging_console_SCB_IRQ_INTERNAL) */

extern bridging_console_BACKUP_STRUCT bridging_console_backup;

#if(bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 bridging_console_scbMode;
    extern uint8 bridging_console_scbEnableWake;
    extern uint8 bridging_console_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 bridging_console_mode;
    extern uint8 bridging_console_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * bridging_console_rxBuffer;
    extern uint8   bridging_console_rxDataBits;
    extern uint32  bridging_console_rxBufferSize;

    extern volatile uint8 * bridging_console_txBuffer;
    extern uint8   bridging_console_txDataBits;
    extern uint32  bridging_console_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 bridging_console_numberOfAddr;
    extern uint8 bridging_console_subAddrSize;
#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (bridging_console_SCB_MODE_I2C_CONST_CFG || \
        bridging_console_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 bridging_console_IntrTxMask;
#endif /* (! (bridging_console_SCB_MODE_I2C_CONST_CFG || \
              bridging_console_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define bridging_console_SCB_MODE_I2C_RUNTM_CFG     (bridging_console_SCB_MODE_I2C      == bridging_console_scbMode)
    #define bridging_console_SCB_MODE_SPI_RUNTM_CFG     (bridging_console_SCB_MODE_SPI      == bridging_console_scbMode)
    #define bridging_console_SCB_MODE_UART_RUNTM_CFG    (bridging_console_SCB_MODE_UART     == bridging_console_scbMode)
    #define bridging_console_SCB_MODE_EZI2C_RUNTM_CFG   (bridging_console_SCB_MODE_EZI2C    == bridging_console_scbMode)
    #define bridging_console_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (bridging_console_SCB_MODE_UNCONFIG == bridging_console_scbMode)

    /* Defines wakeup enable */
    #define bridging_console_SCB_WAKE_ENABLE_CHECK       (0u != bridging_console_scbEnableWake)
#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!bridging_console_CY_SCBIP_V1)
    #define bridging_console_SCB_PINS_NUMBER    (7u)
#else
    #define bridging_console_SCB_PINS_NUMBER    (2u)
#endif /* (!bridging_console_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_bridging_console_H) */


/* [] END OF FILE */
