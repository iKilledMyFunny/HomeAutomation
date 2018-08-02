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

#if !defined(CY_SCB_PVT_from_ble_H)
#define CY_SCB_PVT_from_ble_H

#include "from_ble.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define from_ble_SetI2CExtClkInterruptMode(interruptMask) from_ble_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define from_ble_ClearI2CExtClkInterruptSource(interruptMask) from_ble_CLEAR_INTR_I2C_EC(interruptMask)
#define from_ble_GetI2CExtClkInterruptSource()                (from_ble_INTR_I2C_EC_REG)
#define from_ble_GetI2CExtClkInterruptMode()                  (from_ble_INTR_I2C_EC_MASK_REG)
#define from_ble_GetI2CExtClkInterruptSourceMasked()          (from_ble_INTR_I2C_EC_MASKED_REG)

#if (!from_ble_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define from_ble_SetSpiExtClkInterruptMode(interruptMask) \
                                                                from_ble_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define from_ble_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                from_ble_CLEAR_INTR_SPI_EC(interruptMask)
    #define from_ble_GetExtSpiClkInterruptSource()                 (from_ble_INTR_SPI_EC_REG)
    #define from_ble_GetExtSpiClkInterruptMode()                   (from_ble_INTR_SPI_EC_MASK_REG)
    #define from_ble_GetExtSpiClkInterruptSourceMasked()           (from_ble_INTR_SPI_EC_MASKED_REG)
#endif /* (!from_ble_CY_SCBIP_V1) */

#if(from_ble_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void from_ble_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (from_ble_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_from_ble_CUSTOM_INTR_HANDLER)
    extern cyisraddress from_ble_customIntrHandler;
#endif /* !defined (CY_REMOVE_from_ble_CUSTOM_INTR_HANDLER) */
#endif /* (from_ble_SCB_IRQ_INTERNAL) */

extern from_ble_BACKUP_STRUCT from_ble_backup;

#if(from_ble_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 from_ble_scbMode;
    extern uint8 from_ble_scbEnableWake;
    extern uint8 from_ble_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 from_ble_mode;
    extern uint8 from_ble_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * from_ble_rxBuffer;
    extern uint8   from_ble_rxDataBits;
    extern uint32  from_ble_rxBufferSize;

    extern volatile uint8 * from_ble_txBuffer;
    extern uint8   from_ble_txDataBits;
    extern uint32  from_ble_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 from_ble_numberOfAddr;
    extern uint8 from_ble_subAddrSize;
#endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (from_ble_SCB_MODE_I2C_CONST_CFG || \
        from_ble_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 from_ble_IntrTxMask;
#endif /* (! (from_ble_SCB_MODE_I2C_CONST_CFG || \
              from_ble_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(from_ble_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define from_ble_SCB_MODE_I2C_RUNTM_CFG     (from_ble_SCB_MODE_I2C      == from_ble_scbMode)
    #define from_ble_SCB_MODE_SPI_RUNTM_CFG     (from_ble_SCB_MODE_SPI      == from_ble_scbMode)
    #define from_ble_SCB_MODE_UART_RUNTM_CFG    (from_ble_SCB_MODE_UART     == from_ble_scbMode)
    #define from_ble_SCB_MODE_EZI2C_RUNTM_CFG   (from_ble_SCB_MODE_EZI2C    == from_ble_scbMode)
    #define from_ble_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (from_ble_SCB_MODE_UNCONFIG == from_ble_scbMode)

    /* Defines wakeup enable */
    #define from_ble_SCB_WAKE_ENABLE_CHECK       (0u != from_ble_scbEnableWake)
#endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!from_ble_CY_SCBIP_V1)
    #define from_ble_SCB_PINS_NUMBER    (7u)
#else
    #define from_ble_SCB_PINS_NUMBER    (2u)
#endif /* (!from_ble_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_from_ble_H) */


/* [] END OF FILE */
