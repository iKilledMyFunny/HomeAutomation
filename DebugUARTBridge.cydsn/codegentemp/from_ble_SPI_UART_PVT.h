/***************************************************************************//**
* \file from_ble_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_from_ble_H)
#define CY_SCB_SPI_UART_PVT_from_ble_H

#include "from_ble_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (from_ble_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  from_ble_rxBufferHead;
    extern volatile uint32  from_ble_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   from_ble_rxBufferOverflow;
    /** @} globals */
#endif /* (from_ble_INTERNAL_RX_SW_BUFFER_CONST) */

#if (from_ble_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  from_ble_txBufferHead;
    extern volatile uint32  from_ble_txBufferTail;
#endif /* (from_ble_INTERNAL_TX_SW_BUFFER_CONST) */

#if (from_ble_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 from_ble_rxBufferInternal[from_ble_INTERNAL_RX_BUFFER_SIZE];
#endif /* (from_ble_INTERNAL_RX_SW_BUFFER) */

#if (from_ble_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 from_ble_txBufferInternal[from_ble_TX_BUFFER_SIZE];
#endif /* (from_ble_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void from_ble_SpiPostEnable(void);
void from_ble_SpiStop(void);

#if (from_ble_SCB_MODE_SPI_CONST_CFG)
    void from_ble_SpiInit(void);
#endif /* (from_ble_SCB_MODE_SPI_CONST_CFG) */

#if (from_ble_SPI_WAKE_ENABLE_CONST)
    void from_ble_SpiSaveConfig(void);
    void from_ble_SpiRestoreConfig(void);
#endif /* (from_ble_SPI_WAKE_ENABLE_CONST) */

void from_ble_UartPostEnable(void);
void from_ble_UartStop(void);

#if (from_ble_SCB_MODE_UART_CONST_CFG)
    void from_ble_UartInit(void);
#endif /* (from_ble_SCB_MODE_UART_CONST_CFG) */

#if (from_ble_UART_WAKE_ENABLE_CONST)
    void from_ble_UartSaveConfig(void);
    void from_ble_UartRestoreConfig(void);
#endif /* (from_ble_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in from_ble_SetPins() */
#define from_ble_UART_RX_PIN_ENABLE    (from_ble_UART_RX)
#define from_ble_UART_TX_PIN_ENABLE    (from_ble_UART_TX)

/* UART RTS and CTS position to be used in  from_ble_SetPins() */
#define from_ble_UART_RTS_PIN_ENABLE    (0x10u)
#define from_ble_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define from_ble_SpiUartEnableIntRx(intSourceMask)  from_ble_SetRxInterruptMode(intSourceMask)
#define from_ble_SpiUartEnableIntTx(intSourceMask)  from_ble_SetTxInterruptMode(intSourceMask)
uint32  from_ble_SpiUartDisableIntRx(void);
uint32  from_ble_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_from_ble_H) */


/* [] END OF FILE */
