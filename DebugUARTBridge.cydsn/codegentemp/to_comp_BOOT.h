/***************************************************************************//**
* \file to_comp_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_to_comp_H)
#define CY_SCB_BOOT_to_comp_H

#include "to_comp_PVT.h"

#if (to_comp_SCB_MODE_I2C_INC)
    #include "to_comp_I2C.h"
#endif /* (to_comp_SCB_MODE_I2C_INC) */

#if (to_comp_SCB_MODE_EZI2C_INC)
    #include "to_comp_EZI2C.h"
#endif /* (to_comp_SCB_MODE_EZI2C_INC) */

#if (to_comp_SCB_MODE_SPI_INC || to_comp_SCB_MODE_UART_INC)
    #include "to_comp_SPI_UART.h"
#endif /* (to_comp_SCB_MODE_SPI_INC || to_comp_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define to_comp_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_to_comp) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (to_comp_SCB_MODE_I2C_INC)
    #define to_comp_I2C_BTLDR_COMM_ENABLED     (to_comp_BTLDR_COMM_ENABLED && \
                                                            (to_comp_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             to_comp_I2C_SLAVE_CONST))
#else
     #define to_comp_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (to_comp_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (to_comp_SCB_MODE_EZI2C_INC)
    #define to_comp_EZI2C_BTLDR_COMM_ENABLED   (to_comp_BTLDR_COMM_ENABLED && \
                                                         to_comp_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define to_comp_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (to_comp_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (to_comp_SCB_MODE_SPI_INC)
    #define to_comp_SPI_BTLDR_COMM_ENABLED     (to_comp_BTLDR_COMM_ENABLED && \
                                                            (to_comp_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             to_comp_SPI_SLAVE_CONST))
#else
        #define to_comp_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (to_comp_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (to_comp_SCB_MODE_UART_INC)
       #define to_comp_UART_BTLDR_COMM_ENABLED    (to_comp_BTLDR_COMM_ENABLED && \
                                                            (to_comp_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (to_comp_UART_RX_DIRECTION && \
                                                              to_comp_UART_TX_DIRECTION)))
#else
     #define to_comp_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (to_comp_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define to_comp_BTLDR_COMM_MODE_ENABLED    (to_comp_I2C_BTLDR_COMM_ENABLED   || \
                                                     to_comp_SPI_BTLDR_COMM_ENABLED   || \
                                                     to_comp_EZI2C_BTLDR_COMM_ENABLED || \
                                                     to_comp_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (to_comp_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void to_comp_I2CCyBtldrCommStart(void);
    void to_comp_I2CCyBtldrCommStop (void);
    void to_comp_I2CCyBtldrCommReset(void);
    cystatus to_comp_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus to_comp_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (to_comp_SCB_MODE_I2C_CONST_CFG)
        #define to_comp_CyBtldrCommStart   to_comp_I2CCyBtldrCommStart
        #define to_comp_CyBtldrCommStop    to_comp_I2CCyBtldrCommStop
        #define to_comp_CyBtldrCommReset   to_comp_I2CCyBtldrCommReset
        #define to_comp_CyBtldrCommRead    to_comp_I2CCyBtldrCommRead
        #define to_comp_CyBtldrCommWrite   to_comp_I2CCyBtldrCommWrite
    #endif /* (to_comp_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (to_comp_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (to_comp_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void to_comp_EzI2CCyBtldrCommStart(void);
    void to_comp_EzI2CCyBtldrCommStop (void);
    void to_comp_EzI2CCyBtldrCommReset(void);
    cystatus to_comp_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus to_comp_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (to_comp_SCB_MODE_EZI2C_CONST_CFG)
        #define to_comp_CyBtldrCommStart   to_comp_EzI2CCyBtldrCommStart
        #define to_comp_CyBtldrCommStop    to_comp_EzI2CCyBtldrCommStop
        #define to_comp_CyBtldrCommReset   to_comp_EzI2CCyBtldrCommReset
        #define to_comp_CyBtldrCommRead    to_comp_EzI2CCyBtldrCommRead
        #define to_comp_CyBtldrCommWrite   to_comp_EzI2CCyBtldrCommWrite
    #endif /* (to_comp_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (to_comp_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (to_comp_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void to_comp_SpiCyBtldrCommStart(void);
    void to_comp_SpiCyBtldrCommStop (void);
    void to_comp_SpiCyBtldrCommReset(void);
    cystatus to_comp_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus to_comp_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (to_comp_SCB_MODE_SPI_CONST_CFG)
        #define to_comp_CyBtldrCommStart   to_comp_SpiCyBtldrCommStart
        #define to_comp_CyBtldrCommStop    to_comp_SpiCyBtldrCommStop
        #define to_comp_CyBtldrCommReset   to_comp_SpiCyBtldrCommReset
        #define to_comp_CyBtldrCommRead    to_comp_SpiCyBtldrCommRead
        #define to_comp_CyBtldrCommWrite   to_comp_SpiCyBtldrCommWrite
    #endif /* (to_comp_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (to_comp_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (to_comp_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void to_comp_UartCyBtldrCommStart(void);
    void to_comp_UartCyBtldrCommStop (void);
    void to_comp_UartCyBtldrCommReset(void);
    cystatus to_comp_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus to_comp_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (to_comp_SCB_MODE_UART_CONST_CFG)
        #define to_comp_CyBtldrCommStart   to_comp_UartCyBtldrCommStart
        #define to_comp_CyBtldrCommStop    to_comp_UartCyBtldrCommStop
        #define to_comp_CyBtldrCommReset   to_comp_UartCyBtldrCommReset
        #define to_comp_CyBtldrCommRead    to_comp_UartCyBtldrCommRead
        #define to_comp_CyBtldrCommWrite   to_comp_UartCyBtldrCommWrite
    #endif /* (to_comp_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (to_comp_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (to_comp_BTLDR_COMM_ENABLED)
    #if (to_comp_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void to_comp_CyBtldrCommStart(void);
        void to_comp_CyBtldrCommStop (void);
        void to_comp_CyBtldrCommReset(void);
        cystatus to_comp_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus to_comp_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (to_comp_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_to_comp)
        #define CyBtldrCommStart    to_comp_CyBtldrCommStart
        #define CyBtldrCommStop     to_comp_CyBtldrCommStop
        #define CyBtldrCommReset    to_comp_CyBtldrCommReset
        #define CyBtldrCommWrite    to_comp_CyBtldrCommWrite
        #define CyBtldrCommRead     to_comp_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_to_comp) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (to_comp_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define to_comp_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define to_comp_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define to_comp_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define to_comp_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef to_comp_SPI_BYTE_TO_BYTE
    #define to_comp_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef to_comp_UART_BYTE_TO_BYTE
    #define to_comp_UART_BYTE_TO_BYTE  (520u)
#endif /* to_comp_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_to_comp_H) */


/* [] END OF FILE */
