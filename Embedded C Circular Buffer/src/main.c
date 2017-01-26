//*****************************************************************************
//
//*****************************************************************************
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lm4f120h5qr.h"
#include "board_config.h"
#include "../team.h"
#include "uartPoll.h"
#include "circular_buffer.h"
#include "circularBufferTests.h"


/******************************************************************************
 * Defines
 *****************************************************************************/
#define PORTA                 0x40004000
#define PORTB                 0x40005000
#define PORTC                 0x40006000
#define PORTD                 0x40007000
#define PORTE                 0x40024000
#define PORTF                 0x40025000


/******************************************************************************
 * Global Variables
 *****************************************************************************/
 GPIO_PORT *GpioPortA = (GPIO_PORT *)PORTA;
 GPIO_PORT *GpioPortB = (GPIO_PORT *)PORTB;
 GPIO_PORT *GpioPortC = (GPIO_PORT *)PORTC;
 GPIO_PORT *GpioPortD = (GPIO_PORT *)PORTD;
 GPIO_PORT *GpioPortE = (GPIO_PORT *)PORTE;
 GPIO_PORT *GpioPortF = (GPIO_PORT *)PORTF;
   

//*****************************************************************************
// External Functions
//*****************************************************************************
extern void PLL_Init(void);
extern bool InitializeUART(uint32_t base, UART_CONFIG *init);
extern char uartRxPoll(uint32_t base);
extern void uartTxPoll(uint32_t base, char *data);
extern bool  initializeGPIOPort( uint32_t base, GPIO_CONFIG *init);


//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
  uint32_t i = 1000;
  uint8_t total = 0;
  char msg[80];
  
  // Initialize the PLLs so the the main CPU frequency is 80MHz
  PLL_Init();
  
  initializeGPIOPort(PORTA, &portA_config);
  initializeGPIOPort(PORTB, &portB_config);
  initializeGPIOPort(PORTC, &portC_config);
  initializeGPIOPort(PORTD, &portD_config);
  initializeGPIOPort(PORTE, &portE_config);

  // Initialize the UART and then wait a bit
  InitializeUART(UART0, &UART0_config);
  while(i != 0)
  {
    i--;
  }
  
  uartTxPoll(UART0,"\n\r");
  uartTxPoll(UART0,"****** ECE353 ******\n\r");
  uartTxPoll(UART0,"HW3 Test Bench\n\r");
  uartTxPoll(UART0,teamNumber);
  uartTxPoll(UART0,"\n\r");
  uartTxPoll(UART0,teamMembers);
  uartTxPoll(UART0,"\n\r");
  uartTxPoll(UART0,"********************\n\r");
  uartTxPoll(UART0,"\n\r");
  
  total += cBuffer_tests();
  
  sprintf(msg,"\n\r\n\rPoint Total = %d\n\r",total);
  uartTxPoll(UART0,msg);
  
  uartTxPoll(UART0,"\n\r");
  uartTxPoll(UART0,"****** ECE353 ******\n\r");
  uartTxPoll(UART0,"HW3 Test Bench\n\r");
  uartTxPoll(UART0,"********************\n\r");
  uartTxPoll(UART0,"\n\r");
  
  while(1)
  {

      
  }

  
}

