#ifndef  __T_dpsopercard_H_
#define  __T_dpsopercard_H_
typedef struct {
    char	opercode[8+1];
    int	cardno;
    int	disableflag;
    char	openoper[8+1];
    char	lastsaved[30+1];
} T_t_dpsopercard;
int DB_t_dpsopercard_add(T_t_dpsopercard *pt_dpsopercard);
int DB_t_dpsopercard_read_by_opercode(const char *v_opercode,T_t_dpsopercard *pt_dpsopercard);
int DB_t_dpsopercard_update_by_opercode(char *v_opercode,T_t_dpsopercard *pt_dpsopercard);
int DB_t_dpsopercard_read_by_cardno_and_disableflag(int v_cardno,int v_disableflag,T_t_dpsopercard *pt_dpsopercard);
#endif
