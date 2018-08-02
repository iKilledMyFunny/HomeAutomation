/*******************************************************************************
* File Name: bridging_console_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_bridging_console_SCBCLK_H)
#define CY_CLOCK_bridging_console_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void bridging_console_SCBCLK_StartEx(uint32 alignClkDiv);
#define bridging_console_SCBCLK_Start() \
    bridging_console_SCBCLK_StartEx(bridging_console_SCBCLK__PA_DIV_ID)

#else

void bridging_console_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void bridging_console_SCBCLK_Stop(void);

void bridging_console_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 bridging_console_SCBCLK_GetDividerRegister(void);
uint8  bridging_console_SCBCLK_GetFractionalDividerRegister(void);

#define bridging_console_SCBCLK_Enable()                         bridging_console_SCBCLK_Start()
#define bridging_console_SCBCLK_Disable()                        bridging_console_SCBCLK_Stop()
#define bridging_console_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    bridging_console_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define bridging_console_SCBCLK_SetDivider(clkDivider)           bridging_console_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define bridging_console_SCBCLK_SetDividerValue(clkDivider)      bridging_console_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define bridging_console_SCBCLK_DIV_ID     bridging_console_SCBCLK__DIV_ID

#define bridging_console_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define bridging_console_SCBCLK_CTRL_REG   (*(reg32 *)bridging_console_SCBCLK__CTRL_REGISTER)
#define bridging_console_SCBCLK_DIV_REG    (*(reg32 *)bridging_console_SCBCLK__DIV_REGISTER)

#define bridging_console_SCBCLK_CMD_DIV_SHIFT          (0u)
#define bridging_console_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define bridging_console_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define bridging_console_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define bridging_console_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << bridging_console_SCBCLK_CMD_DISABLE_SHIFT))
#define bridging_console_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << bridging_console_SCBCLK_CMD_ENABLE_SHIFT))

#define bridging_console_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define bridging_console_SCBCLK_DIV_FRAC_SHIFT (3u)
#define bridging_console_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define bridging_console_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define bridging_console_SCBCLK_DIV_REG        (*(reg32 *)bridging_console_SCBCLK__REGISTER)
#define bridging_console_SCBCLK_ENABLE_REG     bridging_console_SCBCLK_DIV_REG
#define bridging_console_SCBCLK_DIV_FRAC_MASK  bridging_console_SCBCLK__FRAC_MASK
#define bridging_console_SCBCLK_DIV_FRAC_SHIFT (16u)
#define bridging_console_SCBCLK_DIV_INT_MASK   bridging_console_SCBCLK__DIVIDER_MASK
#define bridging_console_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_bridging_console_SCBCLK_H) */

/* [] END OF FILE */
