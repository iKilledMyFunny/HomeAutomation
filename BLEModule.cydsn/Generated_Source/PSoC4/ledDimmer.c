/*******************************************************************************
* File Name: ledDimmer.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "ledDimmer.h"

/* Error message for removed <resource> through optimization */
#ifdef ledDimmer_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* ledDimmer_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 ledDimmer_initVar = 0u;


/*******************************************************************************
* Function Name: ledDimmer_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ledDimmer_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ledDimmer_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(ledDimmer_initVar == 0u)
    {
        ledDimmer_Init();
        ledDimmer_initVar = 1u;
    }
    ledDimmer_Enable();

}


/*******************************************************************************
* Function Name: ledDimmer_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  ledDimmer_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ledDimmer_Init(void) 
{
    #if (ledDimmer_UsingFixedFunction || ledDimmer_UseControl)
        uint8 ctrl;
    #endif /* (ledDimmer_UsingFixedFunction || ledDimmer_UseControl) */

    #if(!ledDimmer_UsingFixedFunction)
        #if(ledDimmer_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 ledDimmer_interruptState;
        #endif /* (ledDimmer_UseStatus) */
    #endif /* (!ledDimmer_UsingFixedFunction) */

    #if (ledDimmer_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        ledDimmer_CONTROL |= ledDimmer_CFG0_MODE;
        #if (ledDimmer_DeadBand2_4)
            ledDimmer_CONTROL |= ledDimmer_CFG0_DB;
        #endif /* (ledDimmer_DeadBand2_4) */

        ctrl = ledDimmer_CONTROL3 & ((uint8 )(~ledDimmer_CTRL_CMPMODE1_MASK));
        ledDimmer_CONTROL3 = ctrl | ledDimmer_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        ledDimmer_RT1 &= ((uint8)(~ledDimmer_RT1_MASK));
        ledDimmer_RT1 |= ledDimmer_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        ledDimmer_RT1 &= ((uint8)(~ledDimmer_SYNCDSI_MASK));
        ledDimmer_RT1 |= ledDimmer_SYNCDSI_EN;

    #elif (ledDimmer_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = ledDimmer_CONTROL & ((uint8)(~ledDimmer_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~ledDimmer_CTRL_CMPMODE1_MASK));
        ledDimmer_CONTROL = ctrl | ledDimmer_DEFAULT_COMPARE2_MODE |
                                   ledDimmer_DEFAULT_COMPARE1_MODE;
    #endif /* (ledDimmer_UsingFixedFunction) */

    #if (!ledDimmer_UsingFixedFunction)
        #if (ledDimmer_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            ledDimmer_AUX_CONTROLDP0 |= (ledDimmer_AUX_CTRL_FIFO0_CLR);
        #else /* (ledDimmer_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            ledDimmer_AUX_CONTROLDP0 |= (ledDimmer_AUX_CTRL_FIFO0_CLR);
            ledDimmer_AUX_CONTROLDP1 |= (ledDimmer_AUX_CTRL_FIFO0_CLR);
        #endif /* (ledDimmer_Resolution == 8) */

        ledDimmer_WriteCounter(ledDimmer_INIT_PERIOD_VALUE);
    #endif /* (!ledDimmer_UsingFixedFunction) */

    ledDimmer_WritePeriod(ledDimmer_INIT_PERIOD_VALUE);

        #if (ledDimmer_UseOneCompareMode)
            ledDimmer_WriteCompare(ledDimmer_INIT_COMPARE_VALUE1);
        #else
            ledDimmer_WriteCompare1(ledDimmer_INIT_COMPARE_VALUE1);
            ledDimmer_WriteCompare2(ledDimmer_INIT_COMPARE_VALUE2);
        #endif /* (ledDimmer_UseOneCompareMode) */

        #if (ledDimmer_KillModeMinTime)
            ledDimmer_WriteKillTime(ledDimmer_MinimumKillTime);
        #endif /* (ledDimmer_KillModeMinTime) */

        #if (ledDimmer_DeadBandUsed)
            ledDimmer_WriteDeadTime(ledDimmer_INIT_DEAD_TIME);
        #endif /* (ledDimmer_DeadBandUsed) */

    #if (ledDimmer_UseStatus || ledDimmer_UsingFixedFunction)
        ledDimmer_SetInterruptMode(ledDimmer_INIT_INTERRUPTS_MODE);
    #endif /* (ledDimmer_UseStatus || ledDimmer_UsingFixedFunction) */

    #if (ledDimmer_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        ledDimmer_GLOBAL_ENABLE |= ledDimmer_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        ledDimmer_CONTROL2 |= ledDimmer_CTRL2_IRQ_SEL;
    #else
        #if(ledDimmer_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            ledDimmer_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            ledDimmer_STATUS_AUX_CTRL |= ledDimmer_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(ledDimmer_interruptState);

            /* Clear the FIFO to enable the ledDimmer_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            ledDimmer_ClearFIFO();
        #endif /* (ledDimmer_UseStatus) */
    #endif /* (ledDimmer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ledDimmer_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void ledDimmer_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (ledDimmer_UsingFixedFunction)
        ledDimmer_GLOBAL_ENABLE |= ledDimmer_BLOCK_EN_MASK;
        ledDimmer_GLOBAL_STBY_ENABLE |= ledDimmer_BLOCK_STBY_EN_MASK;
    #endif /* (ledDimmer_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (ledDimmer_UseControl || ledDimmer_UsingFixedFunction)
        ledDimmer_CONTROL |= ledDimmer_CTRL_ENABLE;
    #endif /* (ledDimmer_UseControl || ledDimmer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ledDimmer_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void ledDimmer_Stop(void) 
{
    #if (ledDimmer_UseControl || ledDimmer_UsingFixedFunction)
        ledDimmer_CONTROL &= ((uint8)(~ledDimmer_CTRL_ENABLE));
    #endif /* (ledDimmer_UseControl || ledDimmer_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (ledDimmer_UsingFixedFunction)
        ledDimmer_GLOBAL_ENABLE &= ((uint8)(~ledDimmer_BLOCK_EN_MASK));
        ledDimmer_GLOBAL_STBY_ENABLE &= ((uint8)(~ledDimmer_BLOCK_STBY_EN_MASK));
    #endif /* (ledDimmer_UsingFixedFunction) */
}

#if (ledDimmer_UseOneCompareMode)
    #if (ledDimmer_CompareMode1SW)


        /*******************************************************************************
        * Function Name: ledDimmer_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ledDimmer_SetCompareMode(uint8 comparemode) 
        {
            #if(ledDimmer_UsingFixedFunction)

                #if(0 != ledDimmer_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << ledDimmer_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != ledDimmer_CTRL_CMPMODE1_SHIFT) */

                ledDimmer_CONTROL3 &= ((uint8)(~ledDimmer_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                ledDimmer_CONTROL3 |= comparemodemasked;

            #elif (ledDimmer_UseControl)

                #if(0 != ledDimmer_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << ledDimmer_CTRL_CMPMODE1_SHIFT)) &
                                                ledDimmer_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & ledDimmer_CTRL_CMPMODE1_MASK;
                #endif /* (0 != ledDimmer_CTRL_CMPMODE1_SHIFT) */

                #if(0 != ledDimmer_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << ledDimmer_CTRL_CMPMODE2_SHIFT)) &
                                               ledDimmer_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & ledDimmer_CTRL_CMPMODE2_MASK;
                #endif /* (0 != ledDimmer_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                ledDimmer_CONTROL &= ((uint8)(~(ledDimmer_CTRL_CMPMODE1_MASK |
                                            ledDimmer_CTRL_CMPMODE2_MASK)));
                ledDimmer_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (ledDimmer_UsingFixedFunction) */
        }
    #endif /* ledDimmer_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (ledDimmer_CompareMode1SW)


        /*******************************************************************************
        * Function Name: ledDimmer_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ledDimmer_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != ledDimmer_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << ledDimmer_CTRL_CMPMODE1_SHIFT)) &
                                           ledDimmer_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & ledDimmer_CTRL_CMPMODE1_MASK;
            #endif /* (0 != ledDimmer_CTRL_CMPMODE1_SHIFT) */

            #if (ledDimmer_UseControl)
                ledDimmer_CONTROL &= ((uint8)(~ledDimmer_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                ledDimmer_CONTROL |= comparemodemasked;
            #endif /* (ledDimmer_UseControl) */
        }
    #endif /* ledDimmer_CompareMode1SW */

#if (ledDimmer_CompareMode2SW)


    /*******************************************************************************
    * Function Name: ledDimmer_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ledDimmer_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != ledDimmer_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << ledDimmer_CTRL_CMPMODE2_SHIFT)) &
                                                 ledDimmer_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & ledDimmer_CTRL_CMPMODE2_MASK;
        #endif /* (0 != ledDimmer_CTRL_CMPMODE2_SHIFT) */

        #if (ledDimmer_UseControl)
            ledDimmer_CONTROL &= ((uint8)(~ledDimmer_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            ledDimmer_CONTROL |= comparemodemasked;
        #endif /* (ledDimmer_UseControl) */
    }
    #endif /*ledDimmer_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!ledDimmer_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: ledDimmer_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void ledDimmer_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(ledDimmer_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: ledDimmer_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 ledDimmer_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(ledDimmer_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(ledDimmer_CAPTURE_LSB_PTR));
    }

    #if (ledDimmer_UseStatus)


        /*******************************************************************************
        * Function Name: ledDimmer_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ledDimmer_ClearFIFO(void) 
        {
            while(0u != (ledDimmer_ReadStatusRegister() & ledDimmer_STATUS_FIFONEMPTY))
            {
                (void)ledDimmer_ReadCapture();
            }
        }

    #endif /* ledDimmer_UseStatus */

#endif /* !ledDimmer_UsingFixedFunction */


/*******************************************************************************
* Function Name: ledDimmer_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void ledDimmer_WritePeriod(uint16 period) 
{
    #if(ledDimmer_UsingFixedFunction)
        CY_SET_REG16(ledDimmer_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(ledDimmer_PERIOD_LSB_PTR, period);
    #endif /* (ledDimmer_UsingFixedFunction) */
}

#if (ledDimmer_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: ledDimmer_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void ledDimmer_WriteCompare(uint16 compare) \
                                       
    {
        #if(ledDimmer_UsingFixedFunction)
            CY_SET_REG16(ledDimmer_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(ledDimmer_COMPARE1_LSB_PTR, compare);
        #endif /* (ledDimmer_UsingFixedFunction) */

        #if (ledDimmer_PWMMode == ledDimmer__B_PWM__DITHER)
            #if(ledDimmer_UsingFixedFunction)
                CY_SET_REG16(ledDimmer_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(ledDimmer_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (ledDimmer_UsingFixedFunction) */
        #endif /* (ledDimmer_PWMMode == ledDimmer__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: ledDimmer_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ledDimmer_WriteCompare1(uint16 compare) \
                                        
    {
        #if(ledDimmer_UsingFixedFunction)
            CY_SET_REG16(ledDimmer_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(ledDimmer_COMPARE1_LSB_PTR, compare);
        #endif /* (ledDimmer_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: ledDimmer_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ledDimmer_WriteCompare2(uint16 compare) \
                                        
    {
        #if(ledDimmer_UsingFixedFunction)
            CY_SET_REG16(ledDimmer_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(ledDimmer_COMPARE2_LSB_PTR, compare);
        #endif /* (ledDimmer_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (ledDimmer_DeadBandUsed)


    /*******************************************************************************
    * Function Name: ledDimmer_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ledDimmer_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!ledDimmer_DeadBand2_4)
            CY_SET_REG8(ledDimmer_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            ledDimmer_DEADBAND_COUNT &= ((uint8)(~ledDimmer_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(ledDimmer_DEADBAND_COUNT_SHIFT)
                ledDimmer_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << ledDimmer_DEADBAND_COUNT_SHIFT)) &
                                                    ledDimmer_DEADBAND_COUNT_MASK;
            #else
                ledDimmer_DEADBAND_COUNT |= deadtime & ledDimmer_DEADBAND_COUNT_MASK;
            #endif /* (ledDimmer_DEADBAND_COUNT_SHIFT) */

        #endif /* (!ledDimmer_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: ledDimmer_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 ledDimmer_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!ledDimmer_DeadBand2_4)
            return (CY_GET_REG8(ledDimmer_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(ledDimmer_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(ledDimmer_DEADBAND_COUNT & ledDimmer_DEADBAND_COUNT_MASK)) >>
                                                                           ledDimmer_DEADBAND_COUNT_SHIFT));
            #else
                return (ledDimmer_DEADBAND_COUNT & ledDimmer_DEADBAND_COUNT_MASK);
            #endif /* (ledDimmer_DEADBAND_COUNT_SHIFT) */
        #endif /* (!ledDimmer_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (ledDimmer_UseStatus || ledDimmer_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: ledDimmer_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ledDimmer_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(ledDimmer_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: ledDimmer_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 ledDimmer_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(ledDimmer_STATUS_PTR));
    }

#endif /* (ledDimmer_UseStatus || ledDimmer_UsingFixedFunction) */


#if (ledDimmer_UseControl)


    /*******************************************************************************
    * Function Name: ledDimmer_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 ledDimmer_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(ledDimmer_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: ledDimmer_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ledDimmer_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(ledDimmer_CONTROL_PTR, control);
    }

#endif /* (ledDimmer_UseControl) */


#if (!ledDimmer_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: ledDimmer_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 ledDimmer_ReadCapture(void) 
    {
        return (CY_GET_REG16(ledDimmer_CAPTURE_LSB_PTR));
    }

#endif /* (!ledDimmer_UsingFixedFunction) */


#if (ledDimmer_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: ledDimmer_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 ledDimmer_ReadCompare(void) 
    {
        #if(ledDimmer_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(ledDimmer_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(ledDimmer_COMPARE1_LSB_PTR));
        #endif /* (ledDimmer_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: ledDimmer_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 ledDimmer_ReadCompare1(void) 
    {
        return (CY_GET_REG16(ledDimmer_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: ledDimmer_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 ledDimmer_ReadCompare2(void) 
    {
        return (CY_GET_REG16(ledDimmer_COMPARE2_LSB_PTR));
    }

#endif /* (ledDimmer_UseOneCompareMode) */


/*******************************************************************************
* Function Name: ledDimmer_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 ledDimmer_ReadPeriod(void) 
{
    #if(ledDimmer_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(ledDimmer_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(ledDimmer_PERIOD_LSB_PTR));
    #endif /* (ledDimmer_UsingFixedFunction) */
}

#if ( ledDimmer_KillModeMinTime)


    /*******************************************************************************
    * Function Name: ledDimmer_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ledDimmer_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(ledDimmer_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: ledDimmer_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 ledDimmer_ReadKillTime(void) 
    {
        return (CY_GET_REG8(ledDimmer_KILLMODEMINTIME_PTR));
    }

#endif /* ( ledDimmer_KillModeMinTime) */

/* [] END OF FILE */
