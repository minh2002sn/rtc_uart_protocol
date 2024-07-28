/**
 * @file        sys_adc_uart.c
 * @copyright
 * @license
 * @version     0.0.0
 * @date
 * @author      Minh Phung Nhat
 *              Hung Pham Duc
 *              Khoi Nguyen Thanh
 * @brief       Implementation of system ADC and UART integration
 *
 * @note        none
 *
 * @example     none
 *
 */

/* Includes ----------------------------------------------------------- */
#include "sys_adc2uart.h"
#include "bsp_adc.h"
#include "bsp_uart.h"
#include "common.h"

/* Private variables ------------------------------------------------- */
static bsp_uart_t uart;
static bsp_adc_t  adc;

/* Function definitions ----------------------------------------------- */
uint32_t sys_adc_uart_init(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc)
{
  uint32_t ret;

  // Assert input
  ASSERT(huart != NULL, SYS_ADC_UART_ERROR);
  ASSERT(hadc != NULL, SYS_ADC_UART_ERROR);

  // Initialize UART
  ret = bsp_uart_init(&uart, huart);
  ASSERT(ret == BSP_UART_SUCCESS, SYS_ADC_UART_ERROR);

  // Initialize ADC
  ret = bsp_adc_init(&adc, hadc);
  ASSERT(ret == BSP_ADC_SUCCESS, SYS_ADC_UART_ERROR);

  return SYS_ADC_UART_SUCCESS;
}

uint32_t sys_adc_uart_loop()
{
  uint8_t  buff[20];
  uint32_t ret;
  uint32_t adc_value;

  // Start ADC conversion
  ret = bsp_adc_start_conversion(&adc);
  if (ret != BSP_ADC_SUCCESS)
  {
    return SYS_ADC_UART_ERROR;
  }

  // Wait for ADC conversion to complete
  while (!bsp_adc_conversion_done(&adc))
  {
    // Do nothing, just wait
  }

  // Read ADC value
  ret = bsp_adc_read(&adc, &adc_value);
  if (ret == BSP_ADC_SUCCESS)
  {
    // Format ADC value as string
    snprintf((char *)buff, sizeof(buff), "%lu\r\n", adc_value);

    // Transmit ADC value via UART
    ret = bsp_uart_transmit(&uart, buff, strlen((char *)buff));
    if (ret != BSP_UART_SUCCESS)
    {
      return SYS_ADC_UART_ERROR;
    }
  }
  else
  {
    return SYS_ADC_UART_ERROR;
  }

  return SYS_ADC_UART_SUCCESS;
}

void sys_adc_conversion_complete_handle(ADC_HandleTypeDef *hadc)
{
  if (adc.hadc == hadc)
  {
    // Handle ADC conversion complete
    sys_adc_uart_loop();
  }
}

/* End of file -------------------------------------------------------- */
