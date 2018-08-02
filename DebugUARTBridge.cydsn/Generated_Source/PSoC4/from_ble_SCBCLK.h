/*******************************************************************************
* File Name: from_ble_SCBCLK.h
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

#if !defined(CY_CLOCK_from_ble_SCBCLK_H)
#define CY_CLOCK_from_ble_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void from_ble_SCBCLK_StartEx(uint32 alignClkDiv);
#define from_ble_SCBCLK_Start() \
    from_ble_SCBCLK_StartEx(from_ble_SCBCLK__PA_DIV_ID)

#else

void from_ble_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void from_ble_SCBCLK_Stop(void);

void from_ble_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 from_ble_SCBCLK_GetDividerRegister(void);
uint8  from_ble_SCBCLK_GetFractionalDividerRegister(void);

#define from_ble_SCBCLK_Enable()                         from_ble_SCBCLK_Start()
#define from_ble_SCBCLK_Disable()                        from_ble_SCBCLK_Stop()
#define from_ble_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    from_ble_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define from_ble_SCBCLK_SetDivider(clkDivider)           from_ble_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define from_ble_SCBCLK_SetDividerValue(clkDivider)      from_ble_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define from_ble_SCBCLK_DIV_ID     from_ble_SCBCLK__DIV_ID

#define from_ble_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define from_ble_SCBCLK_CTRL_REG   (*(reg32 *)from_ble_SCBCLK__CTRL_REGISTER)
#define from_ble_SCBCLK_DIV_REG    (*(reg32 *)from_ble_SCBCLK__DIV_REGISTER)

#define from_ble_SCBCLK_CMD_DIV_SHIFT          (0u)
#define from_ble_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define from_ble_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define from_ble_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define from_ble_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << from_ble_SCBCLK_CMD_DISABLE_SHIFT))
#define from_ble_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << from_ble_SCBCLK_CMD_ENABLE_SHIFT))

#define from_ble_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define from_ble_SCBCLK_DIV_FRAC_SHIFT (3u)
#define from_ble_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define from_ble_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define from_ble_SCBCLK_DIV_REG        (*(reg32 *)from_ble_SCBCLK__REGISTER)
#define from_ble_SCBCLK_ENABLE_REG     from_ble_SCBCLK_DIV_REG
#define from_ble_SCBCLK_DIV_FRAC_MASK  from_ble_SCBCLK__FRAC_MASK
#define from_ble_SCBCLK_DIV_FRAC_SHIFT (16u)
#define from_ble_SCBCLK_DIV_INT_MASK   from_ble_SCBCLK__DIVIDER_MASK
#define from_ble_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_from_ble_SCBCLK_H) */

/* [] END OF FILE */
