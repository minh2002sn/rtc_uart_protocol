/**
 * @file       bsp_ds1307.c
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

/* Includes ----------------------------------------------------------- */
#include "bsp_ds1307.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static drv_ds1307_t ds1307_device;

/* Private function prototypes ---------------------------------------- */

/* Public functions --------------------------------------------------- */
uint32_t bsp_ds1307_init(I2C_HandleTypeDef *hi2c)
{
  ASSERT(hi2c != NULL, DRV_DS1307_ERROR);

  return drv_ds1307_init(&ds1307_device, hi2c);
}

uint32_t bsp_ds1307_set_time(drv_ds1307_time_t *time)
{
  ASSERT(time != NULL, DRV_DS1307_ERROR);

  return drv_ds1307_set_time(&ds1307_device, time, DRV_DS1307_TIME_FORMAT_24);
}

uint32_t bsp_ds1307_get_time(drv_ds1307_time_t *time)
{
  ASSERT(time != NULL, DRV_DS1307_ERROR);

  return drv_ds1307_get_time(&ds1307_device, time);
}

uint32_t bsp_ds1307_set_date(drv_ds1307_date_t *date)
{
  ASSERT(date != NULL, DRV_DS1307_ERROR);

  return drv_ds1307_set_date(&ds1307_device, date);
}

uint32_t bsp_ds1307_get_date(drv_ds1307_date_t *date)
{
  ASSERT(date != NULL, DRV_DS1307_ERROR);

  return drv_ds1307_get_date(&ds1307_device, date);
}

uint32_t bsp_ds1307_enable_osci(drv_ds1307_osci_freq_t osci_freq)
{
  return drv_ds1307_enable_osci(&ds1307_device, osci_freq);
}

uint32_t bsp_ds1307_disable_osci(void)
{
  return drv_ds1307_disable_osci(&ds1307_device);
}

/* End of file -------------------------------------------------------- */
