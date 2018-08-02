/***************************************************************************//**
* \file bridging_console_BOOT.h
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

#if !defined(CY_SCB_BOOT_bridging_console_H)
#define CY_SCB_BOOT_bridging_console_H

#include "bridging_console_PVT.h"

#if (bridging_console_SCB_MODE_I2C_INC)
    #include "bridging_console_I2C.h"
#endif /* (bridging_console_SCB_MODE_I2C_INC) */

#if (bridging_console_SCB_MODE_EZI2C_INC)
    #include "bridging_console_EZI2C.h"
#endif /* (bridging_console_SCB_MODE_EZI2C_INC) */

#if (bridging_console_SCB_MODE_SPI_INC || bridging_console_SCB_MODE_UART_INC)
    #include "bridging_console_SPI_UART.h"
#endif /* (bridging_console_SCB_MODE_SPI_INC || bridging_console_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define bridging_console_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_bridging_console) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (bridging_console_SCB_MODE_I2C_INC)
    #define bridging_console_I2C_BTLDR_COMM_ENABLED     (bridging_console_BTLDR_COMM_ENABLED && \
                                                            (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             bridging_console_I2C_SLAVE_CONST))
#else
     #define bridging_console_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (bridging_console_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (bridging_console_SCB_MODE_EZI2C_INC)
    #define bridging_console_EZI2C_BTLDR_COMM_ENABLED   (bridging_console_BTLDR_COMM_ENABLED && \
                                                         bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define bridging_console_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (bridging_console_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (bridging_console_SCB_MODE_SPI_INC)
    #define bridging_console_SPI_BTLDR_COMM_ENABLED     (bridging_console_BTLDR_COMM_ENABLED && \
                                                            (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             bridging_console_SPI_SLAVE_CONST))
#else
        #define bridging_console_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (bridging_console_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (bridging_console_SCB_MODE_UART_INC)
       #define bridging_console_UART_BTLDR_COMM_ENABLED    (bridging_console_BTLDR_COMM_ENABLED && \
                                                            (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (bridging_console_UART_RX_DIRECTION && \
                                                              bridging_console_UART_TX_DIRECTION)))
#else
     #define bridging_console_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (bridging_console_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define bridging_console_BTLDR_COMM_MODE_ENABLED    (bridging_console_I2C_BTLDR_COMM_ENABLED   || \
                                                     bridging_console_SPI_BTLDR_COMM_ENABLED   || \
                                                     bridging_console_EZI2C_BTLDR_COMM_ENABLED || \
                                                     bridging_console_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (bridging_console_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void bridging_console_I2CCyBtldrCommStart(void);
    void bridging_console_I2CCyBtldrCommStop (void);
    void bridging_console_I2CCyBtldrCommReset(void);
    cystatus bridging_console_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus bridging_console_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (bridging_console_SCB_MODE_I2C_CONST_CFG)
        #define bridging_console_CyBtldrCommStart   bridging_console_I2CCyBtldrCommStart
        #define bridging_console_CyBtldrCommStop    bridging_console_I2CCyBtldrCommStop
        #define bridging_console_CyBtldrCommReset   bridging_console_I2CCyBtldrCommReset
        #define bridging_console_CyBtldrCommRead    bridging_console_I2CCyBtldrCommRead
        #define bridging_console_CyBtldrCommWrite   bridging_console_I2CCyBtldrCommWrite
    #endif /* (bridging_console_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (bridging_console_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (bridging_console_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void bridging_console_EzI2CCyBtldrCommStart(void);
    void bridging_console_EzI2CCyBtldrCommStop (void);
    void bridging_console_EzI2CCyBtldrCommReset(void);
    cystatus bridging_console_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus bridging_console_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (bridging_console_SCB_MODE_EZI2C_CONST_CFG)
        #define bridging_console_CyBtldrCommStart   bridging_console_EzI2CCyBtldrCommStart
        #define bridging_console_CyBtldrCommStop    bridging_console_EzI2CCyBtldrCommStop
        #define bridging_console_CyBtldrCommReset   bridging_console_EzI2CCyBtldrCommReset
        #define bridging_console_CyBtldrCommRead    bridging_console_EzI2CCyBtldrCommRead
        #define bridging_console_CyBtldrCommWrite   bridging_console_EzI2CCyBtldrCommWrite
    #endif /* (bridging_console_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (bridging_console_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (bridging_console_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void bridging_console_SpiCyBtldrCommStart(void);
    void bridging_console_SpiCyBtldrCommStop (void);
    void bridging_console_SpiCyBtldrCommReset(void);
    cystatus bridging_console_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus bridging_console_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (bridging_console_SCB_MODE_SPI_CONST_CFG)
        #define bridging_console_CyBtldrCommStart   bridging_console_SpiCyBtldrCommStart
        #define bridging_console_CyBtldrCommStop    bridging_console_SpiCyBtldrCommStop
        #define bridging_console_CyBtldrCommReset   bridging_console_SpiCyBtldrCommReset
        #define bridging_console_CyBtldrCommRead    bridging_console_SpiCyBtldrCommRead
        #define bridging_console_CyBtldrCommWrite   bridging_console_SpiCyBtldrCommWrite
    #endif /* (bridging_console_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (bridging_console_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (bridging_console_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void bridging_console_UartCyBtldrCommStart(void);
    void bridging_console_UartCyBtldrCommStop (void);
    void bridging_console_UartCyBtldrCommReset(void);
    cystatus bridging_console_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus bridging_console_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (bridging_console_SCB_MODE_UART_CONST_CFG)
        #define bridging_console_CyBtldrCommStart   bridging_console_UartCyBtldrCommStart
        #define bridging_console_CyBtldrCommStop    bridging_console_UartCyBtldrCommStop
        #define bridging_console_CyBtldrCommReset   bridging_console_UartCyBtldrCommReset
        #define bridging_console_CyBtldrCommRead    bridging_console_UartCyBtldrCommRead
        #define bridging_console_CyBtldrCommWrite   bridging_console_UartCyBtldrCommWrite
    #endif /* (bridging_console_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (bridging_console_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (bridging_console_BTLDR_COMM_ENABLED)
    #if (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void bridging_console_CyBtldrCommStart(void);
        void bridging_console_CyBtldrCommStop (void);
        void bridging_console_CyBtldrCommReset(void);
        cystatus bridging_console_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus bridging_console_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_bridging_console)
        #define CyBtldrCommStart    bridging_console_CyBtldrCommStart
        #define CyBtldrCommStop     bridging_console_CyBtldrCommStop
        #define CyBtldrCommReset    bridging_console_CyBtldrCommReset
        #define CyBtldrCommWrite    bridging_console_CyBtldrCommWrite
        #define CyBtldrCommRead     bridging_console_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_bridging_console) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (bridging_console_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define bridging_console_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define bridging_console_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define bridging_console_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define bridging_console_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef bridging_console_SPI_BYTE_TO_BYTE
    #define bridging_console_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef bridging_console_UART_BYTE_TO_BYTE
    #define bridging_console_UART_BYTE_TO_BYTE  (520u)
#endif /* bridging_console_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_bridging_console_H) */


/* [] END OF FILE */
