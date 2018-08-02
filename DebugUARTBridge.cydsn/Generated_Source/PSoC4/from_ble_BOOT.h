/***************************************************************************//**
* \file from_ble_BOOT.h
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

#if !defined(CY_SCB_BOOT_from_ble_H)
#define CY_SCB_BOOT_from_ble_H

#include "from_ble_PVT.h"

#if (from_ble_SCB_MODE_I2C_INC)
    #include "from_ble_I2C.h"
#endif /* (from_ble_SCB_MODE_I2C_INC) */

#if (from_ble_SCB_MODE_EZI2C_INC)
    #include "from_ble_EZI2C.h"
#endif /* (from_ble_SCB_MODE_EZI2C_INC) */

#if (from_ble_SCB_MODE_SPI_INC || from_ble_SCB_MODE_UART_INC)
    #include "from_ble_SPI_UART.h"
#endif /* (from_ble_SCB_MODE_SPI_INC || from_ble_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define from_ble_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_from_ble) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (from_ble_SCB_MODE_I2C_INC)
    #define from_ble_I2C_BTLDR_COMM_ENABLED     (from_ble_BTLDR_COMM_ENABLED && \
                                                            (from_ble_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             from_ble_I2C_SLAVE_CONST))
#else
     #define from_ble_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (from_ble_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (from_ble_SCB_MODE_EZI2C_INC)
    #define from_ble_EZI2C_BTLDR_COMM_ENABLED   (from_ble_BTLDR_COMM_ENABLED && \
                                                         from_ble_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define from_ble_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (from_ble_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (from_ble_SCB_MODE_SPI_INC)
    #define from_ble_SPI_BTLDR_COMM_ENABLED     (from_ble_BTLDR_COMM_ENABLED && \
                                                            (from_ble_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             from_ble_SPI_SLAVE_CONST))
#else
        #define from_ble_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (from_ble_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (from_ble_SCB_MODE_UART_INC)
       #define from_ble_UART_BTLDR_COMM_ENABLED    (from_ble_BTLDR_COMM_ENABLED && \
                                                            (from_ble_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (from_ble_UART_RX_DIRECTION && \
                                                              from_ble_UART_TX_DIRECTION)))
#else
     #define from_ble_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (from_ble_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define from_ble_BTLDR_COMM_MODE_ENABLED    (from_ble_I2C_BTLDR_COMM_ENABLED   || \
                                                     from_ble_SPI_BTLDR_COMM_ENABLED   || \
                                                     from_ble_EZI2C_BTLDR_COMM_ENABLED || \
                                                     from_ble_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (from_ble_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void from_ble_I2CCyBtldrCommStart(void);
    void from_ble_I2CCyBtldrCommStop (void);
    void from_ble_I2CCyBtldrCommReset(void);
    cystatus from_ble_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus from_ble_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (from_ble_SCB_MODE_I2C_CONST_CFG)
        #define from_ble_CyBtldrCommStart   from_ble_I2CCyBtldrCommStart
        #define from_ble_CyBtldrCommStop    from_ble_I2CCyBtldrCommStop
        #define from_ble_CyBtldrCommReset   from_ble_I2CCyBtldrCommReset
        #define from_ble_CyBtldrCommRead    from_ble_I2CCyBtldrCommRead
        #define from_ble_CyBtldrCommWrite   from_ble_I2CCyBtldrCommWrite
    #endif /* (from_ble_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (from_ble_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (from_ble_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void from_ble_EzI2CCyBtldrCommStart(void);
    void from_ble_EzI2CCyBtldrCommStop (void);
    void from_ble_EzI2CCyBtldrCommReset(void);
    cystatus from_ble_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus from_ble_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (from_ble_SCB_MODE_EZI2C_CONST_CFG)
        #define from_ble_CyBtldrCommStart   from_ble_EzI2CCyBtldrCommStart
        #define from_ble_CyBtldrCommStop    from_ble_EzI2CCyBtldrCommStop
        #define from_ble_CyBtldrCommReset   from_ble_EzI2CCyBtldrCommReset
        #define from_ble_CyBtldrCommRead    from_ble_EzI2CCyBtldrCommRead
        #define from_ble_CyBtldrCommWrite   from_ble_EzI2CCyBtldrCommWrite
    #endif /* (from_ble_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (from_ble_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (from_ble_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void from_ble_SpiCyBtldrCommStart(void);
    void from_ble_SpiCyBtldrCommStop (void);
    void from_ble_SpiCyBtldrCommReset(void);
    cystatus from_ble_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus from_ble_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (from_ble_SCB_MODE_SPI_CONST_CFG)
        #define from_ble_CyBtldrCommStart   from_ble_SpiCyBtldrCommStart
        #define from_ble_CyBtldrCommStop    from_ble_SpiCyBtldrCommStop
        #define from_ble_CyBtldrCommReset   from_ble_SpiCyBtldrCommReset
        #define from_ble_CyBtldrCommRead    from_ble_SpiCyBtldrCommRead
        #define from_ble_CyBtldrCommWrite   from_ble_SpiCyBtldrCommWrite
    #endif /* (from_ble_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (from_ble_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (from_ble_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void from_ble_UartCyBtldrCommStart(void);
    void from_ble_UartCyBtldrCommStop (void);
    void from_ble_UartCyBtldrCommReset(void);
    cystatus from_ble_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus from_ble_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (from_ble_SCB_MODE_UART_CONST_CFG)
        #define from_ble_CyBtldrCommStart   from_ble_UartCyBtldrCommStart
        #define from_ble_CyBtldrCommStop    from_ble_UartCyBtldrCommStop
        #define from_ble_CyBtldrCommReset   from_ble_UartCyBtldrCommReset
        #define from_ble_CyBtldrCommRead    from_ble_UartCyBtldrCommRead
        #define from_ble_CyBtldrCommWrite   from_ble_UartCyBtldrCommWrite
    #endif /* (from_ble_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (from_ble_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (from_ble_BTLDR_COMM_ENABLED)
    #if (from_ble_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void from_ble_CyBtldrCommStart(void);
        void from_ble_CyBtldrCommStop (void);
        void from_ble_CyBtldrCommReset(void);
        cystatus from_ble_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus from_ble_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (from_ble_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_from_ble)
        #define CyBtldrCommStart    from_ble_CyBtldrCommStart
        #define CyBtldrCommStop     from_ble_CyBtldrCommStop
        #define CyBtldrCommReset    from_ble_CyBtldrCommReset
        #define CyBtldrCommWrite    from_ble_CyBtldrCommWrite
        #define CyBtldrCommRead     from_ble_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_from_ble) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (from_ble_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define from_ble_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define from_ble_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define from_ble_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define from_ble_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef from_ble_SPI_BYTE_TO_BYTE
    #define from_ble_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef from_ble_UART_BYTE_TO_BYTE
    #define from_ble_UART_BYTE_TO_BYTE  (520u)
#endif /* from_ble_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_from_ble_H) */


/* [] END OF FILE */
