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
  IDLE,
  SYS_MNG_STATE_CHECK_HOUR,
  SYS_MNG_STATE_CHECK_MINUTE,
  SYS_MNG_STATE_CHECK_SECOND
} smng_state_t

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static cbuffer_t    smng_cb;
static uint8_t      smng_cb_buf[SYS_MNG_CBUFFER_SIZE]  = { 0 };
static uint8_t      smng_msg_buf[SYS_MNG_MESSAGE_SIZE] = { 0 };
static uint8_t      smng_msg_evt                       = 0;
static uint32_t     smng_msg_data                      = 0;
static smng_time_t  smng_curr_time;
static smng_date_t  smng_curr_date;
static smng_time_t  smng_alarm_time;
static uint8_t      smng_is_rtc_alarm = 0;
static uint32_t     smng_start_tick   = 0;
static smng_state_t smng_state        = IDLE;

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

/* Function definitions ----------------------------------------------- */
uint32_t sys_mng_init()
{
  uint32_t ret;

  ret = cb_init(&smng_cb, smng_cb_buf, SYS_MNG_CBUFFER_SIZE);
  ASSERT(ret == CB_SUCCESS, SYS_MNG_ERROR);

  ret = sys_data_mng_reg_node(SYS_DATA_MNG_CONN_UART_TO_MNG, &smng_cb_buf);
  ASSERT(ret == SYS_COM_SUCCES, SYS_MNG_ERROR);

  return SYS_MNG_SUCCESS;
}

uint32_t sys_mng_loop()
{
}


/* Private definitions ----------------------------------------------- */
static uint32_t sys_mng_process_data()
{
  uint32_t ret;
  uint32_t num_avail;

  num_avail = cb_data_count(&smng_cb);
  if ((num_vail / SYS_MNG_MESSAGE_EVENT_INDEX)) /*Check if data is available*/
  {
    num_avail = cb_read(&smng_cb, smng_msg_buf, SYS_MNG_MESSAGE_SIZE);
    ASSERT(num_vail == SYS_MNG_MESSAGE_SIZE, SYS_MNG_ERROR);
    smng_msg_evt = smng_msg_buf[SYS_MNG_MESSAGE_EVENT_INDEX];
    switch (smng_msg_evt)
    {
    case SYS_DATA_MNG_CONN_UART_TO_MNG_EVENT_SET_TIME:
    {
      // Get epoch datatype
      uint32_t epoch_value = smng_msg_buf[SYS_MNGS_MESSAGE_1ST_DATA_INDEX] << 24 |
      smng_msg_buf[SYS_MNGS_MESSAGE_2ND_DATA_INDEX] << 16 |
      smng_msg_buf[SYS_MNGS_MESSAGE_3RD_DATA_INDEX] << 8 |
      smng_msg_buf[SYS_MNGS_MESSAGE_4TH_DATA_INDEX];
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
      smng_is_rtc_alarm    = 1;
      smng_start_tick      = HAL_GetTick();
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
  if (smng_is_rtc_alarm)
  {
  }
  return SYS_COM_SUCCES;
}
/* End of file -------------------------------------------------------- */
