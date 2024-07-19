/**
 * @file       bsp_uart.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.0.0
 * @date       yyyy-mm-dd
 * @author     <first_name_1> <last_name_1>
 * @author     <first_name_2> <last_name_2>
 * @author     <first_name_3> <last_name_3>
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 *
 * @example    example_file_1.c
 *             Example_1 description
 *
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_uart.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t bsp_uart_init(bsp_uart_t *buart, UART_HandleTypeDef *huart)
{
  uint32_t ret;
  // Assert input
  ASSERT(buart != NULL, BSP_UART_ERROR);
  ASSERT(huart != NULL, BSP_UART_ERROR);

  // Store huart
  buart->huart = huart;

  // Init circular buffer
  ret = cb_init(&buart->rx_cb, buart->buff, sizeof(buart->buff));
  ASSERT(ret == CB_SUCCESS, BSP_UART_ERROR);

  // Start UART receiveing in interrupt mode
  HAL_UART_Receive_IT(buart->huart, &buart->rx_byte, sizeof(buart->rx_byte));
//  HAL_UARTEx_ReceiveToIdle_IT(buart->huart, &buart->rx_byte, 1);

  return BSP_UART_SUCCESS;
}

uint32_t bsp_uart_transmit(bsp_uart_t *buart, uint8_t *buff, uint32_t size)
{
  HAL_StatusTypeDef ret;

  // Assert input
  ASSERT(buart != NULL, BSP_UART_ERROR);
  ASSERT(buff != NULL, BSP_UART_ERROR);
  ASSERT(size <= BSP_UART_RX_BUFF_SIZE, BSP_UART_ERROR);

  // Transmit UART
  ret = HAL_UART_Transmit(buart->huart, buff, size, 0xFFFFFFFF);
  ASSERT(ret == HAL_OK, BSP_UART_ERROR);

  return BSP_UART_SUCCESS;
}

uint32_t bsp_uart_receive(bsp_uart_t *buart, uint8_t *buff, uint32_t size)
{
  uint32_t ret;

  // Assert input
  ASSERT(buart != NULL, BSP_UART_ERROR);
  ASSERT(buff != NULL, BSP_UART_ERROR);
  ASSERT(size <= BSP_UART_RX_BUFF_SIZE, BSP_UART_ERROR);

  // Read data from circular buffer
  ret = cb_read(&buart->rx_cb, buff, size);

  return ret;
}

uint32_t bsp_uart_data_avail(bsp_uart_t *buart)
{
  // Assert input
  ASSERT(buart != NULL, BSP_UART_ERROR);

  return cb_data_count(&buart->rx_cb);
}

void bsp_uart_rx_exti_handle(bsp_uart_t *buart, UART_HandleTypeDef *huart)
{
  if (buart->huart == huart)
  {
    cb_write(&buart->rx_cb, &buart->rx_byte, 1);
    HAL_UART_Receive_IT(buart->huart, &buart->rx_byte, sizeof(buart->rx_byte));
//    HAL_UARTEx_ReceiveToIdle_IT(buart->huart, &buart->rx_byte, 1);
  }
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
