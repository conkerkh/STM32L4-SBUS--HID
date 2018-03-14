#ifndef __RBDMA
#define __RBDMA

/* ----------------BEGIN HEADERS------------------ */

/* ------------Standard C lib includes------------ */
#include <stdint.h>
#include <stdbool.h>
/* ----------Low LVL Trackener includes----------- */

/* ---------High LVL Trackener Includes----------- */

/* -----------------ST includes------------------- */
#include "stm32l4xx_hal.h"
/* -----------------END HEADERS------------------- */

typedef struct tRingBufferDMA {
	uint8_t *buffer;
	uint16_t size;
	volatile uint8_t *tail;
	UART_HandleTypeDef *huart;
} tRingBufferDMA;

void 		RingBuffer_DMA_Init(tRingBufferDMA *ring,UART_HandleTypeDef* huart, uint16_t size);
void 		RingBuffer_DMA_DeInit(tRingBufferDMA *ring);
void 		RingBuffer_DMA_ReInit(tRingBufferDMA *ring);
void 		RingBuffer_DMA_CheckForError(tRingBufferDMA *ring);
uint16_t 	RingBuffer_DMA_Available(tRingBufferDMA *ring);
uint8_t 	RingBuffer_DMA_Read(tRingBufferDMA *ring);
uint16_t 	RingBuffer_DMA_ReadLength(tRingBufferDMA *ring, uint8_t *buf, uint16_t len);
void 		RingBuffer_DMA_Flush(tRingBufferDMA *ring);

#endif
