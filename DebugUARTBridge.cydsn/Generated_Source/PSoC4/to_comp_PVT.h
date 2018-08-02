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

#if !defined(CY_SCB_PVT_to_comp_H)
#define CY_SCB_PVT_to_comp_H

#include "to_comp.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define to_comp_SetI2CExtClkInterruptMode(interruptMask) to_comp_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define to_comp_ClearI2CExtClkInterruptSource(interruptMask) to_comp_CLEAR_INTR_I2C_EC(interruptMask)
#define to_comp_GetI2CExtClkInterruptSource()                (to_comp_INTR_I2C_EC_REG)
#define to_comp_GetI2CExtClkInterruptMode()                  (to_comp_INTR_I2C_EC_MASK_REG)
#define to_comp_GetI2CExtClkInterruptSourceMasked()          (to_comp_INTR_I2C_EC_MASKED_REG)

#if (!to_comp_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define to_comp_SetSpiExtClkInterruptMode(interruptMask) \
                                                                to_comp_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define to_comp_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                to_comp_CLEAR_INTR_SPI_EC(interruptMask)
    #define to_comp_GetExtSpiClkInterruptSource()                 (to_comp_INTR_SPI_EC_REG)
    #define to_comp_GetExtSpiClkInterruptMode()                   (to_comp_INTR_SPI_EC_MASK_REG)
    #define to_comp_GetExtSpiClkInterruptSourceMasked()           (to_comp_INTR_SPI_EC_MASKED_REG)
#endif /* (!to_comp_CY_SCBIP_V1) */

#if(to_comp_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void to_comp_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (to_comp_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (to_comp_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_to_comp_CUSTOM_INTR_HANDLER)
    extern cyisraddress to_comp_customIntrHandler;
#endif /* !defined (CY_REMOVE_to_comp_CUSTOM_INTR_HANDLER) */
#endif /* (to_comp_SCB_IRQ_INTERNAL) */

extern to_comp_BACKUP_STRUCT to_comp_backup;

#if(to_comp_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 to_comp_scbMode;
    extern uint8 to_comp_scbEnableWake;
    extern uint8 to_comp_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 to_comp_mode;
    extern uint8 to_comp_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * to_comp_rxBuffer;
    extern uint8   to_comp_rxDataBits;
    extern uint32  to_comp_rxBufferSize;

    extern volatile uint8 * to_comp_txBuffer;
    extern uint8   to_comp_txDataBits;
    extern uint32  to_comp_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 to_comp_numberOfAddr;
    extern uint8 to_comp_subAddrSize;
#endif /* (to_comp_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (to_comp_SCB_MODE_I2C_CONST_CFG || \
        to_comp_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 to_comp_IntrTxMask;
#endif /* (! (to_comp_SCB_MODE_I2C_CONST_CFG || \
              to_comp_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(to_comp_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define to_comp_SCB_MODE_I2C_RUNTM_CFG     (to_comp_SCB_MODE_I2C      == to_comp_scbMode)
    #define to_comp_SCB_MODE_SPI_RUNTM_CFG     (to_comp_SCB_MODE_SPI      == to_comp_scbMode)
    #define to_comp_SCB_MODE_UART_RUNTM_CFG    (to_comp_SCB_MODE_UART     == to_comp_scbMode)
    #define to_comp_SCB_MODE_EZI2C_RUNTM_CFG   (to_comp_SCB_MODE_EZI2C    == to_comp_scbMode)
    #define to_comp_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (to_comp_SCB_MODE_UNCONFIG == to_comp_scbMode)

    /* Defines wakeup enable */
    #define to_comp_SCB_WAKE_ENABLE_CHECK       (0u != to_comp_scbEnableWake)
#endif /* (to_comp_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!to_comp_CY_SCBIP_V1)
    #define to_comp_SCB_PINS_NUMBER    (7u)
#else
    #define to_comp_SCB_PINS_NUMBER    (2u)
#endif /* (!to_comp_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_to_comp_H) */


/* [] END OF FILE */
