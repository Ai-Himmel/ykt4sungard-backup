#ifndef _YKT_TRANSACTION_H_
#define _YKT_TRANSACTION_H_

// 一卡通交易基类
class YKT_Transaction_Base
{
protected:
	int ret_code_;
	char ret_msg_[256];
	YKT_Transaction_Base *next_transaction_;
	
public:
	YKT_Transaction_Base();
	YKT_Transaction_Base(YKT_Transaction_Base *next);
	virtual ~YKT_Transaction_Base();
	// 现金交易
	int transaction(ST_PACK *rpack,T_t_tif_tradeserial *tradeserial);
	// 冲正交易
	int reverse();
};

#endif // _YKT_TRANSACTION_H_