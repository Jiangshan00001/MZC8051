SPSTAT      DATA    0CDH
SPCTL       DATA    0CEH
SPDAT       DATA    0CFH
IE2         DATA    0AFH
ESPI        EQU     02H

BUSY        BIT     20H.0
SS          BIT     P1.0
LED         BIT     P1.1

            ORG     0000H
            LJMP    MAIN
            ORG     004BH
            LJMP    SPIISR

            ORG     0100H
SPIISR:
            MOV     SPSTAT,#0C0H                ;清中断标志
            SETB    SS                          ;拉高从机的SS管脚
            CLR     BUSY
            CPL     LED
            RETI

MAIN:
            MOV     SP,#3FH

            SETB    LED
            SETB    SS
            CLR     BUSY

            MOV     SPCTL,#50H                  ;使能SPI主机模式
            MOV     SPSTAT,#0C0H                ;清中断标志
            MOV     IE2,#ESPI                   ;使能SPI中断
            SETB    EA

LOOP:
            JB      BUSY,$
            SETB    BUSY
            CLR     SS                          ;拉低从机SS管脚
            MOV     SPDAT,#5AH                  ;发送测试数据
            JMP     LOOP

            END

