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
#define SYS_UART_MESSAGE_SIZE (5)  /*Size of data message*/

#define SYS_UART_MESSAGE_EVENT_INDEX     (0) /*Index of event in message buffer*/
#define SYS_UART_MESSAGE_DATE_DATA_INDEX (1) /*Index of date in message buffer*/
#define SYS_UART_MESSAGE_MONTH_DATA_INDEX \
  (2) /*Index of month in message buffer*/
#define SYS_UART_MESSAGE_YEAR_DATA_INDEX (3) /*Index of year in message buffer*/
#define SYS_UART_MESSAGE_HOUR_DATA_INDEX (4) /*Index of hour in message buffer*/
#define SYS_UART_MESSAGE_MINUTE_DATA_INDEX \
  (5) /*Index of minute in message buffer*/
#define SYS_UART_MESSAGE_SECOND_DATA_INDEX \
  (6) /*Index of second in message buffer*/

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static bsp_uart_t suart;
static cbuffer_t  suart_cb;
static uint8_t    suart_cb_buf[SYS_UART_CBUFFER_SIZE];

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
  uint8_t  rx_data;

  // Read data from rx buffer
  ret = bsp_uart_receive(&suart, &rx_data, 1);
  ASSERT(ret == BSP_UART_SUCCESS, SYS_UART_ERROR);

  // Process data

  return SYS_UART_SUCCESS;
}

void sys_uart_rx_exti_handle(UART_HandleTypeDef *huart)
{
  bsp_uart_rx_exti_handle(&suart, huart);
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
