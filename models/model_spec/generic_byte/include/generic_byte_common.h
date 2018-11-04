/**************************************************************************
  * @file       : generic_byte_common.h
  * @brief      : define some info for generic_byte model
  * @author     : William Nguyen(thnam.nguyen27)
  * @version    : 0.1
  * @history    : created on @20181029
***************************************************************************/

#ifndef GENERIC_BYTE_COMMON_H__
#define GENERIC_BYTE_COMMON_H__

#include <stdint.h>
#include "access.h"

/** Vendor specific company ID for Generic Byte model */
#define GENERIC_BYTE_COMPANY_ID (ACCESS_COMPANY_ID_NORDIC)

/** Simple Byte Send opcodes. */
typedef enum
{
    GENERIC_BYTE_OPCODE_SET = 0xD1,             /**< Generic Byte Acknowledged Set. */
    GENERIC_BYTE_OPCODE_GET = 0xD2,             /**< Generic Byte Get. */
    GENERIC_BYTE_OPCODE_SET_UNRELIABLE = 0xD3,  /**< Generic Byte Set Unreliable. */
    GENERIC_BYTE_OPCODE_STATUS = 0xD4           /**< Generic Byte Status. */
} generic_byte_opcode_t;

/** Message format for the Generic Byte Set message. */
typedef struct __attribute((packed))
{
    uint8_t byte; /**< State to set. */
    uint8_t tid; /**< Transaction number. */
} generic_byte_msg_set_t;

/** Message format for th Generic Byte Set Unreliable message. */
typedef struct __attribute((packed))
{
    uint8_t byte; /**< State to set. */
    uint8_t tid; /**< Transaction number. */
} generic_byte_msg_set_unreliable_t;

/** Message format for the Generic Byte Status message. */
typedef struct __attribute((packed))
{
    uint8_t present_byte; /**< Current state. */
} generic_byte_msg_status_t;

#endif //GENERIC_BYTE_COMMON_H__