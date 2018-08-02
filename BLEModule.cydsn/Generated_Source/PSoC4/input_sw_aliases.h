/*******************************************************************************
* File Name: input_sw.h  
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

#if !defined(CY_PINS_input_sw_ALIASES_H) /* Pins input_sw_ALIASES_H */
#define CY_PINS_input_sw_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define input_sw_0			(input_sw__0__PC)
#define input_sw_0_PS		(input_sw__0__PS)
#define input_sw_0_PC		(input_sw__0__PC)
#define input_sw_0_DR		(input_sw__0__DR)
#define input_sw_0_SHIFT	(input_sw__0__SHIFT)
#define input_sw_0_INTR	((uint16)((uint16)0x0003u << (input_sw__0__SHIFT*2u)))

#define input_sw_INTR_ALL	 ((uint16)(input_sw_0_INTR))


#endif /* End Pins input_sw_ALIASES_H */


/* [] END OF FILE */
