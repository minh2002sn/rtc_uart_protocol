/**
 * @file       bsp_adc.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.0.0
 * @date       yyyy-mm-dd
 * @author     <first_name_1> <last_name_1>
 * @author     <first_name_2> <last_name_2>
 * @author     <first_name_3> <last_name_3>
 *
 * @brief      ADC (Analog-to-Digital Converter) driver for STM32
 *
 * @note
 *
 * @example    example_file_1.c
 *             Example_1 description
 *
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_adc.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */
static bsp_adc_t *g_badc = NULL;

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t bsp_adc_init(bsp_adc_t *badc, ADC_HandleTypeDef *hadc)
{
  uint32_t ret;

  // Assert input
  ASSERT(badc != NULL, BSP_ADC_ERROR);
  ASSERT(hadc != NULL, BSP_ADC_ERROR);

  // Store hadc
  badc->hadc = hadc;
  g_badc = badc;  // Lưu trữ con trỏ toàn cục

  // Init circular buffer
  ret = cb_init(&badc->rx_cb, badc->buff, sizeof(badc->buff));
  ASSERT(ret == CB_SUCCESS, BSP_ADC_ERROR);

  // Start ADC conversion in interrupt mode
  HAL_ADC_Start_IT(badc->hadc);

  return BSP_ADC_SUCCESS;
}

uint32_t bsp_adc_start_conversion(bsp_adc_t *badc)
{
  // Assert input
  ASSERT(badc != NULL, BSP_ADC_ERROR);

  // Start ADC conversion
  if (HAL_ADC_Start(badc->hadc) != HAL_OK)
  {
    return BSP_ADC_ERROR;
  }

  return BSP_ADC_SUCCESS;
}

uint32_t bsp_adc_read(bsp_adc_t *badc, uint32_t *value)
{
  // Assert input
  ASSERT(badc != NULL, BSP_ADC_ERROR);
  ASSERT(value != NULL, BSP_ADC_ERROR);

  // Read data from circular buffer
  if (cb_read(&badc->rx_cb, (uint8_t *)value, sizeof(*value)) != CB_SUCCESS)
  {
    return BSP_ADC_ERROR;
  }

  return BSP_ADC_SUCCESS;
}

uint32_t bsp_adc_conversion_done(bsp_adc_t *badc)
{
  // Assert input
  ASSERT(badc != NULL, BSP_ADC_ERROR);

  // Check if ADC conversion is done
  return cb_data_count(&badc->rx_cb);
}

void bsp_adc_exti_handle(bsp_adc_t *badc, ADC_HandleTypeDef *hadc)
{
  // Assert input
  ASSERT(badc != NULL, BSP_ADC_ERROR);
  ASSERT(hadc != NULL, BSP_ADC_ERROR);

  if (badc->hadc == hadc)
  {
    // Read ADC value
    uint32_t adc_value = HAL_ADC_GetValue(badc->hadc);

    // Write ADC value to circular buffer
    cb_write(&badc->rx_cb, (uint8_t *)&adc_value, sizeof(adc_value));

    // Start the next ADC conversion
    HAL_ADC_Start_IT(badc->hadc);
  }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	  bsp_adc_exti_handle(g_badc, hadc);
	  sys_adc_conversion_complete_handle(hadc);
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
