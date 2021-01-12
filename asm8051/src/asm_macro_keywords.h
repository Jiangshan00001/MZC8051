#ifndef ASM_MACRO_KEYWORDS_H
#define ASM_MACRO_KEYWORDS_H


int ORG_CodeGen(class T_ASM_CONTEXT *mCtx);
int END_CodeGen(class T_ASM_CONTEXT *mCtx);
int DATA_CodeGen(class T_ASM_CONTEXT *mCtx);
int EQU_CodeGen(class T_ASM_CONTEXT *mCtx);
int BIT_CodeGen(class T_ASM_CONTEXT *mCtx);
int SBIT_CodeGen(class T_ASM_CONTEXT *mCtx);
int NOMOD51_CodeGen(class T_ASM_CONTEXT *mCtx);
int SFR_CodeGen(class T_ASM_CONTEXT *mCtx);
int USING_CodeGen(class T_ASM_CONTEXT *mCtx);
int DB_CodeGen(class T_ASM_CONTEXT *mCtx);


#endif // ASM_MACRO_KEYWORDS_H
