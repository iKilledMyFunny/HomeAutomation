/*******************************************************************************
* File Name: input_sw.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_input_sw_H) /* Pins input_sw_H */
#define CY_PINS_input_sw_H

#include "cytypes.h"
#include "cyfitter.h"
#include "input_sw_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} input_sw_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   input_sw_Read(void);
void    input_sw_Write(uint8 value);
uint8   input_sw_ReadDataReg(void);
#if defined(input_sw__PC) || (CY_PSOC4_4200L) 
    void    input_sw_SetDriveMode(uint8 mode);
#endif
void    input_sw_SetInterruptMode(uint16 position, uint16 mode);
uint8   input_sw_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void input_sw_Sleep(void); 
void input_sw_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(input_sw__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define input_sw_DRIVE_MODE_BITS        (3)
    #define input_sw_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - input_sw_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the input_sw_SetDriveMode() function.
         *  @{
         */
        #define input_sw_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define input_sw_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define input_sw_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define input_sw_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define input_sw_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define input_sw_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define input_sw_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define input_sw_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define input_sw_MASK               input_sw__MASK
#define input_sw_SHIFT              input_sw__SHIFT
#define input_sw_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in input_sw_SetInterruptMode() function.
     *  @{
     */
        #define input_sw_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define input_sw_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define input_sw_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define input_sw_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(input_sw__SIO)
    #define input_sw_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(input_sw__PC) && (CY_PSOC4_4200L)
    #define input_sw_USBIO_ENABLE               ((uint32)0x80000000u)
    #define input_sw_USBIO_DISABLE              ((uint32)(~input_sw_USBIO_ENABLE))
    #define input_sw_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define input_sw_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define input_sw_USBIO_ENTER_SLEEP          ((uint32)((1u << input_sw_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << input_sw_USBIO_SUSPEND_DEL_SHIFT)))
    #define input_sw_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << input_sw_USBIO_SUSPEND_SHIFT)))
    #define input_sw_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << input_sw_USBIO_SUSPEND_DEL_SHIFT)))
    #define input_sw_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(input_sw__PC)
    /* Port Configuration */
    #define input_sw_PC                 (* (reg32 *) input_sw__PC)
#endif
/* Pin State */
#define input_sw_PS                     (* (reg32 *) input_sw__PS)
/* Data Register */
#define input_sw_DR                     (* (reg32 *) input_sw__DR)
/* Input Buffer Disable Override */
#define input_sw_INP_DIS                (* (reg32 *) input_sw__PC2)

/* Interrupt configuration Registers */
#define input_sw_INTCFG                 (* (reg32 *) input_sw__INTCFG)
#define input_sw_INTSTAT                (* (reg32 *) input_sw__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define input_sw_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(input_sw__SIO)
    #define input_sw_SIO_REG            (* (reg32 *) input_sw__SIO)
#endif /* (input_sw__SIO_CFG) */

/* USBIO registers */
#if !defined(input_sw__PC) && (CY_PSOC4_4200L)
    #define input_sw_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define input_sw_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define input_sw_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define input_sw_DRIVE_MODE_SHIFT       (0x00u)
#define input_sw_DRIVE_MODE_MASK        (0x07u << input_sw_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins input_sw_H */


/* [] END OF FILE */
