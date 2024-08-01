/**
 * @file       bsp_buzzer_melody.h
 * @copyright  Copyright (C) 2024 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.0.0
 * @date       yyyy-mm-dd
 * @brief      Header file for Buzzer melody functionality.
 *
 * @note
 *
 * @example    example_file_1.c
 *             Example_1 description
 *
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_BUZZER_MELODY_H
#define __BSP_BUZZER_MELODY_H

/* Includes ----------------------------------------------------------- */
#include "bsp_buzzer_tone.h"

/* Public defines ----------------------------------------------------- */
#define MELODY_LENGTH 21 // Cập nhật độ dài đoạn nhạc

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/* Melody data -------------------------------------------------------- */
static const uint16_t melody_notes[MELODY_LENGTH] = {
  NOTE_A4,  NOTE_G4, NOTE_AS4, NOTE_A4, NOTE_F4,  NOTE_G4, 0,
  NOTE_E5,  NOTE_D5, NOTE_C5,  NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_G4,
  NOTE_AS4, NOTE_A4, NOTE_F4,  NOTE_G4, 0,        NOTE_D4, NOTE_G4
};

static const uint16_t melody_durations[MELODY_LENGTH] = {
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12
};

#endif // __BSP_BUZZER_MELODY_H

/* End of file -------------------------------------------------------- */
