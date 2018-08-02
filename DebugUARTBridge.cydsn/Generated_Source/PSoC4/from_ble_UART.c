/***************************************************************************//**
* \file from_ble_UART.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
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

#include "from_ble_PVT.h"
#include "from_ble_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (from_ble_UART_WAKE_ENABLE_CONST && from_ble_UART_RX_WAKEUP_IRQ)
    /**
    * \addtogroup group_globals
    * \{
    */
    /** This global variable determines whether to enable Skip Start
    * functionality when from_ble_Sleep() function is called:
    * 0 – disable, other values – enable. Default value is 1.
    * It is only available when Enable wakeup from Deep Sleep Mode is enabled.
    */
    uint8 from_ble_skipStart = 1u;
    /** \} globals */
#endif /* (from_ble_UART_WAKE_ENABLE_CONST && from_ble_UART_RX_WAKEUP_IRQ) */

#if(from_ble_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const from_ble_UART_INIT_STRUCT from_ble_configUart =
    {
        from_ble_UART_SUB_MODE,
        from_ble_UART_DIRECTION,
        from_ble_UART_DATA_BITS_NUM,
        from_ble_UART_PARITY_TYPE,
        from_ble_UART_STOP_BITS_NUM,
        from_ble_UART_OVS_FACTOR,
        from_ble_UART_IRDA_LOW_POWER,
        from_ble_UART_MEDIAN_FILTER_ENABLE,
        from_ble_UART_RETRY_ON_NACK,
        from_ble_UART_IRDA_POLARITY,
        from_ble_UART_DROP_ON_PARITY_ERR,
        from_ble_UART_DROP_ON_FRAME_ERR,
        from_ble_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        from_ble_UART_MP_MODE_ENABLE,
        from_ble_UART_MP_ACCEPT_ADDRESS,
        from_ble_UART_MP_RX_ADDRESS,
        from_ble_UART_MP_RX_ADDRESS_MASK,
        (uint32) from_ble_SCB_IRQ_INTERNAL,
        from_ble_UART_INTR_RX_MASK,
        from_ble_UART_RX_TRIGGER_LEVEL,
        from_ble_UART_INTR_TX_MASK,
        from_ble_UART_TX_TRIGGER_LEVEL,
        (uint8) from_ble_UART_BYTE_MODE_ENABLE,
        (uint8) from_ble_UART_CTS_ENABLE,
        (uint8) from_ble_UART_CTS_POLARITY,
        (uint8) from_ble_UART_RTS_POLARITY,
        (uint8) from_ble_UART_RTS_FIFO_LEVEL,
        (uint8) from_ble_UART_RX_BREAK_WIDTH
    };


    /*******************************************************************************
    * Function Name: from_ble_UartInit
    ****************************************************************************//**
    *
    *  Configures the from_ble for UART operation.
    *
    *  This function is intended specifically to be used when the from_ble
    *  configuration is set to “Unconfigured from_ble” in the customizer.
    *  After initializing the from_ble in UART mode using this function,
    *  the component can be enabled using the from_ble_Start() or
    * from_ble_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration
    *  settings. This structure contains the same information that would otherwise
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of
    *   fields. These fields match the selections available in the customizer.
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void from_ble_UartInit(const from_ble_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (from_ble_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (from_ble_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1) */

            /* Configure pins */
            from_ble_SetPins(from_ble_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            from_ble_scbMode       = (uint8) from_ble_SCB_MODE_UART;
            from_ble_scbEnableWake = (uint8) config->enableWake;
            from_ble_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            from_ble_rxBuffer      =         config->rxBuffer;
            from_ble_rxDataBits    = (uint8) config->dataBits;
            from_ble_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            from_ble_txBuffer      =         config->txBuffer;
            from_ble_txDataBits    = (uint8) config->dataBits;
            from_ble_txBufferSize  =         config->txBufferSize;

            /* Configure UART interface */
            if(from_ble_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                from_ble_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (from_ble_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (from_ble_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                from_ble_CTRL_REG  = from_ble_GET_CTRL_OVS(config->oversample);
            }

            from_ble_CTRL_REG     |= from_ble_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             from_ble_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             from_ble_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            from_ble_UART_CTRL_REG = from_ble_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            from_ble_UART_RX_CTRL_REG = from_ble_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        from_ble_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        from_ble_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        from_ble_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        from_ble_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr)   |
                                        from_ble_GET_UART_RX_CTRL_BREAK_WIDTH(config->breakWidth);

            if(from_ble_UART_PARITY_NONE != config->parity)
            {
               from_ble_UART_RX_CTRL_REG |= from_ble_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    from_ble_UART_RX_CTRL_PARITY_ENABLED;
            }

            from_ble_RX_CTRL_REG      = from_ble_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                from_ble_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                from_ble_GET_UART_RX_CTRL_ENABLED(config->direction);

            from_ble_RX_FIFO_CTRL_REG = from_ble_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            from_ble_RX_MATCH_REG     = from_ble_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                from_ble_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            from_ble_UART_TX_CTRL_REG = from_ble_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                from_ble_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(from_ble_UART_PARITY_NONE != config->parity)
            {
               from_ble_UART_TX_CTRL_REG |= from_ble_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    from_ble_UART_TX_CTRL_PARITY_ENABLED;
            }

            from_ble_TX_CTRL_REG      = from_ble_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                from_ble_GET_UART_TX_CTRL_ENABLED(config->direction);

            from_ble_TX_FIFO_CTRL_REG = from_ble_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1)
            from_ble_UART_FLOW_CTRL_REG = from_ble_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            from_ble_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            from_ble_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            from_ble_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (from_ble_ISR_NUMBER);
            CyIntSetPriority(from_ble_ISR_NUMBER, from_ble_ISR_PRIORITY);
            (void) CyIntSetVector(from_ble_ISR_NUMBER, &from_ble_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(from_ble_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (from_ble_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(from_ble_RX_WAKE_ISR_NUMBER, from_ble_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(from_ble_RX_WAKE_ISR_NUMBER, &from_ble_UART_WAKEUP_ISR);
        #endif /* (from_ble_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            from_ble_INTR_I2C_EC_MASK_REG = from_ble_NO_INTR_SOURCES;
            from_ble_INTR_SPI_EC_MASK_REG = from_ble_NO_INTR_SOURCES;
            from_ble_INTR_SLAVE_MASK_REG  = from_ble_NO_INTR_SOURCES;
            from_ble_INTR_MASTER_MASK_REG = from_ble_NO_INTR_SOURCES;
            from_ble_INTR_RX_MASK_REG     = config->rxInterruptMask;
            from_ble_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Configure TX interrupt sources to restore. */
            from_ble_IntrTxMask = LO16(from_ble_INTR_TX_MASK_REG);

            /* Clear RX buffer indexes */
            from_ble_rxBufferHead     = 0u;
            from_ble_rxBufferTail     = 0u;
            from_ble_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            from_ble_txBufferHead = 0u;
            from_ble_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: from_ble_UartInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the UART operation.
    *
    *******************************************************************************/
    void from_ble_UartInit(void)
    {
        /* Configure UART interface */
        from_ble_CTRL_REG = from_ble_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        from_ble_UART_CTRL_REG = from_ble_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        from_ble_UART_RX_CTRL_REG = from_ble_UART_DEFAULT_UART_RX_CTRL;
        from_ble_RX_CTRL_REG      = from_ble_UART_DEFAULT_RX_CTRL;
        from_ble_RX_FIFO_CTRL_REG = from_ble_UART_DEFAULT_RX_FIFO_CTRL;
        from_ble_RX_MATCH_REG     = from_ble_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        from_ble_UART_TX_CTRL_REG = from_ble_UART_DEFAULT_UART_TX_CTRL;
        from_ble_TX_CTRL_REG      = from_ble_UART_DEFAULT_TX_CTRL;
        from_ble_TX_FIFO_CTRL_REG = from_ble_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1)
        from_ble_UART_FLOW_CTRL_REG = from_ble_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(from_ble_SCB_IRQ_INTERNAL)
        CyIntDisable    (from_ble_ISR_NUMBER);
        CyIntSetPriority(from_ble_ISR_NUMBER, from_ble_ISR_PRIORITY);
        (void) CyIntSetVector(from_ble_ISR_NUMBER, &from_ble_SPI_UART_ISR);
    #endif /* (from_ble_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(from_ble_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (from_ble_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(from_ble_RX_WAKE_ISR_NUMBER, from_ble_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(from_ble_RX_WAKE_ISR_NUMBER, &from_ble_UART_WAKEUP_ISR);
    #endif /* (from_ble_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        from_ble_INTR_I2C_EC_MASK_REG = from_ble_UART_DEFAULT_INTR_I2C_EC_MASK;
        from_ble_INTR_SPI_EC_MASK_REG = from_ble_UART_DEFAULT_INTR_SPI_EC_MASK;
        from_ble_INTR_SLAVE_MASK_REG  = from_ble_UART_DEFAULT_INTR_SLAVE_MASK;
        from_ble_INTR_MASTER_MASK_REG = from_ble_UART_DEFAULT_INTR_MASTER_MASK;
        from_ble_INTR_RX_MASK_REG     = from_ble_UART_DEFAULT_INTR_RX_MASK;
        from_ble_INTR_TX_MASK_REG     = from_ble_UART_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        from_ble_IntrTxMask = LO16(from_ble_INTR_TX_MASK_REG);

    #if(from_ble_INTERNAL_RX_SW_BUFFER_CONST)
        from_ble_rxBufferHead     = 0u;
        from_ble_rxBufferTail     = 0u;
        from_ble_rxBufferOverflow = 0u;
    #endif /* (from_ble_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(from_ble_INTERNAL_TX_SW_BUFFER_CONST)
        from_ble_txBufferHead = 0u;
        from_ble_txBufferTail = 0u;
    #endif /* (from_ble_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: from_ble_UartPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be
*  controlled by the SCB UART.
*
*******************************************************************************/
void from_ble_UartPostEnable(void)
{
#if (from_ble_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (from_ble_TX_SDA_MISO_PIN)
        if (from_ble_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set SCB UART to drive the output pin */
            from_ble_SET_HSIOM_SEL(from_ble_TX_SDA_MISO_HSIOM_REG, from_ble_TX_SDA_MISO_HSIOM_MASK,
                                           from_ble_TX_SDA_MISO_HSIOM_POS, from_ble_TX_SDA_MISO_HSIOM_SEL_UART);
        }
    #endif /* (from_ble_TX_SDA_MISO_PIN_PIN) */

    #if !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1)
        #if (from_ble_RTS_SS0_PIN)
            if (from_ble_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set SCB UART to drive the output pin */
                from_ble_SET_HSIOM_SEL(from_ble_RTS_SS0_HSIOM_REG, from_ble_RTS_SS0_HSIOM_MASK,
                                               from_ble_RTS_SS0_HSIOM_POS, from_ble_RTS_SS0_HSIOM_SEL_UART);
            }
        #endif /* (from_ble_RTS_SS0_PIN) */
    #endif /* !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1) */

#else
    #if (from_ble_UART_TX_PIN)
         /* Set SCB UART to drive the output pin */
        from_ble_SET_HSIOM_SEL(from_ble_TX_HSIOM_REG, from_ble_TX_HSIOM_MASK,
                                       from_ble_TX_HSIOM_POS, from_ble_TX_HSIOM_SEL_UART);
    #endif /* (from_ble_UART_TX_PIN) */

    #if (from_ble_UART_RTS_PIN)
        /* Set SCB UART to drive the output pin */
        from_ble_SET_HSIOM_SEL(from_ble_RTS_HSIOM_REG, from_ble_RTS_HSIOM_MASK,
                                       from_ble_RTS_HSIOM_POS, from_ble_RTS_HSIOM_SEL_UART);
    #endif /* (from_ble_UART_RTS_PIN) */
#endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    from_ble_SetTxInterruptMode(from_ble_IntrTxMask);
}


/*******************************************************************************
* Function Name: from_ble_UartStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature
*  to not cause it to trigger after the component is enabled.
*
*******************************************************************************/
void from_ble_UartStop(void)
{
#if(from_ble_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (from_ble_TX_SDA_MISO_PIN)
        if (from_ble_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            from_ble_SET_HSIOM_SEL(from_ble_TX_SDA_MISO_HSIOM_REG, from_ble_TX_SDA_MISO_HSIOM_MASK,
                                           from_ble_TX_SDA_MISO_HSIOM_POS, from_ble_TX_SDA_MISO_HSIOM_SEL_GPIO);
        }
    #endif /* (from_ble_TX_SDA_MISO_PIN_PIN) */

    #if !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1)
        #if (from_ble_RTS_SS0_PIN)
            if (from_ble_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set output pin state after block is disabled */
                from_ble_uart_rts_spi_ss0_Write(from_ble_GET_UART_RTS_INACTIVE);

                /* Set GPIO to drive output pin */
                from_ble_SET_HSIOM_SEL(from_ble_RTS_SS0_HSIOM_REG, from_ble_RTS_SS0_HSIOM_MASK,
                                               from_ble_RTS_SS0_HSIOM_POS, from_ble_RTS_SS0_HSIOM_SEL_GPIO);
            }
        #endif /* (from_ble_RTS_SS0_PIN) */
    #endif /* !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1) */

#else
    #if (from_ble_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        from_ble_SET_HSIOM_SEL(from_ble_TX_HSIOM_REG, from_ble_TX_HSIOM_MASK,
                                       from_ble_TX_HSIOM_POS, from_ble_TX_HSIOM_SEL_GPIO);
    #endif /* (from_ble_UART_TX_PIN) */

    #if (from_ble_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        from_ble_rts_Write(from_ble_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        from_ble_SET_HSIOM_SEL(from_ble_RTS_HSIOM_REG, from_ble_RTS_HSIOM_MASK,
                                       from_ble_RTS_HSIOM_POS, from_ble_RTS_HSIOM_SEL_GPIO);
    #endif /* (from_ble_UART_RTS_PIN) */

#endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (from_ble_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    from_ble_UART_RX_CTRL_REG &= (uint32) ~from_ble_UART_RX_CTRL_SKIP_START;
#endif /* (from_ble_UART_WAKE_ENABLE_CONST) */

    /* Store TX interrupt sources (exclude level triggered). */
    from_ble_IntrTxMask = LO16(from_ble_GetTxInterruptMode() & from_ble_INTR_UART_TX_RESTORE);
}


/*******************************************************************************
* Function Name: from_ble_UartSetRxAddress
****************************************************************************//**
*
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
*  \param address: Address for hardware address detection.
*
*******************************************************************************/
void from_ble_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = from_ble_RX_MATCH_REG;

    matchReg &= ((uint32) ~from_ble_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & from_ble_RX_MATCH_ADDR_MASK)); /* Set address  */

    from_ble_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: from_ble_UartSetRxAddressMask
****************************************************************************//**
*
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
*  \param addressMask: Address mask.
*   - Bit value 0 – excludes bit from address comparison.
*   - Bit value 1 – the bit needs to match with the corresponding bit
*     of the address.
*
*******************************************************************************/
void from_ble_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = from_ble_RX_MATCH_REG;

    matchReg &= ((uint32) ~from_ble_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << from_ble_RX_MATCH_MASK_POS));

    from_ble_RX_MATCH_REG = matchReg;
}


#if(from_ble_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: from_ble_UartGetChar
    ****************************************************************************//**
    *
    *  Retrieves next data element from receive buffer.
    *  This function is designed for ASCII characters and returns a char where
    *  1 to 255 are valid characters and 0 indicates an error occurred or no data
    *  is present.
    *  - RX software buffer is disabled: Returns data element retrieved from RX
    *    FIFO.
    *  - RX software buffer is enabled: Returns data element from the software
    *    receive buffer.
    *
    *  \return
    *   Next data element from the receive buffer. ASCII character values from
    *   1 to 255 are valid. A returned zero signifies an error condition or no
    *   data available.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check from_ble_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 from_ble_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != from_ble_SpiUartGetRxBufferSize())
        {
            rxData = from_ble_SpiUartReadRxData();
        }

        if (from_ble_CHECK_INTR_RX(from_ble_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            from_ble_ClearRxInterruptSource(from_ble_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: from_ble_UartGetByte
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    *  \return
    *   Bits 7-0 contain the next data element from the receive buffer and
    *   other bits contain the error condition.
    *   - from_ble_UART_RX_OVERFLOW - Attempt to write to a full
    *     receiver FIFO.
    *   - from_ble_UART_RX_UNDERFLOW    Attempt to read from an empty
    *     receiver FIFO.
    *   - from_ble_UART_RX_FRAME_ERROR - UART framing error detected.
    *   - from_ble_UART_RX_PARITY_ERROR - UART parity error detected.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check from_ble_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 from_ble_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (from_ble_CHECK_RX_SW_BUFFER)
        {
            from_ble_DisableInt();
        }
        #endif

        if (0u != from_ble_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (from_ble_CHECK_RX_SW_BUFFER)
            {
                from_ble_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = from_ble_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the
            * case of empty. Otherwise the first received byte will be read.
            */
            rxData = from_ble_RX_FIFO_RD_REG;


            /* Enables interrupt to receive more bytes. */
            #if (from_ble_CHECK_RX_SW_BUFFER)
            {

                /* The byte has been read from RX FIFO. Clear RX interrupt to
                * not involve interrupt handler when RX FIFO is empty.
                */
                from_ble_ClearRxInterruptSource(from_ble_INTR_RX_NOT_EMPTY);

                from_ble_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (from_ble_GetRxInterruptSource() & from_ble_INTR_RX_ERR);
        from_ble_ClearRxInterruptSource(from_ble_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: from_ble_UartSetRtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of RTS output signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of RTS output signal.
        *   - from_ble_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   - from_ble_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        *******************************************************************************/
        void from_ble_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                from_ble_UART_FLOW_CTRL_REG |= (uint32)  from_ble_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                from_ble_UART_FLOW_CTRL_REG &= (uint32) ~from_ble_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: from_ble_UartSetRtsFifoLevel
        ****************************************************************************//**
        *
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param level: Level in the RX FIFO for RTS signal activation.
        *   The range of valid level values is between 0 and RX FIFO depth - 1.
        *   Setting level value to 0 disables RTS signal activation.
        *
        *******************************************************************************/
        void from_ble_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = from_ble_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~from_ble_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (from_ble_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            from_ble_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1) */

#endif /* (from_ble_UART_RX_DIRECTION) */


#if(from_ble_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: from_ble_UartPutString
    ****************************************************************************//**
    *
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is a space available to put
    *  requested data in transmit buffer.
    *
    *  \param string: pointer to the null terminated string array to be placed in the
    *   transmit buffer.
    *
    *******************************************************************************/
    void from_ble_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            from_ble_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: from_ble_UartPutCRLF
    ****************************************************************************//**
    *
    *  Places byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) in the transmit buffer.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *
    *******************************************************************************/
    void from_ble_UartPutCRLF(uint32 txDataByte)
    {
        from_ble_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        from_ble_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        from_ble_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: from_bleSCB_UartEnableCts
        ****************************************************************************//**
        *
        *  Enables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void from_ble_UartEnableCts(void)
        {
            from_ble_UART_FLOW_CTRL_REG |= (uint32)  from_ble_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: from_ble_UartDisableCts
        ****************************************************************************//**
        *
        *  Disables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void from_ble_UartDisableCts(void)
        {
            from_ble_UART_FLOW_CTRL_REG &= (uint32) ~from_ble_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: from_ble_UartSetCtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of CTS input signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        * \param
        * polarity: Active polarity of CTS output signal.
        *   - from_ble_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   - from_ble_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        *******************************************************************************/
        void from_ble_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                from_ble_UART_FLOW_CTRL_REG |= (uint32)  from_ble_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                from_ble_UART_FLOW_CTRL_REG &= (uint32) ~from_ble_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1) */


    /*******************************************************************************
    * Function Name: from_ble_UartSendBreakBlocking
    ****************************************************************************//**
    *
    * Sends a break condition (logic low) of specified width on UART TX line.
    * Blocks until break is completed. Only call this function when UART TX FIFO
    * and shifter are empty.
    *
    * \param breakWidth
    * Width of break condition. Valid range is 4 to 16 bits.
    *
    * \note
    * Before sending break all UART TX interrupt sources are disabled. The state
    * of UART TX interrupt sources is restored before function returns.
    *
    * \sideeffect
    * If this function is called while there is data in the TX FIFO or shifter that
    * data will be shifted out in packets the size of breakWidth.
    *
    *******************************************************************************/
    void from_ble_UartSendBreakBlocking(uint32 breakWidth)
    {
        uint32 txCtrlReg;
        uint32 txIntrReg;

        /* Disable all UART TX interrupt source and clear UART TX Done history */
        txIntrReg = from_ble_GetTxInterruptMode();
        from_ble_SetTxInterruptMode(0u);
        from_ble_ClearTxInterruptSource(from_ble_INTR_TX_UART_DONE);

        /* Store TX CTRL configuration */
        txCtrlReg = from_ble_TX_CTRL_REG;

        /* Set break width */
        from_ble_TX_CTRL_REG = (from_ble_TX_CTRL_REG & (uint32) ~from_ble_TX_CTRL_DATA_WIDTH_MASK) |
                                        from_ble_GET_TX_CTRL_DATA_WIDTH(breakWidth);

        /* Generate break */
        from_ble_TX_FIFO_WR_REG = 0u;

        /* Wait for break completion */
        while (0u == (from_ble_GetTxInterruptSource() & from_ble_INTR_TX_UART_DONE))
        {
        }

        /* Clear all UART TX interrupt sources to  */
        from_ble_ClearTxInterruptSource(from_ble_INTR_TX_ALL);

        /* Restore TX interrupt sources and data width */
        from_ble_TX_CTRL_REG = txCtrlReg;
        from_ble_SetTxInterruptMode(txIntrReg);
    }
#endif /* (from_ble_UART_TX_DIRECTION) */


#if (from_ble_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: from_ble_UartSaveConfig
    ****************************************************************************//**
    *
    *  Clears and enables an interrupt on a falling edge of the Rx input. The GPIO
    *  interrupt does not track in the active mode, therefore requires to be
    *  cleared by this API.
    *
    *******************************************************************************/
    void from_ble_UartSaveConfig(void)
    {
    #if (from_ble_UART_RX_WAKEUP_IRQ)
        /* Set SKIP_START if requested (set by default). */
        if (0u != from_ble_skipStart)
        {
            from_ble_UART_RX_CTRL_REG |= (uint32)  from_ble_UART_RX_CTRL_SKIP_START;
        }
        else
        {
            from_ble_UART_RX_CTRL_REG &= (uint32) ~from_ble_UART_RX_CTRL_SKIP_START;
        }

        /* Clear RX GPIO interrupt status and pending interrupt in NVIC because
        * falling edge on RX line occurs while UART communication in active mode.
        * Enable interrupt: next interrupt trigger should wakeup device.
        */
        from_ble_CLEAR_UART_RX_WAKE_INTR;
        from_ble_RxWakeClearPendingInt();
        from_ble_RxWakeEnableInt();
    #endif /* (from_ble_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: from_ble_UartRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    *******************************************************************************/
    void from_ble_UartRestoreConfig(void)
    {
    #if (from_ble_UART_RX_WAKEUP_IRQ)
        /* Disable interrupt: no more triggers in active mode */
        from_ble_RxWakeDisableInt();
    #endif /* (from_ble_UART_RX_WAKEUP_IRQ) */
    }


    #if (from_ble_UART_RX_WAKEUP_IRQ)
        /*******************************************************************************
        * Function Name: from_ble_UART_WAKEUP_ISR
        ****************************************************************************//**
        *
        *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
        *  event. This event is configured to trigger on a falling edge of the RX line.
        *
        *******************************************************************************/
        CY_ISR(from_ble_UART_WAKEUP_ISR)
        {
        #ifdef from_ble_UART_WAKEUP_ISR_ENTRY_CALLBACK
            from_ble_UART_WAKEUP_ISR_EntryCallback();
        #endif /* from_ble_UART_WAKEUP_ISR_ENTRY_CALLBACK */

            from_ble_CLEAR_UART_RX_WAKE_INTR;

        #ifdef from_ble_UART_WAKEUP_ISR_EXIT_CALLBACK
            from_ble_UART_WAKEUP_ISR_ExitCallback();
        #endif /* from_ble_UART_WAKEUP_ISR_EXIT_CALLBACK */
        }
    #endif /* (from_ble_UART_RX_WAKEUP_IRQ) */
#endif /* (from_ble_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
