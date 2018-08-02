/***************************************************************************//**
* \file bridging_console_PINS.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
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

#if !defined(CY_SCB_PINS_bridging_console_H)
#define CY_SCB_PINS_bridging_console_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define bridging_console_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define bridging_console_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define bridging_console_REMOVE_TX_SDA_MISO_PIN      (1u)
#define bridging_console_REMOVE_CTS_SCLK_PIN      (1u)
#define bridging_console_REMOVE_RTS_SS0_PIN      (1u)
#define bridging_console_REMOVE_SS1_PIN                 (1u)
#define bridging_console_REMOVE_SS2_PIN                 (1u)
#define bridging_console_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define bridging_console_REMOVE_I2C_PINS                (1u)
#define bridging_console_REMOVE_SPI_MASTER_PINS         (1u)
#define bridging_console_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define bridging_console_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define bridging_console_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define bridging_console_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define bridging_console_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define bridging_console_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define bridging_console_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define bridging_console_REMOVE_SPI_SLAVE_PINS          (1u)
#define bridging_console_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define bridging_console_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define bridging_console_REMOVE_UART_TX_PIN             (0u)
#define bridging_console_REMOVE_UART_RX_TX_PIN          (1u)
#define bridging_console_REMOVE_UART_RX_PIN             (0u)
#define bridging_console_REMOVE_UART_RX_WAKE_PIN        (1u)
#define bridging_console_REMOVE_UART_RTS_PIN            (1u)
#define bridging_console_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define bridging_console_RX_WAKE_SCL_MOSI_PIN (0u == bridging_console_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define bridging_console_RX_SCL_MOSI_PIN     (0u == bridging_console_REMOVE_RX_SCL_MOSI_PIN)
#define bridging_console_TX_SDA_MISO_PIN     (0u == bridging_console_REMOVE_TX_SDA_MISO_PIN)
#define bridging_console_CTS_SCLK_PIN     (0u == bridging_console_REMOVE_CTS_SCLK_PIN)
#define bridging_console_RTS_SS0_PIN     (0u == bridging_console_REMOVE_RTS_SS0_PIN)
#define bridging_console_SS1_PIN                (0u == bridging_console_REMOVE_SS1_PIN)
#define bridging_console_SS2_PIN                (0u == bridging_console_REMOVE_SS2_PIN)
#define bridging_console_SS3_PIN                (0u == bridging_console_REMOVE_SS3_PIN)

/* Mode defined pins */
#define bridging_console_I2C_PINS               (0u == bridging_console_REMOVE_I2C_PINS)
#define bridging_console_SPI_MASTER_PINS        (0u == bridging_console_REMOVE_SPI_MASTER_PINS)
#define bridging_console_SPI_MASTER_SCLK_PIN    (0u == bridging_console_REMOVE_SPI_MASTER_SCLK_PIN)
#define bridging_console_SPI_MASTER_MOSI_PIN    (0u == bridging_console_REMOVE_SPI_MASTER_MOSI_PIN)
#define bridging_console_SPI_MASTER_MISO_PIN    (0u == bridging_console_REMOVE_SPI_MASTER_MISO_PIN)
#define bridging_console_SPI_MASTER_SS0_PIN     (0u == bridging_console_REMOVE_SPI_MASTER_SS0_PIN)
#define bridging_console_SPI_MASTER_SS1_PIN     (0u == bridging_console_REMOVE_SPI_MASTER_SS1_PIN)
#define bridging_console_SPI_MASTER_SS2_PIN     (0u == bridging_console_REMOVE_SPI_MASTER_SS2_PIN)
#define bridging_console_SPI_MASTER_SS3_PIN     (0u == bridging_console_REMOVE_SPI_MASTER_SS3_PIN)
#define bridging_console_SPI_SLAVE_PINS         (0u == bridging_console_REMOVE_SPI_SLAVE_PINS)
#define bridging_console_SPI_SLAVE_MOSI_PIN     (0u == bridging_console_REMOVE_SPI_SLAVE_MOSI_PIN)
#define bridging_console_SPI_SLAVE_MISO_PIN     (0u == bridging_console_REMOVE_SPI_SLAVE_MISO_PIN)
#define bridging_console_UART_TX_PIN            (0u == bridging_console_REMOVE_UART_TX_PIN)
#define bridging_console_UART_RX_TX_PIN         (0u == bridging_console_REMOVE_UART_RX_TX_PIN)
#define bridging_console_UART_RX_PIN            (0u == bridging_console_REMOVE_UART_RX_PIN)
#define bridging_console_UART_RX_WAKE_PIN       (0u == bridging_console_REMOVE_UART_RX_WAKE_PIN)
#define bridging_console_UART_RTS_PIN           (0u == bridging_console_REMOVE_UART_RTS_PIN)
#define bridging_console_UART_CTS_PIN           (0u == bridging_console_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (bridging_console_RX_WAKE_SCL_MOSI_PIN)
    #include "bridging_console_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (bridging_console_RX_SCL_MOSI) */

#if (bridging_console_RX_SCL_MOSI_PIN)
    #include "bridging_console_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (bridging_console_RX_SCL_MOSI) */

#if (bridging_console_TX_SDA_MISO_PIN)
    #include "bridging_console_uart_tx_i2c_sda_spi_miso.h"
#endif /* (bridging_console_TX_SDA_MISO) */

#if (bridging_console_CTS_SCLK_PIN)
    #include "bridging_console_uart_cts_spi_sclk.h"
#endif /* (bridging_console_CTS_SCLK) */

#if (bridging_console_RTS_SS0_PIN)
    #include "bridging_console_uart_rts_spi_ss0.h"
#endif /* (bridging_console_RTS_SS0_PIN) */

#if (bridging_console_SS1_PIN)
    #include "bridging_console_spi_ss1.h"
#endif /* (bridging_console_SS1_PIN) */

#if (bridging_console_SS2_PIN)
    #include "bridging_console_spi_ss2.h"
#endif /* (bridging_console_SS2_PIN) */

#if (bridging_console_SS3_PIN)
    #include "bridging_console_spi_ss3.h"
#endif /* (bridging_console_SS3_PIN) */

#if (bridging_console_I2C_PINS)
    #include "bridging_console_scl.h"
    #include "bridging_console_sda.h"
#endif /* (bridging_console_I2C_PINS) */

#if (bridging_console_SPI_MASTER_PINS)
#if (bridging_console_SPI_MASTER_SCLK_PIN)
    #include "bridging_console_sclk_m.h"
#endif /* (bridging_console_SPI_MASTER_SCLK_PIN) */

#if (bridging_console_SPI_MASTER_MOSI_PIN)
    #include "bridging_console_mosi_m.h"
#endif /* (bridging_console_SPI_MASTER_MOSI_PIN) */

#if (bridging_console_SPI_MASTER_MISO_PIN)
    #include "bridging_console_miso_m.h"
#endif /*(bridging_console_SPI_MASTER_MISO_PIN) */
#endif /* (bridging_console_SPI_MASTER_PINS) */

#if (bridging_console_SPI_SLAVE_PINS)
    #include "bridging_console_sclk_s.h"
    #include "bridging_console_ss_s.h"

#if (bridging_console_SPI_SLAVE_MOSI_PIN)
    #include "bridging_console_mosi_s.h"
#endif /* (bridging_console_SPI_SLAVE_MOSI_PIN) */

#if (bridging_console_SPI_SLAVE_MISO_PIN)
    #include "bridging_console_miso_s.h"
#endif /*(bridging_console_SPI_SLAVE_MISO_PIN) */
#endif /* (bridging_console_SPI_SLAVE_PINS) */

#if (bridging_console_SPI_MASTER_SS0_PIN)
    #include "bridging_console_ss0_m.h"
#endif /* (bridging_console_SPI_MASTER_SS0_PIN) */

#if (bridging_console_SPI_MASTER_SS1_PIN)
    #include "bridging_console_ss1_m.h"
#endif /* (bridging_console_SPI_MASTER_SS1_PIN) */

#if (bridging_console_SPI_MASTER_SS2_PIN)
    #include "bridging_console_ss2_m.h"
#endif /* (bridging_console_SPI_MASTER_SS2_PIN) */

#if (bridging_console_SPI_MASTER_SS3_PIN)
    #include "bridging_console_ss3_m.h"
#endif /* (bridging_console_SPI_MASTER_SS3_PIN) */

#if (bridging_console_UART_TX_PIN)
    #include "bridging_console_tx.h"
#endif /* (bridging_console_UART_TX_PIN) */

#if (bridging_console_UART_RX_TX_PIN)
    #include "bridging_console_rx_tx.h"
#endif /* (bridging_console_UART_RX_TX_PIN) */

#if (bridging_console_UART_RX_PIN)
    #include "bridging_console_rx.h"
#endif /* (bridging_console_UART_RX_PIN) */

#if (bridging_console_UART_RX_WAKE_PIN)
    #include "bridging_console_rx_wake.h"
#endif /* (bridging_console_UART_RX_WAKE_PIN) */

#if (bridging_console_UART_RTS_PIN)
    #include "bridging_console_rts.h"
#endif /* (bridging_console_UART_RTS_PIN) */

#if (bridging_console_UART_CTS_PIN)
    #include "bridging_console_cts.h"
#endif /* (bridging_console_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (bridging_console_RX_SCL_MOSI_PIN)
    #define bridging_console_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) bridging_console_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define bridging_console_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) bridging_console_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define bridging_console_RX_SCL_MOSI_HSIOM_MASK      (bridging_console_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define bridging_console_RX_SCL_MOSI_HSIOM_POS       (bridging_console_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define bridging_console_RX_SCL_MOSI_HSIOM_SEL_GPIO  (bridging_console_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define bridging_console_RX_SCL_MOSI_HSIOM_SEL_I2C   (bridging_console_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define bridging_console_RX_SCL_MOSI_HSIOM_SEL_SPI   (bridging_console_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define bridging_console_RX_SCL_MOSI_HSIOM_SEL_UART  (bridging_console_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (bridging_console_RX_WAKE_SCL_MOSI_PIN)
    #define bridging_console_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) bridging_console_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define bridging_console_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) bridging_console_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define bridging_console_RX_WAKE_SCL_MOSI_HSIOM_MASK      (bridging_console_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define bridging_console_RX_WAKE_SCL_MOSI_HSIOM_POS       (bridging_console_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define bridging_console_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (bridging_console_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define bridging_console_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (bridging_console_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define bridging_console_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (bridging_console_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define bridging_console_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (bridging_console_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define bridging_console_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) bridging_console_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define bridging_console_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) bridging_console_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define bridging_console_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (bridging_console_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define bridging_console_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) bridging_console_INTCFG_TYPE_MASK << \
                                                                           bridging_console_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins bridging_console_RX_SCL_MOSI_PIN or bridging_console_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (bridging_console_RX_SCL_MOSI_PIN) */

#if (bridging_console_TX_SDA_MISO_PIN)
    #define bridging_console_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) bridging_console_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define bridging_console_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) bridging_console_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define bridging_console_TX_SDA_MISO_HSIOM_MASK      (bridging_console_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define bridging_console_TX_SDA_MISO_HSIOM_POS       (bridging_console_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define bridging_console_TX_SDA_MISO_HSIOM_SEL_GPIO  (bridging_console_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define bridging_console_TX_SDA_MISO_HSIOM_SEL_I2C   (bridging_console_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define bridging_console_TX_SDA_MISO_HSIOM_SEL_SPI   (bridging_console_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define bridging_console_TX_SDA_MISO_HSIOM_SEL_UART  (bridging_console_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (bridging_console_TX_SDA_MISO_PIN) */

#if (bridging_console_CTS_SCLK_PIN)
    #define bridging_console_CTS_SCLK_HSIOM_REG   (*(reg32 *) bridging_console_uart_cts_spi_sclk__0__HSIOM)
    #define bridging_console_CTS_SCLK_HSIOM_PTR   ( (reg32 *) bridging_console_uart_cts_spi_sclk__0__HSIOM)
    
    #define bridging_console_CTS_SCLK_HSIOM_MASK      (bridging_console_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define bridging_console_CTS_SCLK_HSIOM_POS       (bridging_console_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define bridging_console_CTS_SCLK_HSIOM_SEL_GPIO  (bridging_console_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define bridging_console_CTS_SCLK_HSIOM_SEL_I2C   (bridging_console_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define bridging_console_CTS_SCLK_HSIOM_SEL_SPI   (bridging_console_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define bridging_console_CTS_SCLK_HSIOM_SEL_UART  (bridging_console_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (bridging_console_CTS_SCLK_PIN) */

#if (bridging_console_RTS_SS0_PIN)
    #define bridging_console_RTS_SS0_HSIOM_REG   (*(reg32 *) bridging_console_uart_rts_spi_ss0__0__HSIOM)
    #define bridging_console_RTS_SS0_HSIOM_PTR   ( (reg32 *) bridging_console_uart_rts_spi_ss0__0__HSIOM)
    
    #define bridging_console_RTS_SS0_HSIOM_MASK      (bridging_console_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define bridging_console_RTS_SS0_HSIOM_POS       (bridging_console_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define bridging_console_RTS_SS0_HSIOM_SEL_GPIO  (bridging_console_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define bridging_console_RTS_SS0_HSIOM_SEL_I2C   (bridging_console_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define bridging_console_RTS_SS0_HSIOM_SEL_SPI   (bridging_console_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1)
    #define bridging_console_RTS_SS0_HSIOM_SEL_UART  (bridging_console_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(bridging_console_CY_SCBIP_V0 || bridging_console_CY_SCBIP_V1) */
#endif /* (bridging_console_RTS_SS0_PIN) */

#if (bridging_console_SS1_PIN)
    #define bridging_console_SS1_HSIOM_REG  (*(reg32 *) bridging_console_spi_ss1__0__HSIOM)
    #define bridging_console_SS1_HSIOM_PTR  ( (reg32 *) bridging_console_spi_ss1__0__HSIOM)
    
    #define bridging_console_SS1_HSIOM_MASK     (bridging_console_spi_ss1__0__HSIOM_MASK)
    #define bridging_console_SS1_HSIOM_POS      (bridging_console_spi_ss1__0__HSIOM_SHIFT)
    #define bridging_console_SS1_HSIOM_SEL_GPIO (bridging_console_spi_ss1__0__HSIOM_GPIO)
    #define bridging_console_SS1_HSIOM_SEL_I2C  (bridging_console_spi_ss1__0__HSIOM_I2C)
    #define bridging_console_SS1_HSIOM_SEL_SPI  (bridging_console_spi_ss1__0__HSIOM_SPI)
#endif /* (bridging_console_SS1_PIN) */

#if (bridging_console_SS2_PIN)
    #define bridging_console_SS2_HSIOM_REG     (*(reg32 *) bridging_console_spi_ss2__0__HSIOM)
    #define bridging_console_SS2_HSIOM_PTR     ( (reg32 *) bridging_console_spi_ss2__0__HSIOM)
    
    #define bridging_console_SS2_HSIOM_MASK     (bridging_console_spi_ss2__0__HSIOM_MASK)
    #define bridging_console_SS2_HSIOM_POS      (bridging_console_spi_ss2__0__HSIOM_SHIFT)
    #define bridging_console_SS2_HSIOM_SEL_GPIO (bridging_console_spi_ss2__0__HSIOM_GPIO)
    #define bridging_console_SS2_HSIOM_SEL_I2C  (bridging_console_spi_ss2__0__HSIOM_I2C)
    #define bridging_console_SS2_HSIOM_SEL_SPI  (bridging_console_spi_ss2__0__HSIOM_SPI)
#endif /* (bridging_console_SS2_PIN) */

#if (bridging_console_SS3_PIN)
    #define bridging_console_SS3_HSIOM_REG     (*(reg32 *) bridging_console_spi_ss3__0__HSIOM)
    #define bridging_console_SS3_HSIOM_PTR     ( (reg32 *) bridging_console_spi_ss3__0__HSIOM)
    
    #define bridging_console_SS3_HSIOM_MASK     (bridging_console_spi_ss3__0__HSIOM_MASK)
    #define bridging_console_SS3_HSIOM_POS      (bridging_console_spi_ss3__0__HSIOM_SHIFT)
    #define bridging_console_SS3_HSIOM_SEL_GPIO (bridging_console_spi_ss3__0__HSIOM_GPIO)
    #define bridging_console_SS3_HSIOM_SEL_I2C  (bridging_console_spi_ss3__0__HSIOM_I2C)
    #define bridging_console_SS3_HSIOM_SEL_SPI  (bridging_console_spi_ss3__0__HSIOM_SPI)
#endif /* (bridging_console_SS3_PIN) */

#if (bridging_console_I2C_PINS)
    #define bridging_console_SCL_HSIOM_REG  (*(reg32 *) bridging_console_scl__0__HSIOM)
    #define bridging_console_SCL_HSIOM_PTR  ( (reg32 *) bridging_console_scl__0__HSIOM)
    
    #define bridging_console_SCL_HSIOM_MASK     (bridging_console_scl__0__HSIOM_MASK)
    #define bridging_console_SCL_HSIOM_POS      (bridging_console_scl__0__HSIOM_SHIFT)
    #define bridging_console_SCL_HSIOM_SEL_GPIO (bridging_console_sda__0__HSIOM_GPIO)
    #define bridging_console_SCL_HSIOM_SEL_I2C  (bridging_console_sda__0__HSIOM_I2C)
    
    #define bridging_console_SDA_HSIOM_REG  (*(reg32 *) bridging_console_sda__0__HSIOM)
    #define bridging_console_SDA_HSIOM_PTR  ( (reg32 *) bridging_console_sda__0__HSIOM)
    
    #define bridging_console_SDA_HSIOM_MASK     (bridging_console_sda__0__HSIOM_MASK)
    #define bridging_console_SDA_HSIOM_POS      (bridging_console_sda__0__HSIOM_SHIFT)
    #define bridging_console_SDA_HSIOM_SEL_GPIO (bridging_console_sda__0__HSIOM_GPIO)
    #define bridging_console_SDA_HSIOM_SEL_I2C  (bridging_console_sda__0__HSIOM_I2C)
#endif /* (bridging_console_I2C_PINS) */

#if (bridging_console_SPI_SLAVE_PINS)
    #define bridging_console_SCLK_S_HSIOM_REG   (*(reg32 *) bridging_console_sclk_s__0__HSIOM)
    #define bridging_console_SCLK_S_HSIOM_PTR   ( (reg32 *) bridging_console_sclk_s__0__HSIOM)
    
    #define bridging_console_SCLK_S_HSIOM_MASK      (bridging_console_sclk_s__0__HSIOM_MASK)
    #define bridging_console_SCLK_S_HSIOM_POS       (bridging_console_sclk_s__0__HSIOM_SHIFT)
    #define bridging_console_SCLK_S_HSIOM_SEL_GPIO  (bridging_console_sclk_s__0__HSIOM_GPIO)
    #define bridging_console_SCLK_S_HSIOM_SEL_SPI   (bridging_console_sclk_s__0__HSIOM_SPI)
    
    #define bridging_console_SS0_S_HSIOM_REG    (*(reg32 *) bridging_console_ss0_s__0__HSIOM)
    #define bridging_console_SS0_S_HSIOM_PTR    ( (reg32 *) bridging_console_ss0_s__0__HSIOM)
    
    #define bridging_console_SS0_S_HSIOM_MASK       (bridging_console_ss0_s__0__HSIOM_MASK)
    #define bridging_console_SS0_S_HSIOM_POS        (bridging_console_ss0_s__0__HSIOM_SHIFT)
    #define bridging_console_SS0_S_HSIOM_SEL_GPIO   (bridging_console_ss0_s__0__HSIOM_GPIO)  
    #define bridging_console_SS0_S_HSIOM_SEL_SPI    (bridging_console_ss0_s__0__HSIOM_SPI)
#endif /* (bridging_console_SPI_SLAVE_PINS) */

#if (bridging_console_SPI_SLAVE_MOSI_PIN)
    #define bridging_console_MOSI_S_HSIOM_REG   (*(reg32 *) bridging_console_mosi_s__0__HSIOM)
    #define bridging_console_MOSI_S_HSIOM_PTR   ( (reg32 *) bridging_console_mosi_s__0__HSIOM)
    
    #define bridging_console_MOSI_S_HSIOM_MASK      (bridging_console_mosi_s__0__HSIOM_MASK)
    #define bridging_console_MOSI_S_HSIOM_POS       (bridging_console_mosi_s__0__HSIOM_SHIFT)
    #define bridging_console_MOSI_S_HSIOM_SEL_GPIO  (bridging_console_mosi_s__0__HSIOM_GPIO)
    #define bridging_console_MOSI_S_HSIOM_SEL_SPI   (bridging_console_mosi_s__0__HSIOM_SPI)
#endif /* (bridging_console_SPI_SLAVE_MOSI_PIN) */

#if (bridging_console_SPI_SLAVE_MISO_PIN)
    #define bridging_console_MISO_S_HSIOM_REG   (*(reg32 *) bridging_console_miso_s__0__HSIOM)
    #define bridging_console_MISO_S_HSIOM_PTR   ( (reg32 *) bridging_console_miso_s__0__HSIOM)
    
    #define bridging_console_MISO_S_HSIOM_MASK      (bridging_console_miso_s__0__HSIOM_MASK)
    #define bridging_console_MISO_S_HSIOM_POS       (bridging_console_miso_s__0__HSIOM_SHIFT)
    #define bridging_console_MISO_S_HSIOM_SEL_GPIO  (bridging_console_miso_s__0__HSIOM_GPIO)
    #define bridging_console_MISO_S_HSIOM_SEL_SPI   (bridging_console_miso_s__0__HSIOM_SPI)
#endif /* (bridging_console_SPI_SLAVE_MISO_PIN) */

#if (bridging_console_SPI_MASTER_MISO_PIN)
    #define bridging_console_MISO_M_HSIOM_REG   (*(reg32 *) bridging_console_miso_m__0__HSIOM)
    #define bridging_console_MISO_M_HSIOM_PTR   ( (reg32 *) bridging_console_miso_m__0__HSIOM)
    
    #define bridging_console_MISO_M_HSIOM_MASK      (bridging_console_miso_m__0__HSIOM_MASK)
    #define bridging_console_MISO_M_HSIOM_POS       (bridging_console_miso_m__0__HSIOM_SHIFT)
    #define bridging_console_MISO_M_HSIOM_SEL_GPIO  (bridging_console_miso_m__0__HSIOM_GPIO)
    #define bridging_console_MISO_M_HSIOM_SEL_SPI   (bridging_console_miso_m__0__HSIOM_SPI)
#endif /* (bridging_console_SPI_MASTER_MISO_PIN) */

#if (bridging_console_SPI_MASTER_MOSI_PIN)
    #define bridging_console_MOSI_M_HSIOM_REG   (*(reg32 *) bridging_console_mosi_m__0__HSIOM)
    #define bridging_console_MOSI_M_HSIOM_PTR   ( (reg32 *) bridging_console_mosi_m__0__HSIOM)
    
    #define bridging_console_MOSI_M_HSIOM_MASK      (bridging_console_mosi_m__0__HSIOM_MASK)
    #define bridging_console_MOSI_M_HSIOM_POS       (bridging_console_mosi_m__0__HSIOM_SHIFT)
    #define bridging_console_MOSI_M_HSIOM_SEL_GPIO  (bridging_console_mosi_m__0__HSIOM_GPIO)
    #define bridging_console_MOSI_M_HSIOM_SEL_SPI   (bridging_console_mosi_m__0__HSIOM_SPI)
#endif /* (bridging_console_SPI_MASTER_MOSI_PIN) */

#if (bridging_console_SPI_MASTER_SCLK_PIN)
    #define bridging_console_SCLK_M_HSIOM_REG   (*(reg32 *) bridging_console_sclk_m__0__HSIOM)
    #define bridging_console_SCLK_M_HSIOM_PTR   ( (reg32 *) bridging_console_sclk_m__0__HSIOM)
    
    #define bridging_console_SCLK_M_HSIOM_MASK      (bridging_console_sclk_m__0__HSIOM_MASK)
    #define bridging_console_SCLK_M_HSIOM_POS       (bridging_console_sclk_m__0__HSIOM_SHIFT)
    #define bridging_console_SCLK_M_HSIOM_SEL_GPIO  (bridging_console_sclk_m__0__HSIOM_GPIO)
    #define bridging_console_SCLK_M_HSIOM_SEL_SPI   (bridging_console_sclk_m__0__HSIOM_SPI)
#endif /* (bridging_console_SPI_MASTER_SCLK_PIN) */

#if (bridging_console_SPI_MASTER_SS0_PIN)
    #define bridging_console_SS0_M_HSIOM_REG    (*(reg32 *) bridging_console_ss0_m__0__HSIOM)
    #define bridging_console_SS0_M_HSIOM_PTR    ( (reg32 *) bridging_console_ss0_m__0__HSIOM)
    
    #define bridging_console_SS0_M_HSIOM_MASK       (bridging_console_ss0_m__0__HSIOM_MASK)
    #define bridging_console_SS0_M_HSIOM_POS        (bridging_console_ss0_m__0__HSIOM_SHIFT)
    #define bridging_console_SS0_M_HSIOM_SEL_GPIO   (bridging_console_ss0_m__0__HSIOM_GPIO)
    #define bridging_console_SS0_M_HSIOM_SEL_SPI    (bridging_console_ss0_m__0__HSIOM_SPI)
#endif /* (bridging_console_SPI_MASTER_SS0_PIN) */

#if (bridging_console_SPI_MASTER_SS1_PIN)
    #define bridging_console_SS1_M_HSIOM_REG    (*(reg32 *) bridging_console_ss1_m__0__HSIOM)
    #define bridging_console_SS1_M_HSIOM_PTR    ( (reg32 *) bridging_console_ss1_m__0__HSIOM)
    
    #define bridging_console_SS1_M_HSIOM_MASK       (bridging_console_ss1_m__0__HSIOM_MASK)
    #define bridging_console_SS1_M_HSIOM_POS        (bridging_console_ss1_m__0__HSIOM_SHIFT)
    #define bridging_console_SS1_M_HSIOM_SEL_GPIO   (bridging_console_ss1_m__0__HSIOM_GPIO)
    #define bridging_console_SS1_M_HSIOM_SEL_SPI    (bridging_console_ss1_m__0__HSIOM_SPI)
#endif /* (bridging_console_SPI_MASTER_SS1_PIN) */

#if (bridging_console_SPI_MASTER_SS2_PIN)
    #define bridging_console_SS2_M_HSIOM_REG    (*(reg32 *) bridging_console_ss2_m__0__HSIOM)
    #define bridging_console_SS2_M_HSIOM_PTR    ( (reg32 *) bridging_console_ss2_m__0__HSIOM)
    
    #define bridging_console_SS2_M_HSIOM_MASK       (bridging_console_ss2_m__0__HSIOM_MASK)
    #define bridging_console_SS2_M_HSIOM_POS        (bridging_console_ss2_m__0__HSIOM_SHIFT)
    #define bridging_console_SS2_M_HSIOM_SEL_GPIO   (bridging_console_ss2_m__0__HSIOM_GPIO)
    #define bridging_console_SS2_M_HSIOM_SEL_SPI    (bridging_console_ss2_m__0__HSIOM_SPI)
#endif /* (bridging_console_SPI_MASTER_SS2_PIN) */

#if (bridging_console_SPI_MASTER_SS3_PIN)
    #define bridging_console_SS3_M_HSIOM_REG    (*(reg32 *) bridging_console_ss3_m__0__HSIOM)
    #define bridging_console_SS3_M_HSIOM_PTR    ( (reg32 *) bridging_console_ss3_m__0__HSIOM)
    
    #define bridging_console_SS3_M_HSIOM_MASK      (bridging_console_ss3_m__0__HSIOM_MASK)
    #define bridging_console_SS3_M_HSIOM_POS       (bridging_console_ss3_m__0__HSIOM_SHIFT)
    #define bridging_console_SS3_M_HSIOM_SEL_GPIO  (bridging_console_ss3_m__0__HSIOM_GPIO)
    #define bridging_console_SS3_M_HSIOM_SEL_SPI   (bridging_console_ss3_m__0__HSIOM_SPI)
#endif /* (bridging_console_SPI_MASTER_SS3_PIN) */

#if (bridging_console_UART_RX_PIN)
    #define bridging_console_RX_HSIOM_REG   (*(reg32 *) bridging_console_rx__0__HSIOM)
    #define bridging_console_RX_HSIOM_PTR   ( (reg32 *) bridging_console_rx__0__HSIOM)
    
    #define bridging_console_RX_HSIOM_MASK      (bridging_console_rx__0__HSIOM_MASK)
    #define bridging_console_RX_HSIOM_POS       (bridging_console_rx__0__HSIOM_SHIFT)
    #define bridging_console_RX_HSIOM_SEL_GPIO  (bridging_console_rx__0__HSIOM_GPIO)
    #define bridging_console_RX_HSIOM_SEL_UART  (bridging_console_rx__0__HSIOM_UART)
#endif /* (bridging_console_UART_RX_PIN) */

#if (bridging_console_UART_RX_WAKE_PIN)
    #define bridging_console_RX_WAKE_HSIOM_REG   (*(reg32 *) bridging_console_rx_wake__0__HSIOM)
    #define bridging_console_RX_WAKE_HSIOM_PTR   ( (reg32 *) bridging_console_rx_wake__0__HSIOM)
    
    #define bridging_console_RX_WAKE_HSIOM_MASK      (bridging_console_rx_wake__0__HSIOM_MASK)
    #define bridging_console_RX_WAKE_HSIOM_POS       (bridging_console_rx_wake__0__HSIOM_SHIFT)
    #define bridging_console_RX_WAKE_HSIOM_SEL_GPIO  (bridging_console_rx_wake__0__HSIOM_GPIO)
    #define bridging_console_RX_WAKE_HSIOM_SEL_UART  (bridging_console_rx_wake__0__HSIOM_UART)
#endif /* (bridging_console_UART_WAKE_RX_PIN) */

#if (bridging_console_UART_CTS_PIN)
    #define bridging_console_CTS_HSIOM_REG   (*(reg32 *) bridging_console_cts__0__HSIOM)
    #define bridging_console_CTS_HSIOM_PTR   ( (reg32 *) bridging_console_cts__0__HSIOM)
    
    #define bridging_console_CTS_HSIOM_MASK      (bridging_console_cts__0__HSIOM_MASK)
    #define bridging_console_CTS_HSIOM_POS       (bridging_console_cts__0__HSIOM_SHIFT)
    #define bridging_console_CTS_HSIOM_SEL_GPIO  (bridging_console_cts__0__HSIOM_GPIO)
    #define bridging_console_CTS_HSIOM_SEL_UART  (bridging_console_cts__0__HSIOM_UART)
#endif /* (bridging_console_UART_CTS_PIN) */

#if (bridging_console_UART_TX_PIN)
    #define bridging_console_TX_HSIOM_REG   (*(reg32 *) bridging_console_tx__0__HSIOM)
    #define bridging_console_TX_HSIOM_PTR   ( (reg32 *) bridging_console_tx__0__HSIOM)
    
    #define bridging_console_TX_HSIOM_MASK      (bridging_console_tx__0__HSIOM_MASK)
    #define bridging_console_TX_HSIOM_POS       (bridging_console_tx__0__HSIOM_SHIFT)
    #define bridging_console_TX_HSIOM_SEL_GPIO  (bridging_console_tx__0__HSIOM_GPIO)
    #define bridging_console_TX_HSIOM_SEL_UART  (bridging_console_tx__0__HSIOM_UART)
#endif /* (bridging_console_UART_TX_PIN) */

#if (bridging_console_UART_RX_TX_PIN)
    #define bridging_console_RX_TX_HSIOM_REG   (*(reg32 *) bridging_console_rx_tx__0__HSIOM)
    #define bridging_console_RX_TX_HSIOM_PTR   ( (reg32 *) bridging_console_rx_tx__0__HSIOM)
    
    #define bridging_console_RX_TX_HSIOM_MASK      (bridging_console_rx_tx__0__HSIOM_MASK)
    #define bridging_console_RX_TX_HSIOM_POS       (bridging_console_rx_tx__0__HSIOM_SHIFT)
    #define bridging_console_RX_TX_HSIOM_SEL_GPIO  (bridging_console_rx_tx__0__HSIOM_GPIO)
    #define bridging_console_RX_TX_HSIOM_SEL_UART  (bridging_console_rx_tx__0__HSIOM_UART)
#endif /* (bridging_console_UART_RX_TX_PIN) */

#if (bridging_console_UART_RTS_PIN)
    #define bridging_console_RTS_HSIOM_REG      (*(reg32 *) bridging_console_rts__0__HSIOM)
    #define bridging_console_RTS_HSIOM_PTR      ( (reg32 *) bridging_console_rts__0__HSIOM)
    
    #define bridging_console_RTS_HSIOM_MASK     (bridging_console_rts__0__HSIOM_MASK)
    #define bridging_console_RTS_HSIOM_POS      (bridging_console_rts__0__HSIOM_SHIFT)    
    #define bridging_console_RTS_HSIOM_SEL_GPIO (bridging_console_rts__0__HSIOM_GPIO)
    #define bridging_console_RTS_HSIOM_SEL_UART (bridging_console_rts__0__HSIOM_UART)    
#endif /* (bridging_console_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define bridging_console_HSIOM_DEF_SEL      (0x00u)
#define bridging_console_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for bridging_console_CY_SCBIP_V0 
* and bridging_console_CY_SCBIP_V1. It is not recommended to use them for 
* bridging_console_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define bridging_console_HSIOM_UART_SEL     (0x09u)
#define bridging_console_HSIOM_I2C_SEL      (0x0Eu)
#define bridging_console_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define bridging_console_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define bridging_console_RX_SCL_MOSI_PIN_INDEX       (0u)
#define bridging_console_TX_SDA_MISO_PIN_INDEX       (1u)
#define bridging_console_CTS_SCLK_PIN_INDEX       (2u)
#define bridging_console_RTS_SS0_PIN_INDEX       (3u)
#define bridging_console_SS1_PIN_INDEX                  (4u)
#define bridging_console_SS2_PIN_INDEX                  (5u)
#define bridging_console_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define bridging_console_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << bridging_console_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define bridging_console_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << bridging_console_RX_SCL_MOSI_PIN_INDEX)
#define bridging_console_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << bridging_console_TX_SDA_MISO_PIN_INDEX)
#define bridging_console_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << bridging_console_CTS_SCLK_PIN_INDEX)
#define bridging_console_RTS_SS0_PIN_MASK     ((uint32) 0x01u << bridging_console_RTS_SS0_PIN_INDEX)
#define bridging_console_SS1_PIN_MASK                ((uint32) 0x01u << bridging_console_SS1_PIN_INDEX)
#define bridging_console_SS2_PIN_MASK                ((uint32) 0x01u << bridging_console_SS2_PIN_INDEX)
#define bridging_console_SS3_PIN_MASK                ((uint32) 0x01u << bridging_console_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define bridging_console_INTCFG_TYPE_MASK           (0x03u)
#define bridging_console_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define bridging_console_PIN_DM_ALG_HIZ  (0u)
#define bridging_console_PIN_DM_DIG_HIZ  (1u)
#define bridging_console_PIN_DM_OD_LO    (4u)
#define bridging_console_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define bridging_console_DM_MASK    (0x7u)
#define bridging_console_DM_SIZE    (3u)
#define bridging_console_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) bridging_console_DM_MASK << (bridging_console_DM_SIZE * (pos)))) >> \
                                                              (bridging_console_DM_SIZE * (pos)) )

#if (bridging_console_TX_SDA_MISO_PIN)
    #define bridging_console_CHECK_TX_SDA_MISO_PIN_USED \
                (bridging_console_PIN_DM_ALG_HIZ != \
                    bridging_console_GET_P4_PIN_DM(bridging_console_uart_tx_i2c_sda_spi_miso_PC, \
                                                   bridging_console_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (bridging_console_TX_SDA_MISO_PIN) */

#if (bridging_console_RTS_SS0_PIN)
    #define bridging_console_CHECK_RTS_SS0_PIN_USED \
                (bridging_console_PIN_DM_ALG_HIZ != \
                    bridging_console_GET_P4_PIN_DM(bridging_console_uart_rts_spi_ss0_PC, \
                                                   bridging_console_uart_rts_spi_ss0_SHIFT))
#endif /* (bridging_console_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define bridging_console_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define bridging_console_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define bridging_console_SET_HSIOM_SEL(reg, mask, pos, sel) bridging_console_SET_REGISTER_BITS(reg, mask, pos, sel)
#define bridging_console_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        bridging_console_SET_REGISTER_BITS(reg, mask, pos, intType)
#define bridging_console_SET_INP_DIS(reg, mask, val) bridging_console_SET_REGISTER_BIT(reg, mask, val)

/* bridging_console_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  bridging_console_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (bridging_console_CY_SCBIP_V0)
#if (bridging_console_I2C_PINS)
    #define bridging_console_SET_I2C_SCL_DR(val) bridging_console_scl_Write(val)

    #define bridging_console_SET_I2C_SCL_HSIOM_SEL(sel) \
                          bridging_console_SET_HSIOM_SEL(bridging_console_SCL_HSIOM_REG,  \
                                                         bridging_console_SCL_HSIOM_MASK, \
                                                         bridging_console_SCL_HSIOM_POS,  \
                                                         (sel))
    #define bridging_console_WAIT_SCL_SET_HIGH  (0u == bridging_console_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (bridging_console_RX_WAKE_SCL_MOSI_PIN)
    #define bridging_console_SET_I2C_SCL_DR(val) \
                            bridging_console_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define bridging_console_SET_I2C_SCL_HSIOM_SEL(sel) \
                    bridging_console_SET_HSIOM_SEL(bridging_console_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   bridging_console_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   bridging_console_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define bridging_console_WAIT_SCL_SET_HIGH  (0u == bridging_console_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (bridging_console_RX_SCL_MOSI_PIN)
    #define bridging_console_SET_I2C_SCL_DR(val) \
                            bridging_console_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define bridging_console_SET_I2C_SCL_HSIOM_SEL(sel) \
                            bridging_console_SET_HSIOM_SEL(bridging_console_RX_SCL_MOSI_HSIOM_REG,  \
                                                           bridging_console_RX_SCL_MOSI_HSIOM_MASK, \
                                                           bridging_console_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define bridging_console_WAIT_SCL_SET_HIGH  (0u == bridging_console_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define bridging_console_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define bridging_console_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define bridging_console_WAIT_SCL_SET_HIGH  (0u)
#endif /* (bridging_console_I2C_PINS) */

/* SCB I2C: sda signal */
#if (bridging_console_I2C_PINS)
    #define bridging_console_WAIT_SDA_SET_HIGH  (0u == bridging_console_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (bridging_console_TX_SDA_MISO_PIN)
    #define bridging_console_WAIT_SDA_SET_HIGH  (0u == bridging_console_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define bridging_console_WAIT_SDA_SET_HIGH  (0u)
#endif /* (bridging_console_MOSI_SCL_RX_PIN) */
#endif /* (bridging_console_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (bridging_console_RX_SCL_MOSI_PIN)
    #define bridging_console_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (bridging_console_RX_WAKE_SCL_MOSI_PIN)
    #define bridging_console_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) bridging_console_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(bridging_console_UART_RX_WAKE_PIN)
    #define bridging_console_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) bridging_console_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (bridging_console_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define bridging_console_REMOVE_MOSI_SCL_RX_WAKE_PIN    bridging_console_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define bridging_console_REMOVE_MOSI_SCL_RX_PIN         bridging_console_REMOVE_RX_SCL_MOSI_PIN
#define bridging_console_REMOVE_MISO_SDA_TX_PIN         bridging_console_REMOVE_TX_SDA_MISO_PIN
#ifndef bridging_console_REMOVE_SCLK_PIN
#define bridging_console_REMOVE_SCLK_PIN                bridging_console_REMOVE_CTS_SCLK_PIN
#endif /* bridging_console_REMOVE_SCLK_PIN */
#ifndef bridging_console_REMOVE_SS0_PIN
#define bridging_console_REMOVE_SS0_PIN                 bridging_console_REMOVE_RTS_SS0_PIN
#endif /* bridging_console_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define bridging_console_MOSI_SCL_RX_WAKE_PIN   bridging_console_RX_WAKE_SCL_MOSI_PIN
#define bridging_console_MOSI_SCL_RX_PIN        bridging_console_RX_SCL_MOSI_PIN
#define bridging_console_MISO_SDA_TX_PIN        bridging_console_TX_SDA_MISO_PIN
#ifndef bridging_console_SCLK_PIN
#define bridging_console_SCLK_PIN               bridging_console_CTS_SCLK_PIN
#endif /* bridging_console_SCLK_PIN */
#ifndef bridging_console_SS0_PIN
#define bridging_console_SS0_PIN                bridging_console_RTS_SS0_PIN
#endif /* bridging_console_SS0_PIN */

#if (bridging_console_MOSI_SCL_RX_WAKE_PIN)
    #define bridging_console_MOSI_SCL_RX_WAKE_HSIOM_REG     bridging_console_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define bridging_console_MOSI_SCL_RX_WAKE_HSIOM_PTR     bridging_console_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define bridging_console_MOSI_SCL_RX_WAKE_HSIOM_MASK    bridging_console_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define bridging_console_MOSI_SCL_RX_WAKE_HSIOM_POS     bridging_console_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define bridging_console_MOSI_SCL_RX_WAKE_INTCFG_REG    bridging_console_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define bridging_console_MOSI_SCL_RX_WAKE_INTCFG_PTR    bridging_console_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define bridging_console_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   bridging_console_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define bridging_console_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  bridging_console_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (bridging_console_RX_WAKE_SCL_MOSI_PIN) */

#if (bridging_console_MOSI_SCL_RX_PIN)
    #define bridging_console_MOSI_SCL_RX_HSIOM_REG      bridging_console_RX_SCL_MOSI_HSIOM_REG
    #define bridging_console_MOSI_SCL_RX_HSIOM_PTR      bridging_console_RX_SCL_MOSI_HSIOM_PTR
    #define bridging_console_MOSI_SCL_RX_HSIOM_MASK     bridging_console_RX_SCL_MOSI_HSIOM_MASK
    #define bridging_console_MOSI_SCL_RX_HSIOM_POS      bridging_console_RX_SCL_MOSI_HSIOM_POS
#endif /* (bridging_console_MOSI_SCL_RX_PIN) */

#if (bridging_console_MISO_SDA_TX_PIN)
    #define bridging_console_MISO_SDA_TX_HSIOM_REG      bridging_console_TX_SDA_MISO_HSIOM_REG
    #define bridging_console_MISO_SDA_TX_HSIOM_PTR      bridging_console_TX_SDA_MISO_HSIOM_REG
    #define bridging_console_MISO_SDA_TX_HSIOM_MASK     bridging_console_TX_SDA_MISO_HSIOM_REG
    #define bridging_console_MISO_SDA_TX_HSIOM_POS      bridging_console_TX_SDA_MISO_HSIOM_REG
#endif /* (bridging_console_MISO_SDA_TX_PIN_PIN) */

#if (bridging_console_SCLK_PIN)
    #ifndef bridging_console_SCLK_HSIOM_REG
    #define bridging_console_SCLK_HSIOM_REG     bridging_console_CTS_SCLK_HSIOM_REG
    #define bridging_console_SCLK_HSIOM_PTR     bridging_console_CTS_SCLK_HSIOM_PTR
    #define bridging_console_SCLK_HSIOM_MASK    bridging_console_CTS_SCLK_HSIOM_MASK
    #define bridging_console_SCLK_HSIOM_POS     bridging_console_CTS_SCLK_HSIOM_POS
    #endif /* bridging_console_SCLK_HSIOM_REG */
#endif /* (bridging_console_SCLK_PIN) */

#if (bridging_console_SS0_PIN)
    #ifndef bridging_console_SS0_HSIOM_REG
    #define bridging_console_SS0_HSIOM_REG      bridging_console_RTS_SS0_HSIOM_REG
    #define bridging_console_SS0_HSIOM_PTR      bridging_console_RTS_SS0_HSIOM_PTR
    #define bridging_console_SS0_HSIOM_MASK     bridging_console_RTS_SS0_HSIOM_MASK
    #define bridging_console_SS0_HSIOM_POS      bridging_console_RTS_SS0_HSIOM_POS
    #endif /* bridging_console_SS0_HSIOM_REG */
#endif /* (bridging_console_SS0_PIN) */

#define bridging_console_MOSI_SCL_RX_WAKE_PIN_INDEX bridging_console_RX_WAKE_SCL_MOSI_PIN_INDEX
#define bridging_console_MOSI_SCL_RX_PIN_INDEX      bridging_console_RX_SCL_MOSI_PIN_INDEX
#define bridging_console_MISO_SDA_TX_PIN_INDEX      bridging_console_TX_SDA_MISO_PIN_INDEX
#ifndef bridging_console_SCLK_PIN_INDEX
#define bridging_console_SCLK_PIN_INDEX             bridging_console_CTS_SCLK_PIN_INDEX
#endif /* bridging_console_SCLK_PIN_INDEX */
#ifndef bridging_console_SS0_PIN_INDEX
#define bridging_console_SS0_PIN_INDEX              bridging_console_RTS_SS0_PIN_INDEX
#endif /* bridging_console_SS0_PIN_INDEX */

#define bridging_console_MOSI_SCL_RX_WAKE_PIN_MASK bridging_console_RX_WAKE_SCL_MOSI_PIN_MASK
#define bridging_console_MOSI_SCL_RX_PIN_MASK      bridging_console_RX_SCL_MOSI_PIN_MASK
#define bridging_console_MISO_SDA_TX_PIN_MASK      bridging_console_TX_SDA_MISO_PIN_MASK
#ifndef bridging_console_SCLK_PIN_MASK
#define bridging_console_SCLK_PIN_MASK             bridging_console_CTS_SCLK_PIN_MASK
#endif /* bridging_console_SCLK_PIN_MASK */
#ifndef bridging_console_SS0_PIN_MASK
#define bridging_console_SS0_PIN_MASK              bridging_console_RTS_SS0_PIN_MASK
#endif /* bridging_console_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_bridging_console_H) */


/* [] END OF FILE */
