/**
 * @file        sys_data_mng.h
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
#ifndef __SYS_COM_
#define __SYS_COM_

/* Includes ----------------------------------------------------------- */
#include "cbuffer.h"
#include "sys_data_mng_conn_define.h"
#include <stdint.h>


/* Public defines ----------------------------------------------------- */
#define SYS_COM_SUCCES    (0x00000000)
#define SYS_COM_ERROR     (0xFFFFFFFF)
#define SYS_COM_BUFF_FULL (0xFFFFFFFE) /* Buffer is full*/

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief           Register circular buffer receive data from node
 *
 * @param[in]       conn    System data manager connection
 * @param[in]       cb      Pointer to a cbuffer_t structure
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_data_mng_reg_node(sys_data_mng_conn_t conn, cbuffer_t *cb);

/**
 * @brief           System manager loop() function
 *
 * @param[in]       conn    System data manager connection
 * @param[out]      data    Pointer to data buffer
 * @param[in]       size    Size of data buffer
 *
 *
 */
uint32_t sys_data_mng_send(sys_data_mng_conn_t conn, uint8_t *data, uint8_t size);

#endif // __SYS_MNG_

/* End of file -------------------------------------------------------- */
