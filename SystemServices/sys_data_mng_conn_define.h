/**
 * @file        sys_data_mng_conn_define.h
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
#ifndef __SYS_DATA_MNG_CONN_DEFINE_H
#define __SYS_DATA_MNG_CONN_DEFINE_H

/* Includes ----------------------------------------------------------- */
#include <stdint.h>

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
// Type define enum sys_btn_id_t that has sizeof() = 1
typedef uint8_t sys_data_mng_conn_t;
#define SYS_DATA_MNG_CONN_UART_TO_MNG ((sys_data_mng_conn_t)0x00)
#define SYS_DATA_MNG_CONN_MNG_TO_UART ((sys_data_mng_conn_t)0x01)

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

#endif // __SYS_DATA_MNG_CONN_DEFINE_H

/* End of file -------------------------------------------------------- */
