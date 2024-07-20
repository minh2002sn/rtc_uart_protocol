/**
 * @file        sys_mng.c
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
#include "sys_mng.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */
#define SYS_MNG_CBUFFER_SIZE (20) /*Size of circular buffer*/

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
static cbuffer_t smng_cb;
static uint8_t   smng_cb_buf[SYS_MNG_CBUFFER_SIZE] = { 0 };

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t sys_mng_init()
{
  uint32_t ret;

  ret = cb_init(&smng_cb, smng_cb_buf, SYS_MNG_CBUFFER_SIZE);
  ASSERT(ret == CB_SUCCESS, SYS_MNG_ERROR);

  ret = sys_data_mng_reg_node(SYS_DATA_MNG_CONN_UART_TO_MNG, &smng_cb_buf);
  ASSERT(ret == SYS_COM_SUCCES, SYS_MNG_ERROR);

  return SYS_MNG_SUCCESS;
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
