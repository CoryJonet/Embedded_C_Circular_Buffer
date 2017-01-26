#include "circularBufferTests.h"

CircularBuffer testBuffer;

/*****************************************************************
 *****************************************************************/
int8_t cBufferBasicTest(void)
{
  char charArray[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  int32_t retVal = 0;
  int8_t i = 0;
  int8_t j = 0;
  int8_t total = 40;
  char myChar = 0;
 
  i = sizeof(charArray);

   uartTxPoll(UART0,"\tInitializing Characters from the Buffer\n\r");

  // Initialize the buffer
    retVal = cBufInit(&testBuffer, i);
    if(retVal != 0)
    {
        uartTxPoll(UART0,"\tFailed cBufInit\n\r");
        total = 0;
    }
   
  uartTxPoll(UART0,"\tAdding Characters from the Buffer\n\r");   
    
  // Write all the characters in the array to the circular buffer
  for(j = 0; j < i; j++)
  {
      //Add the next char in the array
      retVal = cBufAddChar(&testBuffer, charArray[j]);
      
      //Verify the free count in the circular buffer
      retVal = cBufGetFreeCount(&testBuffer);
      
      if( retVal != (i - j - 1) )
      {
           uartTxPoll(UART0,"\tcBufGetFreeCount Failed\n\r");
           total = 0;
      }
  }

  uartTxPoll(UART0,"\tRemoving Characters from the Buffer\n\r");
  for(j = 0; j < i; j++)
  {
      //Verify the free count in the circular buffer
      retVal = cBufGetFreeCount(&testBuffer);
      if( retVal != j)
      {
           uartTxPoll(UART0,"\tcBufGetFreeCount Failed\n\r");
           total = 0;
      }
      
      //Get the next char in the buffer
      retVal = cBufGetChar(&testBuffer, &myChar);
      
      // Check to see if the returned character matches the array
      if( charArray[j] != myChar)
      {
          uartTxPoll(UART0,"\tcBufGetChar Failed\n\r");
          total = 0;
      } 
  }
  
  return total;
}


/*****************************************************************
 *****************************************************************/
int8_t cBuffer_tests(void)
{
    int8_t total = 0;
    
    total += cBufferBasicTest();
    
    return total;
    
}
