/*°汾7.0.0.8    2005.6*/
#define uc unsigned char
extern "C"
{
//1.
int  __stdcall  dc_init(__int16 port,long baud);
//2.
__int16  __stdcall dc_exit(int icdev);
//3.
__int16  __stdcall dc_config(int icdev,unsigned char _Mode,unsigned char _Baud);
//4.
__int16  __stdcall dc_request(int icdev,unsigned char _Mode,unsigned __int16  *TagType);
//5.
__int16  __stdcall  dc_anticoll(int icdev,unsigned char _Bcnt,unsigned long *_Snr);
//6.
__int16  __stdcall dc_select(int icdev,unsigned long _Snr,unsigned char *_Size);
//7.
__int16  __stdcall dc_authentication(int icdev,unsigned char _Mode,unsigned char _SecNr);
//8.
__int16  __stdcall dc_halt(int icdev);
//9
__int16  __stdcall dc_read(int icdev,unsigned char _Adr,unsigned char *_Data);
//10.
__int16  __stdcall dc_read_hex(int icdev,unsigned char _Adr,char *_Data);
//11.
__int16  __stdcall dc_write(int icdev,unsigned char _Adr,unsigned char *_Data);
//12.
__int16  __stdcall dc_write_hex(int icdev,unsigned char _Adr,char *_Data);
//13.
__int16  __stdcall dc_load_key(int icdev,unsigned char _Mode,unsigned char _SecNr,
							   unsigned char *_NKey);
//14.
__int16  __stdcall dc_load_key_hex(int icdev,unsigned char _Mode,unsigned char _SecNr,
								   char *_NKey);
//15.
__int16  __stdcall dc_card(int icdev,unsigned char _Mode,unsigned long *_Snr);
//16
__int16 __stdcall dc_card_hex(int icdev,unsigned char _Mode,unsigned char *snrstr);
//17.
__int16  __stdcall dc_changeb3(int icdev,unsigned char _SecNr,unsigned char *_KeyA,
							   unsigned char _B0,unsigned char _B1,unsigned char _B2,
							   unsigned char _B3,unsigned char _Bk,unsigned char *_KeyB);
//18.
__int16  __stdcall dc_restore(int icdev,unsigned char _Adr);
//19
__int16  __stdcall dc_transfer(int icdev,unsigned char _Adr);
//20
__int16  __stdcall dc_increment(int icdev,unsigned char _Adr,unsigned long _Value);
//21.
__int16  __stdcall dc_decrement(int icdev,unsigned char _Adr,unsigned long _Value);
//22.
__int16  __stdcall dc_initval(int icdev,unsigned char _Adr,unsigned long _Value);
//23.
__int16  __stdcall dc_readval(int icdev,unsigned char _Adr,unsigned long *_Value);
//24
__int16  __stdcall dc_initval_ml(int icdev,unsigned __int16   _Value);
//25
__int16  __stdcall dc_readval_ml(int icdev,unsigned __int16   *_Value);//17
//26
__int16  __stdcall dc_decrement_ml(int icdev,unsigned __int16   _Value);
//27
__int16  __stdcall dc_authentication_2(int icdev,unsigned char _Mode,unsigned char KeyNr,
									   unsigned char Adr);
//28
__int16  __stdcall  dc_anticoll2(int icdev,unsigned char _Bcnt,unsigned long *_Snr);
//29
__int16  __stdcall dc_select2(int icdev,unsigned long _Snr,unsigned char *_Size);
//30.
__int16  __stdcall dc_HL_write(int icdev,unsigned char _Mode,unsigned char _Adr,
							   unsigned long *_Snr,unsigned char *_Data);
//31
__int16  __stdcall dc_HL_writehex(int icdev,unsigned char _Mode,unsigned char _Adr,
								  unsigned long *_Snr,unsigned char *_Data);

//32.
__int16  __stdcall dc_HL_read(int icdev,unsigned char _Mode,unsigned char _Adr,
							  unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
//33
__int16  __stdcall dc_HL_readhex(int icdev,unsigned char _Mode,unsigned char _Adr,
								 unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);

//34.
__int16  __stdcall dc_HL_authentication(int icdev,unsigned char reqmode,unsigned long snr,
										unsigned char authmode,unsigned char secnr);
//35.
__int16  __stdcall dc_check_write(int icdev,unsigned long Snr,unsigned char authmode,
								  unsigned char Adr,unsigned char * _data);
//36
__int16  __stdcall dc_check_writehex(int icdev,unsigned long Snr,unsigned char authmode,
									 unsigned char Adr,unsigned char * _data);

//37.
__int16 __stdcall dc_getver(int icdev,unsigned char *sver);
//39
__int16  __stdcall dc_clr_control_bit(int icdev,unsigned char _b);
//40.
__int16  __stdcall dc_set_control_bit(int icdev,unsigned char _b);
//41.
__int16  __stdcall dc_reset(int icdev,unsigned __int16   _Msec);
//42
__int16  __stdcall dc_beep(int icdev,unsigned short _Msec);
//43.
__int16  __stdcall dc_disp_str(int icdev,char *dispstr);
//44
__int16  __stdcall dc_srd_eeprom(int icdev,__int16   offset,__int16 lenth,
								 unsigned char *rec_buffer);
//45
__int16  __stdcall dc_swr_eeprom(int icdev,__int16   offset,__int16 lenth,
								 unsigned char* send_buffer);
//46
__int16 __stdcall swr_alleeprom(int icdev,__int16 offset,__int16 lenth,
								unsigned char* snd_buffer);
//47
__int16 __stdcall srd_alleeprom(int icdev,__int16 offset,__int16 lenth,
								unsigned char *receive_buffer);
//48
__int16  __stdcall dc_srd_eepromhex(int icdev,__int16   offset,__int16   lenth,
									unsigned char *rec_buffer);

//49
__int16  __stdcall dc_swr_eepromhex(int icdev,__int16   offset,__int16   lenth,
									unsigned char* send_buffer);

//50
__int16  __stdcall dc_gettime(int icdev,unsigned char *time);
//51
__int16  __stdcall dc_gettimehex(int icdev,char *time);

//52
__int16  __stdcall dc_settime(int icdev,unsigned char *time);
//53
__int16  __stdcall dc_settimehex(int icdev,char *time);

//54
__int16  __stdcall dc_setbright(int icdev,unsigned char bright);
//55
__int16  __stdcall dc_ctl_mode(int icdev,unsigned char mode);
//56
__int16  __stdcall dc_disp_mode(int icdev,unsigned char mode);
//57
__int16  __stdcall dcdeshex(unsigned char *key,unsigned char *sour,unsigned char *dest,
							__int16 m);

//58
__int16 __stdcall dcdes(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m);
//59
__int16 __stdcall dc_light(int icdev,unsigned short _OnOff);
//60
__int16 __stdcall dc_high_disp(int icdev,unsigned char offset,unsigned char displen,
							   unsigned char *dispstr);
//61
__int16 __stdcall dc_setcpu(int icdev,unsigned char _Byte);
//62
__int16 __stdcall dc_cpureset(int icdev,unsigned char *rlen,unsigned char *databuffer);
//63
__int16 __stdcall dc_cpuapdusource(int icdev,unsigned char slen,unsigned char * sendbuffer,
								   unsigned char *rlen,unsigned char * databuffer);
//64
__int16 __stdcall dc_cpuapdu(int icdev,unsigned char slen,unsigned char * sendbuffer,
							 unsigned char *rlen,unsigned char * databuffer);
//65
__int16 __stdcall dc_cpureset_hex(int icdev,unsigned char *rlen, char *databuffer);
//66
__int16 __stdcall dc_cpuapdusource_hex(int icdev,unsigned char slen, char * sendbuffer,
									   unsigned char *rlen, char * databuffer);
//67
__int16 __stdcall dc_cpuapdu_hex(int icdev,unsigned char slen, char * sendbuffer,
								 unsigned char *rlen, char * databuffer);
//68
__int16 __stdcall dc_cpudown(int icdev);
//69
__int16 __stdcall dc_set_addr(unsigned char saddr);
//70
int __stdcall dc_init_485(__int16 port,long baud);
//71
__int16 __stdcall dc_changebaud_485(int icdev,long baud);
//72
__int16 __stdcall dc_change_addr(int icdev,unsigned char saddr);
//73
__int16 __stdcall dc_pro_reset(int icdev,unsigned char *rlen,unsigned char *receive_data);
//74
__int16 __stdcall dc_pro_command(int idComDev,unsigned char slen,
								 unsigned char * sendbuffer,unsigned char *rlen,
								 unsigned char * databuffer,unsigned char timeout);
//75
__int16 __stdcall dc_pro_resethex(int icdev,unsigned char *rlen, char *receive_data);


//76
__int16 __stdcall dc_pro_commandhex(int idComDev,unsigned char slen, 
									char * sendbuffer,unsigned char *rlen, 
									char * databuffer,unsigned char timeout);
//77
__int16 __stdcall dc_pro_commandsource(int idComDev,unsigned char slen,
									   unsigned char * sendbuffer,unsigned char *rlen,
									   unsigned char * databuffer,unsigned char timeout);
//78
__int16 __stdcall dc_pro_commandsourcehex(int idComDev,unsigned char slen, 
									char * sendbuffer,unsigned char *rlen, 
									char * databuffer,unsigned char timeout);

//79
__int16 __stdcall dc_pro_halt(int icdev);
//80
__int16 __stdcall dc_request_shc1102(int icdev,unsigned char _Mode,
									 unsigned __int16 *TagType);
//81
__int16 __stdcall dc_auth_shc1102(int icdev,unsigned char *_Data);
//82
__int16 __stdcall dc_read_shc1102(int icdev,unsigned char _Adr,unsigned char *_Data);
//83
__int16 __stdcall dc_write_shc1102(int icdev,unsigned char _Adr,unsigned char *_Data);
//84
__int16 __stdcall dc_halt_shc1102(int icdev);
//85
__int16 __stdcall hex_a(unsigned char *hex,unsigned char *a,__int16 length);
//86
__int16 __stdcall a_hex(unsigned char *a,unsigned char *hex,__int16 len);
//87
__int16 __stdcall dc_config_card(int icdev,unsigned char cardtype);
//88
__int16 __stdcall dc_request_b(int icdev,unsigned char _Mode,unsigned char AFI, 
		                       unsigned char N,unsigned char *ATQB);
//89
__int16 __stdcall dc_slotmarker(int icdev,unsigned char N, unsigned char *ATQB);
//90
__int16 __stdcall dc_attrib(int icdev,unsigned char *PUPI, unsigned char CID);
//91
__int16 __stdcall dc_open_door(int icdev,unsigned char cflag);
//92
__int16 __stdcall dc_open_timedoor(int icdev,unsigned __int16 utime);
//93
__int16 __stdcall dc_read_random(int icdev, unsigned char *data);
//94
__int16 __stdcall dc_write_random(int icdev,__int16 len, unsigned char *data);
//95
__int16 __stdcall dc_read_random_hex(int icdev, unsigned char *data);
//96
__int16 __stdcall dc_write_random_hex(int icdev,__int16 len, unsigned char *data);
//97
__int16 __stdcall dc_erase_random(int icdev,__int16 len);
//98
__int16 __stdcall dc_mfdes_auth(int icdev,unsigned char keyno,unsigned char *authkey,unsigned char *randdata);
//99
__int16 __stdcall dc_authentication_pass(int icdev,unsigned char _Mode,
										 unsigned char _Addr,unsigned char *passbuff);
//100
__int16 __stdcall dc_disp_neg(int icdev,char *dispstr);
//101
__int16 __stdcall dc_pro_commandlink(int idComDev,unsigned char slen,
								 unsigned char * sendbuffer,unsigned char *rlen,
								 unsigned char * databuffer,unsigned char timeout,
								 unsigned char FG);
//102
__int16 __stdcall dc_pro_commandlink_hex(int idComDev,unsigned char slen,
										 unsigned char * sendbuffer,unsigned char *rlen,
										 unsigned char * databuffer,unsigned char timeout,
										 unsigned char FG);

__int16 __stdcall dc_card_double(int icdev,unsigned char _Mode,unsigned char *_Snr);
__int16 __stdcall dc_card_double_hex(int icdev,unsigned char _Mode,unsigned char *_Snr);
__int16 __stdcall dc_read_idcard(int icdev,unsigned char times,unsigned char *_Data);
__int16 __stdcall dc_read_idcard_hex(int icdev,unsigned char times,unsigned char *_Data);

__int16 __stdcall dc_authentication_pass_hex(int icdev,unsigned char _Mode,
										 unsigned char _Addr,unsigned char *passbuff);

__int16  __stdcall  dc_setcpupara(int icdev,unsigned char cputype,
								  unsigned char cpupro,unsigned char cpuetu);
__int16 __stdcall dc_command(int idComDev,unsigned char cmd,unsigned char slen,
									   unsigned char * sendbuffer,unsigned char *rlen,
									   unsigned char * databuffer);

__int16 __stdcall dc_command_hex(int idComDev,unsigned char cmd,unsigned char slen, 
										  char * sendbuffer,unsigned char *rlen, 
										  char * databuffer);
__int16 __stdcall dc_creat_mac(unsigned char KeyLen,unsigned char *Key,unsigned short DataLen,
							unsigned char *Data,unsigned char *InitData,unsigned char FixChar,
							unsigned char *MacData);
__int16 __stdcall dc_creat_mac_hex(unsigned char KeyLen,unsigned char *Key,unsigned short DataLen,
								unsigned char *Data,unsigned char *InitData,unsigned char FixChar,
								unsigned char *MacData);
//--------------------------------------------------------
__int16  __stdcall dc_HL_write_hex(int icdev,unsigned char _Mode,unsigned char _Adr,
								   unsigned long *_Snr,unsigned char *_Data);
__int16  __stdcall dc_HL_read_hex(int icdev,unsigned char _Mode,unsigned char _Adr,
								  unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
__int16  __stdcall dc_check_write_hex(int icdev,unsigned long Snr,unsigned char authmode,
									  unsigned char Adr,unsigned char * _data);

__int16  __stdcall dc_srd_eeprom_hex(int icdev,__int16   offset,__int16   lenth,
									 unsigned char *rec_buffer);
__int16  __stdcall dc_swr_eeprom_hex(int icdev,__int16   offset,__int16   lenth,
									 unsigned char* send_buffer);

__int16  __stdcall dc_gettime_hex(int icdev,char *time);
__int16  __stdcall dc_settime_hex(int icdev,char *time);
__int16  __stdcall dc_des_hex(unsigned char *key,unsigned char *sour,unsigned char *dest,
							  __int16 m);
__int16 __stdcall dc_des(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m);
__int16 __stdcall dc_pro_reset_hex(int icdev,unsigned char *rlen, char *receive_data);
__int16 __stdcall dc_pro_command_hex(int idComDev,unsigned char slen, 
									 char * sendbuffer,unsigned char *rlen, 
									 char * databuffer,unsigned char timeout);
__int16 __stdcall dc_pro_commandsource_hex(int idComDev,unsigned char slen, 
										   char * sendbuffer,unsigned char *rlen, 
										   char * databuffer,unsigned char timeout);
//---------------------------------------------------------------------------------------
}