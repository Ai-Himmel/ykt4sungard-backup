#ifndef __EXPRESS_H_
#define __EXPRESS_H_
#ifdef __cplusplus
extern "C" {
#endif

//�ѱ������ʽת��Ϊ���ֱ��ʽ
int VarExp2NumExp(double amt[],int fee_switch[],char* var_exp,char* num_exp);
//�������ֱ��ʽ������
int ExpCalAmt(char *num_exp,double *out_amt);
#ifdef __cplusplus
}
#endif
#endif
