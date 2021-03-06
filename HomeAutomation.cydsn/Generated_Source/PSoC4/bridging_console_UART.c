/***************************************************************************//**
* \file bridging_console_UART.c
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

#include "bridging_console_PVT.h"
#include "bridging_console_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (bridging_console_UART_WAKE_ENABLE_CONST && bridging_console_UART_RX_WAKEUP_IRQ)
    /**
    * \addtogroup group_globals
    * \{
    */
    /** This global variable determines whether to enable Skip Start
    * functionality when bridging_console_Sleep() function is called:
    * 0 – disable, other values – enable. Default value is 1.
    * It is only available when Enable wakeup from Deep Sleep Mode is enabled.
    */
    uint8 bridging_console_skipStart = 1u;
    /** \} globals */
#endif /* (bridging_console_UART_WAKE_ENABLE_CONST && bridging_console_UART_RX_WAKEUP_IRQ) */

#if(bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const bridging_console_UART_INIT_STRUCT bridging_console_configUart =
    {
        bridging_console_UART_SUB_MODE,
        bridging_console_UART_DIRECTION,
        bridging_console_UART_DATA_BITS_NUM,
        bridging_console_UART_PARITY_TYPE,
        bridging_console_UART_STOP_BITS_NUM,
        bridging_console_UART_OVS_FACTOR,
        bridging_console_UART_IRDA_LOW_POWER,
        bridging_console_UART_MEDIAN_FILTER_ENABLE,
        bridging_console_UART_RETRY_ON_NACK,
        bridging_console_UART_IRDA_POLARITY,
        bridging_console_UART_DROP_ON_PARITY_ERR,
        bridging_console_UART_DROP_ON_FRAME_ERR,
        bridging_console_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        bridging_console_UART_MP_MODE_ENABLE,
        bridging_console_UART_MP_ACCEPT_ADDRESS,
        bridging_console_UART_MP_RX_ADDRESS,
        bridging_console_UART_MP_RX_ADDRESS_MASK,
        (uint32) bridging_console_SCB_IRQ_INTERNAL,
        bridging_console_UART_INTR_RX_MASK,
        bridging_console_UART_RX_TRIGGER_LEVEL,
        bridging_console_UART_INTR_TX_MASK,
        bridging_console_UART_TX_TRIGGER_LEVEL,
        (uint8) bridging_console_UART_BYTE_MODE_ENABLE,
        (uint8) bridging_console_UART_CTS_ENABLE,
        (uint8) bridging_console_UART_CTS_POLARITY,
        (uint8) bridging_console_UART_RTS_POLARITY,
        (uint8) bridging_console_UART_RTS_FIFO_LEVEL,
        (uint8) bridging_console_UART_RX_BREAK_WIDTH
    };


    /*******************************************************************************
    * Function Name: bridging_console_UartInit
    ****************************************************************************//**
    *
    *  Configures the bridging_console for UART operation.
    *
    *  This function is intended specifically to be used when the bridging_console
    *  configuration is set to “Unconfigured bridging_console” in the customizer.
    *  After initializing the bridging_console in UART mode using this function,
    *  the component can be enabled using the bridging_console_Start() or
    * bridging_console_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration
    *  settings. This structure contains the same information that would otherwise
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of
    *   fields. These fields match the selections available in the customizer.
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void bridging_console_UartInit(const bridging_console_UART_INIT_STRUCT *config)
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

        #if !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (bridging_console_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (bridging_console_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1) */

            /* Configure pins */
            bridging_console_SetPins(bridging_console_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            bridging_console_scbMode       = (uint8) bridging_console_SCB_MODE_UART;
            bridging_console_scbEnableWake = (uint8) config->enableWake;
            bridging_console_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            bridging_console_rxBuffer      =         config->rxBuffer;
            bridging_console_rxDataBits    = (uint8) config->dataBits;
            bridging_console_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            bridging_console_txBuffer      =         config->txBuffer;
            bridging_console_txDataBits    = (uint8) config->dataBits;
            bridging_console_txBufferSize  =         config->txBufferSize;

            /* Configure UART interface */
            if(bridging_console_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                bridging_console_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (bridging_console_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (bridging_console_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                bridging_console_CTRL_REG  = bridging_console_GET_CTRL_OVS(config->oversample);
            }

            bridging_console_CTRL_REG     |= bridging_console_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             bridging_console_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             bridging_console_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            bridging_console_UART_CTRL_REG = bridging_console_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            bridging_console_UART_RX_CTRL_REG = bridging_console_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        bridging_console_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        bridging_console_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        bridging_console_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        bridging_console_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr)   |
                                        bridging_console_GET_UART_RX_CTRL_BREAK_WIDTH(config->breakWidth);

            if(bridging_console_UART_PARITY_NONE != config->parity)
            {
               bridging_console_UART_RX_CTRL_REG |= bridging_console_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    bridging_console_UART_RX_CTRL_PARITY_ENABLED;
            }

            bridging_console_RX_CTRL_REG      = bridging_console_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                bridging_console_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                bridging_console_GET_UART_RX_CTRL_ENABLED(config->direction);

            bridging_console_RX_FIFO_CTRL_REG = bridging_console_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            bridging_console_RX_MATCH_REG     = bridging_console_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                bridging_console_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            bridging_console_UART_TX_CTRL_REG = bridging_console_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                bridging_console_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(bridging_console_UART_PARITY_NONE != config->parity)
            {
               bridging_console_UART_TX_CTRL_REG |= bridging_console_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    bridging_console_UART_TX_CTRL_PARITY_ENABLED;
            }

            bridging_console_TX_CTRL_REG      = bridging_console_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                bridging_console_GET_UART_TX_CTRL_ENABLED(config->direction);

            bridging_console_TX_FIFO_CTRL_REG = bridging_console_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1)
            bridging_console_UART_FLOW_CTRL_REG = bridging_console_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            bridging_console_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            bridging_console_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            bridging_console_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (bridging_console_ISR_NUMBER);
            CyIntSetPriority(bridging_console_ISR_NUMBER, bridging_console_ISR_PRIORITY);
            (void) CyIntSetVector(bridging_console_ISR_NUMBER, &bridging_console_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(bridging_console_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (bridging_console_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(bridging_console_RX_WAKE_ISR_NUMBER, bridging_console_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(bridging_console_RX_WAKE_ISR_NUMBER, &bridging_console_UART_WAKEUP_ISR);
        #endif /* (bridging_console_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            bridging_console_INTR_I2C_EC_MASK_REG = bridging_console_NO_INTR_SOURCES;
            bridging_console_INTR_SPI_EC_MASK_REG = bridging_console_NO_INTR_SOURCES;
            bridging_console_INTR_SLAVE_MASK_REG  = bridging_console_NO_INTR_SOURCES;
            bridging_console_INTR_MASTER_MASK_REG = bridging_console_NO_INTR_SOURCES;
            bridging_console_INTR_RX_MASK_REG     = config->rxInterruptMask;
            bridging_console_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Configure TX interrupt sources to restore. */
            bridging_console_IntrTxMask = LO16(bridging_console_INTR_TX_MASK_REG);

            /* Clear RX buffer indexes */
            bridging_console_rxBufferHead     = 0u;
            bridging_console_rxBufferTail     = 0u;
            bridging_console_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            bridging_console_txBufferHead = 0u;
            bridging_console_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: bridging_console_UartInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the UART operation.
    *
    *******************************************************************************/
    void bridging_console_UartInit(void)
    {
        /* Configure UART interface */
        bridging_console_CTRL_REG = bridging_console_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        bridging_console_UART_CTRL_REG = bridging_console_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        bridging_console_UART_RX_CTRL_REG = bridging_console_UART_DEFAULT_UART_RX_CTRL;
        bridging_console_RX_CTRL_REG      = bridging_console_UART_DEFAULT_RX_CTRL;
        bridging_console_RX_FIFO_CTRL_REG = bridging_console_UART_DEFAULT_RX_FIFO_CTRL;
        bridging_console_RX_MATCH_REG     = bridging_console_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        bridging_console_UART_TX_CTRL_REG = bridging_console_UART_DEFAULT_UART_TX_CTRL;
        bridging_console_TX_CTRL_REG      = bridging_console_UART_DEFAULT_TX_CTRL;
        bridging_console_TX_FIFO_CTRL_REG = bridging_console_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1)
        bridging_console_UART_FLOW_CTRL_REG = bridging_console_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(bridging_console_SCB_IRQ_INTERNAL)
        CyIntDisable    (bridging_console_ISR_NUMBER);
        CyIntSetPriority(bridging_console_ISR_NUMBER, bridging_console_ISR_PRIORITY);
        (void) CyIntSetVector(bridging_console_ISR_NUMBER, &bridging_console_SPI_UART_ISR);
    #endif /* (bridging_console_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(bridging_console_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (bridging_console_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(bridging_console_RX_WAKE_ISR_NUMBER, bridging_console_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(bridging_console_RX_WAKE_ISR_NUMBER, &bridging_console_UART_WAKEUP_ISR);
    #endif /* (bridging_console_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        bridging_console_INTR_I2C_EC_MASK_REG = bridging_console_UART_DEFAULT_INTR_I2C_EC_MASK;
        bridging_console_INTR_SPI_EC_MASK_REG = bridging_console_UART_DEFAULT_INTR_SPI_EC_MASK;
        bridging_console_INTR_SLAVE_MASK_REG  = bridging_console_UART_DEFAULT_INTR_SLAVE_MASK;
        bridging_console_INTR_MASTER_MASK_REG = bridging_console_UART_DEFAULT_INTR_MASTER_MASK;
        bridging_console_INTR_RX_MASK_REG     = bridging_console_UART_DEFAULT_INTR_RX_MASK;
        bridging_console_INTR_TX_MASK_REG     = bridging_console_UART_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        bridging_console_IntrTxMask = LO16(bridging_console_INTR_TX_MASK_REG);

    #if(bridging_console_INTERNAL_RX_SW_BUFFER_CONST)
        bridging_console_rxBufferHead     = 0u;
        bridging_console_rxBufferTail     = 0u;
        bridging_console_rxBufferOverflow = 0u;
    #endif /* (bridging_console_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(bridging_console_INTERNAL_TX_SW_BUFFER_CONST)
        bridging_console_txBufferHead = 0u;
        bridging_console_txBufferTail = 0u;
    #endif /* (bridging_console_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: bridging_console_UartPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be
*  controlled by the SCB UART.
*
*******************************************************************************/
void bridging_console_UartPostEnable(void)
{
#if (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (bridging_console_TX_SDA_MISO_PIN)
        if (bridging_console_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set SCB UART to drive the output pin */
            bridging_console_SET_HSIOM_SEL(bridging_console_TX_SDA_MISO_HSIOM_REG, bridging_console_TX_SDA_MISO_HSIOM_MASK,
                                           bridging_console_TX_SDA_MISO_HSIOM_POS, bridging_console_TX_SDA_MISO_HSIOM_SEL_UART);
        }
    #endif /* (bridging_console_TX_SDA_MISO_PIN_PIN) */

    #if !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1)
        #if (bridging_console_RTS_SS0_PIN)
            if (bridging_console_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set SCB UART to drive the output pin */
                bridging_console_SET_HSIOM_SEL(bridging_console_RTS_SS0_HSIOM_REG, bridging_console_RTS_SS0_HSIOM_MASK,
                                               bridging_console_RTS_SS0_HSIOM_POS, bridging_console_RTS_SS0_HSIOM_SEL_UART);
            }
        #endif /* (bridging_console_RTS_SS0_PIN) */
    #endif /* !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1) */

#else
    #if (bridging_console_UART_TX_PIN)
         /* Set SCB UART to drive the output pin */
        bridging_console_SET_HSIOM_SEL(bridging_console_TX_HSIOM_REG, bridging_console_TX_HSIOM_MASK,
                                       bridging_console_TX_HSIOM_POS, bridging_console_TX_HSIOM_SEL_UART);
    #endif /* (bridging_console_UART_TX_PIN) */

    #if (bridging_console_UART_RTS_PIN)
        /* Set SCB UART to drive the output pin */
        bridging_console_SET_HSIOM_SEL(bridging_console_RTS_HSIOM_REG, bridging_console_RTS_HSIOM_MASK,
                                       bridging_console_RTS_HSIOM_POS, bridging_console_RTS_HSIOM_SEL_UART);
    #endif /* (bridging_console_UART_RTS_PIN) */
#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    bridging_console_SetTxInterruptMode(bridging_console_IntrTxMask);
}


/*******************************************************************************
* Function Name: bridging_console_UartStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature
*  to not cause it to trigger after the component is enabled.
*
*******************************************************************************/
void bridging_console_UartStop(void)
{
#if(bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (bridging_console_TX_SDA_MISO_PIN)
        if (bridging_console_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            bridging_console_SET_HSIOM_SEL(bridging_console_TX_SDA_MISO_HSIOM_REG, bridging_console_TX_SDA_MISO_HSIOM_MASK,
                                           bridging_console_TX_SDA_MISO_HSIOM_POS, bridging_console_TX_SDA_MISO_HSIOM_SEL_GPIO);
        }
    #endif /* (bridging_console_TX_SDA_MISO_PIN_PIN) */

    #if !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1)
        #if (bridging_console_RTS_SS0_PIN)
            if (bridging_console_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set output pin state after block is disabled */
                bridging_console_uart_rts_spi_ss0_Write(bridging_console_GET_UART_RTS_INACTIVE);

                /* Set GPIO to drive output pin */
                bridging_console_SET_HSIOM_SEL(bridging_console_RTS_SS0_HSIOM_REG, bridging_console_RTS_SS0_HSIOM_MASK,
                                               bridging_console_RTS_SS0_HSIOM_POS, bridging_console_RTS_SS0_HSIOM_SEL_GPIO);
            }
        #endif /* (bridging_console_RTS_SS0_PIN) */
    #endif /* !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1) */

#else
    #if (bridging_console_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        bridging_console_SET_HSIOM_SEL(bridging_console_TX_HSIOM_REG, bridging_console_TX_HSIOM_MASK,
                                       bridging_console_TX_HSIOM_POS, bridging_console_TX_HSIOM_SEL_GPIO);
    #endif /* (bridging_console_UART_TX_PIN) */

    #if (bridging_console_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        bridging_console_rts_Write(bridging_console_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        bridging_console_SET_HSIOM_SEL(bridging_console_RTS_HSIOM_REG, bridging_console_RTS_HSIOM_MASK,
                                       bridging_console_RTS_HSIOM_POS, bridging_console_RTS_HSIOM_SEL_GPIO);
    #endif /* (bridging_console_UART_RTS_PIN) */

#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (bridging_console_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    bridging_console_UART_RX_CTRL_REG &= (uint32) ~bridging_console_UART_RX_CTRL_SKIP_START;
#endif /* (bridging_console_UART_WAKE_ENABLE_CONST) */

    /* Store TX interrupt sources (exclude level triggered). */
    bridging_console_IntrTxMask = LO16(bridging_console_GetTxInterruptMode() & bridging_console_INTR_UART_TX_RESTORE);
}


/*******************************************************************************
* Function Name: bridging_console_UartSetRxAddress
****************************************************************************//**
*
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
*  \param address: Address for hardware address detection.
*
*******************************************************************************/
void bridging_console_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = bridging_console_RX_MATCH_REG;

    matchReg &= ((uint32) ~bridging_console_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & bridging_console_RX_MATCH_ADDR_MASK)); /* Set address  */

    bridging_console_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: bridging_console_UartSetRxAddressMask
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
void bridging_console_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = bridging_console_RX_MATCH_REG;

    matchReg &= ((uint32) ~bridging_console_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << bridging_console_RX_MATCH_MASK_POS));

    bridging_console_RX_MATCH_REG = matchReg;
}


#if(bridging_console_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: bridging_console_UartGetChar
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
    *   Check bridging_console_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 bridging_console_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != bridging_console_SpiUartGetRxBufferSize())
        {
            rxData = bridging_console_SpiUartReadRxData();
        }

        if (bridging_console_CHECK_INTR_RX(bridging_console_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            bridging_console_ClearRxInterruptSource(bridging_console_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: bridging_console_UartGetByte
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
    *   - bridging_console_UART_RX_OVERFLOW - Attempt to write to a full
    *     receiver FIFO.
    *   - bridging_console_UART_RX_UNDERFLOW    Attempt to read from an empty
    *     receiver FIFO.
    *   - bridging_console_UART_RX_FRAME_ERROR - UART framing error detected.
    *   - bridging_console_UART_RX_PARITY_ERROR - UART parity error detected.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check bridging_console_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 bridging_console_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (bridging_console_CHECK_RX_SW_BUFFER)
        {
            bridging_console_DisableInt();
        }
        #endif

        if (0u != bridging_console_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (bridging_console_CHECK_RX_SW_BUFFER)
            {
                bridging_console_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = bridging_console_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the
            * case of empty. Otherwise the first received byte will be read.
            */
            rxData = bridging_console_RX_FIFO_RD_REG;


            /* Enables interrupt to receive more bytes. */
            #if (bridging_console_CHECK_RX_SW_BUFFER)
            {

                /* The byte has been read from RX FIFO. Clear RX interrupt to
                * not involve interrupt handler when RX FIFO is empty.
                */
                bridging_console_ClearRxInterruptSource(bridging_console_INTR_RX_NOT_EMPTY);

                bridging_console_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (bridging_console_GetRxInterruptSource() & bridging_console_INTR_RX_ERR);
        bridging_console_ClearRxInterruptSource(bridging_console_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: bridging_console_UartSetRtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of RTS output signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of RTS output signal.
        *   - bridging_console_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   - bridging_console_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        *******************************************************************************/
        void bridging_console_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                bridging_console_UART_FLOW_CTRL_REG |= (uint32)  bridging_console_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                bridging_console_UART_FLOW_CTRL_REG &= (uint32) ~bridging_console_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: bridging_console_UartSetRtsFifoLevel
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
        void bridging_console_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = bridging_console_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~bridging_console_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (bridging_console_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            bridging_console_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1) */

#endif /* (bridging_console_UART_RX_DIRECTION) */


#if(bridging_console_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: bridging_console_UartPutString
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
    void bridging_console_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            bridging_console_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: bridging_console_UartPutCRLF
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
    void bridging_console_UartPutCRLF(uint32 txDataByte)
    {
        bridging_console_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        bridging_console_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        bridging_console_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: bridging_consoleSCB_UartEnableCts
        ****************************************************************************//**
        *
        *  Enables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void bridging_console_UartEnableCts(void)
        {
            bridging_console_UART_FLOW_CTRL_REG |= (uint32)  bridging_console_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: bridging_console_UartDisableCts
        ****************************************************************************//**
        *
        *  Disables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void bridging_console_UartDisableCts(void)
        {
            bridging_console_UART_FLOW_CTRL_REG &= (uint32) ~bridging_console_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: bridging_console_UartSetCtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of CTS input signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        * \param
        * polarity: Active polarity of CTS output signal.
        *   - bridging_console_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   - bridging_console_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        *******************************************************************************/
        void bridging_console_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                bridging_console_UART_FLOW_CTRL_REG |= (uint32)  bridging_console_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                bridging_console_UART_FLOW_CTRL_REG &= (uint32) ~bridging_console_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1) */


    /*******************************************************************************
    * Function Name: bridging_console_UartSendBreakBlocking
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
    void bridging_console_UartSendBreakBlocking(uint32 breakWidth)
    {
        uint32 txCtrlReg;
        uint32 txIntrReg;

        /* Disable all UART TX interrupt source and clear UART TX Done history */
        txIntrReg = bridging_console_GetTxInterruptMode();
        bridging_console_SetTxInterruptMode(0u);
        bridging_console_ClearTxInterruptSource(bridging_console_INTR_TX_UART_DONE);

        /* Store TX CTRL configuration */
        txCtrlReg = bridging_console_TX_CTRL_REG;

        /* Set break width */
        bridging_console_TX_CTRL_REG = (bridging_console_TX_CTRL_REG & (uint32) ~bridging_console_TX_CTRL_DATA_WIDTH_MASK) |
                                        bridging_console_GET_TX_CTRL_DATA_WIDTH(breakWidth);

        /* Generate break */
        bridging_console_TX_FIFO_WR_REG = 0u;

        /* Wait for break completion */
        while (0u == (bridging_console_GetTxInterruptSource() & bridging_console_INTR_TX_UART_DONE))
        {
        }

        /* Clear all UART TX interrupt sources to  */
        bridging_console_ClearTxInterruptSource(bridging_console_INTR_TX_ALL);

        /* Restore TX interrupt sources and data width */
        bridging_console_TX_CTRL_REG = txCtrlReg;
        bridging_console_SetTxInterruptMode(txIntrReg);
    }
#endif /* (bridging_console_UART_TX_DIRECTION) */


#if (bridging_console_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: bridging_console_UartSaveConfig
    ****************************************************************************//**
    *
    *  Clears and enables an interrupt on a falling edge of the Rx input. The GPIO
    *  interrupt does not track in the active mode, therefore requires to be
    *  cleared by this API.
    *
    *******************************************************************************/
    void bridging_console_UartSaveConfig(void)
    {
    #if (bridging_console_UART_RX_WAKEUP_IRQ)
        /* Set SKIP_START if requested (set by default). */
        if (0u != bridging_console_skipStart)
        {
            bridging_console_UART_RX_CTRL_REG |= (uint32)  bridging_console_UART_RX_CTRL_SKIP_START;
        }
        else
        {
            bridging_console_UART_RX_CTRL_REG &= (uint32) ~bridging_console_UART_RX_CTRL_SKIP_START;
        }

        /* Clear RX GPIO interrupt status and pending interrupt in NVIC because
        * falling edge on RX line occurs while UART communication in active mode.
        * Enable interrupt: next interrupt trigger should wakeup device.
        */
        bridging_console_CLEAR_UART_RX_WAKE_INTR;
        bridging_console_RxWakeClearPendingInt();
        bridging_console_RxWakeEnableInt();
    #endif /* (bridging_console_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: bridging_console_UartRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    *******************************************************************************/
    void bridging_console_UartRestoreConfig(void)
    {
    #if (bridging_console_UART_RX_WAKEUP_IRQ)
        /* Disable interrupt: no more triggers in active mode */
        bridging_console_RxWakeDisableInt();
    #endif /* (bridging_console_UART_RX_WAKEUP_IRQ) */
    }


    #if (bridging_console_UART_RX_WAKEUP_IRQ)
        /*******************************************************************************
        * Function Name: bridging_console_UART_WAKEUP_ISR
        ****************************************************************************//**
        *
        *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
        *  event. This event is configured to trigger on a falling edge of the RX line.
        *
        *******************************************************************************/
        CY_ISR(bridging_console_UART_WAKEUP_ISR)
        {
        #ifdef bridging_console_UART_WAKEUP_ISR_ENTRY_CALLBACK
            bridging_console_UART_WAKEUP_ISR_EntryCallback();
        #endif /* bridging_console_UART_WAKEUP_ISR_ENTRY_CALLBACK */

            bridging_console_CLEAR_UART_RX_WAKE_INTR;

        #ifdef bridging_console_UART_WAKEUP_ISR_EXIT_CALLBACK
            bridging_console_UART_WAKEUP_ISR_ExitCallback();
        #endif /* bridging_console_UART_WAKEUP_ISR_EXIT_CALLBACK */
        }
    #endif /* (bridging_console_UART_RX_WAKEUP_IRQ) */
#endif /* (bridging_console_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
