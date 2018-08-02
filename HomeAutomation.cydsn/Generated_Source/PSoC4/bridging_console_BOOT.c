/***************************************************************************//**
* \file bridging_console_BOOT.c
* \version 4.0
*
* \brief
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component Unconfigured mode.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "bridging_console_BOOT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (bridging_console_BTLDR_COMM_ENABLED) && \
                                (bridging_console_SCB_MODE_UNCONFIG_CONST_CFG)

/*******************************************************************************
* Function Name: bridging_console_CyBtldrCommStart
****************************************************************************//**
*
*  Starts bridging_console component. After this function call the component is 
*  ready for communication.
*
*******************************************************************************/
void bridging_console_CyBtldrCommStart(void)
{
    if (bridging_console_SCB_MODE_I2C_RUNTM_CFG)
    {
        bridging_console_I2CCyBtldrCommStart();
    }
    else if (bridging_console_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        bridging_console_EzI2CCyBtldrCommStart();
    }
#if (!bridging_console_CY_SCBIP_V1)
    else if (bridging_console_SCB_MODE_SPI_RUNTM_CFG)
    {
        bridging_console_SpiCyBtldrCommStart();
    }
    else if (bridging_console_SCB_MODE_UART_RUNTM_CFG)
    {
        bridging_console_UartCyBtldrCommStart();
    }
#endif /* (!bridging_console_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: bridging_console_CyBtldrCommStop
****************************************************************************//**
*
*  Stops bridging_console component.
*
*******************************************************************************/
void bridging_console_CyBtldrCommStop(void)
{
    if (bridging_console_SCB_MODE_I2C_RUNTM_CFG)
    {
        bridging_console_I2CCyBtldrCommStop();
    }
    else if (bridging_console_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        bridging_console_EzI2CCyBtldrCommStop();
    }
#if (!bridging_console_CY_SCBIP_V1)
    else if (bridging_console_SCB_MODE_SPI_RUNTM_CFG)
    {
        bridging_console_SpiCyBtldrCommStop();
    }
    else if (bridging_console_SCB_MODE_UART_RUNTM_CFG)
    {
        bridging_console_UartCyBtldrCommStop();
    }
#endif /* (!bridging_console_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: bridging_console_CyBtldrCommReset
****************************************************************************//**
*
*  Clears bridging_console component buffers.
*
*******************************************************************************/
void bridging_console_CyBtldrCommReset(void)
{
    if(bridging_console_SCB_MODE_I2C_RUNTM_CFG)
    {
        bridging_console_I2CCyBtldrCommReset();
    }
    else if(bridging_console_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        bridging_console_EzI2CCyBtldrCommReset();
    }
#if (!bridging_console_CY_SCBIP_V1)
    else if(bridging_console_SCB_MODE_SPI_RUNTM_CFG)
    {
        bridging_console_SpiCyBtldrCommReset();
    }
    else if(bridging_console_SCB_MODE_UART_RUNTM_CFG)
    {
        bridging_console_UartCyBtldrCommReset();
    }
#endif /* (!bridging_console_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: bridging_console_CyBtldrCommRead
****************************************************************************//**
*
*  Allows the caller to read data from the bootloader host (the host writes the 
*  data). The function handles polling to allow a block of data to be completely
*  received from the host device.
*
*  \param pData: Pointer to storage for the block of data to be read from the
*   bootloader host.
*  \param size: Number of bytes to be read.
*  \param count: Pointer to the variable to write the number of bytes actually
*   read.
*  \param timeOut: Number of units in 10 ms to wait before returning because of a
*   timeout.
*
* \return
*  \return
*  cystatus: Returns CYRET_SUCCESS if no problem was encountered or returns the
*  value that best describes the problem. For more information refer to 
*  the “Return Codes” section of the System Reference Guide.
*
*******************************************************************************/
cystatus bridging_console_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(bridging_console_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = bridging_console_I2CCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(bridging_console_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = bridging_console_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
    }
#if (!bridging_console_CY_SCBIP_V1)
    else if(bridging_console_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = bridging_console_SpiCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(bridging_console_SCB_MODE_UART_RUNTM_CFG)
    {
        status = bridging_console_UartCyBtldrCommRead(pData, size, count, timeOut);
    }
#endif /* (!bridging_console_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}


/*******************************************************************************
* Function Name: bridging_console_CyBtldrCommWrite
****************************************************************************//**
*
*  Allows the caller to write data to the bootloader host (the host reads the 
*  data). The function does not use timeout and returns after data has been copied
*  into the slave read buffer. This data available to be read by the bootloader
*  host until following host data write.
*
*  \param pData: Pointer to the block of data to be written to the bootloader host.
*  \param size: Number of bytes to be written.
*  \param count: Pointer to the variable to write the number of bytes actually
*   written.
*  \param timeOut: Number of units in 10 ms to wait before returning because of a
*   timeout.
*
*  \return
*  cystatus: Returns CYRET_SUCCESS if no problem was encountered or returns the
*  value that best describes the problem. For more information refer to 
*  the “Return Codes” section of the System Reference Guide.
*
*******************************************************************************/
cystatus bridging_console_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(bridging_console_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = bridging_console_I2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(bridging_console_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = bridging_console_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
#if (!bridging_console_CY_SCBIP_V1)
    else if(bridging_console_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = bridging_console_SpiCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(bridging_console_SCB_MODE_UART_RUNTM_CFG)
    {
        status = bridging_console_UartCyBtldrCommWrite(pData, size, count, timeOut);
    }
#endif /* (!bridging_console_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (bridging_console_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
