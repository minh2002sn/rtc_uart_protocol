/**
 * @file        sys_uart.h
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
#ifndef __SYS_UART_H
#define __SYS_UART_H

/* Includes ----------------------------------------------------------- */
#include "main.h"
#include <stdint.h>


/* Public defines ----------------------------------------------------- */
#define SYS_UART_SUCCESS (0x00000000)
#define SYS_UART_ERROR   (0xFFFFFFFF)

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief           Initialize system button
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_uart_init(UART_HandleTypeDef *huart);

/**
 * @brief           System button loop() function
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_uart_loop();

/**
 * @brief         Receive complete interrupt handling function
 *
 * @param[in]     huart         Pointer to UART_HandleTypeDef structure
 *
 * @return        none
 *
 */
void sys_uart_rx_exti_handle(UART_HandleTypeDef *huart);

#endif // __SYS_UART_H

/* End of file -------------------------------------------------------- */
