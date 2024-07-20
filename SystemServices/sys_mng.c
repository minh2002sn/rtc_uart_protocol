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
/* Define to prevent recursive inclusion ------------------------------ */
#include "sys_mng.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */
#define SYS_MNG_CBUFFER_SIZE            (20) /*Size of circular buffer*/
#define SYS_MNG_MESSAGE_SIZE            (5)  /*Size of data message*/
#define SYS_MNG_MESSAGE_EVENT_INDEX     (0) /*Index of event in message buffer*/
#define SYS_MNG_MESSAGE_HOUR_DATA_INDEX (1) /*Index of hour in message buffer*/
#define SYS_MNG_MESSAGE_MINUTE_DATA_INDEX \
  (2) /*Index of minute in message buffer*/
#define SYS_MNG_MESSAGE_SECOND_DATA_INDEX \
  (3)                                  /*Index of second in message buffer*/
#define SYS_MNG_MESSAGE_EPOCH_SIZE (4) /*Size of epoch datatype*/

#define SYS_MNG_MESSAGE_1ST_DATA_INDEX (1) /*Index of epoch data type*/
#define SYS_MNG_MESSAGE_2ND_DATA_INDEX (2)
#define SYS_MNG_MESSAGE_3RD_DATA_INDEX (3)
#define SYS_MNG_MESSAGE_4TH_DATA_INDEX (4)

#define SYS_MNG_TICK_HOUR   3600000
#define SYS_MNG_TICK_MINUTE 60000
#define SYS_MNG_TICK_SECOND 1000

/* Private enumerate/structure ---------------------------------------- */
typedef struct
{
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
} smng_time_t;

typedef struct
{
  uint8_t day;
  uint8_t date;
  uint8_t month;
  uint8_t year;
} smng_date_t;

typedef enum
{
  SYS_MNG_STATE_CHECK_IDLE,
  SYS_MNG_STATE_CHECK_HOUR,
  SYS_MNG_STATE_CHECK_MINUTE,
  SYS_MNG_STATE_CHECK_SECOND,
  SYS_MNG_STATE_CHECK_ALARM
} smng_state_t;

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static cbuffer_t    smng_cb;
static uint8_t      smng_cb_buf[SYS_MNG_CBUFFER_SIZE]  = { 0 };
static uint8_t      smng_msg_buf[SYS_MNG_MESSAGE_SIZE] = { 0 };
static uint8_t      smng_msg_evt                       = 0;
static smng_time_t  smng_curr_time;
static smng_date_t  smng_curr_date;
static smng_time_t  smng_alarm_time;
static uint32_t     smng_start_tick = 0;
static smng_state_t smng_state      = SYS_MNG_STATE_CHECK_IDLE;
static uint32_t     smng_alarm_tick = 0;
static sys_data_mng_conn_mng_to_uart_msg_t smng_msg_to_uart;

/* Private function prototypes ---------------------------------------- */
/**
 * @brief           Receive and process data from circular buffer
 *
 * @param[in]       none
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
static uint32_t sys_mng_process_data();

/**
 * @brief           Check alarm time
 *
 * @param[in]       none
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
static uint32_t sys_mng_check_alarm();

/**
 * @brief           Get alarm state
 *
 * @param[in]       curr_time   Pointer to current time structure
 * @param[in]       alarm_time  Pointer to alarm time structure
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
static uint32_t sys_mng_get_alarm_state(smng_time_t  *curr_time,
                                        smng_time_t  *alarm_time,
                                        smng_state_t *state);

/* Function definitions ----------------------------------------------- */
uint32_t sys_mng_init()
{
  uint32_t ret;

  ret = cb_init(&smng_cb, smng_cb_buf, SYS_MNG_CBUFFER_SIZE);
  ASSERT(ret == CB_SUCCESS, SYS_MNG_ERROR);

  ret = sys_data_mng_reg_node(SYS_DATA_MNG_CONN_UART_TO_MNG, &smng_cb);
  ASSERT(ret == SYS_COM_SUCCES, SYS_MNG_ERROR);

  return SYS_MNG_SUCCESS;
}

uint32_t sys_mng_loop()
{
    uint32_t ret;
    ret = sys_mng_process_data();
    ASSERT(ret == SYS_MNG_SUCCESS, SYS_MNG_ERROR);
    ret = sys_mng_check_alarm();
    ASSERT(ret == SYS_MNG_SUCCESS, SYS_MNG_ERROR);
    return SYS_MNG_SUCCESS;
}


/* Private definitions ----------------------------------------------- */
static uint32_t sys_mng_process_data()
{
  uint32_t ret;
  uint32_t num_avail;

  num_avail = cb_data_count(&smng_cb);
  if ((num_avail / SYS_MNG_MESSAGE_SIZE)) /*Check if data is available*/
  {
    num_avail = cb_read(&smng_cb, smng_msg_buf, SYS_MNG_MESSAGE_SIZE);
    ASSERT(num_avail == SYS_MNG_MESSAGE_SIZE, SYS_MNG_ERROR);
    smng_msg_evt = smng_msg_buf[SYS_MNG_MESSAGE_EVENT_INDEX];
    switch (smng_msg_evt)
    {
    case SYS_DATA_MNG_CONN_UART_TO_MNG_EVENT_SET_TIME:
    {
      // Get epoch datatype
      uint32_t epoch_value = smng_msg_buf[SYS_MNG_MESSAGE_1ST_DATA_INDEX] << 24 |
      smng_msg_buf[SYS_MNG_MESSAGE_2ND_DATA_INDEX] << 16 |
      smng_msg_buf[SYS_MNG_MESSAGE_3RD_DATA_INDEX] << 8 |
      smng_msg_buf[SYS_MNG_MESSAGE_4TH_DATA_INDEX];
      // Decode epoch datatype, then store in current date and time structure
      epoch_data_t epoch_data;
      epoch_time_decode(epoch_value, &epoch_data);
      smng_curr_date.day   = epoch_data.date.day;
      smng_curr_date.date  = epoch_data.date.date;
      smng_curr_date.month = epoch_data.date.month;
      smng_curr_date.year  = epoch_data.date.year;
      smng_curr_time.hour  = epoch_data.time.hour;
      smng_curr_time.min   = epoch_data.time.min;
      smng_curr_time.sec   = epoch_data.time.sec;
      // Call set time function in BSP layer

      break;
    }
    case SYS_DATA_MNG_CONN_UART_TO_MNG_EVENT_GET_TIME:
    {
      break;
    }
    case SYS_DATA_MNG_CONN_UART_TO_MNG_EVENT_SET_ALARM:
    {
      // Get alarm time from message buffer, then store it into alarm buffer
      smng_alarm_time.hour = smng_msg_buf[SYS_MNG_MESSAGE_HOUR_DATA_INDEX];
      smng_alarm_time.min  = smng_msg_buf[SYS_MNG_MESSAGE_MINUTE_DATA_INDEX];
      smng_alarm_time.sec  = smng_msg_buf[SYS_MNG_MESSAGE_SECOND_DATA_INDEX];
      ret = sys_mng_get_alarm_state(&smng_curr_time, &smng_alarm_time, &smng_state);
      ASSERT(ret == SYS_MNG_SUCCESS, SYS_MNG_ERROR);
      smng_start_tick = HAL_GetTick();
      break;
    }
    default:
      return SYS_MNG_ERROR;
    }
  }
  return SYS_MNG_SUCCESS;
}

static uint32_t sys_mng_check_alarm()
{
  uint32_t ret;
  uint32_t duration = HAL_GetTick() - smng_start_tick;
  switch (smng_state)
  {
  case SYS_MNG_STATE_CHECK_IDLE:
  {
    break;
  }
  case SYS_MNG_STATE_CHECK_HOUR:
  {
    if (duration > SYS_MNG_TICK_HOUR)
    {
      /*Get current time from DS1307 here*/
      ret = sys_mng_get_alarm_state(&smng_curr_time, &smng_alarm_time, &smng_state);
      ASSERT(ret == SYS_MNG_SUCCESS, SYS_MNG_ERROR);
      smng_start_tick = HAL_GetTick();
    }
    break;
  }
  case SYS_MNG_STATE_CHECK_MINUTE:
  {
    if (duration > SYS_MNG_TICK_MINUTE)
    {
      /*Get current time from DS1307 here*/
      ret = sys_mng_get_alarm_state(&smng_curr_time, &smng_alarm_time, &smng_state);
      ASSERT(ret == SYS_MNG_SUCCESS, SYS_MNG_ERROR);
      smng_start_tick = HAL_GetTick();
      if (smng_state == SYS_MNG_STATE_CHECK_SECOND)
      {
        smng_alarm_tick = (60 - smng_curr_time.sec + smng_alarm_time.sec) * 1000;
      }
    }
    break;
  }
  case SYS_MNG_STATE_CHECK_SECOND:
  {
    if (duration >= smng_alarm_tick)
    {
      smng_state = SYS_MNG_STATE_CHECK_ALARM;
    }
    break;
  }
  case SYS_MNG_STATE_CHECK_ALARM:
  {
    smng_state = SYS_MNG_STATE_CHECK_IDLE;
    smng_msg_to_uart.event = SYS_DATA_MNG_CONN_MNG_TO_UART_EVENT_NOTIFY_ALARM;
    sys_data_mng_send(SYS_DATA_MNG_CONN_MNG_TO_UART, (uint8_t*)&smng_msg_to_uart, sizeof(smng_msg_to_uart));
    break;
  }
  }

  return SYS_MNG_SUCCESS;
}

static uint32_t
sys_mng_get_alarm_state(smng_time_t *curr_time, smng_time_t *alarm_time, smng_state_t *state)
{
  ASSERT(curr_time != NULL, SYS_MNG_ERROR);
  ASSERT(alarm_time != NULL, SYS_MNG_ERROR);
  ASSERT(state != NULL, SYS_MNG_ERROR);

  if (alarm_time->hour < curr_time->hour)
  {
    *state = SYS_MNG_STATE_CHECK_HOUR;
  }
  else
  {
    if (alarm_time->hour == curr_time->hour)
    {
      if (alarm_time->min < curr_time->min)
      {
        *state = SYS_MNG_STATE_CHECK_HOUR;
      }
      else
      {
        if (alarm_time->min == curr_time->min)
        {
          if (alarm_time->sec <= curr_time->sec)
          {
            *state = SYS_MNG_STATE_CHECK_HOUR;
          }
          else
          {
            *state = SYS_MNG_STATE_CHECK_SECOND;
          }
        }
        else
        {
          if ((alarm_time->min - curr_time->min) > 1)
          {
            *state = SYS_MNG_STATE_CHECK_MINUTE;
          }
          else
          {
            *state = SYS_MNG_STATE_CHECK_SECOND;
          }
        }
      }
    }
    else
    {
      if ((alarm_time->hour - curr_time->hour) > 1)
      {
        *state = SYS_MNG_STATE_CHECK_HOUR;
      }
      else
      {
        if ((alarm_time->min + (60 - curr_time->min) > 1))
        {
          *state = SYS_MNG_STATE_CHECK_MINUTE;
        }
        else
        {
          *state = SYS_MNG_STATE_CHECK_SECOND;
        }
      }
    }
  }

  return SYS_MNG_SUCCESS;
}

/* End of file -------------------------------------------------------- */
