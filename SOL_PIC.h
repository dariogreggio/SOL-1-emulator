//---------------------------------------------------------------------------
//
#ifndef _SOL_PIC_INCLUDED
#define _SOL_PIC_INCLUDED

//---------------------------------------------------------------------------
#include <stdint.h>

/* check if build is for a real debug tool */
#if defined(__DEBUG) && !defined(__MPLAB_ICD2_) && !defined(__MPLAB_ICD3_) && \
   !defined(__MPLAB_PICKIT2__) && !defined(__MPLAB_PICKIT3__) && \
   !defined(__MPLAB_REALICE__) && \
   !defined(__MPLAB_DEBUGGER_REAL_ICE) && \
   !defined(__MPLAB_DEBUGGER_ICD3) && \
   !defined(__MPLAB_DEBUGGER_PK3) && \
   !defined(__MPLAB_DEBUGGER_PICKIT2) && \
   !defined(__MPLAB_DEBUGGER_PIC32MXSK)
    #warning Debug with broken MPLAB simulator
    #define USING_SIMULATOR
#endif


//#define REAL_SIZE    


#define FCY 204000000ul    //Oscillator frequency; ricontrollato con baud rate, pare giusto cos�!

#define CPU_CLOCK_HZ             (FCY)    // CPU Clock Speed in Hz
#define CPU_CT_HZ            (CPU_CLOCK_HZ/2)    // CPU CoreTimer   in Hz
#define PERIPHERAL_CLOCK_HZ      (FCY/2 /*100000000UL*/)    // Peripheral Bus  in Hz
#define GetSystemClock()         (FCY)    // CPU Clock Speed in Hz
#define GetPeripheralClock()     (PERIPHERAL_CLOCK_HZ)    // Peripheral Bus  in Hz
#define FOSC 8000000ul

#define US_TO_CT_TICKS  (CPU_CT_HZ/1000000UL)    // uS to CoreTimer Ticks
    
#define VERNUML 3
#define VERNUMH 0



typedef char BOOL;
typedef unsigned char UINT8;
typedef unsigned char BYTE;
typedef signed char INT8;
typedef unsigned short int WORD;
//typedef unsigned short int uint16_t;       // v. C64: con int/32bit � pi� veloce!
typedef unsigned long UINT32;
typedef unsigned long DWORD;
typedef signed long INT32;
typedef unsigned short int UINT16;
typedef signed int INT16;

typedef DWORD COLORREF;

#define RGB(r,g,b)      ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))


#define TRUE 1
#define FALSE 0


#define _TFTWIDTH  		160     //the REAL W resolution of the TFT
#define _TFTHEIGHT 		128     //the REAL H resolution of the TFT

typedef signed char GRAPH_COORD_T;
typedef unsigned char UGRAPH_COORD_T;

void mySYSTEMConfigPerformance(void);
void myINTEnableSystemMultiVectoredInt(void);

#define ReadCoreTimer()                  _CP0_GET_COUNT()           // Read the MIPS Core Timer

void ShortDelay(DWORD DelayCount);
#define __delay_ms(n) ShortDelay(n*100000UL)
#define __delay_ns(n) ShortDelay(n*100UL)

#define ClrWdt() { WDTCONbits.WDTCLRKEY=0x5743; }

// PIC32 RTCC Structure
typedef union {
  struct {
    unsigned char   weekday;    // BCD codification for day of the week, 00-06
    unsigned char   mday;       // BCD codification for day of the month, 01-31
    unsigned char   mon;        // BCD codification for month, 01-12
    unsigned char   year;       // BCD codification for years, 00-99
  	};                              // field access	
  unsigned char       b[4];       // byte access
  unsigned short      w[2];       // 16 bits access
  unsigned long       l;          // 32 bits access
	} PIC32_RTCC_DATE;

// PIC32 RTCC Structure
typedef union {
  struct {
    unsigned char   reserved;   // reserved for future use. should be 0
    unsigned char   sec;        // BCD codification for seconds, 00-59
    unsigned char   min;        // BCD codification for minutes, 00-59
    unsigned char   hour;       // BCD codification for hours, 00-24
  	};                              // field access
  unsigned char       b[4];       // byte access
  unsigned short      w[2];       // 16 bits access
  unsigned long       l;          // 32 bits access
	} PIC32_RTCC_TIME;
extern volatile PIC32_RTCC_DATE currentDate;
extern volatile PIC32_RTCC_TIME currentTime;


extern BYTE Pipe1;
extern union __attribute__((__packed__)) PIPE2 {
	uint16_t x;
	BYTE bb[4];
	struct __attribute__((__packed__)) {
		BYTE l;
		BYTE h;
//		BYTE u;		 bah no, sposto la pipe quando ci sono le istruzioni lunghe 4...
		} b;
	} Pipe2;




void Timer_Init(void);
void PWM_Init(void);
void UART_Init(DWORD);
void WriteUART1(unsigned int data);
void putsUART1(unsigned int *buffer);
char BusyUART1(void);
unsigned int ReadUART1(void);
char DataRdyUART1(void);

int decodeKBD(int, long, BOOL);
BYTE GetPipe(uint16_t);
BYTE GetValue(uint16_t);
uint16_t GetIntValue(uint16_t);
void PutValue(uint16_t, BYTE);
int Emulate(int);

int UpdateScreen(uint16_t rowIni, uint16_t rowFin, BYTE _i);
int PlotDisplay(WORD pos,BYTE ch,BYTE c);


#define LED1 LATEbits.LATE2
#define LED2 LATEbits.LATE3
#define LED3 LATEbits.LATE4
#define SW1  PORTDbits.RD2
#define SW2  PORTDbits.RD3


// pcb SDRradio 2019
#define	SPISDITris 0		// niente qua
#define	SPISDOTris TRISGbits.TRISG8				// SDO
#define	SPISCKTris TRISGbits.TRISG6				// SCK
#define	SPICSTris  TRISGbits.TRISG7				// CS
#define	LCDDCTris  TRISEbits.TRISE7				// DC che su questo LCD � "A0" per motivi ignoti
//#define	LCDRSTTris TRISBbits.TRISB7
	
#define	m_SPISCKBit LATGbits.LATG6		// pin 
#define	m_SPISDOBit LATGbits.LATG8		// pin 
#define	m_SPISDIBit 0
#define	m_SPICSBit  LATGbits.LATG7		// pin 
#define	m_LCDDCBit  LATEbits.LATE7 		// pin 
//#define	m_LCDRSTBit LATBbits.LATB7 //FARE
//#define	m_LCDBLBit  LATBbits.LATB12

#endif

