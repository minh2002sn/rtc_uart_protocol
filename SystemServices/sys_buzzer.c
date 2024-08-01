/**
 * @file        sys_buzzer.c
 * @copyright
 * @license
 * @version     0.0.0
 * @date
 * @author      Minh Phung Nhat
 *              Hung Pham Duc
 *              Khoi Nguyen Thanh
 * @brief       Source file for Buzzer system integration
 *
 * @note        none
 *
 * @example     none
 *
 */

/* Includes ----------------------------------------------------------- */
#include "sys_buzzer.h"
#include "stm32f4xx_hal.h"

/* Private defines ---------------------------------------------------- */
static TIM_HandleTypeDef *buzzer_htim;
static GPIO_TypeDef      *buzzer_port;
static uint16_t           buzzer_pin;

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */
static void play_melody(TIM_HandleTypeDef *htim);

/* Function definitions ----------------------------------------------- */

uint32_t sys_buzzer_init(TIM_HandleTypeDef *htim, GPIO_TypeDef *port, uint16_t pin)
{
  if (htim == NULL || port == NULL)
  {
    return SYS_BUZZER_ERROR;
  }

  buzzer_htim = htim;
  buzzer_port = port;
  buzzer_pin  = pin;

  // HAL_GPIO_WritePin(buzzer_port, buzzer_pin, GPIO_PIN_SET); // Set pin to high state by default
  HAL_TIM_PWM_Start(buzzer_htim, TIM_CHANNEL_1);
  __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, 5000); // Turn off the buzzer
  return SYS_BUZZER_SUCCESS;
}

void sys_buzzer_alarm(TIM_HandleTypeDef *htim)
{
  play_melody(htim);
}

/* Private function definitions --------------------------------------- */

static void play_melody(TIM_HandleTypeDef *htim)
{
  uint32_t current_time;

  for (int i = 0; i < MELODY_LENGTH; i++)
  {
    if (melody_notes[i] > 0)
    {
      __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, melody_notes[i]);
      current_time = HAL_GetTick();
      while ((HAL_GetTick() - current_time) < ((1000 / melody_durations[i]) * 2))
      {
        // Delay time
      }
    }
    else
    {
      __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, 5000);
      current_time = HAL_GetTick();
      while ((HAL_GetTick() - current_time) < ((1000 / melody_durations[i]) * 2))
      {
        // Delay time
      }
    }
  }

  __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, 5000); // Turn off the buzzer
}

/* End of file -------------------------------------------------------- */
