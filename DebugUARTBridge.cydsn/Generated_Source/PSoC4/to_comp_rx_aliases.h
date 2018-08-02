/*******************************************************************************
* File Name: to_comp_rx.h  
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

#if !defined(CY_PINS_to_comp_rx_ALIASES_H) /* Pins to_comp_rx_ALIASES_H */
#define CY_PINS_to_comp_rx_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define to_comp_rx_0			(to_comp_rx__0__PC)
#define to_comp_rx_0_PS		(to_comp_rx__0__PS)
#define to_comp_rx_0_PC		(to_comp_rx__0__PC)
#define to_comp_rx_0_DR		(to_comp_rx__0__DR)
#define to_comp_rx_0_SHIFT	(to_comp_rx__0__SHIFT)
#define to_comp_rx_0_INTR	((uint16)((uint16)0x0003u << (to_comp_rx__0__SHIFT*2u)))

#define to_comp_rx_INTR_ALL	 ((uint16)(to_comp_rx_0_INTR))


#endif /* End Pins to_comp_rx_ALIASES_H */


/* [] END OF FILE */
