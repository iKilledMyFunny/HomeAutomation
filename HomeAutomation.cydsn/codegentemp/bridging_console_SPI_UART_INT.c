/***************************************************************************//**
* \file bridging_console_SPI_UART_INT.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
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

#include "bridging_console_PVT.h"
#include "bridging_console_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (bridging_console_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: bridging_console_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(bridging_console_SPI_UART_ISR)
{
#if (bridging_console_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (bridging_console_INTERNAL_RX_SW_BUFFER_CONST) */

#if (bridging_console_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (bridging_console_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef bridging_console_SPI_UART_ISR_ENTRY_CALLBACK
    bridging_console_SPI_UART_ISR_EntryCallback();
#endif /* bridging_console_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != bridging_console_customIntrHandler)
    {
        bridging_console_customIntrHandler();
    }

    #if(bridging_console_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        bridging_console_ClearSpiExtClkInterruptSource(bridging_console_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (bridging_console_CHECK_RX_SW_BUFFER)
    {
        if (bridging_console_CHECK_INTR_RX_MASKED(bridging_console_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (bridging_console_rxBufferHead + 1u);

                /* Adjust local head index */
                if (bridging_console_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == bridging_console_rxBufferTail)
                {
                    #if (bridging_console_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        bridging_console_INTR_RX_MASK_REG &= ~bridging_console_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) bridging_console_RX_FIFO_RD_REG;
                        bridging_console_rxBufferOverflow = (uint8) bridging_console_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    bridging_console_PutWordInRxBuffer(locHead, bridging_console_RX_FIFO_RD_REG);

                    /* Move head index */
                    bridging_console_rxBufferHead = locHead;
                }
            }
            while(0u != bridging_console_GET_RX_FIFO_ENTRIES);

            bridging_console_ClearRxInterruptSource(bridging_console_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (bridging_console_CHECK_TX_SW_BUFFER)
    {
        if (bridging_console_CHECK_INTR_TX_MASKED(bridging_console_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (bridging_console_txBufferHead != bridging_console_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (bridging_console_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (bridging_console_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    bridging_console_TX_FIFO_WR_REG = bridging_console_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    bridging_console_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    bridging_console_DISABLE_INTR_TX(bridging_console_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (bridging_console_SPI_UART_FIFO_SIZE != bridging_console_GET_TX_FIFO_ENTRIES);

            bridging_console_ClearTxInterruptSource(bridging_console_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef bridging_console_SPI_UART_ISR_EXIT_CALLBACK
    bridging_console_SPI_UART_ISR_ExitCallback();
#endif /* bridging_console_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (bridging_console_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
