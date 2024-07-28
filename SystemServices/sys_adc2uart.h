/**
 * @file        sys_adc2uart.h
 * @copyright
 * @license
 * @version     0.0.0
 * @date
 * @author      Minh Phung Nhat
 *              Hung Pham Duc
 *              Khoi Nguyen Thanh
 * @brief       Header file for ADC and UART system integration
 *
 * @note        none
 *
 * @example     none
 *
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SYS_ADC2UART_H
#define __SYS_ADC2UART_H

/* Includes ----------------------------------------------------------- */
#include "bsp_adc.h"
#include "bsp_uart.h"
#include "main.h"


/* Public defines ----------------------------------------------------- */
#define SYS_ADC_UART_SUCCESS (0x00000000)
#define SYS_ADC_UART_ERROR   (0xFFFFFFFF)

/* Public function prototypes ----------------------------------------- */

/**
 * @brief           Initialize system ADC and UART
 *
 * @param[in]       huart         Pointer to UART_HandleTypeDef structure
 * @param[in]       hadc          Pointer to ADC_HandleTypeDef structure
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_adc_uart_init(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc);

/**
 * @brief           System ADC and UART loop() function
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_adc_uart_loop();

/**
 * @brief         ADC conversion complete interrupt handling function
 *
 * @param[in]     hadc         Pointer to ADC_HandleTypeDef structure
 *
 * @return        none
 */
void sys_adc_conversion_complete_handle(ADC_HandleTypeDef *hadc);

#endif // __SYS_ADC2UART_H

/* End of file -------------------------------------------------------- */
