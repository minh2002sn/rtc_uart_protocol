/**
 * @file        sys_mng.c
 * @copyright
 * @license
 * @version     0.0.0
 * @date
 * @author      Minh Phung Nhat
 *              Hung Pham Duc
 *              Khoi Nguyen Thanh
 * @brief       none
 *
 * @note        none
 *
 * @example     none
 *
 */

/* Includes ----------------------------------------------------------- */
#include "epoch_time.h"

/* Private defines ---------------------------------------------------- */
#define SECOND_PER_DAY     (uint32_t)(86400)
#define SECOND_PER_HOUR    (uint32_t)(3600)
#define SECOND_PER_MINUTE  (uint32_t)(60)
#define MINUTE_PER_HOUR    (uint32_t)(60)
#define MONTH_PER_YEAR     12
#define DAY_PER_YEAR       (uint32_t)(365)
#define DAY_PER_LEAP_YEAR  (uint32_t)(366)
#define DAY_PER_WEEK       (uint32_t)(7)
#define GMT_TO_GMT7_SECOND 25200

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
static uint8_t days_in_month[MONTH_PER_YEAR] = { 31, 28, 31, 30, 31, 30,
                                                 31, 31, 30, 31, 30, 31 };

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */
/**
 * @brief           Check if current year is leap year
 *
 * @param[in]       year              Pointer to current year
 * @param[in]       curr_year_days    Number of day in current year
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t check_year(uint32_t year, uint32_t *curr_year_days);

/* Function definitions ----------------------------------------------- */
uint32_t epoch_time_decode(uint32_t epoch, epoch_data_t *epoch_data)
{
  ASSERT(epoch_data != NULL, EPOCH_TIME_ERROR);
  // Adjust epoch data from GMT to GMT+7
  epoch += GMT_TO_GMT7_SECOND;

  // Calculate hour, minute, second
  uint32_t curr_day_second =
  epoch % SECOND_PER_DAY; /*Number of seconds have passed in current day*/
  uint32_t curr_hour = (uint8_t)(curr_day_second / SECOND_PER_HOUR);
  uint32_t curr_min  = (uint8_t)((curr_day_second / SECOND_PER_MINUTE) -
                                (curr_day_second / SECOND_PER_HOUR) * MINUTE_PER_HOUR);
  uint32_t curr_sec  = (uint8_t)(curr_day_second % SECOND_PER_MINUTE);

  // Calculate year, month, date, day
  uint32_t days_passed = epoch / SECOND_PER_DAY; /*Number of days have passed since 01/01/1970*/
  uint32_t curr_year      = 70;  /*Start year of epoch time data, year 1970*/
  uint32_t curr_year_days = 365; /*Number of day in year 1970*/
  uint32_t curr_month     = 1;   /*Start month of epoch time data, January*/
  uint32_t curr_date      = 1;   /*Start day of epoch time data, 1st*/
  uint32_t curr_day       = EPOCH_TIME_THURSDAY; /*Day of 01/01/1970*/

  // Caculate day
  uint32_t day = days_passed % DAY_PER_WEEK;
  if (day < 3)
  {
    curr_day += day;
  }
  else
  {
    curr_day = (day - 2);
  }

  // Caculate year
  uint32_t ret;
  while (days_passed > curr_year_days)
  {
    days_passed -= curr_year_days;
    curr_year++;
    ret = check_year(curr_year, &curr_year_days);
    ASSERT(ret == EPOCH_TIME_SUCCESS, EPOCH_TIME_ERROR);
    if (curr_year_days == 366)
    {
      days_in_month[1] = 29;
    }
    else
    {
      days_in_month[1] = 28;
    }
  }

  // Caculate month
  while (days_passed > days_in_month[curr_month - 1])
  {
    days_passed -= days_in_month[curr_month - 1];
    curr_month++;
  }

  // Caculate date
  if (days_passed == days_in_month[curr_month - 1])
  {
    curr_month++;
    if (curr_month > MONTH_PER_YEAR)
    {
      curr_month = 1;
      curr_year += 1;
    }
    curr_date = 1;
  }
  else
  {
    curr_date = days_passed + 1;
  }

  // Assign data
  epoch_data->time.hour  = (uint8_t)(curr_hour);
  epoch_data->time.min   = (uint8_t)(curr_min);
  epoch_data->time.sec   = (uint8_t)(curr_sec);
  epoch_data->date.day   = (uint8_t)(curr_day);
  epoch_data->date.date  = (uint8_t)(curr_date);
  epoch_data->date.month = (uint8_t)(curr_month);
  epoch_data->date.year  = (uint8_t)(curr_year - 100);

  return EPOCH_TIME_SUCCESS;
}

/* Private definitions ----------------------------------------------- */
uint32_t check_year(uint32_t year, uint32_t *curr_year_days)
{
  ASSERT(curr_year_days != NULL, EPOCH_TIME_ERROR);
  if ((year % 4) == 0)
  {
    *curr_year_days = 366;
  }
  else
  {
    *curr_year_days = 365;
  }
  return EPOCH_TIME_SUCCESS;
}

/* End of file -------------------------------------------------------- */
