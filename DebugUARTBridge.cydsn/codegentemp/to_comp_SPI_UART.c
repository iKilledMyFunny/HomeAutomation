/***************************************************************************//**
* \file to_comp_SPI_UART.c
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

#include "to_comp_PVT.h"
#include "to_comp_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(to_comp_INTERNAL_RX_SW_BUFFER_CONST)
    /* Start index to put data into the software receive buffer.*/
    volatile uint32 to_comp_rxBufferHead;
    /* Start index to get data from the software receive buffer.*/
    volatile uint32 to_comp_rxBufferTail;
    /**
    * \addtogroup group_globals
    * \{
    */
    /** Sets when internal software receive buffer overflow
    *  was occurred.
    */
    volatile uint8  to_comp_rxBufferOverflow;
    /** \} globals */
#endif /* (to_comp_INTERNAL_RX_SW_BUFFER_CONST) */

#if(to_comp_INTERNAL_TX_SW_BUFFER_CONST)
    /* Start index to put data into the software transmit buffer.*/
    volatile uint32 to_comp_txBufferHead;
    /* Start index to get data from the software transmit buffer.*/
    volatile uint32 to_comp_txBufferTail;
#endif /* (to_comp_INTERNAL_TX_SW_BUFFER_CONST) */

#if(to_comp_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 to_comp_rxBufferInternal[to_comp_INTERNAL_RX_BUFFER_SIZE];
#endif /* (to_comp_INTERNAL_RX_SW_BUFFER) */

#if(to_comp_INTERNAL_TX_SW_BUFFER)
    volatile uint8 to_comp_txBufferInternal[to_comp_TX_BUFFER_SIZE];
#endif /* (to_comp_INTERNAL_TX_SW_BUFFER) */


#if(to_comp_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: to_comp_SpiUartReadRxData
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
    *  to_comp_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  to_comp_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 to_comp_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (to_comp_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (to_comp_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (to_comp_CHECK_RX_SW_BUFFER)
        {
            if (to_comp_rxBufferHead != to_comp_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (to_comp_rxBufferTail + 1u);

                if (to_comp_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = to_comp_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                to_comp_rxBufferTail = locTail;

                #if (to_comp_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (to_comp_INTR_RX_MASK_REG & to_comp_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        to_comp_INTR_RX_MASK_REG |= to_comp_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = to_comp_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: to_comp_SpiUartGetRxBufferSize
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
    *  to_comp_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  to_comp_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 to_comp_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (to_comp_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (to_comp_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (to_comp_CHECK_RX_SW_BUFFER)
        {
            locHead = to_comp_rxBufferHead;

            if(locHead >= to_comp_rxBufferTail)
            {
                size = (locHead - to_comp_rxBufferTail);
            }
            else
            {
                size = (locHead + (to_comp_INTERNAL_RX_BUFFER_SIZE - to_comp_rxBufferTail));
            }
        }
        #else
        {
            size = to_comp_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: to_comp_SpiUartClearRxBuffer
    ****************************************************************************//**
    *
    *  Clears the receive buffer and RX FIFO.
    *
    * \globalvars
    *  to_comp_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  to_comp_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    void to_comp_SpiUartClearRxBuffer(void)
    {
        #if (to_comp_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            to_comp_DisableInt();

            /* Flush RX software buffer */
            to_comp_rxBufferHead = to_comp_rxBufferTail;
            to_comp_rxBufferOverflow = 0u;

            to_comp_CLEAR_RX_FIFO;
            to_comp_ClearRxInterruptSource(to_comp_INTR_RX_ALL);

            #if (to_comp_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                to_comp_INTR_RX_MASK_REG |= to_comp_INTR_RX_NOT_EMPTY;
            }
            #endif
            
            /* Release lock */
            to_comp_EnableInt();
        }
        #else
        {
            to_comp_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (to_comp_RX_DIRECTION) */


#if(to_comp_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: to_comp_SpiUartWriteTxData
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
    *  to_comp_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  to_comp_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void to_comp_SpiUartWriteTxData(uint32 txData)
    {
    #if (to_comp_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (to_comp_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (to_comp_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((to_comp_txBufferHead == to_comp_txBufferTail) &&
                (to_comp_SPI_UART_FIFO_SIZE != to_comp_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                to_comp_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (to_comp_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (to_comp_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == to_comp_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                to_comp_ClearTxInterruptSource(to_comp_INTR_TX_NOT_FULL);

                to_comp_PutWordInTxBuffer(locHead, txData);

                to_comp_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (to_comp_INTR_TX_MASK_REG & to_comp_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    to_comp_INTR_TX_MASK_REG |= (uint32) to_comp_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (to_comp_SPI_UART_FIFO_SIZE == to_comp_GET_TX_FIFO_ENTRIES)
            {
            }

            to_comp_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: to_comp_SpiUartPutArray
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
    *  to_comp_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  to_comp_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void to_comp_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            to_comp_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: to_comp_SpiUartGetTxBufferSize
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
    *  to_comp_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  to_comp_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    uint32 to_comp_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (to_comp_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (to_comp_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (to_comp_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = to_comp_txBufferTail;

            if (to_comp_txBufferHead >= locTail)
            {
                size = (to_comp_txBufferHead - locTail);
            }
            else
            {
                size = (to_comp_txBufferHead + (to_comp_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = to_comp_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: to_comp_SpiUartClearTxBuffer
    ****************************************************************************//**
    *
    *  Clears the transmit buffer and TX FIFO.
    *
    * \globalvars
    *  to_comp_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  to_comp_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void to_comp_SpiUartClearTxBuffer(void)
    {
        #if (to_comp_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            to_comp_DisableInt();

            /* Flush TX software buffer */
            to_comp_txBufferHead = to_comp_txBufferTail;

            to_comp_INTR_TX_MASK_REG &= (uint32) ~to_comp_INTR_TX_NOT_FULL;
            to_comp_CLEAR_TX_FIFO;
            to_comp_ClearTxInterruptSource(to_comp_INTR_TX_ALL);

            /* Release lock */
            to_comp_EnableInt();
        }
        #else
        {
            to_comp_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (to_comp_TX_DIRECTION) */


/*******************************************************************************
* Function Name: to_comp_SpiUartDisableIntRx
****************************************************************************//**
*
*  Disables the RX interrupt sources.
*
*  \return
*   Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 to_comp_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = to_comp_GetRxInterruptMode();

    to_comp_SetRxInterruptMode(to_comp_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: to_comp_SpiUartDisableIntTx
****************************************************************************//**
*
*  Disables TX interrupt sources.
*
*  \return
*   Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 to_comp_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = to_comp_GetTxInterruptMode();

    to_comp_SetTxInterruptMode(to_comp_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(to_comp_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: to_comp_PutWordInRxBuffer
    ****************************************************************************//**
    *
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param index:      index to store data byte/word in the RX buffer.
    *  \param rxDataByte: byte/word to store.
    *
    *******************************************************************************/
    void to_comp_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (to_comp_ONE_BYTE_WIDTH == to_comp_rxDataBits)
        {
            to_comp_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            to_comp_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            to_comp_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: to_comp_GetWordFromRxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \return
    *   Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 to_comp_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (to_comp_ONE_BYTE_WIDTH == to_comp_rxDataBits)
        {
            value = to_comp_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) to_comp_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)to_comp_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: to_comp_PutWordInTxBuffer
    ****************************************************************************//**
    *
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx:        index to store data byte/word in the TX buffer.
    *  \param txDataByte: byte/word to store.
    *
    *******************************************************************************/
    void to_comp_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (to_comp_ONE_BYTE_WIDTH == to_comp_txDataBits)
        {
            to_comp_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            to_comp_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            to_comp_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: to_comp_GetWordFromTxBuffer
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
    uint32 to_comp_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (to_comp_ONE_BYTE_WIDTH == to_comp_txDataBits)
        {
            value = (uint32) to_comp_txBuffer[idx];
        }
        else
        {
            value  = (uint32) to_comp_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) to_comp_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (to_comp_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
