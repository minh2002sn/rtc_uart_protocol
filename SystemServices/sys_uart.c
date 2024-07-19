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

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static bsp_uart_t suart;

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t sys_uart_init(UART_HandleTypeDef *huart)
{
  uint32_t ret;

  // Init uart button
  ret = bsp_uart_init(&suart, huart);
  ASSERT(ret == BSP_UART_SUCCESS, SYS_UART_ERROR);

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
