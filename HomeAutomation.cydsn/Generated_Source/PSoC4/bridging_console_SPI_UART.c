/***************************************************************************//**
* \file bridging_console_SPI_UART.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "bridging_console_PVT.h"
#include "bridging_console_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(bridging_console_INTERNAL_RX_SW_BUFFER_CONST)
    /* Start index to put data into the software receive buffer.*/
    volatile uint32 bridging_console_rxBufferHead;
    /* Start index to get data from the software receive buffer.*/
    volatile uint32 bridging_console_rxBufferTail;
    /**
    * \addtogroup group_globals
    * \{
    */
    /** Sets when internal software receive buffer overflow
    *  was occurred.
    */
    volatile uint8  bridging_console_rxBufferOverflow;
    /** \} globals */
#endif /* (bridging_console_INTERNAL_RX_SW_BUFFER_CONST) */

#if(bridging_console_INTERNAL_TX_SW_BUFFER_CONST)
    /* Start index to put data into the software transmit buffer.*/
    volatile uint32 bridging_console_txBufferHead;
    /* Start index to get data from the software transmit buffer.*/
    volatile uint32 bridging_console_txBufferTail;
#endif /* (bridging_console_INTERNAL_TX_SW_BUFFER_CONST) */

#if(bridging_console_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 bridging_console_rxBufferInternal[bridging_console_INTERNAL_RX_BUFFER_SIZE];
#endif /* (bridging_console_INTERNAL_RX_SW_BUFFER) */

#if(bridging_console_INTERNAL_TX_SW_BUFFER)
    volatile uint8 bridging_console_txBufferInternal[bridging_console_TX_BUFFER_SIZE];
#endif /* (bridging_console_INTERNAL_TX_SW_BUFFER) */


#if(bridging_console_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: bridging_console_SpiUartReadRxData
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * \return
    *  Next data element from the receive buffer. 
    *  The amount of data bits to be received depends on RX data bits selection 
    *  (the data bit counting starts from LSB of return value).
    *
    * \globalvars
    *  bridging_console_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  bridging_console_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 bridging_console_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (bridging_console_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (bridging_console_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (bridging_console_CHECK_RX_SW_BUFFER)
        {
            if (bridging_console_rxBufferHead != bridging_console_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (bridging_console_rxBufferTail + 1u);

                if (bridging_console_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = bridging_console_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                bridging_console_rxBufferTail = locTail;

                #if (bridging_console_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (bridging_console_INTR_RX_MASK_REG & bridging_console_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        bridging_console_INTR_RX_MASK_REG |= bridging_console_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = bridging_console_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: bridging_console_SpiUartGetRxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * \return
    *  Number of received data elements.
    *
    * \globalvars
    *  bridging_console_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  bridging_console_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 bridging_console_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (bridging_console_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (bridging_console_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (bridging_console_CHECK_RX_SW_BUFFER)
        {
            locHead = bridging_console_rxBufferHead;

            if(locHead >= bridging_console_rxBufferTail)
            {
                size = (locHead - bridging_console_rxBufferTail);
            }
            else
            {
                size = (locHead + (bridging_console_INTERNAL_RX_BUFFER_SIZE - bridging_console_rxBufferTail));
            }
        }
        #else
        {
            size = bridging_console_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: bridging_console_SpiUartClearRxBuffer
    ****************************************************************************//**
    *
    *  Clears the receive buffer and RX FIFO.
    *
    * \globalvars
    *  bridging_console_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  bridging_console_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    void bridging_console_SpiUartClearRxBuffer(void)
    {
        #if (bridging_console_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            bridging_console_DisableInt();

            /* Flush RX software buffer */
            bridging_console_rxBufferHead = bridging_console_rxBufferTail;
            bridging_console_rxBufferOverflow = 0u;

            bridging_console_CLEAR_RX_FIFO;
            bridging_console_ClearRxInterruptSource(bridging_console_INTR_RX_ALL);

            #if (bridging_console_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                bridging_console_INTR_RX_MASK_REG |= bridging_console_INTR_RX_NOT_EMPTY;
            }
            #endif
            
            /* Release lock */
            bridging_console_EnableInt();
        }
        #else
        {
            bridging_console_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (bridging_console_RX_DIRECTION) */


#if(bridging_console_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: bridging_console_SpiUartWriteTxData
    ****************************************************************************//**
    *
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *   The amount of data bits to be transmitted depends on TX data bits selection 
    *   (the data bit counting starts from LSB of txDataByte).
    *
    * \globalvars
    *  bridging_console_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  bridging_console_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void bridging_console_SpiUartWriteTxData(uint32 txData)
    {
    #if (bridging_console_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (bridging_console_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (bridging_console_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((bridging_console_txBufferHead == bridging_console_txBufferTail) &&
                (bridging_console_SPI_UART_FIFO_SIZE != bridging_console_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                bridging_console_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (bridging_console_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (bridging_console_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == bridging_console_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                bridging_console_ClearTxInterruptSource(bridging_console_INTR_TX_NOT_FULL);

                bridging_console_PutWordInTxBuffer(locHead, txData);

                bridging_console_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (bridging_console_INTR_TX_MASK_REG & bridging_console_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    bridging_console_INTR_TX_MASK_REG |= (uint32) bridging_console_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (bridging_console_SPI_UART_FIFO_SIZE == bridging_console_GET_TX_FIFO_ENTRIES)
            {
            }

            bridging_console_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: bridging_console_SpiUartPutArray
    ****************************************************************************//**
    *
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * \param wrBuf: pointer to an array of data to be placed in transmit buffer. 
    *  The width of the data to be transmitted depends on TX data width selection 
    *  (the data bit counting starts from LSB for each array element).
    * \param count: number of data elements to be placed in the transmit buffer.
    *
    * \globalvars
    *  bridging_console_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  bridging_console_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void bridging_console_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            bridging_console_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: bridging_console_SpiUartGetTxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of elements currently in the transmit buffer.
    *   - TX software buffer is disabled: returns the number of used entries in
    *     TX FIFO.
    *   - TX software buffer is enabled: returns the number of elements currently
    *     used in the transmit buffer. This number does not include used entries in
    *     the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *     not full.
    *
    * \return
    *  Number of data elements ready to transmit.
    *
    * \globalvars
    *  bridging_console_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  bridging_console_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    uint32 bridging_console_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (bridging_console_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (bridging_console_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (bridging_console_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = bridging_console_txBufferTail;

            if (bridging_console_txBufferHead >= locTail)
            {
                size = (bridging_console_txBufferHead - locTail);
            }
            else
            {
                size = (bridging_console_txBufferHead + (bridging_console_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = bridging_console_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: bridging_console_SpiUartClearTxBuffer
    ****************************************************************************//**
    *
    *  Clears the transmit buffer and TX FIFO.
    *
    * \globalvars
    *  bridging_console_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  bridging_console_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void bridging_console_SpiUartClearTxBuffer(void)
    {
        #if (bridging_console_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            bridging_console_DisableInt();

            /* Flush TX software buffer */
            bridging_console_txBufferHead = bridging_console_txBufferTail;

            bridging_console_INTR_TX_MASK_REG &= (uint32) ~bridging_console_INTR_TX_NOT_FULL;
            bridging_console_CLEAR_TX_FIFO;
            bridging_console_ClearTxInterruptSource(bridging_console_INTR_TX_ALL);

            /* Release lock */
            bridging_console_EnableInt();
        }
        #else
        {
            bridging_console_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (bridging_console_TX_DIRECTION) */


/*******************************************************************************
* Function Name: bridging_console_SpiUartDisableIntRx
****************************************************************************//**
*
*  Disables the RX interrupt sources.
*
*  \return
*   Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 bridging_console_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = bridging_console_GetRxInterruptMode();

    bridging_console_SetRxInterruptMode(bridging_console_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: bridging_console_SpiUartDisableIntTx
****************************************************************************//**
*
*  Disables TX interrupt sources.
*
*  \return
*   Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 bridging_console_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = bridging_console_GetTxInterruptMode();

    bridging_console_SetTxInterruptMode(bridging_console_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: bridging_console_PutWordInRxBuffer
    ****************************************************************************//**
    *
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param index:      index to store data byte/word in the RX buffer.
    *  \param rxDataByte: byte/word to store.
    *
    *******************************************************************************/
    void bridging_console_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (bridging_console_ONE_BYTE_WIDTH == bridging_console_rxDataBits)
        {
            bridging_console_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            bridging_console_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            bridging_console_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: bridging_console_GetWordFromRxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \return
    *   Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 bridging_console_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (bridging_console_ONE_BYTE_WIDTH == bridging_console_rxDataBits)
        {
            value = bridging_console_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) bridging_console_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)bridging_console_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: bridging_console_PutWordInTxBuffer
    ****************************************************************************//**
    *
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx:        index to store data byte/word in the TX buffer.
    *  \param txDataByte: byte/word to store.
    *
    *******************************************************************************/
    void bridging_console_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (bridging_console_ONE_BYTE_WIDTH == bridging_console_txDataBits)
        {
            bridging_console_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            bridging_console_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            bridging_console_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: bridging_console_GetWordFromTxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx: index to get data byte/word from the TX buffer.
    *
    *  \return
    *   Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 bridging_console_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (bridging_console_ONE_BYTE_WIDTH == bridging_console_txDataBits)
        {
            value = (uint32) bridging_console_txBuffer[idx];
        }
        else
        {
            value  = (uint32) bridging_console_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) bridging_console_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
