#include "stdio.h"
#include "iso_8583s.h"

void main()
{
	typedef unsigned char* P_UBYTE;
	char buf1[100] = {0};
	ISO_MSG isomsg;/*[] = {{4, (unsigned char*)"\0"}, {8, (unsigned char*)"80000000"}, {4, (unsigned char*)"1234"}};*/
	iso8583_init(&isomsg);
	iso8583_set(&isomsg, 0, (P_UBYTE)"\0" , 4);
	iso8583_set(&isomsg, 1, (P_UBYTE)"  " , 8);
	iso8583_set(&isomsg, 2, (P_UBYTE)"ab1" , 22);
	iso8583_set(&isomsg, 10, (P_UBYTE)"defg12345" , 8);
	iso8583_pack(&isomsg, buf1);
	//iso8583_free(&isomsg);
	iso8583_init(&isomsg);
	iso8583_unpack(&isomsg, buf1);
	puts(buf1);
}