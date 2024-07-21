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
#define DRV_DS1307_I2C_ADDRESS        (0x68 << 1) // I2C address for DS1307
#define DRV_DS1307_TIME_ADDRESS       (0x00)      // Time register address
#define DRV_DS1307_DATE_ADDRESS       (0x03)      // Date register address
#define DRV_DS1307_OSC_ADDRESS        (0x00)      // Osci register address
#define DRV_DS1307_ENA_12H_FORMAT_BIT (0x40)
#define DRV_DS1307_ENA_OSCI_BIT       (0x80)
#define DRV_DS1307_MEM_SIZE           (0x01)

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */
/**
 * @brief         Convert BCD to decimal
 *
 * @param[in]     d_bcd_val   BCD value to convert
 *
 * @return        Decimal value converted from BCD
 */
static uint8_t drv_bcd2dec(uint8_t d_bcd_val);

/**
 * @brief         Convert decimal to BCD
 *
 * @param[in]     d_dec_val   Decimal value to convert
 *
 * @return        BCD value converted from decimal
 */
static uint8_t drv_dec2bcd(uint8_t d_dec_val);

/* Public functions --------------------------------------------------- */
uint32_t drv_ds1307_init(drv_ds1307_t *ds1307, I2C_HandleTypeDef *hi2c)
{
  ASSERT(ds1307 == NULL, DRV_DS1307_ERROR);
  ASSERT(hi2c == NULL, DRV_DS1307_ERROR);

  ds1307->hi2c = hi2c;

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_set_time(drv_ds1307_t *ds1307, drv_ds1307_time_t *time, drv_ds1307_time_format_t time_format)
{
  HAL_StatusTypeDef ret;
  uint8_t           data[3];

  ASSERT(ds1307 == NULL, DRV_DS1307_ERROR);
  ASSERT(time == NULL, DRV_DS1307_ERROR);
  ASSERT((time_format == DRV_DS1307_TIME_FORMAT_12) || (time_format == DRV_DS1307_TIME_FORMAT_24),
         DRV_DS1307_ERROR);

  data[0] = drv_dec2bcd(time->sec);
  data[1] = drv_dec2bcd(time->min);
  data[2] = drv_dec2bcd(time->hour);

  if (time_format == DRV_DS1307_TIME_FORMAT_12)
  {
    data[2] |= DRV_DS1307_ENA_12H_FORMAT_BIT; // 12-hour format
  }

  ret = HAL_I2C_Mem_Write(ds1307->hi2c, DRV_DS1307_I2C_ADDRESS, DRV_DS1307_TIME_ADDRESS,
                          DRV_DS1307_MEM_SIZE, data, sizeof(data), HAL_MAX_DELAY);
  ASSERT(ret == HAL_OK, DRV_DS1307_ERROR);

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_get_time(drv_ds1307_t *ds1307, drv_ds1307_time_t *time)
{
  HAL_StatusTypeDef ret;
  uint8_t           data[3];

  ASSERT(ds1307 == NULL, DRV_DS1307_ERROR);
  ASSERT(time == NULL, DRV_DS1307_ERROR);

  ret = HAL_I2C_Mem_Read(ds1307->hi2c, DRV_DS1307_I2C_ADDRESS, DRV_DS1307_TIME_ADDRESS,
                         DRV_DS1307_MEM_SIZE, data, sizeof(data), HAL_MAX_DELAY);
  ASSERT(ret == HAL_OK, DRV_DS1307_ERROR);

  time->sec  = drv_bcd2dec(data[0]);
  time->min  = drv_bcd2dec(data[1]);
  time->hour = drv_bcd2dec(data[2] & 0x3F); // Mask the 12/24 hour bit

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_set_date(drv_ds1307_t *ds1307, drv_ds1307_date_t *date)
{
  HAL_StatusTypeDef ret;
  uint8_t           data[4];

  ASSERT(ds1307 == NULL, DRV_DS1307_ERROR);
  ASSERT(date == NULL, DRV_DS1307_ERROR);

  data[0] = drv_dec2bcd(date->day);
  data[1] = drv_dec2bcd(date->date);
  data[2] = drv_dec2bcd(date->month);
  data[3] = drv_dec2bcd(date->year);

  ret = HAL_I2C_Mem_Write(ds1307->hi2c, DRV_DS1307_I2C_ADDRESS, DRV_DS1307_DATE_ADDRESS,
                          DRV_DS1307_MEM_SIZE, data, sizeof(data), HAL_MAX_DELAY);
  ASSERT(ret == HAL_OK, DRV_DS1307_ERROR);

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_get_date(drv_ds1307_t *ds1307, drv_ds1307_date_t *date)
{
  HAL_StatusTypeDef ret;
  uint8_t           data[4];

  ASSERT(ds1307 == NULL, DRV_DS1307_ERROR);
  ASSERT(date == NULL, DRV_DS1307_ERROR);

  ret = HAL_I2C_Mem_Read(ds1307->hi2c, DRV_DS1307_I2C_ADDRESS, DRV_DS1307_DATE_ADDRESS,
                         DRV_DS1307_MEM_SIZE, data, sizeof(data), HAL_MAX_DELAY);
  ASSERT(ret == HAL_OK, DRV_DS1307_ERROR);

  date->day   = drv_bcd2dec(data[0]);
  date->date  = drv_bcd2dec(data[1]);
  date->month = drv_bcd2dec(data[2]);
  date->year  = drv_bcd2dec(data[3]);

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_set_time_format(drv_ds1307_t *ds1307, drv_ds1307_time_format_t time_format)
{
  HAL_StatusTypeDef ret;
  uint8_t           data;

  ASSERT((ds1307 == NULL), DRV_DS1307_ERROR);
  ASSERT((time_format == DRV_DS1307_TIME_FORMAT_12) || (time_format == DRV_DS1307_TIME_FORMAT_24),
         DRV_DS1307_ERROR);

  // Read curr format time
  ret = HAL_I2C_Mem_Read(ds1307->hi2c, DRV_DS1307_I2C_ADDRESS, DRV_DS1307_TIME_ADDRESS,
                         DRV_DS1307_MEM_SIZE, data, sizeof(data), HAL_MAX_DELAY);
  ASSERT(ret == HAL_OK, DRV_DS1307_ERROR);

  if (time_format == DRV_DS1307_TIME_FORMAT_12)
  {
    data |= DRV_DS1307_ENA_12H_FORMAT_BIT; // Set 12-hour format bit
  }
  else
  {
    data &= ~DRV_DS1307_ENA_OSCI_BIT; // Ensure 24-hour format
  }

  // Write new format time
  ret = HAL_I2C_Mem_Write(ds1307->hi2c, DRV_DS1307_I2C_ADDRESS, DRV_DS1307_TIME_ADDRESS,
                          DRV_DS1307_MEM_SIZE, data, sizeof(data), HAL_MAX_DELAY);
  ASSERT(ret == HAL_OK, DRV_DS1307_ERROR);

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_enable_osci(drv_ds1307_t *ds1307)
{
  HAL_StatusTypeDef ret;
  uint8_t           data_osci;

  ASSERT((ds1307 == NULL), DRV_DS1307_ERROR);

  // Read curr format time
  ret = HAL_I2C_Mem_Read(ds1307->hi2c, DRV_DS1307_I2C_ADDRESS, DRV_DS1307_OSC_ADDRESS,
                         DRV_DS1307_MEM_SIZE, data_osci, sizeof(data_osci), HAL_MAX_DELAY);
  ASSERT(ret == HAL_OK, DRV_DS1307_ERROR);

  // Turn on bit OSC
  data_osci &= ~DRV_DS1307_ENA_OSCI_BIT; // 1000 0000

  // Write new format time
  ret = HAL_I2C_Mem_Write(ds1307->hi2c, DRV_DS1307_I2C_ADDRESS,
                          DRV_DS1307_OSC_ADDRESS, DRV_DS1307_MEM_SIZE,
                          data_osci, sizeof(data_osci), HAL_MAX_DELAY);
  ASSERT(ret == HAL_OK, DRV_DS1307_ERROR);

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_disable_osci(drv_ds1307_t *ds1307)
{
  HAL_StatusTypeDef ret;
  uint8_t           data_osci;

  ASSERT((ds1307 == NULL), DRV_DS1307_ERROR);

  // Read curr format time
  ret = HAL_I2C_Mem_Read(ds1307->hi2c, DRV_DS1307_I2C_ADDRESS, DRV_DS1307_OSC_ADDRESS,
                         DRV_DS1307_MEM_SIZE, data_osci, sizeof(data_osci), HAL_MAX_DELAY);
  ASSERT(ret == HAL_OK, DRV_DS1307_ERROR);

  // Turn off bit OSC
  data_osci |= DRV_DS1307_ENA_OSCI_BIT;

  // Write new format time
  ret = HAL_I2C_Mem_Write(ds1307->hi2c, DRV_DS1307_I2C_ADDRESS,
                          DRV_DS1307_OSC_ADDRESS, DRV_DS1307_MEM_SIZE,
                          data_osci, sizeof(data_osci), HAL_MAX_DELAY);
  ASSERT(ret == HAL_OK, DRV_DS1307_ERROR);

  return DRV_DS1307_SUCCESS;
}

uint32_t drv_ds1307_set_osci_freq(drv_ds1307_t *ds1307, drv_ds1307_osci_freq_t osci_freq)
{
  HAL_StatusTypeDef ret;
  uint8_t           data_osci;

  ASSERT((ds1307 == NULL), DRV_DS1307_ERROR);
  ASSERT((osci_freq == DRV_DS1307_OSCI_FREQ_1_HZ) ||
         (osci_freq == DRV_DS1307_OSCI_FREQ_4096_KHZ) ||
         (osci_freq == DRV_DS1307_OSCI_FREQ_8192_KHZ) ||
         (osci_freq == DRV_DS1307_OSCI_FREQ_32768_KHZ),
         DRV_DS1307_ERROR);

  // Read curr format time
  ret = HAL_I2C_Mem_Read(ds1307->hi2c, DRV_DS1307_I2C_ADDRESS, DRV_DS1307_OSC_ADDRESS,
                         DRV_DS1307_MEM_SIZE, data_osci, sizeof(data_osci), HAL_MAX_DELAY);
  ASSERT(ret == HAL_OK, DRV_DS1307_ERROR);

  // Clear old freq
  data_osci &= ~0x03;

  // Set Osci freq
  data_osci |= (osci_freq & 0x03);

  // Write new format time
  ret = HAL_I2C_Mem_Write(ds1307->hi2c, DRV_DS1307_I2C_ADDRESS,
                          DRV_DS1307_OSC_ADDRESS, DRV_DS1307_MEM_SIZE,
                          data_osci, sizeof(data_osci), HAL_MAX_DELAY);
  ASSERT(ret == HAL_OK, DRV_DS1307_ERROR);

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
