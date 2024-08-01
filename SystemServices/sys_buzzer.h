/**
 * @file        sys_buzzer.h
 * @copyright
 * @license
 * @version     0.0.0
 * @date
 * @author      Minh Phung Nhat
 *              Hung Pham Duc
 *              Khoi Nguyen Thanh
 * @brief       Header file for Buzzer system integration
 *
 * @note        none
 *
 * @example     none
 *
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SYS_BUZZER_H
#define __SYS_BUZZER_H

/* Includes ----------------------------------------------------------- */
#include "bsp_buzzer.h"
#include "bsp_buzzer_melody.h"
#include "main.h"

/* Public defines ----------------------------------------------------- */
#define SYS_BUZZER_SUCCESS (0x00000000)
#define SYS_BUZZER_ERROR   (0xFFFFFFFF)

/* Public function prototypes ----------------------------------------- */

/**
 * @brief           Initialize the buzzer system
 *
 * @param[in]       htim          Pointer to TIM handle for PWM
 * @param[in]       port          Pointer to GPIO port for the buzzer
 * @param[in]       pin           GPIO pin for the buzzer
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_buzzer_init(TIM_HandleTypeDef *htim, GPIO_TypeDef *port, uint16_t pin);

/**
 * @brief           Control the buzzer alarm state
 *
 * @param[in]       htim          Pointer to TIM handle for PWM
 *
 * @return          None
 */
void sys_buzzer_alarm(TIM_HandleTypeDef *htim);

#endif // __SYS_ADC2UART_H

/* End of file -------------------------------------------------------- */
