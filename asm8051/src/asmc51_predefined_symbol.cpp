#include <sstream>
#include "asmc51_predefined_symbol.h"
#include "trim.h"
#include "split.h"
#include "replace.h"
#include "str2number.h"
asmc51_predefined_symbol::asmc51_predefined_symbol()
{
}

std::map<std::string, unsigned> asmc51_predefined_symbol::get_symbols()
{
    std::string var1=R"(

            ;/*  BYTE Register  */
            sfr P0   0x80;
            sfr P1   0x90;
            sfr P2   0xA0;
            sfr P3   0xB0;
            sfr P4   0xC0;
            sfr P5   0xC8;

            sfr PSW  0xD0;
            sfr ACC  0xE0;
            sfr B    0xF0;
            sfr SP   0x81;
            sfr DPL  0x82;
            sfr DPH  0x83;
            sfr PCON 0x87;
            sfr TCON 0x88;
            sfr TMOD 0x89;
            sfr TL0  0x8A;
            sfr TL1  0x8B;
            sfr TH0  0x8C;
            sfr TH1  0x8D;
            sfr IE   0xA8;
            sfr IP   0xB8;
            sfr SCON 0x98;
            sfr SBUF 0x99;



            ;/*  BIT Register  */
            ;/*  PSW   */
            sbit CY   0xD7;
            sbit AC   0xD6;
            sbit F0   0xD5;
            sbit RS1  0xD4;
            sbit RS0  0xD3;
            sbit OV   0xD2;
            sbit P    0xD0;

            ;/*  TCON  */
            sbit TF1  0x8F;
            sbit TR1  0x8E;
            sbit TF0  0x8D;
            sbit TR0  0x8C;
            sbit IE1  0x8B;
            sbit IT1  0x8A;
            sbit IE0  0x89;
            sbit IT0  0x88;

            ;/*  IE   */
            sbit EA   0xAF;
            sbit ES   0xAC;
            sbit ET1  0xAB;
            sbit EX1  0xAA;
            sbit ET0  0xA9;
            sbit EX0  0xA8;

            ;/*  IP   */
            sbit PS   0xBC;
            sbit PT1  0xBB;
            sbit PX1  0xBA;
            sbit PT0  0xB9;
            sbit PX0  0xB8;

            ;/*  P3  */
            sbit RD   0xB7;
            sbit WR   0xB6;
            sbit T1   0xB5;
            sbit T0   0xB4;
            sbit INT1 0xB3;
            sbit INT0 0xB2;
            sbit TXD  0xB1;
            sbit RXD  0xB0;

            ;/*  SCON  */
            sbit SM0  0x9F;
            sbit SM1  0x9E;
            sbit SM2  0x9D;
            sbit REN  0x9C;
            sbit TB8  0x9B;
            sbit RB8  0x9A;
            sbit TI   0x99;
            sbit RI   0x98;



            )";

            m_symbols.clear();
            std::stringstream istr(var1);
            std::string one_line;
            while(std::getline(istr, one_line))
            {
                replace(one_line, "\t", " ");
                trim(one_line);
                if(one_line.empty())continue;
                if(one_line[0]==';')continue;
                replace(one_line, ";", "");
                std::vector<std::string> kk = split(one_line," ", 1);
                if(kk.size()!=3)
                {
                    continue;
                }
                m_symbols[kk[1]] = StrToNumber( kk[2]);
            }


    return m_symbols;






}
