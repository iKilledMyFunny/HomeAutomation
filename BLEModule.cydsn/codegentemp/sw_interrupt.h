/*******************************************************************************
* File Name: sw_interrupt.h
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
#if !defined(CY_ISR_sw_interrupt_H)
#define CY_ISR_sw_interrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void sw_interrupt_Start(void);
void sw_interrupt_StartEx(cyisraddress address);
void sw_interrupt_Stop(void);

CY_ISR_PROTO(sw_interrupt_Interrupt);

void sw_interrupt_SetVector(cyisraddress address);
cyisraddress sw_interrupt_GetVector(void);

void sw_interrupt_SetPriority(uint8 priority);
uint8 sw_interrupt_GetPriority(void);

void sw_interrupt_Enable(void);
uint8 sw_interrupt_GetState(void);
void sw_interrupt_Disable(void);

void sw_interrupt_SetPending(void);
void sw_interrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the sw_interrupt ISR. */
#define sw_interrupt_INTC_VECTOR            ((reg32 *) sw_interrupt__INTC_VECT)

/* Address of the sw_interrupt ISR priority. */
#define sw_interrupt_INTC_PRIOR             ((reg32 *) sw_interrupt__INTC_PRIOR_REG)

/* Priority of the sw_interrupt interrupt. */
#define sw_interrupt_INTC_PRIOR_NUMBER      sw_interrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable sw_interrupt interrupt. */
#define sw_interrupt_INTC_SET_EN            ((reg32 *) sw_interrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the sw_interrupt interrupt. */
#define sw_interrupt_INTC_CLR_EN            ((reg32 *) sw_interrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the sw_interrupt interrupt state to pending. */
#define sw_interrupt_INTC_SET_PD            ((reg32 *) sw_interrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the sw_interrupt interrupt. */
#define sw_interrupt_INTC_CLR_PD            ((reg32 *) sw_interrupt__INTC_CLR_PD_REG)



#endif /* CY_ISR_sw_interrupt_H */


/* [] END OF FILE */
