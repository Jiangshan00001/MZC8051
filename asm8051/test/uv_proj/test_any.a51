ORG 0000H; program entry
LJMP __main_before;
__main_before:
MOV 0x81, #0x7f; sp<-#0x7f
LJMP _func_main;
__MAIN_ALL_END_HERE:
SJMP __MAIN_ALL_END_HERE;
;DEF_VAR: P0, bw:8, type:sfr, tt:1, addr:0x1ffff//6

;OPR: =, ICONST(0x80,8,9);, null;, SYM_REF(name:P0, num:6)

;DEF_VAR: P1, bw:8, type:sfr, tt:1, addr:0x1ffff//12

;OPR: =, ICONST(0x90,8,15);, null;, SYM_REF(name:P1, num:18)

;DEF_VAR: P2, bw:8, type:sfr, tt:1, addr:0x1ffff//1e

;OPR: =, ICONST(0xa0,8,21);, null;, SYM_REF(name:P2, num:30)

;DEF_VAR: P3, bw:8, type:sfr, tt:1, addr:0x1ffff//2a

;OPR: =, ICONST(0xb0,8,2d);, null;, SYM_REF(name:P3, num:42)

;DEF_VAR: PSW, bw:8, type:sfr, tt:1, addr:0x1ffff//36

;OPR: =, ICONST(0xd0,8,39);, null;, SYM_REF(name:PSW, num:54)

;DEF_VAR: ACC, bw:8, type:sfr, tt:1, addr:0x1ffff//42

;OPR: =, ICONST(0xe0,8,45);, null;, SYM_REF(name:ACC, num:66)

;DEF_VAR: B, bw:8, type:sfr, tt:1, addr:0x1ffff//4e

;OPR: =, ICONST(0xf0,8,51);, null;, SYM_REF(name:B, num:78)

;DEF_VAR: SP, bw:8, type:sfr, tt:1, addr:0x1ffff//5a

;OPR: =, ICONST(0x81,8,5d);, null;, SYM_REF(name:SP, num:90)

;DEF_VAR: DPL, bw:8, type:sfr, tt:1, addr:0x1ffff//66

;OPR: =, ICONST(0x82,8,69);, null;, SYM_REF(name:DPL, num:102)

;DEF_VAR: DPH, bw:8, type:sfr, tt:1, addr:0x1ffff//72

;OPR: =, ICONST(0x83,8,75);, null;, SYM_REF(name:DPH, num:114)

;DEF_VAR: PCON, bw:8, type:sfr, tt:1, addr:0x1ffff//7e

;OPR: =, ICONST(0x87,8,81);, null;, SYM_REF(name:PCON, num:126)

;DEF_VAR: TCON, bw:8, type:sfr, tt:1, addr:0x1ffff//8a

;OPR: =, ICONST(0x88,8,8d);, null;, SYM_REF(name:TCON, num:138)

;DEF_VAR: TMOD, bw:8, type:sfr, tt:1, addr:0x1ffff//96

;OPR: =, ICONST(0x89,8,99);, null;, SYM_REF(name:TMOD, num:150)

;DEF_VAR: TL0, bw:8, type:sfr, tt:1, addr:0x1ffff//a2

;OPR: =, ICONST(0x8a,8,a5);, null;, SYM_REF(name:TL0, num:162)

;DEF_VAR: TL1, bw:8, type:sfr, tt:1, addr:0x1ffff//ae

;OPR: =, ICONST(0x8b,8,b1);, null;, SYM_REF(name:TL1, num:174)

;DEF_VAR: TH0, bw:8, type:sfr, tt:1, addr:0x1ffff//ba

;OPR: =, ICONST(0x8c,8,bd);, null;, SYM_REF(name:TH0, num:186)

;DEF_VAR: TH1, bw:8, type:sfr, tt:1, addr:0x1ffff//c6

;OPR: =, ICONST(0x8d,8,c9);, null;, SYM_REF(name:TH1, num:198)

;DEF_VAR: IE, bw:8, type:sfr, tt:1, addr:0x1ffff//d2

;OPR: =, ICONST(0xa8,8,d5);, null;, SYM_REF(name:IE, num:210)

;DEF_VAR: IP, bw:8, type:sfr, tt:1, addr:0x1ffff//de

;OPR: =, ICONST(0xb8,8,e1);, null;, SYM_REF(name:IP, num:222)

;DEF_VAR: SCON, bw:8, type:sfr, tt:1, addr:0x1ffff//ea

;OPR: =, ICONST(0x98,8,ed);, null;, SYM_REF(name:SCON, num:234)

;DEF_VAR: SBUF, bw:8, type:sfr, tt:1, addr:0x1ffff//f6

;OPR: =, ICONST(0x99,8,f9);, null;, SYM_REF(name:SBUF, num:246)

;DEF_VAR: T2CON, bw:8, type:sfr, tt:1, addr:0x1ffff//102

;OPR: =, ICONST(0xc8,8,105);, null;, SYM_REF(name:T2CON, num:258)

;DEF_VAR: RCAP2L, bw:8, type:sfr, tt:1, addr:0x1ffff//10e

;OPR: =, ICONST(0xca,8,111);, null;, SYM_REF(name:RCAP2L, num:270)

;DEF_VAR: RCAP2H, bw:8, type:sfr, tt:1, addr:0x1ffff//11a

;OPR: =, ICONST(0xcb,8,11d);, null;, SYM_REF(name:RCAP2H, num:282)

;DEF_VAR: TL2, bw:8, type:sfr, tt:1, addr:0x1ffff//126

;OPR: =, ICONST(0xcc,8,129);, null;, SYM_REF(name:TL2, num:294)

;DEF_VAR: TH2, bw:8, type:sfr, tt:1, addr:0x1ffff//132

;OPR: =, ICONST(0xcd,8,135);, null;, SYM_REF(name:TH2, num:306)

;DEF_VAR: CY, bw:1, type:sbit, tt:6, addr:0x1ffff//13e

;OPR: ^, SYM_REF(name:PSW, num:54);, ICONST(0x7,8,145);, SYM_REF(name:CY, num:318)

;DEF_VAR: AC, bw:1, type:sbit, tt:6, addr:0x1ffff//14d

;OPR: ^, SYM_REF(name:PSW, num:54);, ICONST(0x6,8,154);, SYM_REF(name:AC, num:333)

;DEF_VAR: F0, bw:1, type:sbit, tt:6, addr:0x1ffff//15c

;OPR: ^, SYM_REF(name:PSW, num:54);, ICONST(0x5,8,163);, SYM_REF(name:F0, num:348)

;DEF_VAR: RS1, bw:1, type:sbit, tt:6, addr:0x1ffff//16b

;OPR: ^, SYM_REF(name:PSW, num:54);, ICONST(0x4,8,172);, SYM_REF(name:RS1, num:363)

;DEF_VAR: RS0, bw:1, type:sbit, tt:6, addr:0x1ffff//17a

;OPR: ^, SYM_REF(name:PSW, num:54);, ICONST(0x3,8,181);, SYM_REF(name:RS0, num:378)

;DEF_VAR: OV, bw:1, type:sbit, tt:6, addr:0x1ffff//189

;OPR: ^, SYM_REF(name:PSW, num:54);, ICONST(0x2,8,190);, SYM_REF(name:OV, num:393)

;DEF_VAR: P, bw:1, type:sbit, tt:6, addr:0x1ffff//198

;OPR: ^, SYM_REF(name:PSW, num:54);, ICONST(0x0,8,19f);, SYM_REF(name:P, num:408)

;DEF_VAR: TF1, bw:1, type:sbit, tt:6, addr:0x1ffff//1a7

;OPR: ^, SYM_REF(name:TCON, num:138);, ICONST(0x7,8,1ae);, SYM_REF(name:TF1, num:423)

;DEF_VAR: TR1, bw:1, type:sbit, tt:6, addr:0x1ffff//1b6

;OPR: ^, SYM_REF(name:TCON, num:138);, ICONST(0x6,8,1bd);, SYM_REF(name:TR1, num:438)

;DEF_VAR: TF0, bw:1, type:sbit, tt:6, addr:0x1ffff//1c5

;OPR: ^, SYM_REF(name:TCON, num:138);, ICONST(0x5,8,1cc);, SYM_REF(name:TF0, num:453)

;DEF_VAR: TR0, bw:1, type:sbit, tt:6, addr:0x1ffff//1d4

;OPR: ^, SYM_REF(name:TCON, num:138);, ICONST(0x4,8,1db);, SYM_REF(name:TR0, num:468)

;DEF_VAR: IE1, bw:1, type:sbit, tt:6, addr:0x1ffff//1e3

;OPR: ^, SYM_REF(name:TCON, num:138);, ICONST(0x3,8,1ea);, SYM_REF(name:IE1, num:483)

;DEF_VAR: IT1, bw:1, type:sbit, tt:6, addr:0x1ffff//1f2

;OPR: ^, SYM_REF(name:TCON, num:138);, ICONST(0x2,8,1f9);, SYM_REF(name:IT1, num:498)

;DEF_VAR: IE0, bw:1, type:sbit, tt:6, addr:0x1ffff//201

;OPR: ^, SYM_REF(name:TCON, num:138);, ICONST(0x1,8,208);, SYM_REF(name:IE0, num:513)

;DEF_VAR: IT0, bw:1, type:sbit, tt:6, addr:0x1ffff//210

;OPR: ^, SYM_REF(name:TCON, num:138);, ICONST(0x0,8,217);, SYM_REF(name:IT0, num:528)

;DEF_VAR: EA, bw:1, type:sbit, tt:6, addr:0x1ffff//21f

;OPR: ^, SYM_REF(name:IE, num:210);, ICONST(0x7,8,226);, SYM_REF(name:EA, num:543)

;DEF_VAR: ET2, bw:1, type:sbit, tt:6, addr:0x1ffff//22e

;OPR: ^, SYM_REF(name:IE, num:210);, ICONST(0x5,8,235);, SYM_REF(name:ET2, num:558)

;DEF_VAR: ES, bw:1, type:sbit, tt:6, addr:0x1ffff//23d

;OPR: ^, SYM_REF(name:IE, num:210);, ICONST(0x4,8,244);, SYM_REF(name:ES, num:573)

;DEF_VAR: ET1, bw:1, type:sbit, tt:6, addr:0x1ffff//24c

;OPR: ^, SYM_REF(name:IE, num:210);, ICONST(0x3,8,253);, SYM_REF(name:ET1, num:588)

;DEF_VAR: EX1, bw:1, type:sbit, tt:6, addr:0x1ffff//25b

;OPR: ^, SYM_REF(name:IE, num:210);, ICONST(0x2,8,262);, SYM_REF(name:EX1, num:603)

;DEF_VAR: ET0, bw:1, type:sbit, tt:6, addr:0x1ffff//26a

;OPR: ^, SYM_REF(name:IE, num:210);, ICONST(0x1,8,271);, SYM_REF(name:ET0, num:618)

;DEF_VAR: EX0, bw:1, type:sbit, tt:6, addr:0x1ffff//279

;OPR: ^, SYM_REF(name:IE, num:210);, ICONST(0x0,8,280);, SYM_REF(name:EX0, num:633)

;DEF_VAR: PT2, bw:1, type:sbit, tt:6, addr:0x1ffff//288

;OPR: ^, SYM_REF(name:IP, num:222);, ICONST(0x5,8,28f);, SYM_REF(name:PT2, num:648)

;DEF_VAR: PS, bw:1, type:sbit, tt:6, addr:0x1ffff//297

;OPR: ^, SYM_REF(name:IP, num:222);, ICONST(0x4,8,29e);, SYM_REF(name:PS, num:663)

;DEF_VAR: PT1, bw:1, type:sbit, tt:6, addr:0x1ffff//2a6

;OPR: ^, SYM_REF(name:IP, num:222);, ICONST(0x3,8,2ad);, SYM_REF(name:PT1, num:678)

;DEF_VAR: PX1, bw:1, type:sbit, tt:6, addr:0x1ffff//2b5

;OPR: ^, SYM_REF(name:IP, num:222);, ICONST(0x2,8,2bc);, SYM_REF(name:PX1, num:693)

;DEF_VAR: PT0, bw:1, type:sbit, tt:6, addr:0x1ffff//2c4

;OPR: ^, SYM_REF(name:IP, num:222);, ICONST(0x1,8,2cb);, SYM_REF(name:PT0, num:708)

;DEF_VAR: PX0, bw:1, type:sbit, tt:6, addr:0x1ffff//2d3

;OPR: ^, SYM_REF(name:IP, num:222);, ICONST(0x0,8,2da);, SYM_REF(name:PX0, num:723)

;DEF_VAR: RD, bw:1, type:sbit, tt:6, addr:0x1ffff//2e2

;OPR: ^, SYM_REF(name:P3, num:42);, ICONST(0x7,8,2e9);, SYM_REF(name:RD, num:738)

;DEF_VAR: WR, bw:1, type:sbit, tt:6, addr:0x1ffff//2f1

;OPR: ^, SYM_REF(name:P3, num:42);, ICONST(0x6,8,2f8);, SYM_REF(name:WR, num:753)

;DEF_VAR: T1, bw:1, type:sbit, tt:6, addr:0x1ffff//300

;OPR: ^, SYM_REF(name:P3, num:42);, ICONST(0x5,8,307);, SYM_REF(name:T1, num:768)

;DEF_VAR: T0, bw:1, type:sbit, tt:6, addr:0x1ffff//30f

;OPR: ^, SYM_REF(name:P3, num:42);, ICONST(0x4,8,316);, SYM_REF(name:T0, num:783)

;DEF_VAR: INT1, bw:1, type:sbit, tt:6, addr:0x1ffff//31e

;OPR: ^, SYM_REF(name:P3, num:42);, ICONST(0x3,8,325);, SYM_REF(name:INT1, num:798)

;DEF_VAR: INT0, bw:1, type:sbit, tt:6, addr:0x1ffff//32d

;OPR: ^, SYM_REF(name:P3, num:42);, ICONST(0x2,8,334);, SYM_REF(name:INT0, num:813)

;DEF_VAR: TXD, bw:1, type:sbit, tt:6, addr:0x1ffff//33c

;OPR: ^, SYM_REF(name:P3, num:42);, ICONST(0x1,8,343);, SYM_REF(name:TXD, num:828)

;DEF_VAR: RXD, bw:1, type:sbit, tt:6, addr:0x1ffff//34b

;OPR: ^, SYM_REF(name:P3, num:42);, ICONST(0x0,8,352);, SYM_REF(name:RXD, num:843)

;DEF_VAR: SM0, bw:1, type:sbit, tt:6, addr:0x1ffff//35a

;OPR: ^, SYM_REF(name:SCON, num:234);, ICONST(0x7,8,361);, SYM_REF(name:SM0, num:858)

;DEF_VAR: SM1, bw:1, type:sbit, tt:6, addr:0x1ffff//369

;OPR: ^, SYM_REF(name:SCON, num:234);, ICONST(0x6,8,370);, SYM_REF(name:SM1, num:873)

;DEF_VAR: SM2, bw:1, type:sbit, tt:6, addr:0x1ffff//378

;OPR: ^, SYM_REF(name:SCON, num:234);, ICONST(0x5,8,37f);, SYM_REF(name:SM2, num:888)

;DEF_VAR: REN, bw:1, type:sbit, tt:6, addr:0x1ffff//387

;OPR: ^, SYM_REF(name:SCON, num:234);, ICONST(0x4,8,38e);, SYM_REF(name:REN, num:903)

;DEF_VAR: TB8, bw:1, type:sbit, tt:6, addr:0x1ffff//396

;OPR: ^, SYM_REF(name:SCON, num:234);, ICONST(0x3,8,39d);, SYM_REF(name:TB8, num:918)

;DEF_VAR: RB8, bw:1, type:sbit, tt:6, addr:0x1ffff//3a5

;OPR: ^, SYM_REF(name:SCON, num:234);, ICONST(0x2,8,3ac);, SYM_REF(name:RB8, num:933)

;DEF_VAR: TI, bw:1, type:sbit, tt:6, addr:0x1ffff//3b4

;OPR: ^, SYM_REF(name:SCON, num:234);, ICONST(0x1,8,3bb);, SYM_REF(name:TI, num:948)

;DEF_VAR: RI, bw:1, type:sbit, tt:6, addr:0x1ffff//3c3

;OPR: ^, SYM_REF(name:SCON, num:234);, ICONST(0x0,8,3ca);, SYM_REF(name:RI, num:963)

;DEF_VAR: T2EX, bw:1, type:sbit, tt:6, addr:0x1ffff//3d2

;OPR: ^, SYM_REF(name:P1, num:18);, ICONST(0x1,8,3d9);, SYM_REF(name:T2EX, num:978)

;DEF_VAR: T2, bw:1, type:sbit, tt:6, addr:0x1ffff//3e1

;OPR: ^, SYM_REF(name:P1, num:18);, ICONST(0x0,8,3e8);, SYM_REF(name:T2, num:993)

;DEF_VAR: TF2, bw:1, type:sbit, tt:6, addr:0x1ffff//3f0

;OPR: ^, SYM_REF(name:T2CON, num:258);, ICONST(0x7,8,3f7);, SYM_REF(name:TF2, num:1008)

;DEF_VAR: EXF2, bw:1, type:sbit, tt:6, addr:0x1ffff//3ff

;OPR: ^, SYM_REF(name:T2CON, num:258);, ICONST(0x6,8,406);, SYM_REF(name:EXF2, num:1023)

;DEF_VAR: RCLK, bw:1, type:sbit, tt:6, addr:0x1ffff//40e

;OPR: ^, SYM_REF(name:T2CON, num:258);, ICONST(0x5,8,415);, SYM_REF(name:RCLK, num:1038)

;DEF_VAR: TCLK, bw:1, type:sbit, tt:6, addr:0x1ffff//41d

;OPR: ^, SYM_REF(name:T2CON, num:258);, ICONST(0x4,8,424);, SYM_REF(name:TCLK, num:1053)

;DEF_VAR: EXEN2, bw:1, type:sbit, tt:6, addr:0x1ffff//42c

;OPR: ^, SYM_REF(name:T2CON, num:258);, ICONST(0x3,8,433);, SYM_REF(name:EXEN2, num:1068)

;DEF_VAR: TR2, bw:1, type:sbit, tt:6, addr:0x1ffff//43b

;OPR: ^, SYM_REF(name:T2CON, num:258);, ICONST(0x2,8,442);, SYM_REF(name:TR2, num:1083)

;DEF_VAR: C_T2, bw:1, type:sbit, tt:6, addr:0x1ffff//44a

;OPR: ^, SYM_REF(name:T2CON, num:258);, ICONST(0x1,8,451);, SYM_REF(name:C_T2, num:1098)

;DEF_VAR: CP_RL2, bw:1, type:sbit, tt:6, addr:0x1ffff//459

;OPR: ^, SYM_REF(name:T2CON, num:258);, ICONST(0x0,8,460);, SYM_REF(name:CP_RL2, num:1113)

;DEF_VAR: LSA, bw:1, type:sbit, tt:6, addr:0x1ffff//47e

;OPR: ^, SYM_REF(name:P2, num:30);, ICONST(0x2,8,485);, SYM_REF(name:LSA, num:1150)

;DEF_VAR: LSB, bw:1, type:sbit, tt:6, addr:0x1ffff//48d

;OPR: ^, SYM_REF(name:P2, num:30);, ICONST(0x3,8,494);, SYM_REF(name:LSB, num:1165)

;DEF_VAR: LSC, bw:1, type:sbit, tt:6, addr:0x1ffff//49c

;OPR: ^, SYM_REF(name:P2, num:30);, ICONST(0x4,8,4a3);, SYM_REF(name:LSC, num:1180)

;DEF_VAR: smgduan, bw:8, ptr:1, ptr_s:ICONST(0x11,8,4af), type:u8, tt:5, addr:0x1ffff//4b0

;OPR: =, CLIST(ICONST(0x3f,8,4c3)ICONST(0x6,8,4c5)ICONST(0x5b,8,4c8)ICONST(0x4f,8,4ca)ICONST(0x66,8,4cc)ICONST(0x6d,8,4ce)ICONST(0x7d,8,4d0)ICONST(0x7,8,4d2)ICONST(0x7f,8,4d4)ICONST(0x6f,8,4d6)ICONST(0x77,8,4d8)ICONST(0x7c,8,4da)ICONST(0x39,8,4dc)ICONST(0x5e,8,4de)ICONST(0x79,8,4e0)ICONST(0x71,8,4e2)ICONST(0x0,8,4e3));, null;, SYM_REF(name:smgduan, num:1200)

_func_delay:
__block__1275_start:
__block__1275_end:
;DEF_VAR_TMP: tmp_var_1, 16, ptr:0, 1271,,1, 11

;OPR: =, SYM_REF(name:i, num:1261);, null;, SYM_REF(name:tmp_var_1, num:1271)

MOV 0xb, 0x9;
MOV 0xc, 0xa;
;OPR: --, null;, null;, SYM_REF(name:i, num:1261)

MOV A, 0x9;
DEC 0x9;
JNZ decA_1594127266_0;
MOV A, 0xa;
DEC 0xa;
decA_1594127266_0:
;OPR: JZ, SYM_REF(name:tmp_var_1, num:1271);, null;, LABEL_REF_BSTART(1276)

MOV A, 0xb;
ORL A, 0xc;
JZ __block__1276_start;
;OPR: JMP, null;, null;, LABEL_REF_BSTART(1275)

LJMP __block__1275_start;
__block__1276_start:
__block__1276_end:
RET;
_func_delay_end:
_func_DigDisplay:
;DEF_VAR: i, bw:8, type:u8, tt:1, addr:0xe//515

;OPR: =, ICONST(0x0,8,51c);, null;, SYM_REF(name:i, num:1301)

MOV 0xe, #0x0;
__block__1324_start:
__block__1324_end:
;DEF_VAR_TMP: tmp_var_2, 8, ptr:0, 1318,,1, 15

;OPR: <, SYM_REF(name:i, num:1301);, ICONST(0x8,8,525);, SYM_REF(name:tmp_var_2, num:1318)

CLR C;
MOV A, #0x8;
MOV R2, A;
MOV A, 0xe;
SUBB A, R2;
MOV 0xf, A;
JC lessA_1594127266_1;
MOV A, #0;
MOV 0xf, A;
;
SJMP lessA_1594127266_2;
lessA_1594127266_1:
MOV A, #1;
MOV 0xf, A;
;
lessA_1594127266_2:
;OPR: JZ, SYM_REF(name:tmp_var_2, num:1318);, null;, LABEL_REF_BSTART(1325)

MOV A, 0xf;
JZ __block__1325_start;
;OPR: JMP, null;, null;, LABEL_REF_BSTART(1341)

LJMP __block__1341_start;
__block__1381_start:
__block__1381_end:
;OPR: =, ICONST(0x1,8,56b);, null;, SYM_REF(name:LSA, num:1150)

SETB 0xa2;
;OPR: =, ICONST(0x1,8,573);, null;, SYM_REF(name:LSB, num:1165)

SETB 0xa3;
;OPR: =, ICONST(0x1,8,57b);, null;, SYM_REF(name:LSC, num:1180)

SETB 0xa4;
;OPR: JMP, null;, null;, LABEL_REF_BSTART(1342)

LJMP __block__1342_start;
__block__1411_start:
__block__1411_end:
;OPR: =, ICONST(0x0,8,589);, null;, SYM_REF(name:LSA, num:1150)

CLR 0xa2;
;OPR: =, ICONST(0x1,8,591);, null;, SYM_REF(name:LSB, num:1165)

SETB 0xa3;
;OPR: =, ICONST(0x1,8,599);, null;, SYM_REF(name:LSC, num:1180)

SETB 0xa4;
;OPR: JMP, null;, null;, LABEL_REF_BSTART(1342)

LJMP __block__1342_start;
__block__1441_start:
__block__1441_end:
;OPR: =, ICONST(0x1,8,5a7);, null;, SYM_REF(name:LSA, num:1150)

SETB 0xa2;
;OPR: =, ICONST(0x0,8,5af);, null;, SYM_REF(name:LSB, num:1165)

CLR 0xa3;
;OPR: =, ICONST(0x1,8,5b7);, null;, SYM_REF(name:LSC, num:1180)

SETB 0xa4;
;OPR: JMP, null;, null;, LABEL_REF_BSTART(1342)

LJMP __block__1342_start;
__block__1471_start:
__block__1471_end:
;OPR: =, ICONST(0x0,8,5c5);, null;, SYM_REF(name:LSA, num:1150)

CLR 0xa2;
;OPR: =, ICONST(0x0,8,5cd);, null;, SYM_REF(name:LSB, num:1165)

CLR 0xa3;
;OPR: =, ICONST(0x1,8,5d5);, null;, SYM_REF(name:LSC, num:1180)

SETB 0xa4;
;OPR: JMP, null;, null;, LABEL_REF_BSTART(1342)

LJMP __block__1342_start;
__block__1501_start:
__block__1501_end:
;OPR: =, ICONST(0x1,8,5e3);, null;, SYM_REF(name:LSA, num:1150)

SETB 0xa2;
;OPR: =, ICONST(0x1,8,5eb);, null;, SYM_REF(name:LSB, num:1165)

SETB 0xa3;
;OPR: =, ICONST(0x0,8,5f3);, null;, SYM_REF(name:LSC, num:1180)

CLR 0xa4;
;OPR: JMP, null;, null;, LABEL_REF_BSTART(1342)

LJMP __block__1342_start;
__block__1531_start:
__block__1531_end:
;OPR: =, ICONST(0x0,8,601);, null;, SYM_REF(name:LSA, num:1150)

CLR 0xa2;
;OPR: =, ICONST(0x1,8,609);, null;, SYM_REF(name:LSB, num:1165)

SETB 0xa3;
;OPR: =, ICONST(0x0,8,611);, null;, SYM_REF(name:LSC, num:1180)

CLR 0xa4;
;OPR: JMP, null;, null;, LABEL_REF_BSTART(1342)

LJMP __block__1342_start;
__block__1561_start:
__block__1561_end:
;OPR: =, ICONST(0x1,8,61f);, null;, SYM_REF(name:LSA, num:1150)

SETB 0xa2;
;OPR: =, ICONST(0x0,8,627);, null;, SYM_REF(name:LSB, num:1165)

CLR 0xa3;
;OPR: =, ICONST(0x0,8,62f);, null;, SYM_REF(name:LSC, num:1180)

CLR 0xa4;
;OPR: JMP, null;, null;, LABEL_REF_BSTART(1342)

LJMP __block__1342_start;
__block__1591_start:
__block__1591_end:
;OPR: =, ICONST(0x0,8,63d);, null;, SYM_REF(name:LSA, num:1150)

CLR 0xa2;
;OPR: =, ICONST(0x0,8,645);, null;, SYM_REF(name:LSB, num:1165)

CLR 0xa3;
;OPR: =, ICONST(0x0,8,64d);, null;, SYM_REF(name:LSC, num:1180)

CLR 0xa4;
;OPR: JMP, null;, null;, LABEL_REF_BSTART(1342)

LJMP __block__1342_start;
;OPR: JMP, null;, null;, LABEL_REF_BSTART(1342)

LJMP __block__1342_start;
__block__1341_start:
__block__1341_end:
;DEF_VAR_TMP: tmp_var_3, 8, ptr:0, 1621,,1, 16

;OPR: ==, SYM_REF(name:i, num:1301);, ICONST(0x0,10,656);, SYM_REF(name:tmp_var_3, num:1621)

MOV A, 0xe;
XRL A, #0x0;
JNZ is_equal_sz_1594127266_3;
MOV A, #0; mov from shift over. just mov zero. 1
XRL A, #0x0;
JNZ is_equal_sz_1594127266_3;
MOV A, #1;
MOV 0x10, A;
JMP is_equal_end_1594127266_4;
is_equal_sz_1594127266_3:
MOV A, #0;
MOV 0x10, A;
is_equal_end_1594127266_4:
;OPR: JNZ, SYM_REF(name:tmp_var_3, num:1621);, null;, LABEL_REF_BSTART(1381)

MOV A, 0x10;
JNZ __block__1381_start;
;OPR: ==, SYM_REF(name:i, num:1301);, ICONST(0x1,10,65c);, SYM_REF(name:tmp_var_3, num:1621)

MOV A, 0xe;
XRL A, #0x1;
JNZ is_equal_sz_1594127266_5;
MOV A, #0; mov from shift over. just mov zero. 1
XRL A, #0x0;
JNZ is_equal_sz_1594127266_5;
MOV A, #1;
MOV 0x10, A;
JMP is_equal_end_1594127266_6;
is_equal_sz_1594127266_5:
MOV A, #0;
MOV 0x10, A;
is_equal_end_1594127266_6:
;OPR: JNZ, SYM_REF(name:tmp_var_3, num:1621);, null;, LABEL_REF_BSTART(1411)

MOV A, 0x10;
JNZ __block__1411_start;
;OPR: ==, SYM_REF(name:i, num:1301);, ICONST(0x2,10,662);, SYM_REF(name:tmp_var_3, num:1621)

MOV A, 0xe;
XRL A, #0x2;
JNZ is_equal_sz_1594127266_7;
MOV A, #0; mov from shift over. just mov zero. 1
XRL A, #0x0;
JNZ is_equal_sz_1594127266_7;
MOV A, #1;
MOV 0x10, A;
JMP is_equal_end_1594127266_8;
is_equal_sz_1594127266_7:
MOV A, #0;
MOV 0x10, A;
is_equal_end_1594127266_8:
;OPR: JNZ, SYM_REF(name:tmp_var_3, num:1621);, null;, LABEL_REF_BSTART(1441)

MOV A, 0x10;
JNZ __block__1441_start;
;OPR: ==, SYM_REF(name:i, num:1301);, ICONST(0x3,10,668);, SYM_REF(name:tmp_var_3, num:1621)

MOV A, 0xe;
XRL A, #0x3;
JNZ is_equal_sz_1594127266_9;
MOV A, #0; mov from shift over. just mov zero. 1
XRL A, #0x0;
JNZ is_equal_sz_1594127266_9;
MOV A, #1;
MOV 0x10, A;
JMP is_equal_end_1594127266_10;
is_equal_sz_1594127266_9:
MOV A, #0;
MOV 0x10, A;
is_equal_end_1594127266_10:
;OPR: JNZ, SYM_REF(name:tmp_var_3, num:1621);, null;, LABEL_REF_BSTART(1471)

MOV A, 0x10;
JNZ __block__1471_start;
;OPR: ==, SYM_REF(name:i, num:1301);, ICONST(0x4,10,66e);, SYM_REF(name:tmp_var_3, num:1621)

MOV A, 0xe;
XRL A, #0x4;
JNZ is_equal_sz_1594127266_11;
MOV A, #0; mov from shift over. just mov zero. 1
XRL A, #0x0;
JNZ is_equal_sz_1594127266_11;
MOV A, #1;
MOV 0x10, A;
JMP is_equal_end_1594127266_12;
is_equal_sz_1594127266_11:
MOV A, #0;
MOV 0x10, A;
is_equal_end_1594127266_12:
;OPR: JNZ, SYM_REF(name:tmp_var_3, num:1621);, null;, LABEL_REF_BSTART(1501)

MOV A, 0x10;
JNZ __block__1501_start;
;OPR: ==, SYM_REF(name:i, num:1301);, ICONST(0x5,10,674);, SYM_REF(name:tmp_var_3, num:1621)

MOV A, 0xe;
XRL A, #0x5;
JNZ is_equal_sz_1594127266_13;
MOV A, #0; mov from shift over. just mov zero. 1
XRL A, #0x0;
JNZ is_equal_sz_1594127266_13;
MOV A, #1;
MOV 0x10, A;
JMP is_equal_end_1594127266_14;
is_equal_sz_1594127266_13:
MOV A, #0;
MOV 0x10, A;
is_equal_end_1594127266_14:
;OPR: JNZ, SYM_REF(name:tmp_var_3, num:1621);, null;, LABEL_REF_BSTART(1531)

MOV A, 0x10;
JNZ __block__1531_start;
;OPR: ==, SYM_REF(name:i, num:1301);, ICONST(0x6,10,67a);, SYM_REF(name:tmp_var_3, num:1621)

MOV A, 0xe;
XRL A, #0x6;
JNZ is_equal_sz_1594127266_15;
MOV A, #0; mov from shift over. just mov zero. 1
XRL A, #0x0;
JNZ is_equal_sz_1594127266_15;
MOV A, #1;
MOV 0x10, A;
JMP is_equal_end_1594127266_16;
is_equal_sz_1594127266_15:
MOV A, #0;
MOV 0x10, A;
is_equal_end_1594127266_16:
;OPR: JNZ, SYM_REF(name:tmp_var_3, num:1621);, null;, LABEL_REF_BSTART(1561)

MOV A, 0x10;
JNZ __block__1561_start;
;OPR: ==, SYM_REF(name:i, num:1301);, ICONST(0x7,10,680);, SYM_REF(name:tmp_var_3, num:1621)

MOV A, 0xe;
XRL A, #0x7;
JNZ is_equal_sz_1594127266_17;
MOV A, #0; mov from shift over. just mov zero. 1
XRL A, #0x0;
JNZ is_equal_sz_1594127266_17;
MOV A, #1;
MOV 0x10, A;
JMP is_equal_end_1594127266_18;
is_equal_sz_1594127266_17:
MOV A, #0;
MOV 0x10, A;
is_equal_end_1594127266_18:
;OPR: JNZ, SYM_REF(name:tmp_var_3, num:1621);, null;, LABEL_REF_BSTART(1591)

MOV A, 0x10;
JNZ __block__1591_start;
;OPR: JMP, null;, null;, LABEL_REF_BSTART(1342)

LJMP __block__1342_start;
__block__1342_start:
__block__1342_end:
;OPR: =, SYM_REF(name:tmp_var_4, ptr:-1, ptr_s:SYM_REF(name:i, num:1301), num:1727);, null;, SYM_REF(name:P0, num:6)

;DEF_VAR_TMP: tmp_var_5, 16, ptr:0, 1728,,1, 17

;OPR: =, ICONST(0x0,0,6c2);, null;, SYM_REF(name:tmp_var_5, num:1728)

MOV A, #(__const_label_0);
MOV 0x11, A;
MOV A, #(0xff&(( 0xff00&__const_label_0) >>8));
MOV 0x12, A;
;DEF_VAR_TMP: tmp_var_6, 0, ptr:0, 1732,,1, 19

;OPR: *, SYM_REF(name:i, num:1301);, ICONST(0x1,8,6c6);, SYM_REF(name:tmp_var_6, num:1732)

MOV 0xf0, 0xe;
MOV A, #0x1;
MUL AB;
MOV 0x13, A;
;OPR: +, DEF_VAR_TMP: tmp_var_6, 0, ptr:0, 1732,,1, 19
;, DEF_VAR_TMP: tmp_var_5, 16, ptr:0, 1728,,1, 17
;, DEF_VAR_TMP: tmp_var_5, 16, ptr:0, 1728,,1, 17


MOV A, 0x13;
ADD A, 0x11;
MOV 0x11, A;
MOV A, #0; mov from shift over. just mov zero. 1
ADDC A, 0x12;
MOV 0x12, A;
MOV 0x82, 0x11;
MOV 0x83, 0x12;
CLR A;
MOVC A, @A+DPTR;
MOV 0x80, A;
MOV 0x9, #0x64;
MOV 0xa, #0x0;
LCALL _func_delay
;OPR: =, ICONST(0x0,8,6a1);, null;, SYM_REF(name:P0, num:6)

MOV 0x80, #0x0;
;OPR: ++, null;, null;, SYM_REF(name:i, num:1301)

INC 0xe;
MOV A, 0xe;
;OPR: JMP, null;, null;, LABEL_REF_BSTART(1324)

LJMP __block__1324_start;
__block__1325_start:
__block__1325_end:
RET;
_func_DigDisplay_end:
_func_main:
__block__1711_start:
__block__1711_end:
;OPR: JZ, ICONST(0x1,8,6ae);, null;, LABEL_REF_BSTART(1712)

; jmp with const zero is ignored
LCALL _func_DigDisplay
;OPR: JMP, null;, null;, LABEL_REF_BSTART(1711)

LJMP __block__1711_start;
__block__1712_start:
__block__1712_end:
RET;
_func_main_end:
__const_label_0:
DB 0x3f 0x6 0x5b 0x4f 0x66 0x6d 0x7d 0x7 0x7f 0x6f 0x77 0x7c 0x39 0x5e 0x79 0x71 0x0 ;
