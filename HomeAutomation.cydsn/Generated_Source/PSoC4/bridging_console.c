/***************************************************************************//**
* \file bridging_console.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component.
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

#if (bridging_console_SCB_MODE_I2C_INC)
    #include "bridging_console_I2C_PVT.h"
#endif /* (bridging_console_SCB_MODE_I2C_INC) */

#if (bridging_console_SCB_MODE_EZI2C_INC)
    #include "bridging_console_EZI2C_PVT.h"
#endif /* (bridging_console_SCB_MODE_EZI2C_INC) */

#if (bridging_console_SCB_MODE_SPI_INC || bridging_console_SCB_MODE_UART_INC)
    #include "bridging_console_SPI_UART_PVT.h"
#endif /* (bridging_console_SCB_MODE_SPI_INC || bridging_console_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 bridging_console_scbMode = bridging_console_SCB_MODE_UNCONFIG;
    uint8 bridging_console_scbEnableWake;
    uint8 bridging_console_scbEnableIntr;

    /* I2C configuration variables */
    uint8 bridging_console_mode;
    uint8 bridging_console_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * bridging_console_rxBuffer;
    uint8  bridging_console_rxDataBits;
    uint32 bridging_console_rxBufferSize;

    volatile uint8 * bridging_console_txBuffer;
    uint8  bridging_console_txDataBits;
    uint32 bridging_console_txBufferSize;

    /* EZI2C configuration variables */
    uint8 bridging_console_numberOfAddr;
    uint8 bridging_console_subAddrSize;
#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** bridging_console_initVar indicates whether the bridging_console 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the bridging_console_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  bridging_console_Init() function can be called before the 
*  bridging_console_Start() or bridging_console_Enable() function.
*/
uint8 bridging_console_initVar = 0u;


#if (! (bridging_console_SCB_MODE_I2C_CONST_CFG || \
        bridging_console_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * bridging_console_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent bridging_console_Enable() call.
    */
    uint16 bridging_console_IntrTxMask = 0u;
#endif /* (! (bridging_console_SCB_MODE_I2C_CONST_CFG || \
              bridging_console_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (bridging_console_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_bridging_console_CUSTOM_INTR_HANDLER)
    void (*bridging_console_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_bridging_console_CUSTOM_INTR_HANDLER) */
#endif /* (bridging_console_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void bridging_console_ScbEnableIntr(void);
static void bridging_console_ScbModeStop(void);
static void bridging_console_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: bridging_console_Init
****************************************************************************//**
*
*  Initializes the bridging_console component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  bridging_console_I2CInit, bridging_console_SpiInit, 
*  bridging_console_UartInit or bridging_console_EzI2CInit.
*
*******************************************************************************/
void bridging_console_Init(void)
{
#if (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
    if (bridging_console_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        bridging_console_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (bridging_console_SCB_MODE_I2C_CONST_CFG)
    bridging_console_I2CInit();

#elif (bridging_console_SCB_MODE_SPI_CONST_CFG)
    bridging_console_SpiInit();

#elif (bridging_console_SCB_MODE_UART_CONST_CFG)
    bridging_console_UartInit();

#elif (bridging_console_SCB_MODE_EZI2C_CONST_CFG)
    bridging_console_EzI2CInit();

#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: bridging_console_Enable
****************************************************************************//**
*
*  Enables bridging_console component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  bridging_console_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The bridging_console configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured bridging_console”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void bridging_console_Enable(void)
{
#if (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!bridging_console_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        bridging_console_CTRL_REG |= bridging_console_CTRL_ENABLED;

        bridging_console_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        bridging_console_ScbModePostEnable();
    }
#else
    bridging_console_CTRL_REG |= bridging_console_CTRL_ENABLED;

    bridging_console_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    bridging_console_ScbModePostEnable();
#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: bridging_console_Start
****************************************************************************//**
*
*  Invokes bridging_console_Init() and bridging_console_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  bridging_console_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void bridging_console_Start(void)
{
    if (0u == bridging_console_initVar)
    {
        bridging_console_Init();
        bridging_console_initVar = 1u; /* Component was initialized */
    }

    bridging_console_Enable();
}


/*******************************************************************************
* Function Name: bridging_console_Stop
****************************************************************************//**
*
*  Disables the bridging_console component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function bridging_console_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void bridging_console_Stop(void)
{
#if (bridging_console_SCB_IRQ_INTERNAL)
    bridging_console_DisableInt();
#endif /* (bridging_console_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    bridging_console_ScbModeStop();

    /* Disable SCB IP */
    bridging_console_CTRL_REG &= (uint32) ~bridging_console_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    bridging_console_SetTxInterruptMode(bridging_console_NO_INTR_SOURCES);

#if (bridging_console_SCB_IRQ_INTERNAL)
    bridging_console_ClearPendingInt();
#endif /* (bridging_console_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: bridging_console_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void bridging_console_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = bridging_console_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~bridging_console_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (bridging_console_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    bridging_console_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: bridging_console_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void bridging_console_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = bridging_console_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~bridging_console_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (bridging_console_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    bridging_console_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (bridging_console_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: bridging_console_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void bridging_console_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_bridging_console_CUSTOM_INTR_HANDLER)
        bridging_console_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_bridging_console_CUSTOM_INTR_HANDLER) */
    }
#endif /* (bridging_console_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: bridging_console_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void bridging_console_ScbEnableIntr(void)
{
#if (bridging_console_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != bridging_console_scbEnableIntr)
        {
            bridging_console_EnableInt();
        }

    #else
        bridging_console_EnableInt();

    #endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (bridging_console_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: bridging_console_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void bridging_console_ScbModePostEnable(void)
{
#if (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!bridging_console_CY_SCBIP_V1)
    if (bridging_console_SCB_MODE_SPI_RUNTM_CFG)
    {
        bridging_console_SpiPostEnable();
    }
    else if (bridging_console_SCB_MODE_UART_RUNTM_CFG)
    {
        bridging_console_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!bridging_console_CY_SCBIP_V1) */

#elif (bridging_console_SCB_MODE_SPI_CONST_CFG)
    bridging_console_SpiPostEnable();

#elif (bridging_console_SCB_MODE_UART_CONST_CFG)
    bridging_console_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: bridging_console_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void bridging_console_ScbModeStop(void)
{
#if (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
    if (bridging_console_SCB_MODE_I2C_RUNTM_CFG)
    {
        bridging_console_I2CStop();
    }
    else if (bridging_console_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        bridging_console_EzI2CStop();
    }
#if (!bridging_console_CY_SCBIP_V1)
    else if (bridging_console_SCB_MODE_SPI_RUNTM_CFG)
    {
        bridging_console_SpiStop();
    }
    else if (bridging_console_SCB_MODE_UART_RUNTM_CFG)
    {
        bridging_console_UartStop();
    }
#endif /* (!bridging_console_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (bridging_console_SCB_MODE_I2C_CONST_CFG)
    bridging_console_I2CStop();

#elif (bridging_console_SCB_MODE_EZI2C_CONST_CFG)
    bridging_console_EzI2CStop();

#elif (bridging_console_SCB_MODE_SPI_CONST_CFG)
    bridging_console_SpiStop();

#elif (bridging_console_SCB_MODE_UART_CONST_CFG)
    bridging_console_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: bridging_console_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void bridging_console_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[bridging_console_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!bridging_console_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!bridging_console_CY_SCBIP_V1) */
        
        uint32 hsiomSel[bridging_console_SCB_PINS_NUMBER] = 
        {
            bridging_console_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            bridging_console_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (bridging_console_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (bridging_console_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < bridging_console_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = bridging_console_PIN_DM_ALG_HIZ;
        }

        if ((bridging_console_SCB_MODE_I2C   == mode) ||
            (bridging_console_SCB_MODE_EZI2C == mode))
        {
        #if (bridging_console_RX_SCL_MOSI_PIN)
            hsiomSel[bridging_console_RX_SCL_MOSI_PIN_INDEX] = bridging_console_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [bridging_console_RX_SCL_MOSI_PIN_INDEX] = bridging_console_PIN_DM_OD_LO;
        #elif (bridging_console_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[bridging_console_RX_WAKE_SCL_MOSI_PIN_INDEX] = bridging_console_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [bridging_console_RX_WAKE_SCL_MOSI_PIN_INDEX] = bridging_console_PIN_DM_OD_LO;
        #else
        #endif /* (bridging_console_RX_SCL_MOSI_PIN) */
        
        #if (bridging_console_TX_SDA_MISO_PIN)
            hsiomSel[bridging_console_TX_SDA_MISO_PIN_INDEX] = bridging_console_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [bridging_console_TX_SDA_MISO_PIN_INDEX] = bridging_console_PIN_DM_OD_LO;
        #endif /* (bridging_console_TX_SDA_MISO_PIN) */
        }
    #if (!bridging_console_CY_SCBIP_V1)
        else if (bridging_console_SCB_MODE_SPI == mode)
        {
        #if (bridging_console_RX_SCL_MOSI_PIN)
            hsiomSel[bridging_console_RX_SCL_MOSI_PIN_INDEX] = bridging_console_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (bridging_console_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[bridging_console_RX_WAKE_SCL_MOSI_PIN_INDEX] = bridging_console_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (bridging_console_RX_SCL_MOSI_PIN) */
        
        #if (bridging_console_TX_SDA_MISO_PIN)
            hsiomSel[bridging_console_TX_SDA_MISO_PIN_INDEX] = bridging_console_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (bridging_console_TX_SDA_MISO_PIN) */
        
        #if (bridging_console_CTS_SCLK_PIN)
            hsiomSel[bridging_console_CTS_SCLK_PIN_INDEX] = bridging_console_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (bridging_console_CTS_SCLK_PIN) */

            if (bridging_console_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[bridging_console_RX_SCL_MOSI_PIN_INDEX] = bridging_console_PIN_DM_DIG_HIZ;
                pinsDm[bridging_console_TX_SDA_MISO_PIN_INDEX] = bridging_console_PIN_DM_STRONG;
                pinsDm[bridging_console_CTS_SCLK_PIN_INDEX] = bridging_console_PIN_DM_DIG_HIZ;

            #if (bridging_console_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[bridging_console_RTS_SS0_PIN_INDEX] = bridging_console_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [bridging_console_RTS_SS0_PIN_INDEX] = bridging_console_PIN_DM_DIG_HIZ;
            #endif /* (bridging_console_RTS_SS0_PIN) */

            #if (bridging_console_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= bridging_console_TX_SDA_MISO_PIN_MASK;
            #endif /* (bridging_console_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[bridging_console_RX_SCL_MOSI_PIN_INDEX] = bridging_console_PIN_DM_STRONG;
                pinsDm[bridging_console_TX_SDA_MISO_PIN_INDEX] = bridging_console_PIN_DM_DIG_HIZ;
                pinsDm[bridging_console_CTS_SCLK_PIN_INDEX] = bridging_console_PIN_DM_STRONG;

            #if (bridging_console_RTS_SS0_PIN)
                hsiomSel [bridging_console_RTS_SS0_PIN_INDEX] = bridging_console_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [bridging_console_RTS_SS0_PIN_INDEX] = bridging_console_PIN_DM_STRONG;
                pinsInBuf |= bridging_console_RTS_SS0_PIN_MASK;
            #endif /* (bridging_console_RTS_SS0_PIN) */

            #if (bridging_console_SS1_PIN)
                hsiomSel [bridging_console_SS1_PIN_INDEX] = bridging_console_SS1_HSIOM_SEL_SPI;
                pinsDm   [bridging_console_SS1_PIN_INDEX] = bridging_console_PIN_DM_STRONG;
                pinsInBuf |= bridging_console_SS1_PIN_MASK;
            #endif /* (bridging_console_SS1_PIN) */

            #if (bridging_console_SS2_PIN)
                hsiomSel [bridging_console_SS2_PIN_INDEX] = bridging_console_SS2_HSIOM_SEL_SPI;
                pinsDm   [bridging_console_SS2_PIN_INDEX] = bridging_console_PIN_DM_STRONG;
                pinsInBuf |= bridging_console_SS2_PIN_MASK;
            #endif /* (bridging_console_SS2_PIN) */

            #if (bridging_console_SS3_PIN)
                hsiomSel [bridging_console_SS3_PIN_INDEX] = bridging_console_SS3_HSIOM_SEL_SPI;
                pinsDm   [bridging_console_SS3_PIN_INDEX] = bridging_console_PIN_DM_STRONG;
                pinsInBuf |= bridging_console_SS3_PIN_MASK;
            #endif /* (bridging_console_SS3_PIN) */

                /* Disable input buffers */
            #if (bridging_console_RX_SCL_MOSI_PIN)
                pinsInBuf |= bridging_console_RX_SCL_MOSI_PIN_MASK;
            #elif (bridging_console_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= bridging_console_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (bridging_console_RX_SCL_MOSI_PIN) */

            #if (bridging_console_CTS_SCLK_PIN)
                pinsInBuf |= bridging_console_CTS_SCLK_PIN_MASK;
            #endif /* (bridging_console_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (bridging_console_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (bridging_console_TX_SDA_MISO_PIN)
                hsiomSel[bridging_console_TX_SDA_MISO_PIN_INDEX] = bridging_console_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [bridging_console_TX_SDA_MISO_PIN_INDEX] = bridging_console_PIN_DM_OD_LO;
            #endif /* (bridging_console_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (bridging_console_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (bridging_console_RX_SCL_MOSI_PIN)
                    hsiomSel[bridging_console_RX_SCL_MOSI_PIN_INDEX] = bridging_console_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [bridging_console_RX_SCL_MOSI_PIN_INDEX] = bridging_console_PIN_DM_DIG_HIZ;
                #elif (bridging_console_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[bridging_console_RX_WAKE_SCL_MOSI_PIN_INDEX] = bridging_console_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [bridging_console_RX_WAKE_SCL_MOSI_PIN_INDEX] = bridging_console_PIN_DM_DIG_HIZ;
                #else
                #endif /* (bridging_console_RX_SCL_MOSI_PIN) */
                }

                if (0u != (bridging_console_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (bridging_console_TX_SDA_MISO_PIN)
                    hsiomSel[bridging_console_TX_SDA_MISO_PIN_INDEX] = bridging_console_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [bridging_console_TX_SDA_MISO_PIN_INDEX] = bridging_console_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= bridging_console_TX_SDA_MISO_PIN_MASK;
                #endif /* (bridging_console_TX_SDA_MISO_PIN) */
                }

            #if !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1)
                if (bridging_console_UART_MODE_STD == subMode)
                {
                    if (0u != (bridging_console_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (bridging_console_CTS_SCLK_PIN)
                        hsiomSel[bridging_console_CTS_SCLK_PIN_INDEX] = bridging_console_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [bridging_console_CTS_SCLK_PIN_INDEX] = bridging_console_PIN_DM_DIG_HIZ;
                    #endif /* (bridging_console_CTS_SCLK_PIN) */
                    }

                    if (0u != (bridging_console_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (bridging_console_RTS_SS0_PIN)
                        hsiomSel[bridging_console_RTS_SS0_PIN_INDEX] = bridging_console_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [bridging_console_RTS_SS0_PIN_INDEX] = bridging_console_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= bridging_console_RTS_SS0_PIN_MASK;
                    #endif /* (bridging_console_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1) */
            }
        }
    #endif /* (!bridging_console_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (bridging_console_RX_SCL_MOSI_PIN)
        bridging_console_SET_HSIOM_SEL(bridging_console_RX_SCL_MOSI_HSIOM_REG,
                                       bridging_console_RX_SCL_MOSI_HSIOM_MASK,
                                       bridging_console_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[bridging_console_RX_SCL_MOSI_PIN_INDEX]);

        bridging_console_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[bridging_console_RX_SCL_MOSI_PIN_INDEX]);

        #if (!bridging_console_CY_SCBIP_V1)
            bridging_console_SET_INP_DIS(bridging_console_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         bridging_console_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & bridging_console_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!bridging_console_CY_SCBIP_V1) */
    
    #elif (bridging_console_RX_WAKE_SCL_MOSI_PIN)
        bridging_console_SET_HSIOM_SEL(bridging_console_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       bridging_console_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       bridging_console_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[bridging_console_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        bridging_console_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[bridging_console_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        bridging_console_SET_INP_DIS(bridging_console_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     bridging_console_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & bridging_console_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        bridging_console_SET_INCFG_TYPE(bridging_console_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        bridging_console_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        bridging_console_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        bridging_console_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (bridging_console_RX_WAKE_SCL_MOSI_PIN) */

    #if (bridging_console_TX_SDA_MISO_PIN)
        bridging_console_SET_HSIOM_SEL(bridging_console_TX_SDA_MISO_HSIOM_REG,
                                       bridging_console_TX_SDA_MISO_HSIOM_MASK,
                                       bridging_console_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[bridging_console_TX_SDA_MISO_PIN_INDEX]);

        bridging_console_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[bridging_console_TX_SDA_MISO_PIN_INDEX]);

    #if (!bridging_console_CY_SCBIP_V1)
        bridging_console_SET_INP_DIS(bridging_console_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     bridging_console_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & bridging_console_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!bridging_console_CY_SCBIP_V1) */
    #endif /* (bridging_console_RX_SCL_MOSI_PIN) */

    #if (bridging_console_CTS_SCLK_PIN)
        bridging_console_SET_HSIOM_SEL(bridging_console_CTS_SCLK_HSIOM_REG,
                                       bridging_console_CTS_SCLK_HSIOM_MASK,
                                       bridging_console_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[bridging_console_CTS_SCLK_PIN_INDEX]);

        bridging_console_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[bridging_console_CTS_SCLK_PIN_INDEX]);

        bridging_console_SET_INP_DIS(bridging_console_uart_cts_spi_sclk_INP_DIS,
                                     bridging_console_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & bridging_console_CTS_SCLK_PIN_MASK)));
    #endif /* (bridging_console_CTS_SCLK_PIN) */

    #if (bridging_console_RTS_SS0_PIN)
        bridging_console_SET_HSIOM_SEL(bridging_console_RTS_SS0_HSIOM_REG,
                                       bridging_console_RTS_SS0_HSIOM_MASK,
                                       bridging_console_RTS_SS0_HSIOM_POS,
                                       hsiomSel[bridging_console_RTS_SS0_PIN_INDEX]);

        bridging_console_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[bridging_console_RTS_SS0_PIN_INDEX]);

        bridging_console_SET_INP_DIS(bridging_console_uart_rts_spi_ss0_INP_DIS,
                                     bridging_console_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & bridging_console_RTS_SS0_PIN_MASK)));
    #endif /* (bridging_console_RTS_SS0_PIN) */

    #if (bridging_console_SS1_PIN)
        bridging_console_SET_HSIOM_SEL(bridging_console_SS1_HSIOM_REG,
                                       bridging_console_SS1_HSIOM_MASK,
                                       bridging_console_SS1_HSIOM_POS,
                                       hsiomSel[bridging_console_SS1_PIN_INDEX]);

        bridging_console_spi_ss1_SetDriveMode((uint8) pinsDm[bridging_console_SS1_PIN_INDEX]);

        bridging_console_SET_INP_DIS(bridging_console_spi_ss1_INP_DIS,
                                     bridging_console_spi_ss1_MASK,
                                     (0u != (pinsInBuf & bridging_console_SS1_PIN_MASK)));
    #endif /* (bridging_console_SS1_PIN) */

    #if (bridging_console_SS2_PIN)
        bridging_console_SET_HSIOM_SEL(bridging_console_SS2_HSIOM_REG,
                                       bridging_console_SS2_HSIOM_MASK,
                                       bridging_console_SS2_HSIOM_POS,
                                       hsiomSel[bridging_console_SS2_PIN_INDEX]);

        bridging_console_spi_ss2_SetDriveMode((uint8) pinsDm[bridging_console_SS2_PIN_INDEX]);

        bridging_console_SET_INP_DIS(bridging_console_spi_ss2_INP_DIS,
                                     bridging_console_spi_ss2_MASK,
                                     (0u != (pinsInBuf & bridging_console_SS2_PIN_MASK)));
    #endif /* (bridging_console_SS2_PIN) */

    #if (bridging_console_SS3_PIN)
        bridging_console_SET_HSIOM_SEL(bridging_console_SS3_HSIOM_REG,
                                       bridging_console_SS3_HSIOM_MASK,
                                       bridging_console_SS3_HSIOM_POS,
                                       hsiomSel[bridging_console_SS3_PIN_INDEX]);

        bridging_console_spi_ss3_SetDriveMode((uint8) pinsDm[bridging_console_SS3_PIN_INDEX]);

        bridging_console_SET_INP_DIS(bridging_console_spi_ss3_INP_DIS,
                                     bridging_console_spi_ss3_MASK,
                                     (0u != (pinsInBuf & bridging_console_SS3_PIN_MASK)));
    #endif /* (bridging_console_SS3_PIN) */
    }

#endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: bridging_console_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void bridging_console_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (bridging_console_CTRL_REG & bridging_console_CTRL_EC_AM_MODE)) &&
            (0u == (bridging_console_I2C_CTRL_REG & bridging_console_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            bridging_console_CTRL_REG &= ~bridging_console_CTRL_EC_AM_MODE;
            bridging_console_CTRL_REG |=  bridging_console_CTRL_EC_AM_MODE;
        }

        bridging_console_I2C_SLAVE_CMD_REG = bridging_console_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1) */


/* [] END OF FILE */
