/*******************************************************************************
* File Name: debounceTimerIntr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_debounceTimerIntr_H)
#define CY_ISR_debounceTimerIntr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void debounceTimerIntr_Start(void);
void debounceTimerIntr_StartEx(cyisraddress address);
void debounceTimerIntr_Stop(void);

CY_ISR_PROTO(debounceTimerIntr_Interrupt);

void debounceTimerIntr_SetVector(cyisraddress address);
cyisraddress debounceTimerIntr_GetVector(void);

void debounceTimerIntr_SetPriority(uint8 priority);
uint8 debounceTimerIntr_GetPriority(void);

void debounceTimerIntr_Enable(void);
uint8 debounceTimerIntr_GetState(void);
void debounceTimerIntr_Disable(void);

void debounceTimerIntr_SetPending(void);
void debounceTimerIntr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the debounceTimerIntr ISR. */
#define debounceTimerIntr_INTC_VECTOR            ((reg32 *) debounceTimerIntr__INTC_VECT)

/* Address of the debounceTimerIntr ISR priority. */
#define debounceTimerIntr_INTC_PRIOR             ((reg32 *) debounceTimerIntr__INTC_PRIOR_REG)

/* Priority of the debounceTimerIntr interrupt. */
#define debounceTimerIntr_INTC_PRIOR_NUMBER      debounceTimerIntr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable debounceTimerIntr interrupt. */
#define debounceTimerIntr_INTC_SET_EN            ((reg32 *) debounceTimerIntr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the debounceTimerIntr interrupt. */
#define debounceTimerIntr_INTC_CLR_EN            ((reg32 *) debounceTimerIntr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the debounceTimerIntr interrupt state to pending. */
#define debounceTimerIntr_INTC_SET_PD            ((reg32 *) debounceTimerIntr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the debounceTimerIntr interrupt. */
#define debounceTimerIntr_INTC_CLR_PD            ((reg32 *) debounceTimerIntr__INTC_CLR_PD_REG)



#endif /* CY_ISR_debounceTimerIntr_H */


/* [] END OF FILE */
