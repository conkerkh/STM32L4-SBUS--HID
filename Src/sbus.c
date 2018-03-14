/*
 * sbus.c
 *
 *  Created on: Mar 8, 2018
 *      Author: khockuba
 */

#include "sbus.h"
#include <math.h>

static float _apply_deadband_f(float value, float deadband) {
	return (fabs(value) < deadband) ? 0 : value;
}

int32_t _constrain(int32_t val, int32_t min, int32_t max)
{
	if (val > max) return max;
	else if (val < min) return min;
	else return val;
}

int32_t _map(int32_t value, int32_t old_min, int32_t old_max, int32_t new_min, int32_t new_max)
{
	return (value - old_min) * (new_max - new_min) / (old_max - old_min) + new_min;
}

void SBUS_Init(tSbusProto *proto, UART_HandleTypeDef *huart) {
	proto->lastFrame = 0;
	proto->receivedPackets = 0;
	proto->step = 0;
	proto->flags = 0;
	//RingBuffer_DMA_Init(&proto->usartRX, huart, 128);
	huart->Instance->CR1 |= USART_CR1_RXNEIE;
	huart->Instance->ICR |= USART_ICR_FECF | USART_ICR_PECF | USART_ICR_ORECF;
}

static void SBUS_GetChannelsFromBuffer(tSbusProto *proto) {
	proto->receivedPackets++;
	proto->lastFrame = HAL_GetTick();

	proto->ch[0]  = ((proto->byteBuffer[1]    | proto->byteBuffer[2]<<8)                             & 0x07FF);
	proto->ch[1]  = ((proto->byteBuffer[2]>>3 | proto->byteBuffer[3]<<5)                             & 0x07FF);
	proto->ch[2]  = ((proto->byteBuffer[3]>>6 | proto->byteBuffer[4]<<2 | proto->byteBuffer[5]<<10)  & 0x07FF);
	proto->ch[3]  = ((proto->byteBuffer[5]>>1 | proto->byteBuffer[6]<<7)                             & 0x07FF);
	proto->ch[4]  = ((proto->byteBuffer[6]>>4 | proto->byteBuffer[7]<<4)                             & 0x07FF);
	proto->ch[5]  = ((proto->byteBuffer[7]>>7 | proto->byteBuffer[8]<<1 | proto->byteBuffer[9]<<9)   & 0x07FF);
	proto->ch[6]  = ((proto->byteBuffer[9]>>2 | proto->byteBuffer[10]<<6)                            & 0x07FF);
	proto->ch[7]  = ((proto->byteBuffer[10]>>5| proto->byteBuffer[11]<<3)                            & 0x07FF);
	proto->ch[8]  = ((proto->byteBuffer[12]   | proto->byteBuffer[13]<<8)                            & 0x07FF);
	proto->ch[9]  = ((proto->byteBuffer[13]>>3| proto->byteBuffer[14]<<5)                            & 0x07FF);
	proto->ch[10] = ((proto->byteBuffer[14]>>6| proto->byteBuffer[15]<<2| proto->byteBuffer[16]<<10) & 0x07FF);
	proto->ch[11] = ((proto->byteBuffer[16]>>1| proto->byteBuffer[17]<<7)                            & 0x07FF);
	proto->ch[12] = ((proto->byteBuffer[17]>>4| proto->byteBuffer[18]<<4)                            & 0x07FF);
	proto->ch[13] = ((proto->byteBuffer[18]>>7| proto->byteBuffer[19]<<1| proto->byteBuffer[20]<<9)  & 0x07FF);
	proto->ch[14] = ((proto->byteBuffer[20]>>2| proto->byteBuffer[21]<<6)                            & 0x07FF);
	proto->ch[15] = ((proto->byteBuffer[21]>>5| proto->byteBuffer[22]<<3)                            & 0x07FF);

	proto->ch[16] = ((proto->byteBuffer[23])      & 0x0001) ? 2047: 0;
	proto->ch[17] = ((proto->byteBuffer[23] >> 1) & 0x0001) ? 2047: 0;

	if ((proto->byteBuffer[23] >> 3) & 0x0001) {
		proto->flags = SBUS_FAILSAFE_ACTIVE;
	} else {
		proto->flags = SBUS_FAILSAFE_INACTIVE;
	}

	if ((proto->byteBuffer[23] >> 2) & 0x0001) {
		proto->lostPackets++;
	}
}

void SBUS_Parse(tSbusProto *proto) {
	uint16_t data_len = RingBuffer_DMA_Available(&proto->usartRX);
	while (data_len--) {
		uint8_t byte = RingBuffer_DMA_Read(&proto->usartRX);
		if (proto->step == 0 && byte != SBUS_STARTBYTE) {
			proto->errorPackets++;
			continue;
		}

		proto->byteBuffer[proto->step++] = byte;

		if (proto->step == 25) {
			proto->step = 0;
			if (proto->byteBuffer[24] != SBUS_ENDBYTE) {
				proto->errorPackets++;
				continue;
			}

			SBUS_GetChannelsFromBuffer(proto);
		}
	}
}

void SBUS_ParseChar(tSbusProto *proto, uint8_t byte) {
	if (proto->step == 0 && byte != SBUS_STARTBYTE) {
		proto->errorPackets++;
		return;
	}

	proto->byteBuffer[proto->step++] = byte;

	if (proto->step == 25) {
		proto->step = 0;
		if (proto->byteBuffer[24] != SBUS_ENDBYTE) {
			proto->errorPackets++;
			return;
		}

		SBUS_GetChannelsFromBuffer(proto);
	}
}
