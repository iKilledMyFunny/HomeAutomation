/*******************************************************************************
* File Name: DebounceTimer.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the DebounceTimer
*  component.
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

#if !defined(CY_TCPWM_DebounceTimer_H)
#define CY_TCPWM_DebounceTimer_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} DebounceTimer_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  DebounceTimer_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define DebounceTimer_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define DebounceTimer_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define DebounceTimer_CONFIG                         (8lu)

/* Quad Mode */
/* Parameters */
#define DebounceTimer_QUAD_ENCODING_MODES            (0lu)
#define DebounceTimer_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define DebounceTimer_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define DebounceTimer_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define DebounceTimer_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define DebounceTimer_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define DebounceTimer_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define DebounceTimer_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define DebounceTimer_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define DebounceTimer_TC_RUN_MODE                    (0lu)
#define DebounceTimer_TC_COUNTER_MODE                (0lu)
#define DebounceTimer_TC_COMP_CAP_MODE               (2lu)
#define DebounceTimer_TC_PRESCALER                   (0lu)

/* Signal modes */
#define DebounceTimer_TC_RELOAD_SIGNAL_MODE          (1lu)
#define DebounceTimer_TC_COUNT_SIGNAL_MODE           (3lu)
#define DebounceTimer_TC_START_SIGNAL_MODE           (1lu)
#define DebounceTimer_TC_STOP_SIGNAL_MODE            (0lu)
#define DebounceTimer_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define DebounceTimer_TC_RELOAD_SIGNAL_PRESENT       (1lu)
#define DebounceTimer_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define DebounceTimer_TC_START_SIGNAL_PRESENT        (1lu)
#define DebounceTimer_TC_STOP_SIGNAL_PRESENT         (1lu)
#define DebounceTimer_TC_CAPTURE_SIGNAL_PRESENT      (1lu)

/* Interrupt Mask */
#define DebounceTimer_TC_INTERRUPT_MASK              (2lu)

/* PWM Mode */
/* Parameters */
#define DebounceTimer_PWM_KILL_EVENT                 (0lu)
#define DebounceTimer_PWM_STOP_EVENT                 (0lu)
#define DebounceTimer_PWM_MODE                       (4lu)
#define DebounceTimer_PWM_OUT_N_INVERT               (0lu)
#define DebounceTimer_PWM_OUT_INVERT                 (0lu)
#define DebounceTimer_PWM_ALIGN                      (0lu)
#define DebounceTimer_PWM_RUN_MODE                   (0lu)
#define DebounceTimer_PWM_DEAD_TIME_CYCLE            (0lu)
#define DebounceTimer_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define DebounceTimer_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define DebounceTimer_PWM_COUNT_SIGNAL_MODE          (3lu)
#define DebounceTimer_PWM_START_SIGNAL_MODE          (0lu)
#define DebounceTimer_PWM_STOP_SIGNAL_MODE           (0lu)
#define DebounceTimer_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define DebounceTimer_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define DebounceTimer_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define DebounceTimer_PWM_START_SIGNAL_PRESENT       (0lu)
#define DebounceTimer_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define DebounceTimer_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define DebounceTimer_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define DebounceTimer_TC_PERIOD_VALUE                (65535lu)
#define DebounceTimer_TC_COMPARE_VALUE               (65535lu)
#define DebounceTimer_TC_COMPARE_BUF_VALUE           (65535lu)
#define DebounceTimer_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define DebounceTimer_PWM_PERIOD_VALUE               (65535lu)
#define DebounceTimer_PWM_PERIOD_BUF_VALUE           (65535lu)
#define DebounceTimer_PWM_PERIOD_SWAP                (0lu)
#define DebounceTimer_PWM_COMPARE_VALUE              (65535lu)
#define DebounceTimer_PWM_COMPARE_BUF_VALUE          (65535lu)
#define DebounceTimer_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define DebounceTimer__LEFT 0
#define DebounceTimer__RIGHT 1
#define DebounceTimer__CENTER 2
#define DebounceTimer__ASYMMETRIC 3

#define DebounceTimer__X1 0
#define DebounceTimer__X2 1
#define DebounceTimer__X4 2

#define DebounceTimer__PWM 4
#define DebounceTimer__PWM_DT 5
#define DebounceTimer__PWM_PR 6

#define DebounceTimer__INVERSE 1
#define DebounceTimer__DIRECT 0

#define DebounceTimer__CAPTURE 2
#define DebounceTimer__COMPARE 0

#define DebounceTimer__TRIG_LEVEL 3
#define DebounceTimer__TRIG_RISING 0
#define DebounceTimer__TRIG_FALLING 1
#define DebounceTimer__TRIG_BOTH 2

#define DebounceTimer__INTR_MASK_TC 1
#define DebounceTimer__INTR_MASK_CC_MATCH 2
#define DebounceTimer__INTR_MASK_NONE 0
#define DebounceTimer__INTR_MASK_TC_CC 3

#define DebounceTimer__UNCONFIG 8
#define DebounceTimer__TIMER 1
#define DebounceTimer__QUAD 3
#define DebounceTimer__PWM_SEL 7

#define DebounceTimer__COUNT_UP 0
#define DebounceTimer__COUNT_DOWN 1
#define DebounceTimer__COUNT_UPDOWN0 2
#define DebounceTimer__COUNT_UPDOWN1 3


/* Prescaler */
#define DebounceTimer_PRESCALE_DIVBY1                ((uint32)(0u << DebounceTimer_PRESCALER_SHIFT))
#define DebounceTimer_PRESCALE_DIVBY2                ((uint32)(1u << DebounceTimer_PRESCALER_SHIFT))
#define DebounceTimer_PRESCALE_DIVBY4                ((uint32)(2u << DebounceTimer_PRESCALER_SHIFT))
#define DebounceTimer_PRESCALE_DIVBY8                ((uint32)(3u << DebounceTimer_PRESCALER_SHIFT))
#define DebounceTimer_PRESCALE_DIVBY16               ((uint32)(4u << DebounceTimer_PRESCALER_SHIFT))
#define DebounceTimer_PRESCALE_DIVBY32               ((uint32)(5u << DebounceTimer_PRESCALER_SHIFT))
#define DebounceTimer_PRESCALE_DIVBY64               ((uint32)(6u << DebounceTimer_PRESCALER_SHIFT))
#define DebounceTimer_PRESCALE_DIVBY128              ((uint32)(7u << DebounceTimer_PRESCALER_SHIFT))

/* TCPWM set modes */
#define DebounceTimer_MODE_TIMER_COMPARE             ((uint32)(DebounceTimer__COMPARE         <<  \
                                                                  DebounceTimer_MODE_SHIFT))
#define DebounceTimer_MODE_TIMER_CAPTURE             ((uint32)(DebounceTimer__CAPTURE         <<  \
                                                                  DebounceTimer_MODE_SHIFT))
#define DebounceTimer_MODE_QUAD                      ((uint32)(DebounceTimer__QUAD            <<  \
                                                                  DebounceTimer_MODE_SHIFT))
#define DebounceTimer_MODE_PWM                       ((uint32)(DebounceTimer__PWM             <<  \
                                                                  DebounceTimer_MODE_SHIFT))
#define DebounceTimer_MODE_PWM_DT                    ((uint32)(DebounceTimer__PWM_DT          <<  \
                                                                  DebounceTimer_MODE_SHIFT))
#define DebounceTimer_MODE_PWM_PR                    ((uint32)(DebounceTimer__PWM_PR          <<  \
                                                                  DebounceTimer_MODE_SHIFT))

/* Quad Modes */
#define DebounceTimer_MODE_X1                        ((uint32)(DebounceTimer__X1              <<  \
                                                                  DebounceTimer_QUAD_MODE_SHIFT))
#define DebounceTimer_MODE_X2                        ((uint32)(DebounceTimer__X2              <<  \
                                                                  DebounceTimer_QUAD_MODE_SHIFT))
#define DebounceTimer_MODE_X4                        ((uint32)(DebounceTimer__X4              <<  \
                                                                  DebounceTimer_QUAD_MODE_SHIFT))

/* Counter modes */
#define DebounceTimer_COUNT_UP                       ((uint32)(DebounceTimer__COUNT_UP        <<  \
                                                                  DebounceTimer_UPDOWN_SHIFT))
#define DebounceTimer_COUNT_DOWN                     ((uint32)(DebounceTimer__COUNT_DOWN      <<  \
                                                                  DebounceTimer_UPDOWN_SHIFT))
#define DebounceTimer_COUNT_UPDOWN0                  ((uint32)(DebounceTimer__COUNT_UPDOWN0   <<  \
                                                                  DebounceTimer_UPDOWN_SHIFT))
#define DebounceTimer_COUNT_UPDOWN1                  ((uint32)(DebounceTimer__COUNT_UPDOWN1   <<  \
                                                                  DebounceTimer_UPDOWN_SHIFT))

/* PWM output invert */
#define DebounceTimer_INVERT_LINE                    ((uint32)(DebounceTimer__INVERSE         <<  \
                                                                  DebounceTimer_INV_OUT_SHIFT))
#define DebounceTimer_INVERT_LINE_N                  ((uint32)(DebounceTimer__INVERSE         <<  \
                                                                  DebounceTimer_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define DebounceTimer_TRIG_RISING                    ((uint32)DebounceTimer__TRIG_RISING)
#define DebounceTimer_TRIG_FALLING                   ((uint32)DebounceTimer__TRIG_FALLING)
#define DebounceTimer_TRIG_BOTH                      ((uint32)DebounceTimer__TRIG_BOTH)
#define DebounceTimer_TRIG_LEVEL                     ((uint32)DebounceTimer__TRIG_LEVEL)

/* Interrupt mask */
#define DebounceTimer_INTR_MASK_TC                   ((uint32)DebounceTimer__INTR_MASK_TC)
#define DebounceTimer_INTR_MASK_CC_MATCH             ((uint32)DebounceTimer__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define DebounceTimer_CC_MATCH_SET                   (0x00u)
#define DebounceTimer_CC_MATCH_CLEAR                 (0x01u)
#define DebounceTimer_CC_MATCH_INVERT                (0x02u)
#define DebounceTimer_CC_MATCH_NO_CHANGE             (0x03u)
#define DebounceTimer_OVERLOW_SET                    (0x00u)
#define DebounceTimer_OVERLOW_CLEAR                  (0x04u)
#define DebounceTimer_OVERLOW_INVERT                 (0x08u)
#define DebounceTimer_OVERLOW_NO_CHANGE              (0x0Cu)
#define DebounceTimer_UNDERFLOW_SET                  (0x00u)
#define DebounceTimer_UNDERFLOW_CLEAR                (0x10u)
#define DebounceTimer_UNDERFLOW_INVERT               (0x20u)
#define DebounceTimer_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define DebounceTimer_PWM_MODE_LEFT                  (DebounceTimer_CC_MATCH_CLEAR        |   \
                                                         DebounceTimer_OVERLOW_SET           |   \
                                                         DebounceTimer_UNDERFLOW_NO_CHANGE)
#define DebounceTimer_PWM_MODE_RIGHT                 (DebounceTimer_CC_MATCH_SET          |   \
                                                         DebounceTimer_OVERLOW_NO_CHANGE     |   \
                                                         DebounceTimer_UNDERFLOW_CLEAR)
#define DebounceTimer_PWM_MODE_ASYM                  (DebounceTimer_CC_MATCH_INVERT       |   \
                                                         DebounceTimer_OVERLOW_SET           |   \
                                                         DebounceTimer_UNDERFLOW_CLEAR)

#if (DebounceTimer_CY_TCPWM_V2)
    #if(DebounceTimer_CY_TCPWM_4000)
        #define DebounceTimer_PWM_MODE_CENTER                (DebounceTimer_CC_MATCH_INVERT       |   \
                                                                 DebounceTimer_OVERLOW_NO_CHANGE     |   \
                                                                 DebounceTimer_UNDERFLOW_CLEAR)
    #else
        #define DebounceTimer_PWM_MODE_CENTER                (DebounceTimer_CC_MATCH_INVERT       |   \
                                                                 DebounceTimer_OVERLOW_SET           |   \
                                                                 DebounceTimer_UNDERFLOW_CLEAR)
    #endif /* (DebounceTimer_CY_TCPWM_4000) */
#else
    #define DebounceTimer_PWM_MODE_CENTER                (DebounceTimer_CC_MATCH_INVERT       |   \
                                                             DebounceTimer_OVERLOW_NO_CHANGE     |   \
                                                             DebounceTimer_UNDERFLOW_CLEAR)
#endif /* (DebounceTimer_CY_TCPWM_NEW) */

/* Command operations without condition */
#define DebounceTimer_CMD_CAPTURE                    (0u)
#define DebounceTimer_CMD_RELOAD                     (8u)
#define DebounceTimer_CMD_STOP                       (16u)
#define DebounceTimer_CMD_START                      (24u)

/* Status */
#define DebounceTimer_STATUS_DOWN                    (1u)
#define DebounceTimer_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   DebounceTimer_Init(void);
void   DebounceTimer_Enable(void);
void   DebounceTimer_Start(void);
void   DebounceTimer_Stop(void);

void   DebounceTimer_SetMode(uint32 mode);
void   DebounceTimer_SetCounterMode(uint32 counterMode);
void   DebounceTimer_SetPWMMode(uint32 modeMask);
void   DebounceTimer_SetQDMode(uint32 qdMode);

void   DebounceTimer_SetPrescaler(uint32 prescaler);
void   DebounceTimer_TriggerCommand(uint32 mask, uint32 command);
void   DebounceTimer_SetOneShot(uint32 oneShotEnable);
uint32 DebounceTimer_ReadStatus(void);

void   DebounceTimer_SetPWMSyncKill(uint32 syncKillEnable);
void   DebounceTimer_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   DebounceTimer_SetPWMDeadTime(uint32 deadTime);
void   DebounceTimer_SetPWMInvert(uint32 mask);

void   DebounceTimer_SetInterruptMode(uint32 interruptMask);
uint32 DebounceTimer_GetInterruptSourceMasked(void);
uint32 DebounceTimer_GetInterruptSource(void);
void   DebounceTimer_ClearInterrupt(uint32 interruptMask);
void   DebounceTimer_SetInterrupt(uint32 interruptMask);

void   DebounceTimer_WriteCounter(uint32 count);
uint32 DebounceTimer_ReadCounter(void);

uint32 DebounceTimer_ReadCapture(void);
uint32 DebounceTimer_ReadCaptureBuf(void);

void   DebounceTimer_WritePeriod(uint32 period);
uint32 DebounceTimer_ReadPeriod(void);
void   DebounceTimer_WritePeriodBuf(uint32 periodBuf);
uint32 DebounceTimer_ReadPeriodBuf(void);

void   DebounceTimer_WriteCompare(uint32 compare);
uint32 DebounceTimer_ReadCompare(void);
void   DebounceTimer_WriteCompareBuf(uint32 compareBuf);
uint32 DebounceTimer_ReadCompareBuf(void);

void   DebounceTimer_SetPeriodSwap(uint32 swapEnable);
void   DebounceTimer_SetCompareSwap(uint32 swapEnable);

void   DebounceTimer_SetCaptureMode(uint32 triggerMode);
void   DebounceTimer_SetReloadMode(uint32 triggerMode);
void   DebounceTimer_SetStartMode(uint32 triggerMode);
void   DebounceTimer_SetStopMode(uint32 triggerMode);
void   DebounceTimer_SetCountMode(uint32 triggerMode);

void   DebounceTimer_SaveConfig(void);
void   DebounceTimer_RestoreConfig(void);
void   DebounceTimer_Sleep(void);
void   DebounceTimer_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define DebounceTimer_BLOCK_CONTROL_REG              (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define DebounceTimer_BLOCK_CONTROL_PTR              ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define DebounceTimer_COMMAND_REG                    (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define DebounceTimer_COMMAND_PTR                    ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define DebounceTimer_INTRRUPT_CAUSE_REG             (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define DebounceTimer_INTRRUPT_CAUSE_PTR             ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define DebounceTimer_CONTROL_REG                    (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__CTRL )
#define DebounceTimer_CONTROL_PTR                    ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__CTRL )
#define DebounceTimer_STATUS_REG                     (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__STATUS )
#define DebounceTimer_STATUS_PTR                     ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__STATUS )
#define DebounceTimer_COUNTER_REG                    (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__COUNTER )
#define DebounceTimer_COUNTER_PTR                    ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__COUNTER )
#define DebounceTimer_COMP_CAP_REG                   (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__CC )
#define DebounceTimer_COMP_CAP_PTR                   ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__CC )
#define DebounceTimer_COMP_CAP_BUF_REG               (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define DebounceTimer_COMP_CAP_BUF_PTR               ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define DebounceTimer_PERIOD_REG                     (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__PERIOD )
#define DebounceTimer_PERIOD_PTR                     ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__PERIOD )
#define DebounceTimer_PERIOD_BUF_REG                 (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define DebounceTimer_PERIOD_BUF_PTR                 ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define DebounceTimer_TRIG_CONTROL0_REG              (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define DebounceTimer_TRIG_CONTROL0_PTR              ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define DebounceTimer_TRIG_CONTROL1_REG              (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define DebounceTimer_TRIG_CONTROL1_PTR              ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define DebounceTimer_TRIG_CONTROL2_REG              (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define DebounceTimer_TRIG_CONTROL2_PTR              ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define DebounceTimer_INTERRUPT_REQ_REG              (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__INTR )
#define DebounceTimer_INTERRUPT_REQ_PTR              ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__INTR )
#define DebounceTimer_INTERRUPT_SET_REG              (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define DebounceTimer_INTERRUPT_SET_PTR              ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define DebounceTimer_INTERRUPT_MASK_REG             (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define DebounceTimer_INTERRUPT_MASK_PTR             ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define DebounceTimer_INTERRUPT_MASKED_REG           (*(reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__INTR_MASKED )
#define DebounceTimer_INTERRUPT_MASKED_PTR           ( (reg32 *) DebounceTimer_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define DebounceTimer_MASK                           ((uint32)DebounceTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define DebounceTimer_RELOAD_CC_SHIFT                (0u)
#define DebounceTimer_RELOAD_PERIOD_SHIFT            (1u)
#define DebounceTimer_PWM_SYNC_KILL_SHIFT            (2u)
#define DebounceTimer_PWM_STOP_KILL_SHIFT            (3u)
#define DebounceTimer_PRESCALER_SHIFT                (8u)
#define DebounceTimer_UPDOWN_SHIFT                   (16u)
#define DebounceTimer_ONESHOT_SHIFT                  (18u)
#define DebounceTimer_QUAD_MODE_SHIFT                (20u)
#define DebounceTimer_INV_OUT_SHIFT                  (20u)
#define DebounceTimer_INV_COMPL_OUT_SHIFT            (21u)
#define DebounceTimer_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define DebounceTimer_RELOAD_CC_MASK                 ((uint32)(DebounceTimer_1BIT_MASK        <<  \
                                                                            DebounceTimer_RELOAD_CC_SHIFT))
#define DebounceTimer_RELOAD_PERIOD_MASK             ((uint32)(DebounceTimer_1BIT_MASK        <<  \
                                                                            DebounceTimer_RELOAD_PERIOD_SHIFT))
#define DebounceTimer_PWM_SYNC_KILL_MASK             ((uint32)(DebounceTimer_1BIT_MASK        <<  \
                                                                            DebounceTimer_PWM_SYNC_KILL_SHIFT))
#define DebounceTimer_PWM_STOP_KILL_MASK             ((uint32)(DebounceTimer_1BIT_MASK        <<  \
                                                                            DebounceTimer_PWM_STOP_KILL_SHIFT))
#define DebounceTimer_PRESCALER_MASK                 ((uint32)(DebounceTimer_8BIT_MASK        <<  \
                                                                            DebounceTimer_PRESCALER_SHIFT))
#define DebounceTimer_UPDOWN_MASK                    ((uint32)(DebounceTimer_2BIT_MASK        <<  \
                                                                            DebounceTimer_UPDOWN_SHIFT))
#define DebounceTimer_ONESHOT_MASK                   ((uint32)(DebounceTimer_1BIT_MASK        <<  \
                                                                            DebounceTimer_ONESHOT_SHIFT))
#define DebounceTimer_QUAD_MODE_MASK                 ((uint32)(DebounceTimer_3BIT_MASK        <<  \
                                                                            DebounceTimer_QUAD_MODE_SHIFT))
#define DebounceTimer_INV_OUT_MASK                   ((uint32)(DebounceTimer_2BIT_MASK        <<  \
                                                                            DebounceTimer_INV_OUT_SHIFT))
#define DebounceTimer_MODE_MASK                      ((uint32)(DebounceTimer_3BIT_MASK        <<  \
                                                                            DebounceTimer_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define DebounceTimer_CAPTURE_SHIFT                  (0u)
#define DebounceTimer_COUNT_SHIFT                    (2u)
#define DebounceTimer_RELOAD_SHIFT                   (4u)
#define DebounceTimer_STOP_SHIFT                     (6u)
#define DebounceTimer_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define DebounceTimer_CAPTURE_MASK                   ((uint32)(DebounceTimer_2BIT_MASK        <<  \
                                                                  DebounceTimer_CAPTURE_SHIFT))
#define DebounceTimer_COUNT_MASK                     ((uint32)(DebounceTimer_2BIT_MASK        <<  \
                                                                  DebounceTimer_COUNT_SHIFT))
#define DebounceTimer_RELOAD_MASK                    ((uint32)(DebounceTimer_2BIT_MASK        <<  \
                                                                  DebounceTimer_RELOAD_SHIFT))
#define DebounceTimer_STOP_MASK                      ((uint32)(DebounceTimer_2BIT_MASK        <<  \
                                                                  DebounceTimer_STOP_SHIFT))
#define DebounceTimer_START_MASK                     ((uint32)(DebounceTimer_2BIT_MASK        <<  \
                                                                  DebounceTimer_START_SHIFT))

/* MASK */
#define DebounceTimer_1BIT_MASK                      ((uint32)0x01u)
#define DebounceTimer_2BIT_MASK                      ((uint32)0x03u)
#define DebounceTimer_3BIT_MASK                      ((uint32)0x07u)
#define DebounceTimer_6BIT_MASK                      ((uint32)0x3Fu)
#define DebounceTimer_8BIT_MASK                      ((uint32)0xFFu)
#define DebounceTimer_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define DebounceTimer_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define DebounceTimer_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(DebounceTimer_QUAD_ENCODING_MODES     << DebounceTimer_QUAD_MODE_SHIFT))       |\
         ((uint32)(DebounceTimer_CONFIG                  << DebounceTimer_MODE_SHIFT)))

#define DebounceTimer_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(DebounceTimer_PWM_STOP_EVENT          << DebounceTimer_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(DebounceTimer_PWM_OUT_INVERT          << DebounceTimer_INV_OUT_SHIFT))         |\
         ((uint32)(DebounceTimer_PWM_OUT_N_INVERT        << DebounceTimer_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(DebounceTimer_PWM_MODE                << DebounceTimer_MODE_SHIFT)))

#define DebounceTimer_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(DebounceTimer_PWM_RUN_MODE         << DebounceTimer_ONESHOT_SHIFT))
            
#define DebounceTimer_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(DebounceTimer_PWM_ALIGN            << DebounceTimer_UPDOWN_SHIFT))

#define DebounceTimer_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(DebounceTimer_PWM_KILL_EVENT      << DebounceTimer_PWM_SYNC_KILL_SHIFT))

#define DebounceTimer_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(DebounceTimer_PWM_DEAD_TIME_CYCLE  << DebounceTimer_PRESCALER_SHIFT))

#define DebounceTimer_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(DebounceTimer_PWM_PRESCALER        << DebounceTimer_PRESCALER_SHIFT))

#define DebounceTimer_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(DebounceTimer_TC_PRESCALER            << DebounceTimer_PRESCALER_SHIFT))       |\
         ((uint32)(DebounceTimer_TC_COUNTER_MODE         << DebounceTimer_UPDOWN_SHIFT))          |\
         ((uint32)(DebounceTimer_TC_RUN_MODE             << DebounceTimer_ONESHOT_SHIFT))         |\
         ((uint32)(DebounceTimer_TC_COMP_CAP_MODE        << DebounceTimer_MODE_SHIFT)))
        
#define DebounceTimer_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(DebounceTimer_QUAD_PHIA_SIGNAL_MODE   << DebounceTimer_COUNT_SHIFT))           |\
         ((uint32)(DebounceTimer_QUAD_INDEX_SIGNAL_MODE  << DebounceTimer_RELOAD_SHIFT))          |\
         ((uint32)(DebounceTimer_QUAD_STOP_SIGNAL_MODE   << DebounceTimer_STOP_SHIFT))            |\
         ((uint32)(DebounceTimer_QUAD_PHIB_SIGNAL_MODE   << DebounceTimer_START_SHIFT)))

#define DebounceTimer_PWM_SIGNALS_MODES                                                              \
        (((uint32)(DebounceTimer_PWM_SWITCH_SIGNAL_MODE  << DebounceTimer_CAPTURE_SHIFT))         |\
         ((uint32)(DebounceTimer_PWM_COUNT_SIGNAL_MODE   << DebounceTimer_COUNT_SHIFT))           |\
         ((uint32)(DebounceTimer_PWM_RELOAD_SIGNAL_MODE  << DebounceTimer_RELOAD_SHIFT))          |\
         ((uint32)(DebounceTimer_PWM_STOP_SIGNAL_MODE    << DebounceTimer_STOP_SHIFT))            |\
         ((uint32)(DebounceTimer_PWM_START_SIGNAL_MODE   << DebounceTimer_START_SHIFT)))

#define DebounceTimer_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(DebounceTimer_TC_CAPTURE_SIGNAL_MODE  << DebounceTimer_CAPTURE_SHIFT))         |\
         ((uint32)(DebounceTimer_TC_COUNT_SIGNAL_MODE    << DebounceTimer_COUNT_SHIFT))           |\
         ((uint32)(DebounceTimer_TC_RELOAD_SIGNAL_MODE   << DebounceTimer_RELOAD_SHIFT))          |\
         ((uint32)(DebounceTimer_TC_STOP_SIGNAL_MODE     << DebounceTimer_STOP_SHIFT))            |\
         ((uint32)(DebounceTimer_TC_START_SIGNAL_MODE    << DebounceTimer_START_SHIFT)))
        
#define DebounceTimer_TIMER_UPDOWN_CNT_USED                                                          \
                ((DebounceTimer__COUNT_UPDOWN0 == DebounceTimer_TC_COUNTER_MODE)                  ||\
                 (DebounceTimer__COUNT_UPDOWN1 == DebounceTimer_TC_COUNTER_MODE))

#define DebounceTimer_PWM_UPDOWN_CNT_USED                                                            \
                ((DebounceTimer__CENTER == DebounceTimer_PWM_ALIGN)                               ||\
                 (DebounceTimer__ASYMMETRIC == DebounceTimer_PWM_ALIGN))               
        
#define DebounceTimer_PWM_PR_INIT_VALUE              (1u)
#define DebounceTimer_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_DebounceTimer_H */

/* [] END OF FILE */
