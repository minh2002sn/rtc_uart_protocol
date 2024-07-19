/**
 * @file        sys_data_mng.c
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

/* Includes ----------------------------------------------------------- */
#include "sys_data_mng.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static cbuffer_t *sdmng_conn_cbuffer[2] = { NULL };

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t sys_data_mng_reg_node(sys_data_mng_conn_t conn, cbuffer_t *cb)
{
  // Assert input
  ASSERT(conn < sizeof(sdmng_conn_cbuffer), SYS_COM_ERROR);
  ASSERT(cb != NULL, SYS_COM_ERROR);

  // Store circular buffer pointer
  sdmng_conn_cbuffer[conn] = cb;

  return SYS_COM_SUCCES;
}

uint32_t sys_data_mng_send(sys_data_mng_conn_t conn, uint8_t *data, uint8_t size)
{
  // Assert input
  ASSERT(conn < sizeof(sdmng_conn_cbuffer), SYS_COM_ERROR);
  ASSERT(data != NULL, SYS_COM_ERROR);
  ASSERT(sdmng_conn_cbuffer[conn] != NULL, SYS_COM_ERROR);

  // Check buffer size
  if (cb_space_count(sdmng_conn_cbuffer[conn]) < size)
  {
    return SYS_COM_ERROR;
  }

  // Write date
  cb_write(sdmng_conn_cbuffer[conn], data, size);
  return SYS_COM_SUCCES;
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
