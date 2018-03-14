/*
 * ringbufferdma.c
 *
 *  Created on: Nov 6, 2016
 *      Author: khockuba
 */

//TODO:Make library OS independent

/* ----------------BEGIN HEADERS------------------ */
#include "ringbufferdma.h"
/* ------------Standard C lib includes------------ */
#include <stdlib.h>
#include <string.h>
/* ----------Low LVL Trackener includes----------- */

/* ---------High LVL Trackener Includes----------- */

/* -----------------ST includes------------------- */

/* -----------------END HEADERS------------------- */

#define MALLOC(x) 	malloc(x)
#define FREE(x)		free(x)

void RingBuffer_DMA_Init(tRingBufferDMA *ring, UART_HandleTypeDef* huart, uint16_t size)
{
	ring->huart = huart;
	ring->size = size;
	ring->buffer = MALLOC(ring->size);
	memset(ring->buffer, 0x00, ring->size);
	ring->tail = ring->buffer;
#ifdef __HAL_UART_CLEAR_OREFLAG
	__HAL_UART_CLEAR_OREFLAG(ring->huart);
#endif
	HAL_UART_Receive_DMA(ring->huart, (uint8_t *)ring->buffer, ring->size);
}

void RingBuffer_DMA_ReInit(tRingBufferDMA *ring)
{
	//ReInit if not initialized.
	if (!HAL_IS_BIT_SET(ring->huart->Instance->CR3, USART_CR3_DMAR)) {
		ring->tail = ring->buffer;
		memset(ring->buffer, 0x00, ring->size);
		HAL_UART_Receive_DMA(ring->huart, (uint8_t *)ring->buffer, ring->size);
	}
}

void RingBuffer_DMA_DeInit(tRingBufferDMA *ring)
{
	HAL_UART_DMAStop(ring->huart);
	if (ring->buffer != NULL) {
		FREE(ring->buffer);
		ring->buffer = NULL;
	}
}

uint16_t RingBuffer_DMA_Available(tRingBufferDMA *ring)
{
	uint32_t leftToTransfer = __HAL_DMA_GET_COUNTER(ring->huart->hdmarx);
	volatile uint8_t const* head = ring->buffer + ring->size - leftToTransfer;
	volatile uint8_t const* tail = ring->tail;
	if (head >= tail) {
		return head - tail;
	} else {
		return head - tail + ring->size;
	}
}

uint8_t RingBuffer_DMA_Read(tRingBufferDMA *ring)
{
	uint8_t val = *ring->tail++;
	if (ring->tail >= ring->buffer + ring->size) {
		ring->tail -= ring->size;
	}
	return val;
}

uint16_t RingBuffer_DMA_ReadLength(tRingBufferDMA *ring, uint8_t *buf, uint16_t len)
{
	uint16_t i;
	uint16_t available_bytes = RingBuffer_DMA_Available(ring);
	uint8_t *floatingPointer = buf;
	len = (available_bytes < len) ? available_bytes : len;
	for (i = 0; i < len; i++) {
		uint8_t val = *ring->tail;
		__DSB();
		ring->tail++;
		if (ring->tail >= ring->buffer + ring->size) {
			ring->tail -= ring->size;
		}
		*floatingPointer = val;
		floatingPointer++;
	}
	return i;
}

void RingBuffer_DMA_CheckForError(tRingBufferDMA *ring)
{
	if (!(ring->huart->Instance->CR3 & 0x40)) {
		//DMA Recieve is disabled we need to reenable it
		RingBuffer_DMA_DeInit(ring);
		RingBuffer_DMA_Init(ring, ring->huart, ring->size);
	}
}

void RingBuffer_DMA_Flush(tRingBufferDMA *ring)
{
	uint32_t leftToTransfer = __HAL_DMA_GET_COUNTER(ring->huart->hdmarx);
	volatile uint8_t const* head = ring->buffer + ring->size - leftToTransfer;
	ring->tail = (uint8_t *) head;
}
