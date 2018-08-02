/***************************************************************************//**
* \file to_comp_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_to_comp_H)
#define CY_SCB_SPI_UART_PVT_to_comp_H

#include "to_comp_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (to_comp_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  to_comp_rxBufferHead;
    extern volatile uint32  to_comp_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   to_comp_rxBufferOverflow;
    /** @} globals */
#endif /* (to_comp_INTERNAL_RX_SW_BUFFER_CONST) */

#if (to_comp_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  to_comp_txBufferHead;
    extern volatile uint32  to_comp_txBufferTail;
#endif /* (to_comp_INTERNAL_TX_SW_BUFFER_CONST) */

#if (to_comp_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 to_comp_rxBufferInternal[to_comp_INTERNAL_RX_BUFFER_SIZE];
#endif /* (to_comp_INTERNAL_RX_SW_BUFFER) */

#if (to_comp_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 to_comp_txBufferInternal[to_comp_TX_BUFFER_SIZE];
#endif /* (to_comp_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void to_comp_SpiPostEnable(void);
void to_comp_SpiStop(void);

#if (to_comp_SCB_MODE_SPI_CONST_CFG)
    void to_comp_SpiInit(void);
#endif /* (to_comp_SCB_MODE_SPI_CONST_CFG) */

#if (to_comp_SPI_WAKE_ENABLE_CONST)
    void to_comp_SpiSaveConfig(void);
    void to_comp_SpiRestoreConfig(void);
#endif /* (to_comp_SPI_WAKE_ENABLE_CONST) */

void to_comp_UartPostEnable(void);
void to_comp_UartStop(void);

#if (to_comp_SCB_MODE_UART_CONST_CFG)
    void to_comp_UartInit(void);
#endif /* (to_comp_SCB_MODE_UART_CONST_CFG) */

#if (to_comp_UART_WAKE_ENABLE_CONST)
    void to_comp_UartSaveConfig(void);
    void to_comp_UartRestoreConfig(void);
#endif /* (to_comp_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in to_comp_SetPins() */
#define to_comp_UART_RX_PIN_ENABLE    (to_comp_UART_RX)
#define to_comp_UART_TX_PIN_ENABLE    (to_comp_UART_TX)

/* UART RTS and CTS position to be used in  to_comp_SetPins() */
#define to_comp_UART_RTS_PIN_ENABLE    (0x10u)
#define to_comp_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define to_comp_SpiUartEnableIntRx(intSourceMask)  to_comp_SetRxInterruptMode(intSourceMask)
#define to_comp_SpiUartEnableIntTx(intSourceMask)  to_comp_SetTxInterruptMode(intSourceMask)
uint32  to_comp_SpiUartDisableIntRx(void);
uint32  to_comp_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_to_comp_H) */


/* [] END OF FILE */
