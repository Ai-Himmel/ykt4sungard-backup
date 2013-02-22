#ifndef _Z18POS_GPRS_
#define  _Z18POS_GPRS_

#include "communication.h"

uint8 gprs_connect(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op);
uint8 gprs_disconnect(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op);

#endif //  _Z18POS_GPRS_

