/*******************************************************************************
* File Name: DebounceTimer.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the DebounceTimer
*  component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DebounceTimer.h"

uint8 DebounceTimer_initVar = 0u;


/*******************************************************************************
* Function Name: DebounceTimer_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default DebounceTimer configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (DebounceTimer__QUAD == DebounceTimer_CONFIG)
        DebounceTimer_CONTROL_REG = DebounceTimer_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        DebounceTimer_TRIG_CONTROL1_REG  = DebounceTimer_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        DebounceTimer_SetInterruptMode(DebounceTimer_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        DebounceTimer_SetCounterMode(DebounceTimer_COUNT_DOWN);
        DebounceTimer_WritePeriod(DebounceTimer_QUAD_PERIOD_INIT_VALUE);
        DebounceTimer_WriteCounter(DebounceTimer_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (DebounceTimer__QUAD == DebounceTimer_CONFIG) */

    #if (DebounceTimer__TIMER == DebounceTimer_CONFIG)
        DebounceTimer_CONTROL_REG = DebounceTimer_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        DebounceTimer_TRIG_CONTROL1_REG  = DebounceTimer_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        DebounceTimer_SetInterruptMode(DebounceTimer_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        DebounceTimer_WritePeriod(DebounceTimer_TC_PERIOD_VALUE );

        #if (DebounceTimer__COMPARE == DebounceTimer_TC_COMP_CAP_MODE)
            DebounceTimer_WriteCompare(DebounceTimer_TC_COMPARE_VALUE);

            #if (1u == DebounceTimer_TC_COMPARE_SWAP)
                DebounceTimer_SetCompareSwap(1u);
                DebounceTimer_WriteCompareBuf(DebounceTimer_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == DebounceTimer_TC_COMPARE_SWAP) */
        #endif  /* (DebounceTimer__COMPARE == DebounceTimer_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (DebounceTimer_CY_TCPWM_V2 && DebounceTimer_TIMER_UPDOWN_CNT_USED && !DebounceTimer_CY_TCPWM_4000)
            DebounceTimer_WriteCounter(1u);
        #elif(DebounceTimer__COUNT_DOWN == DebounceTimer_TC_COUNTER_MODE)
            DebounceTimer_WriteCounter(DebounceTimer_TC_PERIOD_VALUE);
        #else
            DebounceTimer_WriteCounter(0u);
        #endif /* (DebounceTimer_CY_TCPWM_V2 && DebounceTimer_TIMER_UPDOWN_CNT_USED && !DebounceTimer_CY_TCPWM_4000) */
    #endif  /* (DebounceTimer__TIMER == DebounceTimer_CONFIG) */

    #if (DebounceTimer__PWM_SEL == DebounceTimer_CONFIG)
        DebounceTimer_CONTROL_REG = DebounceTimer_CTRL_PWM_BASE_CONFIG;

        #if (DebounceTimer__PWM_PR == DebounceTimer_PWM_MODE)
            DebounceTimer_CONTROL_REG |= DebounceTimer_CTRL_PWM_RUN_MODE;
            DebounceTimer_WriteCounter(DebounceTimer_PWM_PR_INIT_VALUE);
        #else
            DebounceTimer_CONTROL_REG |= DebounceTimer_CTRL_PWM_ALIGN | DebounceTimer_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (DebounceTimer_CY_TCPWM_V2 && DebounceTimer_PWM_UPDOWN_CNT_USED && !DebounceTimer_CY_TCPWM_4000)
                DebounceTimer_WriteCounter(1u);
            #elif (DebounceTimer__RIGHT == DebounceTimer_PWM_ALIGN)
                DebounceTimer_WriteCounter(DebounceTimer_PWM_PERIOD_VALUE);
            #else 
                DebounceTimer_WriteCounter(0u);
            #endif  /* (DebounceTimer_CY_TCPWM_V2 && DebounceTimer_PWM_UPDOWN_CNT_USED && !DebounceTimer_CY_TCPWM_4000) */
        #endif  /* (DebounceTimer__PWM_PR == DebounceTimer_PWM_MODE) */

        #if (DebounceTimer__PWM_DT == DebounceTimer_PWM_MODE)
            DebounceTimer_CONTROL_REG |= DebounceTimer_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (DebounceTimer__PWM_DT == DebounceTimer_PWM_MODE) */

        #if (DebounceTimer__PWM == DebounceTimer_PWM_MODE)
            DebounceTimer_CONTROL_REG |= DebounceTimer_CTRL_PWM_PRESCALER;
        #endif  /* (DebounceTimer__PWM == DebounceTimer_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        DebounceTimer_TRIG_CONTROL1_REG  = DebounceTimer_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        DebounceTimer_SetInterruptMode(DebounceTimer_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (DebounceTimer__PWM_PR == DebounceTimer_PWM_MODE)
            DebounceTimer_TRIG_CONTROL2_REG =
                    (DebounceTimer_CC_MATCH_NO_CHANGE    |
                    DebounceTimer_OVERLOW_NO_CHANGE      |
                    DebounceTimer_UNDERFLOW_NO_CHANGE);
        #else
            #if (DebounceTimer__LEFT == DebounceTimer_PWM_ALIGN)
                DebounceTimer_TRIG_CONTROL2_REG = DebounceTimer_PWM_MODE_LEFT;
            #endif  /* ( DebounceTimer_PWM_LEFT == DebounceTimer_PWM_ALIGN) */

            #if (DebounceTimer__RIGHT == DebounceTimer_PWM_ALIGN)
                DebounceTimer_TRIG_CONTROL2_REG = DebounceTimer_PWM_MODE_RIGHT;
            #endif  /* ( DebounceTimer_PWM_RIGHT == DebounceTimer_PWM_ALIGN) */

            #if (DebounceTimer__CENTER == DebounceTimer_PWM_ALIGN)
                DebounceTimer_TRIG_CONTROL2_REG = DebounceTimer_PWM_MODE_CENTER;
            #endif  /* ( DebounceTimer_PWM_CENTER == DebounceTimer_PWM_ALIGN) */

            #if (DebounceTimer__ASYMMETRIC == DebounceTimer_PWM_ALIGN)
                DebounceTimer_TRIG_CONTROL2_REG = DebounceTimer_PWM_MODE_ASYM;
            #endif  /* (DebounceTimer__ASYMMETRIC == DebounceTimer_PWM_ALIGN) */
        #endif  /* (DebounceTimer__PWM_PR == DebounceTimer_PWM_MODE) */

        /* Set other values from customizer */
        DebounceTimer_WritePeriod(DebounceTimer_PWM_PERIOD_VALUE );
        DebounceTimer_WriteCompare(DebounceTimer_PWM_COMPARE_VALUE);

        #if (1u == DebounceTimer_PWM_COMPARE_SWAP)
            DebounceTimer_SetCompareSwap(1u);
            DebounceTimer_WriteCompareBuf(DebounceTimer_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == DebounceTimer_PWM_COMPARE_SWAP) */

        #if (1u == DebounceTimer_PWM_PERIOD_SWAP)
            DebounceTimer_SetPeriodSwap(1u);
            DebounceTimer_WritePeriodBuf(DebounceTimer_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == DebounceTimer_PWM_PERIOD_SWAP) */
    #endif  /* (DebounceTimer__PWM_SEL == DebounceTimer_CONFIG) */
    
}


/*******************************************************************************
* Function Name: DebounceTimer_Enable
********************************************************************************
*
* Summary:
*  Enables the DebounceTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    DebounceTimer_BLOCK_CONTROL_REG |= DebounceTimer_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (DebounceTimer__PWM_SEL == DebounceTimer_CONFIG)
        #if (0u == DebounceTimer_PWM_START_SIGNAL_PRESENT)
            DebounceTimer_TriggerCommand(DebounceTimer_MASK, DebounceTimer_CMD_START);
        #endif /* (0u == DebounceTimer_PWM_START_SIGNAL_PRESENT) */
    #endif /* (DebounceTimer__PWM_SEL == DebounceTimer_CONFIG) */

    #if (DebounceTimer__TIMER == DebounceTimer_CONFIG)
        #if (0u == DebounceTimer_TC_START_SIGNAL_PRESENT)
            DebounceTimer_TriggerCommand(DebounceTimer_MASK, DebounceTimer_CMD_START);
        #endif /* (0u == DebounceTimer_TC_START_SIGNAL_PRESENT) */
    #endif /* (DebounceTimer__TIMER == DebounceTimer_CONFIG) */
    
    #if (DebounceTimer__QUAD == DebounceTimer_CONFIG)
        #if (0u != DebounceTimer_QUAD_AUTO_START)
            DebounceTimer_TriggerCommand(DebounceTimer_MASK, DebounceTimer_CMD_RELOAD);
        #endif /* (0u != DebounceTimer_QUAD_AUTO_START) */
    #endif  /* (DebounceTimer__QUAD == DebounceTimer_CONFIG) */
}


/*******************************************************************************
* Function Name: DebounceTimer_Start
********************************************************************************
*
* Summary:
*  Initializes the DebounceTimer with default customizer
*  values when called the first time and enables the DebounceTimer.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  DebounceTimer_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time DebounceTimer_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the DebounceTimer_Start() routine.
*
*******************************************************************************/
void DebounceTimer_Start(void)
{
    if (0u == DebounceTimer_initVar)
    {
        DebounceTimer_Init();
        DebounceTimer_initVar = 1u;
    }

    DebounceTimer_Enable();
}


/*******************************************************************************
* Function Name: DebounceTimer_Stop
********************************************************************************
*
* Summary:
*  Disables the DebounceTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_BLOCK_CONTROL_REG &= (uint32)~DebounceTimer_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the DebounceTimer. This function is used when
*  configured as a generic DebounceTimer and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the DebounceTimer to operate in
*   Values:
*   - DebounceTimer_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - DebounceTimer_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - DebounceTimer_MODE_QUAD - Quadrature decoder
*         - DebounceTimer_MODE_PWM - PWM
*         - DebounceTimer_MODE_PWM_DT - PWM with dead time
*         - DebounceTimer_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_CONTROL_REG &= (uint32)~DebounceTimer_MODE_MASK;
    DebounceTimer_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - DebounceTimer_MODE_X1 - Counts on phi 1 rising
*         - DebounceTimer_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - DebounceTimer_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_CONTROL_REG &= (uint32)~DebounceTimer_QUAD_MODE_MASK;
    DebounceTimer_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - DebounceTimer_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - DebounceTimer_PRESCALE_DIVBY2    - Divide by 2
*         - DebounceTimer_PRESCALE_DIVBY4    - Divide by 4
*         - DebounceTimer_PRESCALE_DIVBY8    - Divide by 8
*         - DebounceTimer_PRESCALE_DIVBY16   - Divide by 16
*         - DebounceTimer_PRESCALE_DIVBY32   - Divide by 32
*         - DebounceTimer_PRESCALE_DIVBY64   - Divide by 64
*         - DebounceTimer_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_CONTROL_REG &= (uint32)~DebounceTimer_PRESCALER_MASK;
    DebounceTimer_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the DebounceTimer runs
*  continuously or stops when terminal count is reached.  By default the
*  DebounceTimer operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_CONTROL_REG &= (uint32)~DebounceTimer_ONESHOT_MASK;
    DebounceTimer_CONTROL_REG |= ((uint32)((oneShotEnable & DebounceTimer_1BIT_MASK) <<
                                                               DebounceTimer_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetPWMMode(uint32 modeMask)
{
    DebounceTimer_TRIG_CONTROL2_REG = (modeMask & DebounceTimer_6BIT_MASK);
}



/*******************************************************************************
* Function Name: DebounceTimer_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_CONTROL_REG &= (uint32)~DebounceTimer_PWM_SYNC_KILL_MASK;
    DebounceTimer_CONTROL_REG |= ((uint32)((syncKillEnable & DebounceTimer_1BIT_MASK)  <<
                                               DebounceTimer_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_CONTROL_REG &= (uint32)~DebounceTimer_PWM_STOP_KILL_MASK;
    DebounceTimer_CONTROL_REG |= ((uint32)((stopOnKillEnable & DebounceTimer_1BIT_MASK)  <<
                                                         DebounceTimer_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_CONTROL_REG &= (uint32)~DebounceTimer_PRESCALER_MASK;
    DebounceTimer_CONTROL_REG |= ((uint32)((deadTime & DebounceTimer_8BIT_MASK) <<
                                                          DebounceTimer_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - DebounceTimer_INVERT_LINE   - Inverts the line output
*         - DebounceTimer_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_CONTROL_REG &= (uint32)~DebounceTimer_INV_OUT_MASK;
    DebounceTimer_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: DebounceTimer_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_WriteCounter(uint32 count)
{
    DebounceTimer_COUNTER_REG = (count & DebounceTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: DebounceTimer_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 DebounceTimer_ReadCounter(void)
{
    return (DebounceTimer_COUNTER_REG & DebounceTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - DebounceTimer_COUNT_UP       - Counts up
*     - DebounceTimer_COUNT_DOWN     - Counts down
*     - DebounceTimer_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - DebounceTimer_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_CONTROL_REG &= (uint32)~DebounceTimer_UPDOWN_MASK;
    DebounceTimer_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_WritePeriod(uint32 period)
{
    DebounceTimer_PERIOD_REG = (period & DebounceTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: DebounceTimer_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 DebounceTimer_ReadPeriod(void)
{
    return (DebounceTimer_PERIOD_REG & DebounceTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_CONTROL_REG &= (uint32)~DebounceTimer_RELOAD_CC_MASK;
    DebounceTimer_CONTROL_REG |= (swapEnable & DebounceTimer_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_WritePeriodBuf(uint32 periodBuf)
{
    DebounceTimer_PERIOD_BUF_REG = (periodBuf & DebounceTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: DebounceTimer_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 DebounceTimer_ReadPeriodBuf(void)
{
    return (DebounceTimer_PERIOD_BUF_REG & DebounceTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_CONTROL_REG &= (uint32)~DebounceTimer_RELOAD_PERIOD_MASK;
    DebounceTimer_CONTROL_REG |= ((uint32)((swapEnable & DebounceTimer_1BIT_MASK) <<
                                                            DebounceTimer_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void DebounceTimer_WriteCompare(uint32 compare)
{
    #if (DebounceTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (DebounceTimer_CY_TCPWM_4000) */

    #if (DebounceTimer_CY_TCPWM_4000)
        currentMode = ((DebounceTimer_CONTROL_REG & DebounceTimer_UPDOWN_MASK) >> DebounceTimer_UPDOWN_SHIFT);

        if (((uint32)DebounceTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)DebounceTimer__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (DebounceTimer_CY_TCPWM_4000) */
    
    DebounceTimer_COMP_CAP_REG = (compare & DebounceTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: DebounceTimer_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 DebounceTimer_ReadCompare(void)
{
    #if (DebounceTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (DebounceTimer_CY_TCPWM_4000) */

    #if (DebounceTimer_CY_TCPWM_4000)
        currentMode = ((DebounceTimer_CONTROL_REG & DebounceTimer_UPDOWN_MASK) >> DebounceTimer_UPDOWN_SHIFT);
        
        regVal = DebounceTimer_COMP_CAP_REG;
        
        if (((uint32)DebounceTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)DebounceTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & DebounceTimer_16BIT_MASK);
    #else
        return (DebounceTimer_COMP_CAP_REG & DebounceTimer_16BIT_MASK);
    #endif /* (DebounceTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: DebounceTimer_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void DebounceTimer_WriteCompareBuf(uint32 compareBuf)
{
    #if (DebounceTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (DebounceTimer_CY_TCPWM_4000) */

    #if (DebounceTimer_CY_TCPWM_4000)
        currentMode = ((DebounceTimer_CONTROL_REG & DebounceTimer_UPDOWN_MASK) >> DebounceTimer_UPDOWN_SHIFT);

        if (((uint32)DebounceTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)DebounceTimer__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (DebounceTimer_CY_TCPWM_4000) */
    
    DebounceTimer_COMP_CAP_BUF_REG = (compareBuf & DebounceTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: DebounceTimer_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 DebounceTimer_ReadCompareBuf(void)
{
    #if (DebounceTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (DebounceTimer_CY_TCPWM_4000) */

    #if (DebounceTimer_CY_TCPWM_4000)
        currentMode = ((DebounceTimer_CONTROL_REG & DebounceTimer_UPDOWN_MASK) >> DebounceTimer_UPDOWN_SHIFT);

        regVal = DebounceTimer_COMP_CAP_BUF_REG;
        
        if (((uint32)DebounceTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)DebounceTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & DebounceTimer_16BIT_MASK);
    #else
        return (DebounceTimer_COMP_CAP_BUF_REG & DebounceTimer_16BIT_MASK);
    #endif /* (DebounceTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: DebounceTimer_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 DebounceTimer_ReadCapture(void)
{
    return (DebounceTimer_COMP_CAP_REG & DebounceTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: DebounceTimer_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 DebounceTimer_ReadCaptureBuf(void)
{
    return (DebounceTimer_COMP_CAP_BUF_REG & DebounceTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - DebounceTimer_TRIG_LEVEL     - Level
*     - DebounceTimer_TRIG_RISING    - Rising edge
*     - DebounceTimer_TRIG_FALLING   - Falling edge
*     - DebounceTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_TRIG_CONTROL1_REG &= (uint32)~DebounceTimer_CAPTURE_MASK;
    DebounceTimer_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - DebounceTimer_TRIG_LEVEL     - Level
*     - DebounceTimer_TRIG_RISING    - Rising edge
*     - DebounceTimer_TRIG_FALLING   - Falling edge
*     - DebounceTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_TRIG_CONTROL1_REG &= (uint32)~DebounceTimer_RELOAD_MASK;
    DebounceTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << DebounceTimer_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - DebounceTimer_TRIG_LEVEL     - Level
*     - DebounceTimer_TRIG_RISING    - Rising edge
*     - DebounceTimer_TRIG_FALLING   - Falling edge
*     - DebounceTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_TRIG_CONTROL1_REG &= (uint32)~DebounceTimer_START_MASK;
    DebounceTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << DebounceTimer_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - DebounceTimer_TRIG_LEVEL     - Level
*     - DebounceTimer_TRIG_RISING    - Rising edge
*     - DebounceTimer_TRIG_FALLING   - Falling edge
*     - DebounceTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_TRIG_CONTROL1_REG &= (uint32)~DebounceTimer_STOP_MASK;
    DebounceTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << DebounceTimer_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - DebounceTimer_TRIG_LEVEL     - Level
*     - DebounceTimer_TRIG_RISING    - Rising edge
*     - DebounceTimer_TRIG_FALLING   - Falling edge
*     - DebounceTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_TRIG_CONTROL1_REG &= (uint32)~DebounceTimer_COUNT_MASK;
    DebounceTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << DebounceTimer_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - DebounceTimer_CMD_CAPTURE    - Trigger Capture/Switch command
*     - DebounceTimer_CMD_RELOAD     - Trigger Reload/Index command
*     - DebounceTimer_CMD_STOP       - Trigger Stop/Kill command
*     - DebounceTimer_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    DebounceTimer_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DebounceTimer_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the DebounceTimer.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - DebounceTimer_STATUS_DOWN    - Set if counting down
*     - DebounceTimer_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 DebounceTimer_ReadStatus(void)
{
    return ((DebounceTimer_STATUS_REG >> DebounceTimer_RUNNING_STATUS_SHIFT) |
            (DebounceTimer_STATUS_REG & DebounceTimer_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: DebounceTimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - DebounceTimer_INTR_MASK_TC       - Terminal count mask
*     - DebounceTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetInterruptMode(uint32 interruptMask)
{
    DebounceTimer_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: DebounceTimer_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - DebounceTimer_INTR_MASK_TC       - Terminal count mask
*     - DebounceTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 DebounceTimer_GetInterruptSourceMasked(void)
{
    return (DebounceTimer_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: DebounceTimer_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - DebounceTimer_INTR_MASK_TC       - Terminal count mask
*     - DebounceTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 DebounceTimer_GetInterruptSource(void)
{
    return (DebounceTimer_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: DebounceTimer_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - DebounceTimer_INTR_MASK_TC       - Terminal count mask
*     - DebounceTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_ClearInterrupt(uint32 interruptMask)
{
    DebounceTimer_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: DebounceTimer_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - DebounceTimer_INTR_MASK_TC       - Terminal count mask
*     - DebounceTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void DebounceTimer_SetInterrupt(uint32 interruptMask)
{
    DebounceTimer_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
