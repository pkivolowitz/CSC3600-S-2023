#pragma once

#include <stdint.h>

struct ClientDatagram
{
	uint32_t sequence_number;
	uint16_t  payload_length;
    // The payload comes next.
};

struct ServerDatagram
{
	uint32_t  sequence_number;
	uint16_t  datagram_length;
};

