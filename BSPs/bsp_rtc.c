/**
 * @file       bsp_rtc.c
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
#include "bsp_rtc.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static drv_ds1307_t ds1307_device;

/* Private function prototypes ---------------------------------------- */

/* Public functions --------------------------------------------------- */
uint32_t bsp_rtc_init(I2C_HandleTypeDef *hi2c)
{
  uint32_t ret;
  ASSERT(hi2c == NULL, BSP_RTC_ERROR);

  ret = drv_ds1307_init(&ds1307_device, hi2c);
  ASSERT(ret == DRV_DS1307_SUCCESS, BSP_RTC_ERROR);

  return BSP_RTC_SUCCESS;
}

uint32_t bsp_rtc_set_time(drv_ds1307_time_t *time, drv_ds1307_time_format_t time_format)
{
  uint32_t ret;
  ASSERT(time == NULL, BSP_RTC_ERROR);
  ASSERT((time_format == DRV_DS1307_TIME_FORMAT_12) || (time_format == DRV_DS1307_TIME_FORMAT_24),
         BSP_RTC_ERROR);

  ret = drv_ds1307_set_time(&ds1307_device, time, time_format);
  ASSERT(ret == DRV_DS1307_SUCCESS, BSP_RTC_ERROR);

  return BSP_RTC_SUCCESS;
}

uint32_t bsp_rtc_get_time(drv_ds1307_time_t *time)
{
  uint32_t ret;
  ASSERT(time == NULL, BSP_RTC_ERROR);

  ret = drv_ds1307_get_time(&ds1307_device, time);
  ASSERT(ret == DRV_DS1307_SUCCESS, BSP_RTC_ERROR);

  return BSP_RTC_SUCCESS;
}

uint32_t bsp_rtc_set_date(drv_ds1307_date_t *date)
{
  uint32_t ret;
  ASSERT(date == NULL, BSP_RTC_ERROR);

  ret = drv_ds1307_set_date(&ds1307_device, date);
  ASSERT(ret == DRV_DS1307_SUCCESS, BSP_RTC_ERROR);

  return BSP_RTC_SUCCESS;
}

uint32_t bsp_rtc_get_date(drv_ds1307_date_t *date)
{
  uint32_t ret;
  ASSERT(date == NULL, BSP_RTC_ERROR);

  ret = drv_ds1307_get_date(&ds1307_device, date);
  ASSERT(ret == DRV_DS1307_SUCCESS, BSP_RTC_ERROR);

  return BSP_RTC_SUCCESS;
}

uint32_t bsp_rtc_enable_osci(void)
{
  uint32_t ret;

  ret = drv_ds1307_enable_osci(&ds1307_device);
  ASSERT(ret == DRV_DS1307_SUCCESS, BSP_RTC_ERROR);

  return BSP_RTC_SUCCESS;
}

uint32_t bsp_rtc_disable_osci(void)
{
  uint32_t ret;

  ret = drv_ds1307_disable_osci(&ds1307_device);
  ASSERT(ret == DRV_DS1307_SUCCESS, BSP_RTC_ERROR);

  return BSP_RTC_SUCCESS;
}

uint32_t bsp_rtc_set_osci_freg(drv_ds1307_osci_freq_t osci_freq)
{
  uint32_t ret;

  ret = drv_ds1307_set_osci_freq(&ds1307_device, osci_freq);
  ASSERT(ret == DRV_DS1307_SUCCESS, BSP_RTC_ERROR);

  return BSP_RTC_SUCCESS;
}

/* End of file -------------------------------------------------------- */
