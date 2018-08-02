/***************************************************************************//**
* \file from_ble.c
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

#include "from_ble_PVT.h"

#if (from_ble_SCB_MODE_I2C_INC)
    #include "from_ble_I2C_PVT.h"
#endif /* (from_ble_SCB_MODE_I2C_INC) */

#if (from_ble_SCB_MODE_EZI2C_INC)
    #include "from_ble_EZI2C_PVT.h"
#endif /* (from_ble_SCB_MODE_EZI2C_INC) */

#if (from_ble_SCB_MODE_SPI_INC || from_ble_SCB_MODE_UART_INC)
    #include "from_ble_SPI_UART_PVT.h"
#endif /* (from_ble_SCB_MODE_SPI_INC || from_ble_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (from_ble_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 from_ble_scbMode = from_ble_SCB_MODE_UNCONFIG;
    uint8 from_ble_scbEnableWake;
    uint8 from_ble_scbEnableIntr;

    /* I2C configuration variables */
    uint8 from_ble_mode;
    uint8 from_ble_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * from_ble_rxBuffer;
    uint8  from_ble_rxDataBits;
    uint32 from_ble_rxBufferSize;

    volatile uint8 * from_ble_txBuffer;
    uint8  from_ble_txDataBits;
    uint32 from_ble_txBufferSize;

    /* EZI2C configuration variables */
    uint8 from_ble_numberOfAddr;
    uint8 from_ble_subAddrSize;
#endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** from_ble_initVar indicates whether the from_ble 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the from_ble_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  from_ble_Init() function can be called before the 
*  from_ble_Start() or from_ble_Enable() function.
*/
uint8 from_ble_initVar = 0u;


#if (! (from_ble_SCB_MODE_I2C_CONST_CFG || \
        from_ble_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * from_ble_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent from_ble_Enable() call.
    */
    uint16 from_ble_IntrTxMask = 0u;
#endif /* (! (from_ble_SCB_MODE_I2C_CONST_CFG || \
              from_ble_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (from_ble_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_from_ble_CUSTOM_INTR_HANDLER)
    void (*from_ble_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_from_ble_CUSTOM_INTR_HANDLER) */
#endif /* (from_ble_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void from_ble_ScbEnableIntr(void);
static void from_ble_ScbModeStop(void);
static void from_ble_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: from_ble_Init
****************************************************************************//**
*
*  Initializes the from_ble component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  from_ble_I2CInit, from_ble_SpiInit, 
*  from_ble_UartInit or from_ble_EzI2CInit.
*
*******************************************************************************/
void from_ble_Init(void)
{
#if (from_ble_SCB_MODE_UNCONFIG_CONST_CFG)
    if (from_ble_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        from_ble_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (from_ble_SCB_MODE_I2C_CONST_CFG)
    from_ble_I2CInit();

#elif (from_ble_SCB_MODE_SPI_CONST_CFG)
    from_ble_SpiInit();

#elif (from_ble_SCB_MODE_UART_CONST_CFG)
    from_ble_UartInit();

#elif (from_ble_SCB_MODE_EZI2C_CONST_CFG)
    from_ble_EzI2CInit();

#endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: from_ble_Enable
****************************************************************************//**
*
*  Enables from_ble component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  from_ble_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The from_ble configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured from_ble”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void from_ble_Enable(void)
{
#if (from_ble_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!from_ble_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        from_ble_CTRL_REG |= from_ble_CTRL_ENABLED;

        from_ble_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        from_ble_ScbModePostEnable();
    }
#else
    from_ble_CTRL_REG |= from_ble_CTRL_ENABLED;

    from_ble_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    from_ble_ScbModePostEnable();
#endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: from_ble_Start
****************************************************************************//**
*
*  Invokes from_ble_Init() and from_ble_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  from_ble_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void from_ble_Start(void)
{
    if (0u == from_ble_initVar)
    {
        from_ble_Init();
        from_ble_initVar = 1u; /* Component was initialized */
    }

    from_ble_Enable();
}


/*******************************************************************************
* Function Name: from_ble_Stop
****************************************************************************//**
*
*  Disables the from_ble component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function from_ble_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void from_ble_Stop(void)
{
#if (from_ble_SCB_IRQ_INTERNAL)
    from_ble_DisableInt();
#endif /* (from_ble_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    from_ble_ScbModeStop();

    /* Disable SCB IP */
    from_ble_CTRL_REG &= (uint32) ~from_ble_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    from_ble_SetTxInterruptMode(from_ble_NO_INTR_SOURCES);

#if (from_ble_SCB_IRQ_INTERNAL)
    from_ble_ClearPendingInt();
#endif /* (from_ble_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: from_ble_SetRxFifoLevel
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
void from_ble_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = from_ble_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~from_ble_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (from_ble_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    from_ble_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: from_ble_SetTxFifoLevel
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
void from_ble_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = from_ble_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~from_ble_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (from_ble_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    from_ble_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (from_ble_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: from_ble_SetCustomInterruptHandler
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
    void from_ble_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_from_ble_CUSTOM_INTR_HANDLER)
        from_ble_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_from_ble_CUSTOM_INTR_HANDLER) */
    }
#endif /* (from_ble_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: from_ble_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void from_ble_ScbEnableIntr(void)
{
#if (from_ble_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (from_ble_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != from_ble_scbEnableIntr)
        {
            from_ble_EnableInt();
        }

    #else
        from_ble_EnableInt();

    #endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (from_ble_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: from_ble_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void from_ble_ScbModePostEnable(void)
{
#if (from_ble_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!from_ble_CY_SCBIP_V1)
    if (from_ble_SCB_MODE_SPI_RUNTM_CFG)
    {
        from_ble_SpiPostEnable();
    }
    else if (from_ble_SCB_MODE_UART_RUNTM_CFG)
    {
        from_ble_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!from_ble_CY_SCBIP_V1) */

#elif (from_ble_SCB_MODE_SPI_CONST_CFG)
    from_ble_SpiPostEnable();

#elif (from_ble_SCB_MODE_UART_CONST_CFG)
    from_ble_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: from_ble_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void from_ble_ScbModeStop(void)
{
#if (from_ble_SCB_MODE_UNCONFIG_CONST_CFG)
    if (from_ble_SCB_MODE_I2C_RUNTM_CFG)
    {
        from_ble_I2CStop();
    }
    else if (from_ble_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        from_ble_EzI2CStop();
    }
#if (!from_ble_CY_SCBIP_V1)
    else if (from_ble_SCB_MODE_SPI_RUNTM_CFG)
    {
        from_ble_SpiStop();
    }
    else if (from_ble_SCB_MODE_UART_RUNTM_CFG)
    {
        from_ble_UartStop();
    }
#endif /* (!from_ble_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (from_ble_SCB_MODE_I2C_CONST_CFG)
    from_ble_I2CStop();

#elif (from_ble_SCB_MODE_EZI2C_CONST_CFG)
    from_ble_EzI2CStop();

#elif (from_ble_SCB_MODE_SPI_CONST_CFG)
    from_ble_SpiStop();

#elif (from_ble_SCB_MODE_UART_CONST_CFG)
    from_ble_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (from_ble_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: from_ble_SetPins
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
    void from_ble_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[from_ble_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!from_ble_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!from_ble_CY_SCBIP_V1) */
        
        uint32 hsiomSel[from_ble_SCB_PINS_NUMBER] = 
        {
            from_ble_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            from_ble_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (from_ble_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (from_ble_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < from_ble_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = from_ble_PIN_DM_ALG_HIZ;
        }

        if ((from_ble_SCB_MODE_I2C   == mode) ||
            (from_ble_SCB_MODE_EZI2C == mode))
        {
        #if (from_ble_RX_SCL_MOSI_PIN)
            hsiomSel[from_ble_RX_SCL_MOSI_PIN_INDEX] = from_ble_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [from_ble_RX_SCL_MOSI_PIN_INDEX] = from_ble_PIN_DM_OD_LO;
        #elif (from_ble_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[from_ble_RX_WAKE_SCL_MOSI_PIN_INDEX] = from_ble_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [from_ble_RX_WAKE_SCL_MOSI_PIN_INDEX] = from_ble_PIN_DM_OD_LO;
        #else
        #endif /* (from_ble_RX_SCL_MOSI_PIN) */
        
        #if (from_ble_TX_SDA_MISO_PIN)
            hsiomSel[from_ble_TX_SDA_MISO_PIN_INDEX] = from_ble_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [from_ble_TX_SDA_MISO_PIN_INDEX] = from_ble_PIN_DM_OD_LO;
        #endif /* (from_ble_TX_SDA_MISO_PIN) */
        }
    #if (!from_ble_CY_SCBIP_V1)
        else if (from_ble_SCB_MODE_SPI == mode)
        {
        #if (from_ble_RX_SCL_MOSI_PIN)
            hsiomSel[from_ble_RX_SCL_MOSI_PIN_INDEX] = from_ble_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (from_ble_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[from_ble_RX_WAKE_SCL_MOSI_PIN_INDEX] = from_ble_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (from_ble_RX_SCL_MOSI_PIN) */
        
        #if (from_ble_TX_SDA_MISO_PIN)
            hsiomSel[from_ble_TX_SDA_MISO_PIN_INDEX] = from_ble_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (from_ble_TX_SDA_MISO_PIN) */
        
        #if (from_ble_CTS_SCLK_PIN)
            hsiomSel[from_ble_CTS_SCLK_PIN_INDEX] = from_ble_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (from_ble_CTS_SCLK_PIN) */

            if (from_ble_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[from_ble_RX_SCL_MOSI_PIN_INDEX] = from_ble_PIN_DM_DIG_HIZ;
                pinsDm[from_ble_TX_SDA_MISO_PIN_INDEX] = from_ble_PIN_DM_STRONG;
                pinsDm[from_ble_CTS_SCLK_PIN_INDEX] = from_ble_PIN_DM_DIG_HIZ;

            #if (from_ble_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[from_ble_RTS_SS0_PIN_INDEX] = from_ble_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [from_ble_RTS_SS0_PIN_INDEX] = from_ble_PIN_DM_DIG_HIZ;
            #endif /* (from_ble_RTS_SS0_PIN) */

            #if (from_ble_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= from_ble_TX_SDA_MISO_PIN_MASK;
            #endif /* (from_ble_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[from_ble_RX_SCL_MOSI_PIN_INDEX] = from_ble_PIN_DM_STRONG;
                pinsDm[from_ble_TX_SDA_MISO_PIN_INDEX] = from_ble_PIN_DM_DIG_HIZ;
                pinsDm[from_ble_CTS_SCLK_PIN_INDEX] = from_ble_PIN_DM_STRONG;

            #if (from_ble_RTS_SS0_PIN)
                hsiomSel [from_ble_RTS_SS0_PIN_INDEX] = from_ble_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [from_ble_RTS_SS0_PIN_INDEX] = from_ble_PIN_DM_STRONG;
                pinsInBuf |= from_ble_RTS_SS0_PIN_MASK;
            #endif /* (from_ble_RTS_SS0_PIN) */

            #if (from_ble_SS1_PIN)
                hsiomSel [from_ble_SS1_PIN_INDEX] = from_ble_SS1_HSIOM_SEL_SPI;
                pinsDm   [from_ble_SS1_PIN_INDEX] = from_ble_PIN_DM_STRONG;
                pinsInBuf |= from_ble_SS1_PIN_MASK;
            #endif /* (from_ble_SS1_PIN) */

            #if (from_ble_SS2_PIN)
                hsiomSel [from_ble_SS2_PIN_INDEX] = from_ble_SS2_HSIOM_SEL_SPI;
                pinsDm   [from_ble_SS2_PIN_INDEX] = from_ble_PIN_DM_STRONG;
                pinsInBuf |= from_ble_SS2_PIN_MASK;
            #endif /* (from_ble_SS2_PIN) */

            #if (from_ble_SS3_PIN)
                hsiomSel [from_ble_SS3_PIN_INDEX] = from_ble_SS3_HSIOM_SEL_SPI;
                pinsDm   [from_ble_SS3_PIN_INDEX] = from_ble_PIN_DM_STRONG;
                pinsInBuf |= from_ble_SS3_PIN_MASK;
            #endif /* (from_ble_SS3_PIN) */

                /* Disable input buffers */
            #if (from_ble_RX_SCL_MOSI_PIN)
                pinsInBuf |= from_ble_RX_SCL_MOSI_PIN_MASK;
            #elif (from_ble_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= from_ble_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (from_ble_RX_SCL_MOSI_PIN) */

            #if (from_ble_CTS_SCLK_PIN)
                pinsInBuf |= from_ble_CTS_SCLK_PIN_MASK;
            #endif /* (from_ble_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (from_ble_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (from_ble_TX_SDA_MISO_PIN)
                hsiomSel[from_ble_TX_SDA_MISO_PIN_INDEX] = from_ble_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [from_ble_TX_SDA_MISO_PIN_INDEX] = from_ble_PIN_DM_OD_LO;
            #endif /* (from_ble_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (from_ble_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (from_ble_RX_SCL_MOSI_PIN)
                    hsiomSel[from_ble_RX_SCL_MOSI_PIN_INDEX] = from_ble_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [from_ble_RX_SCL_MOSI_PIN_INDEX] = from_ble_PIN_DM_DIG_HIZ;
                #elif (from_ble_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[from_ble_RX_WAKE_SCL_MOSI_PIN_INDEX] = from_ble_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [from_ble_RX_WAKE_SCL_MOSI_PIN_INDEX] = from_ble_PIN_DM_DIG_HIZ;
                #else
                #endif /* (from_ble_RX_SCL_MOSI_PIN) */
                }

                if (0u != (from_ble_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (from_ble_TX_SDA_MISO_PIN)
                    hsiomSel[from_ble_TX_SDA_MISO_PIN_INDEX] = from_ble_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [from_ble_TX_SDA_MISO_PIN_INDEX] = from_ble_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= from_ble_TX_SDA_MISO_PIN_MASK;
                #endif /* (from_ble_TX_SDA_MISO_PIN) */
                }

            #if !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1)
                if (from_ble_UART_MODE_STD == subMode)
                {
                    if (0u != (from_ble_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (from_ble_CTS_SCLK_PIN)
                        hsiomSel[from_ble_CTS_SCLK_PIN_INDEX] = from_ble_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [from_ble_CTS_SCLK_PIN_INDEX] = from_ble_PIN_DM_DIG_HIZ;
                    #endif /* (from_ble_CTS_SCLK_PIN) */
                    }

                    if (0u != (from_ble_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (from_ble_RTS_SS0_PIN)
                        hsiomSel[from_ble_RTS_SS0_PIN_INDEX] = from_ble_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [from_ble_RTS_SS0_PIN_INDEX] = from_ble_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= from_ble_RTS_SS0_PIN_MASK;
                    #endif /* (from_ble_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1) */
            }
        }
    #endif /* (!from_ble_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (from_ble_RX_SCL_MOSI_PIN)
        from_ble_SET_HSIOM_SEL(from_ble_RX_SCL_MOSI_HSIOM_REG,
                                       from_ble_RX_SCL_MOSI_HSIOM_MASK,
                                       from_ble_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[from_ble_RX_SCL_MOSI_PIN_INDEX]);

        from_ble_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[from_ble_RX_SCL_MOSI_PIN_INDEX]);

        #if (!from_ble_CY_SCBIP_V1)
            from_ble_SET_INP_DIS(from_ble_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         from_ble_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & from_ble_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!from_ble_CY_SCBIP_V1) */
    
    #elif (from_ble_RX_WAKE_SCL_MOSI_PIN)
        from_ble_SET_HSIOM_SEL(from_ble_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       from_ble_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       from_ble_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[from_ble_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        from_ble_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[from_ble_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        from_ble_SET_INP_DIS(from_ble_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     from_ble_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & from_ble_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        from_ble_SET_INCFG_TYPE(from_ble_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        from_ble_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        from_ble_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        from_ble_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (from_ble_RX_WAKE_SCL_MOSI_PIN) */

    #if (from_ble_TX_SDA_MISO_PIN)
        from_ble_SET_HSIOM_SEL(from_ble_TX_SDA_MISO_HSIOM_REG,
                                       from_ble_TX_SDA_MISO_HSIOM_MASK,
                                       from_ble_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[from_ble_TX_SDA_MISO_PIN_INDEX]);

        from_ble_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[from_ble_TX_SDA_MISO_PIN_INDEX]);

    #if (!from_ble_CY_SCBIP_V1)
        from_ble_SET_INP_DIS(from_ble_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     from_ble_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & from_ble_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!from_ble_CY_SCBIP_V1) */
    #endif /* (from_ble_RX_SCL_MOSI_PIN) */

    #if (from_ble_CTS_SCLK_PIN)
        from_ble_SET_HSIOM_SEL(from_ble_CTS_SCLK_HSIOM_REG,
                                       from_ble_CTS_SCLK_HSIOM_MASK,
                                       from_ble_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[from_ble_CTS_SCLK_PIN_INDEX]);

        from_ble_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[from_ble_CTS_SCLK_PIN_INDEX]);

        from_ble_SET_INP_DIS(from_ble_uart_cts_spi_sclk_INP_DIS,
                                     from_ble_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & from_ble_CTS_SCLK_PIN_MASK)));
    #endif /* (from_ble_CTS_SCLK_PIN) */

    #if (from_ble_RTS_SS0_PIN)
        from_ble_SET_HSIOM_SEL(from_ble_RTS_SS0_HSIOM_REG,
                                       from_ble_RTS_SS0_HSIOM_MASK,
                                       from_ble_RTS_SS0_HSIOM_POS,
                                       hsiomSel[from_ble_RTS_SS0_PIN_INDEX]);

        from_ble_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[from_ble_RTS_SS0_PIN_INDEX]);

        from_ble_SET_INP_DIS(from_ble_uart_rts_spi_ss0_INP_DIS,
                                     from_ble_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & from_ble_RTS_SS0_PIN_MASK)));
    #endif /* (from_ble_RTS_SS0_PIN) */

    #if (from_ble_SS1_PIN)
        from_ble_SET_HSIOM_SEL(from_ble_SS1_HSIOM_REG,
                                       from_ble_SS1_HSIOM_MASK,
                                       from_ble_SS1_HSIOM_POS,
                                       hsiomSel[from_ble_SS1_PIN_INDEX]);

        from_ble_spi_ss1_SetDriveMode((uint8) pinsDm[from_ble_SS1_PIN_INDEX]);

        from_ble_SET_INP_DIS(from_ble_spi_ss1_INP_DIS,
                                     from_ble_spi_ss1_MASK,
                                     (0u != (pinsInBuf & from_ble_SS1_PIN_MASK)));
    #endif /* (from_ble_SS1_PIN) */

    #if (from_ble_SS2_PIN)
        from_ble_SET_HSIOM_SEL(from_ble_SS2_HSIOM_REG,
                                       from_ble_SS2_HSIOM_MASK,
                                       from_ble_SS2_HSIOM_POS,
                                       hsiomSel[from_ble_SS2_PIN_INDEX]);

        from_ble_spi_ss2_SetDriveMode((uint8) pinsDm[from_ble_SS2_PIN_INDEX]);

        from_ble_SET_INP_DIS(from_ble_spi_ss2_INP_DIS,
                                     from_ble_spi_ss2_MASK,
                                     (0u != (pinsInBuf & from_ble_SS2_PIN_MASK)));
    #endif /* (from_ble_SS2_PIN) */

    #if (from_ble_SS3_PIN)
        from_ble_SET_HSIOM_SEL(from_ble_SS3_HSIOM_REG,
                                       from_ble_SS3_HSIOM_MASK,
                                       from_ble_SS3_HSIOM_POS,
                                       hsiomSel[from_ble_SS3_PIN_INDEX]);

        from_ble_spi_ss3_SetDriveMode((uint8) pinsDm[from_ble_SS3_PIN_INDEX]);

        from_ble_SET_INP_DIS(from_ble_spi_ss3_INP_DIS,
                                     from_ble_spi_ss3_MASK,
                                     (0u != (pinsInBuf & from_ble_SS3_PIN_MASK)));
    #endif /* (from_ble_SS3_PIN) */
    }

#endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: from_ble_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void from_ble_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (from_ble_CTRL_REG & from_ble_CTRL_EC_AM_MODE)) &&
            (0u == (from_ble_I2C_CTRL_REG & from_ble_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            from_ble_CTRL_REG &= ~from_ble_CTRL_EC_AM_MODE;
            from_ble_CTRL_REG |=  from_ble_CTRL_EC_AM_MODE;
        }

        from_ble_I2C_SLAVE_CMD_REG = from_ble_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1) */


/* [] END OF FILE */
