/*******************************************************************************
* File Name: user_switch_pin.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_user_switch_pin_ALIASES_H) /* Pins user_switch_pin_ALIASES_H */
#define CY_PINS_user_switch_pin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define user_switch_pin_0			(user_switch_pin__0__PC)
#define user_switch_pin_0_PS		(user_switch_pin__0__PS)
#define user_switch_pin_0_PC		(user_switch_pin__0__PC)
#define user_switch_pin_0_DR		(user_switch_pin__0__DR)
#define user_switch_pin_0_SHIFT	(user_switch_pin__0__SHIFT)
#define user_switch_pin_0_INTR	((uint16)((uint16)0x0003u << (user_switch_pin__0__SHIFT*2u)))

#define user_switch_pin_INTR_ALL	 ((uint16)(user_switch_pin_0_INTR))


#endif /* End Pins user_switch_pin_ALIASES_H */


/* [] END OF FILE */
