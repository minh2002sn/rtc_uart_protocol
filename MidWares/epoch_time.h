/**
 * @file       epoch_time.h
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
#ifndef __EPOCH_TIME_H
#define __EPOCH_TIME_H

/* Includes ----------------------------------------------------------- */
#include "stdint.h"
#include "common.h"

/* Public defines ----------------------------------------------------- */
#define EPOCH_TIME_ERROR   (0xFFFFFFFF)
#define EPOCH_TIME_SUCCESS (0x00000000)

#define EPOCH_TIME_SUNDAY    ((uint32_t)0x01)
#define EPOCH_TIME_MONDAY    ((uint32_t)0x02)
#define EPOCH_TIME_TUESDAY   ((uint32_t)0x03)
#define EPOCH_TIME_WEDNESDAY ((uint32_t)0x04)
#define EPOCH_TIME_THURSDAY  ((uint32_t)0x05)
#define EPOCH_TIME_FRIDAY    ((uint32_t)0x06)
#define EPOCH_TIME_SATURDAY  ((uint32_t)0x07)

/* Public enumerate/structure ----------------------------------------- */
typedef struct
{
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
} epoch_time_t;

typedef struct
{
  uint8_t day;
  uint8_t date;
  uint8_t month;
  uint8_t year;
} epoch_date_t;

typedef struct
{
  epoch_time_t time;
  epoch_date_t date;
} epoch_data_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief           Decode epoch datatype to time and date
 *
 * @param[in]       epoch   Epoch datatype need to decode
 * @param[in]       epoch_data    Pointer to epoch_data_t structure (current data)
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t epoch_time_decode(uint32_t epoch, epoch_data_t *epoch_data);

#endif // __EPOCH_TIME_H

/* End of file -------------------------------------------------------- */
