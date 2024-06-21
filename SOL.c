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


#include "SOL_PIC.h"
#include "Adafruit_ST77xx.h"      // per LOBYTE ecc...


#pragma check_stack(off)
// #pragma check_pointer( off )
#pragma intrinsic( _enable, _disable )


extern BYTE fExit;
extern BYTE debug;

extern volatile BYTE keysFeedPtr;
extern volatile BYTE TIMIRQ;

BYTE DoReset=0,DoIRQ=0,DoHalt=0,DoWait=0;
BYTE ColdReset=1;
BYTE Pipe1;
union /*__attribute__((__packed__))*/ PIPE2 Pipe2;





union /*__attribute__((__packed__))*/ Z_REG {
  SWORD x;
  struct /*__attribute__((__packed__))*/ { 
    BYTE l;
    BYTE h;
    } b;
  };
union /*__attribute__((__packed__))*/ Z_REGISTERS {
  BYTE  b[10];
  union Z_REG r[5];
  };

#define ID_CARRY 0x1
#define ID_ADDSUB 0x2
#define ID_PV 0x4
#define ID_HALFCARRY 0x10
#define ID_ZERO 0x40
#define ID_SIGN 0x80
union /*__attribute__((__packed__))*/ REGISTRO_F {
  BYTE b;
  struct /*__attribute__((__packed__))*/ {
    unsigned int Carry: 1;
    unsigned int AddSub: 1;
    unsigned int PV: 1;   // 1=pari 0=dispari
    unsigned int unused: 1;
    unsigned int HalfCarry: 1;
    unsigned int Ovf: 1;
    unsigned int Zero: 1;
    unsigned int Sign: 1;
    };
  };
union /*__attribute__((__packed__))*/ OPERAND {
  BYTE *reg8;
  WORD *reg16;
  WORD mem;
  };
union /*__attribute__((__packed__))*/ RESULT {
  struct /*__attribute__((__packed__))*/ {
    BYTE l;
    BYTE h;
    } b;
  WORD x;
  DWORD d;
  };
    
// http://clrhome.org/table/
// https://wikiti.brandonw.net/index.php?title=Z80_Instruction_Set
int Emulate(int mode) {
/*Registers (http://www.z80.info/z80syntx.htm#LD)
--------------
 A = 111
 B = 000
 C = 001
 D = 010
 E = 011
 H = 100
 L = 101*/
#define _ah regs1.r[0].b.h
#define _bh regs1.r[1].b.h
#define _ch regs1.r[2].b.h
#define _dh regs1.r[3].b.h
#define _gh regs1.r[4].b.h
#define _al regs1.r[0].b.l
#define _bl regs1.r[1].b.l
#define _cl regs1.r[2].b.l
#define _dl regs1.r[3].b.l
#define _gl regs1.r[4].b.l
#define _a regs1.r[0].x
#define _b regs1.r[1].x
#define _c regs1.r[2].x
#define _d regs1.r[3].x
#define _g regs1.r[4].x
#define WORKING_REG regs1.b[((Pipe1 & 0x38) ^ 8) >> 3]      // la parte bassa/alta è invertita...
#define WORKING_REG2 regs1.b[(Pipe1 ^ 1) & 7]
//#define WORKING_REG_CB regs1.b[((Pipe2.b.l & 0x38) ^ 8) >> 3]
#define WORKING_REG_CB regs1.b[(Pipe2.b.l ^ 1) & 7]
#define WORKING_BITPOS (1 << ((Pipe2.b.l & 0x38) >> 3))
#define WORKING_BITPOS2 (1 << ((Pipe2.b.h & 0x38) >> 3))
    
	SWORD _pc=0;
	SWORD _si=0;
	SWORD _di=0;
	SWORD _sp=0,_ssp=0;
	SWORD _bp=0;
	SWORD _ptb=0;
  union Z_REGISTERS _tdr;
#define _tdrl _tdr.b.l
#define _tdrh _tdr.b.h
	BYTE IRQ_Mode=0;
	BYTE IRQ_Enable1=0,IRQ_Enable2=0;
  union Z_REGISTERS regs1,regs2;
  union RESULT res1,res2,res3;
//  union OPERAND op1,op2;
	union REGISTRO_F _flags;
	union REGISTRO_F _status;
	/*register*/ SWORD i;
  int c=0;


	_pc=0;
  
  
  
  
	do {

		c++;
		if(!(c & 0x3ffff)) {
      ClrWdt();
// yield()
#ifndef USING_SIMULATOR      
			UpdateScreen(0,127,0);
#endif
      LED1^=1;    // 42mS~ con SKYNET 7/6/20; 10~mS con Z80NE 10/7/21; 35mS GALAKSIJA 16/10/22; 30mS ZX80 27/10/22
      // QUADRUPLICO/ecc! 27/10/22
      
      
      }

		if(ColdReset) {
			ColdReset=0;
      DoReset=1;
			continue;
      }


#ifdef ZX80
    { static oldR=0;
      if(!(_r & 0x40) && (oldR & 0x40)) {
        DoIRQ=1;
        }
      oldR=_r;
      }
#endif

    
		if(debug) {
//			printf("%04x    %02x\n",_pc,GetValue(_pc));
			}

		if(DoReset) {
	  	_pc=GetIntValue(0x0010);
			IRQ_Enable1=0;IRQ_Enable2=0;
     	IRQ_Mode=0;
			DoReset=0;DoHalt=0;//DoWait=0;
      keysFeedPtr=255; //meglio ;)
      continue;
			}
		if(DoIRQ) {
      
      // LED2^=1;    // 
      DoHalt=0;     // 
      
			if(IRQ_Enable1) {
				IRQ_Enable1=0;    // 
				DoIRQ=0;
				PutValue(--_sp,HIBYTE(_pc));
				PutValue(--_sp,LOBYTE(_pc));
        
        i;
        
// EXTERNAL INTERRUPT TABLE @0x0000, highest priority at lowest address
		  	_pc=GetIntValue(0x0000+i*2);
				}
			}

  
		if(DoHalt) {
      //mettere ritardino per analogia con le istruzioni?
//      __delay_ns(500); non va più nulla... boh...
			continue;		// esegue cmq IRQ e refresh
      }
		if(DoWait) {
      //mettere ritardino per analogia con le istruzioni?
//      __delay_ns(100);
			continue;		// esegue cmq IRQ?? penso di no... sistemare
      }

//printf("Pipe1: %02x, Pipe2w: %04x, Pipe2b1: %02x,%02x\n",Pipe1,Pipe2.word,Pipe2.bytes.byte1,Pipe2.bytes.byte2);
    
    
      if(!SW1) {        // test tastiera, me ne frego del repeat/rientro :)
       // continue;
        __delay_ms(100); ClrWdt();
        DoReset=1;
        }
      if(!SW2) {        // test tastiera
#if defined(ZX80)
        if(keysFeedPtr==255)      // debounce...
          keysFeedPtr=254;
#endif
        }

      LED2^=1;    // ~700nS 7/6/20, ~600 con 32bit 10/7/21 MA NON FUNZIONA/visualizza!! verificare; 5-700nS 27/10/22

    
/*      if(_pc == 0x069d ab5 43c Cd3) {
        ClrWdt();
        }*/
  
		switch(GetPipe(_pc++)) {
			case 0:   // 
				break;

			case 1:   // SETPTB
				_ptb;
				break;

			case 2:   // PAGEMAP
				
				break;

			case 3:   // STORE
				
				break;

			case 4:   // LOAD
				
				break;

			case 5:   // SYSCALL
// SYSTEM CALL VECTOR TABLE starts at address $0020
				_pc++;
				i=Pipe2.b.l;

        PutValue(--_sp,HIBYTE(_pc));
				PutValue(--_sp,LOBYTE(_pc));

				_pc=i*2+0x0020;
				break;

			case 6:   // SYSRET
        _pc=GetValue(_sp++);
        _pc |= ((SWORD)GetValue(_sp++)) << 8;
				
				break;

			case 7:    // CALL @, [@+A]
				i=Pipe2.x;
		    _pc+=2;

Call:
				PutValue(--_sp,HIBYTE(_pc));
				PutValue(--_sp,LOBYTE(_pc));
				_pc=i;
				break;

			case 8:    // CALL A
				i=_a;
				goto Call;
				break;

			case 9:    // RET
Return:
        _pc=GetValue(_sp++);
        _pc |= ((SWORD)GetValue(_sp++)) << 8;
				break;

			case 0xa:    // JMP @
Jump:
				_pc=Pipe2.x;
				break;

			case 0xb:    // JMP A
				_pc=_a;
				break;

			case 0x0c:		// LODSTAT
			  _al=_status.b;
				break;

			case 0x0d:		// STOSTAT
			  _status.b=_al;
				break;

			case 0x0e:		// LODFLGS
			  _al=_flags.b;
				break;

			case 0x0f:		// STOFLGS
			  _flags.b=_al;
				break;

			case 0x10:		// MOV A,@
				_a=Pipe2.x;
				_pc+=2;
				break;

			case 0x11:		// MOV A,B
				_a=_b;
				break;

			case 0x12:		// MOV A,C
				_a=_c;
				break;

			case 0x13:		// MOV A,D
				_a=_d;
				break;

			case 0x14:		// MOV A,[@]
				_a=GetValue(Pipe2.x++);
        _a |= ((SWORD)GetValue(Pipe2.x)) << 8;
				_pc+=2;
				break;

			case 0x15:		// MOV A,[D]
				_a=GetValue(_d);
        _a |= ((SWORD)GetValue(_d+1)) << 8;
				break;

			case 0x16:		// MOV A,[D+@]
				_a=GetValue(_d+Pipe2.x);
        _a |= ((SWORD)GetValue(_d+Pipe2.x+1)) << 8;
				_pc+=2;
				break;

			case 0x17:		// MOV A,[BP+@]
				_a=GetValue(_bp+Pipe2.x);
	      _a |= ((SWORD)GetValue(_bp+Pipe2.x+1)) << 8;
				_pc+=2;
				break;

			case 0x18:		// MOV A,[BP+D]
				_a=GetValue(_bp+_d);
				_a |= ((SWORD)GetValue(_bp+_d+1)) << 8;
				break;

			case 0x19:		// MOV AL,@
				_al=Pipe2.b.l;
				_pc++;
				break;

			case 0x1a:		// MOV AL,AH
				_al=_ah;
				break;

			case 0x1b:		// MOV AL,BL
				_al=_bl;
				break;

			case 0x1c:		// MOV AL,BH
				_al=_bh;
				break;

			case 0x1d:		// MOV AL,[@]
				_al=GetValue(Pipe2.x);
				_pc+=2;
				break;

			case 0x1e:		// MOV AL,[D]
				_al=GetValue(_d);
				break;

			case 0x1f:		// MOV AL,[D+@]
				_al=GetValue(_d+Pipe2.x);
				_pc+=2;
				break;

			case 0x20:		// MOV AL,[BP+@]
				_al=GetValue(_bp+Pipe2.x);
				_pc+=2;
				break;

			case 0x21:		// MOV AL,[BP+D]
				_al=GetValue(_bp+_d);
				break;

			case 0x22:		// MOV AH,[@]
				_ah=GetValue(Pipe2.x);
				_pc+=2;
				break;

			case 0x23:		// MOV AH,AL
				_ah=_al;
				break;

			case 0x24:		// MOV AH,BL
				_ah=_bl;
				break;

			case 0x25:		// MOV AH,BH
				_ah=_bh;
				break;

			case 0x26:		// MOV B,@
				_b=Pipe2.x;
				_pc+=2;
				break;

			case 0x27:		// MOV B,A
				_b=_a;
				break;

			case 0x28:		// MOV B,C
				_b=_c;
				break;

			case 0x2d:		// MOV B,D
				_a=_d;
				break;

			case 0x29:		// MOV B,[@]
				_b=GetValue(Pipe2.x++);
        _b |= ((SWORD)GetValue(Pipe2.x)) << 8;
				_pc+=2;
				break;

			case 0x2a:		// MOV B,[D]
				_b=GetValue(_d);
				_b |= ((SWORD)GetValue(_d+1)) << 8;
				break;

			case 0x2b:		// MOV B,[D+@]
				_b=GetValue(_d+Pipe2.x);
        _b |= ((SWORD)GetValue(_d+Pipe2.x+1)) << 8;
				_pc+=2;
				break;

			case 0x2c:		// MOV B,[BP+@]
				_b=GetValue(_bp+Pipe2.x);
	      _b |= ((SWORD)GetValue(_bp+Pipe2.x+1)) << 8;
				_pc+=2;
				break;

        // *****************BUG duplicato
//			case 0x2d:		// MOV B,[BP+D]
//				_b=GetValue(_bp+_d);
//				_b |= ((SWORD)GetValue(_bp+_d+1)) << 8;
//				break;

			case 0x2e:		// MOV BL,@
				_bl=Pipe2.b.l;
				_pc++;
				break;

			case 0x2f:		// MOV BL,AL
				_bl=_al;
				break;

			case 0x30:		// MOV BL,BH
				_bl=_bh;
				break;

			case 0x31:		// MOV BL,[@]
				_bl=GetValue(Pipe2.x);
				_pc+=2;
				break;

			case 0x32:		// MOV BL,[D]
				_bl=GetValue(_d);
				break;

			case 0x33:		// MOV BL,[D+@]
				_bl=GetValue(_d+Pipe2.x);
				_pc+=2;
				break;

			case 0x34:		// MOV BL,[BP+@]
				_bl=GetValue(_bp+Pipe2.x);
				_pc+=2;
				break;

			case 0x35:		// MOV BL,[BP+D]
				_bl=GetValue(_bp+_d);
				break;


			case 0x36:		// MOV BH,AL
				_bh=_al;
				break;

			case 0x37:		// MOV BH,BL
				_bh=_bl;
				break;

			case 0x38:		// MOV C,@
				_c=Pipe2.x;
				_pc+=2;
				break;

			case 0x39:		// MOV C,A
				_c=_a;
				break;

			case 0x3a:		// MOV CL,@
				_cl=Pipe2.b.l;
			  _pc++;
				break;

			case 0x3b:		// MOV D,@
				_d=Pipe2.x;
				_pc+=2;
				break;

			case 0x3c:		// MOV D,A
				_d=_a;
				break;

			case 0x3d:		// MOV [@],AL
				PutValue(Pipe2.x,_al);
				_pc+=2;
				break;

			case 0x3e:		// MOV [D],AL
				PutValue(_d,_al);
				break;

			case 0x3f:		// MOV [D+@],AL
				PutValue(_d+Pipe2.x,_al);
				_pc+=2;
				break;

			case 0x40:		// MOV [BP+@],AL
				PutValue(_bp+Pipe2.x,_al);
				_pc+=2;
				break;

			case 0x41:		// MOV [BP+D],AL
				PutValue(_bp+_d,_al);
				break;

			case 0x42:		// MOV [@],A
				PutValue(Pipe2.x,_al);
				PutValue(Pipe2.x+1,_ah);
				_pc+=2;
				break;

			case 0x43:		// MOV [D],A
				PutValue(_d,_al);
				PutValue(_d+1,_ah);
				break;

			case 0x44:		// MOV [D+@],A
				PutValue(_d+Pipe2.x,_al);
				PutValue(_d+Pipe2.x+1,_ah);
				_pc+=2;
				break;

			case 0x45:		// MOV [BP+@],A
				PutValue(_bp+Pipe2.x,_al);
				PutValue(_bp+Pipe2.x+1,_ah);
				_pc+=2;
				break;

			case 0x46:		// MOV [BP+D],A
				PutValue(_bp+_d,_al);
				PutValue(_bp+_d+1,_ah);
				break;

			case 0x47:		// MOV SP,A
				_sp=_a;
				break;

			case 0x48:		// MOV A,SP
				_a=_sp;
				break;

			case 0x49:		// MOV BP,A
				_bp=_a;
				break;

			case 0x4a:		// MOV A,BP
				_a=_bp;
				break;

			case 0x4b:		// PUSHA

				break;

			case 0x4c:		// POPA

				break;

			case 0x4e:		// MOV A,SI
				_a=_si;
				break;

			case 0x50:		// MOV A,DI
				_a=_di;
				break;


			case 0x51:    // ADD SP,@
        res1.d=res2.d=0;
				res1.x=_sp;
				res2.x=Pipe2.x;
				res3.x=res1.x+res2.x;
				_sp=res3.x;
				_pc+=2;
				break;

			case 0x52:    // SUB SP,@
        res1.d=res2.d=0;
				res1.x=_sp;
				res2.x=Pipe2.x;
				res3.x=res1.x-res2.x;
				_sp=res3.x;
				_pc+=2;
				break;


			case 0x53:    // ADD A,@
        res1.d=res2.d=0;
				res1.x=_a;
				res2.x=Pipe2.x;
				res3.x=res1.x+res2.x;
				_a=res3.x;
				_pc+=2;
    
aggSomma2:
aggSommaB2:
aggSommaC2:
aggSommaD2:
        _flags.AddSub=0;
        _flags.HalfCarry = ((res1.b.l & 0xf) + (res2.b.l & 0xf)) >= 0x10 ? 1 : 0;   // 

aggFlag2:
        _flags.PV = !!HIWORD(res3.d) != !!((res3.b.h & 0x80) ^ (res1.b.h & 0x80) ^ (res2.b.h & 0x80));
        
aggFlagC2:    // 
				_flags.Carry=!!res3.b.h;
        
        _flags.Zero=res3.b.l ? 0 : 1;
        _flags.Sign=res3.b.l & 0x80 ? 1 : 0;
				break;
                                   
			case 0x54:    // ADD A,B
        res1.d=res2.d=0;
				res1.x=_a;
				res2.x=_b;
				res3.x=res1.x+res2.x;
				_a=res3.x;
    
				goto aggSomma2;
				break;
                                   
			case 0x55:    // ADD B,@
        res1.d=res2.d=0;
				res1.x=_b;
				res2.x=Pipe2.x;
				res3.x=res1.x+res2.x;
				_b=res3.x;
				_pc+=2;
    
				goto aggSommaB2;
				break;
                                   
			case 0x56:    // ADD B,A
        res1.d=res2.d=0;
				res1.x=_b;
				res2.x=_a;
				res3.x=res1.x+res2.x;
				_b=res3.x;
    
				goto aggSommaB2;
				break;
                                   
			case 0x57:    // ADD C,@
        res1.d=res2.d=0;
				res1.x=_c;
				res2.x=Pipe2.x;
				res3.x=res1.x+res2.x;
				_c=res3.x;
				_pc+=2;
    
				goto aggSommaC2;
				break;
                                   
			case 0x58:    // ADD D,@
        res1.d=res2.d=0;
				res1.x=_d;
				res2.x=Pipe2.x;
				res3.x=res1.x+res2.x;
				_d=res3.x;
				_pc+=2;
    
				goto aggSommaD2;
				break;
                                   
			case 0x59:    // ADD D,A
        res1.d=res2.d=0;
				res1.x=_d;
				res2.x=_a;
				res3.x=res1.x+res2.x;
				_d=res3.x;
    
				goto aggSommaD2;
				break;
                                   
			case 0x5a:    // ADD D,B
        res1.d=res2.d=0;
				res1.x=_d;
				res2.x=_b;
				res3.x=res1.x+res2.x;
				_d=res3.x;
    
				goto aggSommaD2;
				break;
                                   
			case 0x5b:    // ADC A,@
        res1.d=res2.d=0;
				res1.x=_a;
				res2.x=Pipe2.x;
				res3.x=res1.x+res2.x+_flags.Carry;
				_a=res3.x;
				_pc+=2;
    
aggSomma2C:
        _flags.AddSub=0;
        _flags.HalfCarry = ((SWORD)(res1.b.l) + (SWORD)(res2.b.l)) >= 0x100 ? 1 : 0;   // 
        goto aggAnd2;
				break;
                                   
			case 0x5c:    // ADC A,B
        res1.d=res2.d=0;
				res1.x=_a;
				res2.x=_b;
				res3.x=res1.x+res2.x+_flags.Carry;
				_a=res3.x;
				_pc+=2;
    
				goto aggSomma2C;
				break;
                                   
			case 0x5d:    // ADC B,@
        res1.d=res2.d=0;
				res1.x=_b;
				res2.x=Pipe2.x;
				res3.x=res1.x+res2.x+_flags.Carry;
				_b=res3.x;
				_pc+=2;
    
				goto aggSommaB2;
				break;
                                   
			case 0x5e:    // ADC C,@
        res1.d=res2.d=0;
				res1.x=_c;
				res2.x=Pipe2.x;
				res3.x=res1.x+res2.x+_flags.Carry;
				_c=res3.x;
				_pc+=2;
    
				goto aggSommaC2;
				break;
                                   
                                   
			case 0x5f:    // SUB A,@
        res1.d=res2.d=0;
				res1.x=_a;
				res2.x=Pipe2.x;
				res3.d=res1.d-res2.d;
				_a=res3.x;
				_pc+=2;
    
				goto aggSottr2;
				break;

			case 0x6a:    // ADD AL,@
        res1.x=res2.x=0;
				res1.b.l=_al;
				res2.b.l=Pipe2.b.l;
				res3.x=res1.x+res2.x;
				_al=res3.b.l;
    
aggSomma:
aggSommaB:
aggSommaC:
aggSommaD:
				res1.b.l=_a;
        res1.b.h=res2.b.h=0;
        res3.x=res1.x+res2.x;
        _a=res3.b.l;
        _flags.AddSub=0;
        _flags.HalfCarry = ((res1.b.l & 0xf) + (res2.b.l & 0xf)) >= 0x10 ? 1 : 0;   // 

aggFlagB:
        _flags.PV = !!res3.b.h != !!((res3.b.l & 0x80) ^ (res1.b.l & 0x80) ^ (res2.b.l & 0x80));
        
aggFlagBC:    // 
				_flags.Carry=!!res3.b.h;
        
        _flags.Zero=res3.b.l ? 0 : 1;
        _flags.Sign=res3.b.l & 0x80 ? 1 : 0;
				break;
                                   
			case 0x6b:    // ADD AL,BL
        res1.x=res2.x=0;
				res1.b.l=_al;
				res2.b.l=_bl;
				res3.x=res1.x+res2.x;
				_al=res3.b.l;
    
				goto aggSomma;
				break;
                                   
			case 0x6c:    // ADD BL,@
        res1.x=res2.x=0;
				res1.b.l=_bl;
				res2.b.l=Pipe2.b.l;
				res3.x=res1.x+res2.x;
				_bl=res3.b.l;
        _pc++;
    
				goto aggSomma;
				break;
                                   
			case 0x6d:    // ADD CL,@
        res1.x=res2.x=0;
				res1.b.l=_cl;
				res2.b.l=Pipe2.b.l;
				res3.x=res1.x+res2.x;
				_cl=res3.b.l;
        _pc++;
    
				goto aggSommaC;
				break;
                                   
			case 0x6e:    // ADD CH,@
        res1.x=res2.x=0;
				res1.b.l=_ch;
				res2.b.l=Pipe2.b.l;
				res3.x=res1.x+res2.x;
				_ch=res3.b.l;
        _pc++;
    
				goto aggSommaC;
				break;
                                   
			case 0x6f:    // SUB AL,@
        res1.x=res2.x=0;
				res1.b.l=_al;
				res2.b.l=Pipe2.b.l;
				res3.x=res1.x-res2.x;
				_al=res3.b.l;
				_pc++;
    
aggSottr:
aggSottrB:
aggSottrC:
aggSottrD:
        _flags.AddSub=1;
        _flags.HalfCarry = ((res1.b.l & 0xf) - (res2.b.l & 0xf)) & 0xf0 ? 1 : 0;   // 
        _flags.PV = !!res3.b.h != !!((res3.b.l & 0x80) ^ (res1.b.l & 0x80) ^ (res2.b.l & 0x80));
  			goto aggFlagBC;
				break;

			case 0x70:    // SUB AL,BL
        res1.x=res2.x=0;
				res1.b.l=_al;
				res2.b.l=_bl;
				res3.x=res1.x-res2.x;
				_al=res3.b.l;
    
				goto aggSottr;
				break;

			case 0x71:    // SUB CL,@
        res1.x=res2.x=0;
				res1.b.l=_cl;
				res2.b.l=Pipe2.b.l;
				res3.x=res1.x-res2.x;
				_cl=res3.b.l;
				_pc++;
    
				goto aggSottrC;
				break;

			case 0x72:    // SUB CH,@
        res1.x=res2.x=0;
				res1.b.l=_ch;
				res2.b.l=Pipe2.b.l;
				res3.x=res1.x-res2.x;
				_ch=res3.b.l;
				_pc++;
    
				goto aggSottrC;
				break;


			case 0x77:   // INC A
				_a++;

aggInc2:
      	_flags.Zero=res3.x ? 0 : 1;
        _flags.Sign=res3.x & 0x8000 ? 1 : 0;
        _flags.AddSub=0;
      	_flags.PV= res3.x == 0x8000 ? 1 : 0; //P = 1 if x=7FH before, else 0
      	_flags.HalfCarry= (res3.x & 0xf) == 0 ? 1 : 0; // INC x      1 if carry from bit 3 else 0 
				break;

			case 0x78:   // INC C
				_c++;
				break;

			case 0x79:   // INC D
				_d++;
				break;

			case 0x7a:   // INC AL
				_al++;

aggInc:
      	_flags.Zero=res3.b.l ? 0 : 1;
        _flags.Sign=res3.b.l & 0x80 ? 1 : 0;
        _flags.AddSub=0;
      	_flags.PV= res3.b.l == 0x80 ? 1 : 0; //P = 1 if x=7FH before, else 0
      	_flags.HalfCarry= (res3.b.l & 0xf) == 0 ? 1 : 0; // INC x      1 if carry from bit 3 else 0 
				break;

			case 0x75:   // INC AH
				_ah++;
				break;

			case 0x7b:   // INC CL
				_cl++;
				break;

			case 0x7c:   // INC CH
				_ch++;
				break;

			case 0x7d:   // DEC A
				_a--;
        
aggDec2:
      	_flags.Zero=res3.x ? 0 : 1;
        _flags.Sign=res3.x & 0x8000 ? 1 : 0;
        _flags.AddSub=1;
      	_flags.PV= res3.x == 0x7fff ? 1 : 0; //P = 1    // DEC x         P = 1 if x=80H before, else 0
      	_flags.HalfCarry= (res3.x & 0xf) == 0xf ? 1 : 0; // DEC x      1 if borrow from bit 4 else 0 
				break;

			case 0x7e:   // DEC C
				_c--;
				break;

			case 0x7f:   // DEC D
				_d--;
				break;

			case 0x80:   // DEC AL
				_al--;
        
aggDec:
      	_flags.Zero=res3.b.l ? 0 : 1;
        _flags.Sign=res3.b.l & 0x80 ? 1 : 0;
        _flags.AddSub=1;
      	_flags.PV= res3.b.l == 0x7f ? 1 : 0; //P = 1    // DEC x         P = 1 if x=80H before, else 0
      	_flags.HalfCarry= (res3.b.l & 0xf) == 0xf ? 1 : 0; // DEC x      1 if borrow from bit 4 else 0 
				break;

			case 0x73:   // DEC AH
				_ah--;
				break;

			case 0x81:   // DEC CL
				_cl--;
				break;

			case 0x82:   // DEC CH
				_ch--;
				break;

                                        
			case 0x74:		// MOV D,B
				_d=_b;
				break;

			case 0x83:		// MOV CL,AL
				_cl=_al;
				break;


			case 0x85:    // AND A,@
				_a &= Pipe2.x;
        res3.x=_a;
				_pc+=2;
        
aggAnd2C:
        _flags.Carry=0;
aggAnd2:      // 
        _flags.AddSub=0;
        _flags.Zero=res3.x ? 0 : 1;
        _flags.Sign=res3.x & 0x8000 ? 1 : 0;
        // halfcarry è 1 fisso se AND e 0 se OR/XOR
        
calcParity2:
          {
          SWORD par;
          par= res3.x >> 1;			// Microchip AN774
          par ^= res3.x;
          res3.x= par >> 2;
          par ^= res3.x;
          res3.x= par >> 4;
          par ^= res3.x;
          _flags.PV=par & 1 ? 1 : 0;
          }
				break;

			case 0x86:    // AND A,B
				_a &= _b;
        res3.x=_a;
        goto aggAnd2;
				break;

			case 0x87:    // AND AL,@
				_al &= Pipe2.b.l;
        res3.b.l=_al;
				_pc++;
//				_a &= WORKING_REG2;
//        _f.HalfCarry=1;
        
aggAnd:
        _flags.Carry=0;
aggAndC:      // 
        _flags.AddSub=0;
        _flags.Zero=res3.b.l ? 0 : 1;
        _flags.Sign=res3.b.l & 0x80 ? 1 : 0;
        // halfcarry è 1 fisso se AND e 0 se OR/XOR
        
calcParity:
          {
          BYTE par;
          par= res3.b.l >> 1;			// Microchip AN774
          par ^= res3.b.l;
          res3.b.l= par >> 2;
          par ^= res3.b.l;
          res3.b.l= par >> 4;
          par ^= res3.b.l;
          _flags.PV=par & 1 ? 1 : 0;
          }
				break;

			case 0x88:    // AND AL,BL
				_al &= _bl;
        res3.b.l=_al;
        goto aggAnd;
				break;

			case 0x89:    // OR A,@
				_a |= Pipe2.x;
        res3.x=_a;
				_pc+=2;
        goto aggAnd2;
				break;

			case 0x8a:    // OR A,B
				_a |= _b;
        res3.x=_a;
        goto aggAnd2;
				break;

			case 0x8b:    // OR AL,@
				_al |= Pipe2.b.l;
        res3.b.l=_al;
				_pc++;
        goto aggAnd;
				break;

			case 0x8c:    // OR AL,BL
				_al |= _bl;
        res3.b.l=_al;
        goto aggAnd;
				break;

			case 0x8d:    // XOR A,@
				_a ^= Pipe2.x;
        res3.x=_a;
				_pc+=2;
        goto aggAnd2;
				break;

			case 0x8e:    // XOR A,B
				_a ^= _b;
        res3.x=_a;
        goto aggAnd2;
				break;

			case 0x8f:    // XOR AL,@
				_al ^= Pipe2.b.l;
        res3.b.l=_al;
				_pc++;
        goto aggAnd;
				break;

			case 0x90:    // XOR AL,BL
				_al ^= _bl;
        res3.b.l=_al;
        goto aggAnd;
				break;

			case 0x91:    // TEST A,@
				res3.x = _a & Pipe2.x;
				_pc+=2;
        goto aggAnd2;
				break;

			case 0x92:    // TEST A,B
				res3.x = _a & _b;
        goto aggAnd2;
				break;

			case 0x93:    // TEST AL,@
				res3.b.l = _al & Pipe2.b.l;
				_pc++;
        goto aggAnd;
				break;

			case 0x94:    // TEST AL,BL
				res3.b.l = _al & _bl;
        goto aggAnd;
				break;

			case 0x95:		// NOT A
				_a=~_a;
				break;

			case 0x96:		// NOT AL
				_al=~_al;
				break;

			case 0x97:		// NOT B
				_b=~_b;
				break;

			case 0x98:		// NOT BL
				_bl=~_bl;
				break;

			case 0x60:    // SUB A,B
        res1.d=res2.d=0;
				res1.x=_a;
				res2.x=_b;
				res3.d=res1.d-res2.d;
				_a=res3.x;
        
aggSottr2:
aggSottrB2:
aggSottrC2:
aggSottrD2:
        _flags.AddSub=1;
        _flags.HalfCarry = ((res1.b.h) - (res2.b.h)) & 0xff00 ? 1 : 0;   // 
        _flags.PV = !!HIWORD(res3.x) != !!((res3.x & 0x8000) ^ (res1.x & 0x8000) ^ (res2.x & 0x8000));
  			goto aggFlagBC;
				break;

			case 0x61:    // SUB B,@
        res1.d=res2.d=0;
				res1.x=_b;
				res2.x=Pipe2.x;
				res3.d=res1.d-res2.d;
				_b=res3.x;
				_pc+=2;
    
				goto aggSottrB2;
				break;

			case 0x62:    // SUB C,@
        res1.d=res2.d=0;
				res1.x=_c;
				res2.x=Pipe2.x;
				res3.d=res1.d-res2.d;
				_c=res3.x;
				_pc+=2;
    
				goto aggSottrC2;
				break;

			case 0x63:    // SUB D,@
        res1.d=res2.d=0;
				res1.x=_d;
				res2.x=Pipe2.x;
				res3.d=res1.d-res2.d;
				_d=res3.x;
				_pc+=2;
    
				goto aggSottrD2;
				break;

			case 0x64:    // SUB D,A
        res1.d=res2.d=0;
				res1.x=_d;
				res2.x=_a;
				res3.d=res1.d-res2.d;
				_d=res3.x;
    
				goto aggSottrD2;
				break;

			case 0x65:    // SUB D,B
        res1.d=res2.d=0;
				res1.x=_d;
				res2.x=_b;
				res3.d=res1.d-res2.d;
				_d=res3.x;
    
				goto aggSottrD2;
				break;

			case 0x66:    // SBB A,@
				res1.x=_a;
				res2.x=Pipe2.x;
				res3.x=res1.x-res2.x;
				_a=res3.x;
				_pc+=2;
    
aggSottr2C:
aggSottrB2C:
aggSottrC2C:
aggSottrD2C:
				res1.b.l=_a;
        res1.b.h=res2.b.h=0;
        res3.x=res1.x-res2.x-_flags.Carry;
        _a=res3.b.l;
        _flags.AddSub=1;
        _flags.HalfCarry = ((res1.b.l & 0xf) - (res2.b.l & 0xf)) & 0xf0  ? 1 : 0;   // 
//#warning CONTARE IL CARRY NELL overflow?? no, pare di no (v. emulatore ma io credo di sì..
//        _f.PV = !!(((res1.b.l & 0x40) + (res2.b.l & 0x40)) & 0x80) != !!(((res1.x & 0x80) + (res2.x & 0x80)) & 0x100);
/*        if((res1.b.l & 0x80) != (res2.b.l & 0x80)) {
          if(((res1.b.l & 0x80) && !(res3.b.l & 0x80)) || (!(res1.b.l & 0x80) && (res3.b.l & 0x80)))
            _f.PV=1;
          else
            _f.PV=0;
          }
        else
          _f.PV=0;*/
        goto aggFlagB;
				break;

			case 0x67:    // SBB A,B
				res1.x=_a;
				res2.x=_b;
				res3.x=res1.x-res2.x;
				_a=res3.x;
    
				goto aggSottr2C;
				break;

			case 0x68:    // SBB B,@
				res1.x=_b;
				res2.x=Pipe2.x;
				res3.x=res1.x-res2.x;
				_b=res3.x;
				_pc+=2;
    
				goto aggSottrB2C;
				break;

			case 0x69:    // SBB C,@
				res1.x=_c;
				res2.x=Pipe2.x;
				res3.x=res1.x-res2.x;
				_c=res3.x;
				_pc+=2;
    
				goto aggSottrC2C;
				break;

			case 0x76:    // CMP AH,@
				res1.b.l=_ah;
				res2.b.l=Pipe2.b.l;
				_pc++;
        
				goto compare;
				break;


			case 0x9b:		// MOV BP,SP
				_bp=_sp;
				break;

			case 0x9c:		// MOV SP,BP
				_sp=_bp;
				break;

			case 0x9d:		// SHL A,CL
				res2.b.l=_cl;
        while(res2.b.l) {
              }

aggRotate:
        _flags.HalfCarry=_flags.AddSub=0;
        goto aggAnd;
				break;

			case 0x9e:		// SHL AL,CL
				res2.b.l=_cl;
        while(res2.b.l) {
              }

        goto aggRotate;
				break;

			case 0x9f:		// SHL B,CL
				res2.b.l=_cl;
        while(res2.b.l) {
              }

aggRotate2:
        _flags.HalfCarry=_flags.AddSub=0;
        goto aggFlag2;
				break;

			case 0xa0:		// SHL BL,CL
				res2.b.l=_cl;
        while(res2.b.l) {
              }

        goto aggRotate;
				break;

			case 0xa1:		// SHR A,CL
				res2.b.l=_cl;
        while(res2.b.l) {
              }

        goto aggRotate2;
				break;

			case 0xa2:		// SHR AL,CL
				res2.b.l=_cl;
        while(res2.b.l) {
              }

        goto aggRotate;
				break;

			case 0xa3:		// SHR B,CL
				res2.b.l=_cl;
        while(res2.b.l) {
              }

        goto aggRotate2;
				break;

			case 0xa4:		// SHR BL,CL
				res2.b.l=_cl;
        while(res2.b.l) {
              }

        goto aggRotate;
				break;

			case 0xa5:		// ASHR A,CL
				res2.b.l=_cl;
        while(res2.b.l) {
              }

        goto aggRotate2;
				break;

			case 0xa6:		// ASHR AL,CL
				res2.b.l=_cl;
        while(res2.b.l) {
              }

        goto aggRotate;
				break;


			case 0xa9:		// LOOPC @
				_pc++;
			  _b--;
				if(_b)
					_pc+=(signed char)Pipe2.b.l;




				break;

			case 0xaa:		// SNEX A


				break;

			case 0xab:		// SNEX B


				break;

			case 0xac:		// MUL A,B
				res1.d=res2.d=0;
				res1.x=_a;
				res2.x=_b;
				res3.d=res1.d*res2.d;
				_a=res3.x;

				break;

			case 0xad:		// MUL AL,BL
				res1.x=res2.x=0;
				res1.b.l=_al;
				res2.b.l=_bl;
				res3.x=res1.x*res2.x;
				_al=res3.b.l;

				break;

			case 0xae:		// DIV A,B
        res1.d=res2.d=0;
        res1.x = _a;
        res2.x = _b;
	      if(!res2.x) {
		      res3.b.l=5;
          i=1;

doTrap:
// EXCEPTION VECTOR TABLE total of 7 entries, starting at address $0012
          PutValue(--_sp,HIBYTE(_pc));
          PutValue(--_sp,LOBYTE(_pc));

          _pc=i*2+0x0012;
				  }
  			res3.d = (int32_t)res1.d / (int16_t)res2.x;
		    _flags.Ovf=!!(HIWORD(res3.d));
				// If overflow is detected during division, the operands are unaffected  (in which case the Z- and N-bits are undefined)
				if(!_flags.Ovf)
  				_a = MAKELONG(res3.x, (int32_t)res1.d % (int16_t)res2.x);
				break;

			case 0xaf:    // CMP A,@
				res1.d=res2.d=0;
				res1.x=_a;
				res2.x=Pipe2.x;
				_pc+=2;

				goto compare2;
				break;

			case 0xb0:    // CMP A,B
				res1.d=res2.d=0;
				res1.x=_a;
				res2.x=_b;
        
compare2:
				res3.d=res1.d-res2.d;
        _flags.HalfCarry = ((res1.x & 0xff) - (res2.x & 0xff)) & 0xff00 ? 1 : 0;   // 
        _flags.PV = !!HIWORD(res3.d) != !!((res3.x & 0x8000) ^ (res1.x & 0x8000) ^ (res2.x & 0x8000));
        _flags.AddSub=1;
  			goto aggFlagBC;
				break;

			case 0xb1:    // CMP A,C
				res1.d=res2.d=0;
				res1.x=_a;
				res2.x=_c;

				goto compare2;
				break;

			case 0xb2:    // CMP A,D
				res1.d=res2.d=0;
				res1.x=_a;
				res2.x=_d;

				goto compare2;
				break;

			case 0xb3:    // CMP WORD[@],@
				res1.d=res2.d=0;
				res1.x=GetIntValue(Pipe2.x);
				_pc+=2;
				GetPipe(_pc);
				res2.x=Pipe2.x;
				_pc+=2;
        
				goto compare2;
				break;

			case 0xb4:    // CMP WORD[D],@
				res1.d=res2.d=0;
				res1.x=GetIntValue(_d);
				res2.x=Pipe2.x;
				_pc+=2;
        
				goto compare2;
				break;

			case 0xb5:    // CMP WORD[D+@],@
				res1.d=res2.d=0;
				res1.x=GetIntValue(_d+Pipe2.x);
				_pc+=2;
				GetPipe(_pc);
				res2.x=Pipe2.x;
				_pc+=2;
        
				goto compare2;
				break;

			case 0xb6:    // CMP WORD[BP+@],@
				res1.d=res2.d=0;
				res1.x=GetIntValue(_bp+Pipe2.x);
				_pc+=2;
				GetPipe(_pc);
				res2.x=Pipe2.x;
				_pc+=2;
        
				goto compare2;
				break;

			case 0xb9:    // CMP AL,@
				res1.b.l=_al;
				res2.b.l=Pipe2.b.l;
				_pc++;
        
				goto compare;
				break;

			case 0xba:    // CMP AL,BL
				res1.b.l=_al;
				res2.b.l=_bl;
        
compare:
				res1.b.h=res2.b.h=0;
				res3.x=res1.x-res2.x;
        _flags.HalfCarry = ((res1.b.l & 0xf) - (res2.b.l & 0xf)) & 0xf0 ? 1 : 0;   // 
        _flags.PV = !!res3.b.h != !!((res3.b.l & 0x80) ^ (res1.b.l & 0x80) ^ (res2.b.l & 0x80));
        _flags.AddSub=1;
  			goto aggFlagBC;
				break;

			case 0xbb:    // CMP AL,CL
				res1.b.l=_al;
				res2.b.l=_cl;
        
				goto compare;
				break;

			case 0xb8:    // MOV WORD[@],@
				i=Pipe2.x;
				_pc+=2;
				GetPipe(_pc);
				PutValue(i,Pipe2.b.l);
				PutValue(i+1,Pipe2.b.h);
				_pc+=2;
				break;

			case 0xbc:    // CMP BYTE[@],@
				res1.b.l=GetValue(Pipe2.x);
				_pc+=2;
				GetPipe(_pc);
				res2.b.l=Pipe2.b.l;
				_pc++;
        
				goto compare;
				break;

			case 0xbd:    // CMP BYTE[D],@
				res1.b.l=GetValue(_d);
				res2.b.l=Pipe2.b.l;
				_pc++;
        
				goto compare;
				break;

			case 0xbe:    // CMP BYTE[D+@],@
				res1.b.l=GetValue(_d+Pipe2.x);
				_pc+=2;
				GetPipe(_pc);
				res2.b.l=Pipe2.b.l;
				_pc++;
        
				goto compare;
				break;

			case 0xbf:    // CMP BYTE[BP+@],@
				res1.b.l=GetValue(_bp+Pipe2.x);
				_pc+=2;
				GetPipe(_pc);
				res2.b.l=Pipe2.b.l;
				_pc++;
        
				goto compare;
				break;

			case 0xc0:    // CMP B,@
				res1.d=res2.d=0;
				res1.x=_b;
				res2.x=Pipe2.x;
				_pc+=2;
        
				goto compare2;
				break;

			case 0xc1:    // CMP BL,@
				res1.b.l=_bl;
				res2.b.l=Pipe2.b.l;
				_pc++;
        
				goto compare;
				break;

			case 0xc2:    // CMP C,@
				res1.d=res2.d=0;
				res1.x=_c;
				res2.x=Pipe2.x;
				_pc+=2;
        
				goto compare2;
				break;

			case 0xc3:    // CMP CL,@
				res1.b.l=_cl;
				res2.b.l=Pipe2.b.l;
				_pc++;
        
				goto compare;
				break;

			case 0xc4:    // CMP CH,@
				res1.b.l=_ch;
				res2.b.l=Pipe2.b.l;
				_pc++;
        
				goto compare;
				break;

			case 0xc5:    // CMP D,@
				res1.d=res2.d=0;
				res1.x=_d;
				res2.x=Pipe2.x;
				_pc+=2;
        
				goto compare2;
				break;

			case 0xc6:    // JZ @; JE @
			  if(_flags.Zero)
			    goto Jump;
			  else
			    _pc+=2;
				break;

			case 0xc7:    // JNZ @; JNE @
			  if(!_flags.Zero)
			    goto Jump;
			  else
			    _pc+=2;
				break;

			case 0xc8:    // JC @; JLU @
			  if(_flags.Carry)
			    goto Jump;
			  else
			    _pc+=2;
				break;

			case 0xc9:    // JNC @; JGEU @
			  if(!_flags.Carry)
			    goto Jump;
			  else
			    _pc+=2;
				break;

			case 0xca:    // JNEG @
			  if(_flags.Sign)
			    goto Jump;
			  else
			    _pc+=2;
				break;

			case 0xcb:    // JPOS @
			  if(!_flags.Sign)
			    goto Jump;
			  else
			    _pc+=2;
				break;

			case 0xcc:    // JL @
			  if(0 )
			    goto Jump;
			  else
			    _pc+=2;
				break;

			case 0xcd:    // JLE @
			  if(0)
			    goto Jump;
			  else
			    _pc+=2;
				break;

			case 0xce:    // JG @
			  if(0)
			    goto Jump;
			  else
			    _pc+=2;
				break;

			case 0xcf:    // JGE @
			  if(0)
			    goto Jump;
			  else
			    _pc+=2;
				break;

			case 0xd0:    // JLEU @
			  if(0)
			    goto Jump;
			  else
			    _pc+=2;
				break;

			case 0xd1:    // JGU @
			  if(0)
			    goto Jump;
			  else
			    _pc+=2;
				break;



			case 0xd2:    // PUSH BP
				PutValue(--_sp,LOBYTE(_bp));
				PutValue(--_sp,HIBYTE(_bp));
				break;

			case 0xd3:    // ADD SI,@
				res1.x=_si;
				res2.x=Pipe2.x;
				res3.x=res1.x+res2.x;
				_si=res3.x;
				_pc+=2;
				break;

			case 0xd4:    // ADD DI,@
				res1.x=_di;
				res2.x=Pipe2.x;
				res3.x=res1.x+res2.x;
				_di=res3.x;
				_pc+=2;
				break;

			case 0xd5:    // SUB SI,@
        res1.d=res2.d=0;
				res1.x=_si;
				res2.x=Pipe2.x;
				res3.d=res1.d-res2.d;
				_si=res3.x;
				_pc+=2;
				break;

			case 0xd6:    // SUB DI,@
        res1.d=res2.d=0;
				res1.x=_di;
				res2.x=Pipe2.x;
				res3.d=res1.d-res2.d;
				_di=res3.x;
				_pc+=2;
				break;

			case 0xd7:    // PUSH A; PUSH WORD@
				PutValue(--_sp,_ah);
				PutValue(--_sp,_al);
				break;

			case 0xd8:    // PUSH B, PUSH G
				PutValue(--_sp,_bh);
				PutValue(--_sp,_bl);
				break;

			case 0xd9:    // PUSH C
				PutValue(--_sp,_ch);
				PutValue(--_sp,_cl);
				break;

			case 0xda:    // PUSH D
				PutValue(--_sp,_dh);
				PutValue(--_sp,_dl);
				break;

			case 0xdb:    // PUSH AL
				PutValue(--_sp,_al);
				break;

			case 0xdc:    // PUSH AH
				PutValue(--_sp,_ah);
				break;

			case 0xdd:    // PUSH BL
				PutValue(--_sp,_bl);
				break;

			case 0xde:    // PUSH BH
				PutValue(--_sp,_bh);
				break;

			case 0xdf:    // PUSH CL
				PutValue(--_sp,_cl);
				break;

			case 0xe0:    // PUSH CH
				PutValue(--_sp,_ch);
				break;

			case 0xe1:    // PUSHF
				PutValue(--_sp,_flags.b);
				break;

			case 0xe2:    // PUSH SI
				PutValue(--_sp,LOBYTE(_si));
				PutValue(--_sp,HIBYTE(_si));
				break;

			case 0xe3:    // PUSH DI
				PutValue(--_sp,LOBYTE(_di));
				PutValue(--_sp,HIBYTE(_di));
				break;

			case 0xe4:    // POP A
				_a=GetValue(_sp++);
				_a |= ((SWORD)GetValue(_sp++)) << 8;
				break;

			case 0xe5:    // POP B
				_b=GetValue(_sp++);
				_b |= ((SWORD)GetValue(_sp++)) << 8;
				break;

			case 0xe6:    // POP C
				_c=GetValue(_sp++);
				_c |= ((SWORD)GetValue(_sp++)) << 8;
				break;

			case 0xe7:    // POP D
				_d=GetValue(_sp++);
				_d |= ((SWORD)GetValue(_sp++)) << 8;
				break;

			case 0xe8:    // POP AL
				_al=GetValue(_sp++);
				break;

			case 0xe9:    // POP AH
				_ah=GetValue(_sp++);
				break;

			case 0xea:    // POP BL
				_bl=GetValue(_sp++);
				break;

			case 0xeb:    // POP BH
				_bh=GetValue(_sp++);
				break;

			case 0xec:    // POP CL
				_cl=GetValue(_sp++);
				break;

			case 0xed:    // POP CH
				_ch=GetValue(_sp++);
				break;

			case 0xee:    // POPF
				_flags.b=GetValue(_sp++);
				break;

			case 0xef:    // POP SI
				_si=GetValue(_sp++);
				_si |= ((SWORD)GetValue(_sp++)) << 8;
				break;

			case 0xf0:    // POP DI
				_di=GetValue(_sp++);
				_di |= ((SWORD)GetValue(_sp++)) << 8;
				break;

			case 0xf1:    // POP BP
				_bp=GetValue(_sp++);
				_bp |= ((SWORD)GetValue(_sp++)) << 8;
				break;




			case 0xf2:    // MOV BYTE[@],@
				i=Pipe2.x;
				_pc+=2;
				GetPipe(_pc++);
				PutValue(i,Pipe2.b.l);
				break;

			case 0xf3:    // CMPSB
				_b--;
				res1.b.l=_a;
				res2.b.l=GetValue(_c++);
        
aggCPI:
				res1.b.h=res2.b.h=0;
				res3.x=res1.x-res2.x;
        _flags.AddSub=1;
        _flags.HalfCarry = ((res1.b.l & 0xf) - (res2.b.l & 0xf)) & 0xf0 ? 1 : 0;   // 
        _flags.Zero=res3.b.l ? 0 : 1;
        _flags.Sign=res3.b.l & 0x80 ? 1 : 0;
				_flags.PV=!!_c;
				break;

			case 0xf4:    // SCANSB
				break;

			case 0xf5:    // MOVSB
				PutValue(_b++,GetValue(_c++));
aggLDI:
				_d--;
        _flags.AddSub=_flags.HalfCarry=0;
				_flags.PV=!!_d;
				break;

			case 0xf6:    // LODSB
				break;

			case 0xf7:    // STOSB
				break;

			case 0xf8:    // ENTER @
				PutValue(--_sp,HIBYTE(_bp));
				PutValue(--_sp,LOBYTE(_bp));
        _bp=_sp;
        _sp-=Pipe2.x;
        _pc+=2;
				break;

			case 0xf9:    // LEAVE
        _sp=_bp;
				break;

			case 0xfa:    // LEA D,[BP+@]
				_d=_bp+Pipe2.x;
				_pc+=2;
				break;

			case 0xfb:    // LEA D,[SI+@]
				_d=_si+Pipe2.x;
				_pc+=2;
				break;

			case 0xfc:    // LEA D,[DI+@]
				_d=_di+Pipe2.x;
				_pc+=2;
				break;



			case 0xfd:    // ESC
				switch(GetPipe(_pc++)) {
					case 7:    // CALL [@+A]
						i=GetValue(Pipe2.x+_a);
						i |= ((SWORD)GetValue(Pipe2.x+1+_a)) << 8;
						_pc+=2;
						goto Call;
						break;

					case 8:    //  SUPCPY
						i;
						break;

					case 0x0c:    // STI
						IRQ_Enable1=IRQ_Enable2=1;
						break;

					case 0x0d:    // CLI
						IRQ_Enable1=IRQ_Enable2=0;
						break;

					case 0xa:    // JMP [@+BL]
						i=GetValue(Pipe2.x+_bl);
						i |= ((SWORD)GetValue(Pipe2.x+1+_bl)) << 8;
						_pc=i;
						break;

					case 0xb:    // JMP [@+BH]
						i=GetValue(Pipe2.x+_bh);
						i |= ((SWORD)GetValue(Pipe2.x+1+_bh)) << 8;
						_pc=i;
						break;


					case 0x0e:		// LODMSK
		_al;
						break;

					case 0x0f:		// STOMSK
		_al;
						break;

					case 0x10:		// CLA
						_a=0;
						break;

					case 0x11:		// MOV A,PC
						_a=_pc;
						break;

					case 0x12:		// MOV A,G
						_a=_g;
						break;

					case 0x14:		// CLB
						_b=0;
						break;

					case 0x17:		// MOV A,[SP+@]
						_a=GetValue(_sp+Pipe2.x);
						_a |= ((SWORD)GetValue(_sp+Pipe2.x+1)) << 8;
						_pc+=2;
						break;

					case 0x18:		// MOV A,[SP+D]
						_a=GetValue(_sp+_d);
						_a |= ((SWORD)GetValue(_sp+_d+1)) << 8;
						break;

					case 0x19:		// MOV AL,@
						_al=Pipe2.b.l;
						break;

					case 0x1a:		// MOV AL,GL
						_al=_gl;
						break;

					case 0x1b:		// MOV AL,GH
						_al=_gh;
						break;

					case 0x20:		// MOV AL,[SP+@]
						_al=GetValue(_sp+Pipe2.x);
						_pc+=2;
						break;

					case 0x21:		// MOV AL,[SP+D]
						_al=GetValue(_sp+_d);
						break;

					case 0x24:		// MOV AH,GL
						_ah=_gl;
						break;

					case 0x25:		// MOV AH,GH
						_ah=_gh;
						break;

					case 0x27:		// MOV B,G
						_b=_g;
						break;

					case 0x2a:		// MOV D,[D]
						res3.b.l=GetValue(_d);
						res3.b.h=GetValue(_d+1);
						_d=res3.x;
						break;

					case 0x2c:		// MOV B,[SP+@]
						_b=GetValue(_sp+Pipe2.x);
						_b |= ((SWORD)GetValue(_sp+Pipe2.x+1)) << 8;
						_pc+=2;
						break;

					case 0x2f:		// MOV BL,GL
						_bl=_gl;
						break;

					case 0x30:		// MOV BL,GH
						_bl=_gh;
						break;

					case 0x34:		// MOV BL,[SP+@]
						_bl=GetValue(_sp+Pipe2.x);
						_pc+=2;
						break;

					case 0x35:		// MOV BL,[SP+D]
						_bl=GetValue(_sp+_d);
						break;

					case 0x36:		// MOV BH,GL
						_bh=_gl;
						break;

					case 0x37:		// MOV BH,GH
						_bh=_gh;
						break;

					case 0x38:		// MOV C,G
						_c=_g;
						break;

					case 0x39:		// MOV C,B
						_c=_b;
						break;

					case 0x3a:		// MOV CL,GL
						_cl=_gl;
						break;

					case 0x3b:		// MOV D,G
						_d=_g;
						break;

					case 0x3c:		// MOV D,C
						_d=_c;
						break;

					case 0x3d:		// MOV [@],BL
						PutValue(Pipe2.x,_bl);
						_pc+=2;
						break;

					case 0x3e:		// MOV [D],BL
						PutValue(_d,_bl);
						break;

					case 0x42:		// MOV [@],B
						PutValue(Pipe2.x,_bl);
						PutValue(Pipe2.x+1,_bh);
						_pc+=2;
						break;

					case 0x43:		// MOV [D],B
						PutValue(_d,_bl);
						PutValue(_d+1,_bh);
						break;

					case 0x44:		// MOV [D+@],B
						PutValue(_d+Pipe2.x,_bl);
						PutValue(_d+Pipe2.x+1,_bh);
						_pc+=2;
						break;

					case 0x45:		// MOV [SP+@],A
						PutValue(_sp+Pipe2.x,_al);
						PutValue(_sp+Pipe2.x+1,_ah);
						_pc+=2;
						break;

					case 0x46:		// MOV [SP+D],A
						PutValue(_sp+_d,_al);
						PutValue(_sp+_d+1,_ah);
						break;

					case 0x4a:    // CMC
						_flags.Carry=!_flags.Carry;
						break;
                                   
					case 0x51:		// INC SP
						_sp++;
						break;

					case 0x52:		// DEC SP
						_sp--;
						break;

					case 0x53:    // STC
						_flags.Carry=1;
						break;
                                   
					case 0x54:    // CLC
						_flags.Carry=0;
						break;
                                   
					case 0x55:    // ADD A,C
						res1.x=_a;
						res2.x=_c;
						res3.x=res1.x+res2.x;
						_a=res3.x;
    
						goto aggSomma2;
						break;
                                   
					case 0x56:    // ADD A,D
						res1.x=_a;
						res2.x=_d;
						res3.x=res1.x+res2.x;
						_a=res3.x;
    
						goto aggSomma2;
						break;
                                   
					case 0x57:    // ADD B,C
						res1.x=_b;
						res2.x=_c;
						res3.x=res1.x+res2.x;
						_b=res3.x;
    
						goto aggSommaB2;
						break;
                                  
					case 0x58:    // ADD B,D
						res1.x=_b;
						res2.x=_d;
						res3.x=res1.x+res2.x;
						_b=res3.x;
    
						goto aggSommaB2;
						break;
                                   
					case 0x59:    // ADD C,A
						res1.x=_c;
						res2.x=_a;
						res3.x=res1.x+res2.x;
						_c=res3.x;
    
						goto aggSommaC2;
						break;
                                   
					case 0x5a:    // ADD C,B
						res1.x=_c;
						res2.x=_b;
						res3.x=res1.x+res2.x;
						_c=res3.x;
    
						goto aggSommaC2;
						break;
                                   
					case 0x5b:    // ADD C,D
						res1.x=_c;
						res2.x=_d;
						res3.x=res1.x+res2.x;
						_c=res3.x;
    
						goto aggSommaC2;
						break;
                                   
					case 0x5c:    // ADD D,C
						res1.x=_d;
						res2.x=_c;
						res3.x=res1.x+res2.x;
						_d=res3.x;
    
						goto aggSommaD2;
						break;
                                   
					case 0x5d:    // SUB A,C
            res1.d=res2.d=0;
						res1.x=_a;
						res2.x=_c;
						res3.d=res1.d-res2.d;
						_a=res3.x;
        
						goto aggSottr2;
						break;

					case 0x5e:    // SUB A,D
            res1.d=res2.d=0;
						res1.x=_a;
						res2.x=_d;
						res3.d=res1.d-res2.d;
						_a=res3.x;
        
						goto aggSottr2;
						break;

					case 0x5f:    // SUB B,A
            res1.d=res2.d=0;
						res1.x=_b;
						res2.x=_a;
						res3.d=res1.d-res2.d;
						_b=res3.x;
        
						goto aggSottrB2;
						break;

					case 0x60:    // SUB B,C
            res1.d=res2.d=0;
						res1.x=_b;
						res2.x=_c;
						res3.d=res1.d-res2.d;
						_b=res3.x;
        
						goto aggSottrB2;
						break;

					case 0x61:    // SUB B,D
            res1.d=res2.d=0;
						res1.x=_b;
						res2.x=_d;
						res3.d=res1.d-res2.d;
						_b=res3.x;
        
						goto aggSottrB2;
						break;

					case 0x62:    // SUB C,A
            res1.d=res2.d=0;
						res1.x=_c;
						res2.x=_a;
						res3.d=res1.d-res2.d;
						_c=res3.x;
        
						goto aggSottrC2;
						break;

					case 0x63:    // SUB C,B
            res1.d=res2.d=0;
						res1.x=_c;
						res2.x=_b;
						res3.d=res1.d-res2.d;
						_c=res3.x;
        
						goto aggSottrC2;
						break;

					case 0x64:    // SUB C,D
            res1.d=res2.d=0;
						res1.x=_c;
						res2.x=_d;
						res3.d=res1.d-res2.d;
						_c=res3.x;
        
						goto aggSottrC2;
						break;

          case 0x6c:    // ADD BL,AL
            res1.x=res2.x=0;
            res1.b.l=_bl;
            res2.b.l=_al;
            res3.x=res1.x+res2.x;
            _bl=res3.b.l;

            goto aggSomma;
            break;
                                   
					case 0x70:    // OR B,A
						_b |= _a;
						goto aggAnd2;
						break;

					case 0x71:		// SEQ
						;
						break;

					case 0x72:		// SNEQ
						;
						break;

					case 0x73:		// SLT
						;
						break;

					case 0x74:		// SLE
						;
						break;

					case 0x75:		// SLU
						;
						break;

					case 0x76:		// SLEU
						;
						break;

					case 0x77:		// INC B
						_b++;
						break;

					case 0x78:		// MOV G,A
						_g=_a;
						break;

					case 0x79:		// MOV G,B
						_g=_b;
						break;

					case 0x7a:		// MOV G,C
						_g=_c;
						break;

					case 0x7b:		// MOV G,D
						_g=_d;
						break;

					case 0x7c:		// MOV G,SI
						_g=_si;
						break;

					case 0x7d:		// MOV G,DI
						_g=_di;
						break;

//						BUG ********************************
//					case 0x7d:		// DEC B
//						_b--;
//						break;

					case 0x7f:		// SGT
						;
						break;

					case 0x80:		// SGE
						;
						break;

					case 0x81:		// SGU
						;
						break;

					case 0x82:		// SGEU
						;
						break;

					case 0x83:		// MOV CL,GH
						_cl=_gh;
						break;

					case 0x84:    // NAND AL,@
						_al &= Pipe2.b.l;
						_al = ~_al;
            res3.b.l=_al;
						_pc++;
						goto aggAnd;
						break;

					case 0x85:    // NAND A,@
						_a &= Pipe2.x;
						_a = ~_a;
            res3.x=_a;
						_pc+=2;
						goto aggAnd2;
						break;

					case 0x86:    // NAND A,B
						_a &= _b;
						_a = ~_a;
            res3.x=_a;
						goto aggAnd2;
						break;

					case 0x87:    // AND BL,@
						_bl &= Pipe2.b.l;
            res3.b.l=_bl;
						_pc++;
						goto aggAnd;
						break;

					case 0x88:    // NAND AL,BL
						_al &= _bl;
						_al = ~_al;
            res3.b.l=_al;
						goto aggAnd;
						break;

					case 0x8d:    // NOR AL,@
						_al |= Pipe2.b.l;
						_al = ~_al;
            res3.b.l=_al;
						_pc++;
						goto aggAnd;
						break;

					case 0x89:    // NOR A,@
						_a |= Pipe2.x;
						_a = ~_a;
						_pc+=2;
						goto aggAnd2;
						break;

					case 0x8a:    // NOR A,B
						_a |= _b;
						_a = ~_a;
						goto aggAnd2;
						break;

					case 0x8b:    // OR BL,@
						_bl |= Pipe2.b.l;
						_pc++;
						goto aggAnd;
						break;

					case 0x8c:    // NOR AL,BL
						_al |= _bl;
						_al = ~_al;
						goto aggAnd;
						break;

					case 0x8e:		// ASHR B,CL
						res2.b.l=_cl;
            while(res2.b.l) {
              }

						goto aggRotate2;
						break;

					case 0x8f:		// ASHR BL,CL
						res2.b.l=_cl;
            while(res2.b.l) {
              }

						goto aggRotate;
						break;

					case 0x90:		// ASHR B,@

						_pc++;
						goto aggRotate2;
						break;

					case 0x91:		// ASHR BL,@

						_pc++;
						goto aggRotate;
						break;

					case 0x92:    // AND B,A
						_b &= _a;
            res3.x=_a;
						goto aggAnd2;
						break;

					case 0x93:    // TEST BL,@
						res3.b.l = _bl & Pipe2.b.l;
						_pc++;
						goto aggAnd;
						break;

					case 0x94:    // TEST CL,@
						res3.b.l = _cl & Pipe2.b.l;
						goto aggAnd;
						break;

					case 0x95:		// NEG A
						res1.x=0;
						res2.x=_a;
						res3.x=res1.x-res2.x;
						_a=res3.x;
						break;

					case 0x96:		// NEG AL
						res1.b.l=0;
						res2.b.l=_al;
						res3.b.l=res1.b.l-res2.b.l;
						_al=res3.b.l;
						break;

					case 0x97:		// NEG B
						res1.x=0;
						res2.x=_b;
						res3.x=res1.x-res2.x;
						_b=res3.x;
						break;

					case 0x98:		// NEG BL
						res1.b.l=0;
						res2.b.l=_bl;
						res3.b.l=res1.b.l-res2.b.l;
						_bl=res3.b.l;
						break;

					case 0x99:		// SHL A
						_flags.Carry=_a & 0x8000 ? 1 : 0;
						_a <<= 1;
            res3.x=_a;
            goto aggRotate2;
						break;

					case 0x9a:		// SHL AL
						_flags.Carry=_al & 0x80 ? 1 : 0;
						_al <<= 1;
            res3.b.l=_al;
            goto aggRotate;
						break;

					case 0x9b:		// SHR A
						_flags.Carry=_a & 0x0001;
						_a >>= 1;
            res3.x=_a;
            goto aggRotate2;
						break;

					case 0x9c:		// SHR AL
						_flags.Carry=_al & 0x01;
						_al >>= 1;
            res3.b.l=_al;
            goto aggRotate;
						break;

					case 0x9d:		// SHL A,@

						_pc++;
            goto aggRotate2;
						break;

					case 0x9e:		// SHL AL,@

						_pc++;
            goto aggRotate;
						break;

					case 0x9f:		// SHL B,@

						_pc++;
            goto aggRotate2;
						break;

					case 0xa0:		// SHL BL,@
						res2.b.l=_cl;
            while(res2.b.l) {
              }

						_pc++;
            goto aggRotate;
						break;

					case 0xa1:		// SHR A,@

						_pc++;
            goto aggRotate2;
						break;

					case 0xa2:		// SHR AL,@

						_pc++;
            goto aggRotate;
						break;

					case 0xa3:		// SHR B,@

						_pc++;
            goto aggRotate2;
						break;

					case 0xa4:		// SHR BL,@

						_pc++;
            goto aggRotate;
						break;

					case 0xa5:		// ASHR A,@

						_pc++;
						goto aggRotate2;
						break;

					case 0xa6:		// ASHR AL,@

						_pc++;
						goto aggRotate;
						break;

					case 0xa7:		// SAND A,B
						;
						break;

					case 0xa8:		// SOR A,B
						;
						break;

					case 0xa9:		// LOOPB @
						;
						break;

					case 0xaa:		// SWP A
						res3.x=_a;
						_a = MAKELONG(res3.b.h,res3.b.l);
            res3.x=_a;
						break;

					case 0xab:		// SWP B
						res3.x=_b;
						_b = MAKELONG(res3.b.h,res3.b.l);
            res3.x=_b;
						break;

					case 0xac:		// MUL A,C
						res1.x=_a;
						res2.x=_c;
						res3.x=res1.x*res2.x;
						_a=res3.x;

						break;

					case 0xc0:    // CMP B,C
						res1.d=res2.d=0;
						res1.x=_b;
						res2.x=_c;

						goto compare2;
						break;

					case 0xd7:    // PUSH WORD@
						PutValue(--_sp,Pipe2.b.h);
						PutValue(--_sp,Pipe2.b.l);
						_pc+=2;
						break;

					case 0xd8:    // PUSH G
						PutValue(--_sp,_gh);
						PutValue(--_sp,_gl);
						break;

					case 0xdb:    // PUSH BYTE@
						PutValue(--_sp,Pipe2.b.l);
						break;

					case 0xde:		// ROL A,CL
						res2.b.l=_cl;
            while(res2.b.l) {
              }

            goto aggRotate2;
						break;

					case 0xdf:		// ROL AL,CL
						res2.b.l=_cl;
            while(res2.b.l) {
              }

            goto aggRotate;
						break;

					case 0xe0:		// RLC A,CL
						res2.b.l=_cl;
            while(res2.b.l) {
						_flags.Carry=_a & 0x80 ? 1 : 0;
						_a <<= 1;
						_a |= _flags.Carry;
              }

            goto aggRotate2;
						break;

					case 0xe1:		// RLC AL,CL
						res2.b.l=_cl;
            while(res2.b.l) {
						_flags.Carry=_a & 0x80 ? 1 : 0;
						_a <<= 1;
						_a |= _flags.Carry;
              }

            goto aggRotate;
						break;

					case 0xe2:		// ROR A,CL
						res2.b.l=_cl;
            while(res2.b.l) {
              
              }

            goto aggRotate2;
						break;

					case 0xe3:		// ROR AL,CL
						res2.b.l=_cl;
            while(res2.b.l) {
              }

            goto aggRotate;
						break;

					case 0xe4:		// RRC A,CL
						_flags.Carry=_a & 1;
						res2.b.l=_cl;
            while(res2.b.l) {
						_a >>= 1;
						if(_flags.Carry)
							_a |= 0x8000;
              }

            goto aggRotate2;
						break;

					case 0xe5:		// RRC AL,CL
						_flags.Carry=_a & 1;
						res2.b.l=_cl;
            while(res2.b.l) {
						_a >>= 1;
						if(_flags.Carry)
							_a |= 0x80;
              }

            goto aggRotate;
						break;

					case 0xe6:		// ROL B,CL
						res2.b.l=_cl;
            while(res2.b.l) {
              }

            goto aggRotate2;
						break;

					case 0xe7:		// ROL BL,CL
						res2.b.l=_cl;
            while(res2.b.l) {
              }

            goto aggRotate;
						break;

					case 0xe8:		// RLC B,CL
						res2.b.l=_cl;
            while(res2.b.l) {
						_flags.Carry=_a & 0x80 ? 1 : 0;
						_a <<= 1;
						_a |= _flags.Carry;
              }

            goto aggRotate2;
						break;

					case 0xe9:		// RLC BL,CL
						res2.b.l=_cl;
            while(res2.b.l) {
						_flags.Carry=_a & 0x80 ? 1 : 0;
						_a <<= 1;
						_a |= _flags.Carry;
              }

            goto aggRotate;
						break;

					case 0xea:		// ROR B,CL
						res2.b.l=_cl;
            while(res2.b.l) {
              }

            goto aggRotate2;
						break;

					case 0xeb:		// ROR BL,CL
						res2.b.l=_cl;
            while(res2.b.l) {
              }

            goto aggRotate;
						break;

					case 0xec:		// RRC B,CL
						_flags.Carry=_a & 1;
						_a >>= 1;
						if(_flags.Carry)
							_a |= 0x8000;

            goto aggRotate2;
						break;

					case 0xed:		// RRC BL,CL
						_flags.Carry=_a & 1;
						_a >>= 1;
						if(_flags.Carry)
							_a |= 0x80;

            goto aggRotate;
						break;

					case 0xf1:    // POP G
						_g=GetValue(_sp++);
						_g |= ((SWORD)GetValue(_sp++)) << 8;
						break;

					case 0xf3:    // REPZ CMPSB (REPE)
						res1.b.l=_a;
						res2.b.l=GetValue(_c++);
            _d--;
						if(res1.b.l != res2.b.l) {
              if(_d) 
                _pc-=2;			// così ripeto e consento IRQ...
              }
            goto aggCPI;    // 
						break;

					case 0xf6:    // REPNZ CMPSB (REPNE)
						res1.b.l=_a;
						res2.b.l=GetValue(_c++);
            _d--;
						if(res1.b.l != res2.b.l) {
              if(_d) 
                _pc-=2;			// così ripeto e consento IRQ...
              }
            goto aggCPI;    // 
						break;

					case 0xf5:    // REP MOVSB
						PutValue(_b++,GetValue(_c++));
						_d--;
						if(_d)
							_pc-=2;			// così ripeto e consento IRQ...
            _flags.AddSub=_flags.HalfCarry=0;
            _flags.PV=0;
						break;

					case 0xf7:    // REP STOSB
						PutValue(_b++,GetValue(_c++));
						_d--;
						if(_d)
							_pc-=2;			// così ripeto e consento IRQ...
            _flags.AddSub=_flags.HalfCarry=0;
            _flags.PV=0;
						break;

					case 0xf9:    // LEA D,[@+A*2^+@+B]; LEA D,[BP+A*2^+@+B]
						GetPipe(_pc++);

						_pc+=3;
						break;

					case 0xfa:    // LEA D,[SP+@]
						GetPipe(_pc++);
						_d=_sp+Pipe2.x;
						_pc+=2;
						break;
					}
				break;

			case 0xfe:    // NOP
				break;

			case 0xff:    // HALT
			  DoHalt=1;
				break;

			}
		} while(!fExit);
	}


