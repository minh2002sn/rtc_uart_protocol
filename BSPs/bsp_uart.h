/**
 * @file       bsp_uart.h
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

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_UART_H
#define __BSP_UART_H

/* Includes ----------------------------------------------------------- */
#include "cbuffer.h"
#include "main.h"

/* Public defines ----------------------------------------------------- */
#define BSP_UART_ERROR         0xFFFFFFFF
#define BSP_UART_SUCCESS       0x00000000
#define BSP_UART_DATA_AVAIL    0x00000001
#define BSP_UART_NO_DATA_AVAIL 0x00000000

#define BSP_UART_RX_BUFF_SIZE 255

/* Public enumerate/structure ----------------------------------------- */
typedef struct
{
  UART_HandleTypeDef *huart;
  uint8_t             rx_byte;
  cbuffer_t           rx_cb;
  uint8_t             buff[BSP_UART_RX_BUFF_SIZE];
} bsp_uart_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         Init UART
 *
 * @param[in]     buart         Pointer to bsp_uart_t structure
 * @param[in]     huart         Pointer to UART_HandleTypeDef structure
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t bsp_uart_init(bsp_uart_t *buart, UART_HandleTypeDef *huart);

/**
 * @brief         Transmit UART
 *
 * @param[in]     buart         Pointer to bsp_uart_t structure
 * @param[in]     buf           Pointer to data buffer
 * @param[in]     size          Size of data buffer
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t bsp_uart_transmit(bsp_uart_t *buart, uint8_t *buff, uint32_t size);

/**
 * @brief         Receive UART
 *
 * @param[in]     buart         Pointer to bsp_uart_t structure
 * @param[out]    buf           Pointer to data buffer
 * @param[in]     size          Size of data buffer
 *
 * @return
 *  - (-1): Error
 *  - Number of Received bytes, maximum value is BSP_UART_RX_BUFF_SIZE = 32
 */
uint32_t bsp_uart_receive(bsp_uart_t *buart, uint8_t *buff, uint32_t size);

/**
 * @brief         Check whether data is available in buffer
 *
 * @param[in]     buart         Pointer to bsp_uart_t structure
 *
 * @return
 *  - (1): Data is available in buffer
 *  - (0): Data is not available in buffer
 */
uint32_t bsp_uart_data_avail(bsp_uart_t *buart);

/**
 * @brief         Receive complete interrupt handling function
 *
 * @param[in]     buart         Pointer to bsp_uart_t structure
 * @param[in]     huart         Pointer to UART_HandleTypeDef structure
 *
 * @return        Number of bytes in buffer
 *
 */
void bsp_uart_rx_exti_handle(bsp_uart_t *buart, UART_HandleTypeDef *huart);

#endif // __BSP_UART_H

/* End of file -------------------------------------------------------- */
