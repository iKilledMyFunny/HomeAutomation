/*******************************************************************************
* File Name: USER_PIN.h  
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

#if !defined(CY_PINS_USER_PIN_ALIASES_H) /* Pins USER_PIN_ALIASES_H */
#define CY_PINS_USER_PIN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define USER_PIN_0			(USER_PIN__0__PC)
#define USER_PIN_0_PS		(USER_PIN__0__PS)
#define USER_PIN_0_PC		(USER_PIN__0__PC)
#define USER_PIN_0_DR		(USER_PIN__0__DR)
#define USER_PIN_0_SHIFT	(USER_PIN__0__SHIFT)
#define USER_PIN_0_INTR	((uint16)((uint16)0x0003u << (USER_PIN__0__SHIFT*2u)))

#define USER_PIN_INTR_ALL	 ((uint16)(USER_PIN_0_INTR))


#endif /* End Pins USER_PIN_ALIASES_H */


/* [] END OF FILE */
