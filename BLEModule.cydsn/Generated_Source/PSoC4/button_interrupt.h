/*******************************************************************************
* File Name: button_interrupt.h
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
#if !defined(CY_ISR_button_interrupt_H)
#define CY_ISR_button_interrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void button_interrupt_Start(void);
void button_interrupt_StartEx(cyisraddress address);
void button_interrupt_Stop(void);

CY_ISR_PROTO(button_interrupt_Interrupt);

void button_interrupt_SetVector(cyisraddress address);
cyisraddress button_interrupt_GetVector(void);

void button_interrupt_SetPriority(uint8 priority);
uint8 button_interrupt_GetPriority(void);

void button_interrupt_Enable(void);
uint8 button_interrupt_GetState(void);
void button_interrupt_Disable(void);

void button_interrupt_SetPending(void);
void button_interrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the button_interrupt ISR. */
#define button_interrupt_INTC_VECTOR            ((reg32 *) button_interrupt__INTC_VECT)

/* Address of the button_interrupt ISR priority. */
#define button_interrupt_INTC_PRIOR             ((reg32 *) button_interrupt__INTC_PRIOR_REG)

/* Priority of the button_interrupt interrupt. */
#define button_interrupt_INTC_PRIOR_NUMBER      button_interrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable button_interrupt interrupt. */
#define button_interrupt_INTC_SET_EN            ((reg32 *) button_interrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the button_interrupt interrupt. */
#define button_interrupt_INTC_CLR_EN            ((reg32 *) button_interrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the button_interrupt interrupt state to pending. */
#define button_interrupt_INTC_SET_PD            ((reg32 *) button_interrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the button_interrupt interrupt. */
#define button_interrupt_INTC_CLR_PD            ((reg32 *) button_interrupt__INTC_CLR_PD_REG)



#endif /* CY_ISR_button_interrupt_H */


/* [] END OF FILE */
