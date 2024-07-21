/**
 * @file       bsp_rtc.h
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
#ifndef __BSP_RTC_H
#define __BSP_RTC_H

/* Includes ----------------------------------------------------------- */
#include "drv_ds1307.h"

/* Public defines ----------------------------------------------------- */
#define BSP_RTC_ERROR   (0xFFFFFFFF)
#define BSP_RTC_SUCCESS (0x00000000)

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         Initialize RTC hardware interface
 *
 * @param[in]     hi2c      Pointer to I2C_HandleTypeDef structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_rtc_init(I2C_HandleTypeDef *hi2c);

/**
 * @brief         Set RTC time through BSP layer
 *
 * @param[in]     time             Pointer to drv_ds1307_time_t structure
 * @param[in]     time_format      Pointer to drv_ds1307_time_format_t structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_rtc_set_time(drv_ds1307_time_t *time, drv_ds1307_time_format_t time_format);

/**
 * @brief         Get RTC time through BSP layer
 *
 * @param[out]    time      Pointer to drv_ds1307_time_t structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_rtc_get_time(drv_ds1307_time_t *time);

/**
 * @brief         Set RTC date through BSP layer
 *
 * @param[in]     date      Pointer to drv_ds1307_date_t structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_rtc_set_date(drv_ds1307_date_t *date);

/**
 * @brief         Get RTC date through BSP layer
 *
 * @param[out]    date      Pointer to drv_ds1307_date_t structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_rtc_get_date(drv_ds1307_date_t *date);

/**
 * @brief         Enable RTC oscillator frequency through BSP layer
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_rtc_enable_osci(void);

/**
 * @brief         Disable RTC oscillator frequency through BSP layer
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_rtc_disable_osci(void);

/**
 * @brief         Set RTC oscillator frequency through BSP layer
 *
 * @param[in]     osci_freq   Oscillator frequency
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t bsp_rtc_set_osci_freg(drv_ds1307_osci_freq_t osci_freq);

#endif // __BSP_RTC_H

/* End of file -------------------------------------------------------- */
