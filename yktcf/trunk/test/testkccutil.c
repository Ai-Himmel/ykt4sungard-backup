/** 
 * ģ����					ͨ��ǰ�ò��Գ���
 * �ļ���					testkccutil.c
 * �ļ�ʵ�ֹ���				�� kcc_util �������е�Ԫ����
 * ����						����
 * �汾						V0.1
 * ����						2005-09-25
 * ��ע
 * $Id$
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "kcc_util.h"

void test_kcc_get_tick_count()
{
	unsigned long tickcount,tickcount2;
	tickcount = kcc_get_tick_count();
	printf("tickcount [%lu]\n",tickcount);
	sleep(1);
	tickcount2 = kcc_get_tick_count();
	printf("tickcount2 [%lu]\n",tickcount2);
	sleep(3);
	tickcount2 = kcc_get_tick_count();
	printf("tickcount2 [%lu]\n",tickcount2);
	sleep(5);
	tickcount2 = kcc_get_tick_count();
	printf("tickcount2 [%lu]\n",tickcount2);
}

void test_kcc_hex2src()
{
	char tmp[128] = "";
	int value = 0;

	value = 0x123456;
	memset(tmp,0,sizeof tmp);
	kcc_hex2src((const char*)&value,4,tmp);
	printf("value %x str[%s]\n",value,tmp);

	value = 0x1F3EB36;
	memset(tmp,0,sizeof tmp);
	kcc_hex2src((const char*)&value,4,tmp);
	printf("value %x str[%s]\n",value,tmp);

	value = 0x12321;
	memset(tmp,0,sizeof tmp);
	kcc_hex2src((const char*)&value,4,tmp);
	printf("value %x str[%s]\n",value,tmp);
}

void test_kcc_str_trim()
{
	char value[] = "  china is first !!! d		\t\t";
	char tmp[128] = "";
	kcc_str_trim(value,tmp," \t");
	printf("value[%s] trim[%s]\n",value,tmp);
}

int main(int argc,char **argv)
{
	test_kcc_get_tick_count();
	test_kcc_hex2src();
	test_kcc_str_trim();
	return 0;
}
