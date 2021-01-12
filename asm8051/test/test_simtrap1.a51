ORG 0H
LJMP M1

M1:
MOV A, #0;
SIMTRAP 0x00, 0x00;//failed
MOV A, #1;
SIMTRAP 0x00, 0x00;//success
SIMTRAP 0x01, 0x00;//exit