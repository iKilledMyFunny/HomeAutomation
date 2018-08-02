/***************************************************************************//**
* \file from_ble_SPI_UART_INT.c
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

#include "from_ble_PVT.h"
#include "from_ble_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (from_ble_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: from_ble_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(from_ble_SPI_UART_ISR)
{
#if (from_ble_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (from_ble_INTERNAL_RX_SW_BUFFER_CONST) */

#if (from_ble_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (from_ble_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef from_ble_SPI_UART_ISR_ENTRY_CALLBACK
    from_ble_SPI_UART_ISR_EntryCallback();
#endif /* from_ble_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != from_ble_customIntrHandler)
    {
        from_ble_customIntrHandler();
    }

    #if(from_ble_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        from_ble_ClearSpiExtClkInterruptSource(from_ble_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (from_ble_CHECK_RX_SW_BUFFER)
    {
        if (from_ble_CHECK_INTR_RX_MASKED(from_ble_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (from_ble_rxBufferHead + 1u);

                /* Adjust local head index */
                if (from_ble_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == from_ble_rxBufferTail)
                {
                    #if (from_ble_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        from_ble_INTR_RX_MASK_REG &= ~from_ble_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) from_ble_RX_FIFO_RD_REG;
                        from_ble_rxBufferOverflow = (uint8) from_ble_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    from_ble_PutWordInRxBuffer(locHead, from_ble_RX_FIFO_RD_REG);

                    /* Move head index */
                    from_ble_rxBufferHead = locHead;
                }
            }
            while(0u != from_ble_GET_RX_FIFO_ENTRIES);

            from_ble_ClearRxInterruptSource(from_ble_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (from_ble_CHECK_TX_SW_BUFFER)
    {
        if (from_ble_CHECK_INTR_TX_MASKED(from_ble_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (from_ble_txBufferHead != from_ble_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (from_ble_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (from_ble_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    from_ble_TX_FIFO_WR_REG = from_ble_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    from_ble_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    from_ble_DISABLE_INTR_TX(from_ble_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (from_ble_SPI_UART_FIFO_SIZE != from_ble_GET_TX_FIFO_ENTRIES);

            from_ble_ClearTxInterruptSource(from_ble_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef from_ble_SPI_UART_ISR_EXIT_CALLBACK
    from_ble_SPI_UART_ISR_ExitCallback();
#endif /* from_ble_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (from_ble_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
