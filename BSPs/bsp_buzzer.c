/**
 * @file       bsp_buzzer.c
 * @copyright  Copyright (C) 2024 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.0.0
 * @date       yyyy-mm-dd
 * @author     <first_name_1> <last_name_1>
 * @author     <first_name_2> <last_name_2>
 * @author     <first_name_3> <last_name_3>
 *
 * @brief      Source file for Buzzer functionality.
 *
 * @note
 *
 * @example    example_file_1.c
 *             Example_1 description
 *
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_buzzer.h"

/* Private defines ---------------------------------------------------- */
#define BSP_BUZZER_SOUND    0
#define BSP_BUZZER_NO_SOUND 1

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t bsp_buzzer_init(bsp_buzzer_t *buzzer, GPIO_TypeDef *port, uint16_t pin)
{
  ASSERT(buzzer != NULL, BSP_BUZZER_ERROR);
  ASSERT(port != NULL, BSP_BUZZER_ERROR);

  buzzer->port = port;
  buzzer->pin  = pin;

  // /* Ensure the buzzer is off initially */
  HAL_GPIO_WritePin(port, pin, BSP_BUZZER_NO_SOUND);

  return BSP_BUZZER_SUCCESS;
}

void bsp_buzzer_on(bsp_buzzer_t *buzzer)
{
  ASSERT(buzzer != NULL, BSP_BUZZER_ERROR);
  HAL_GPIO_WritePin(buzzer->port, buzzer->pin, BSP_BUZZER_SOUND);
}

void bsp_buzzer_off(bsp_buzzer_t *buzzer)
{
  ASSERT(buzzer != NULL, BSP_BUZZER_ERROR);
  HAL_GPIO_WritePin(buzzer->port, buzzer->pin, BSP_BUZZER_NO_SOUND);
}

void bsp_buzzer_toggle(bsp_buzzer_t *buzzer)
{
  ASSERT(buzzer != NULL, BSP_BUZZER_ERROR);
  HAL_GPIO_TogglePin(buzzer->port, buzzer->pin);
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
