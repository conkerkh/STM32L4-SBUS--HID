/*
 * sbus.h
 *
 *  Created on: Mar 8, 2018
 *      Author: khockuba
 */

#ifndef SBUS_H_
#define SBUS_H_

#include "ringbufferdma.h"

#define SBUS_FAILSAFE_INACTIVE 0
#define SBUS_FAILSAFE_ACTIVE   1
#define SBUS_STARTBYTE         0x0f
#define SBUS_ENDBYTE           0x00

#define SBUS_DIGITAL_CHANNEL_MIN 173
#define SBUS_DIGITAL_CHANNEL_MAX 1812

typedef struct {
	uint8_t step;
	uint8_t flags;
	uint8_t byteBuffer[26];
	uint16_t ch[18];
	uint32_t receivedPackets;
	uint32_t lostPackets;
	uint32_t errorPackets;
	uint32_t lastFrame;
	tRingBufferDMA usartRX;
} tSbusProto;

int32_t _constrain(int32_t val, int32_t min, int32_t max);
int32_t _map(int32_t value, int32_t old_min, int32_t old_max, int32_t new_min, int32_t new_max);

void SBUS_Init(tSbusProto *proto, UART_HandleTypeDef *huart);
void SBUS_Parse(tSbusProto *proto);
void SBUS_ParseChar(tSbusProto *proto, uint8_t byte);

#endif /* SBUS_H_ */
