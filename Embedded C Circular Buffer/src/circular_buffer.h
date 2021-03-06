#ifndef __ECE353_CIRCULAR_BUFFER__
#define __ECE353_CIRCULAR_BUFFER__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "lm4f120h5qr.h"

typedef struct {
    volatile uint32_t tailIndex;
    volatile int32_t size;
    volatile int32_t count;
    volatile char *buffer;
} CircularBuffer ;


/******************************************************************************
 * cBufInit
 *
 * Description:
 *		Allocates 'size' bytes from the heap and initializes the circular buffer
 *      to be empty.
 *
 *  Retuns 0 on success and a negative number for failure.
 *****************************************************************************/
int32_t		cBufInit(CircularBuffer *bufPtr, int16_t size);

/******************************************************************************
 * cBufAddChar
 *
 * Description:
 *		Adds a character to a circular buffer.  
 *
 *      If there is room in the circular buffer, the character is added to 
 *      the buffer and 0 is returned
 *
 *      If the buffer is full, the oldest entry in the circular buffer is 
 *      overwritten and 1 is returned
 *
 *      A full buffer contains no unused entries in the buffer
 *      (i.e. a buffer of size 8 should accept 8 characters before
 *       cBufGetFreeCount would return 0 free entries)
 *
 *      All other error conditions should return a negative value.
 *****************************************************************************/
int32_t		cBufAddChar(CircularBuffer *bufPtr, char c);

/******************************************************************************
 * cBufGetChar:
 *		returns a character in retChar from a circular buffer.  
 *
 *      If there is a character to return, the return value is 0.  
 *
 *      If the circular is empty, it will return a positive number
 *
 *      All other error conditions should return a negative number
 *****************************************************************************/
int32_t		cBufGetChar(CircularBuffer *bufPtr, char *retChar); 

/******************************************************************************
 * cBufGetFreeCount
 *		Returns the number of unused entries in the circular buffer
 *
 *      All other error conditions should return a negative number
 *****************************************************************************/
int32_t		cBufGetFreeCount(CircularBuffer *bufPtr);

#endif
