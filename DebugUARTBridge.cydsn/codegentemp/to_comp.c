/***************************************************************************//**
* \file to_comp.c
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

#include "to_comp_PVT.h"

#if (to_comp_SCB_MODE_I2C_INC)
    #include "to_comp_I2C_PVT.h"
#endif /* (to_comp_SCB_MODE_I2C_INC) */

#if (to_comp_SCB_MODE_EZI2C_INC)
    #include "to_comp_EZI2C_PVT.h"
#endif /* (to_comp_SCB_MODE_EZI2C_INC) */

#if (to_comp_SCB_MODE_SPI_INC || to_comp_SCB_MODE_UART_INC)
    #include "to_comp_SPI_UART_PVT.h"
#endif /* (to_comp_SCB_MODE_SPI_INC || to_comp_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (to_comp_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 to_comp_scbMode = to_comp_SCB_MODE_UNCONFIG;
    uint8 to_comp_scbEnableWake;
    uint8 to_comp_scbEnableIntr;

    /* I2C configuration variables */
    uint8 to_comp_mode;
    uint8 to_comp_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * to_comp_rxBuffer;
    uint8  to_comp_rxDataBits;
    uint32 to_comp_rxBufferSize;

    volatile uint8 * to_comp_txBuffer;
    uint8  to_comp_txDataBits;
    uint32 to_comp_txBufferSize;

    /* EZI2C configuration variables */
    uint8 to_comp_numberOfAddr;
    uint8 to_comp_subAddrSize;
#endif /* (to_comp_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** to_comp_initVar indicates whether the to_comp 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the to_comp_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  to_comp_Init() function can be called before the 
*  to_comp_Start() or to_comp_Enable() function.
*/
uint8 to_comp_initVar = 0u;


#if (! (to_comp_SCB_MODE_I2C_CONST_CFG || \
        to_comp_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * to_comp_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent to_comp_Enable() call.
    */
    uint16 to_comp_IntrTxMask = 0u;
#endif /* (! (to_comp_SCB_MODE_I2C_CONST_CFG || \
              to_comp_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (to_comp_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_to_comp_CUSTOM_INTR_HANDLER)
    void (*to_comp_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_to_comp_CUSTOM_INTR_HANDLER) */
#endif /* (to_comp_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void to_comp_ScbEnableIntr(void);
static void to_comp_ScbModeStop(void);
static void to_comp_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: to_comp_Init
****************************************************************************//**
*
*  Initializes the to_comp component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  to_comp_I2CInit, to_comp_SpiInit, 
*  to_comp_UartInit or to_comp_EzI2CInit.
*
*******************************************************************************/
void to_comp_Init(void)
{
#if (to_comp_SCB_MODE_UNCONFIG_CONST_CFG)
    if (to_comp_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        to_comp_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (to_comp_SCB_MODE_I2C_CONST_CFG)
    to_comp_I2CInit();

#elif (to_comp_SCB_MODE_SPI_CONST_CFG)
    to_comp_SpiInit();

#elif (to_comp_SCB_MODE_UART_CONST_CFG)
    to_comp_UartInit();

#elif (to_comp_SCB_MODE_EZI2C_CONST_CFG)
    to_comp_EzI2CInit();

#endif /* (to_comp_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: to_comp_Enable
****************************************************************************//**
*
*  Enables to_comp component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  to_comp_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The to_comp configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured to_comp”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void to_comp_Enable(void)
{
#if (to_comp_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!to_comp_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        to_comp_CTRL_REG |= to_comp_CTRL_ENABLED;

        to_comp_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        to_comp_ScbModePostEnable();
    }
#else
    to_comp_CTRL_REG |= to_comp_CTRL_ENABLED;

    to_comp_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    to_comp_ScbModePostEnable();
#endif /* (to_comp_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: to_comp_Start
****************************************************************************//**
*
*  Invokes to_comp_Init() and to_comp_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  to_comp_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void to_comp_Start(void)
{
    if (0u == to_comp_initVar)
    {
        to_comp_Init();
        to_comp_initVar = 1u; /* Component was initialized */
    }

    to_comp_Enable();
}


/*******************************************************************************
* Function Name: to_comp_Stop
****************************************************************************//**
*
*  Disables the to_comp component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function to_comp_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void to_comp_Stop(void)
{
#if (to_comp_SCB_IRQ_INTERNAL)
    to_comp_DisableInt();
#endif /* (to_comp_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    to_comp_ScbModeStop();

    /* Disable SCB IP */
    to_comp_CTRL_REG &= (uint32) ~to_comp_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    to_comp_SetTxInterruptMode(to_comp_NO_INTR_SOURCES);

#if (to_comp_SCB_IRQ_INTERNAL)
    to_comp_ClearPendingInt();
#endif /* (to_comp_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: to_comp_SetRxFifoLevel
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
void to_comp_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = to_comp_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~to_comp_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (to_comp_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    to_comp_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: to_comp_SetTxFifoLevel
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
void to_comp_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = to_comp_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~to_comp_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (to_comp_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    to_comp_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (to_comp_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: to_comp_SetCustomInterruptHandler
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
    void to_comp_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_to_comp_CUSTOM_INTR_HANDLER)
        to_comp_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_to_comp_CUSTOM_INTR_HANDLER) */
    }
#endif /* (to_comp_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: to_comp_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void to_comp_ScbEnableIntr(void)
{
#if (to_comp_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (to_comp_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != to_comp_scbEnableIntr)
        {
            to_comp_EnableInt();
        }

    #else
        to_comp_EnableInt();

    #endif /* (to_comp_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (to_comp_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: to_comp_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void to_comp_ScbModePostEnable(void)
{
#if (to_comp_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!to_comp_CY_SCBIP_V1)
    if (to_comp_SCB_MODE_SPI_RUNTM_CFG)
    {
        to_comp_SpiPostEnable();
    }
    else if (to_comp_SCB_MODE_UART_RUNTM_CFG)
    {
        to_comp_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!to_comp_CY_SCBIP_V1) */

#elif (to_comp_SCB_MODE_SPI_CONST_CFG)
    to_comp_SpiPostEnable();

#elif (to_comp_SCB_MODE_UART_CONST_CFG)
    to_comp_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (to_comp_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: to_comp_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void to_comp_ScbModeStop(void)
{
#if (to_comp_SCB_MODE_UNCONFIG_CONST_CFG)
    if (to_comp_SCB_MODE_I2C_RUNTM_CFG)
    {
        to_comp_I2CStop();
    }
    else if (to_comp_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        to_comp_EzI2CStop();
    }
#if (!to_comp_CY_SCBIP_V1)
    else if (to_comp_SCB_MODE_SPI_RUNTM_CFG)
    {
        to_comp_SpiStop();
    }
    else if (to_comp_SCB_MODE_UART_RUNTM_CFG)
    {
        to_comp_UartStop();
    }
#endif /* (!to_comp_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (to_comp_SCB_MODE_I2C_CONST_CFG)
    to_comp_I2CStop();

#elif (to_comp_SCB_MODE_EZI2C_CONST_CFG)
    to_comp_EzI2CStop();

#elif (to_comp_SCB_MODE_SPI_CONST_CFG)
    to_comp_SpiStop();

#elif (to_comp_SCB_MODE_UART_CONST_CFG)
    to_comp_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (to_comp_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (to_comp_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: to_comp_SetPins
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
    void to_comp_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[to_comp_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!to_comp_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!to_comp_CY_SCBIP_V1) */
        
        uint32 hsiomSel[to_comp_SCB_PINS_NUMBER] = 
        {
            to_comp_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            to_comp_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (to_comp_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (to_comp_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < to_comp_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = to_comp_PIN_DM_ALG_HIZ;
        }

        if ((to_comp_SCB_MODE_I2C   == mode) ||
            (to_comp_SCB_MODE_EZI2C == mode))
        {
        #if (to_comp_RX_SCL_MOSI_PIN)
            hsiomSel[to_comp_RX_SCL_MOSI_PIN_INDEX] = to_comp_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [to_comp_RX_SCL_MOSI_PIN_INDEX] = to_comp_PIN_DM_OD_LO;
        #elif (to_comp_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[to_comp_RX_WAKE_SCL_MOSI_PIN_INDEX] = to_comp_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [to_comp_RX_WAKE_SCL_MOSI_PIN_INDEX] = to_comp_PIN_DM_OD_LO;
        #else
        #endif /* (to_comp_RX_SCL_MOSI_PIN) */
        
        #if (to_comp_TX_SDA_MISO_PIN)
            hsiomSel[to_comp_TX_SDA_MISO_PIN_INDEX] = to_comp_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [to_comp_TX_SDA_MISO_PIN_INDEX] = to_comp_PIN_DM_OD_LO;
        #endif /* (to_comp_TX_SDA_MISO_PIN) */
        }
    #if (!to_comp_CY_SCBIP_V1)
        else if (to_comp_SCB_MODE_SPI == mode)
        {
        #if (to_comp_RX_SCL_MOSI_PIN)
            hsiomSel[to_comp_RX_SCL_MOSI_PIN_INDEX] = to_comp_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (to_comp_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[to_comp_RX_WAKE_SCL_MOSI_PIN_INDEX] = to_comp_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (to_comp_RX_SCL_MOSI_PIN) */
        
        #if (to_comp_TX_SDA_MISO_PIN)
            hsiomSel[to_comp_TX_SDA_MISO_PIN_INDEX] = to_comp_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (to_comp_TX_SDA_MISO_PIN) */
        
        #if (to_comp_CTS_SCLK_PIN)
            hsiomSel[to_comp_CTS_SCLK_PIN_INDEX] = to_comp_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (to_comp_CTS_SCLK_PIN) */

            if (to_comp_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[to_comp_RX_SCL_MOSI_PIN_INDEX] = to_comp_PIN_DM_DIG_HIZ;
                pinsDm[to_comp_TX_SDA_MISO_PIN_INDEX] = to_comp_PIN_DM_STRONG;
                pinsDm[to_comp_CTS_SCLK_PIN_INDEX] = to_comp_PIN_DM_DIG_HIZ;

            #if (to_comp_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[to_comp_RTS_SS0_PIN_INDEX] = to_comp_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [to_comp_RTS_SS0_PIN_INDEX] = to_comp_PIN_DM_DIG_HIZ;
            #endif /* (to_comp_RTS_SS0_PIN) */

            #if (to_comp_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= to_comp_TX_SDA_MISO_PIN_MASK;
            #endif /* (to_comp_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[to_comp_RX_SCL_MOSI_PIN_INDEX] = to_comp_PIN_DM_STRONG;
                pinsDm[to_comp_TX_SDA_MISO_PIN_INDEX] = to_comp_PIN_DM_DIG_HIZ;
                pinsDm[to_comp_CTS_SCLK_PIN_INDEX] = to_comp_PIN_DM_STRONG;

            #if (to_comp_RTS_SS0_PIN)
                hsiomSel [to_comp_RTS_SS0_PIN_INDEX] = to_comp_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [to_comp_RTS_SS0_PIN_INDEX] = to_comp_PIN_DM_STRONG;
                pinsInBuf |= to_comp_RTS_SS0_PIN_MASK;
            #endif /* (to_comp_RTS_SS0_PIN) */

            #if (to_comp_SS1_PIN)
                hsiomSel [to_comp_SS1_PIN_INDEX] = to_comp_SS1_HSIOM_SEL_SPI;
                pinsDm   [to_comp_SS1_PIN_INDEX] = to_comp_PIN_DM_STRONG;
                pinsInBuf |= to_comp_SS1_PIN_MASK;
            #endif /* (to_comp_SS1_PIN) */

            #if (to_comp_SS2_PIN)
                hsiomSel [to_comp_SS2_PIN_INDEX] = to_comp_SS2_HSIOM_SEL_SPI;
                pinsDm   [to_comp_SS2_PIN_INDEX] = to_comp_PIN_DM_STRONG;
                pinsInBuf |= to_comp_SS2_PIN_MASK;
            #endif /* (to_comp_SS2_PIN) */

            #if (to_comp_SS3_PIN)
                hsiomSel [to_comp_SS3_PIN_INDEX] = to_comp_SS3_HSIOM_SEL_SPI;
                pinsDm   [to_comp_SS3_PIN_INDEX] = to_comp_PIN_DM_STRONG;
                pinsInBuf |= to_comp_SS3_PIN_MASK;
            #endif /* (to_comp_SS3_PIN) */

                /* Disable input buffers */
            #if (to_comp_RX_SCL_MOSI_PIN)
                pinsInBuf |= to_comp_RX_SCL_MOSI_PIN_MASK;
            #elif (to_comp_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= to_comp_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (to_comp_RX_SCL_MOSI_PIN) */

            #if (to_comp_CTS_SCLK_PIN)
                pinsInBuf |= to_comp_CTS_SCLK_PIN_MASK;
            #endif /* (to_comp_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (to_comp_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (to_comp_TX_SDA_MISO_PIN)
                hsiomSel[to_comp_TX_SDA_MISO_PIN_INDEX] = to_comp_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [to_comp_TX_SDA_MISO_PIN_INDEX] = to_comp_PIN_DM_OD_LO;
            #endif /* (to_comp_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (to_comp_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (to_comp_RX_SCL_MOSI_PIN)
                    hsiomSel[to_comp_RX_SCL_MOSI_PIN_INDEX] = to_comp_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [to_comp_RX_SCL_MOSI_PIN_INDEX] = to_comp_PIN_DM_DIG_HIZ;
                #elif (to_comp_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[to_comp_RX_WAKE_SCL_MOSI_PIN_INDEX] = to_comp_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [to_comp_RX_WAKE_SCL_MOSI_PIN_INDEX] = to_comp_PIN_DM_DIG_HIZ;
                #else
                #endif /* (to_comp_RX_SCL_MOSI_PIN) */
                }

                if (0u != (to_comp_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (to_comp_TX_SDA_MISO_PIN)
                    hsiomSel[to_comp_TX_SDA_MISO_PIN_INDEX] = to_comp_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [to_comp_TX_SDA_MISO_PIN_INDEX] = to_comp_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= to_comp_TX_SDA_MISO_PIN_MASK;
                #endif /* (to_comp_TX_SDA_MISO_PIN) */
                }

            #if !(to_comp_CY_SCBIP_V0 || to_comp_CY_SCBIP_V1)
                if (to_comp_UART_MODE_STD == subMode)
                {
                    if (0u != (to_comp_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (to_comp_CTS_SCLK_PIN)
                        hsiomSel[to_comp_CTS_SCLK_PIN_INDEX] = to_comp_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [to_comp_CTS_SCLK_PIN_INDEX] = to_comp_PIN_DM_DIG_HIZ;
                    #endif /* (to_comp_CTS_SCLK_PIN) */
                    }

                    if (0u != (to_comp_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (to_comp_RTS_SS0_PIN)
                        hsiomSel[to_comp_RTS_SS0_PIN_INDEX] = to_comp_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [to_comp_RTS_SS0_PIN_INDEX] = to_comp_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= to_comp_RTS_SS0_PIN_MASK;
                    #endif /* (to_comp_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(to_comp_CY_SCBIP_V0 || to_comp_CY_SCBIP_V1) */
            }
        }
    #endif /* (!to_comp_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (to_comp_RX_SCL_MOSI_PIN)
        to_comp_SET_HSIOM_SEL(to_comp_RX_SCL_MOSI_HSIOM_REG,
                                       to_comp_RX_SCL_MOSI_HSIOM_MASK,
                                       to_comp_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[to_comp_RX_SCL_MOSI_PIN_INDEX]);

        to_comp_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[to_comp_RX_SCL_MOSI_PIN_INDEX]);

        #if (!to_comp_CY_SCBIP_V1)
            to_comp_SET_INP_DIS(to_comp_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         to_comp_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & to_comp_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!to_comp_CY_SCBIP_V1) */
    
    #elif (to_comp_RX_WAKE_SCL_MOSI_PIN)
        to_comp_SET_HSIOM_SEL(to_comp_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       to_comp_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       to_comp_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[to_comp_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        to_comp_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[to_comp_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        to_comp_SET_INP_DIS(to_comp_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     to_comp_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & to_comp_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        to_comp_SET_INCFG_TYPE(to_comp_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        to_comp_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        to_comp_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        to_comp_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (to_comp_RX_WAKE_SCL_MOSI_PIN) */

    #if (to_comp_TX_SDA_MISO_PIN)
        to_comp_SET_HSIOM_SEL(to_comp_TX_SDA_MISO_HSIOM_REG,
                                       to_comp_TX_SDA_MISO_HSIOM_MASK,
                                       to_comp_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[to_comp_TX_SDA_MISO_PIN_INDEX]);

        to_comp_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[to_comp_TX_SDA_MISO_PIN_INDEX]);

    #if (!to_comp_CY_SCBIP_V1)
        to_comp_SET_INP_DIS(to_comp_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     to_comp_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & to_comp_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!to_comp_CY_SCBIP_V1) */
    #endif /* (to_comp_RX_SCL_MOSI_PIN) */

    #if (to_comp_CTS_SCLK_PIN)
        to_comp_SET_HSIOM_SEL(to_comp_CTS_SCLK_HSIOM_REG,
                                       to_comp_CTS_SCLK_HSIOM_MASK,
                                       to_comp_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[to_comp_CTS_SCLK_PIN_INDEX]);

        to_comp_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[to_comp_CTS_SCLK_PIN_INDEX]);

        to_comp_SET_INP_DIS(to_comp_uart_cts_spi_sclk_INP_DIS,
                                     to_comp_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & to_comp_CTS_SCLK_PIN_MASK)));
    #endif /* (to_comp_CTS_SCLK_PIN) */

    #if (to_comp_RTS_SS0_PIN)
        to_comp_SET_HSIOM_SEL(to_comp_RTS_SS0_HSIOM_REG,
                                       to_comp_RTS_SS0_HSIOM_MASK,
                                       to_comp_RTS_SS0_HSIOM_POS,
                                       hsiomSel[to_comp_RTS_SS0_PIN_INDEX]);

        to_comp_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[to_comp_RTS_SS0_PIN_INDEX]);

        to_comp_SET_INP_DIS(to_comp_uart_rts_spi_ss0_INP_DIS,
                                     to_comp_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & to_comp_RTS_SS0_PIN_MASK)));
    #endif /* (to_comp_RTS_SS0_PIN) */

    #if (to_comp_SS1_PIN)
        to_comp_SET_HSIOM_SEL(to_comp_SS1_HSIOM_REG,
                                       to_comp_SS1_HSIOM_MASK,
                                       to_comp_SS1_HSIOM_POS,
                                       hsiomSel[to_comp_SS1_PIN_INDEX]);

        to_comp_spi_ss1_SetDriveMode((uint8) pinsDm[to_comp_SS1_PIN_INDEX]);

        to_comp_SET_INP_DIS(to_comp_spi_ss1_INP_DIS,
                                     to_comp_spi_ss1_MASK,
                                     (0u != (pinsInBuf & to_comp_SS1_PIN_MASK)));
    #endif /* (to_comp_SS1_PIN) */

    #if (to_comp_SS2_PIN)
        to_comp_SET_HSIOM_SEL(to_comp_SS2_HSIOM_REG,
                                       to_comp_SS2_HSIOM_MASK,
                                       to_comp_SS2_HSIOM_POS,
                                       hsiomSel[to_comp_SS2_PIN_INDEX]);

        to_comp_spi_ss2_SetDriveMode((uint8) pinsDm[to_comp_SS2_PIN_INDEX]);

        to_comp_SET_INP_DIS(to_comp_spi_ss2_INP_DIS,
                                     to_comp_spi_ss2_MASK,
                                     (0u != (pinsInBuf & to_comp_SS2_PIN_MASK)));
    #endif /* (to_comp_SS2_PIN) */

    #if (to_comp_SS3_PIN)
        to_comp_SET_HSIOM_SEL(to_comp_SS3_HSIOM_REG,
                                       to_comp_SS3_HSIOM_MASK,
                                       to_comp_SS3_HSIOM_POS,
                                       hsiomSel[to_comp_SS3_PIN_INDEX]);

        to_comp_spi_ss3_SetDriveMode((uint8) pinsDm[to_comp_SS3_PIN_INDEX]);

        to_comp_SET_INP_DIS(to_comp_spi_ss3_INP_DIS,
                                     to_comp_spi_ss3_MASK,
                                     (0u != (pinsInBuf & to_comp_SS3_PIN_MASK)));
    #endif /* (to_comp_SS3_PIN) */
    }

#endif /* (to_comp_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (to_comp_CY_SCBIP_V0 || to_comp_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: to_comp_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void to_comp_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (to_comp_CTRL_REG & to_comp_CTRL_EC_AM_MODE)) &&
            (0u == (to_comp_I2C_CTRL_REG & to_comp_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            to_comp_CTRL_REG &= ~to_comp_CTRL_EC_AM_MODE;
            to_comp_CTRL_REG |=  to_comp_CTRL_EC_AM_MODE;
        }

        to_comp_I2C_SLAVE_CMD_REG = to_comp_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (to_comp_CY_SCBIP_V0 || to_comp_CY_SCBIP_V1) */


/* [] END OF FILE */
