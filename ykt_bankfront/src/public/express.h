#ifndef __EXPRESS_H_
#define __EXPRESS_H_
#ifdef __cplusplus
extern "C" {
#endif

//把变量表达式转换为数字表达式
int VarExp2NumExp(double amt[],int fee_switch[],char* var_exp,char* num_exp);
//根据数字表达式计算结果
int ExpCalAmt(char *num_exp,double *out_amt);
#ifdef __cplusplus
}
#endif
#endif
