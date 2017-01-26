#ifndef __CIRCULAR_BUFFER_TESTS_H__
#define __CIRCULAR_BUFFER_TESTS_H__

#include <stdint.h>
#include <stdlib.h>
#include "uartPoll.h"
#include "circular_buffer.h"

extern void uartTxPoll(uint32_t base, char *data);
int8_t cBuffer_tests(void);

#endif
