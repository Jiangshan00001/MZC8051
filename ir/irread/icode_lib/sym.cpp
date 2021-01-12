#include <deque>
//#include "lex.h"
#include "sym.h"
//#include "sys_io.h"
//#include "code_gen.h"
#include <iostream>
//char *table;
//int table_size;
//int table_pos;
int stack_pos;

int number_of_args;


std::vector<sym> table;


sym::sym()
{
    this->addr = 0;
    this->name = "";
    this->type = '1';
    def_icode=NULL;
}

