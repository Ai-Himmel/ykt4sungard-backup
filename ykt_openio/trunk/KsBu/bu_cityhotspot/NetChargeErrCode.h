#ifndef _NET_CHARGE_H_
#define _NET_CHARGE_H_

#pragma once

#define RETURN_ERRCODE(retvalue, errcode, gotopos) do { \
	retvalue = errcode; goto gotopos; \
} while(FALSE);

#define NETCHARGE_ERR_NO_INTERFACE		-1001
#define NETCHARGE_ERR_CONNECT_DB		-1002
#define NETCHARGE_ERR_NO_ACCOUNT		-1003
#define NETCHARGE_ERR_STOP_SERVICE		-1004
#define NETCHARGE_ERR_STOP_OWE_FEE		-1005
#define NETCHARGE_ERR_CONVERSION_TIME	-1006

#endif