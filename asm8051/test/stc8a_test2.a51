AUXR	DATA	8EH
BGV	DATA	0EFH

BUSY	BIT	20H.0

	ORG	0000H
	LJMP	MAIN
	ORG	0023H
	LJMP	UART_ISR

	ORG	0100H

UART_ISR:
	JNB	TI,CHKRI
	CLR	TI
	CLR	BUSY
CHKRI:
	JNB	RI,UARTISR_EXIT
	CLR	RI
UARTISR_EXIT:
	RETI

UART_INIT:
	MOV	SCON,#50H
	MOV	TMOD,#00H
	MOV	TL1,#0E8H	;65536-11059200/115200/4=0FFE8H
	MOV	TH1,#0FFH
	SETB	TR1
	MOV	AUXR,#40H
	CLR	BUSY
	RET

UART_SEND:
	JB	BUSY,$
	SETB	BUSY
	MOV	SBUF,A
	RET

MAIN:
	MOV	SP,#3FH

	LCALL	UART_INIT
	SETB	ES
	SETB	EA

	MOV	R0,#BGV
	MOV	A,@R0	;读取Bandgap电压的高字节
	LCALL	UART_SEND
	INC	R0
	MOV	A,@R0	;读取Bandgap电压的低字节
	LCALL	UART_SEND

LOOP:
	JMP	LOOP

	END

