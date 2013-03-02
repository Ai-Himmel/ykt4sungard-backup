#ifndef  __T_tradeact_H_
#define  __T_tradeact_H_
typedef struct 
{
		int	trade_no;
		int	dbflag_1;
		int	dbflag_2;
		int	dbflag_3;
		int	dbflag_4;
		int	crflag_1;
		int	crflag_2;
		int	crflag_3;
		int	crflag_4;
		int	idxdbact1;
		int	idxdbact2;
		int	idxdbact3;
		int	idxdbact4;
		int	idxcract1;
		int	idxcract2;
		int	idxcract3;
		int	idxcract4;
		int	idxamt1;
		int	idxamt2;
		int	idxamt3;
		int	idxamt4;
		int	fee_type1;
		int	fee_type2;
		int	fee_type3;
		int	fee_type4;
		char	dbactno_1[16+1];
		char	dbactno_2[16+1];
		char	dbactno_3[16+1];
		char	dbactno_4[16+1];
		char	cractno_1[16+1];
		char	cractno_2[16+1];
		char	cractno_3[16+1];
		char	cractno_4[16+1];
		char	comments1[60+1];
		char	comments2[60+1];
		char	comments3[60+1];
		char	comments4[60+1];
}T_t_aif_tradeact;
int DB_t_aif_tradeact_read_by_trade_no(int v_trade_no,T_t_aif_tradeact *pt_aif_tradeact);
int DB_t_aif_tradeact_open_select_by_c0();
int DB_t_aif_tradeact_fetch_select_by_c0(T_t_aif_tradeact *pt_aif_tradeact);
int DB_t_aif_tradeact_close_select_by_c0();
#endif
