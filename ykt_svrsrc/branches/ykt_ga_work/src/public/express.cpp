// ExpressTest.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "express.h"

#define MAXNUM_ARRLIST		20

#define ADD 1 //运算符
#define SUB 2
#define MUL 3
#define DIV 4
#define POW 5
#define FACT 6
#define LEFT 7
#define ADDLEVEL 1 //运算优先级别
#define SUBLEVEL 1
#define MULLEVEL 2
#define DIVLEVEL 2
#define POWLEVEL 3
#define FACTLEVEL 4
#define LEFTLEVEL 5

char string[1001];
int STRLEN;
typedef struct stack
{
	double num;//数字
	char opsign;//运算符
	int bracket;//所处括号层
	struct stack * pnext;//链表
}stack;

double getnumber();//得到数字
double fact(int n);//阶乘
int getlevel(int opsign);//得到运算符的优先级别
char getnextopsign();//得到下一个运算符,包括'('
void push(char opsign);//压入堆栈
void pop();//从堆栈拉出
bool check();//检查表达式是否合法
stack * getstack(int n);//得到某堆栈指针

stack firststack;//动态堆栈首
int point;//表达式指针
int stacknum;//堆栈数目
char repeat='y';
static double result;
int bracket;//当前层次深度

//四舍五入函数,保留num位小数
static double d4u5(double value,int num)
{

	int sign=1;
	long long i=0;
	double k=1.0;

	for(i=0;i<num+1;i++)
		k=10.0*k;
	if(value<0)
	{
		sign=-1;
		value=-value;
	}
	value=value*k + 5;
	i=value;
	i -= i % 10;
	value=i/k;
	return value*sign;
	
}

int ExpCalAmt(char *num_exp,double *out_amt)
{
	bool error=0;
	point=0;bracket=0;stacknum=0;error=0;
	strcpy(string,num_exp);
	STRLEN=strlen(string);
		if(!check()) 
		{
			return -1;
		}
		result=getnumber();
		while(point<=STRLEN-1){
			switch(string[point++]){//哪个运算符?
			case '+':
				if(getnextopsign()>ADDLEVEL){
					push(ADD);
					result=getnumber();
				}
				else result+=getnumber();
				break;
			case '-':
				if(getnextopsign()>SUBLEVEL){
					push(SUB);
					result=getnumber();
				}
				else result-=getnumber();
				break;
			case '*':
				if(getnextopsign()>MULLEVEL){
					push(MUL);
					result=getnumber();
				}
				else
				{
					result*=getnumber();
					result=d4u5(result,2);
					if(stacknum>0 && getnextopsign()<MULLEVEL && getstack(stacknum)->bracket>=bracket)
						pop();
				}
				break;
			case '/':
				if(getnextopsign()>DIVLEVEL){
					push(DIV);
					result=getnumber();
				}
				else
				{
					result/=getnumber();
					if(stacknum>0 && getnextopsign()<DIVLEVEL && getstack(stacknum)->bracket>=bracket)
						pop();
				}
				break;
			case ')'://右括号
				--bracket;
				if(getstack(stacknum)->opsign==0){//括号前面为空
					pop();
					break;
				}
				while(stacknum>0 && getnextopsign()<getlevel(getstack(stacknum)->opsign)
						&& getstack(stacknum)->bracket>=bracket && getstack(stacknum)->opsign!=0)
						//将本层括号内可以pop的都pop
						pop();
				break;
			case '^':
				if(getnextopsign()>POWLEVEL){
					push(POW);
					result=getnumber();
				}
				else
				{
					result=pow(result,getnumber());
					while(stacknum>0 && getnextopsign()<getlevel(getstack(stacknum)->opsign)
						&& getstack(stacknum)->bracket>=bracket) pop();
				}
				break;
			case '!':
				if(getnextopsign()>FACTLEVEL){
					push(FACT);
					result=getnumber();
				}
				else
				{
					result=fact((long)result);
					while(stacknum>0 && getnextopsign()<getlevel(getstack(stacknum)->opsign)
						&& getstack(stacknum)->bracket>=bracket) pop();
				}
				break;
			}
		}
		//if(!error) printf("计算结果:%g\n",result);
	*out_amt=result;
	return 0;
}
double getnumber()
{
	if(point>STRLEN-1) return 0;
	char strnum[20];
	int n=0;
	if(string[point]=='-'){//一开始就是负号
		return 0;
	}
	while(string[point]=='('){
		if(string[point+1]=='-'){//负号
			point++;
			return 0;
		}
		else if(string[point+1]=='(') push(0);
		else break;
	}
	while((string[point]<'0' || string[point]>'9') && string[point]!='.') point++;
	while((string[point]>='0' && string[point]<='9') || string[point]=='.'){
		strnum[n++]=string[point++];
		if(point>STRLEN-1) break;
	}
	strnum[n]='\0';
	return atof(strnum);
}
char getnextopsign()
{
	int p=point;
	while(p<=STRLEN-1){
		switch(string[p++]){
		case '+':
			return ADDLEVEL;
		case '-':
			return SUBLEVEL;
		case '*':
			return MULLEVEL;
		case '/':
			return DIVLEVEL;
		case '(':
			return LEFTLEVEL;
		case '^':
			return POWLEVEL;
		case '!':
			return FACT;
		case ')':
			return 0;
		}
	}
	return 0;
}
void push(char opsign)
{
	stack *p=getstack(stacknum);
	if(stacknum>0) p=(p->pnext=new stack);
	p->bracket=bracket;
	if(string[point]=='('){
		++bracket;
		point++;
	}
	p->num=result;
	p->opsign=opsign;
	stacknum++;
}
void pop()
{
	stack *p=getstack(stacknum);
	switch(p->opsign){
	case ADD:
		result+=p->num;
		break;
	case SUB:
		result=p->num-result;
		break;
	case MUL:
		result*=p->num;
		break;
	case DIV:
		result=p->num/result;
		break;
	case POW:
		result=pow(p->num,result);
		break;
	case FACT:
		result=fact((long)result);
		break;
	case 0:
		break;
	}
	if(stacknum>1) delete p;
	stacknum--;
}

bool check()//检查表达式的合法性
{
	int left=0,right=0;
	for(int i=0;i<STRLEN;i++){
		if(string[i]<='9' && string[i]>='0')
			continue;
		switch(string[i]){
		case '(':
			++right;
			break;
		case ')':
			++left;
			break;
		case '^':
		case '!':
		case '+':
		case '-':
		case '*':
		case '/':
		case '.':
			break;
		default:
			printf("错误:出现非法字符!\n");
			return 0;
		}
	}
	if(right!=left){
		printf("错误:括号不匹配!\n");
		return 0;
	}
	return 1;
}

double fact(int n)
{
	double r=1;
	if(n<=1) return 1;
	while(n>1){
		r*=n;
		--n;
	}
	return r;
}
int getlevel(int opsign)
{
	if(opsign<=2) return 1;
	if(opsign<=4) return 2;
	return opsign-2;
}
stack * getstack(int n)
{
	stack *p=NULL;
	if(n==0) return &firststack;
	for(int i=0;i<n;i++){
		if(i==0) p=&firststack;
		else p=p->pnext;
	}
	return p;
}
//把变量表达式转换为数字表达式
int VarExp2NumExp(double amt[],int fee_switch[],char* var_exp,char* num_exp)
{
	int len=0;
	int var_len=0;
	int var_no=0;
	char expstr[255]="";
	char var[20]="";
	char var_value[20]="";
	char *phead=var_exp;
	char *ptail=var_exp;
	char *pexp=expstr;

	len=strlen(var_exp);
	for(int i=0;i<len;i++)
	{
	    while(*ptail==' '||*ptail=='\t')ptail++;
	    if('$'==(*ptail))
	    {
			++ptail;
			if((*ptail<'0')||(*ptail>'9'))
			{
				printf("exp err ch[%c]\n",*ptail);
				return -1;
			}
			phead=ptail;
			while((*ptail>='0')&&(*ptail<='9'))ptail++;
			memcpy(var,phead,ptail-phead);
			var[ptail-phead]=0;
			{
				var_no=atoi(var);
				sprintf(var_value,"%.4f",amt[var_no]);
				var_len=strlen(var_value);
				memcpy(pexp,var_value,var_len);
				pexp+=var_len;
			}
	    }
	    if('$'==(*ptail))
	    {
			++ptail;
			if((*ptail<'0')||(*ptail>'9'))
			{
				printf("exp err ch[%c]\n",*ptail);
				return -1;
			}
			phead=ptail;
			while((*ptail>='0')&&(*ptail<='9'))ptail++;
			memcpy(var,phead,ptail-phead);
			var[ptail-phead]=0;
			{
				var_no=atoi(var);
				if(var_no>=MAXNUM_ARRLIST)
					return -2;
				sprintf(var_value,"%.4f",amt[var_no]);
				var_len=strlen(var_value);
				memcpy(pexp,var_value,var_len);
				pexp+=var_len;
			}
	    }
	    else if('@'==(*ptail))
	    {
			++ptail;
			if((*ptail<'0')||(*ptail>'9'))
			{
				printf("exp err ch[%c]\n",*ptail);
				return -1;
			}
			phead=ptail;
			while((*ptail>='0')&&(*ptail<='9'))ptail++;
			memcpy(var,phead,ptail-phead);
			var[ptail-phead]=0;
			{
				var_no=atoi(var);
				if(var_no>MAXNUM_ARRLIST)
					return -3;
				sprintf(var_value,"%d",fee_switch[var_no]);
				var_len=strlen(var_value);
				memcpy(pexp,var_value,var_len);
				pexp+=var_len;
			}
	    }
	    else 
	    {
		*pexp=*ptail;	
		pexp++;
		ptail++;
	    }
	}
	strcpy(num_exp,expstr);
	return 0;
}
