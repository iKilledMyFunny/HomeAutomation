/***************************************************************************//**
* \file from_ble_PINS.h
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

#if !defined(CY_SCB_PINS_from_ble_H)
#define CY_SCB_PINS_from_ble_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define from_ble_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define from_ble_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define from_ble_REMOVE_TX_SDA_MISO_PIN      (1u)
#define from_ble_REMOVE_CTS_SCLK_PIN      (1u)
#define from_ble_REMOVE_RTS_SS0_PIN      (1u)
#define from_ble_REMOVE_SS1_PIN                 (1u)
#define from_ble_REMOVE_SS2_PIN                 (1u)
#define from_ble_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define from_ble_REMOVE_I2C_PINS                (1u)
#define from_ble_REMOVE_SPI_MASTER_PINS         (1u)
#define from_ble_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define from_ble_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define from_ble_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define from_ble_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define from_ble_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define from_ble_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define from_ble_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define from_ble_REMOVE_SPI_SLAVE_PINS          (1u)
#define from_ble_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define from_ble_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define from_ble_REMOVE_UART_TX_PIN             (0u)
#define from_ble_REMOVE_UART_RX_TX_PIN          (1u)
#define from_ble_REMOVE_UART_RX_PIN             (0u)
#define from_ble_REMOVE_UART_RX_WAKE_PIN        (1u)
#define from_ble_REMOVE_UART_RTS_PIN            (1u)
#define from_ble_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define from_ble_RX_WAKE_SCL_MOSI_PIN (0u == from_ble_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define from_ble_RX_SCL_MOSI_PIN     (0u == from_ble_REMOVE_RX_SCL_MOSI_PIN)
#define from_ble_TX_SDA_MISO_PIN     (0u == from_ble_REMOVE_TX_SDA_MISO_PIN)
#define from_ble_CTS_SCLK_PIN     (0u == from_ble_REMOVE_CTS_SCLK_PIN)
#define from_ble_RTS_SS0_PIN     (0u == from_ble_REMOVE_RTS_SS0_PIN)
#define from_ble_SS1_PIN                (0u == from_ble_REMOVE_SS1_PIN)
#define from_ble_SS2_PIN                (0u == from_ble_REMOVE_SS2_PIN)
#define from_ble_SS3_PIN                (0u == from_ble_REMOVE_SS3_PIN)

/* Mode defined pins */
#define from_ble_I2C_PINS               (0u == from_ble_REMOVE_I2C_PINS)
#define from_ble_SPI_MASTER_PINS        (0u == from_ble_REMOVE_SPI_MASTER_PINS)
#define from_ble_SPI_MASTER_SCLK_PIN    (0u == from_ble_REMOVE_SPI_MASTER_SCLK_PIN)
#define from_ble_SPI_MASTER_MOSI_PIN    (0u == from_ble_REMOVE_SPI_MASTER_MOSI_PIN)
#define from_ble_SPI_MASTER_MISO_PIN    (0u == from_ble_REMOVE_SPI_MASTER_MISO_PIN)
#define from_ble_SPI_MASTER_SS0_PIN     (0u == from_ble_REMOVE_SPI_MASTER_SS0_PIN)
#define from_ble_SPI_MASTER_SS1_PIN     (0u == from_ble_REMOVE_SPI_MASTER_SS1_PIN)
#define from_ble_SPI_MASTER_SS2_PIN     (0u == from_ble_REMOVE_SPI_MASTER_SS2_PIN)
#define from_ble_SPI_MASTER_SS3_PIN     (0u == from_ble_REMOVE_SPI_MASTER_SS3_PIN)
#define from_ble_SPI_SLAVE_PINS         (0u == from_ble_REMOVE_SPI_SLAVE_PINS)
#define from_ble_SPI_SLAVE_MOSI_PIN     (0u == from_ble_REMOVE_SPI_SLAVE_MOSI_PIN)
#define from_ble_SPI_SLAVE_MISO_PIN     (0u == from_ble_REMOVE_SPI_SLAVE_MISO_PIN)
#define from_ble_UART_TX_PIN            (0u == from_ble_REMOVE_UART_TX_PIN)
#define from_ble_UART_RX_TX_PIN         (0u == from_ble_REMOVE_UART_RX_TX_PIN)
#define from_ble_UART_RX_PIN            (0u == from_ble_REMOVE_UART_RX_PIN)
#define from_ble_UART_RX_WAKE_PIN       (0u == from_ble_REMOVE_UART_RX_WAKE_PIN)
#define from_ble_UART_RTS_PIN           (0u == from_ble_REMOVE_UART_RTS_PIN)
#define from_ble_UART_CTS_PIN           (0u == from_ble_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (from_ble_RX_WAKE_SCL_MOSI_PIN)
    #include "from_ble_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (from_ble_RX_SCL_MOSI) */

#if (from_ble_RX_SCL_MOSI_PIN)
    #include "from_ble_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (from_ble_RX_SCL_MOSI) */

#if (from_ble_TX_SDA_MISO_PIN)
    #include "from_ble_uart_tx_i2c_sda_spi_miso.h"
#endif /* (from_ble_TX_SDA_MISO) */

#if (from_ble_CTS_SCLK_PIN)
    #include "from_ble_uart_cts_spi_sclk.h"
#endif /* (from_ble_CTS_SCLK) */

#if (from_ble_RTS_SS0_PIN)
    #include "from_ble_uart_rts_spi_ss0.h"
#endif /* (from_ble_RTS_SS0_PIN) */

#if (from_ble_SS1_PIN)
    #include "from_ble_spi_ss1.h"
#endif /* (from_ble_SS1_PIN) */

#if (from_ble_SS2_PIN)
    #include "from_ble_spi_ss2.h"
#endif /* (from_ble_SS2_PIN) */

#if (from_ble_SS3_PIN)
    #include "from_ble_spi_ss3.h"
#endif /* (from_ble_SS3_PIN) */

#if (from_ble_I2C_PINS)
    #include "from_ble_scl.h"
    #include "from_ble_sda.h"
#endif /* (from_ble_I2C_PINS) */

#if (from_ble_SPI_MASTER_PINS)
#if (from_ble_SPI_MASTER_SCLK_PIN)
    #include "from_ble_sclk_m.h"
#endif /* (from_ble_SPI_MASTER_SCLK_PIN) */

#if (from_ble_SPI_MASTER_MOSI_PIN)
    #include "from_ble_mosi_m.h"
#endif /* (from_ble_SPI_MASTER_MOSI_PIN) */

#if (from_ble_SPI_MASTER_MISO_PIN)
    #include "from_ble_miso_m.h"
#endif /*(from_ble_SPI_MASTER_MISO_PIN) */
#endif /* (from_ble_SPI_MASTER_PINS) */

#if (from_ble_SPI_SLAVE_PINS)
    #include "from_ble_sclk_s.h"
    #include "from_ble_ss_s.h"

#if (from_ble_SPI_SLAVE_MOSI_PIN)
    #include "from_ble_mosi_s.h"
#endif /* (from_ble_SPI_SLAVE_MOSI_PIN) */

#if (from_ble_SPI_SLAVE_MISO_PIN)
    #include "from_ble_miso_s.h"
#endif /*(from_ble_SPI_SLAVE_MISO_PIN) */
#endif /* (from_ble_SPI_SLAVE_PINS) */

#if (from_ble_SPI_MASTER_SS0_PIN)
    #include "from_ble_ss0_m.h"
#endif /* (from_ble_SPI_MASTER_SS0_PIN) */

#if (from_ble_SPI_MASTER_SS1_PIN)
    #include "from_ble_ss1_m.h"
#endif /* (from_ble_SPI_MASTER_SS1_PIN) */

#if (from_ble_SPI_MASTER_SS2_PIN)
    #include "from_ble_ss2_m.h"
#endif /* (from_ble_SPI_MASTER_SS2_PIN) */

#if (from_ble_SPI_MASTER_SS3_PIN)
    #include "from_ble_ss3_m.h"
#endif /* (from_ble_SPI_MASTER_SS3_PIN) */

#if (from_ble_UART_TX_PIN)
    #include "from_ble_tx.h"
#endif /* (from_ble_UART_TX_PIN) */

#if (from_ble_UART_RX_TX_PIN)
    #include "from_ble_rx_tx.h"
#endif /* (from_ble_UART_RX_TX_PIN) */

#if (from_ble_UART_RX_PIN)
    #include "from_ble_rx.h"
#endif /* (from_ble_UART_RX_PIN) */

#if (from_ble_UART_RX_WAKE_PIN)
    #include "from_ble_rx_wake.h"
#endif /* (from_ble_UART_RX_WAKE_PIN) */

#if (from_ble_UART_RTS_PIN)
    #include "from_ble_rts.h"
#endif /* (from_ble_UART_RTS_PIN) */

#if (from_ble_UART_CTS_PIN)
    #include "from_ble_cts.h"
#endif /* (from_ble_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (from_ble_RX_SCL_MOSI_PIN)
    #define from_ble_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) from_ble_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define from_ble_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) from_ble_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define from_ble_RX_SCL_MOSI_HSIOM_MASK      (from_ble_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define from_ble_RX_SCL_MOSI_HSIOM_POS       (from_ble_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define from_ble_RX_SCL_MOSI_HSIOM_SEL_GPIO  (from_ble_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define from_ble_RX_SCL_MOSI_HSIOM_SEL_I2C   (from_ble_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define from_ble_RX_SCL_MOSI_HSIOM_SEL_SPI   (from_ble_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define from_ble_RX_SCL_MOSI_HSIOM_SEL_UART  (from_ble_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (from_ble_RX_WAKE_SCL_MOSI_PIN)
    #define from_ble_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) from_ble_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define from_ble_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) from_ble_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define from_ble_RX_WAKE_SCL_MOSI_HSIOM_MASK      (from_ble_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define from_ble_RX_WAKE_SCL_MOSI_HSIOM_POS       (from_ble_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define from_ble_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (from_ble_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define from_ble_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (from_ble_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define from_ble_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (from_ble_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define from_ble_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (from_ble_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define from_ble_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) from_ble_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define from_ble_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) from_ble_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define from_ble_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (from_ble_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define from_ble_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) from_ble_INTCFG_TYPE_MASK << \
                                                                           from_ble_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins from_ble_RX_SCL_MOSI_PIN or from_ble_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (from_ble_RX_SCL_MOSI_PIN) */

#if (from_ble_TX_SDA_MISO_PIN)
    #define from_ble_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) from_ble_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define from_ble_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) from_ble_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define from_ble_TX_SDA_MISO_HSIOM_MASK      (from_ble_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define from_ble_TX_SDA_MISO_HSIOM_POS       (from_ble_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define from_ble_TX_SDA_MISO_HSIOM_SEL_GPIO  (from_ble_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define from_ble_TX_SDA_MISO_HSIOM_SEL_I2C   (from_ble_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define from_ble_TX_SDA_MISO_HSIOM_SEL_SPI   (from_ble_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define from_ble_TX_SDA_MISO_HSIOM_SEL_UART  (from_ble_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (from_ble_TX_SDA_MISO_PIN) */

#if (from_ble_CTS_SCLK_PIN)
    #define from_ble_CTS_SCLK_HSIOM_REG   (*(reg32 *) from_ble_uart_cts_spi_sclk__0__HSIOM)
    #define from_ble_CTS_SCLK_HSIOM_PTR   ( (reg32 *) from_ble_uart_cts_spi_sclk__0__HSIOM)
    
    #define from_ble_CTS_SCLK_HSIOM_MASK      (from_ble_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define from_ble_CTS_SCLK_HSIOM_POS       (from_ble_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define from_ble_CTS_SCLK_HSIOM_SEL_GPIO  (from_ble_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define from_ble_CTS_SCLK_HSIOM_SEL_I2C   (from_ble_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define from_ble_CTS_SCLK_HSIOM_SEL_SPI   (from_ble_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define from_ble_CTS_SCLK_HSIOM_SEL_UART  (from_ble_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (from_ble_CTS_SCLK_PIN) */

#if (from_ble_RTS_SS0_PIN)
    #define from_ble_RTS_SS0_HSIOM_REG   (*(reg32 *) from_ble_uart_rts_spi_ss0__0__HSIOM)
    #define from_ble_RTS_SS0_HSIOM_PTR   ( (reg32 *) from_ble_uart_rts_spi_ss0__0__HSIOM)
    
    #define from_ble_RTS_SS0_HSIOM_MASK      (from_ble_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define from_ble_RTS_SS0_HSIOM_POS       (from_ble_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define from_ble_RTS_SS0_HSIOM_SEL_GPIO  (from_ble_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define from_ble_RTS_SS0_HSIOM_SEL_I2C   (from_ble_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define from_ble_RTS_SS0_HSIOM_SEL_SPI   (from_ble_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1)
    #define from_ble_RTS_SS0_HSIOM_SEL_UART  (from_ble_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(from_ble_CY_SCBIP_V0 || from_ble_CY_SCBIP_V1) */
#endif /* (from_ble_RTS_SS0_PIN) */

#if (from_ble_SS1_PIN)
    #define from_ble_SS1_HSIOM_REG  (*(reg32 *) from_ble_spi_ss1__0__HSIOM)
    #define from_ble_SS1_HSIOM_PTR  ( (reg32 *) from_ble_spi_ss1__0__HSIOM)
    
    #define from_ble_SS1_HSIOM_MASK     (from_ble_spi_ss1__0__HSIOM_MASK)
    #define from_ble_SS1_HSIOM_POS      (from_ble_spi_ss1__0__HSIOM_SHIFT)
    #define from_ble_SS1_HSIOM_SEL_GPIO (from_ble_spi_ss1__0__HSIOM_GPIO)
    #define from_ble_SS1_HSIOM_SEL_I2C  (from_ble_spi_ss1__0__HSIOM_I2C)
    #define from_ble_SS1_HSIOM_SEL_SPI  (from_ble_spi_ss1__0__HSIOM_SPI)
#endif /* (from_ble_SS1_PIN) */

#if (from_ble_SS2_PIN)
    #define from_ble_SS2_HSIOM_REG     (*(reg32 *) from_ble_spi_ss2__0__HSIOM)
    #define from_ble_SS2_HSIOM_PTR     ( (reg32 *) from_ble_spi_ss2__0__HSIOM)
    
    #define from_ble_SS2_HSIOM_MASK     (from_ble_spi_ss2__0__HSIOM_MASK)
    #define from_ble_SS2_HSIOM_POS      (from_ble_spi_ss2__0__HSIOM_SHIFT)
    #define from_ble_SS2_HSIOM_SEL_GPIO (from_ble_spi_ss2__0__HSIOM_GPIO)
    #define from_ble_SS2_HSIOM_SEL_I2C  (from_ble_spi_ss2__0__HSIOM_I2C)
    #define from_ble_SS2_HSIOM_SEL_SPI  (from_ble_spi_ss2__0__HSIOM_SPI)
#endif /* (from_ble_SS2_PIN) */

#if (from_ble_SS3_PIN)
    #define from_ble_SS3_HSIOM_REG     (*(reg32 *) from_ble_spi_ss3__0__HSIOM)
    #define from_ble_SS3_HSIOM_PTR     ( (reg32 *) from_ble_spi_ss3__0__HSIOM)
    
    #define from_ble_SS3_HSIOM_MASK     (from_ble_spi_ss3__0__HSIOM_MASK)
    #define from_ble_SS3_HSIOM_POS      (from_ble_spi_ss3__0__HSIOM_SHIFT)
    #define from_ble_SS3_HSIOM_SEL_GPIO (from_ble_spi_ss3__0__HSIOM_GPIO)
    #define from_ble_SS3_HSIOM_SEL_I2C  (from_ble_spi_ss3__0__HSIOM_I2C)
    #define from_ble_SS3_HSIOM_SEL_SPI  (from_ble_spi_ss3__0__HSIOM_SPI)
#endif /* (from_ble_SS3_PIN) */

#if (from_ble_I2C_PINS)
    #define from_ble_SCL_HSIOM_REG  (*(reg32 *) from_ble_scl__0__HSIOM)
    #define from_ble_SCL_HSIOM_PTR  ( (reg32 *) from_ble_scl__0__HSIOM)
    
    #define from_ble_SCL_HSIOM_MASK     (from_ble_scl__0__HSIOM_MASK)
    #define from_ble_SCL_HSIOM_POS      (from_ble_scl__0__HSIOM_SHIFT)
    #define from_ble_SCL_HSIOM_SEL_GPIO (from_ble_sda__0__HSIOM_GPIO)
    #define from_ble_SCL_HSIOM_SEL_I2C  (from_ble_sda__0__HSIOM_I2C)
    
    #define from_ble_SDA_HSIOM_REG  (*(reg32 *) from_ble_sda__0__HSIOM)
    #define from_ble_SDA_HSIOM_PTR  ( (reg32 *) from_ble_sda__0__HSIOM)
    
    #define from_ble_SDA_HSIOM_MASK     (from_ble_sda__0__HSIOM_MASK)
    #define from_ble_SDA_HSIOM_POS      (from_ble_sda__0__HSIOM_SHIFT)
    #define from_ble_SDA_HSIOM_SEL_GPIO (from_ble_sda__0__HSIOM_GPIO)
    #define from_ble_SDA_HSIOM_SEL_I2C  (from_ble_sda__0__HSIOM_I2C)
#endif /* (from_ble_I2C_PINS) */

#if (from_ble_SPI_SLAVE_PINS)
    #define from_ble_SCLK_S_HSIOM_REG   (*(reg32 *) from_ble_sclk_s__0__HSIOM)
    #define from_ble_SCLK_S_HSIOM_PTR   ( (reg32 *) from_ble_sclk_s__0__HSIOM)
    
    #define from_ble_SCLK_S_HSIOM_MASK      (from_ble_sclk_s__0__HSIOM_MASK)
    #define from_ble_SCLK_S_HSIOM_POS       (from_ble_sclk_s__0__HSIOM_SHIFT)
    #define from_ble_SCLK_S_HSIOM_SEL_GPIO  (from_ble_sclk_s__0__HSIOM_GPIO)
    #define from_ble_SCLK_S_HSIOM_SEL_SPI   (from_ble_sclk_s__0__HSIOM_SPI)
    
    #define from_ble_SS0_S_HSIOM_REG    (*(reg32 *) from_ble_ss0_s__0__HSIOM)
    #define from_ble_SS0_S_HSIOM_PTR    ( (reg32 *) from_ble_ss0_s__0__HSIOM)
    
    #define from_ble_SS0_S_HSIOM_MASK       (from_ble_ss0_s__0__HSIOM_MASK)
    #define from_ble_SS0_S_HSIOM_POS        (from_ble_ss0_s__0__HSIOM_SHIFT)
    #define from_ble_SS0_S_HSIOM_SEL_GPIO   (from_ble_ss0_s__0__HSIOM_GPIO)  
    #define from_ble_SS0_S_HSIOM_SEL_SPI    (from_ble_ss0_s__0__HSIOM_SPI)
#endif /* (from_ble_SPI_SLAVE_PINS) */

#if (from_ble_SPI_SLAVE_MOSI_PIN)
    #define from_ble_MOSI_S_HSIOM_REG   (*(reg32 *) from_ble_mosi_s__0__HSIOM)
    #define from_ble_MOSI_S_HSIOM_PTR   ( (reg32 *) from_ble_mosi_s__0__HSIOM)
    
    #define from_ble_MOSI_S_HSIOM_MASK      (from_ble_mosi_s__0__HSIOM_MASK)
    #define from_ble_MOSI_S_HSIOM_POS       (from_ble_mosi_s__0__HSIOM_SHIFT)
    #define from_ble_MOSI_S_HSIOM_SEL_GPIO  (from_ble_mosi_s__0__HSIOM_GPIO)
    #define from_ble_MOSI_S_HSIOM_SEL_SPI   (from_ble_mosi_s__0__HSIOM_SPI)
#endif /* (from_ble_SPI_SLAVE_MOSI_PIN) */

#if (from_ble_SPI_SLAVE_MISO_PIN)
    #define from_ble_MISO_S_HSIOM_REG   (*(reg32 *) from_ble_miso_s__0__HSIOM)
    #define from_ble_MISO_S_HSIOM_PTR   ( (reg32 *) from_ble_miso_s__0__HSIOM)
    
    #define from_ble_MISO_S_HSIOM_MASK      (from_ble_miso_s__0__HSIOM_MASK)
    #define from_ble_MISO_S_HSIOM_POS       (from_ble_miso_s__0__HSIOM_SHIFT)
    #define from_ble_MISO_S_HSIOM_SEL_GPIO  (from_ble_miso_s__0__HSIOM_GPIO)
    #define from_ble_MISO_S_HSIOM_SEL_SPI   (from_ble_miso_s__0__HSIOM_SPI)
#endif /* (from_ble_SPI_SLAVE_MISO_PIN) */

#if (from_ble_SPI_MASTER_MISO_PIN)
    #define from_ble_MISO_M_HSIOM_REG   (*(reg32 *) from_ble_miso_m__0__HSIOM)
    #define from_ble_MISO_M_HSIOM_PTR   ( (reg32 *) from_ble_miso_m__0__HSIOM)
    
    #define from_ble_MISO_M_HSIOM_MASK      (from_ble_miso_m__0__HSIOM_MASK)
    #define from_ble_MISO_M_HSIOM_POS       (from_ble_miso_m__0__HSIOM_SHIFT)
    #define from_ble_MISO_M_HSIOM_SEL_GPIO  (from_ble_miso_m__0__HSIOM_GPIO)
    #define from_ble_MISO_M_HSIOM_SEL_SPI   (from_ble_miso_m__0__HSIOM_SPI)
#endif /* (from_ble_SPI_MASTER_MISO_PIN) */

#if (from_ble_SPI_MASTER_MOSI_PIN)
    #define from_ble_MOSI_M_HSIOM_REG   (*(reg32 *) from_ble_mosi_m__0__HSIOM)
    #define from_ble_MOSI_M_HSIOM_PTR   ( (reg32 *) from_ble_mosi_m__0__HSIOM)
    
    #define from_ble_MOSI_M_HSIOM_MASK      (from_ble_mosi_m__0__HSIOM_MASK)
    #define from_ble_MOSI_M_HSIOM_POS       (from_ble_mosi_m__0__HSIOM_SHIFT)
    #define from_ble_MOSI_M_HSIOM_SEL_GPIO  (from_ble_mosi_m__0__HSIOM_GPIO)
    #define from_ble_MOSI_M_HSIOM_SEL_SPI   (from_ble_mosi_m__0__HSIOM_SPI)
#endif /* (from_ble_SPI_MASTER_MOSI_PIN) */

#if (from_ble_SPI_MASTER_SCLK_PIN)
    #define from_ble_SCLK_M_HSIOM_REG   (*(reg32 *) from_ble_sclk_m__0__HSIOM)
    #define from_ble_SCLK_M_HSIOM_PTR   ( (reg32 *) from_ble_sclk_m__0__HSIOM)
    
    #define from_ble_SCLK_M_HSIOM_MASK      (from_ble_sclk_m__0__HSIOM_MASK)
    #define from_ble_SCLK_M_HSIOM_POS       (from_ble_sclk_m__0__HSIOM_SHIFT)
    #define from_ble_SCLK_M_HSIOM_SEL_GPIO  (from_ble_sclk_m__0__HSIOM_GPIO)
    #define from_ble_SCLK_M_HSIOM_SEL_SPI   (from_ble_sclk_m__0__HSIOM_SPI)
#endif /* (from_ble_SPI_MASTER_SCLK_PIN) */

#if (from_ble_SPI_MASTER_SS0_PIN)
    #define from_ble_SS0_M_HSIOM_REG    (*(reg32 *) from_ble_ss0_m__0__HSIOM)
    #define from_ble_SS0_M_HSIOM_PTR    ( (reg32 *) from_ble_ss0_m__0__HSIOM)
    
    #define from_ble_SS0_M_HSIOM_MASK       (from_ble_ss0_m__0__HSIOM_MASK)
    #define from_ble_SS0_M_HSIOM_POS        (from_ble_ss0_m__0__HSIOM_SHIFT)
    #define from_ble_SS0_M_HSIOM_SEL_GPIO   (from_ble_ss0_m__0__HSIOM_GPIO)
    #define from_ble_SS0_M_HSIOM_SEL_SPI    (from_ble_ss0_m__0__HSIOM_SPI)
#endif /* (from_ble_SPI_MASTER_SS0_PIN) */

#if (from_ble_SPI_MASTER_SS1_PIN)
    #define from_ble_SS1_M_HSIOM_REG    (*(reg32 *) from_ble_ss1_m__0__HSIOM)
    #define from_ble_SS1_M_HSIOM_PTR    ( (reg32 *) from_ble_ss1_m__0__HSIOM)
    
    #define from_ble_SS1_M_HSIOM_MASK       (from_ble_ss1_m__0__HSIOM_MASK)
    #define from_ble_SS1_M_HSIOM_POS        (from_ble_ss1_m__0__HSIOM_SHIFT)
    #define from_ble_SS1_M_HSIOM_SEL_GPIO   (from_ble_ss1_m__0__HSIOM_GPIO)
    #define from_ble_SS1_M_HSIOM_SEL_SPI    (from_ble_ss1_m__0__HSIOM_SPI)
#endif /* (from_ble_SPI_MASTER_SS1_PIN) */

#if (from_ble_SPI_MASTER_SS2_PIN)
    #define from_ble_SS2_M_HSIOM_REG    (*(reg32 *) from_ble_ss2_m__0__HSIOM)
    #define from_ble_SS2_M_HSIOM_PTR    ( (reg32 *) from_ble_ss2_m__0__HSIOM)
    
    #define from_ble_SS2_M_HSIOM_MASK       (from_ble_ss2_m__0__HSIOM_MASK)
    #define from_ble_SS2_M_HSIOM_POS        (from_ble_ss2_m__0__HSIOM_SHIFT)
    #define from_ble_SS2_M_HSIOM_SEL_GPIO   (from_ble_ss2_m__0__HSIOM_GPIO)
    #define from_ble_SS2_M_HSIOM_SEL_SPI    (from_ble_ss2_m__0__HSIOM_SPI)
#endif /* (from_ble_SPI_MASTER_SS2_PIN) */

#if (from_ble_SPI_MASTER_SS3_PIN)
    #define from_ble_SS3_M_HSIOM_REG    (*(reg32 *) from_ble_ss3_m__0__HSIOM)
    #define from_ble_SS3_M_HSIOM_PTR    ( (reg32 *) from_ble_ss3_m__0__HSIOM)
    
    #define from_ble_SS3_M_HSIOM_MASK      (from_ble_ss3_m__0__HSIOM_MASK)
    #define from_ble_SS3_M_HSIOM_POS       (from_ble_ss3_m__0__HSIOM_SHIFT)
    #define from_ble_SS3_M_HSIOM_SEL_GPIO  (from_ble_ss3_m__0__HSIOM_GPIO)
    #define from_ble_SS3_M_HSIOM_SEL_SPI   (from_ble_ss3_m__0__HSIOM_SPI)
#endif /* (from_ble_SPI_MASTER_SS3_PIN) */

#if (from_ble_UART_RX_PIN)
    #define from_ble_RX_HSIOM_REG   (*(reg32 *) from_ble_rx__0__HSIOM)
    #define from_ble_RX_HSIOM_PTR   ( (reg32 *) from_ble_rx__0__HSIOM)
    
    #define from_ble_RX_HSIOM_MASK      (from_ble_rx__0__HSIOM_MASK)
    #define from_ble_RX_HSIOM_POS       (from_ble_rx__0__HSIOM_SHIFT)
    #define from_ble_RX_HSIOM_SEL_GPIO  (from_ble_rx__0__HSIOM_GPIO)
    #define from_ble_RX_HSIOM_SEL_UART  (from_ble_rx__0__HSIOM_UART)
#endif /* (from_ble_UART_RX_PIN) */

#if (from_ble_UART_RX_WAKE_PIN)
    #define from_ble_RX_WAKE_HSIOM_REG   (*(reg32 *) from_ble_rx_wake__0__HSIOM)
    #define from_ble_RX_WAKE_HSIOM_PTR   ( (reg32 *) from_ble_rx_wake__0__HSIOM)
    
    #define from_ble_RX_WAKE_HSIOM_MASK      (from_ble_rx_wake__0__HSIOM_MASK)
    #define from_ble_RX_WAKE_HSIOM_POS       (from_ble_rx_wake__0__HSIOM_SHIFT)
    #define from_ble_RX_WAKE_HSIOM_SEL_GPIO  (from_ble_rx_wake__0__HSIOM_GPIO)
    #define from_ble_RX_WAKE_HSIOM_SEL_UART  (from_ble_rx_wake__0__HSIOM_UART)
#endif /* (from_ble_UART_WAKE_RX_PIN) */

#if (from_ble_UART_CTS_PIN)
    #define from_ble_CTS_HSIOM_REG   (*(reg32 *) from_ble_cts__0__HSIOM)
    #define from_ble_CTS_HSIOM_PTR   ( (reg32 *) from_ble_cts__0__HSIOM)
    
    #define from_ble_CTS_HSIOM_MASK      (from_ble_cts__0__HSIOM_MASK)
    #define from_ble_CTS_HSIOM_POS       (from_ble_cts__0__HSIOM_SHIFT)
    #define from_ble_CTS_HSIOM_SEL_GPIO  (from_ble_cts__0__HSIOM_GPIO)
    #define from_ble_CTS_HSIOM_SEL_UART  (from_ble_cts__0__HSIOM_UART)
#endif /* (from_ble_UART_CTS_PIN) */

#if (from_ble_UART_TX_PIN)
    #define from_ble_TX_HSIOM_REG   (*(reg32 *) from_ble_tx__0__HSIOM)
    #define from_ble_TX_HSIOM_PTR   ( (reg32 *) from_ble_tx__0__HSIOM)
    
    #define from_ble_TX_HSIOM_MASK      (from_ble_tx__0__HSIOM_MASK)
    #define from_ble_TX_HSIOM_POS       (from_ble_tx__0__HSIOM_SHIFT)
    #define from_ble_TX_HSIOM_SEL_GPIO  (from_ble_tx__0__HSIOM_GPIO)
    #define from_ble_TX_HSIOM_SEL_UART  (from_ble_tx__0__HSIOM_UART)
#endif /* (from_ble_UART_TX_PIN) */

#if (from_ble_UART_RX_TX_PIN)
    #define from_ble_RX_TX_HSIOM_REG   (*(reg32 *) from_ble_rx_tx__0__HSIOM)
    #define from_ble_RX_TX_HSIOM_PTR   ( (reg32 *) from_ble_rx_tx__0__HSIOM)
    
    #define from_ble_RX_TX_HSIOM_MASK      (from_ble_rx_tx__0__HSIOM_MASK)
    #define from_ble_RX_TX_HSIOM_POS       (from_ble_rx_tx__0__HSIOM_SHIFT)
    #define from_ble_RX_TX_HSIOM_SEL_GPIO  (from_ble_rx_tx__0__HSIOM_GPIO)
    #define from_ble_RX_TX_HSIOM_SEL_UART  (from_ble_rx_tx__0__HSIOM_UART)
#endif /* (from_ble_UART_RX_TX_PIN) */

#if (from_ble_UART_RTS_PIN)
    #define from_ble_RTS_HSIOM_REG      (*(reg32 *) from_ble_rts__0__HSIOM)
    #define from_ble_RTS_HSIOM_PTR      ( (reg32 *) from_ble_rts__0__HSIOM)
    
    #define from_ble_RTS_HSIOM_MASK     (from_ble_rts__0__HSIOM_MASK)
    #define from_ble_RTS_HSIOM_POS      (from_ble_rts__0__HSIOM_SHIFT)    
    #define from_ble_RTS_HSIOM_SEL_GPIO (from_ble_rts__0__HSIOM_GPIO)
    #define from_ble_RTS_HSIOM_SEL_UART (from_ble_rts__0__HSIOM_UART)    
#endif /* (from_ble_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define from_ble_HSIOM_DEF_SEL      (0x00u)
#define from_ble_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for from_ble_CY_SCBIP_V0 
* and from_ble_CY_SCBIP_V1. It is not recommended to use them for 
* from_ble_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define from_ble_HSIOM_UART_SEL     (0x09u)
#define from_ble_HSIOM_I2C_SEL      (0x0Eu)
#define from_ble_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define from_ble_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define from_ble_RX_SCL_MOSI_PIN_INDEX       (0u)
#define from_ble_TX_SDA_MISO_PIN_INDEX       (1u)
#define from_ble_CTS_SCLK_PIN_INDEX       (2u)
#define from_ble_RTS_SS0_PIN_INDEX       (3u)
#define from_ble_SS1_PIN_INDEX                  (4u)
#define from_ble_SS2_PIN_INDEX                  (5u)
#define from_ble_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define from_ble_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << from_ble_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define from_ble_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << from_ble_RX_SCL_MOSI_PIN_INDEX)
#define from_ble_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << from_ble_TX_SDA_MISO_PIN_INDEX)
#define from_ble_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << from_ble_CTS_SCLK_PIN_INDEX)
#define from_ble_RTS_SS0_PIN_MASK     ((uint32) 0x01u << from_ble_RTS_SS0_PIN_INDEX)
#define from_ble_SS1_PIN_MASK                ((uint32) 0x01u << from_ble_SS1_PIN_INDEX)
#define from_ble_SS2_PIN_MASK                ((uint32) 0x01u << from_ble_SS2_PIN_INDEX)
#define from_ble_SS3_PIN_MASK                ((uint32) 0x01u << from_ble_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define from_ble_INTCFG_TYPE_MASK           (0x03u)
#define from_ble_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define from_ble_PIN_DM_ALG_HIZ  (0u)
#define from_ble_PIN_DM_DIG_HIZ  (1u)
#define from_ble_PIN_DM_OD_LO    (4u)
#define from_ble_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define from_ble_DM_MASK    (0x7u)
#define from_ble_DM_SIZE    (3u)
#define from_ble_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) from_ble_DM_MASK << (from_ble_DM_SIZE * (pos)))) >> \
                                                              (from_ble_DM_SIZE * (pos)) )

#if (from_ble_TX_SDA_MISO_PIN)
    #define from_ble_CHECK_TX_SDA_MISO_PIN_USED \
                (from_ble_PIN_DM_ALG_HIZ != \
                    from_ble_GET_P4_PIN_DM(from_ble_uart_tx_i2c_sda_spi_miso_PC, \
                                                   from_ble_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (from_ble_TX_SDA_MISO_PIN) */

#if (from_ble_RTS_SS0_PIN)
    #define from_ble_CHECK_RTS_SS0_PIN_USED \
                (from_ble_PIN_DM_ALG_HIZ != \
                    from_ble_GET_P4_PIN_DM(from_ble_uart_rts_spi_ss0_PC, \
                                                   from_ble_uart_rts_spi_ss0_SHIFT))
#endif /* (from_ble_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define from_ble_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define from_ble_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define from_ble_SET_HSIOM_SEL(reg, mask, pos, sel) from_ble_SET_REGISTER_BITS(reg, mask, pos, sel)
#define from_ble_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        from_ble_SET_REGISTER_BITS(reg, mask, pos, intType)
#define from_ble_SET_INP_DIS(reg, mask, val) from_ble_SET_REGISTER_BIT(reg, mask, val)

/* from_ble_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  from_ble_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (from_ble_CY_SCBIP_V0)
#if (from_ble_I2C_PINS)
    #define from_ble_SET_I2C_SCL_DR(val) from_ble_scl_Write(val)

    #define from_ble_SET_I2C_SCL_HSIOM_SEL(sel) \
                          from_ble_SET_HSIOM_SEL(from_ble_SCL_HSIOM_REG,  \
                                                         from_ble_SCL_HSIOM_MASK, \
                                                         from_ble_SCL_HSIOM_POS,  \
                                                         (sel))
    #define from_ble_WAIT_SCL_SET_HIGH  (0u == from_ble_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (from_ble_RX_WAKE_SCL_MOSI_PIN)
    #define from_ble_SET_I2C_SCL_DR(val) \
                            from_ble_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define from_ble_SET_I2C_SCL_HSIOM_SEL(sel) \
                    from_ble_SET_HSIOM_SEL(from_ble_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   from_ble_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   from_ble_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define from_ble_WAIT_SCL_SET_HIGH  (0u == from_ble_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (from_ble_RX_SCL_MOSI_PIN)
    #define from_ble_SET_I2C_SCL_DR(val) \
                            from_ble_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define from_ble_SET_I2C_SCL_HSIOM_SEL(sel) \
                            from_ble_SET_HSIOM_SEL(from_ble_RX_SCL_MOSI_HSIOM_REG,  \
                                                           from_ble_RX_SCL_MOSI_HSIOM_MASK, \
                                                           from_ble_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define from_ble_WAIT_SCL_SET_HIGH  (0u == from_ble_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define from_ble_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define from_ble_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define from_ble_WAIT_SCL_SET_HIGH  (0u)
#endif /* (from_ble_I2C_PINS) */

/* SCB I2C: sda signal */
#if (from_ble_I2C_PINS)
    #define from_ble_WAIT_SDA_SET_HIGH  (0u == from_ble_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (from_ble_TX_SDA_MISO_PIN)
    #define from_ble_WAIT_SDA_SET_HIGH  (0u == from_ble_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define from_ble_WAIT_SDA_SET_HIGH  (0u)
#endif /* (from_ble_MOSI_SCL_RX_PIN) */
#endif /* (from_ble_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (from_ble_RX_SCL_MOSI_PIN)
    #define from_ble_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (from_ble_RX_WAKE_SCL_MOSI_PIN)
    #define from_ble_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) from_ble_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(from_ble_UART_RX_WAKE_PIN)
    #define from_ble_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) from_ble_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (from_ble_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define from_ble_REMOVE_MOSI_SCL_RX_WAKE_PIN    from_ble_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define from_ble_REMOVE_MOSI_SCL_RX_PIN         from_ble_REMOVE_RX_SCL_MOSI_PIN
#define from_ble_REMOVE_MISO_SDA_TX_PIN         from_ble_REMOVE_TX_SDA_MISO_PIN
#ifndef from_ble_REMOVE_SCLK_PIN
#define from_ble_REMOVE_SCLK_PIN                from_ble_REMOVE_CTS_SCLK_PIN
#endif /* from_ble_REMOVE_SCLK_PIN */
#ifndef from_ble_REMOVE_SS0_PIN
#define from_ble_REMOVE_SS0_PIN                 from_ble_REMOVE_RTS_SS0_PIN
#endif /* from_ble_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define from_ble_MOSI_SCL_RX_WAKE_PIN   from_ble_RX_WAKE_SCL_MOSI_PIN
#define from_ble_MOSI_SCL_RX_PIN        from_ble_RX_SCL_MOSI_PIN
#define from_ble_MISO_SDA_TX_PIN        from_ble_TX_SDA_MISO_PIN
#ifndef from_ble_SCLK_PIN
#define from_ble_SCLK_PIN               from_ble_CTS_SCLK_PIN
#endif /* from_ble_SCLK_PIN */
#ifndef from_ble_SS0_PIN
#define from_ble_SS0_PIN                from_ble_RTS_SS0_PIN
#endif /* from_ble_SS0_PIN */

#if (from_ble_MOSI_SCL_RX_WAKE_PIN)
    #define from_ble_MOSI_SCL_RX_WAKE_HSIOM_REG     from_ble_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define from_ble_MOSI_SCL_RX_WAKE_HSIOM_PTR     from_ble_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define from_ble_MOSI_SCL_RX_WAKE_HSIOM_MASK    from_ble_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define from_ble_MOSI_SCL_RX_WAKE_HSIOM_POS     from_ble_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define from_ble_MOSI_SCL_RX_WAKE_INTCFG_REG    from_ble_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define from_ble_MOSI_SCL_RX_WAKE_INTCFG_PTR    from_ble_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define from_ble_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   from_ble_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define from_ble_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  from_ble_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (from_ble_RX_WAKE_SCL_MOSI_PIN) */

#if (from_ble_MOSI_SCL_RX_PIN)
    #define from_ble_MOSI_SCL_RX_HSIOM_REG      from_ble_RX_SCL_MOSI_HSIOM_REG
    #define from_ble_MOSI_SCL_RX_HSIOM_PTR      from_ble_RX_SCL_MOSI_HSIOM_PTR
    #define from_ble_MOSI_SCL_RX_HSIOM_MASK     from_ble_RX_SCL_MOSI_HSIOM_MASK
    #define from_ble_MOSI_SCL_RX_HSIOM_POS      from_ble_RX_SCL_MOSI_HSIOM_POS
#endif /* (from_ble_MOSI_SCL_RX_PIN) */

#if (from_ble_MISO_SDA_TX_PIN)
    #define from_ble_MISO_SDA_TX_HSIOM_REG      from_ble_TX_SDA_MISO_HSIOM_REG
    #define from_ble_MISO_SDA_TX_HSIOM_PTR      from_ble_TX_SDA_MISO_HSIOM_REG
    #define from_ble_MISO_SDA_TX_HSIOM_MASK     from_ble_TX_SDA_MISO_HSIOM_REG
    #define from_ble_MISO_SDA_TX_HSIOM_POS      from_ble_TX_SDA_MISO_HSIOM_REG
#endif /* (from_ble_MISO_SDA_TX_PIN_PIN) */

#if (from_ble_SCLK_PIN)
    #ifndef from_ble_SCLK_HSIOM_REG
    #define from_ble_SCLK_HSIOM_REG     from_ble_CTS_SCLK_HSIOM_REG
    #define from_ble_SCLK_HSIOM_PTR     from_ble_CTS_SCLK_HSIOM_PTR
    #define from_ble_SCLK_HSIOM_MASK    from_ble_CTS_SCLK_HSIOM_MASK
    #define from_ble_SCLK_HSIOM_POS     from_ble_CTS_SCLK_HSIOM_POS
    #endif /* from_ble_SCLK_HSIOM_REG */
#endif /* (from_ble_SCLK_PIN) */

#if (from_ble_SS0_PIN)
    #ifndef from_ble_SS0_HSIOM_REG
    #define from_ble_SS0_HSIOM_REG      from_ble_RTS_SS0_HSIOM_REG
    #define from_ble_SS0_HSIOM_PTR      from_ble_RTS_SS0_HSIOM_PTR
    #define from_ble_SS0_HSIOM_MASK     from_ble_RTS_SS0_HSIOM_MASK
    #define from_ble_SS0_HSIOM_POS      from_ble_RTS_SS0_HSIOM_POS
    #endif /* from_ble_SS0_HSIOM_REG */
#endif /* (from_ble_SS0_PIN) */

#define from_ble_MOSI_SCL_RX_WAKE_PIN_INDEX from_ble_RX_WAKE_SCL_MOSI_PIN_INDEX
#define from_ble_MOSI_SCL_RX_PIN_INDEX      from_ble_RX_SCL_MOSI_PIN_INDEX
#define from_ble_MISO_SDA_TX_PIN_INDEX      from_ble_TX_SDA_MISO_PIN_INDEX
#ifndef from_ble_SCLK_PIN_INDEX
#define from_ble_SCLK_PIN_INDEX             from_ble_CTS_SCLK_PIN_INDEX
#endif /* from_ble_SCLK_PIN_INDEX */
#ifndef from_ble_SS0_PIN_INDEX
#define from_ble_SS0_PIN_INDEX              from_ble_RTS_SS0_PIN_INDEX
#endif /* from_ble_SS0_PIN_INDEX */

#define from_ble_MOSI_SCL_RX_WAKE_PIN_MASK from_ble_RX_WAKE_SCL_MOSI_PIN_MASK
#define from_ble_MOSI_SCL_RX_PIN_MASK      from_ble_RX_SCL_MOSI_PIN_MASK
#define from_ble_MISO_SDA_TX_PIN_MASK      from_ble_TX_SDA_MISO_PIN_MASK
#ifndef from_ble_SCLK_PIN_MASK
#define from_ble_SCLK_PIN_MASK             from_ble_CTS_SCLK_PIN_MASK
#endif /* from_ble_SCLK_PIN_MASK */
#ifndef from_ble_SS0_PIN_MASK
#define from_ble_SS0_PIN_MASK              from_ble_RTS_SS0_PIN_MASK
#endif /* from_ble_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_from_ble_H) */


/* [] END OF FILE */
