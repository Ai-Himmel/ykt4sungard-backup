
extern "C"
{
//1.
__int32 __stdcall  rf_init(__int16 port,long baud);
//2.
__int16 __stdcall rf_exit(__int32 icdev);
//3.
__int16 __stdcall rf_config(__int32 icdev,unsigned char _Mode,unsigned char _Baud);
//4.
__int16 __stdcall rf_request(__int32 icdev,unsigned char _Mode,unsigned __int16 *TagType);
//5.
__int16 __stdcall rf_anticoll(__int32 icdev,unsigned char _Bcnt,unsigned long *_Snr);
//6.
__int16 __stdcall rf_select(__int32 icdev,unsigned long _Snr,unsigned char *_Size);
//7.
__int16 __stdcall rf_authentication(__int32 icdev,unsigned char _Mode,unsigned char _SecNr);
//8.
__int16 __stdcall rf_halt(__int32 icdev);
//9
__int16 __stdcall rf_read(__int32 icdev,unsigned char _Adr,unsigned char *_Data);
//10.
__int16 __stdcall rf_read_hex(__int32 icdev,unsigned char _Adr, char *_Data);
//11.
__int16 __stdcall rf_write(__int32 icdev,unsigned char _Adr,unsigned char *_Data);
//12.
__int16 __stdcall rf_write_hex(__int32 icdev,unsigned char _Adr,char *_Data);
//13.
__int16 __stdcall rf_load_key(__int32 icdev,unsigned char _Mode,unsigned char _SecNr,unsigned char *_NKey);
//14.
__int16 __stdcall rf_load_key_hex(__int32 icdev,unsigned char _Mode,unsigned char _SecNr, char *_NKey);
//15.
__int16 __stdcall rf_increment(__int32 icdev,unsigned char _Adr,unsigned long _Value);
//16.
__int16 __stdcall rf_decrement(__int32 icdev,unsigned char _Adr,unsigned long _Value);
//17
__int16 __stdcall rf_decrement_ml(__int32 icdev,unsigned __int16 _Value);
//18.
__int16 __stdcall rf_restore(__int32 icdev,unsigned char _Adr);
//19
__int16 __stdcall rf_transfer(__int32 icdev,unsigned char _Adr);
//20.
__int16 __stdcall rf_card(__int32 icdev,unsigned char _Mode,unsigned long *_Snr);
//21.
__int16 __stdcall rf_initval(__int32 icdev,unsigned char _Adr,unsigned long _Value);
//22
__int16 __stdcall rf_initval_ml(__int32 icdev,unsigned __int16 _Value);
//23.
__int16 __stdcall rf_readval(__int32 icdev,unsigned char _Adr,unsigned long *_Value);
//24
__int16 __stdcall rf_readval_ml(__int32 icdev,unsigned __int16 *_Value);
//25.
__int16 __stdcall rf_changeb3(__int32 icdev,unsigned char _SecNr,unsigned char *_KeyA,unsigned char _B0,unsigned char _B1,unsigned char _B2,unsigned char _B3,unsigned char _Bk,unsigned char *_KeyB);
//26.
__int16 __stdcall rf_get_status(__int32 icdev,unsigned char *_Status);
//27.
__int16 __stdcall rf_clr_control_bit(__int32 icdev,unsigned char _b);
//28.
__int16 __stdcall rf_set_control_bit(__int32 icdev,unsigned char _b);
//29.
__int16 __stdcall rf_reset(__int32 icdev,unsigned __int16 _Msec);
//30.
__int16 __stdcall rf_HL_decrement(__int32 icdev,unsigned char _Mode,unsigned char _SecNr,unsigned long _Value,unsigned long _Snr,unsigned long *_NValue,unsigned long *_NSnr);
//31.
__int16 __stdcall rf_HL_increment(__int32 icdev,unsigned char _Mode,unsigned char _SecNr,unsigned long _Value,unsigned long _Snr,unsigned long *_NValue,unsigned long *_NSnr);
//32.
__int16 __stdcall rf_HL_write(__int32 icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data);
//33.
__int16 __stdcall rf_HL_writehex(__int32 icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr, char *_Data);
//34
__int16 __stdcall rf_HL_read(__int32 icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
//35
__int16 __stdcall rf_HL_readhex(__int32 icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr, char *_Data,unsigned long *_NSnr);
//36.
__int16 __stdcall rf_HL_initval(__int32 icdev,unsigned char _Mode,unsigned char _SecNr,unsigned long _Value,unsigned long *_Snr);
//37.
__int16 __stdcall rf_beep(__int32 icdev,unsigned short _Msec);
//38.
__int16 __stdcall rf_disp8(__int32 icdev,__int16 pt_mode,unsigned char* disp_str);
//39.
__int16 __stdcall rf_disp(__int32 icdev,unsigned char pt_mode,unsigned short digit);
//40.
__int16 __stdcall rf_encrypt(unsigned char *key,unsigned char *ptrSource, unsigned __int16 msgLen,unsigned char *ptrDest);
//41.
__int16 __stdcall rf_decrypt(unsigned char *key,unsigned char *ptrSource, unsigned __int16 msgLen,unsigned char *ptrDest);
//42
__int16 __stdcall rf_HL_authentication(__int32 icdev,unsigned char reqmode,unsigned long snr,unsigned char authmode,unsigned char secnr);
//43
__int16 __stdcall rf_srd_eeprom(__int32 icdev,__int16 offset,__int16 lenth,unsigned char *rec_buffer);
//44
__int16 __stdcall rf_swr_eeprom(__int32 icdev,__int16 offset,__int16 lenth,unsigned char* send_buffer);
//45
__int16 __stdcall rf_srd_snr(__int32 icdev,__int16 lenth,unsigned char *rec_buffer);
//46
__int16 __stdcall rf_check_write(__int32 icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char * _data);
//47
__int16 __stdcall rf_check_writehex(__int32 icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr, char * _data);
//48
__int16 __stdcall rf_authentication_2(__int32 icdev,unsigned char _Mode,unsigned char KeyNr,unsigned char Adr);
//49
__int16 __stdcall rf_decrement_transfer(__int32 icdev,unsigned char Adr,unsigned long _Value);
//50
__int16 __stdcall rf_setport(__int32 icdev,unsigned char _Byte);
//51
__int16 __stdcall rf_getport(__int32 icdev,unsigned char *receive_data);
//52
__int16 __stdcall rf_gettime(__int32 icdev,unsigned char *time);
//53
__int16 __stdcall rf_gettimehex(__int32 icdev,char *time);
//54
__int16 __stdcall rf_settime(__int32 icdev,unsigned char *time);
//55
__int16 __stdcall rf_settimehex(__int32 icdev,char *time);
//56
__int16 __stdcall rf_setbright(__int32 icdev,unsigned char bright);
//57
__int16 __stdcall rf_ctl_mode(__int32 icdev,unsigned char mode);
//58
__int16 __stdcall rf_disp_mode(__int32 icdev,unsigned char mode);
//59
__int16 __stdcall lib_ver(unsigned char *str_ver);
//60
__int16 __stdcall rf_comm_check(__int32 icdev,unsigned char _Mode);
//61
__int16 __stdcall set_host_check(unsigned char _Mode);
//62
__int16 __stdcall set_host_485(unsigned char _Mode);
//63
__int16 __stdcall rf_set_485(__int32 icdev,unsigned char _Mode);
//64
__int16 __stdcall hex_a(unsigned char *hex,char *a,unsigned char length);
//65
__int16 __stdcall a_hex(char *a,unsigned char *hex,unsigned char len);
//66
__int16 __stdcall srd_alleeprom(__int32 icdev,__int16 offset,__int16 len,unsigned char *receive_buffer);
//67
__int16 __stdcall swr_alleeprom(__int32 icdev,__int16 offset,__int16 len,unsigned char* send_buffer);
//68
__int16 __stdcall rf_swr_snr(__int32 icdev,__int16 lenth,unsigned char* send_buffer);
//69
__int16 __stdcall rf_sam_rst(__int32 icdev, unsigned char baud, unsigned char *samack);
//70
__int16 __stdcall rf_sam_trn(__int32 icdev, unsigned char *samblock,unsigned char *recv);
//71
__int16 __stdcall rf_sam_off(__int32 icdev);
//72
__int16 __stdcall mf2_protocol(__int32 icdev,unsigned __int16 timeout,unsigned char slen,char *dbuff);
//73
__int16 __stdcall rf_cpu_rst(__int32 icdev, unsigned char baud, unsigned char *cpuack);
//74
__int16 __stdcall rf_cpu_trn(__int32 icdev, unsigned char *cpublock,unsigned char *recv);
//75
__int16 __stdcall rf_pro_rst(__int32 icdev,unsigned char *_Data);
//76
__int16 __stdcall rf_pro_trn(__int32 icdev,unsigned char *problock,unsigned char *recv);
//77
__int16 __stdcall rf_pro_halt(__int32 icdev);
//78
void __stdcall Set_Reader_Mode(unsigned char _Mode);



}