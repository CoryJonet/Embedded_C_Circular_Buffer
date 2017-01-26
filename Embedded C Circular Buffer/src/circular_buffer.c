/************************************************************************/
/* FILE NAME    - circular_buffer.c                                     */
/* AUTHOR       - ECE353 Staff                                          */
/* DATE CREATED - 26-Feb-2014                                           */
/* DESCRIPTION  -                                                       */
/*                                                                      */
/* (c) ECE Department, University of Wisconsin - Madison                */
/************************************************************************/
#include "circular_buffer.h"



/******************************************************************************
 * cBufInit
 *****************************************************************************/
int32_t		cBufInit(CircularBuffer *bufPtr, int16_t size)
{
		//Check address
    if(&bufPtr == NULL || size == NULL)
		{
			return -1;
		}
		
		bufPtr->buffer = malloc(size * sizeof(char)); //Allocate space for buffer
		bufPtr->size = size; //Update size of buffer
		bufPtr->count = 0; //Initial character count in buffer
		
		bufPtr->tailIndex = bufPtr->count; //Set tail to initial buffer position
		
    return 0; 
}

/******************************************************************************
 * cBufAddChar
 *****************************************************************************/
int32_t		cBufAddChar(CircularBuffer *bufPtr, char c)
{
		volatile char *iter; //Temp pointer to traverse
	
		//Check address & charcter != NULL & max buffer count hit 
    if(&bufPtr == NULL || c == NULL)
		{
			return -1;
		}

		//If buffer is full
		if(bufPtr->count == bufPtr->size)
		{
			//tailIndex at end
			if(bufPtr->tailIndex == bufPtr->size)
			{
				iter = bufPtr->buffer; //Puts buffer ptr to beginning
				bufPtr->tailIndex = 0; 	//Resets tailIndex
				*iter = c; 		//Adds character to oldest buffer location
				iter++; 			//Increment buffer oldest location
				bufPtr->tailIndex++; 		//Increment oldest tail location
			}
			
			//tailIndex not at end
			else
			{
				iter = bufPtr->buffer;
				iter += (bufPtr->tailIndex * sizeof(char));	//Increment buffer oldest location
				*iter = c; 	//Adds character to oldest buffer location
				bufPtr->tailIndex++; 	//Increment oldest tail location
			}
			return 1;
		}
		
		//Buffer not full
		else
		{
			iter = bufPtr->buffer;
			iter += (bufPtr->count * sizeof(char));
			*iter = c; //Adds character to buffer
			bufPtr->count++;
		}
		return 0;
}

/******************************************************************************
 * cBufGetChar:
 *****************************************************************************/
int32_t		cBufGetChar(CircularBuffer *bufPtr, char *retChar)
{
		volatile char *iter; //Temp pointer to traverse
	
		//Check address
    if(&bufPtr == NULL)
		{
			return -1;
		}
		
		//If buffer is empty
		if(bufPtr->count == 0)
		{
			return 1;
		}
		
		iter = bufPtr->buffer; //Assign iter to buffer start
		
		iter += (bufPtr->tailIndex * sizeof(char)); //Assign up to correct position
		
		*retChar = *iter;
		bufPtr->tailIndex++;
		bufPtr->count--;

    return 0;
}

/******************************************************************************
 * cBufGetFreeCount
 *****************************************************************************/
int32_t		cBufGetFreeCount(CircularBuffer *bufPtr)
{
	int32_t unused; //Unused space count
	
	//Check address
	if(&bufPtr == NULL || bufPtr->size == NULL)
		{
			return -1;
		}
   
		unused = (bufPtr->size - bufPtr->count); //Calculates unused space
		
		return unused;
	
}

