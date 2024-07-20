/**
 * @file        sys_mng.h
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
#ifndef __SYS_MNG_
#define __SYS_MNG_

/* Includes ----------------------------------------------------------- */
#include <stdint.h>
#include "cbuffer.h"
#include "common.h"
#include "sys_data_mng.h"
#include "bsp_ds1307.h"
#include "drv_ds1307.h"
#include "sys_data_mng_msg_define.h"
#include "sys_data_mng_conn_define.h"

/* Public defines ----------------------------------------------------- */
#define SYS_MNG_SUCCESS (0x00000000)
#define SYS_MNG_ERROR   (0xFFFFFFFF)
#define SYS_MNG_BUFFULL (0xFFFFFFFE) /* Buffer full */

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief           Initialize system manager
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_mng_init();

/**
 * @brief           System manager loop() function
 */
uint32_t sys_mng_loop();

#endif // __SYS_MNG_

/* End of file -------------------------------------------------------- */
