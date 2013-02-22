
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystring.h"
#include "kscardtype.h"
#include "global_func.h"
#include "ks_cardtype_mobile.h"
#include "ksreader.h"
#include "des.h"

static char g_version[]="1.0";
static char g_cardtype_name[] = "RFID SIM";
static unsigned char g_cardtype_buff[32]={0};

//static CCardTypeMobile CardTypeMb;

int KSAPI register_cardtype_op(ks_cardtype_base *&op)
{
	op = new CCardTypeMobile();
	return 0;
}
