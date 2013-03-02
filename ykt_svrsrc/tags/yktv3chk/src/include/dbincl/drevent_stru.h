#ifndef  __T_drevent_H_
#define  __T_drevent_H_
typedef struct 
{
		int	deviceid;
		int	eventcode;
		char	transdate[8+1];
		char	transtime[6+1];
		char	eventmsg[255+1];
		int	sysid;
		char	coldate[8+1];
		char	coltime[6+1];
}T_t_doorevent;
int DB_t_doorevent_add(T_t_doorevent *pt_doorevent);
#endif
