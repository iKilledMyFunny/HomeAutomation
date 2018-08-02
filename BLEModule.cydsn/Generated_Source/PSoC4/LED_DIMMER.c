/*******************************************************************************
* File Name: LED_DIMMER.c
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

#include "LED_DIMMER.h"

/* Error message for removed <resource> through optimization */
#ifdef LED_DIMMER_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* LED_DIMMER_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 LED_DIMMER_initVar = 0u;


/*******************************************************************************
* Function Name: LED_DIMMER_Start
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
*  LED_DIMMER_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void LED_DIMMER_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(LED_DIMMER_initVar == 0u)
    {
        LED_DIMMER_Init();
        LED_DIMMER_initVar = 1u;
    }
    LED_DIMMER_Enable();

}


/*******************************************************************************
* Function Name: LED_DIMMER_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  LED_DIMMER_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LED_DIMMER_Init(void) 
{
    #if (LED_DIMMER_UsingFixedFunction || LED_DIMMER_UseControl)
        uint8 ctrl;
    #endif /* (LED_DIMMER_UsingFixedFunction || LED_DIMMER_UseControl) */

    #if(!LED_DIMMER_UsingFixedFunction)
        #if(LED_DIMMER_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 LED_DIMMER_interruptState;
        #endif /* (LED_DIMMER_UseStatus) */
    #endif /* (!LED_DIMMER_UsingFixedFunction) */

    #if (LED_DIMMER_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        LED_DIMMER_CONTROL |= LED_DIMMER_CFG0_MODE;
        #if (LED_DIMMER_DeadBand2_4)
            LED_DIMMER_CONTROL |= LED_DIMMER_CFG0_DB;
        #endif /* (LED_DIMMER_DeadBand2_4) */

        ctrl = LED_DIMMER_CONTROL3 & ((uint8 )(~LED_DIMMER_CTRL_CMPMODE1_MASK));
        LED_DIMMER_CONTROL3 = ctrl | LED_DIMMER_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        LED_DIMMER_RT1 &= ((uint8)(~LED_DIMMER_RT1_MASK));
        LED_DIMMER_RT1 |= LED_DIMMER_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        LED_DIMMER_RT1 &= ((uint8)(~LED_DIMMER_SYNCDSI_MASK));
        LED_DIMMER_RT1 |= LED_DIMMER_SYNCDSI_EN;

    #elif (LED_DIMMER_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = LED_DIMMER_CONTROL & ((uint8)(~LED_DIMMER_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~LED_DIMMER_CTRL_CMPMODE1_MASK));
        LED_DIMMER_CONTROL = ctrl | LED_DIMMER_DEFAULT_COMPARE2_MODE |
                                   LED_DIMMER_DEFAULT_COMPARE1_MODE;
    #endif /* (LED_DIMMER_UsingFixedFunction) */

    #if (!LED_DIMMER_UsingFixedFunction)
        #if (LED_DIMMER_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            LED_DIMMER_AUX_CONTROLDP0 |= (LED_DIMMER_AUX_CTRL_FIFO0_CLR);
        #else /* (LED_DIMMER_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            LED_DIMMER_AUX_CONTROLDP0 |= (LED_DIMMER_AUX_CTRL_FIFO0_CLR);
            LED_DIMMER_AUX_CONTROLDP1 |= (LED_DIMMER_AUX_CTRL_FIFO0_CLR);
        #endif /* (LED_DIMMER_Resolution == 8) */

        LED_DIMMER_WriteCounter(LED_DIMMER_INIT_PERIOD_VALUE);
    #endif /* (!LED_DIMMER_UsingFixedFunction) */

    LED_DIMMER_WritePeriod(LED_DIMMER_INIT_PERIOD_VALUE);

        #if (LED_DIMMER_UseOneCompareMode)
            LED_DIMMER_WriteCompare(LED_DIMMER_INIT_COMPARE_VALUE1);
        #else
            LED_DIMMER_WriteCompare1(LED_DIMMER_INIT_COMPARE_VALUE1);
            LED_DIMMER_WriteCompare2(LED_DIMMER_INIT_COMPARE_VALUE2);
        #endif /* (LED_DIMMER_UseOneCompareMode) */

        #if (LED_DIMMER_KillModeMinTime)
            LED_DIMMER_WriteKillTime(LED_DIMMER_MinimumKillTime);
        #endif /* (LED_DIMMER_KillModeMinTime) */

        #if (LED_DIMMER_DeadBandUsed)
            LED_DIMMER_WriteDeadTime(LED_DIMMER_INIT_DEAD_TIME);
        #endif /* (LED_DIMMER_DeadBandUsed) */

    #if (LED_DIMMER_UseStatus || LED_DIMMER_UsingFixedFunction)
        LED_DIMMER_SetInterruptMode(LED_DIMMER_INIT_INTERRUPTS_MODE);
    #endif /* (LED_DIMMER_UseStatus || LED_DIMMER_UsingFixedFunction) */

    #if (LED_DIMMER_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        LED_DIMMER_GLOBAL_ENABLE |= LED_DIMMER_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        LED_DIMMER_CONTROL2 |= LED_DIMMER_CTRL2_IRQ_SEL;
    #else
        #if(LED_DIMMER_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            LED_DIMMER_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            LED_DIMMER_STATUS_AUX_CTRL |= LED_DIMMER_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(LED_DIMMER_interruptState);

            /* Clear the FIFO to enable the LED_DIMMER_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            LED_DIMMER_ClearFIFO();
        #endif /* (LED_DIMMER_UseStatus) */
    #endif /* (LED_DIMMER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LED_DIMMER_Enable
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
void LED_DIMMER_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (LED_DIMMER_UsingFixedFunction)
        LED_DIMMER_GLOBAL_ENABLE |= LED_DIMMER_BLOCK_EN_MASK;
        LED_DIMMER_GLOBAL_STBY_ENABLE |= LED_DIMMER_BLOCK_STBY_EN_MASK;
    #endif /* (LED_DIMMER_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (LED_DIMMER_UseControl || LED_DIMMER_UsingFixedFunction)
        LED_DIMMER_CONTROL |= LED_DIMMER_CTRL_ENABLE;
    #endif /* (LED_DIMMER_UseControl || LED_DIMMER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LED_DIMMER_Stop
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
void LED_DIMMER_Stop(void) 
{
    #if (LED_DIMMER_UseControl || LED_DIMMER_UsingFixedFunction)
        LED_DIMMER_CONTROL &= ((uint8)(~LED_DIMMER_CTRL_ENABLE));
    #endif /* (LED_DIMMER_UseControl || LED_DIMMER_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (LED_DIMMER_UsingFixedFunction)
        LED_DIMMER_GLOBAL_ENABLE &= ((uint8)(~LED_DIMMER_BLOCK_EN_MASK));
        LED_DIMMER_GLOBAL_STBY_ENABLE &= ((uint8)(~LED_DIMMER_BLOCK_STBY_EN_MASK));
    #endif /* (LED_DIMMER_UsingFixedFunction) */
}

#if (LED_DIMMER_UseOneCompareMode)
    #if (LED_DIMMER_CompareMode1SW)


        /*******************************************************************************
        * Function Name: LED_DIMMER_SetCompareMode
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
        void LED_DIMMER_SetCompareMode(uint8 comparemode) 
        {
            #if(LED_DIMMER_UsingFixedFunction)

                #if(0 != LED_DIMMER_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << LED_DIMMER_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != LED_DIMMER_CTRL_CMPMODE1_SHIFT) */

                LED_DIMMER_CONTROL3 &= ((uint8)(~LED_DIMMER_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                LED_DIMMER_CONTROL3 |= comparemodemasked;

            #elif (LED_DIMMER_UseControl)

                #if(0 != LED_DIMMER_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << LED_DIMMER_CTRL_CMPMODE1_SHIFT)) &
                                                LED_DIMMER_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & LED_DIMMER_CTRL_CMPMODE1_MASK;
                #endif /* (0 != LED_DIMMER_CTRL_CMPMODE1_SHIFT) */

                #if(0 != LED_DIMMER_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << LED_DIMMER_CTRL_CMPMODE2_SHIFT)) &
                                               LED_DIMMER_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & LED_DIMMER_CTRL_CMPMODE2_MASK;
                #endif /* (0 != LED_DIMMER_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                LED_DIMMER_CONTROL &= ((uint8)(~(LED_DIMMER_CTRL_CMPMODE1_MASK |
                                            LED_DIMMER_CTRL_CMPMODE2_MASK)));
                LED_DIMMER_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (LED_DIMMER_UsingFixedFunction) */
        }
    #endif /* LED_DIMMER_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (LED_DIMMER_CompareMode1SW)


        /*******************************************************************************
        * Function Name: LED_DIMMER_SetCompareMode1
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
        void LED_DIMMER_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != LED_DIMMER_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << LED_DIMMER_CTRL_CMPMODE1_SHIFT)) &
                                           LED_DIMMER_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & LED_DIMMER_CTRL_CMPMODE1_MASK;
            #endif /* (0 != LED_DIMMER_CTRL_CMPMODE1_SHIFT) */

            #if (LED_DIMMER_UseControl)
                LED_DIMMER_CONTROL &= ((uint8)(~LED_DIMMER_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                LED_DIMMER_CONTROL |= comparemodemasked;
            #endif /* (LED_DIMMER_UseControl) */
        }
    #endif /* LED_DIMMER_CompareMode1SW */

#if (LED_DIMMER_CompareMode2SW)


    /*******************************************************************************
    * Function Name: LED_DIMMER_SetCompareMode2
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
    void LED_DIMMER_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != LED_DIMMER_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << LED_DIMMER_CTRL_CMPMODE2_SHIFT)) &
                                                 LED_DIMMER_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & LED_DIMMER_CTRL_CMPMODE2_MASK;
        #endif /* (0 != LED_DIMMER_CTRL_CMPMODE2_SHIFT) */

        #if (LED_DIMMER_UseControl)
            LED_DIMMER_CONTROL &= ((uint8)(~LED_DIMMER_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            LED_DIMMER_CONTROL |= comparemodemasked;
        #endif /* (LED_DIMMER_UseControl) */
    }
    #endif /*LED_DIMMER_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!LED_DIMMER_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: LED_DIMMER_WriteCounter
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
    void LED_DIMMER_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(LED_DIMMER_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: LED_DIMMER_ReadCounter
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
    uint16 LED_DIMMER_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(LED_DIMMER_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(LED_DIMMER_CAPTURE_LSB_PTR));
    }

    #if (LED_DIMMER_UseStatus)


        /*******************************************************************************
        * Function Name: LED_DIMMER_ClearFIFO
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
        void LED_DIMMER_ClearFIFO(void) 
        {
            while(0u != (LED_DIMMER_ReadStatusRegister() & LED_DIMMER_STATUS_FIFONEMPTY))
            {
                (void)LED_DIMMER_ReadCapture();
            }
        }

    #endif /* LED_DIMMER_UseStatus */

#endif /* !LED_DIMMER_UsingFixedFunction */


/*******************************************************************************
* Function Name: LED_DIMMER_WritePeriod
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
void LED_DIMMER_WritePeriod(uint16 period) 
{
    #if(LED_DIMMER_UsingFixedFunction)
        CY_SET_REG16(LED_DIMMER_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(LED_DIMMER_PERIOD_LSB_PTR, period);
    #endif /* (LED_DIMMER_UsingFixedFunction) */
}

#if (LED_DIMMER_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: LED_DIMMER_WriteCompare
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
    void LED_DIMMER_WriteCompare(uint16 compare) \
                                       
    {
        #if(LED_DIMMER_UsingFixedFunction)
            CY_SET_REG16(LED_DIMMER_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(LED_DIMMER_COMPARE1_LSB_PTR, compare);
        #endif /* (LED_DIMMER_UsingFixedFunction) */

        #if (LED_DIMMER_PWMMode == LED_DIMMER__B_PWM__DITHER)
            #if(LED_DIMMER_UsingFixedFunction)
                CY_SET_REG16(LED_DIMMER_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(LED_DIMMER_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (LED_DIMMER_UsingFixedFunction) */
        #endif /* (LED_DIMMER_PWMMode == LED_DIMMER__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: LED_DIMMER_WriteCompare1
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
    void LED_DIMMER_WriteCompare1(uint16 compare) \
                                        
    {
        #if(LED_DIMMER_UsingFixedFunction)
            CY_SET_REG16(LED_DIMMER_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(LED_DIMMER_COMPARE1_LSB_PTR, compare);
        #endif /* (LED_DIMMER_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: LED_DIMMER_WriteCompare2
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
    void LED_DIMMER_WriteCompare2(uint16 compare) \
                                        
    {
        #if(LED_DIMMER_UsingFixedFunction)
            CY_SET_REG16(LED_DIMMER_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(LED_DIMMER_COMPARE2_LSB_PTR, compare);
        #endif /* (LED_DIMMER_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (LED_DIMMER_DeadBandUsed)


    /*******************************************************************************
    * Function Name: LED_DIMMER_WriteDeadTime
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
    void LED_DIMMER_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!LED_DIMMER_DeadBand2_4)
            CY_SET_REG8(LED_DIMMER_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            LED_DIMMER_DEADBAND_COUNT &= ((uint8)(~LED_DIMMER_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(LED_DIMMER_DEADBAND_COUNT_SHIFT)
                LED_DIMMER_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << LED_DIMMER_DEADBAND_COUNT_SHIFT)) &
                                                    LED_DIMMER_DEADBAND_COUNT_MASK;
            #else
                LED_DIMMER_DEADBAND_COUNT |= deadtime & LED_DIMMER_DEADBAND_COUNT_MASK;
            #endif /* (LED_DIMMER_DEADBAND_COUNT_SHIFT) */

        #endif /* (!LED_DIMMER_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: LED_DIMMER_ReadDeadTime
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
    uint8 LED_DIMMER_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!LED_DIMMER_DeadBand2_4)
            return (CY_GET_REG8(LED_DIMMER_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(LED_DIMMER_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(LED_DIMMER_DEADBAND_COUNT & LED_DIMMER_DEADBAND_COUNT_MASK)) >>
                                                                           LED_DIMMER_DEADBAND_COUNT_SHIFT));
            #else
                return (LED_DIMMER_DEADBAND_COUNT & LED_DIMMER_DEADBAND_COUNT_MASK);
            #endif /* (LED_DIMMER_DEADBAND_COUNT_SHIFT) */
        #endif /* (!LED_DIMMER_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (LED_DIMMER_UseStatus || LED_DIMMER_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: LED_DIMMER_SetInterruptMode
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
    void LED_DIMMER_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(LED_DIMMER_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: LED_DIMMER_ReadStatusRegister
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
    uint8 LED_DIMMER_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(LED_DIMMER_STATUS_PTR));
    }

#endif /* (LED_DIMMER_UseStatus || LED_DIMMER_UsingFixedFunction) */


#if (LED_DIMMER_UseControl)


    /*******************************************************************************
    * Function Name: LED_DIMMER_ReadControlRegister
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
    uint8 LED_DIMMER_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(LED_DIMMER_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: LED_DIMMER_WriteControlRegister
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
    void LED_DIMMER_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(LED_DIMMER_CONTROL_PTR, control);
    }

#endif /* (LED_DIMMER_UseControl) */


#if (!LED_DIMMER_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: LED_DIMMER_ReadCapture
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
    uint16 LED_DIMMER_ReadCapture(void) 
    {
        return (CY_GET_REG16(LED_DIMMER_CAPTURE_LSB_PTR));
    }

#endif /* (!LED_DIMMER_UsingFixedFunction) */


#if (LED_DIMMER_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: LED_DIMMER_ReadCompare
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
    uint16 LED_DIMMER_ReadCompare(void) 
    {
        #if(LED_DIMMER_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(LED_DIMMER_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(LED_DIMMER_COMPARE1_LSB_PTR));
        #endif /* (LED_DIMMER_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: LED_DIMMER_ReadCompare1
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
    uint16 LED_DIMMER_ReadCompare1(void) 
    {
        return (CY_GET_REG16(LED_DIMMER_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: LED_DIMMER_ReadCompare2
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
    uint16 LED_DIMMER_ReadCompare2(void) 
    {
        return (CY_GET_REG16(LED_DIMMER_COMPARE2_LSB_PTR));
    }

#endif /* (LED_DIMMER_UseOneCompareMode) */


/*******************************************************************************
* Function Name: LED_DIMMER_ReadPeriod
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
uint16 LED_DIMMER_ReadPeriod(void) 
{
    #if(LED_DIMMER_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(LED_DIMMER_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(LED_DIMMER_PERIOD_LSB_PTR));
    #endif /* (LED_DIMMER_UsingFixedFunction) */
}

#if ( LED_DIMMER_KillModeMinTime)


    /*******************************************************************************
    * Function Name: LED_DIMMER_WriteKillTime
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
    void LED_DIMMER_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(LED_DIMMER_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: LED_DIMMER_ReadKillTime
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
    uint8 LED_DIMMER_ReadKillTime(void) 
    {
        return (CY_GET_REG8(LED_DIMMER_KILLMODEMINTIME_PTR));
    }

#endif /* ( LED_DIMMER_KillModeMinTime) */

/* [] END OF FILE */
