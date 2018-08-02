/*******************************************************************************
* File Name: user_pin_blue.h  
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

#if !defined(CY_PINS_user_pin_blue_H) /* Pins user_pin_blue_H */
#define CY_PINS_user_pin_blue_H

#include "cytypes.h"
#include "cyfitter.h"
#include "user_pin_blue_aliases.h"


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
} user_pin_blue_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   user_pin_blue_Read(void);
void    user_pin_blue_Write(uint8 value);
uint8   user_pin_blue_ReadDataReg(void);
#if defined(user_pin_blue__PC) || (CY_PSOC4_4200L) 
    void    user_pin_blue_SetDriveMode(uint8 mode);
#endif
void    user_pin_blue_SetInterruptMode(uint16 position, uint16 mode);
uint8   user_pin_blue_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void user_pin_blue_Sleep(void); 
void user_pin_blue_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(user_pin_blue__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define user_pin_blue_DRIVE_MODE_BITS        (3)
    #define user_pin_blue_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - user_pin_blue_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the user_pin_blue_SetDriveMode() function.
         *  @{
         */
        #define user_pin_blue_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define user_pin_blue_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define user_pin_blue_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define user_pin_blue_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define user_pin_blue_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define user_pin_blue_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define user_pin_blue_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define user_pin_blue_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define user_pin_blue_MASK               user_pin_blue__MASK
#define user_pin_blue_SHIFT              user_pin_blue__SHIFT
#define user_pin_blue_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in user_pin_blue_SetInterruptMode() function.
     *  @{
     */
        #define user_pin_blue_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define user_pin_blue_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define user_pin_blue_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define user_pin_blue_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(user_pin_blue__SIO)
    #define user_pin_blue_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(user_pin_blue__PC) && (CY_PSOC4_4200L)
    #define user_pin_blue_USBIO_ENABLE               ((uint32)0x80000000u)
    #define user_pin_blue_USBIO_DISABLE              ((uint32)(~user_pin_blue_USBIO_ENABLE))
    #define user_pin_blue_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define user_pin_blue_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define user_pin_blue_USBIO_ENTER_SLEEP          ((uint32)((1u << user_pin_blue_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << user_pin_blue_USBIO_SUSPEND_DEL_SHIFT)))
    #define user_pin_blue_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << user_pin_blue_USBIO_SUSPEND_SHIFT)))
    #define user_pin_blue_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << user_pin_blue_USBIO_SUSPEND_DEL_SHIFT)))
    #define user_pin_blue_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(user_pin_blue__PC)
    /* Port Configuration */
    #define user_pin_blue_PC                 (* (reg32 *) user_pin_blue__PC)
#endif
/* Pin State */
#define user_pin_blue_PS                     (* (reg32 *) user_pin_blue__PS)
/* Data Register */
#define user_pin_blue_DR                     (* (reg32 *) user_pin_blue__DR)
/* Input Buffer Disable Override */
#define user_pin_blue_INP_DIS                (* (reg32 *) user_pin_blue__PC2)

/* Interrupt configuration Registers */
#define user_pin_blue_INTCFG                 (* (reg32 *) user_pin_blue__INTCFG)
#define user_pin_blue_INTSTAT                (* (reg32 *) user_pin_blue__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define user_pin_blue_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(user_pin_blue__SIO)
    #define user_pin_blue_SIO_REG            (* (reg32 *) user_pin_blue__SIO)
#endif /* (user_pin_blue__SIO_CFG) */

/* USBIO registers */
#if !defined(user_pin_blue__PC) && (CY_PSOC4_4200L)
    #define user_pin_blue_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define user_pin_blue_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define user_pin_blue_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define user_pin_blue_DRIVE_MODE_SHIFT       (0x00u)
#define user_pin_blue_DRIVE_MODE_MASK        (0x07u << user_pin_blue_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins user_pin_blue_H */


/* [] END OF FILE */
