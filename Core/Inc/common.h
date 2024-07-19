/**
 * @file        common.h
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
#ifndef __COMMON_
#define __COMMON_

/* Includes ----------------------------------------------------------- */
#include "main.h"

/* Public defines ----------------------------------------------------- */
#define UART_DEBUG_ENABLE  1 /* Enable UART debug */

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */
// Assert input parameter
#define ASSERT(_expr_, _rc_) \
  do                         \
  {                          \
    if (!(_expr_))           \
      return (_rc_);         \
  } while (0)

// Check callback function and call that function
#define CALLBACK(_cb_func_, ...) \
  do                             \
  {                              \
    if (((_cb_func_) != NULL))   \
      _cb_func_(__VA_ARGS__);    \
  } while (0)

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/* Public function prototypes ----------------------------------------- */

#endif // __COMMON_

/* End of file -------------------------------------------------------- */
