// Paulo Costantino https://github.com/Pconst167/sol-1/tree/main

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
//#include <graph.h>
//#include <dos.h>
//#include <malloc.h>
//#include <memory.h>
//#include <fcntl.h>
//#include <io.h>
#include <xc.h>

#include "Adafruit_ST77xx.h"
#include "Adafruit_ST7735.h"
#include "adafruit_gfx.h"

#include "SOL_PIC.h"


#pragma check_stack(off)
// #pragma check_pointer( off )
#pragma intrinsic( _enable, _disable )


extern BYTE fExit;
extern BYTE debug;
#define RAM_START 0x8000
#define RAM_SIZE 0x7f00
#define ROM_START 0x0000
#define ROM_SIZE 0x7fff				// 
BYTE ram_seg[RAM_SIZE];
BYTE rom_seg[ROM_SIZE];			
volatile BYTE TIMIRQ;
BYTE Keyboard[8]={255,255,255,255,255,255,255,255};
BYTE M48T02[8];
BYTE U16550_0[8],U16550_1[8],U16550_0alt[3],U16550_1alt[3];
BYTE U8255_0[4],U8255_1[4];
BYTE U8253[8];
BYTE NVRAM[64];

extern volatile BYTE keysFeedPtr;

extern BYTE DoReset,DoIRQ,DoHalt,DoWait;
extern BYTE ColdReset;


BYTE GetValue(SWORD t) {
	register BYTE i;

	if(t >= RAM_START && t < (RAM_START+RAM_SIZE)) {
		t-=RAM_START;
		i=ram_seg[t];
		}
	else if(t >= ROM_START && t < (ROM_START+ROM_SIZE)) {
		t-=ROM_START;
		i=rom_seg[t];
		}
/*0019   0000             ; FF80    UART 0    (16550)
0020   0000             ; FF90    UART 1    (16550)
0021   0000             ; FFA0    RTC       (M48T02)
0022   0000             ; FFB0    PIO 0     (8255)
0023   0000             ; FFC0    PIO 1     (8255)
0024   0000             ; FFD0    IDE       (Compact Flash / PATA)
0025   0000             ; FFE0    Timer     (8253)
0026   0000             ; FFF0    BIOS CONFIGURATION NV-RAM STORE AREA
*/
  else if(t>=0xff80 && t<=0xff8f) {        // UART 0
//_UART0_DATA      .equ $FF80        		 ; data
//_UART0_DLAB_0    .equ $FF80        		 ; divisor latch low byte
//_UART0_DLAB_1    .equ $FF81        		 ; divisor latch high byte
//_UART0_IER       .equ $FF81        		 ; Interrupt enable register
//_UART0_FCR       .equ $FF82        		 ; FIFO control register
//_UART0_LCR       .equ $FF83        		 ; line control register
// 4= Modem CTRL
//_UART0_LSR       .equ $FF85        		 ; line status register
// 6= Modem Status
// 7= scratchpad
    t &= 0x7;
    switch(t) {
      case 0:
        if(U16550_0[3] & 0x80) {
          i=U16550_0alt[0];
          }
        else {
          i=ReadUART1();
          }
        break;
      case 1:
        if(U16550_0[3] & 0x80) {
          i=U16550_0alt[1];
          }
        else {
          if(DataRdyUART1())
            U16550_0[1] |= 1;
          else
            U16550_0[1] &= ~1;
          if(!BusyUART1())
            U16550_0[1] |= 2;
          else
            U16550_0[1] &= ~2;
          i=U16550_0[1];
          }
        break;
      case 2:
        i=U16550_0[2];
        break;
      case 3:
        i=U16550_0[3];
        break;
      case 4:
        i=U16550_0[4];
        break;
      case 5:
        if(U16550_0[3] & 0x80) {
//          i=U16550_0alt[2];
          }
        else {
          if(DataRdyUART1())
            U16550_0[5] |= 1;
          else
            U16550_0[5] &= ~1;
          if(U1STAbits.FERR)
            U16550_0[5] |= 8;
          else
            U16550_0[5] &= ~8;
          if(U1STAbits.OERR)
            U16550_0[5] |= 2;
          else
            U16550_0[5] &= ~2;
          if(U1STAbits.PERR)
            U16550_0[5] |= 4;
          else
            U16550_0[5] &= ~4;
          if(!BusyUART1())    // THR
            U16550_0[5] |= 0x20;
          else
            U16550_0[5] &= ~0x20;
          if(!U1STAbits.UTXBF)    // TX
            U16550_0[5] |= 0x40;
          else
            U16550_0[5] &= ~0x40;
          i=U16550_0[5];
          }
        break;
      case 6:
        i=U16550_0[6];
        break;
      case 7:
        i=U16550_0[7];
        break;
      }
    }
  else if(t>=0xff90 && t<=0xff9f) {        // UART 1
    t &= 0x7;
    i=U16550_1[t];
    }
  else if(t>=0xffa0 && t<=0xffaf) {        // RTC
//Address  Data D7 D6 D5 D4 D3 D2 D1 D0  Function/range BCD format
//7FF 10 years Year Year 00-99
//7FE 0 0 0 10 M Month Month 01-12
//7FD 0 0 10 date Date Date 01-31
//7FC 0 FT 0 0 0 Day Day 01-07
//7FB 0 0 10 hours Hours Hours 00-23
//7FA 0 10 minutes Minutes Minutes 00-59
//7F9 ST 10 seconds Seconds Seconds 00-59
//7F8 W R S Calibration Control
    t &= 0x7;
    switch(t) {   // BCD!!
      case 0:
//        M48T02[0]= 0;   // flag IRQ
        break;
      case 1:
        M48T02[1]=currentTime.sec;
        break;
      case 2:
        M48T02[2]=currentTime.min;
        break;
      case 3:
        M48T02[3]=currentTime.hour;
        break;
      case 4:
        M48T02[4]=currentDate.weekday;
        break;
      case 5:
        M48T02[5]=currentDate.mday;
        break;
      case 6:
        M48T02[6]=currentDate.mon;
        break;
      case 7:
        M48T02[7]=currentDate.year;
        break;
      }
    i=M48T02[t];
    }
  else if(t>=0xffb0 && t<=0xffbf) {        // PIO 0
    t &= 0x3;
    i=U8255_0[t];
    }
  else if(t>=0xffc0 && t<=0xffcf) {        // PIO 1
    t &= 0x3;
    i=U8255_1[t];
    }
  else if(t>=0xffd0 && t<=0xffdf) {        // IDE
    t &= 0xf;

    }
  else if(t>=0xffe0 && t<=0xffef) {        // Timer
//_TIMER_C_0       .equ $FFE0        		 ; TIMER COUNTER 0
//_TIMER_C_1       .equ $FFE1        		 ; TIMER COUNTER 1
//_TIMER_C_2       .equ $FFE2        		 ; TIMER COUNTER 2
//_TIMER_CTRL      .equ $FFE3        		 ; TIMER CONTROL REGISTER
    t &= 0x3;
    i=U8253[t];
    }
  else if(t>=0xfff0 && t<=0xffff) {        // NV-RAM
    t &= 0x3f;
    i=NVRAM[t];
    }

	return i;
	}


SWORD GetIntValue(SWORD t) {
	register SWORD i;

	if(t >= RAM_START && t < (RAM_START+RAM_SIZE)) {
		t-=RAM_START;
		i=MAKEWORD(ram_seg[t],ram_seg[t+1]);
		}
	else if(t >= ROM_START && t < (ROM_START+ROM_SIZE)) {
		t-=ROM_START;
		i=MAKEWORD(rom_seg[t],rom_seg[t+1]);
		}

	return i;
	}

BYTE GetPipe(SWORD t) {

	if(t >= RAM_START && t < (RAM_START+RAM_SIZE)) {
		t-=RAM_START;
	  Pipe1=ram_seg[t++];
		Pipe2.b.l=ram_seg[t++];
//		Pipe2.b.h=ram_seg[t++];
//		Pipe2.b.u=ram_seg[t];
		Pipe2.b.h=ram_seg[t];
		}
	else if(t >= ROM_START && t < (ROM_START+ROM_SIZE)) {
		t-=ROM_START;
	  Pipe1=rom_seg[t++];
		Pipe2.b.l=rom_seg[t++];
//		Pipe2.b.h=rom_seg[t++];
//		Pipe2.b.u=rom_seg[t];
		Pipe2.b.h=rom_seg[t];
		}

	return Pipe1;
	}

void PutValue(SWORD t,BYTE t1) {
	register SWORD i;

// printf("rom_seg: %04x, p: %04x\n",rom_seg,p);

	if(t >= RAM_START && t < (RAM_START+RAM_SIZE)) {
	  ram_seg[t-RAM_START]=t1;
		}
  else if(t>=0xff80 && t<=0xff8f) {        // UART 0
//_UART0_DATA      .equ $FF80        		 ; data
//_UART0_DLAB_0    .equ $FF80        		 ; divisor latch low byte
//_UART0_DLAB_1    .equ $FF81        		 ; divisor latch high byte
//_UART0_IER       .equ $FF81        		 ; Interrupt enable register
//_UART0_FCR       .equ $FF82        		 ; FIFO control register
//_UART0_LCR       .equ $FF83        		 ; line control register
// 4= Modem CTRL
//_UART0_LSR       .equ $FF85        		 ; line status register
// 6= Modem Status
// 7= scratchpad
    t &= 0x7;
    switch(t) {
      case 0:
        if(U16550_0[3] & 0x80) {
          DWORD baudRateDivider;
          U16550_0alt[0]=t;
set_uart1:
          baudRateDivider = (GetPeripheralClock()/(4*MAKEWORD(U16550_0alt[0],U16550_0alt[1]))-1)
              /*U16550_0alt[2]*/;
          U6BRG=baudRateDivider;
          }
        else {
          U16550_0[0]=t1;
          WriteUART1(t1);
          }
        break;
      case 1:
        if(U16550_0[3] & 0x80) {
          U16550_0alt[1]=t;
          goto set_uart1;
          }
        else {
          U16550_0[1]=t1;
          }
        break;
      case 2:
        U16550_0[2]=t1;
        break;
      case 3:
        U16550_0[3]=t1;
        break;
      case 4:
        U16550_0[4]=t1;
        break;
      case 5:
        if(U16550_1[3] & 0x80) {
          U16550_1alt[2]=t;
          }
        else {
//          U16550_1[5]=t1;
          }
        break;
      case 6:
//         U16550_1[6]=t1;
        break;
      case 7:
        U16550_1[7]=t1;
        break;
      }
    }
  else if(t>=0xff90 && t<=0xff9f) {        // UART 1
    t &= 0x7;
    U16550_1[t]=t1;
    }
  else if(t>=0xffa0 && t<=0xffaf) {        // RTC
//Address  Data D7 D6 D5 D4 D3 D2 D1 D0  Function/range BCD format
//7FF 10 years Year Year 00-99
//7FE 0 0 0 10 M Month Month 01-12
//7FD 0 0 10 date Date Date 01-31
//7FC 0 FT 0 0 0 Day Day 01-07
//7FB 0 0 10 hours Hours Hours 00-23
//7FA 0 10 minutes Minutes Minutes 00-59
//7F9 ST 10 seconds Seconds Seconds 00-59
//7F8 W R S Calibration Control
    t &= 0x7;
    M48T02[t] = t1;
    switch(t) {   // BCD!!
      case 0:
//        M48T02[0]= 0;   // flag IRQ
        break;
      case 1:
        currentTime.sec=M48T02[1];
        break;
      case 2:
        currentTime.min=M48T02[2];
        break;
      case 3:
        currentTime.hour=M48T02[3];
        break;
      case 4:
        currentDate.weekday=M48T02[4];
        break;
      case 5:
        currentDate.mday=M48T02[5];
        break;
      case 6:
        currentDate.mon=M48T02[6];
        break;
      case 7:
        currentDate.year=M48T02[7];
        break;
      }
    }
  else if(t>=0xffb0 && t<=0xffbf) {        // PIO 0
    t &= 0x3;
    U8255_0[t]=t1;
    PlotDisplay(0,t1 >> 4,1);
    PlotDisplay(1,t1 & 0xf,1);
    }
  else if(t>=0xffc0 && t<=0xffcf) {        // PIO 1
    t &= 0x3;
    U8255_1[t]=t1;
    }
  else if(t>=0xffd0 && t<=0xffdf) {        // IDE
    t &= 0xf;

    }
  else if(t>=0xffe0 && t<=0xffef) {        // Timer
//_TIMER_C_0       .equ $FFE0        		 ; TIMER COUNTER 0
//_TIMER_C_1       .equ $FFE1        		 ; TIMER COUNTER 1
//_TIMER_C_2       .equ $FFE2        		 ; TIMER COUNTER 2
//_TIMER_CTRL      .equ $FFE3        		 ; TIMER CONTROL REGISTER
    t &= 0x3;
    U8253[t]=t1;
    }
  else if(t>=0xfff0 && t<=0xffff) {        // NV-RAM
    t &= 0x3f;
    NVRAM[t] = t1;
    switch(NVRAM[t]) {
      case 0:
        break;
      default:      // 
        break;
      }
    }

	}

void PutIntValue(SWORD t,SWORD t1) {
	register SWORD i;

// printf("rom_seg: %04x, p: %04x\n",rom_seg,p);

	if(t >= RAM_START && t < (RAM_START+RAM_SIZE)) {
		t-=RAM_START;
	  ram_seg[t++]=LOBYTE(t1);
	  ram_seg[t]=HIBYTE(t1);
		}
	}


