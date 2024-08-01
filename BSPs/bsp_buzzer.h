/**
 * @file       bsp_buzzer.h
 * @copyright  Copyright (C) 2024 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.0.0
 * @date       yyyy-mm-dd
 * @author     <first_name_1> <last_name_1>
 * @author     <first_name_2> <last_name_2>
 * @author     <first_name_3> <last_name_3>
 *
 * @brief      Header file for Buzzer functionality.
 *
 * @note
 *
 * @example    example_file_1.c
 *             Example_1 description
 *
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_BUZZER_H
#define __BSP_BUZZER_H

/* Includes ----------------------------------------------------------- */
#include "common.h"
#include "main.h"

/* Public defines ----------------------------------------------------- */
#define BSP_BUZZER_ERROR   0xFFFFFFFF
#define BSP_BUZZER_SUCCESS 0x00000000

/* Public enumerate/structure ----------------------------------------- */
typedef struct
{
  GPIO_TypeDef *port;
  uint16_t      pin;
} bsp_buzzer_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         Initialize the Buzzer
 *
 * @param[in]     buzzer       Pointer to bsp_buzzer_t structure
 * @param[in]     port         GPIO port where buzzer is connected
 * @param[in]     pin          GPIO pin where buzzer is connected
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t bsp_buzzer_init(bsp_buzzer_t *buzzer, GPIO_TypeDef *port, uint16_t pin);

/**
 * @brief         Turn on the Buzzer
 *
 * @param[in]     buzzer       Pointer to bsp_buzzer_t structure
 *
 * @return        None
 */
void bsp_buzzer_on(bsp_buzzer_t *buzzer);

/**
 * @brief         Turn off the Buzzer
 *
 * @param[in]     buzzer       Pointer to bsp_buzzer_t structure
 *
 * @return        None
 */
void bsp_buzzer_off(bsp_buzzer_t *buzzer);

/**
 * @brief         Toggle the Buzzer
 *
 * @param[in]     buzzer       Pointer to bsp_buzzer_t structure
 *
 * @return        None
 */
void bsp_buzzer_toggle(bsp_buzzer_t *buzzer);

#endif // __BSP_BUZZER_H

/* End of file -------------------------------------------------------- */
