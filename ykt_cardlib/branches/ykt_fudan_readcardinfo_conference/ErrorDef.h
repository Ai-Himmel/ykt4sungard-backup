#ifndef _ERROR_DEF_
#define _ERROR_DEF_

// ¶¨Òå·µ»Ø´íÎóÂë
struct Get_Error_Info
{
	int return_error_code;
	char return_error_msg[30];
};

#define CONF_REQ_SUCCESS "0000"
#define CONF_REQ_FAILED "1111"

#endif