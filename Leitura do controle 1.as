opt subtitle "HI-TECH Software Omniscient Code Generator (Lite mode) build 10920"

opt pagewidth 120

	opt lm

	processor	16F628A
clrc	macro
	bcf	3,0
	endm
clrz	macro
	bcf	3,2
	endm
setc	macro
	bsf	3,0
	endm
setz	macro
	bsf	3,2
	endm
skipc	macro
	btfss	3,0
	endm
skipz	macro
	btfss	3,2
	endm
skipnc	macro
	btfsc	3,0
	endm
skipnz	macro
	btfsc	3,2
	endm
indf	equ	0
indf0	equ	0
pc	equ	2
pcl	equ	2
status	equ	3
fsr	equ	4
fsr0	equ	4
c	equ	1
z	equ	0
pclath	equ	10
# 8 "D:\Usuários\Eduardo\Documentos\PIC\Leitura do controle 1\main.c"
	psect config,class=CONFIG,delta=2 ;#
# 8 "D:\Usuários\Eduardo\Documentos\PIC\Leitura do controle 1\main.c"
	dw 0x3FFD & 0x3FFB & 0x3FF7 & 0x3FDF & 0x3F7F & 0x3FFF ;#
	FNCALL	_main,_calculate_pulse_width
	FNROOT	_main
	FNCALL	intlevel1,_interruptions
	global	intlevel1
	FNROOT	intlevel1
	global	_interval
	global	_fl_exit
	global	_TMR1
psect	text82,local,class=CODE,delta=2
global __ptext82
__ptext82:
_TMR1	set	14
	global	_CCP1CON
_CCP1CON	set	23
	global	_INTCON
_INTCON	set	11
	global	_T1CON
_T1CON	set	16
	global	_CARRY
_CARRY	set	24
	global	_GIE
_GIE	set	95
	global	_RB0
_RB0	set	48
	global	_RB1
_RB1	set	49
	global	_RB2
_RB2	set	50
	global	_RB3
_RB3	set	51
	global	_RB4
_RB4	set	52
	global	_RBIE
_RBIE	set	91
	global	_RBIF
_RBIF	set	88
	global	_TMR1ON
_TMR1ON	set	128
	global	_EEADR
_EEADR	set	155
	global	_EECON1
_EECON1	set	156
	global	_EECON2
_EECON2	set	157
	global	_EEDATA
_EEDATA	set	154
	global	_OPTION
_OPTION	set	129
	global	_TRISB
_TRISB	set	134
	global	_RD
_RD	set	1248
	global	_WR
_WR	set	1249
	global	_WREN
_WREN	set	1250
	file	"Leitura do controle 1.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

psect	bssCOMMON,class=COMMON,space=1
global __pbssCOMMON
__pbssCOMMON:
_interval:
       ds      4

_fl_exit:
       ds      2

; Clear objects allocated to COMMON
psect cinit,class=CODE,delta=2
	clrf	((__pbssCOMMON)+0)&07Fh
	clrf	((__pbssCOMMON)+1)&07Fh
	clrf	((__pbssCOMMON)+2)&07Fh
	clrf	((__pbssCOMMON)+3)&07Fh
	clrf	((__pbssCOMMON)+4)&07Fh
	clrf	((__pbssCOMMON)+5)&07Fh
psect cinit,class=CODE,delta=2
global end_of_initialization

;End of C runtime variable initialization code

end_of_initialization:
clrf status
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1
global __pcstackCOMMON
__pcstackCOMMON:
	global	?_calculate_pulse_width
?_calculate_pulse_width:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 0 bytes @ 0x0
	global	??_interruptions
??_interruptions:	; 0 bytes @ 0x0
	global	?_interruptions
?_interruptions:	; 2 bytes @ 0x0
	ds	4
	global	??_calculate_pulse_width
??_calculate_pulse_width:	; 0 bytes @ 0x4
	global	??_main
??_main:	; 0 bytes @ 0x4
;;Data sizes: Strings 0, constant 0, data 0, bss 6, persistent 0 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14      4      10
;; BANK0           80      0       0
;; BANK1           80      0       0
;; BANK2           48      0       0

;;
;; Pointer list with targets:



;;
;; Critical Paths under _main in COMMON
;;
;;   None.
;;
;; Critical Paths under _interruptions in COMMON
;;
;;   None.
;;
;; Critical Paths under _main in BANK0
;;
;;   None.
;;
;; Critical Paths under _interruptions in BANK0
;;
;;   None.
;;
;; Critical Paths under _main in BANK1
;;
;;   None.
;;
;; Critical Paths under _interruptions in BANK1
;;
;;   None.
;;
;; Critical Paths under _main in BANK2
;;
;;   None.
;;
;; Critical Paths under _interruptions in BANK2
;;
;;   None.

;;
;;Main: autosize = 0, tempsize = 0, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                 0     0      0       0
;;              _calculate_pulse_width
;; ---------------------------------------------------------------------------------
;; (1) _calculate_pulse_width                                0     0      0       0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 1
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (2) _interruptions                                        4     4      0       0
;;                                              0 COMMON     4     4      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 2
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _calculate_pulse_width
;;
;; _interruptions (ROOT)
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON            E      0       0       0        0.0%
;;EEDATA              80      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;COMMON               E      4       A       1       71.4%
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;STACK                0      0       1       2        0.0%
;;BANK0               50      0       0       3        0.0%
;;BITSFR3              0      0       0       4        0.0%
;;SFR3                 0      0       0       4        0.0%
;;ABS                  0      0       A       4        0.0%
;;BITBANK0            50      0       0       5        0.0%
;;BITSFR2              0      0       0       5        0.0%
;;SFR2                 0      0       0       5        0.0%
;;BITBANK1            50      0       0       6        0.0%
;;BANK1               50      0       0       7        0.0%
;;BITBANK2            30      0       0       8        0.0%
;;BANK2               30      0       0       9        0.0%
;;DATA                 0      0       B      10        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 19 in file "D:\Usuários\Eduardo\Documentos\PIC\Leitura do controle 1\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          0       0       0       0
;;      Totals:         0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_calculate_pulse_width
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"D:\Usuários\Eduardo\Documentos\PIC\Leitura do controle 1\main.c"
	line	19
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 6
; Regs used in _main: [wreg+status,2+status,0+pclath+cstack]
	line	22
	
l2073:	
;main.c: 22: TRISB = 0b00010000;
	movlw	(010h)
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	movwf	(134)^080h	;volatile
	line	25
;main.c: 25: OPTION = 0b11010000;
	movlw	(0D0h)
	movwf	(129)^080h	;volatile
	line	28
;main.c: 28: INTCON = 0b10000000;
	movlw	(080h)
	movwf	(11)	;volatile
	line	31
	
l2075:	
;main.c: 31: T1CON = 0b00000000;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(16)	;volatile
	line	34
	
l2077:	
;main.c: 34: CCP1CON = 0b00000100;
	movlw	(04h)
	movwf	(23)	;volatile
	line	36
	
l2079:	
;main.c: 36: RBIE = 0;
	bcf	(91/8),(91)&7
	line	37
;main.c: 37: TMR1 = 0;
	clrf	(14)	;volatile
	clrf	(14+1)	;volatile
	line	39
	
l2081:	
;main.c: 39: RB0 = 0;
	bcf	(48/8),(48)&7
	line	40
	
l2083:	
;main.c: 40: RB1 = 0;
	bcf	(49/8),(49)&7
	line	41
	
l2085:	
;main.c: 41: RB2 = 0;
	bcf	(50/8),(50)&7
	line	42
	
l2087:	
;main.c: 42: RB3 = 1;
	bsf	(51/8),(51)&7
	goto	l2089
	line	43
;main.c: 43: while (1) {
	
l397:	
	line	45
	
l2089:	
;main.c: 45: calculate_pulse_width();
	fcall	_calculate_pulse_width
	line	47
	
l2091:	
;main.c: 47: if (interval < 1250) {
	movlw	0
	subwf	(_interval+3),w
	skipz
	goto	u2265
	movlw	0
	subwf	(_interval+2),w
	skipz
	goto	u2265
	movlw	04h
	subwf	(_interval+1),w
	skipz
	goto	u2265
	movlw	0E2h
	subwf	(_interval),w
u2265:
	skipnc
	goto	u2261
	goto	u2260
u2261:
	goto	l2095
u2260:
	line	48
	
l2093:	
;main.c: 48: RB0 = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(48/8),(48)&7
	line	49
;main.c: 49: RB1 = 0;
	bcf	(49/8),(49)&7
	line	50
;main.c: 50: RB2 = 0;
	bcf	(50/8),(50)&7
	line	51
;main.c: 51: } else if (interval < 1500) {
	goto	l2089
	
l398:	
	
l2095:	
	movlw	0
	subwf	(_interval+3),w
	skipz
	goto	u2275
	movlw	0
	subwf	(_interval+2),w
	skipz
	goto	u2275
	movlw	05h
	subwf	(_interval+1),w
	skipz
	goto	u2275
	movlw	0DCh
	subwf	(_interval),w
u2275:
	skipnc
	goto	u2271
	goto	u2270
u2271:
	goto	l2099
u2270:
	line	52
	
l2097:	
;main.c: 52: RB0 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(48/8),(48)&7
	line	53
;main.c: 53: RB1 = 0;
	bcf	(49/8),(49)&7
	line	54
;main.c: 54: RB2 = 0;
	bcf	(50/8),(50)&7
	line	55
;main.c: 55: } else if (interval < 1750) {
	goto	l2089
	
l400:	
	
l2099:	
	movlw	0
	subwf	(_interval+3),w
	skipz
	goto	u2285
	movlw	0
	subwf	(_interval+2),w
	skipz
	goto	u2285
	movlw	06h
	subwf	(_interval+1),w
	skipz
	goto	u2285
	movlw	0D6h
	subwf	(_interval),w
u2285:
	skipnc
	goto	u2281
	goto	u2280
u2281:
	goto	l2103
u2280:
	line	56
	
l2101:	
;main.c: 56: RB0 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(48/8),(48)&7
	line	57
;main.c: 57: RB1 = 1;
	bsf	(49/8),(49)&7
	line	58
;main.c: 58: RB2 = 0;
	bcf	(50/8),(50)&7
	line	59
;main.c: 59: } else if (interval < 2100) {
	goto	l2089
	
l402:	
	
l2103:	
	movlw	0
	subwf	(_interval+3),w
	skipz
	goto	u2295
	movlw	0
	subwf	(_interval+2),w
	skipz
	goto	u2295
	movlw	08h
	subwf	(_interval+1),w
	skipz
	goto	u2295
	movlw	034h
	subwf	(_interval),w
u2295:
	skipnc
	goto	u2291
	goto	u2290
u2291:
	goto	l2089
u2290:
	line	60
	
l2105:	
;main.c: 60: RB0 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(48/8),(48)&7
	line	61
;main.c: 61: RB1 = 1;
	bsf	(49/8),(49)&7
	line	62
;main.c: 62: RB2 = 1;
	bsf	(50/8),(50)&7
	goto	l2089
	line	63
	
l404:	
	goto	l2089
	line	64
	
l403:	
	goto	l2089
	
l401:	
	goto	l2089
	
l399:	
	goto	l2089
	
l405:	
	line	43
	goto	l2089
	
l406:	
	line	65
	
l407:	
	global	start
	ljmp	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,88
	global	_calculate_pulse_width
psect	text83,local,class=CODE,delta=2
global __ptext83
__ptext83:

;; *************** function _calculate_pulse_width *****************
;; Defined at:
;;		line 84 in file "D:\Usuários\Eduardo\Documentos\PIC\Leitura do controle 1\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          0       0       0       0
;;      Totals:         0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text83
	file	"D:\Usuários\Eduardo\Documentos\PIC\Leitura do controle 1\main.c"
	line	84
	global	__size_of_calculate_pulse_width
	__size_of_calculate_pulse_width	equ	__end_of_calculate_pulse_width-_calculate_pulse_width
	
_calculate_pulse_width:	
	opt	stack 6
; Regs used in _calculate_pulse_width: [wreg+status,2]
	line	86
	
l1193:	
;main.c: 86: RBIF = 0;
	bcf	(88/8),(88)&7
	line	87
;main.c: 87: while (RB4);
	goto	l416
	
l417:	
	
l416:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfsc	(52/8),(52)&7
	goto	u11
	goto	u10
u11:
	goto	l416
u10:
	
l418:	
	line	90
;main.c: 90: RBIE = 1;
	bsf	(91/8),(91)&7
	line	92
;main.c: 92: while (!fl_exit);
	goto	l1195
	
l420:	
	goto	l1195
	
l419:	
	
l1195:	
	movf	(_fl_exit+1),w
	iorwf	(_fl_exit),w
	skipnz
	goto	u21
	goto	u20
u21:
	goto	l1195
u20:
	goto	l1197
	
l421:	
	line	93
	
l1197:	
;main.c: 93: fl_exit = 0;
	clrf	(_fl_exit)
	clrf	(_fl_exit+1)
	line	96
	
l1199:	
;main.c: 96: RBIE = 0;
	bcf	(91/8),(91)&7
	line	97
	
l422:	
	return
	opt stack 0
GLOBAL	__end_of_calculate_pulse_width
	__end_of_calculate_pulse_width:
;; =============== function _calculate_pulse_width ends ============

	signat	_calculate_pulse_width,88
	global	_interruptions
psect	text84,local,class=CODE,delta=2
global __ptext84
__ptext84:

;; *************** function _interruptions *****************
;; Defined at:
;;		line 68 in file "D:\Usuários\Eduardo\Documentos\PIC\Leitura do controle 1\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  2  409[COMMON] int 
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          4       0       0       0
;;      Totals:         4       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Interrupt level 1
;; This function uses a non-reentrant model
;;
psect	text84
	file	"D:\Usuários\Eduardo\Documentos\PIC\Leitura do controle 1\main.c"
	line	68
	global	__size_of_interruptions
	__size_of_interruptions	equ	__end_of_interruptions-_interruptions
	
_interruptions:	
	opt	stack 6
; Regs used in _interruptions: [wreg+status,2]
psect	intentry,class=CODE,delta=2
global __pintentry
__pintentry:
global interrupt_function
interrupt_function:
	global saved_w
	saved_w	set	btemp+0
	movwf	saved_w
	swapf	status,w
	movwf	(??_interruptions+0)
	movf	fsr0,w
	movwf	(??_interruptions+1)
	movf	pclath,w
	movwf	(??_interruptions+2)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	btemp+1,w
	movwf	(??_interruptions+3)
	ljmp	_interruptions
psect	text84
	line	70
	
i1l1201:	
;main.c: 70: if (RBIF) {
	btfss	(88/8),(88)&7
	goto	u3_21
	goto	u3_20
u3_21:
	goto	i1l413
u3_20:
	line	71
	
i1l1203:	
;main.c: 71: if (RB4) {
	btfss	(52/8),(52)&7
	goto	u4_21
	goto	u4_20
u4_21:
	goto	i1l411
u4_20:
	line	72
	
i1l1205:	
;main.c: 72: TMR1ON = 1;
	bsf	(128/8),(128)&7
	line	73
;main.c: 73: RBIF = 0;
	bcf	(88/8),(88)&7
	line	74
;main.c: 74: } else {
	goto	i1l413
	
i1l411:	
	line	75
;main.c: 75: TMR1ON = 0;
	bcf	(128/8),(128)&7
	line	76
	
i1l1207:	
;main.c: 76: interval = TMR1;
	movf	(14),w	;volatile
	movwf	(_interval)
	movf	(14+1),w	;volatile
	movwf	((_interval))+1
	clrf	2+((_interval))
	clrf	3+((_interval))
	line	77
	
i1l1209:	
;main.c: 77: TMR1 = 0;
	clrf	(14)	;volatile
	clrf	(14+1)	;volatile
	line	78
	
i1l1211:	
;main.c: 78: RBIF = 0;
	bcf	(88/8),(88)&7
	line	79
	
i1l1213:	
;main.c: 79: fl_exit = 1;
	movlw	low(01h)
	movwf	(_fl_exit)
	movlw	high(01h)
	movwf	((_fl_exit))+1
	goto	i1l413
	line	80
	
i1l412:	
	goto	i1l413
	line	81
	
i1l410:	
	line	82
	
i1l413:	
	movf	(??_interruptions+3),w
	movwf	btemp+1
	movf	(??_interruptions+2),w
	movwf	pclath
	movf	(??_interruptions+1),w
	movwf	fsr0
	swapf	(??_interruptions+0)^0FFFFFF80h,w
	movwf	status
	swapf	saved_w,f
	swapf	saved_w,w
	retfie
	opt stack 0
GLOBAL	__end_of_interruptions
	__end_of_interruptions:
;; =============== function _interruptions ends ============

	signat	_interruptions,90
psect	text85,local,class=CODE,delta=2
global __ptext85
__ptext85:
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
