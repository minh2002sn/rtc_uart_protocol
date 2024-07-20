/**
 * @file       drv_ds1307.c
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

/* Includes ----------------------------------------------------------- */
#include "drv_ds1307.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */
#define DS1307_ADDRESS (0x68 << 1) // I2C address for DS1307
#define TIME_ADDRESS   (0x00)      // Time register address
#define DATE_ADDRESS   (0x03)      // Date register address
#define OSC_ADDRESS    (0x07)      // Osci register address

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static uint16_t d_mem_size  = 1;
static uint16_t d_date_size = 1;
static uint16_t d_ocsi_size = 1;

/* Private function prototypes ---------------------------------------- */
static uint8_t d_bcd2dec(uint8_t d_bcd_val);
static uint8_t d_dec2bcd(uint8_t d_dec_val);

/* Public functions --------------------------------------------------- */
uint32_t drv_ds1307_init(drv_ds1307_t *ds1307, I2C_HandleTypeDef *hi2c)
{
  ASSERT((ds1307 != NULL) || (hi2c != NULL), DRV_DS1307_ERROR);

  ds1307->hi2c = hi2c;

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_set_time(drv_ds1307_t *ds1307, drv_ds1307_time_t *time, drv_ds1307_time_format_t time_format)
{
  ASSERT((ds1307 != NULL) || (time != NULL), DRV_DS1307_ERROR);
  ASSERT((time_format != DRV_DS1307_TIME_FORMAT_12) || (time_format != DRV_DS1307_TIME_FORMAT_24),
         DRV_DS1307_ERROR);

  uint8_t data[3];
  data[0] = drv_dec2bcd(time->sec);
  data[1] = drv_dec2bcd(time->min);
  data[2] = drv_dec2bcd(time->hour);

  if (time_format == DRV_DS1307_TIME_FORMAT_12)
  {
    data[2] |= 0x40; // 12-hour format
  }

  if (HAL_I2C_Mem_Write(ds1307->hi2c, DS1307_ADDRESS, TIME_ADDRESS, d_mem_size,
                        data, sizeof(data), HAL_MAX_DELAY) != HAL_OK)
  {
    return DRV_DS1307_ERROR;
  }

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_get_time(drv_ds1307_t *ds1307, drv_ds1307_time_t *time)
{
  ASSERT((ds1307 != NULL) || (time != NULL), DRV_DS1307_ERROR);

  uint8_t data[3];

  if (HAL_I2C_Mem_Read(ds1307->hi2c, DS1307_ADDRESS, TIME_ADDRESS, d_mem_size,
                       data, sizeof(data), HAL_MAX_DELAY) != HAL_OK)
  {
    return DRV_DS1307_ERROR;
  }

  time->sec  = drv_bcd2dec(data[0]);
  time->min  = drv_bcd2dec(data[1]);
  time->hour = drv_bcd2dec(data[2] & 0x3F); // Mask the 12/24 hour bit

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_set_date(drv_ds1307_t *ds1307, drv_ds1307_date_t *date)
{
  ASSERT((ds1307 != NULL) || (date != NULL), DRV_DS1307_ERROR);

  uint8_t data[4];
  data[0] = drv_dec2bcd(date->day);
  data[1] = drv_dec2bcd(date->date);
  data[2] = drv_dec2bcd(date->month);
  data[3] = drv_dec2bcd(date->year);

  if (HAL_I2C_Mem_Write(ds1307->hi2c, DS1307_ADDRESS, DATE_ADDRESS, d_date_size,
                        data, sizeof(data), HAL_MAX_DELAY) != HAL_OK)
  {
    return DRV_DS1307_ERROR;
  }

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_get_date(drv_ds1307_t *ds1307, drv_ds1307_date_t *date)
{
  ASSERT((ds1307 != NULL) || (date != NULL), DRV_DS1307_ERROR);

  uint8_t data[4];

  if (HAL_I2C_Mem_Read(ds1307->hi2c, DS1307_ADDRESS, DATE_ADDRESS, d_date_size,
                       data, sizeof(data), HAL_MAX_DELAY) != HAL_OK)
  {
    return DRV_DS1307_ERROR;
  }

  date->day   = drv_bcd2dec(data[0]);
  date->date  = drv_bcd2dec(data[1]);
  date->month = drv_bcd2dec(data[2]);
  date->year  = drv_bcd2dec(data[3]);

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_set_time_format(drv_ds1307_t *ds1307, drv_ds1307_time_format_t time_format)
{
  ASSERT((ds1307 != NULL), DRV_DS1307_ERROR);
  ASSERT((time_format != DRV_DS1307_TIME_FORMAT_12) || (time_format != DRV_DS1307_TIME_FORMAT_24),
         DRV_DS1307_ERROR);

  uint8_t data;
  // Read curr format time
  if (HAL_I2C_Mem_Read(ds1307->hi2c, DS1307_ADDRESS, TIME_ADDRESS, d_mem_size,
                       data, sizeof(data), HAL_MAX_DELAY) != HAL_OK)
  {
    return DRV_DS1307_ERROR;
  }

  if (time_format == DRV_DS1307_TIME_FORMAT_12)
  {
    data |= 0x40; // Set 12-hour format bit
  }
  else
  {
    data &= ~0x40; // Ensure 24-hour format
  }

  // Write new format time
  if (HAL_I2C_Mem_Write(ds1307->hi2c, DS1307_ADDRESS, TIME_ADDRESS, d_mem_size,
                        data, sizeof(data), HAL_MAX_DELAY) != HAL_OK)
  {
    return DRV_DS1307_ERROR;
  }

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_enable_osci(drv_ds1307_t *ds1307, drv_ds1307_osci_freq_t osci_freq)
{
  ASSERT((ds1307 != NULL), DRV_DS1307_ERROR);
  ASSERT((osci_freq != DRV_DS1307_OSCI_FREQ_1_HZ) ||
         (osci_freq != DRV_DS1307_OSCI_FREQ_4096_KHZ) ||
         (osci_freq != DRV_DS1307_OSCI_FREQ_8192_KHZ) ||
         (osci_freq != DRV_DS1307_OSCI_FREQ_32768_KHZ),
         DRV_DS1307_ERROR);

  uint8_t data_osci;
  // Read curr format time
  if (HAL_I2C_Mem_Read(ds1307->hi2c, DS1307_ADDRESS, OSC_ADDRESS, d_ocsi_size,
                       data_osci, sizeof(data_osci), HAL_MAX_DELAY) != HAL_OK)
  {
    return DRV_DS1307_ERROR;
  }

  // Turn on bit OSC
  data_osci |= 0x80; // 1000 0000

  // Write new format time
  if (HAL_I2C_Mem_Write(ds1307->hi2c, DS1307_ADDRESS, OSC_ADDRESS, d_ocsi_size,
                        data_osci, sizeof(data_osci), HAL_MAX_DELAY) != HAL_OK)
  {
    return DRV_DS1307_ERROR;
  }

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_disable_osci(drv_ds1307_t *ds1307)
{
  ASSERT((ds1307 != NULL), DRV_DS1307_ERROR);

  uint8_t data_osci;
  // Read curr format time
  if (HAL_I2C_Mem_Read(ds1307->hi2c, DS1307_ADDRESS, OSC_ADDRESS, d_ocsi_size,
                       data_osci, sizeof(data_osci), HAL_MAX_DELAY) != HAL_OK)
  {
    return DRV_DS1307_ERROR;
  }

  // Turn off bit OSC
  data_osci &= ~0x80;

  // Write new format time
  if (HAL_I2C_Mem_Write(ds1307->hi2c, DS1307_ADDRESS, OSC_ADDRESS, d_ocsi_size,
                        data_osci, sizeof(data_osci), HAL_MAX_DELAY) != HAL_OK)
  {
    return DRV_DS1307_ERROR;
  }

  return DRV_DS1307_SUCCESS;
}

/* Private functions -------------------------------------------------- */
static uint8_t drv_bcd2dec(uint8_t d_bcd_val)
{
  return ((d_bcd_val >> 4) * 10) + (d_bcd_val & 0x0F);
}

static uint8_t drv_dec2bcd(uint8_t d_dec_val)
{
  return ((d_dec_val / 10) << 4) | (d_dec_val % 10);
}

/* End of file -------------------------------------------------------- */
