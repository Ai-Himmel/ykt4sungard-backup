#ifndef _CONSUME_H_
#define _CONSUME_H_

#include ".\Include\DataType.h"


uint8 read_card_loop();
uint16 get_serial_count();
uint32 get_record_addr(uint32 serial_no);
uint8 get_next_wr_ptr();
uint8 update_record_read_ptr();


#endif // _CONSUME_H_

