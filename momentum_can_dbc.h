/*******************************************************************************
 * @file momentum_can_dbc.h
 * @brief Auto-generated CAN message definitions from DBC file.
 *******************************************************************************
 */

#ifndef MOMENTUM_CAN_DBC_H
#define MOMENTUM_CAN_DBC_H

/** Includes. *****************************************************************/

#include "can_driver/can_driver.h"

/** CPP guard open. ***********************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/** DBC message index enum. **************************************************/

typedef enum {
  MOMENTUM_CAN_DBC_IDX_STATE = 0,
  MOMENTUM_CAN_DBC_IDX_BAROMETRIC = 1,
  MOMENTUM_CAN_DBC_IDX_GNSS1 = 2,
  MOMENTUM_CAN_DBC_IDX_GNSS2 = 3,
  MOMENTUM_CAN_DBC_IDX_GNSS3 = 4,
  MOMENTUM_CAN_DBC_IDX_IMU1 = 5,
  MOMENTUM_CAN_DBC_IDX_IMU2 = 6,
  MOMENTUM_CAN_DBC_IDX_IMU3 = 7,
  MOMENTUM_CAN_DBC_IDX_IMU4 = 8,
  MOMENTUM_CAN_DBC_IDX_IMU5 = 9,
  MOMENTUM_CAN_DBC_IDX_DATETIME_GET = 10,
  MOMENTUM_CAN_DBC_IDX_DATETIME_GET_RESPONSE = 11,
  MOMENTUM_CAN_DBC_IDX_VERSION_GET = 12,
  MOMENTUM_CAN_DBC_IDX_VERSION_GET_RESPONSE = 13,

  MOMENTUM_CAN_DBC_IDX_COUNT // Total message count.
} momentum_can_dbc_index_t;

/** Public variables. *********************************************************/

extern const can_message_t dbc_messages[];

/** CPP guard close. **********************************************************/

#ifdef __cplusplus
}
#endif

#endif // MOMENTUM_CAN_DBC_H
