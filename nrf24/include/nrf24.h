/**
 * This file defines the API to access the NRF24L01+.
 *
 * The main use cases considered will be
 *  1. unidirectional communication (sender -> receiver); and
 *  2. bidirectional peer-to-peer communication.
 */

#ifndef _NRF24_H_
#define _NRF24_H_

/// @brief Structure for the state of the device for troubleshooting,
/// maintaining statistical data about the quality of service (number
/// of packets successfully sent/dropped), latency, etc.
typedef struct {
    /// @brief The current number of packets in the TX buffer
    uint8_t tx_fifo_size;

    /// @brief The current number of packets in the RX buffer
    uint8_t rx_fifo_size;

    /// @brief The device status, can be used to determine the IRQ kind
    uint8_t status;

    /// @brief The FIFO status
    uint8_t fifo_status;
} nrf24_t;

/// @brief Initialize the NRF24 unit
/// @todo Add configuration
void nrf24_init(nrf24_t *rf);

/// @brief Update the status of the device
void nrf24_get_status(nrf24_t *rf);

/// @brief Update the FIFO status of the device
void nrf24_get_fifo_status(nrf24_t *rf);

/// @brief Read a packet arrived in the RX FIFO
/// @param buffer Buffer provided by client to store the data 
/// @param length To contain the size of the data read
void nrf24_receive(nrf24_t *rf, uint8_t* buffer, uint8_t *length);

/// @brief For primary transmitter (PTX) node, put a packet into the TX FIFO for transmission
/// @param payload The payload to transmit
/// @param length The length of the payload message
void nrf24_transmit(nrf24_t *rf, uint8_t* payload, uint8_t length);

/// @brief For primary receiver (PRX) node, put an acknowledgement payload into the TX FIFO
/// to transmit back to the transmitter (PTX) on the arrival of the NEXT packet.
/// @param ack The acknowledgement payload
/// @param length Length of the acknowledgement
void nrf24_write_ack(nrf24_t *rf, uint8_t* ack, uint8_t length);

#endif

