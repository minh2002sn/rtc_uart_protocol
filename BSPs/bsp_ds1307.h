/**
 * @file       bsp_ds1307.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the XXX License.
 * @version    0.0.0
 * @date       yyyy-mm-dd
 * @author     Minh Phung Nhat
 * @author     Hung Pham Duc
 * @author     Khoi Thanh Nguyen
 *
 * @brief      Board Support Package for DS1307 RTC
 *
 * @note       none
 *
 * @example    none
 *
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_DS1307_H
#define __BSP_DS1307_H

/* Includes ----------------------------------------------------------- */
#include "drv_ds1307.h"

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         Initialize DS1307 hardware interface
 *
 * @param[in]     hi2c      Pointer to I2C_HandleTypeDef structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_ds1307_init(I2C_HandleTypeDef *hi2c);

/**
 * @brief         Set DS1307 time through BSP layer
 *
 * @param[in]     time      Pointer to drv_ds1307_time_t structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_ds1307_set_time(drv_ds1307_time_t *time);

/**
 * @brief         Get DS1307 time through BSP layer
 *
 * @param[out]    time      Pointer to drv_ds1307_time_t structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_ds1307_get_time(drv_ds1307_time_t *time);

/**
 * @brief         Set DS1307 date through BSP layer
 *
 * @param[in]     date      Pointer to drv_ds1307_date_t structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_ds1307_set_date(drv_ds1307_date_t *date);

/**
 * @brief         Get DS1307 date through BSP layer
 *
 * @param[out]    date      Pointer to drv_ds1307_date_t structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_ds1307_get_date(drv_ds1307_date_t *date);

/**
 * @brief         Enable DS1307 oscillator frequency through BSP layer
 *
 * @param[in]     osci_freq   Oscillator frequency
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_ds1307_enable_osci(drv_ds1307_osci_freq_t osci_freq);

/**
 * @brief         Disable DS1307 oscillator frequency through BSP layer
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_ds1307_disable_osci(void);

#endif // __BSP_DS1307_H

/* End of file -------------------------------------------------------- */
