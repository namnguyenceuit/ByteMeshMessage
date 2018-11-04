/**************************************************************************
  * @file       : generic_byte_client.h
  * @brief      : create a new model client for sending a byte (unsigned char) from client
  * @author     : William Nguyen(thnam.nguyen27) 
  * @version    : 0.1
  * @history    : created on @20181029
***************************************************************************/

#ifndef GENERIC_BYTE_CLIENT_H__
#define GENERIC_BYTE_CLIENT_H__

#include <stdint.h>
#include <stdbool.h>
#include "access.h"
#include "generic_byte_common.h"

#define GENERIC_BYTE_MODEL_CLIENT_ID (0x0005)

#define GENERIC_BYTE_VALUE_MIN (0)
#define GENERIC_BYTE_VALUE_MAX (100)

typedef enum
{
    /** Received normal status from the server. */
    GENERIC_BYTE_STATUS_NORMAL,
    /** The server did not reply to a Byte Send Set/Get. */
    GENERIC_BYTE_STATUS_ERROR_NO_REPLY,
    /** Simple Byte Send Set/Get was cancelled. */
    GENERIC_BYTE_STATUS_CANCELLED
} generic_byte_status_t;

/** Forward declaration. */
typedef struct generic_byte_client generic_byte_client_t;

/**
 * Byte Send status callback type.
 *
 * @param[in] p_self Pointer to the Generic Byte client structure that received the status.
 * @param[in] status The received status of the remote server.
 * @param[in] src    Element address of the remote server.
 */
typedef void (*generic_byte_status_cb_t)(const generic_byte_client_t * p_self, generic_byte_status_t status, uint16_t src);

/**
 * Byte Send timeout callback type.
 *
 * @param[in] handle Model handle
 * @param[in] p_self Pointer to the ByteSend client structure that received the status.
 */
typedef void (*generic_byte_timeout_cb_t)(access_model_handle_t handle, void * p_self);

/** Generic Byte Client state structure. */
struct generic_byte_client
{
    /** Model handle assigned to the client. */
    access_model_handle_t model_handle;
    /** Status callback called after status received from server. */
    generic_byte_status_cb_t status_cb;
    /** Timeout callback called after acknowledged message sending times out */
    generic_byte_timeout_cb_t timeout_cb;
    /** Internal client state. */
    struct
    {
        bool reliable_transfer_active;    /**< Variable used to determine if a transfer is currently active. */
        generic_byte_msg_set_t data;  /**< Variable reflecting the data stored in the server. */
    }state;
};

/**
 * Initializes the Generic Byte client.
 *
 * @note This function should only be called ONCE.
 * @note The client handles the model allocation and adding.
 *
 * @param[in,out] p_client      Generic Byte Client structure pointer.
 * @param[in]     element_index Element index to add the server model.
 *
 * @retval NRF_SUCCESS         Successfully added client.
 * @retval NRF_ERROR_NULL      NULL pointer supplied to function.
 * @retval NRF_ERROR_NO_MEM    No more memory available to allocate model.
 * @retval NRF_ERROR_FORBIDDEN Multiple model instances per element is not allowed.
 * @retval NRF_ERROR_NOT_FOUND Invalid element index.
 */
uint32_t generic_byte_client_init(generic_byte_client_t * p_client, uint16_t element_index);

/**
 * Sets the state of the Generic Byte server.
 *
 * @param[in,out] p_client Generic Byte Client structure pointer.
 * @param[in]     on_off   Value to set the Generic Byte Server state to.
 *
 * @retval NRF_SUCCESS              Successfully sent message.
 * @retval NRF_ERROR_NULL           NULL pointer in function arguments
 * @retval NRF_ERROR_NO_MEM         Not enough memory available for message.
 * @retval NRF_ERROR_NOT_FOUND      Invalid model handle or model not bound to element.
 * @retval NRF_ERROR_INVALID_ADDR   The element index is greater than the number of local unicast
 *                                  addresses stored by the @ref DEVICE_STATE_MANAGER.
 * @retval NRF_ERROR_INVALID_STATE  Message already scheduled for a reliable transfer.
 * @retval NRF_ERROR_INVALID_PARAM  Model not bound to appkey, publish address not set or wrong
 *                                  opcode format.
 */
uint32_t generic_byte_client_set(generic_byte_client_t * p_client, uint8_t byte);

/**
 * Sets the state of the Generic Byte Server unreliably (without acknowledgment).
 *
 * @param[in,out] p_client Generic Byte Client structure pointer.
 * @param[in]     on_off   Value to set the Generic Byte Server state to.
 * @param[in]     repeats  Number of messages to send in a single burst. Increasing the number may
 *                     increase probability of successful delivery.
 *
 * @retval NRF_SUCCESS              Successfully sent message.
 * @retval NRF_ERROR_NULL           NULL pointer in function arguments
 * @retval NRF_ERROR_NO_MEM         Not enough memory available for message.
 * @retval NRF_ERROR_NOT_FOUND      Invalid model handle or model not bound to element.
 * @retval NRF_ERROR_INVALID_ADDR   The element index is greater than the number of local unicast
 *                                  addresses stored by the @ref DEVICE_STATE_MANAGER.
 * @retval NRF_ERROR_INVALID_PARAM  Model not bound to appkey, publish address not set or wrong
 *                                  opcode format.
 */
uint32_t generic_byte_client_set_unreliable(generic_byte_client_t * p_client, uint8_t byte, uint8_t repeats);

/**
 * Gets the state of the Generic Byte server.
 *
 * @note The state of the server will be given in the @ref simple_on_off_status_cb_t callback.
 *
 * @param[in,out] p_client Generic Byte Client structure pointer.
 *
 * @retval NRF_SUCCESS              Successfully sent message.
 * @retval NRF_ERROR_NULL           NULL pointer in function arguments
 * @retval NRF_ERROR_NO_MEM         Not enough memory available for message.
 * @retval NRF_ERROR_NOT_FOUND      Invalid model handle or model not bound to element.
 * @retval NRF_ERROR_INVALID_ADDR   The element index is greater than the number of local unicast
 *                                  addresses stored by the @ref DEVICE_STATE_MANAGER.
 * @retval NRF_ERROR_INVALID_STATE  Message already scheduled for a reliable transfer.
 * @retval NRF_ERROR_INVALID_PARAM  Model not bound to appkey, publish address not set or wrong
 *                                  opcode format.
 */
uint32_t generic_byte_client_get(generic_byte_client_t * p_client);

/**
 * Cancel any ongoing reliable message transfer.
 *
 * @param[in,out] p_client Pointer to the client instance structure.
 */
void generic_byte_client_pending_msg_cancel(generic_byte_client_t * p_client);

#endif //GENERIC_BYTE_CLIENT_H__