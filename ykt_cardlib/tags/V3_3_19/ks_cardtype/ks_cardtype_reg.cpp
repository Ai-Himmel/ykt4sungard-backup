
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystring.h"
#include "kscardtype.h"
#include "global_func.h"
#include "ks_cardtype.h"
#include "ksreader.h"
#include "des.h"

static char g_version[]="1.0";
static char g_cardtype_name[] = "CPUCARD";
static CCardType CardTypeMb;


int KSAPI register_cardtype_op(ks_cardtype_base *&op)
{
	op = &CardTypeMb;
	return 0;
}
