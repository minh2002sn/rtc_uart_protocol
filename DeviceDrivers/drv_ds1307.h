/**
 * @file       drv_ds1307.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the XXX License.
 * @version    0.0.0
 * @date       yyyy-mm-dd
 * @author     Minh Phung Nhat
 * @author     Hung Pham Duc
 * @author     Khoi Thanh Nguyen
 *
 * @brief      none
 *
 * @note       none
 *
 * @example    none
 *
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DRV_DS1307_H
#define __DRV_DS1307_H

/* Includes ----------------------------------------------------------- */
#include "main.h"
#include <stdint.h>


/* Public defines ----------------------------------------------------- */
#define DRV_DS1307_ERROR   (0xFFFFFFFF)
#define DRV_DS1307_SUCCESS (0x00000000)

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  DRV_DS1307_TIME_FORMAT_12,
  DRV_DS1307_TIME_FORMAT_24,
} drv_ds1307_time_format_t;

typedef struct
{
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
} drv_ds1307_time_t;

typedef struct
{
  uint8_t day;
  uint8_t date;
  uint8_t month;
  uint8_t year;
} drv_ds1307_date_t;

typedef enum
{
  DRV_DS1307_OSCI_FREQ_1_HZ,
  DRV_DS1307_OSCI_FREQ_4096_KHZ,
  DRV_DS1307_OSCI_FREQ_8192_KHZ,
  DRV_DS1307_OSCI_FREQ_32768_KHZ
} drv_ds1307_osci_freq_t;

typedef struct
{
  drv_ds1307_time_format_t time_format;
  drv_ds1307_time_t        time;
  drv_ds1307_date_t        data;
  drv_ds1307_osci_freq_t   osci_freq;
  I2C_HandleTypeDef       *hi2c;
} drv_ds1307_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         DS1307 init function
 *
 * @param[in]     ds1307    Pointer to drv_ds1307_t structure
 * @param[in]     hi2c      Pointer to I2C_HandleTypeDef structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t drv_ds1307_init(drv_ds1307_t *ds1307, I2C_HandleTypeDef *hi2c);

/**
 * @brief         Set time function
 *
 * @param[in]     ds1307    Pointer to drv_ds1307_t structure
 * @param[in]     time      Pointer to drv_ds1307_time_t structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t drv_ds1307_set_time(drv_ds1307_t            *ds1307,
                             drv_ds1307_time_t       *time,
                             drv_ds1307_time_format_t time_format);

/**
 * @brief         Get time function
 *
 * @param[in]     ds1307    Pointer to drv_ds1307_t structure
 * @param[out]    time      Pointer to drv_ds1307_time_t structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t drv_ds1307_get_time(drv_ds1307_t *ds1307, drv_ds1307_time_t *time);

/**
 * @brief         Set date function
 *
 * @param[in]     ds1307    Pointer to drv_ds1307_t structure
 * @param[in]     date      Pointer to drv_ds1307_date_t structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t drv_ds1307_set_date(drv_ds1307_t *ds1307, drv_ds1307_date_t *date);

/**
 * @brief         Get date function
 *
 * @param[in]     ds1307    Pointer to drv_ds1307_t structure
 * @param[out]    date      Pointer to drv_ds1307_date_t structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t drv_ds1307_det_date(drv_ds1307_t *ds1307, drv_ds1307_date_t *date);

/**
 * @brief         Set time format
 *
 * @param[in]     ds1307      Pointer to drv_ds1307_t structure
 * @param[in]     time_format Time format
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t drv_ds1307_set_time_format(drv_ds1307_t *ds1307, drv_ds1307_time_format_t time_format);

/**
 * @brief         Enable oscillator
 *
 * @param[in]     ds1307      Pointer to drv_ds1307_t structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t drv_ds1307_enable_osci(drv_ds1307_t *ds1307);

/**
 * @brief         Disable oscillator
 *
 * @param[in]     ds1307      Pointer to drv_ds1307_t structure
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t drv_ds1307_disable_osci(drv_ds1307_t *ds1307);

/**
 * @brief         Set oscillator frequency
 *
 * @param[in]     ds1307      Pointer to drv_ds1307_t structure
 * @param[in]     osci_freq   Oscillator frequency
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
uint32_t drv_ds1307_set_osci_freq(drv_ds1307_t *ds1307, drv_ds1307_osci_freq_t osci_freq);

#endif // __DRV_DS1307_H

/* End of file -------------------------------------------------------- */
