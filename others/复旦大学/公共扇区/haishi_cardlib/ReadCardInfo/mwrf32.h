extern "C"
{
//1.
HANDLE __stdcall  rf_init(__int16 port,long baud);
//2.
__int16 __stdcall rf_exit(HANDLE icdev);
//3.
__int16 __stdcall rf_config(HANDLE icdev,unsigned char _Mode,unsigned char _Baud);
//4.
__int16 __stdcall rf_request(HANDLE icdev,unsigned char _Mode,unsigned __int16 *TagType);
//5.
__int16 __stdcall rf_request_std(HANDLE icdev,unsigned char _Mode,unsigned __int16 *TagType);

__int16 __stdcall rf_anticoll(HANDLE icdev,unsigned char _Bcnt,unsigned long *_Snr);
//6.
__int16 __stdcall rf_select(HANDLE icdev,unsigned long _Snr,unsigned char *_Size);
//7.
__int16 __stdcall rf_authentication(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr);
//8.
__int16 __stdcall rf_halt(HANDLE icdev);
//9
__int16 __stdcall rf_read(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
//10.
__int16 __stdcall rf_read_hex(HANDLE icdev,unsigned char _Adr, char *_Data);
//11.
__int16 __stdcall rf_write(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
//12.
__int16 __stdcall rf_write_hex(HANDLE icdev,unsigned char _Adr,char *_Data);
//13.
__int16 __stdcall rf_load_key(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,unsigned char *_NKey);
//14.
__int16 __stdcall rf_load_key_hex(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr, char *_NKey);
//15.
__int16 __stdcall rf_increment(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
//16.
__int16 __stdcall rf_decrement(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
//17
__int16 __stdcall rf_decrement_ml(HANDLE icdev,unsigned __int16 _Value);
//18.
__int16 __stdcall rf_restore(HANDLE icdev,unsigned char _Adr);
//19
__int16 __stdcall rf_transfer(HANDLE icdev,unsigned char _Adr);
//20.
__int16 __stdcall rf_card(HANDLE icdev,unsigned char _Mode,unsigned long *_Snr);
//21.
__int16 __stdcall rf_initval(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
//22
__int16 __stdcall rf_initval_ml(HANDLE icdev,unsigned __int16 _Value);
//23.
__int16 __stdcall rf_readval(HANDLE icdev,unsigned char _Adr,unsigned long *_Value);
//24
__int16 __stdcall rf_readval_ml(HANDLE icdev,unsigned __int16 *_Value);
//25.
__int16 __stdcall rf_changeb3(HANDLE icdev,unsigned char _SecNr,unsigned char *_KeyA,unsigned char _B0,unsigned char _B1,unsigned char _B2,unsigned char _B3,unsigned char _Bk,unsigned char *_KeyB);
//26.
__int16 __stdcall rf_get_status(HANDLE icdev,unsigned char *_Status);
//27.
__int16 __stdcall rf_clr_control_bit(HANDLE icdev,unsigned char _b);
//28.
__int16 __stdcall rf_set_control_bit(HANDLE icdev,unsigned char _b);
//29.
__int16 __stdcall rf_reset(HANDLE icdev,unsigned __int16 _Msec);
//30.
__int16 __stdcall rf_HL_decrement(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,unsigned long _Value,unsigned long _Snr,unsigned long *_NValue,unsigned long *_NSnr);
//31.
__int16 __stdcall rf_HL_increment(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,unsigned long _Value,unsigned long _Snr,unsigned long *_NValue,unsigned long *_NSnr);
//32.
__int16 __stdcall rf_HL_write(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data);
//33.
__int16 __stdcall rf_HL_writehex(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr, char *_Data);
//34
__int16 __stdcall rf_HL_read(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
//35
__int16 __stdcall rf_HL_readhex(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr, char *_Data,unsigned long *_NSnr);
//36.
__int16 __stdcall rf_HL_initval(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,unsigned long _Value,unsigned long *_Snr);
//37.
__int16 __stdcall rf_beep(HANDLE icdev,unsigned short _Msec);
//38.
__int16 __stdcall rf_disp8(HANDLE icdev,__int16 pt_mode,unsigned char* disp_str);
//39.
__int16 __stdcall rf_disp(HANDLE icdev,unsigned char pt_mode,unsigned short digit);
//40.
__int16 __stdcall rf_encrypt(unsigned char *key,unsigned char *ptrSource, unsigned __int16 msgLen,unsigned char *ptrDest);
//41.
__int16 __stdcall rf_decrypt(unsigned char *key,unsigned char *ptrSource, unsigned __int16 msgLen,unsigned char *ptrDest);
//42
__int16 __stdcall rf_HL_authentication(HANDLE icdev,unsigned char reqmode,unsigned long snr,unsigned char authmode,unsigned char secnr);
//43
__int16 __stdcall rf_srd_eeprom(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char *rec_buffer);
//44
__int16 __stdcall rf_swr_eeprom(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* send_buffer);
//45
__int16 __stdcall rf_srd_snr(HANDLE icdev,__int16 lenth,unsigned char *rec_buffer);
//46
__int16 __stdcall rf_check_write(HANDLE icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char * _data);
//47
__int16 __stdcall rf_check_writehex(HANDLE icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr, char * _data);
//48
__int16 __stdcall rf_authentication_2(HANDLE icdev,unsigned char _Mode,unsigned char KeyNr,unsigned char Adr);
//49
__int16 __stdcall rf_decrement_transfer(HANDLE icdev,unsigned char Adr,unsigned long _Value);
//50
__int16 __stdcall rf_setport(HANDLE icdev,unsigned char _Byte);
//51
__int16 __stdcall rf_getport(HANDLE icdev,unsigned char *receive_data);
//52
__int16 __stdcall rf_gettime(HANDLE icdev,unsigned char *time);
//53
__int16 __stdcall rf_gettimehex(HANDLE icdev,char *time);
//54
__int16 __stdcall rf_settime(HANDLE icdev,unsigned char *time);
//55
__int16 __stdcall rf_settimehex(HANDLE icdev,char *time);
//56
__int16 __stdcall rf_setbright(HANDLE icdev,unsigned char bright);
//57
__int16 __stdcall rf_ctl_mode(HANDLE icdev,unsigned char mode);
//58
__int16 __stdcall rf_disp_mode(HANDLE icdev,unsigned char mode);
//59
__int16 __stdcall lib_ver(unsigned char *str_ver);
//60
__int16 __stdcall rf_comm_check(HANDLE icdev,unsigned char _Mode);
//61
__int16 __stdcall set_host_check(unsigned char _Mode);
//62
__int16 __stdcall set_host_485(unsigned char _Mode);
//63
__int16 __stdcall rf_set_485(HANDLE icdev,unsigned char _Mode);
//64
__int16 __stdcall hex_a(unsigned char *hex,char *a,unsigned char length);
//65
__int16 __stdcall a_hex(const char *a,unsigned char *hex,unsigned char len);
//66
//__int16 __stdcall srd_alleeprom(HANDLE icdev,__int16 offset,__int16 len,unsigned char *receive_buffer);
//67
//__int16 __stdcall swr_alleeprom(HANDLE icdev,__int16 offset,__int16 len,unsigned char* send_buffer);
//68
__int16 __stdcall rf_swr_snr(HANDLE icdev,__int16 lenth,unsigned char* send_buffer);
//69
__int16 __stdcall rf_sam_rst(HANDLE icdev, unsigned char baud, unsigned char *samack);
//70
__int16 __stdcall rf_sam_trn(HANDLE icdev, unsigned char *samblock,unsigned char *recv);
//71
__int16 __stdcall rf_sam_off(HANDLE icdev);
//72
__int16 __stdcall mf2_protocol(HANDLE icdev,unsigned __int16 timeout,unsigned char slen,char *dbuff);
//73
__int16 __stdcall rf_cpu_rst(HANDLE icdev, unsigned char baud, unsigned char *cpuack);
//74
__int16 __stdcall rf_cpu_trn(HANDLE icdev, unsigned char *cpublock,unsigned char *recv);
//75
__int16 __stdcall rf_pro_rst(HANDLE icdev,unsigned char *_Data);
//76
__int16 __stdcall rf_pro_trn(HANDLE icdev,unsigned char *problock,unsigned char *recv);
//77
__int16 __stdcall rf_pro_halt(HANDLE icdev);
//78
void __stdcall Set_Reader_Mode(unsigned char _Mode);
__int16 __stdcall rf_get_snr(HANDLE icdev,unsigned char *_Snr);
}