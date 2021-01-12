P_SW2       DATA    0BAH

I2CCFG      XDATA   0FE80H
I2CMSCR     XDATA   0FE81H
I2CMSST     XDATA   0FE82H
I2CSLCR     XDATA   0FE83H
I2CSLST     XDATA   0FE84H
I2CSLADR    XDATA   0FE85H
I2CTXD      XDATA   0FE86H
I2CRXD      XDATA   0FE87H

SDA         BIT     P1.4
SCL         BIT     P1.5

BUSY        BIT     20H.0

            ORG     0000H
            LJMP    MAIN
            ORG     00C3H
            LJMP    I2CISR
            
            ORG     0100H
I2CISR:
            PUSH    ACC
            PUSH    DPL
            PUSH    DPH

            MOV     DPTR,#I2CMSST               ;清中断标志
            MOVX    A,@DPTR
            ANL     A,#NOT 40H
            MOV     DPTR,#I2CMSST
            MOVX    @DPTR,A
            CLR     BUSY                        ;复位忙标志

            POP     DPH
            POP     DPL
            POP     ACC
            RETI

START:
            SETB    BUSY
            MOV     A,#10000001B                ;发送START命令
            MOV     DPTR,#I2CMSCR
            MOVX    @DPTR,A
            JMP     WAIT
SENDDATA:
            MOV     DPTR,#I2CTXD                ;写数据到数据缓冲区
            MOVX    @DPTR,A
            SETB    BUSY
            MOV     A,#10000010B                ;发送SEND命令
            MOV     DPTR,#I2CMSCR
            MOVX    @DPTR,A
            JMP     WAIT
RECVACK:
            SETB    BUSY
            MOV     A,#10000011B                ;发送读ACK命令
            MOV     DPTR,#I2CMSCR
            MOVX    @DPTR,A
            JMP     WAIT
RECVDATA:
            SETB    BUSY
            MOV     A,#10000100B                ;发送RECV命令
            MOV     DPTR,#I2CMSCR
            MOVX    @DPTR,A
            CALL    WAIT
            MOV     DPTR,#I2CRXD                ;从数据缓冲区读取数据
            MOVX    A,@DPTR
            RET
SENDACK:
            MOV     A,#00000000B                ;设置ACK信号
            MOV     DPTR,#I2CMSST
            MOVX    @DPTR,A
            SETB    BUSY
            MOV     A,#10000101B                ;发送ACK命令
            MOV     DPTR,#I2CMSCR
            MOVX    @DPTR,A
            JMP     WAIT
SENDNAK:
            MOV     A,#00000001B                ;设置NAK信号
            MOV     DPTR,#I2CMSST
            MOVX    @DPTR,A
            SETB    BUSY
            MOV     A,#10000101B                ;发送ACK命令
            MOV     DPTR,#I2CMSCR
            MOVX    @DPTR,A
            JMP     WAIT
STOP:
            SETB    BUSY
            MOV     A,#10000110B                ;发送STOP命令
            MOV     DPTR,#I2CMSCR
            MOVX    @DPTR,A
            JMP     WAIT
WAIT:
            JB      BUSY,$                      ;等待命令发送完成
            RET

DELAY:
            MOV     R0,#0
            MOV     R1,#0
DELAY1:
            NOP
            NOP
            NOP
            NOP
            DJNZ    R1,DELAY1
            DJNZ    R0,DELAY1
            RET
            
MAIN:
            MOV     SP,#3FH
            MOV     P_SW2,#80H
            
            MOV     A,#11100000B                ;设置I2C模块为主机模式
            MOV     DPTR,#I2CCFG
            MOVX    @DPTR,A
            MOV     A,#00000000B
            MOV     DPTR,#I2CMSST
            MOVX    @DPTR,A
            SETB    EA

            CALL    START                       ;发送起始命令
            MOV     A,#0A0H
            CALL    SENDDATA                    ;发送设备地址+写命令
            CALL    RECVACK
            MOV     A,#000H                     ;发送存储地址高字节
            CALL    SENDDATA
            CALL    RECVACK
            MOV     A,#000H                     ;发送存储地址低字节
            CALL    SENDDATA
            CALL    RECVACK
            MOV     A,#12H                      ;写测试数据1
            CALL    SENDDATA
            CALL    RECVACK
            MOV     A,#78H                      ;写测试数据2
            CALL    SENDDATA
            CALL    RECVACK
            CALL    STOP                        ;发送停止命令
            
            CALL    DELAY                       ;等待设备写数据
            
            CALL    START                       ;发送起始命令
            MOV     A,#0A0H                     ;发送设备地址+写命令
            CALL    SENDDATA
            CALL    RECVACK
            MOV     A,#000H                     ;发送存储地址高字节
            CALL    SENDDATA
            CALL    RECVACK
            MOV     A,#000H                     ;发送存储地址低字节
            CALL    SENDDATA
            CALL    RECVACK
            CALL    START                       ;发送起始命令
            MOV     A,#0A1H                     ;发送设备地址+读命令
            CALL    SENDDATA
            CALL    RECVACK
            CALL    RECVDATA                    ;读取数据1
            MOV     P0,A
            CALL    SENDACK
            CALL    RECVDATA                    ;读取数据2
            MOV     P2,A
            CALL    SENDNAK
            CALL    STOP                        ;发送停止命令
            
            JMP     $
            
            END

