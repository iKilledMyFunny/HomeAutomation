/***************************************************************************//**
* \file bridging_console_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_bridging_console_H)
#define CY_SCB_SPI_UART_PVT_bridging_console_H

#include "bridging_console_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (bridging_console_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  bridging_console_rxBufferHead;
    extern volatile uint32  bridging_console_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   bridging_console_rxBufferOverflow;
    /** @} globals */
#endif /* (bridging_console_INTERNAL_RX_SW_BUFFER_CONST) */

#if (bridging_console_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  bridging_console_txBufferHead;
    extern volatile uint32  bridging_console_txBufferTail;
#endif /* (bridging_console_INTERNAL_TX_SW_BUFFER_CONST) */

#if (bridging_console_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 bridging_console_rxBufferInternal[bridging_console_INTERNAL_RX_BUFFER_SIZE];
#endif /* (bridging_console_INTERNAL_RX_SW_BUFFER) */

#if (bridging_console_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 bridging_console_txBufferInternal[bridging_console_TX_BUFFER_SIZE];
#endif /* (bridging_console_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void bridging_console_SpiPostEnable(void);
void bridging_console_SpiStop(void);

#if (bridging_console_SCB_MODE_SPI_CONST_CFG)
    void bridging_console_SpiInit(void);
#endif /* (bridging_console_SCB_MODE_SPI_CONST_CFG) */

#if (bridging_console_SPI_WAKE_ENABLE_CONST)
    void bridging_console_SpiSaveConfig(void);
    void bridging_console_SpiRestoreConfig(void);
#endif /* (bridging_console_SPI_WAKE_ENABLE_CONST) */

void bridging_console_UartPostEnable(void);
void bridging_console_UartStop(void);

#if (bridging_console_SCB_MODE_UART_CONST_CFG)
    void bridging_console_UartInit(void);
#endif /* (bridging_console_SCB_MODE_UART_CONST_CFG) */

#if (bridging_console_UART_WAKE_ENABLE_CONST)
    void bridging_console_UartSaveConfig(void);
    void bridging_console_UartRestoreConfig(void);
#endif /* (bridging_console_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in bridging_console_SetPins() */
#define bridging_console_UART_RX_PIN_ENABLE    (bridging_console_UART_RX)
#define bridging_console_UART_TX_PIN_ENABLE    (bridging_console_UART_TX)

/* UART RTS and CTS position to be used in  bridging_console_SetPins() */
#define bridging_console_UART_RTS_PIN_ENABLE    (0x10u)
#define bridging_console_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define bridging_console_SpiUartEnableIntRx(intSourceMask)  bridging_console_SetRxInterruptMode(intSourceMask)
#define bridging_console_SpiUartEnableIntTx(intSourceMask)  bridging_console_SetTxInterruptMode(intSourceMask)
uint32  bridging_console_SpiUartDisableIntRx(void);
uint32  bridging_console_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_bridging_console_H) */


/* [] END OF FILE */
