/**
 * @file       bsp_adc.h
 * @copyright  Copyright (C) 2024 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.0.0
 * @date       yyyy-mm-dd
 * @author     <first_name_1> <last_name_1>
 * @author     <first_name_2> <last_name_2>
 * @author     <first_name_3> <last_name_3>
 *
 * @brief      Header file for ADC (Analog-to-Digital Converter) functionality.
 *
 * @note
 *
 * @example    example_file_1.c
 *             Example_1 description
 *
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_ADC_H
#define __BSP_ADC_H

/* Includes ----------------------------------------------------------- */
#include "cbuffer.h"
#include "main.h"

/* Public defines ----------------------------------------------------- */
#define BSP_ADC_ERROR       0xFFFFFFFF
#define BSP_ADC_SUCCESS     0x00000000
#define BSP_ADC_BUFFER_SIZE 256

/* Public enumerate/structure ----------------------------------------- */
typedef struct
{
  ADC_HandleTypeDef *hadc;
  uint8_t            buff[BSP_ADC_BUFFER_SIZE];
  cbuffer_t          rx_cb;
} bsp_adc_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         Initialize ADC
 *
 * @param[in]     badc         Pointer to bsp_adc_t structure
 * @param[in]     hadc         Pointer to ADC_HandleTypeDef structure
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t bsp_adc_init(bsp_adc_t *badc, ADC_HandleTypeDef *hadc);

/**
 * @brief         Start ADC conversion
 *
 * @param[in]     badc         Pointer to bsp_adc_t structure
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t bsp_adc_start_conversion(bsp_adc_t *badc);

/**
 * @brief         Read ADC value
 *
 * @param[in]     badc         Pointer to bsp_adc_t structure
 * @param[out]    value        Pointer to store the ADC value
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t bsp_adc_read(bsp_adc_t *badc, uint32_t *value);

/**
 * @brief         Check if ADC conversion is done
 *
 * @param[in]     badc         Pointer to bsp_adc_t structure
 *
 * @return
 *  - (1) : Conversion is done
 *  - (0) : Conversion is not done
 */
uint32_t bsp_adc_conversion_done(bsp_adc_t *badc);

/**
 * @brief         ADC interrupt handling function
 *
 * @param[in]     badc         Pointer to bsp_adc_t structure
 * @param[in]     hadc         Pointer to ADC_HandleTypeDef structure
 *
 * @return        None
 *
 */
void bsp_adc_irq_handler(bsp_adc_t *badc, ADC_HandleTypeDef *hadc);

#endif // __BSP_ADC_H

/* End of file -------------------------------------------------------- */
