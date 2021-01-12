P_SW1       DATA    0A2H

            ORG     0000H
            LJMP    MAIN

            ORG     0100H
MAIN:
            MOV     SP, #3FH

            MOV     P_SW1,#00H                  ;RXD/P3.0,TXD/P3.1
;           MOV     P_SW1,#40H                  ;RXD_2/P3.6,TXD_2/P3.7
;           MOV     P_SW1,#80H                  ;RXD_3/P1.6,TXD_3/P1.7
;           MOV     P_SW1,#0C0H                 ;RXD_4/P4.3,TXD_4/P4.4

            SJMP    $

            END

