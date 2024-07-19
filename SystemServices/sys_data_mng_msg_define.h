/**
 * @file        sys_data_mng_msg_define.h
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
#ifndef __SYS_DATA_MNG_MSG_DEFINE_H
#define __SYS_DATA_MNG_MSG_DEFINE_H

/* Includes ----------------------------------------------------------- */
#include "sys_data_mng_conn_define.h"
#include <stdint.h>


/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
typedef uint8_t sys_data_mng_conn_uart_to_mng_event_t;
#define SYS_DATA_MNG_CONN_UART_TO_MNG_EVENT_SET_TIME \
  ((sys_data_mng_conn_uart_to_mng_event_t)0x00)
#define SYS_DATA_MNG_CONN_UART_TO_MNG_EVENT_GET_TIME \
  ((sys_data_mng_conn_uart_to_mng_event_t)0x01)
#define SYS_DATA_MNG_CONN_UART_TO_MNG_EVENT_SET_ALARM \
  ((sys_data_mng_conn_uart_to_mng_event_t)0x02)

typedef struct __attribute__((packed))
{
  sys_data_mng_conn_uart_to_mng_event_t event;
  union
  {
    struct
    {
      uint32_t epoch;
    } set_time_data;

    struct
    {
      uint32_t padding;
    } get_time_data;

    struct
    {
      uint8_t hour;
      uint8_t min;
      uint8_t sec;
      uint8_t padding;
    } set_alarm_data;
  } data;
} sys_data_mng_conn_uart_to_mng_msg_t;

typedef uint8_t sys_data_mng_conn_mng_to_uart_event_t;
#define SYS_DATA_MNG_CONN_MNG_TO_UART_EVENT_NOTIFY_ALARM \
  ((sys_data_mng_conn_mng_to_uart_event_t)0x00)
#define SYS_DATA_MNG_CONN_MNG_TO_UART_EVENT_RES_GET_TIME \
  ((sys_data_mng_conn_mng_to_uart_event_t)0x01)
#define SYS_DATA_MNG_CONN_MNG_TO_UART_EVENT_RES_SET_TIME_ERROR \
  ((sys_data_mng_conn_mng_to_uart_event_t)0x02)

typedef struct __attribute__((packed))
{
  sys_data_mng_conn_mng_to_uart_event_t event;
  union
  {
    struct
    {
      uint8_t padding[6];
    } notify_alarm_data;

    struct
    {
      uint8_t date;
      uint8_t month;
      uint8_t year;
      uint8_t hour;
      uint8_t min;
      uint8_t sec;
    } res_get_time_data;

    struct
    {
      uint8_t padding[6];
    } res_set_time_error_data;
  } data;
} sys_data_mng_conn_mng_to_uart_msg_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

#endif // __SYS_DATA_MNG_MSG_DEFINE_H

/* End of file -------------------------------------------------------- */
