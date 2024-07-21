/**
 * @file        sys_btn.c
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

/* Includes ----------------------------------------------------------- */
#include "sys_uart.h"
#include "bsp_uart.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */
#define SYS_UART_CBUFFER_SIZE (20) /*Size of circular buffer*/

// Message received from UART
#define SYS_UART_RX_MESSAGE_SIZE       (6) /*Size of data message*/
#define SYS_UART_RX_MESSAGE_TYPE_INDEX (0) /*Index of type in message buffer*/
#define SYS_UART_RX_MESSAGE_LEN_INDEX  (1) /*Index of len in message buffer*/
#define SYS_UART_RX_MESSAGE_1ST_DATA_INDEX \
  (uint8_t)(2) /*Index of first data in message buffer*/
#define SYS_UART_RX_MESSAGE_2ND_DATA_INDEX \
  (uint8_t)(3) /*Index of second data in message buffer*/
#define SYS_UART_RX_MESSAGE_3RD_DATA_INDEX \
  (uint8_t)(4) /*Index of third data in message buffer*/
#define SYS_UART_RX_MESSAGE_4TH_DATA_INDEX \
  (uint8_t)(5) /*Index of fourth data in message buffer*/
#define SYS_UART_RX_MESSAGE_LEN_MAX (4) /*Maximum data len in message buffer*/

// Message received from system manager
#define SYS_UART_MESSAGE_SIZE \
  (7) /*Size of message received from system manager*/
#define SYS_UART_MESSAGE_EVENT_INDEX (0) /*Index of event in message buffer*/
#define SYS_UART_MESSAGE_DATE_INDEX  (1) /*Index of date in message buffer*/
#define SYS_UART_MESSAGE_MONTH_INDEX (2) /*Index of month in message buffer*/
#define SYS_UART_MESSAGE_YEAR_INDEX  (3) /*Index of year in message buffer*/
#define SYS_UART_MESSAGE_HOUR_INDEX  (4) /*Index of hour in message buffer*/
#define SYS_UART_MESSAGE_MIN_INDEX   (5) /*Index of min in message buffer*/
#define SYS_UART_MESSAGE_SEC_INDEX   (6) /*Index of sec in message buffer*/

// Else
#define TYPE_NUM              3
#define SYS_UART_TIMEOUT_TICK 500

/* Private enumerate/structure ---------------------------------------- */
typedef enum
{
  SYS_UART_STATE_WAIT_TYPE,
  SYS_UART_STATE_WAIT_LEN,
  SYS_UART_STATE_WAIT_DATA
} sys_uart_state_t;

typedef uint8_t sys_uart_type_t;
#define UART_TYPE_SET_TIME  ((sys_uart_type_t)0x00)
#define UART_TYPE_GET_TIME  ((sys_uart_type_t)0x01)
#define UART_TYPE_SET_ALARM ((sys_uart_type_t)0x02)

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static bsp_uart_t       suart;
static cbuffer_t        suart_cb;
static uint8_t          suart_cb_buf[SYS_UART_CBUFFER_SIZE];
static sys_uart_state_t suart_state = SYS_UART_STATE_WAIT_TYPE;
static uint8_t          suart_rx_msg_buf[SYS_UART_RX_MESSAGE_SIZE];
static uint8_t          suart_msg_buf[SYS_UART_MESSAGE_SIZE];
static sys_data_mng_conn_uart_to_mng_msg_t suart_msg_to_mng;
static uint32_t                            suart_start_tick = 0;
static uint8_t                             suart_data_count = 0;

/* Private function prototypes ---------------------------------------- */
/**
 * @brief           Receive and process data from uart bsp
 *
 * @param[in]       none
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
static uint32_t sys_uart_process_data_from_uart();

/**
 * @brief           Receive and process data from system manager
 *
 * @param[in]       none
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
static uint32_t sys_uart_process_data_from_sys_mng();

/* Function definitions ----------------------------------------------- */
uint32_t sys_uart_init(UART_HandleTypeDef *huart)
{
  uint32_t ret;

  // Initialize UART
  ret = bsp_uart_init(&suart, huart);
  ASSERT(ret == BSP_UART_SUCCESS, SYS_UART_ERROR);
  // Initialize circular buffer
  ret = cb_init(&suart_cb, suart_cb_buf, SYS_UART_CBUFFER_SIZE);
  ASSERT(ret == CB_SUCCESS, SYS_UART_ERROR);
  // Initialize connection to system mangager
  ret = sys_data_mng_reg_node(SYS_DATA_MNG_CONN_MNG_TO_UART, &suart_cb);
  ASSERT(ret == SYS_COM_SUCCES, SYS_UART_ERROR);

  return SYS_UART_SUCCESS;
}

uint32_t sys_uart_loop()
{
  uint32_t ret;
  ret = sys_uart_process_data_from_uart();
  ASSERT(ret == SYS_UART_SUCCESS, SYS_UART_ERROR);
  ret = sys_uart_process_data_from_sys_mng();
  ASSERT(ret == SYS_UART_SUCCESS, SYS_UART_ERROR);
  return SYS_UART_SUCCESS;
}

void sys_uart_rx_exti_handle(UART_HandleTypeDef *huart)
{
  bsp_uart_rx_exti_handle(&suart, huart);
}

/* Private definitions ----------------------------------------------- */
static uint32_t sys_uart_process_data_from_uart()
{
  uint32_t ret;
  uint8_t  rx_data;
  uint8_t  send_msg_to_mng_flag = 0;
  // Read data from rx buffer
  ret = bsp_uart_receive(&suart, &rx_data, 1);
  ASSERT(ret != BSP_UART_ERROR, SYS_UART_ERROR);
  // Process data
  switch (suart_state)
  {
  case SYS_UART_STATE_WAIT_TYPE:
  {
    if (ret == 1)
    {
      if (rx_data < TYPE_NUM)
      {
        suart_rx_msg_buf[SYS_UART_RX_MESSAGE_TYPE_INDEX] = rx_data;
        suart_state      = SYS_UART_STATE_WAIT_LEN;
        suart_start_tick = HAL_GetTick();
      }
    }
    break;
  }
  case SYS_UART_STATE_WAIT_LEN:
  {
    uint32_t duration = HAL_GetTick() - suart_start_tick;
    if (duration < SYS_UART_TIMEOUT_TICK)
    {
      if (ret == 1)
      {
        if (rx_data <= SYS_UART_RX_MESSAGE_LEN_MAX)
        {
          suart_rx_msg_buf[SYS_UART_RX_MESSAGE_LEN_INDEX] = rx_data;
          suart_state      = SYS_UART_STATE_WAIT_DATA;
          suart_start_tick = HAL_GetTick();
        }
        else
        {
          suart_state = SYS_UART_STATE_WAIT_TYPE;
        }
      }
      else
      {
        suart_state = SYS_UART_STATE_WAIT_LEN;
      }
    }
    else
    {
      suart_state = SYS_UART_STATE_WAIT_TYPE;
    }
    break;
  }
  case SYS_UART_STATE_WAIT_DATA:
  {
    uint32_t duration = HAL_GetTick() - suart_start_tick;
    if (duration < SYS_UART_TIMEOUT_TICK)
    {
      if ((suart_rx_msg_buf[SYS_UART_RX_MESSAGE_LEN_INDEX] == 0) &&
          (suart_rx_msg_buf[SYS_UART_RX_MESSAGE_TYPE_INDEX] == UART_TYPE_GET_TIME))
      {
        suart_state          = SYS_UART_STATE_WAIT_TYPE;
        send_msg_to_mng_flag = 1;
      }
      else
      {
        if (ret == 1)
        {
          suart_rx_msg_buf[SYS_UART_RX_MESSAGE_1ST_DATA_INDEX + suart_data_count] = rx_data;
          suart_data_count++;
          suart_start_tick = HAL_GetTick();
          if (suart_data_count == suart_rx_msg_buf[SYS_UART_RX_MESSAGE_LEN_INDEX])
          {
            suart_data_count     = 0;
            suart_state          = SYS_UART_STATE_WAIT_TYPE;
            send_msg_to_mng_flag = 1;
          }
        }
        else
        {
          suart_state = SYS_UART_STATE_WAIT_DATA;
        }
      }
    }
    else
    {
      suart_data_count = 0;
      suart_state = SYS_UART_STATE_WAIT_TYPE;
    }
    break;
  }
  default:
  {
    suart_state = SYS_UART_STATE_WAIT_TYPE;
    break;
  }
  }
  // Send message to system manger
  if (send_msg_to_mng_flag == 1)
  {
    switch (suart_rx_msg_buf[SYS_UART_RX_MESSAGE_TYPE_INDEX])
    {
    case UART_TYPE_SET_TIME:
    {
      suart_msg_to_mng.event = SYS_DATA_MNG_CONN_UART_TO_MNG_EVENT_SET_TIME;
      suart_msg_to_mng.data.set_time_data.epoch =
      suart_rx_msg_buf[SYS_UART_RX_MESSAGE_1ST_DATA_INDEX] << 24 |
      suart_rx_msg_buf[SYS_UART_RX_MESSAGE_2ND_DATA_INDEX] << 16 |
      suart_rx_msg_buf[SYS_UART_RX_MESSAGE_3RD_DATA_INDEX] << 8 |
      suart_rx_msg_buf[SYS_UART_RX_MESSAGE_4TH_DATA_INDEX];
      ret = sys_data_mng_send(SYS_DATA_MNG_CONN_UART_TO_MNG,
                              (uint8_t *)&suart_msg_to_mng, sizeof(suart_msg_to_mng));
      ASSERT(ret == SYS_COM_SUCCES, SYS_UART_ERROR);
      break;
    }
    case UART_TYPE_GET_TIME:
    {
      suart_msg_to_mng.event = SYS_DATA_MNG_CONN_UART_TO_MNG_EVENT_GET_TIME;
      ret                    = sys_data_mng_send(SYS_DATA_MNG_CONN_UART_TO_MNG,
                                                 (uint8_t *)&suart_msg_to_mng, sizeof(suart_msg_to_mng));
      ASSERT(ret == SYS_COM_SUCCES, SYS_UART_ERROR);
      break;
    }
    case UART_TYPE_SET_ALARM:
    {
      suart_msg_to_mng.event = SYS_DATA_MNG_CONN_UART_TO_MNG_EVENT_SET_ALARM;
      suart_msg_to_mng.data.set_alarm_data.hour =
      suart_rx_msg_buf[SYS_UART_RX_MESSAGE_1ST_DATA_INDEX];
      suart_msg_to_mng.data.set_alarm_data.min =
      suart_rx_msg_buf[SYS_UART_RX_MESSAGE_2ND_DATA_INDEX];
      suart_msg_to_mng.data.set_alarm_data.sec =
      suart_rx_msg_buf[SYS_UART_RX_MESSAGE_3RD_DATA_INDEX];
      ret = sys_data_mng_send(SYS_DATA_MNG_CONN_UART_TO_MNG,
                              (uint8_t *)&suart_msg_to_mng, sizeof(suart_msg_to_mng));
      ASSERT(ret == SYS_COM_SUCCES, SYS_UART_ERROR);
      break;
    }
    default:
      break;
    }
    send_msg_to_mng_flag = 0;
  }

  return SYS_UART_SUCCESS;
}

static uint32_t sys_uart_process_data_from_sys_mng()
{
  uint32_t ret;
  uint32_t num_avail;
  uint8_t  evt;

  num_avail = cb_data_count(&suart_cb);
  if ((num_avail / SYS_UART_MESSAGE_SIZE)) /*Check if data is available*/
  {
    num_avail = cb_read(&suart_cb, suart_msg_buf, SYS_UART_MESSAGE_SIZE);
    ASSERT(num_avail == SYS_UART_MESSAGE_SIZE, SYS_UART_ERROR);
    evt = suart_msg_buf[SYS_UART_MESSAGE_EVENT_INDEX];
    switch (evt)
    {
    case SYS_DATA_MNG_CONN_MNG_TO_UART_EVENT_NOTIFY_ALARM:
    {
      char str[] = "ALARM ALARM ALARM!!!!!!";
      ret        = bsp_uart_transmit(&suart, (uint8_t *)&str, sizeof(str) - 1);
      ASSERT(ret == BSP_UART_SUCCESS, SYS_UART_ERROR);
      break;
    }
    case SYS_DATA_MNG_CONN_MNG_TO_UART_EVENT_RES_GET_TIME:
    {
      char str[35];
      sprintf(str, "%d-%d-%d | %d:%d:%d", suart_msg_buf[SYS_UART_MESSAGE_DATE_INDEX],
              suart_msg_buf[SYS_UART_MESSAGE_MONTH_INDEX],
              suart_msg_buf[SYS_UART_MESSAGE_YEAR_INDEX],
              suart_msg_buf[SYS_UART_MESSAGE_HOUR_INDEX],
              suart_msg_buf[SYS_UART_MESSAGE_MIN_INDEX],
              suart_msg_buf[SYS_UART_MESSAGE_SEC_INDEX]);
      ret = bsp_uart_transmit(&suart, (uint8_t *)&str, sizeof(str) - 1);
      ASSERT(ret == BSP_UART_SUCCESS, SYS_UART_ERROR);
      break;
    }
    case SYS_DATA_MNG_CONN_MNG_TO_UART_EVENT_RES_SET_TIME_ERROR:
    {
      char str[] = "SET TIME FAILED!!!";
      ret        = bsp_uart_transmit(&suart, (uint8_t *)&str, sizeof(str) - 1);
      ASSERT(ret == BSP_UART_SUCCESS, SYS_UART_ERROR);
      break;
      break;
    }
    default:
      break;
    }
  }
  return SYS_UART_SUCCESS;
}
/* End of file -------------------------------------------------------- */
