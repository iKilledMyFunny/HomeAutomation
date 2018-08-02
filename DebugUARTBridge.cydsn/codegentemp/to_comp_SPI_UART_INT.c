/***************************************************************************//**
* \file to_comp_SPI_UART_INT.c
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

#include "to_comp_PVT.h"
#include "to_comp_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (to_comp_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: to_comp_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(to_comp_SPI_UART_ISR)
{
#if (to_comp_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (to_comp_INTERNAL_RX_SW_BUFFER_CONST) */

#if (to_comp_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (to_comp_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef to_comp_SPI_UART_ISR_ENTRY_CALLBACK
    to_comp_SPI_UART_ISR_EntryCallback();
#endif /* to_comp_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != to_comp_customIntrHandler)
    {
        to_comp_customIntrHandler();
    }

    #if(to_comp_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        to_comp_ClearSpiExtClkInterruptSource(to_comp_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (to_comp_CHECK_RX_SW_BUFFER)
    {
        if (to_comp_CHECK_INTR_RX_MASKED(to_comp_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (to_comp_rxBufferHead + 1u);

                /* Adjust local head index */
                if (to_comp_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == to_comp_rxBufferTail)
                {
                    #if (to_comp_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        to_comp_INTR_RX_MASK_REG &= ~to_comp_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) to_comp_RX_FIFO_RD_REG;
                        to_comp_rxBufferOverflow = (uint8) to_comp_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    to_comp_PutWordInRxBuffer(locHead, to_comp_RX_FIFO_RD_REG);

                    /* Move head index */
                    to_comp_rxBufferHead = locHead;
                }
            }
            while(0u != to_comp_GET_RX_FIFO_ENTRIES);

            to_comp_ClearRxInterruptSource(to_comp_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (to_comp_CHECK_TX_SW_BUFFER)
    {
        if (to_comp_CHECK_INTR_TX_MASKED(to_comp_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (to_comp_txBufferHead != to_comp_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (to_comp_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (to_comp_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    to_comp_TX_FIFO_WR_REG = to_comp_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    to_comp_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    to_comp_DISABLE_INTR_TX(to_comp_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (to_comp_SPI_UART_FIFO_SIZE != to_comp_GET_TX_FIFO_ENTRIES);

            to_comp_ClearTxInterruptSource(to_comp_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef to_comp_SPI_UART_ISR_EXIT_CALLBACK
    to_comp_SPI_UART_ISR_ExitCallback();
#endif /* to_comp_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (to_comp_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
