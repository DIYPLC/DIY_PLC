#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define F_CPU 16000000UL      // Arduino Nano quartz resonator Hz.
#define REG_HOLDING_START 1   // Смещение адреса.
#define REG_HOLDING_NREGS 16  // Количество регистров.

typedef enum {
  MB_ENOERR,    /*!< no error. */
  MB_ENOREG,    /*!< illegal register address. */
  MB_EINVAL,    /*!< illegal argument. */
  MB_EPORTERR,  /*!< porting layer error. */
  MB_ENORES,    /*!< insufficient resources. */
  MB_EIO,       /*!< I/O error. */
  MB_EILLSTATE, /*!< protocol stack in illegal state. */
  MB_ETIMEDOUT  /*!< timeout error occurred. */
} eMBErrorCode;

typedef enum {
  MB_PAR_NONE,  /*!< No parity. */
  MB_PAR_ODD,   /*!< Odd parity. */
  MB_PAR_EVEN   /*!< Even parity. */
} eMBParity;

eMBErrorCode eMBInit(uint8_t ucSlaveAddress, uint8_t ucPort, uint32_t ulBaudRate, eMBParity eParity);
eMBErrorCode eMBEnable(void);
eMBErrorCode eMBPoll(void);

#ifdef __cplusplus
}
#endif

// https://github.com/cwalter-at/freemodbus

/*
   FreeModbus Libary: A portable Modbus implementation for Modbus ASCII/RTU.
   Copyright (c) 2006-2018 Christian Walter <cwalter@embedded-solutions.at>
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   1. Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
   3. The name of the author may not be used to endorse or promote products
      derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
   IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
   NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
   THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
