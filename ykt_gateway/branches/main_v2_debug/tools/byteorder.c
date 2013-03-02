#include <stdlib.h>
#include <stdio.h>

struct order_test_t
{
	union
	{
		short s;
		char c[sizeof(short)];
	} u;
};
static int test_byte_order()
{
	struct order_test_t tOrder;
	tOrder.u.s = 0x0102;
	// big-endin
	if(tOrder.u.c[0] == 0x01)
		return 1;
	// little-endin
	else if(tOrder.u.c[0] == 0x02)
		return -1;
	// unknown
	else
		return 0;
}

int main()
{
	int ret;
	ret = test_byte_order();
	switch(ret)
	{
	default:
	case 0:
		printf("unknown byte order !\n");
		break;
	case 1:
		printf("big-endian byte order!\n");
		break;
	case -1:
		printf("little-endian byte order!\n");
		break;
	}
	return 0;
}

