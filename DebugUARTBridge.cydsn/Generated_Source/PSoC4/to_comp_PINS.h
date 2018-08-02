/***************************************************************************//**
* \file to_comp_PINS.h
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

#if !defined(CY_SCB_PINS_to_comp_H)
#define CY_SCB_PINS_to_comp_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define to_comp_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define to_comp_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define to_comp_REMOVE_TX_SDA_MISO_PIN      (1u)
#define to_comp_REMOVE_CTS_SCLK_PIN      (1u)
#define to_comp_REMOVE_RTS_SS0_PIN      (1u)
#define to_comp_REMOVE_SS1_PIN                 (1u)
#define to_comp_REMOVE_SS2_PIN                 (1u)
#define to_comp_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define to_comp_REMOVE_I2C_PINS                (1u)
#define to_comp_REMOVE_SPI_MASTER_PINS         (1u)
#define to_comp_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define to_comp_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define to_comp_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define to_comp_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define to_comp_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define to_comp_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define to_comp_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define to_comp_REMOVE_SPI_SLAVE_PINS          (1u)
#define to_comp_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define to_comp_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define to_comp_REMOVE_UART_TX_PIN             (0u)
#define to_comp_REMOVE_UART_RX_TX_PIN          (1u)
#define to_comp_REMOVE_UART_RX_PIN             (0u)
#define to_comp_REMOVE_UART_RX_WAKE_PIN        (1u)
#define to_comp_REMOVE_UART_RTS_PIN            (1u)
#define to_comp_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define to_comp_RX_WAKE_SCL_MOSI_PIN (0u == to_comp_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define to_comp_RX_SCL_MOSI_PIN     (0u == to_comp_REMOVE_RX_SCL_MOSI_PIN)
#define to_comp_TX_SDA_MISO_PIN     (0u == to_comp_REMOVE_TX_SDA_MISO_PIN)
#define to_comp_CTS_SCLK_PIN     (0u == to_comp_REMOVE_CTS_SCLK_PIN)
#define to_comp_RTS_SS0_PIN     (0u == to_comp_REMOVE_RTS_SS0_PIN)
#define to_comp_SS1_PIN                (0u == to_comp_REMOVE_SS1_PIN)
#define to_comp_SS2_PIN                (0u == to_comp_REMOVE_SS2_PIN)
#define to_comp_SS3_PIN                (0u == to_comp_REMOVE_SS3_PIN)

/* Mode defined pins */
#define to_comp_I2C_PINS               (0u == to_comp_REMOVE_I2C_PINS)
#define to_comp_SPI_MASTER_PINS        (0u == to_comp_REMOVE_SPI_MASTER_PINS)
#define to_comp_SPI_MASTER_SCLK_PIN    (0u == to_comp_REMOVE_SPI_MASTER_SCLK_PIN)
#define to_comp_SPI_MASTER_MOSI_PIN    (0u == to_comp_REMOVE_SPI_MASTER_MOSI_PIN)
#define to_comp_SPI_MASTER_MISO_PIN    (0u == to_comp_REMOVE_SPI_MASTER_MISO_PIN)
#define to_comp_SPI_MASTER_SS0_PIN     (0u == to_comp_REMOVE_SPI_MASTER_SS0_PIN)
#define to_comp_SPI_MASTER_SS1_PIN     (0u == to_comp_REMOVE_SPI_MASTER_SS1_PIN)
#define to_comp_SPI_MASTER_SS2_PIN     (0u == to_comp_REMOVE_SPI_MASTER_SS2_PIN)
#define to_comp_SPI_MASTER_SS3_PIN     (0u == to_comp_REMOVE_SPI_MASTER_SS3_PIN)
#define to_comp_SPI_SLAVE_PINS         (0u == to_comp_REMOVE_SPI_SLAVE_PINS)
#define to_comp_SPI_SLAVE_MOSI_PIN     (0u == to_comp_REMOVE_SPI_SLAVE_MOSI_PIN)
#define to_comp_SPI_SLAVE_MISO_PIN     (0u == to_comp_REMOVE_SPI_SLAVE_MISO_PIN)
#define to_comp_UART_TX_PIN            (0u == to_comp_REMOVE_UART_TX_PIN)
#define to_comp_UART_RX_TX_PIN         (0u == to_comp_REMOVE_UART_RX_TX_PIN)
#define to_comp_UART_RX_PIN            (0u == to_comp_REMOVE_UART_RX_PIN)
#define to_comp_UART_RX_WAKE_PIN       (0u == to_comp_REMOVE_UART_RX_WAKE_PIN)
#define to_comp_UART_RTS_PIN           (0u == to_comp_REMOVE_UART_RTS_PIN)
#define to_comp_UART_CTS_PIN           (0u == to_comp_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (to_comp_RX_WAKE_SCL_MOSI_PIN)
    #include "to_comp_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (to_comp_RX_SCL_MOSI) */

#if (to_comp_RX_SCL_MOSI_PIN)
    #include "to_comp_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (to_comp_RX_SCL_MOSI) */

#if (to_comp_TX_SDA_MISO_PIN)
    #include "to_comp_uart_tx_i2c_sda_spi_miso.h"
#endif /* (to_comp_TX_SDA_MISO) */

#if (to_comp_CTS_SCLK_PIN)
    #include "to_comp_uart_cts_spi_sclk.h"
#endif /* (to_comp_CTS_SCLK) */

#if (to_comp_RTS_SS0_PIN)
    #include "to_comp_uart_rts_spi_ss0.h"
#endif /* (to_comp_RTS_SS0_PIN) */

#if (to_comp_SS1_PIN)
    #include "to_comp_spi_ss1.h"
#endif /* (to_comp_SS1_PIN) */

#if (to_comp_SS2_PIN)
    #include "to_comp_spi_ss2.h"
#endif /* (to_comp_SS2_PIN) */

#if (to_comp_SS3_PIN)
    #include "to_comp_spi_ss3.h"
#endif /* (to_comp_SS3_PIN) */

#if (to_comp_I2C_PINS)
    #include "to_comp_scl.h"
    #include "to_comp_sda.h"
#endif /* (to_comp_I2C_PINS) */

#if (to_comp_SPI_MASTER_PINS)
#if (to_comp_SPI_MASTER_SCLK_PIN)
    #include "to_comp_sclk_m.h"
#endif /* (to_comp_SPI_MASTER_SCLK_PIN) */

#if (to_comp_SPI_MASTER_MOSI_PIN)
    #include "to_comp_mosi_m.h"
#endif /* (to_comp_SPI_MASTER_MOSI_PIN) */

#if (to_comp_SPI_MASTER_MISO_PIN)
    #include "to_comp_miso_m.h"
#endif /*(to_comp_SPI_MASTER_MISO_PIN) */
#endif /* (to_comp_SPI_MASTER_PINS) */

#if (to_comp_SPI_SLAVE_PINS)
    #include "to_comp_sclk_s.h"
    #include "to_comp_ss_s.h"

#if (to_comp_SPI_SLAVE_MOSI_PIN)
    #include "to_comp_mosi_s.h"
#endif /* (to_comp_SPI_SLAVE_MOSI_PIN) */

#if (to_comp_SPI_SLAVE_MISO_PIN)
    #include "to_comp_miso_s.h"
#endif /*(to_comp_SPI_SLAVE_MISO_PIN) */
#endif /* (to_comp_SPI_SLAVE_PINS) */

#if (to_comp_SPI_MASTER_SS0_PIN)
    #include "to_comp_ss0_m.h"
#endif /* (to_comp_SPI_MASTER_SS0_PIN) */

#if (to_comp_SPI_MASTER_SS1_PIN)
    #include "to_comp_ss1_m.h"
#endif /* (to_comp_SPI_MASTER_SS1_PIN) */

#if (to_comp_SPI_MASTER_SS2_PIN)
    #include "to_comp_ss2_m.h"
#endif /* (to_comp_SPI_MASTER_SS2_PIN) */

#if (to_comp_SPI_MASTER_SS3_PIN)
    #include "to_comp_ss3_m.h"
#endif /* (to_comp_SPI_MASTER_SS3_PIN) */

#if (to_comp_UART_TX_PIN)
    #include "to_comp_tx.h"
#endif /* (to_comp_UART_TX_PIN) */

#if (to_comp_UART_RX_TX_PIN)
    #include "to_comp_rx_tx.h"
#endif /* (to_comp_UART_RX_TX_PIN) */

#if (to_comp_UART_RX_PIN)
    #include "to_comp_rx.h"
#endif /* (to_comp_UART_RX_PIN) */

#if (to_comp_UART_RX_WAKE_PIN)
    #include "to_comp_rx_wake.h"
#endif /* (to_comp_UART_RX_WAKE_PIN) */

#if (to_comp_UART_RTS_PIN)
    #include "to_comp_rts.h"
#endif /* (to_comp_UART_RTS_PIN) */

#if (to_comp_UART_CTS_PIN)
    #include "to_comp_cts.h"
#endif /* (to_comp_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (to_comp_RX_SCL_MOSI_PIN)
    #define to_comp_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) to_comp_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define to_comp_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) to_comp_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define to_comp_RX_SCL_MOSI_HSIOM_MASK      (to_comp_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define to_comp_RX_SCL_MOSI_HSIOM_POS       (to_comp_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define to_comp_RX_SCL_MOSI_HSIOM_SEL_GPIO  (to_comp_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define to_comp_RX_SCL_MOSI_HSIOM_SEL_I2C   (to_comp_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define to_comp_RX_SCL_MOSI_HSIOM_SEL_SPI   (to_comp_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define to_comp_RX_SCL_MOSI_HSIOM_SEL_UART  (to_comp_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (to_comp_RX_WAKE_SCL_MOSI_PIN)
    #define to_comp_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) to_comp_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define to_comp_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) to_comp_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define to_comp_RX_WAKE_SCL_MOSI_HSIOM_MASK      (to_comp_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define to_comp_RX_WAKE_SCL_MOSI_HSIOM_POS       (to_comp_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define to_comp_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (to_comp_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define to_comp_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (to_comp_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define to_comp_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (to_comp_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define to_comp_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (to_comp_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define to_comp_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) to_comp_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define to_comp_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) to_comp_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define to_comp_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (to_comp_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define to_comp_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) to_comp_INTCFG_TYPE_MASK << \
                                                                           to_comp_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins to_comp_RX_SCL_MOSI_PIN or to_comp_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (to_comp_RX_SCL_MOSI_PIN) */

#if (to_comp_TX_SDA_MISO_PIN)
    #define to_comp_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) to_comp_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define to_comp_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) to_comp_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define to_comp_TX_SDA_MISO_HSIOM_MASK      (to_comp_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define to_comp_TX_SDA_MISO_HSIOM_POS       (to_comp_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define to_comp_TX_SDA_MISO_HSIOM_SEL_GPIO  (to_comp_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define to_comp_TX_SDA_MISO_HSIOM_SEL_I2C   (to_comp_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define to_comp_TX_SDA_MISO_HSIOM_SEL_SPI   (to_comp_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define to_comp_TX_SDA_MISO_HSIOM_SEL_UART  (to_comp_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (to_comp_TX_SDA_MISO_PIN) */

#if (to_comp_CTS_SCLK_PIN)
    #define to_comp_CTS_SCLK_HSIOM_REG   (*(reg32 *) to_comp_uart_cts_spi_sclk__0__HSIOM)
    #define to_comp_CTS_SCLK_HSIOM_PTR   ( (reg32 *) to_comp_uart_cts_spi_sclk__0__HSIOM)
    
    #define to_comp_CTS_SCLK_HSIOM_MASK      (to_comp_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define to_comp_CTS_SCLK_HSIOM_POS       (to_comp_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define to_comp_CTS_SCLK_HSIOM_SEL_GPIO  (to_comp_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define to_comp_CTS_SCLK_HSIOM_SEL_I2C   (to_comp_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define to_comp_CTS_SCLK_HSIOM_SEL_SPI   (to_comp_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define to_comp_CTS_SCLK_HSIOM_SEL_UART  (to_comp_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (to_comp_CTS_SCLK_PIN) */

#if (to_comp_RTS_SS0_PIN)
    #define to_comp_RTS_SS0_HSIOM_REG   (*(reg32 *) to_comp_uart_rts_spi_ss0__0__HSIOM)
    #define to_comp_RTS_SS0_HSIOM_PTR   ( (reg32 *) to_comp_uart_rts_spi_ss0__0__HSIOM)
    
    #define to_comp_RTS_SS0_HSIOM_MASK      (to_comp_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define to_comp_RTS_SS0_HSIOM_POS       (to_comp_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define to_comp_RTS_SS0_HSIOM_SEL_GPIO  (to_comp_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define to_comp_RTS_SS0_HSIOM_SEL_I2C   (to_comp_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define to_comp_RTS_SS0_HSIOM_SEL_SPI   (to_comp_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(to_comp_CY_SCBIP_V0 || to_comp_CY_SCBIP_V1)
    #define to_comp_RTS_SS0_HSIOM_SEL_UART  (to_comp_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(to_comp_CY_SCBIP_V0 || to_comp_CY_SCBIP_V1) */
#endif /* (to_comp_RTS_SS0_PIN) */

#if (to_comp_SS1_PIN)
    #define to_comp_SS1_HSIOM_REG  (*(reg32 *) to_comp_spi_ss1__0__HSIOM)
    #define to_comp_SS1_HSIOM_PTR  ( (reg32 *) to_comp_spi_ss1__0__HSIOM)
    
    #define to_comp_SS1_HSIOM_MASK     (to_comp_spi_ss1__0__HSIOM_MASK)
    #define to_comp_SS1_HSIOM_POS      (to_comp_spi_ss1__0__HSIOM_SHIFT)
    #define to_comp_SS1_HSIOM_SEL_GPIO (to_comp_spi_ss1__0__HSIOM_GPIO)
    #define to_comp_SS1_HSIOM_SEL_I2C  (to_comp_spi_ss1__0__HSIOM_I2C)
    #define to_comp_SS1_HSIOM_SEL_SPI  (to_comp_spi_ss1__0__HSIOM_SPI)
#endif /* (to_comp_SS1_PIN) */

#if (to_comp_SS2_PIN)
    #define to_comp_SS2_HSIOM_REG     (*(reg32 *) to_comp_spi_ss2__0__HSIOM)
    #define to_comp_SS2_HSIOM_PTR     ( (reg32 *) to_comp_spi_ss2__0__HSIOM)
    
    #define to_comp_SS2_HSIOM_MASK     (to_comp_spi_ss2__0__HSIOM_MASK)
    #define to_comp_SS2_HSIOM_POS      (to_comp_spi_ss2__0__HSIOM_SHIFT)
    #define to_comp_SS2_HSIOM_SEL_GPIO (to_comp_spi_ss2__0__HSIOM_GPIO)
    #define to_comp_SS2_HSIOM_SEL_I2C  (to_comp_spi_ss2__0__HSIOM_I2C)
    #define to_comp_SS2_HSIOM_SEL_SPI  (to_comp_spi_ss2__0__HSIOM_SPI)
#endif /* (to_comp_SS2_PIN) */

#if (to_comp_SS3_PIN)
    #define to_comp_SS3_HSIOM_REG     (*(reg32 *) to_comp_spi_ss3__0__HSIOM)
    #define to_comp_SS3_HSIOM_PTR     ( (reg32 *) to_comp_spi_ss3__0__HSIOM)
    
    #define to_comp_SS3_HSIOM_MASK     (to_comp_spi_ss3__0__HSIOM_MASK)
    #define to_comp_SS3_HSIOM_POS      (to_comp_spi_ss3__0__HSIOM_SHIFT)
    #define to_comp_SS3_HSIOM_SEL_GPIO (to_comp_spi_ss3__0__HSIOM_GPIO)
    #define to_comp_SS3_HSIOM_SEL_I2C  (to_comp_spi_ss3__0__HSIOM_I2C)
    #define to_comp_SS3_HSIOM_SEL_SPI  (to_comp_spi_ss3__0__HSIOM_SPI)
#endif /* (to_comp_SS3_PIN) */

#if (to_comp_I2C_PINS)
    #define to_comp_SCL_HSIOM_REG  (*(reg32 *) to_comp_scl__0__HSIOM)
    #define to_comp_SCL_HSIOM_PTR  ( (reg32 *) to_comp_scl__0__HSIOM)
    
    #define to_comp_SCL_HSIOM_MASK     (to_comp_scl__0__HSIOM_MASK)
    #define to_comp_SCL_HSIOM_POS      (to_comp_scl__0__HSIOM_SHIFT)
    #define to_comp_SCL_HSIOM_SEL_GPIO (to_comp_sda__0__HSIOM_GPIO)
    #define to_comp_SCL_HSIOM_SEL_I2C  (to_comp_sda__0__HSIOM_I2C)
    
    #define to_comp_SDA_HSIOM_REG  (*(reg32 *) to_comp_sda__0__HSIOM)
    #define to_comp_SDA_HSIOM_PTR  ( (reg32 *) to_comp_sda__0__HSIOM)
    
    #define to_comp_SDA_HSIOM_MASK     (to_comp_sda__0__HSIOM_MASK)
    #define to_comp_SDA_HSIOM_POS      (to_comp_sda__0__HSIOM_SHIFT)
    #define to_comp_SDA_HSIOM_SEL_GPIO (to_comp_sda__0__HSIOM_GPIO)
    #define to_comp_SDA_HSIOM_SEL_I2C  (to_comp_sda__0__HSIOM_I2C)
#endif /* (to_comp_I2C_PINS) */

#if (to_comp_SPI_SLAVE_PINS)
    #define to_comp_SCLK_S_HSIOM_REG   (*(reg32 *) to_comp_sclk_s__0__HSIOM)
    #define to_comp_SCLK_S_HSIOM_PTR   ( (reg32 *) to_comp_sclk_s__0__HSIOM)
    
    #define to_comp_SCLK_S_HSIOM_MASK      (to_comp_sclk_s__0__HSIOM_MASK)
    #define to_comp_SCLK_S_HSIOM_POS       (to_comp_sclk_s__0__HSIOM_SHIFT)
    #define to_comp_SCLK_S_HSIOM_SEL_GPIO  (to_comp_sclk_s__0__HSIOM_GPIO)
    #define to_comp_SCLK_S_HSIOM_SEL_SPI   (to_comp_sclk_s__0__HSIOM_SPI)
    
    #define to_comp_SS0_S_HSIOM_REG    (*(reg32 *) to_comp_ss0_s__0__HSIOM)
    #define to_comp_SS0_S_HSIOM_PTR    ( (reg32 *) to_comp_ss0_s__0__HSIOM)
    
    #define to_comp_SS0_S_HSIOM_MASK       (to_comp_ss0_s__0__HSIOM_MASK)
    #define to_comp_SS0_S_HSIOM_POS        (to_comp_ss0_s__0__HSIOM_SHIFT)
    #define to_comp_SS0_S_HSIOM_SEL_GPIO   (to_comp_ss0_s__0__HSIOM_GPIO)  
    #define to_comp_SS0_S_HSIOM_SEL_SPI    (to_comp_ss0_s__0__HSIOM_SPI)
#endif /* (to_comp_SPI_SLAVE_PINS) */

#if (to_comp_SPI_SLAVE_MOSI_PIN)
    #define to_comp_MOSI_S_HSIOM_REG   (*(reg32 *) to_comp_mosi_s__0__HSIOM)
    #define to_comp_MOSI_S_HSIOM_PTR   ( (reg32 *) to_comp_mosi_s__0__HSIOM)
    
    #define to_comp_MOSI_S_HSIOM_MASK      (to_comp_mosi_s__0__HSIOM_MASK)
    #define to_comp_MOSI_S_HSIOM_POS       (to_comp_mosi_s__0__HSIOM_SHIFT)
    #define to_comp_MOSI_S_HSIOM_SEL_GPIO  (to_comp_mosi_s__0__HSIOM_GPIO)
    #define to_comp_MOSI_S_HSIOM_SEL_SPI   (to_comp_mosi_s__0__HSIOM_SPI)
#endif /* (to_comp_SPI_SLAVE_MOSI_PIN) */

#if (to_comp_SPI_SLAVE_MISO_PIN)
    #define to_comp_MISO_S_HSIOM_REG   (*(reg32 *) to_comp_miso_s__0__HSIOM)
    #define to_comp_MISO_S_HSIOM_PTR   ( (reg32 *) to_comp_miso_s__0__HSIOM)
    
    #define to_comp_MISO_S_HSIOM_MASK      (to_comp_miso_s__0__HSIOM_MASK)
    #define to_comp_MISO_S_HSIOM_POS       (to_comp_miso_s__0__HSIOM_SHIFT)
    #define to_comp_MISO_S_HSIOM_SEL_GPIO  (to_comp_miso_s__0__HSIOM_GPIO)
    #define to_comp_MISO_S_HSIOM_SEL_SPI   (to_comp_miso_s__0__HSIOM_SPI)
#endif /* (to_comp_SPI_SLAVE_MISO_PIN) */

#if (to_comp_SPI_MASTER_MISO_PIN)
    #define to_comp_MISO_M_HSIOM_REG   (*(reg32 *) to_comp_miso_m__0__HSIOM)
    #define to_comp_MISO_M_HSIOM_PTR   ( (reg32 *) to_comp_miso_m__0__HSIOM)
    
    #define to_comp_MISO_M_HSIOM_MASK      (to_comp_miso_m__0__HSIOM_MASK)
    #define to_comp_MISO_M_HSIOM_POS       (to_comp_miso_m__0__HSIOM_SHIFT)
    #define to_comp_MISO_M_HSIOM_SEL_GPIO  (to_comp_miso_m__0__HSIOM_GPIO)
    #define to_comp_MISO_M_HSIOM_SEL_SPI   (to_comp_miso_m__0__HSIOM_SPI)
#endif /* (to_comp_SPI_MASTER_MISO_PIN) */

#if (to_comp_SPI_MASTER_MOSI_PIN)
    #define to_comp_MOSI_M_HSIOM_REG   (*(reg32 *) to_comp_mosi_m__0__HSIOM)
    #define to_comp_MOSI_M_HSIOM_PTR   ( (reg32 *) to_comp_mosi_m__0__HSIOM)
    
    #define to_comp_MOSI_M_HSIOM_MASK      (to_comp_mosi_m__0__HSIOM_MASK)
    #define to_comp_MOSI_M_HSIOM_POS       (to_comp_mosi_m__0__HSIOM_SHIFT)
    #define to_comp_MOSI_M_HSIOM_SEL_GPIO  (to_comp_mosi_m__0__HSIOM_GPIO)
    #define to_comp_MOSI_M_HSIOM_SEL_SPI   (to_comp_mosi_m__0__HSIOM_SPI)
#endif /* (to_comp_SPI_MASTER_MOSI_PIN) */

#if (to_comp_SPI_MASTER_SCLK_PIN)
    #define to_comp_SCLK_M_HSIOM_REG   (*(reg32 *) to_comp_sclk_m__0__HSIOM)
    #define to_comp_SCLK_M_HSIOM_PTR   ( (reg32 *) to_comp_sclk_m__0__HSIOM)
    
    #define to_comp_SCLK_M_HSIOM_MASK      (to_comp_sclk_m__0__HSIOM_MASK)
    #define to_comp_SCLK_M_HSIOM_POS       (to_comp_sclk_m__0__HSIOM_SHIFT)
    #define to_comp_SCLK_M_HSIOM_SEL_GPIO  (to_comp_sclk_m__0__HSIOM_GPIO)
    #define to_comp_SCLK_M_HSIOM_SEL_SPI   (to_comp_sclk_m__0__HSIOM_SPI)
#endif /* (to_comp_SPI_MASTER_SCLK_PIN) */

#if (to_comp_SPI_MASTER_SS0_PIN)
    #define to_comp_SS0_M_HSIOM_REG    (*(reg32 *) to_comp_ss0_m__0__HSIOM)
    #define to_comp_SS0_M_HSIOM_PTR    ( (reg32 *) to_comp_ss0_m__0__HSIOM)
    
    #define to_comp_SS0_M_HSIOM_MASK       (to_comp_ss0_m__0__HSIOM_MASK)
    #define to_comp_SS0_M_HSIOM_POS        (to_comp_ss0_m__0__HSIOM_SHIFT)
    #define to_comp_SS0_M_HSIOM_SEL_GPIO   (to_comp_ss0_m__0__HSIOM_GPIO)
    #define to_comp_SS0_M_HSIOM_SEL_SPI    (to_comp_ss0_m__0__HSIOM_SPI)
#endif /* (to_comp_SPI_MASTER_SS0_PIN) */

#if (to_comp_SPI_MASTER_SS1_PIN)
    #define to_comp_SS1_M_HSIOM_REG    (*(reg32 *) to_comp_ss1_m__0__HSIOM)
    #define to_comp_SS1_M_HSIOM_PTR    ( (reg32 *) to_comp_ss1_m__0__HSIOM)
    
    #define to_comp_SS1_M_HSIOM_MASK       (to_comp_ss1_m__0__HSIOM_MASK)
    #define to_comp_SS1_M_HSIOM_POS        (to_comp_ss1_m__0__HSIOM_SHIFT)
    #define to_comp_SS1_M_HSIOM_SEL_GPIO   (to_comp_ss1_m__0__HSIOM_GPIO)
    #define to_comp_SS1_M_HSIOM_SEL_SPI    (to_comp_ss1_m__0__HSIOM_SPI)
#endif /* (to_comp_SPI_MASTER_SS1_PIN) */

#if (to_comp_SPI_MASTER_SS2_PIN)
    #define to_comp_SS2_M_HSIOM_REG    (*(reg32 *) to_comp_ss2_m__0__HSIOM)
    #define to_comp_SS2_M_HSIOM_PTR    ( (reg32 *) to_comp_ss2_m__0__HSIOM)
    
    #define to_comp_SS2_M_HSIOM_MASK       (to_comp_ss2_m__0__HSIOM_MASK)
    #define to_comp_SS2_M_HSIOM_POS        (to_comp_ss2_m__0__HSIOM_SHIFT)
    #define to_comp_SS2_M_HSIOM_SEL_GPIO   (to_comp_ss2_m__0__HSIOM_GPIO)
    #define to_comp_SS2_M_HSIOM_SEL_SPI    (to_comp_ss2_m__0__HSIOM_SPI)
#endif /* (to_comp_SPI_MASTER_SS2_PIN) */

#if (to_comp_SPI_MASTER_SS3_PIN)
    #define to_comp_SS3_M_HSIOM_REG    (*(reg32 *) to_comp_ss3_m__0__HSIOM)
    #define to_comp_SS3_M_HSIOM_PTR    ( (reg32 *) to_comp_ss3_m__0__HSIOM)
    
    #define to_comp_SS3_M_HSIOM_MASK      (to_comp_ss3_m__0__HSIOM_MASK)
    #define to_comp_SS3_M_HSIOM_POS       (to_comp_ss3_m__0__HSIOM_SHIFT)
    #define to_comp_SS3_M_HSIOM_SEL_GPIO  (to_comp_ss3_m__0__HSIOM_GPIO)
    #define to_comp_SS3_M_HSIOM_SEL_SPI   (to_comp_ss3_m__0__HSIOM_SPI)
#endif /* (to_comp_SPI_MASTER_SS3_PIN) */

#if (to_comp_UART_RX_PIN)
    #define to_comp_RX_HSIOM_REG   (*(reg32 *) to_comp_rx__0__HSIOM)
    #define to_comp_RX_HSIOM_PTR   ( (reg32 *) to_comp_rx__0__HSIOM)
    
    #define to_comp_RX_HSIOM_MASK      (to_comp_rx__0__HSIOM_MASK)
    #define to_comp_RX_HSIOM_POS       (to_comp_rx__0__HSIOM_SHIFT)
    #define to_comp_RX_HSIOM_SEL_GPIO  (to_comp_rx__0__HSIOM_GPIO)
    #define to_comp_RX_HSIOM_SEL_UART  (to_comp_rx__0__HSIOM_UART)
#endif /* (to_comp_UART_RX_PIN) */

#if (to_comp_UART_RX_WAKE_PIN)
    #define to_comp_RX_WAKE_HSIOM_REG   (*(reg32 *) to_comp_rx_wake__0__HSIOM)
    #define to_comp_RX_WAKE_HSIOM_PTR   ( (reg32 *) to_comp_rx_wake__0__HSIOM)
    
    #define to_comp_RX_WAKE_HSIOM_MASK      (to_comp_rx_wake__0__HSIOM_MASK)
    #define to_comp_RX_WAKE_HSIOM_POS       (to_comp_rx_wake__0__HSIOM_SHIFT)
    #define to_comp_RX_WAKE_HSIOM_SEL_GPIO  (to_comp_rx_wake__0__HSIOM_GPIO)
    #define to_comp_RX_WAKE_HSIOM_SEL_UART  (to_comp_rx_wake__0__HSIOM_UART)
#endif /* (to_comp_UART_WAKE_RX_PIN) */

#if (to_comp_UART_CTS_PIN)
    #define to_comp_CTS_HSIOM_REG   (*(reg32 *) to_comp_cts__0__HSIOM)
    #define to_comp_CTS_HSIOM_PTR   ( (reg32 *) to_comp_cts__0__HSIOM)
    
    #define to_comp_CTS_HSIOM_MASK      (to_comp_cts__0__HSIOM_MASK)
    #define to_comp_CTS_HSIOM_POS       (to_comp_cts__0__HSIOM_SHIFT)
    #define to_comp_CTS_HSIOM_SEL_GPIO  (to_comp_cts__0__HSIOM_GPIO)
    #define to_comp_CTS_HSIOM_SEL_UART  (to_comp_cts__0__HSIOM_UART)
#endif /* (to_comp_UART_CTS_PIN) */

#if (to_comp_UART_TX_PIN)
    #define to_comp_TX_HSIOM_REG   (*(reg32 *) to_comp_tx__0__HSIOM)
    #define to_comp_TX_HSIOM_PTR   ( (reg32 *) to_comp_tx__0__HSIOM)
    
    #define to_comp_TX_HSIOM_MASK      (to_comp_tx__0__HSIOM_MASK)
    #define to_comp_TX_HSIOM_POS       (to_comp_tx__0__HSIOM_SHIFT)
    #define to_comp_TX_HSIOM_SEL_GPIO  (to_comp_tx__0__HSIOM_GPIO)
    #define to_comp_TX_HSIOM_SEL_UART  (to_comp_tx__0__HSIOM_UART)
#endif /* (to_comp_UART_TX_PIN) */

#if (to_comp_UART_RX_TX_PIN)
    #define to_comp_RX_TX_HSIOM_REG   (*(reg32 *) to_comp_rx_tx__0__HSIOM)
    #define to_comp_RX_TX_HSIOM_PTR   ( (reg32 *) to_comp_rx_tx__0__HSIOM)
    
    #define to_comp_RX_TX_HSIOM_MASK      (to_comp_rx_tx__0__HSIOM_MASK)
    #define to_comp_RX_TX_HSIOM_POS       (to_comp_rx_tx__0__HSIOM_SHIFT)
    #define to_comp_RX_TX_HSIOM_SEL_GPIO  (to_comp_rx_tx__0__HSIOM_GPIO)
    #define to_comp_RX_TX_HSIOM_SEL_UART  (to_comp_rx_tx__0__HSIOM_UART)
#endif /* (to_comp_UART_RX_TX_PIN) */

#if (to_comp_UART_RTS_PIN)
    #define to_comp_RTS_HSIOM_REG      (*(reg32 *) to_comp_rts__0__HSIOM)
    #define to_comp_RTS_HSIOM_PTR      ( (reg32 *) to_comp_rts__0__HSIOM)
    
    #define to_comp_RTS_HSIOM_MASK     (to_comp_rts__0__HSIOM_MASK)
    #define to_comp_RTS_HSIOM_POS      (to_comp_rts__0__HSIOM_SHIFT)    
    #define to_comp_RTS_HSIOM_SEL_GPIO (to_comp_rts__0__HSIOM_GPIO)
    #define to_comp_RTS_HSIOM_SEL_UART (to_comp_rts__0__HSIOM_UART)    
#endif /* (to_comp_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define to_comp_HSIOM_DEF_SEL      (0x00u)
#define to_comp_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for to_comp_CY_SCBIP_V0 
* and to_comp_CY_SCBIP_V1. It is not recommended to use them for 
* to_comp_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define to_comp_HSIOM_UART_SEL     (0x09u)
#define to_comp_HSIOM_I2C_SEL      (0x0Eu)
#define to_comp_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define to_comp_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define to_comp_RX_SCL_MOSI_PIN_INDEX       (0u)
#define to_comp_TX_SDA_MISO_PIN_INDEX       (1u)
#define to_comp_CTS_SCLK_PIN_INDEX       (2u)
#define to_comp_RTS_SS0_PIN_INDEX       (3u)
#define to_comp_SS1_PIN_INDEX                  (4u)
#define to_comp_SS2_PIN_INDEX                  (5u)
#define to_comp_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define to_comp_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << to_comp_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define to_comp_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << to_comp_RX_SCL_MOSI_PIN_INDEX)
#define to_comp_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << to_comp_TX_SDA_MISO_PIN_INDEX)
#define to_comp_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << to_comp_CTS_SCLK_PIN_INDEX)
#define to_comp_RTS_SS0_PIN_MASK     ((uint32) 0x01u << to_comp_RTS_SS0_PIN_INDEX)
#define to_comp_SS1_PIN_MASK                ((uint32) 0x01u << to_comp_SS1_PIN_INDEX)
#define to_comp_SS2_PIN_MASK                ((uint32) 0x01u << to_comp_SS2_PIN_INDEX)
#define to_comp_SS3_PIN_MASK                ((uint32) 0x01u << to_comp_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define to_comp_INTCFG_TYPE_MASK           (0x03u)
#define to_comp_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define to_comp_PIN_DM_ALG_HIZ  (0u)
#define to_comp_PIN_DM_DIG_HIZ  (1u)
#define to_comp_PIN_DM_OD_LO    (4u)
#define to_comp_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define to_comp_DM_MASK    (0x7u)
#define to_comp_DM_SIZE    (3u)
#define to_comp_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) to_comp_DM_MASK << (to_comp_DM_SIZE * (pos)))) >> \
                                                              (to_comp_DM_SIZE * (pos)) )

#if (to_comp_TX_SDA_MISO_PIN)
    #define to_comp_CHECK_TX_SDA_MISO_PIN_USED \
                (to_comp_PIN_DM_ALG_HIZ != \
                    to_comp_GET_P4_PIN_DM(to_comp_uart_tx_i2c_sda_spi_miso_PC, \
                                                   to_comp_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (to_comp_TX_SDA_MISO_PIN) */

#if (to_comp_RTS_SS0_PIN)
    #define to_comp_CHECK_RTS_SS0_PIN_USED \
                (to_comp_PIN_DM_ALG_HIZ != \
                    to_comp_GET_P4_PIN_DM(to_comp_uart_rts_spi_ss0_PC, \
                                                   to_comp_uart_rts_spi_ss0_SHIFT))
#endif /* (to_comp_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define to_comp_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define to_comp_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define to_comp_SET_HSIOM_SEL(reg, mask, pos, sel) to_comp_SET_REGISTER_BITS(reg, mask, pos, sel)
#define to_comp_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        to_comp_SET_REGISTER_BITS(reg, mask, pos, intType)
#define to_comp_SET_INP_DIS(reg, mask, val) to_comp_SET_REGISTER_BIT(reg, mask, val)

/* to_comp_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  to_comp_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (to_comp_CY_SCBIP_V0)
#if (to_comp_I2C_PINS)
    #define to_comp_SET_I2C_SCL_DR(val) to_comp_scl_Write(val)

    #define to_comp_SET_I2C_SCL_HSIOM_SEL(sel) \
                          to_comp_SET_HSIOM_SEL(to_comp_SCL_HSIOM_REG,  \
                                                         to_comp_SCL_HSIOM_MASK, \
                                                         to_comp_SCL_HSIOM_POS,  \
                                                         (sel))
    #define to_comp_WAIT_SCL_SET_HIGH  (0u == to_comp_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (to_comp_RX_WAKE_SCL_MOSI_PIN)
    #define to_comp_SET_I2C_SCL_DR(val) \
                            to_comp_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define to_comp_SET_I2C_SCL_HSIOM_SEL(sel) \
                    to_comp_SET_HSIOM_SEL(to_comp_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   to_comp_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   to_comp_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define to_comp_WAIT_SCL_SET_HIGH  (0u == to_comp_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (to_comp_RX_SCL_MOSI_PIN)
    #define to_comp_SET_I2C_SCL_DR(val) \
                            to_comp_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define to_comp_SET_I2C_SCL_HSIOM_SEL(sel) \
                            to_comp_SET_HSIOM_SEL(to_comp_RX_SCL_MOSI_HSIOM_REG,  \
                                                           to_comp_RX_SCL_MOSI_HSIOM_MASK, \
                                                           to_comp_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define to_comp_WAIT_SCL_SET_HIGH  (0u == to_comp_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define to_comp_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define to_comp_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define to_comp_WAIT_SCL_SET_HIGH  (0u)
#endif /* (to_comp_I2C_PINS) */

/* SCB I2C: sda signal */
#if (to_comp_I2C_PINS)
    #define to_comp_WAIT_SDA_SET_HIGH  (0u == to_comp_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (to_comp_TX_SDA_MISO_PIN)
    #define to_comp_WAIT_SDA_SET_HIGH  (0u == to_comp_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define to_comp_WAIT_SDA_SET_HIGH  (0u)
#endif /* (to_comp_MOSI_SCL_RX_PIN) */
#endif /* (to_comp_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (to_comp_RX_SCL_MOSI_PIN)
    #define to_comp_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (to_comp_RX_WAKE_SCL_MOSI_PIN)
    #define to_comp_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) to_comp_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(to_comp_UART_RX_WAKE_PIN)
    #define to_comp_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) to_comp_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (to_comp_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define to_comp_REMOVE_MOSI_SCL_RX_WAKE_PIN    to_comp_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define to_comp_REMOVE_MOSI_SCL_RX_PIN         to_comp_REMOVE_RX_SCL_MOSI_PIN
#define to_comp_REMOVE_MISO_SDA_TX_PIN         to_comp_REMOVE_TX_SDA_MISO_PIN
#ifndef to_comp_REMOVE_SCLK_PIN
#define to_comp_REMOVE_SCLK_PIN                to_comp_REMOVE_CTS_SCLK_PIN
#endif /* to_comp_REMOVE_SCLK_PIN */
#ifndef to_comp_REMOVE_SS0_PIN
#define to_comp_REMOVE_SS0_PIN                 to_comp_REMOVE_RTS_SS0_PIN
#endif /* to_comp_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define to_comp_MOSI_SCL_RX_WAKE_PIN   to_comp_RX_WAKE_SCL_MOSI_PIN
#define to_comp_MOSI_SCL_RX_PIN        to_comp_RX_SCL_MOSI_PIN
#define to_comp_MISO_SDA_TX_PIN        to_comp_TX_SDA_MISO_PIN
#ifndef to_comp_SCLK_PIN
#define to_comp_SCLK_PIN               to_comp_CTS_SCLK_PIN
#endif /* to_comp_SCLK_PIN */
#ifndef to_comp_SS0_PIN
#define to_comp_SS0_PIN                to_comp_RTS_SS0_PIN
#endif /* to_comp_SS0_PIN */

#if (to_comp_MOSI_SCL_RX_WAKE_PIN)
    #define to_comp_MOSI_SCL_RX_WAKE_HSIOM_REG     to_comp_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define to_comp_MOSI_SCL_RX_WAKE_HSIOM_PTR     to_comp_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define to_comp_MOSI_SCL_RX_WAKE_HSIOM_MASK    to_comp_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define to_comp_MOSI_SCL_RX_WAKE_HSIOM_POS     to_comp_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define to_comp_MOSI_SCL_RX_WAKE_INTCFG_REG    to_comp_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define to_comp_MOSI_SCL_RX_WAKE_INTCFG_PTR    to_comp_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define to_comp_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   to_comp_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define to_comp_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  to_comp_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (to_comp_RX_WAKE_SCL_MOSI_PIN) */

#if (to_comp_MOSI_SCL_RX_PIN)
    #define to_comp_MOSI_SCL_RX_HSIOM_REG      to_comp_RX_SCL_MOSI_HSIOM_REG
    #define to_comp_MOSI_SCL_RX_HSIOM_PTR      to_comp_RX_SCL_MOSI_HSIOM_PTR
    #define to_comp_MOSI_SCL_RX_HSIOM_MASK     to_comp_RX_SCL_MOSI_HSIOM_MASK
    #define to_comp_MOSI_SCL_RX_HSIOM_POS      to_comp_RX_SCL_MOSI_HSIOM_POS
#endif /* (to_comp_MOSI_SCL_RX_PIN) */

#if (to_comp_MISO_SDA_TX_PIN)
    #define to_comp_MISO_SDA_TX_HSIOM_REG      to_comp_TX_SDA_MISO_HSIOM_REG
    #define to_comp_MISO_SDA_TX_HSIOM_PTR      to_comp_TX_SDA_MISO_HSIOM_REG
    #define to_comp_MISO_SDA_TX_HSIOM_MASK     to_comp_TX_SDA_MISO_HSIOM_REG
    #define to_comp_MISO_SDA_TX_HSIOM_POS      to_comp_TX_SDA_MISO_HSIOM_REG
#endif /* (to_comp_MISO_SDA_TX_PIN_PIN) */

#if (to_comp_SCLK_PIN)
    #ifndef to_comp_SCLK_HSIOM_REG
    #define to_comp_SCLK_HSIOM_REG     to_comp_CTS_SCLK_HSIOM_REG
    #define to_comp_SCLK_HSIOM_PTR     to_comp_CTS_SCLK_HSIOM_PTR
    #define to_comp_SCLK_HSIOM_MASK    to_comp_CTS_SCLK_HSIOM_MASK
    #define to_comp_SCLK_HSIOM_POS     to_comp_CTS_SCLK_HSIOM_POS
    #endif /* to_comp_SCLK_HSIOM_REG */
#endif /* (to_comp_SCLK_PIN) */

#if (to_comp_SS0_PIN)
    #ifndef to_comp_SS0_HSIOM_REG
    #define to_comp_SS0_HSIOM_REG      to_comp_RTS_SS0_HSIOM_REG
    #define to_comp_SS0_HSIOM_PTR      to_comp_RTS_SS0_HSIOM_PTR
    #define to_comp_SS0_HSIOM_MASK     to_comp_RTS_SS0_HSIOM_MASK
    #define to_comp_SS0_HSIOM_POS      to_comp_RTS_SS0_HSIOM_POS
    #endif /* to_comp_SS0_HSIOM_REG */
#endif /* (to_comp_SS0_PIN) */

#define to_comp_MOSI_SCL_RX_WAKE_PIN_INDEX to_comp_RX_WAKE_SCL_MOSI_PIN_INDEX
#define to_comp_MOSI_SCL_RX_PIN_INDEX      to_comp_RX_SCL_MOSI_PIN_INDEX
#define to_comp_MISO_SDA_TX_PIN_INDEX      to_comp_TX_SDA_MISO_PIN_INDEX
#ifndef to_comp_SCLK_PIN_INDEX
#define to_comp_SCLK_PIN_INDEX             to_comp_CTS_SCLK_PIN_INDEX
#endif /* to_comp_SCLK_PIN_INDEX */
#ifndef to_comp_SS0_PIN_INDEX
#define to_comp_SS0_PIN_INDEX              to_comp_RTS_SS0_PIN_INDEX
#endif /* to_comp_SS0_PIN_INDEX */

#define to_comp_MOSI_SCL_RX_WAKE_PIN_MASK to_comp_RX_WAKE_SCL_MOSI_PIN_MASK
#define to_comp_MOSI_SCL_RX_PIN_MASK      to_comp_RX_SCL_MOSI_PIN_MASK
#define to_comp_MISO_SDA_TX_PIN_MASK      to_comp_TX_SDA_MISO_PIN_MASK
#ifndef to_comp_SCLK_PIN_MASK
#define to_comp_SCLK_PIN_MASK             to_comp_CTS_SCLK_PIN_MASK
#endif /* to_comp_SCLK_PIN_MASK */
#ifndef to_comp_SS0_PIN_MASK
#define to_comp_SS0_PIN_MASK              to_comp_RTS_SS0_PIN_MASK
#endif /* to_comp_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_to_comp_H) */


/* [] END OF FILE */
