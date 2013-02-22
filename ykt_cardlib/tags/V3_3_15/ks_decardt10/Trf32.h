/*! \file Trf32.h
 *  \brief 用户接口声明头文件
 *
 *  此文件包含用户可以使用的定义、函数等相关声明。
 */

#if defined(__cplusplus)
extern "C" {
#endif
 
#if defined(OS_VER_LINUX) || defined(OS_VER_UNIX)
#define __stdcall
#endif
 
#define	 KEY_DIGIT0		0x45
#define	 KEY_DIGIT1		0x16
#define	 KEY_DIGIT2		0x1E
#define	 KEY_DIGIT3		0x26
#define	 KEY_DIGIT4		0x25
#define	 KEY_DIGIT5		0x2E
#define	 KEY_DIGIT6		0x36
#define	 KEY_DIGIT7		0x3D
#define	 KEY_DIGIT8		0x3E
#define	 KEY_DIGIT9		0x46
#define	 KEY_DOT		0x49
#define	 KEY_F1			0x05
#define	 KEY_F2			0x06
#define	 KEY_F3			0x04
#define	 KEY_F4			0x0C
#define	 KEY_F5			0x03
#define	 KEY_F6			0x0B
#define	 KEY_ESC		0x76
#define  KEY_CANCEL		0x66
#define  KEY_ENTER		0x5A

	/*! \brief 初始化通讯口
	 *  \par 说明:
	 *  用来初始化通讯口，成功后返回的通讯设备标识符当在不使用的时候必须用DC_exit_comm将其关闭。
	 *  \param[in] DeviceName 通讯设备名称，一般为"COM1"、"COM2"......。
	 *  \param[in] Baudrate 通讯波特率，取值为9600～115200。
	 *  \return 如果<0表示失败，否则为通讯设备标识符。
	 *  \par 示例:
	 *  \code
	 *  long icdev;
	 *  icdev = DC_init_comm("COM1", 115200);
	 *  \endcode
	 */
	long __stdcall DC_init_comm(const char *DeviceName, unsigned long Baudrate);

	/*! \brief 关闭通讯口
	 *  \par 说明:
	 *  用来关闭之前成功调用DC_init_comm打开的通讯口。
	 *  \param[in] DeviceHandle 通讯设备标识符。
	 *  \return 如果<0表示失败，否则表示成功。
	 *  \par 示例:
	 *  \code
	 *  long result;
	 *  result = DC_exit_comm(icdev);
	 *  \endcode
	 */
	long __stdcall DC_exit_comm(long DeviceHandle);

	/*! \brief 查询身份证卡
	 *  \par 说明:
	 *  查询身份证卡是否存在。
	 *  \param[in] DeviceHandle 通讯设备标识符。
	 *  \return 如果<0表示失败，否则表示成功。
	 *  \par 示例:
	 *  \code
	 *  long result;
	 *  result = DC_find_i_d(icdev);
	 *  \endcode
	 */
	long __stdcall DC_find_i_d(long DeviceHandle);

	/*! \brief 开始读身份证卡操作
	 *  \par 说明:
	 *  用于读取身份证卡信息，调用成功后，读出的身份证卡信息将保存在库内部存储中，可以使用以DC_i_d_query_开头的函数去读取这些内部存储中的信息，不再使用内部存储中的信息时必须调用DC_end_i_d进行释放。
	 *  \param[in] DeviceHandle 通讯设备标识符。
	 *  \return 如果=-1表示失败，否则为身份证卡信息标识符。
	 *  \par 示例:
	 *  \code
	 *  long IdHandle;
	 *  IdHandle = DC_start_i_d(icdev);
	 *  \endcode
	 */
	long __stdcall DC_start_i_d(long DeviceHandle);

	/*! \brief 取身份证卡姓名
	 *  \par 说明:
	 *  从库内部存储中取身份证卡姓名信息
	 *  \param[in] IdHandle 身份证卡信息标识符。
	 *  \return 如果=0表示失败，否则指向身份证卡姓名信息。
	 *  \par 示例:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_name(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_name(long IdHandle);
	
	/*! \brief 取身份证卡性别
	 *  \par 说明:
	 *  从库内部存储中取身份证卡性别信息
	 *  \param[in] IdHandle 身份证卡信息标识符。
	 *  \return 如果=0表示失败，否则指向身份证卡性别信息。
	 *  \par 示例:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_sex(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_sex(long IdHandle);
	
	/*! \brief 取身份证卡民族
	 *  \par 说明:
	 *  从库内部存储中取身份证卡民族信息
	 *  \param[in] IdHandle 身份证卡信息标识符。
	 *  \return 如果=0表示失败，否则指向身份证卡民族信息。
	 *  \par 示例:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_nation(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_nation(long IdHandle);
	
	/*! \brief 取身份证卡出生日期
	 *  \par 说明:
	 *  从库内部存储中取身份证卡出生日期信息
	 *  \param[in] IdHandle 身份证卡信息标识符。
	 *  \return 如果=0表示失败，否则指向身份证卡出生日期信息。
	 *  \par 示例:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_birth(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_birth(long IdHandle);
	
	/*! \brief 取身份证卡住址
	 *  \par 说明:
	 *  从库内部存储中取身份证卡住址信息
	 *  \param[in] IdHandle 身份证卡信息标识符。
	 *  \return 如果=0表示失败，否则指向身份证卡住址信息。
	 *  \par 示例:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_address(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_address(long IdHandle);
	
	/*! \brief 取身份证卡证件号码
	 *  \par 说明:
	 *  从库内部存储中取身份证卡证件号码信息
	 *  \param[in] IdHandle 身份证卡信息标识符。
	 *  \return 如果=0表示失败，否则指向身份证卡证件号码信息。
	 *  \par 示例:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_id_number(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_id_number(long IdHandle);
	
	/*! \brief 取身份证卡签发机关
	 *  \par 说明:
	 *  从库内部存储中取身份证卡签发机关信息
	 *  \param[in] IdHandle 身份证卡信息标识符。
	 *  \return 如果=0表示失败，否则指向身份证卡签发机关信息。
	 *  \par 示例:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_department(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_department(long IdHandle);
	
	/*! \brief 取身份证卡有效期限
	 *  \par 说明:
	 *  从库内部存储中取身份证卡有效期限信息
	 *  \param[in] IdHandle 身份证卡信息标识符。
	 *  \return 如果=0表示失败，否则指向身份证卡有效期限信息。
	 *  \par 示例:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_expire_day(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_expire_day(long IdHandle);
	
	/*! \brief 取身份证卡照片数据信息
	 *  \par 说明:
	 *  从库内部存储中取身份证卡照片数据信息，必须联合DC_i_d_query_photo_len一起使用。
	 *  \param[in] IdHandle 身份证卡信息标识符。
	 *  \return 如果=0表示失败，否则指向身份证卡照片数据信息。
	 *  \par 示例:
	 *  \code
	 *  unsigned char *p;
	 *  p = DC_i_d_query_photo(IdHandle);
	 *  \endcode
	 */
	unsigned char* __stdcall DC_i_d_query_photo(long IdHandle);
	
	/*! \brief 取身份证卡照片数据长度信息
	 *  \par 说明:
	 *  从库内部存储中取身份证卡照片数据长度信息，必须联合DC_i_d_query_photo一起使用。
	 *  \param[in] IdHandle 身份证卡信息标识符。
	 *  \return 如果=0表示失败，否则指向身份证卡照片数据长度信息。
	 *  \par 示例:
	 *  \code
	 *  unsigned char *p;
	 *  p = DC_i_d_query_photo_len(IdHandle);
	 *  \endcode
	 */
	unsigned long __stdcall DC_i_d_query_photo_len(long IdHandle);

	/*! \brief 取身份证卡照片文件
	 *  \par 说明:
	 *  从库内部存储中取身份证卡照片数据并且存储为BMP文件。
	 *  \param[in] IdHandle 身份证卡信息标识符。
	 *  \param[in] FileName 要保存的BMP文件名。
	 *  \return 如果<0表示失败，否则表示成功。
	 *  \par 示例:
	 *  \code
	 *  long result;
	 *  result = DC_i_d_query_photo_file(IdHandle, "C:\\me.bmp");
	 *  \endcode
	 */
	long __stdcall DC_i_d_query_photo_file(long IdHandle, const char *FileName);

	/*! \brief 取身份证卡照片文件的BMP格式数据
	 *  \par 说明:
	 *  从库内部存储中取身份证卡照片数据并且存储为BMP格式。
	 *  \param[in] IdHandle 身份证卡信息标识符。
	 *  \param[in] BmpBuffer 要保存的BMP格式缓冲区。
	 *  \param[in,out] BmpLength 传入缓冲区大小，调用成功后返回实际使用的大小。
	 *  \return 如果<0表示失败，否则表示成功。
	 *  \par 示例:
	 *  \code
	 *  long result;
	 *  unsigned char BmpBuffer[4096];
	 *  unsigned long BmpLength;
	 *  result = DC_i_d_query_photo_file(IdHandle, BmpBuffer, &BmpLength);
	 *  \endcode
	 */
	long __stdcall DC_i_d_query_photo_bmp_buffer(long IdHandle, unsigned char *BmpBuffer, unsigned long *BmpLength);
	
	
	/*! \brief 结束读取身份证卡操作
	 *  \par 说明:
	 *  用来释放之前成功调用DC_start_i_d分配的资源。
	 *  \param[in] IdHandle 身份证卡信息标识符。
	 *  \par 示例:
	 *  \code
	 *  DC_end_i_d(IdHandle);
	 *  \endcode
	 */
	void __stdcall DC_end_i_d(long IdHandle);

	/*! \brief 初始化通讯口
	 *  \par 说明:
	 *  用来初始化通讯口，成功后返回的通讯设备标识符当在不使用的时候必须用dc_exit将其关闭。
	 *  \param[in] port 取值为0～19时，表示串口1～20；为100时，表示USB口通讯，此时波特率无效。
	 *  \param[in] baud 通讯波特率，取值为9600～115200。
	 *  \return 如果<0表示失败，否则为通讯设备标识符。
	 *  \par 示例:
	 *  \code
	 *  long icdev;
	 *  icdev = dc_init(0, 115200);
	 *  \endcode
	 */
	long __stdcall dc_init(long port, unsigned long baud);
	
	/*! \brief 关闭通讯口
	 *  \par 说明:
	 *  用来关闭之前成功调用dc_init打开的通讯口。
	 *  \param[in] icdev 通讯设备标识符。
	 *  \return 如果<0表示失败，否则表示成功。
	 *  \par 示例:
	 *  \code
	 *  long result;
	 *  result = dc_exit(icdev);
	 *  \endcode
	 */
	long __stdcall dc_exit(long icdev);
	
	/*! \brief 蜂鸣
	 *  \par 说明:
	 *  控制设备蜂鸣。
	 *  \param[in] icdev 通讯设备标识符。
	 *  \param[in] ms 蜂鸣时间，以10毫秒为单位。
	 *  \return 如果<0表示失败，否则表示成功。
	 *  \par 示例:
	 *  \code
	 *  long result;
	 *  result = dc_beep(icdev, 10);
	 *  \endcode
	 */
	long __stdcall dc_beep(long icdev, unsigned short ms);
	
	/*! \brief 读取设备存储
	 *  \par 说明:
	 *  设备内部含有一块存储区域可以使用，具体大小可参见硬件规格，此函数用于读取这部分区域。
	 *  \param[in] icdev 通讯设备标识符。
	 *  \param[in] offset 偏移地址（offset+len必须小于设备存储区域的大小）。
	 *  \param[in] len 长度（offset+len必须小于设备存储区域的大小）。
	 *  \param[out] data_buffer 读取到的信息。
	 *  \return 如果<0表示失败，否则表示成功。
	 *  \par 示例:
	 *  \code
	 *  long result;
	 *  unsigned char data_buffer[4];
	 *  result = dc_srd_eeprom(icdev, 0, 4, data_buffer);
	 *  \endcode
	 */
	long __stdcall dc_srd_eeprom(long icdev, unsigned long offset, unsigned long len, unsigned char *data_buffer);
	
	/*! \brief 读取设备存储（HEX形式）
	 *  \par 说明:
	 *  dc_srd_eeprom函数的HEX形式，字符串数据将以HEX形式传递。
	 */
	long __stdcall dc_srd_eepromhex(long icdev, unsigned long offset, unsigned long len, unsigned char *data_buffer);

	/*! \brief 写入设备存储
	 *  \par 说明:
	 *  设备内部含有一块存储区域可以使用，具体大小可参见硬件规格，此函数用于写入这部分区域。
	 *  \param[in] icdev 通讯设备标识符。
	 *  \param[in] offset 偏移地址（offset+len必须小于设备存储区域的大小）。
	 *  \param[in] len 长度（offset+len必须小于设备存储区域的大小）。
	 *  \param[in] data_buffer 要写入的信息。
	 *  \return 如果<0表示失败，否则表示成功。
	 *  \par 示例:
	 *  \code
	 *  long result;
	 *  unsigned char data_buffer[4] = {0x31, 0x32, 0x33, 0x34};
	 *  result = dc_swr_eeprom(icdev, 0, 4, data_buffer);
	 *  \endcode
	 */
	long __stdcall dc_swr_eeprom(long icdev, unsigned long offset, unsigned long len, const unsigned char *data_buffer);
	
	/*! \brief 写入设备存储（HEX形式）
	 *  \par 说明:
	 *  dc_swr_eeprom函数的HEX形式，字符串数据将以HEX形式传递。
	 */
	long __stdcall dc_swr_eepromhex(long icdev, unsigned long offset, unsigned long len, const unsigned char *data_buffer);
	
	/*! \brief 获得硬件版本号
	 *  \par 说明:
	 *  设备内维护了一个硬件版本号，表示当前设备的版本，用此函数可以获得这个版本号。
	 *  \param[in] icdev 通讯设备标识符。
	 *  \param[out] data_buffer 存放版本号的缓冲区，长度固定为4字节（包括结束字符’\\0’）。
	 *  \return 如果<0表示失败，否则表示成功。
	 *  \par 示例:
	 *  \code
	 *  long result;
	 *  unsigned char data_buffer[4];
	 *  result = dc_getver(icdev, data_buffer);
	 *  \endcode
	 */
	long __stdcall dc_getver(long icdev, unsigned char *data_buffer);
	
	/*! \brief 设置设备波特率
	 *  \par 说明:
	 *  设备支持以不同的波特率通讯，通过此函数设置成功后，必须关闭通讯口再重新以相应的波特率初始化通讯口才能正常操作设备。
	 *  \param[in] icdev 通讯设备标识符。
	 *  \param[in] baud 通讯波特率，取值为9600～115200。
	 *  \return 如果<0表示失败，否则表示成功。
	 *  \par 示例:
	 *  \code
	 *  long result;
	 *  result = dc_set_baudrate(icdev, 9600);
	 *  \endcode
	 */
	long __stdcall dc_set_baudrate(long icdev, unsigned long baud);

	/*! \brief 寻卡请求
	 *  \par 说明:
	 *  搜寻感应区内的卡片。dc_request、dc_anticoll、dc_select通常结合使用，这种情况下也可以使用dc_card函数。
	 *  \param[in] icdev 通讯设备标识符。
	 *  \param[in] _Mode 0表示IDLE模式，一次只对一张卡操作；1表示ALL模式，一次可对多张卡操作。
	 *  \param[out] TagType 卡类型值。
	 *  \return 如果<0表示失败，否则表示成功（其中无卡=1，有卡=0）。
	 *  \par 示例:
	 *  \code
	 *  long result;
	 *  unsigned short TagType;
	 *  result = dc_request(icdev, 0, &TagType);
	 *  \endcode
	 */
	long __stdcall dc_request(long icdev, unsigned char _Mode, unsigned short *TagType);
	
	/*! \brief 防卡冲突
	 *  \par 说明:
	 *  此函数用来返回卡片的序列号。dc_request、dc_anticoll、dc_select通常结合使用，这种情况下也可以使用dc_card函数。
	 *  \param[in] icdev 通讯设备标识符。
	 *  \param[in] _Bcnt 固定为0。
	 *  \param[out] _Snr 卡序列号。
	 *  \return 如果<0表示失败，否则表示成功。
	 *  \par 示例:
	 *  \code
	 *  long result;
	 *  unsigned long _Snr;
	 *  result = dc_anticoll(icdev, 0, &_Snr);
	 *  \endcode
	 */
	long __stdcall dc_anticoll(long icdev, unsigned char _Bcnt, unsigned long *_Snr);
	
	/*! \brief 选取卡片
	 *  \par 说明:
	 *  选取一个给定序列号的卡。dc_request、dc_anticoll、dc_select通常结合使用，这种情况下也可以使用dc_card函数。
	 *  \param[in] icdev 通讯设备标识符。
	 *  \param[in] _Snr 卡序列号。
	 *  \param[out] _Size 卡容量。
	 *  \return 如果<0表示失败，否则表示成功。
	 *  \par 示例:
	 *  \code
	 *  long result;
	 *  unsigned short TagType;
	 *  unsigned long _Snr;
	 *  dc_request(icdev, 0, &TagType);
	 *  dc_anticoll(icdev, 0, &_Snr);
	 *  result = dc_select(icdev, _Snr, &_Size);
	 *  \endcode
	 */
	long __stdcall dc_select(long icdev, unsigned long _Snr, unsigned char *_Size);
	
	/*! \brief 寻卡
	 *  \par 说明:
	 *	返回在工作区域内某张卡的序列号(该函数包含了de_request、dc_anticoll、dc_select的整体功能)。
	 *  \param[in] icdev 通讯设备标识符。
	 *	\param[in] _Mode 0表示IDLE模式，一次只对一张卡操作；1表示ALL模式，一次可对多张卡操作。
	 *	\param[out] _Snr 卡序列号。
	 *	\return 如果<0失败，否则表示成功。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	unsigned long snr;
	 *	st = dc_card(icdev, 0, &snr);
	 *	\endcode
	 *	\par 注意:
	 *	选择IDLE模式，在对卡进行读写操作，执行dc_halt()指令中止卡操作后，
	 *	只有当该卡离开并再次进入操作区时，读写器才能够再次对它进行操作。
	 */
	long __stdcall dc_card(long icdev,unsigned char _Mode,unsigned long *_Snr);
	
	/*! \brief 下载设备密码
	 *	\par 说明:
	 *	将密码装入读写模块RAM中。
	 *	\param[in] icdev 通讯设备标识符。
	 *	\param[in] _Mode 0表示A密码；4表示B密码,与核对密码函数对应。
	 *	\param[in] _SecNr 扇区号(M1卡:0~15)。
	 *	\param[in] _NKey 写入读写器中的卡密码。
	 *	\return 如果<0失败，否则表示成功。
	 *	\par 示例：
	 *	\code
	 *	unsigned char password[7] = {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5};		//KeyA 或者KeyB;
	 *	if(dc_load_key(icdev, 0, 1, password) != 0)		//装入1扇区的A密码；
	 *	{
	 *		printf("Load Key Error!");
	 *		dc_exit(icdev);
	 * 	}
	 *	\endcode
	 */
	long __stdcall dc_load_key(long icdev,unsigned char _Mode,unsigned char _SecNr,unsigned char *_NKey);
	
  /*! \brief 下载设备密码（HEX形式）
	 *  \par 说明:
	 *  dc_load_key函数的HEX形式，字符串数据将以HEX形式传递。
	 */
	long __stdcall dc_load_key_hex(long icdev,unsigned char _Mode,unsigned char _SecNr,unsigned char *_NKey);
	
	/*! \brief 核对密码
	 *	\par 说明:
	 *	核对扇区中的密码。
	 *	\param[in] icdev 通讯设备标识符。
	 *	\param[in] _Mode 0表示A密码；4表示B密码，与下载设备密码函数对应。
	 *	\param[in] _SecNr 要核对密码的扇区号。
	 *	\return 如果< 0失败，否则表示成功。
	 */
	long __stdcall dc_authentication(long icdev,unsigned char _Mode,unsigned char _SecNr);
	
	/*! \brief 核对密码
	 *	\par 说明:
	 *	用此函数时，可以不执行dc_load_key函数(只支持M1和S70卡)。
	 *	\param[in] icdev 通讯设备标识符。
	 *	\param[in] _Mode 0表示A密码，4表示B密码。
 	 *	\param[in] _SecAddr 要核对的扇区存放密码的块号。
 	 *	\param[in] passbuff 密码字符串。
	 *	\return 如果< 0失败，否则表示成功。
	 */
	long __stdcall dc_authentication_pass(long icdev,unsigned char _Mode,
										  unsigned char _SecAddr,unsigned char *passbuff);
										  
  /*! \brief 中止操作
   *	\par 说明:
   *	中止对卡的操作。
   *	\param[in] icdev 通讯设备标识符。
   *	\return 成功则返回0。
   *	\par 示例:
   *	\code
   *	int st;
   *	st = dc_halt(icdev);
   *	\endcode
   *	\par 说明:
   *	使用dc_card(icdev)函数时，有个_Mode参数，如果_Mode = 0,则对卡进行操作完毕后，
   *	执行dc_halt(icdev);则该卡进入HALT模式，则必须把卡移开感应区才能寻到这张卡。
   */
	long __stdcall dc_halt(long icdev);
	
	/*! \brief 读卡
	 *	\par 说明:
	 *	读取卡中数据，一次读取一个块的数据，为16个字节。
	 *	\param[in] icdev 通讯设备标识符。
	 *	\param[in] _Adr 块地址（M1卡(0~63), MS70卡(0~255)）。
	 *	\param[in] _Data 读出数据。
	 *	\return 如果<0则失败，否则表示成功。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	unsigned char data[16];
	 *	st = dc_read(icdev, 4, data);		//读M1卡块4的数据；
	 *	\endcode
	 */
	long __stdcall dc_read(long icdev,unsigned char _Adr,unsigned char *_Data);
	
	/*! \brief 读卡(HEX形式)
	 *	\par 说明:
	 *	dc_read函数的HEX形式，字符串数据将以HEX形式传递。
	 */
	long __stdcall dc_read_hex(long icdev,unsigned char _Adr,unsigned char *_Data);
	
	/*! \brief 写卡
	 *	\par 说明:
	 *	向卡中写入数据。一次必须写一个块，为16个字节。
	 *	\param[in] icdev 通讯设备标识号。
	 *	\param[in] _Adr 块地址（M1卡(0~63), MS70卡(0~255)）。
	 *	\param[in] _Data 要写入的数据。
	 *	\return 如果<0则失败，否则表示成功。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	unsigned char *data = "1234567890123456";
	 *	st = dc_write(icdev, 4, data);		//写第四块。
	 *	\endcode
	 */
	long __stdcall dc_write(long icdev,unsigned char _Adr,unsigned char *_Data);
	
	/*! \brief 写卡（HEX形式）
	 *	\par 说明:
	 *	向卡中写入数据。数据以HEX形式传递。
	 */
	long __stdcall dc_write_hex(long icdev,unsigned char _Adr,unsigned char *_Data);
	
	/*! \brief 初始化块值
	 *	\par 说明:
	 *	初始化块的值。
	 *	\param[in] icdev 通讯设备标识符。
	 *	\param[in] _Adr 地址块。
	 *	\param[in] _Value 初始值。
	 *	\return 如果<0则失败，否则表示成功。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	unsigned long value;
	 *	value = 1000;		//给value赋值。
	 *	st = dc_initval(icdev, 1, value);		//将块1的值初始为1000。
	 *	\endcode
	 *	\par 注意:
	 *	在进行值操作时，必须先执行初始化函数，然后才可以读、减、加的操作。
	 */
	long __stdcall dc_initval(long icdev,unsigned char _Adr,unsigned long _Value);
	
	/*!	\brief 加值
	 *	\par 说明:
	 *	块加值
	 *	\param[in] icdev 通讯设备标识符。
	 *	\param[in] _Adr 块地址。
	 *	\param[in] _Value 要增加的值。
	 *	\return 如果<0则失败，否则表示成功。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	unsigned long value;
	 *	value = 10;
	 *	st = dc_increment(icdev, 1, value);		//将块1的值增加10。
	 *	\endcode
	 */
	long __stdcall dc_increment(long icdev,unsigned char _Adr,unsigned long _Value);
	
	/*!	\brief 减值
	 *	\par 说明:
	 *	块减值
	 *	\param[in] icdev 通讯设备标志。
	 *	\param[in] _Adr 块地址。
	 *	\param[in] _Value 要减的值。
	 *	\return 如果<0则失败，否则表示成功。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	unsigned long value;
	 *	value = 10;
	 *	st = dc_decrement(icdev, 1, value);		//将块1的值减少10。
	 *	\endcode
	 */
	long __stdcall dc_decrement(long icdev,unsigned char _Adr,unsigned long _Value);
	
	/*!	\brief 读块值
	 *	\par 说明:
	 *	读出块的值。
	 *	\param[in] icdev 通讯标识符。
	 *	\param[in] _Adr 块地址。
	 *	\param[out] _Value 读出值的地址。
	 *	\return 如果< 0则失败，否则表示成功。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	unsigned long value;
	 *	st = dc_readval(icdev, 1, &value);		//读出块1的值，放入value中。
	 *	\endcode
	 */
	long __stdcall dc_readval(long icdev,unsigned char _Adr,unsigned long *_Value);
	long __stdcall dc_valuebackup(long icdev,unsigned char _OriginalAdr,unsigned char _BackupAdr);
	
	/*! \brief 设置卡座
	 *	\par 说明:
	 *	设置要操作的SAM卡座。
	 *	\param[in] icdev 通讯设备标识符。
	 *	\param[in] Cardtype 要操作的卡座号。（0x0c表示附卡座,0x0d表示为SAM1,0x0e表示为SAM2）
	 *	\return 如果< 0则失败，否则表示成功。
	 */
	long __stdcall dc_setcpu(long icdev,unsigned char Cardtype);
	
	/*! \brief 上电复位
	 *	\par 说明:
	 *	CPU卡上电复位函数，复位后自动判断卡片协议。
	 *	\param[in] icdev 通讯设备标识符。
	 *	\param[in] cardtype 要操作的卡座号。（1表示SIM1,2表示SIM2,3表示大卡座）。		//注意和dc_setcpu参数值意义的不同。
	 *	\param[in] baudrate 1表示9600，2表示14400，3表示19200，4表示38400，5表示57600，6表示115200。
	 *	\param[in] Volt 2表示3.3V, 3表示5.0V。
	 *	\param[out] rlen 返回复位信息的长度。
	 *	\param[out] databuffer 存放返回的复位信息。
	 *	\param[in]	protocol 返回卡片协议（0表示T = 0, 1表示 T = 1）。
	 *	\return 如果< 0则表示失败，否则表示成功。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	unsigned char *rlen, DataBuffer;
	 *	st = dc_cpureset(icdev, 3, 1, 2, rlen, DataBuffer, 0);		//复位大卡座。
	 *	\endcode
	 */
	long __stdcall dc_cpureset(long icdev,unsigned char cardtype,unsigned char baudrate,
							   unsigned char Volt,unsigned char *rlen,unsigned char *databuffer,unsigned char *protocol);
							   
	/*! \brief CPU上电复位(HEX形式)
	 *	\par 说明:
	 *	dc_setcpu函数的HEX形式，字符串数据将以HEX形式传递。
	 */
	long __stdcall dc_cpureset_hex(long icdev,unsigned char cardtype,unsigned char baudrate,
								   unsigned char Volt,unsigned char *rlen,unsigned char *databuffer,unsigned char *protocol);
			 					   
	/*! \brief 信息交换函数（未封装）
	 *	\par 说明:
	 *	CPU卡APDU（应用协议数据单元）信息交换函数。该函数未封装，用户需自行判断协议类型并组织数据发送。
	 *	\param[in] icdev 设备端口标识符。
	 *	\param[in] Cardtype 要操作的卡座号。（0x0c表示附卡座,0x0d表示为SAM1,0x0e表示为SAM2）。
	 *	\param[in] slen 发送的信息长度。
	 *	\param[in] sendbuffer 存放要发送的信息。
	 *	\param[out] rlen 返回信息的长度。
	 *	\param[out] databuffer 存放返回的信息。
	 *	\param[in] protocol 存放返回的卡片协议。（0表示T = 0, 1表示T = 1）
	 *	\return 如果< 0表示失败，= 0表示成功。
	 *	\par 示例:
	 *	\code
	 *	int i, st;
	 *	unsigned char slen, rlen, sdata[100], rdata[100];
	 *	slen = 5;
	 *	sdata[0] = nad;	 sdata[1] = pcd;  sdata[2] = 5;
	 *	sdata[3] = 0x00; sdata[4] = 0x84; sdata[5] =0x00;
	 *	sdata[6] = 0x00; sdata[7] = 0x08;
	 *	for(i = 0; i < 8; i++)
	 *      {
	 *        sdata[8] ^= sdata[i];		//计算异或和。
	 *       };
	 *	st = dc_cpuapdusource(icdev, slen, sdata, &rlen, rdata, 0);
	 *	\endcode
	 */
	long __stdcall dc_cpuapdusource(long icdev,unsigned char Cardtype,unsigned char slen,unsigned char * sendbuffer,
									unsigned char *rlen,unsigned char * databuffer,unsigned char protocol);
									
	/*! \brief 信息交换函数（未封装HEX形式）
	 *	\par 说明:
	 *	CPU卡APDU（应用协议数据单元）信息交换函数。该函数未封装，用户需自行判断协议类型并组织数据发送。
	 *	字符串数据将以HEX形式传递。
	 */
	long __stdcall dc_cpuapdusource_hex(long icdev,unsigned char Cardtype,unsigned char slen,unsigned char * sendbuffer,
										unsigned char *rlen,unsigned char * databuffer,unsigned char protocol);
										
	/*!	\brief 信息交换函数
	 *	\par 说明:
	 *	CPU卡APDU（应用协议数据单元）信息交换函数。该函数封装了T = 0和T = 1操作。
	 *	\param[in]	icdev 设备端口标识符。
	 *	\param[in]	Cardtype 要操作的卡座号。（0x0c表示附卡座,0x0d表示为SAM1,0x0e表示为SAM2）。
	 *	\param[in]	slen 发送的信息长度。
	 *	\param[in]	sendbuffer 存放要发送的信息。
	 * 	\param[out]	rlen 返回信息的长度。
	 *	\param[out]	databuffer 存放返回的信息。
	 *	\param[in]	protocol 存放返回的卡片协议。（0表示T = 0, 1表示T = 1。）
	 *	\return 如果<0表示失败，否则表示成功。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	unsigned char slen, rlen, sdata[100], rdata[100];
	 *	slen = 5;
	 *	sdata[0] = 0x00; sdata[1] = 0x84; sdata[2] = 0x00; sdata[3] = 0x00; sdata[4] = 0x04;
	 *	st = dc_cpuapdu(icdev, slen, sdata, &rlen, rdata, 0);		//对卡发取随机数命令。
	 *	\endcode
	 */
	long __stdcall dc_cpuapdu(long icdev,unsigned char Cardtype,unsigned char slen,unsigned char * sendbuffer,
							  unsigned char *rlen,unsigned char * databuffer,unsigned char protocol);
							  
	/*!	\brief 信息交换函数（HEX形式）
	 *	\par 说明:
	 *	CPU卡APDU（应用协议数据单元）信息交换函数的HEX形式，字符串数据将以HEX形式传递。
	 */
	long __stdcall dc_cpuapdu_hex(long icdev,unsigned char Cardtype,unsigned char slen,unsigned char * sendbuffer,
								  unsigned char *rlen,unsigned char * databuffer,unsigned char protocol);
								  
	/*!	\brief 射频复位
	 *	\par 说明:
	 *	复位射频操作。
	 *	\param[in] icdev 设备端口标识符。
	 *	\return 成功则返回0，否则表示失败。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	st = dc_reset(icdev);
	 *	\endcode
	 */
	long __stdcall dc_reset(long icdev);

	/*!	\brief 设置卡型
	 *	\par 说明:
	 *	设置读写器要对哪一种卡操作。
	 *	\param[in] icdev 设备端口标识符。
	 *	\param[in] cardtype 设置卡型（A表示对TYPEA卡操作，B表示对TYPEB卡操作）。
	 *	\return 成功则返回0，否则表示失败。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	st = dc_config_card(icdev, 'B');		//设置对TYPEB型卡进行操作。
	 *	\endcode
	 */
	long __stdcall dc_config_card(long icdev,unsigned char cardtype);
	
	/*!	\brief 寻卡函数
	 *	\par 说明:
	 *	CPU卡寻卡函数
	 *	\param[in] icdev 设备端口标识符。
	 *	\param[out] rlen 返回卡号的长度。
	 *	\param[out] _Snr 返回16进制的卡号。
	 *	\return 如果 = 0 表示成功，< 0 表示失败。
	 *	\par 示例:
	 *	\code
	 *	long st;
	 *	unsigned char rlen;
	 *	unsigned char snr[32] = {0};
	 *	st = dc_card_pro(icdev, &rlen, snr);
	 *	\endcode
	 */
	long __stdcall dc_card_pro(long icdev,unsigned char *rlen,unsigned char *_Snr);
	
	/*! \brief 寻卡函数（HEX形式）
	 *	\par 说明:
	 *	CPU卡寻卡函数的HEX形式，字符串数据将以HEX形式传递。
	 */
	long __stdcall dc_card_prohex(long icdev,unsigned char *rlen,unsigned char *_Snr);
	
	/*!	\brief 上电复位
	 *	\par 说明:
	 *	TypeA卡上电复位
	 *	\param[in] icdev 设备端口标识符。
	 *	\param[out] rlen 返回的复位信息的长度。
	 *	\param[out] databuf 存放返回的复位信息。
	 *	\return 如果= 0表示成功，< 0表示失败。
	 *	\par 示例:
	 *	\code
	 *	long st;
	 *	unsigned char rlen;
	 *	unsigned char databuf[64] = {0};
	 *	st = dc_pro_reset(icdev, &rlen, databuf);
	 *	\endcode
	 */
	long __stdcall dc_pro_reset(long icdev,unsigned char *rlen,unsigned char *databuf);
	
	/*! \brief 上电复位（HEX形式）
	 *	\par 说明:
	 *	TypeA卡上电复位函数的HEX形式，字符串数据将以HEX形式传递。
	 */
	long __stdcall dc_pro_resethex(long icdev,unsigned char *rlen,unsigned char *databuf);
	
	/*!	\brief 信息交换函数
	 *	\par 说明:
	 *	TypeA或TypeB CPU卡APDU（应用协议数据单元）信息交换函数。
	 *	\param[in] icdev 设备端口标志。
	 *	\param[in] slen 发送信息的长度。
	 *	\param[in] sendbuffer 存放要发送的信息。
	 *	\param[out] rlen 返回信息的长度。
	 *	\param[out] databuffer 存放返回的信息。
	 *	\param[in] timeout 延迟时间，单位为:10ms。
	 *	\param[in] FG 分割长度，建议此值< 64。
	 *	\return 如果= 0表示成功，< 0则表示失败。
	 *	\par 示例:
	 *	\code
	 *	long st;
	 *	unsigned char slen, rlen, sdata[100], rdata[100];
	 *	slen = 5;
	 *	sdata[0] = 0x00; sdata[1] = 0x84; sdata[2] = 0x00; sdata[3] = 0x00; sdata[4] = 0x04;
	 *	st = dc_pro_commandlink(icdev, slen, sdata, &rlen, rdata, 7, 56);		//对卡发送取随机数命令。
	 *	\endcode
	 */
	long __stdcall dc_pro_commandlink(long icdev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,
									  unsigned char * databuffer,unsigned char timeout,unsigned char FG);
									  
	/*! \brief 信息交换函数（HEX形式）
	 *	\par 说明:
	 *	TypeA或TypeB CPU卡APDC（应用协议数据单元）信息交换函数的HEX形式，字符串数据将以HEX形式传递。
	 */
	long __stdcall dc_pro_commandlink_hex(long icdev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,
										  unsigned char * databuffer,unsigned char timeout,unsigned char FG);
	
	long __stdcall dc_pro_commandsource(long icdev,unsigned char slen,unsigned char * sendbuffer,
							 unsigned char *rlen,unsigned char * databuffer,unsigned char time);

	/*!	\brief 读取磁条卡数据
	 *	\param[in] icdev 设备端口标识符。
	 *	\param[in] ctime 等待用户刷卡的超时时间，以second为单元；最大255s，最小1s；超出该时间退出。
	 *	\param[out] pTrack1Data和pTrack1Len 返回轨道1的数据和长度。
	 *	\param[out] pTrack2Data和pTrack2Len 返回轨道2的数据和长度。
	 *	\param[out] pTrack3Data和pTrack3Len 返回轨道3的数据和长度。
	 *	\return 如果< 0表示失败，否则表示成功。
	 *	\par 示例:
	 *	\code
	 *	long result;
	 *	unsigned char rlen1, rlen2, rlen3;
	 *	unsigned char track1[64], track2[64], track3[64];
	 *	result = dc_readmagcardall(icdev, 2, track1, &rlen1, track2, &rlen2, track3, &rlen3);
	 *	\endcode
	 */
	long __stdcall dc_readmagcardall(long icdev, unsigned char ctime, unsigned char *pTrack1Data, unsigned long *pTrack1Len,
									 unsigned char *pTrack2Data, unsigned long *pTrack2Len, unsigned char *pTrack3Data, unsigned long *pTrack3Len);
	
	/*! \brief 获取键盘输入
	 *	\par 说明:
	 *	获取用户键盘密码的输入，该函数会一直等待用户输入直到超时。
	 *	\param[in] icdev 设备端口标识符。
	 *	\param[in] ctime 等待用户刷卡的超时时间，以second为单位；最大255s，最小1s；操作该时间退出。
	 *	\param[out] rlen 用户输入密码的长度。
	 *	\param[out] cpass 存放用户输入的密码。
	 *	\return 如果< 0表示失败，否则成功。
	 *	\par 示例:
	 *	\code
	 *	long result;
	 *	unsigned char rlen, pass[64];
	 *	result = dc_getinputpass(icdev, 20, &rlen, pass);
	 *	\endcode
	 */
	long __stdcall dc_getinputpass(long icdev,unsigned char ctime,unsigned char *rlen,unsigned char * cpass);
	
	/*! \brief LED控制函数
	 *	\par 说明:
	 *	控制3个LED指示灯的亮和灭。
	 *	\param[in] icdev 设备端口标识符。
	 *	\param[in] LedSel LED标识号（0表示LED1，1表示LED2，2表示LED3）。
	 *	\param[in] LedCtr LED控制标志（1表示亮，0表示灭）。
	 *	\return 如果< 0 表示失败，否则表示成功。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	st = dc_ctlled(icdev, 1, 1);		//设置LED2亮。
	 *	\endcode
	 */
	long __stdcall dc_ctlled(long icdev,unsigned char LedSel,unsigned char LedCtr);	
	/*!	\brief LCD背光设置函数
	 *	\par 说明:
	 *	控制LCD的背光显示，可以打开或关闭背光。
	 *	\param[in] icdev 设备端口标识符。
	 *	\param[in] OpenFlag 背光控制标志（0表示开背光，1表示关背光）。
	 *	\return 如果< 0表示失败，否则表示成功。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	st = dc_ctlbacklight(icdev, 0);		//开背光。
	 *	\endcode
	 */
	long __stdcall dc_ctlbacklight(long icdev,unsigned char OpenFlag);
	
	/*!	\brief LCD清屏函数
	 *	\param[in] icdev 设备端口标识符。
	 *	\param[in] LineFlag 行标志（0表示第一行，1表示第二行，2表示第三行，3表示地四行，4表示清全屏）。
	 *	\return 如果< 0表示失败，否则表示成功。
	 */
	long __stdcall dc_lcdclrscrn(long icdev,unsigned char LineFlag);
	
	/*!	\brief 嵌入式字符显示
	 *	\par 说明:
	 *	嵌入式字符显示的控制函数。
	 *	\param[in] icdev 设备端口标识符。
	 *	\param[in] line 显示行选择，取值范围0~3。
	 *	\param[in] offset 显示列选择，取值范围0~15。
	 *	\param[in] info 要显示的内容。数字（0~9），字符（a~z,A~Z）。
	 *	\return 如果< 0表示失败，否则表示成功。
	 */
	long __stdcall dc_dispsingle(long icdev,unsigned char line,unsigned char offset,unsigned char info);
	
	/*!	\brief 全角字符显示
	 *	\par 说明:
	 *	全角字符（ASC或汉字，一个字符占用2个字节）显示控制。
	 *	\param[in] icdev 设备端口标识符。
	 *	\param[in] line 显示行选择，范围0~3。
	 *	\param[in] offset 显示列选择，范围0~15。
	 *	\param[in] length 显示字符的个数，范围1~8。
	 *	\param[in] data 要显示的内容，自行编码，点阵16 * 8。
	 *	\return 如果< 0表示失败，否则表示成功。
	 *	\par 示例:
	 *	\code
	 *	long st;
	 *	st = dc_dispinfo(icdev, 0, 2, 3, "CAT");		//从第0行、第2列、开始显示长度为3的全角字符CAT。
	 *	\endcode
	 */ 
	long  __stdcall  dc_dispinfo(long icdev,unsigned char line,unsigned char offset,
								 unsigned char length,unsigned  char *data);
	
	/*! \brief 半角西文字符显示
	 *	\param[in] icdev 设备端口标识符。
	 *	\param[in] line 显示行选择，范围0~3。
	 *	\param[in] offset 显示列选择，0~15。
	 *	\param[in] info 要显示的内容。
	 */						
	long  __stdcall dc_dispsingleinfo(long icdev,unsigned char line,unsigned char offset,const char *info);
	
	/*!	\brief 设置读写器时间
	 *	\param[in] icdev 设备端口标识符。
	 *	\param[in] year,month,date,hour,minute,second 设置时间:年、月、日、小时、分钟、秒。
	 *	\return 如果< 0失败，否则成功。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	st = dc_setreadertime(icdev, 08, 06, 23, 12, 00, 00);		//设置读写器时间为:2008年6月23日12点整。
	 *	\endcode
	 */
	long __stdcall dc_setreadertime(long icdev,unsigned short year,unsigned short month,unsigned short date,
							        unsigned short hour,unsigned short minute,unsigned short second);
	
	/*!	\brief 获取读写器时间
	 *	\param[in] icdev 设备端口标识符。
	 *	\param[out] year 获得的读写器时间的年份<100;
	 *	\param[out] month,date,hour,minute,second 获得的读写器时间的月、日、小时、分钟、秒。
	 *	\return 如果< 0表示失败，否则表示成功。
	 *	\par 示例:
	 *	\code
	 *	int st;
	 *	st = dc_getreadertime(icdev, &year, &month, &data, &hour, &minute, &second);
	 *	\endcode
	 */
	long __stdcall dc_getreadertime(long icdev,unsigned short *year,unsigned short *month,unsigned short *date,
									unsigned short *hour,unsigned short *minute,unsigned short *second);

long	__stdcall	 dc_down(long idComDev);
long	__stdcall	 dc_inittype (long hDev,unsigned char type);
long  __stdcall  dc_check_4442(long idcomdev);
long  __stdcall  dc_read_4442(long idcomdev,unsigned char  offset,__int16 len,unsigned char * databuffer);
long  __stdcall  dc_write_4442(long idcomdev,unsigned char  offset,__int16 len,unsigned char * databuffer);
long  __stdcall  dc_readpass_sle4442(long idcomdev,unsigned char*password);
long  __stdcall  dc_readcount_sle4442(long idcomdev);
long  __stdcall  dc_checkpass_sle4442(long idcomdev,unsigned char* password);
long  __stdcall  dc_changepass_sle4442(long idcomdev,unsigned char*password);
long  __stdcall  dc_readprotection(long dcdev,unsigned char offset,unsigned char len,unsigned char* protbuffer);
long  __stdcall  dc_writeprotection(long dcdev, unsigned char offset,unsigned char len,unsigned char *protbuffer);
long  __stdcall  dc_down_4442(long icdev);

long  __stdcall  dc_writeprotection_hex(long idcomdev,unsigned char offset,unsigned char len,unsigned char *protbuffer);
long  __stdcall  dc_readprotection_hex(long idcomdev,unsigned char offset,unsigned char len,unsigned char* protbuffer);
long  __stdcall  dc_checkpass_4442hex(long idcomdev,unsigned char*password);
long  __stdcall  dc_changepass_4442hex(long idcomdev,unsigned char*password);
long  __stdcall   dc_readpass_4442hex(long idcomdev,unsigned char*password);

//*****************sle4428***********************************************************
long  __stdcall  dc_check_4428(long idcomdev);
long  __stdcall  dc_read_4428(long idcomdev,__int16 offset,__int16 len,unsigned char * databuffer);
long  __stdcall  dc_write_4428(long idcomdev,__int16 offset,__int16 len,unsigned char * databuffer);
long  __stdcall  dc_readcount_sle4428(long idcomdev);
long  __stdcall  dc_checkpass_sle4428(long idcomdev,unsigned char* password);
long  __stdcall  dc_changepass_sle4428(long idcomdev,unsigned char* password);
long  __stdcall  dc_writewithprotection (long dcdev, __int16 offset, __int16 len,unsigned char *protbuffer);
long  __stdcall  dc_readwithprotection (long dcdev,__int16 offset,__int16 len,unsigned char* protbuffer);
long  __stdcall  dc_down_4428(long icdev);

long  __stdcall  dc_writewithprotection_hex(long idcomdev,__int16 offset,__int16 len,unsigned char * writebuffer);
long  __stdcall  dc_readwithprotection_hex(long idcomdev,__int16 offset,__int16 len,unsigned char* protbuffer);
long  __stdcall  dc_checkpass_4428hex(long idcomdev,unsigned char* password);
long  __stdcall  dc_changepass_4428hex(long idcomdev,unsigned char* password);

//*****************24c***********************************************************
long  __stdcall  dc_check_24c01(long idcomdev);
long  __stdcall  dc_check_24c02(long idcomdev);
long  __stdcall  dc_check_24c04(long idcomdev);
long  __stdcall  dc_check_24c08(long idcomdev);
long  __stdcall  dc_check_24c16(long idcomdev);
long  __stdcall  dc_check_24c64(long idcomdev);
long  __stdcall  dc_read24(long idcomdev,__int16 offset,__int16 len,unsigned char *writebuffer);
long  __stdcall  dc_write24(long idcomdev,__int16 offset,__int16 len,unsigned char *writebuffer);
long  __stdcall  dc_write24_hex(long idcomdev,__int16 offset,__int16 len,unsigned char *writebuffer);

long  __stdcall  dc_read64(long idcomdev,__int16 offset,__int16 len,unsigned char *writebuffer);
long  __stdcall  dc_write64(long idcomdev,__int16 offset,__int16 len,unsigned char *writebuffer);
long  __stdcall  dc_write64_hex(long idcomdev,__int16 offset,__int16 len,unsigned char *writebuffer);
long  __stdcall  dc_down_24c(long icdev);

long  __stdcall  a_hex(unsigned char *pHexChar, unsigned char *pStdChar, unsigned long StdCharLen);
long  __stdcall  hex_a(unsigned char *pStdChar, unsigned char *pHexChar, unsigned long StdCharLen);
//设置ID模块
long  __stdcall  dc_setID(long icdev,unsigned char *sdata,unsigned long slen);
//查找手机
long __stdcall  dc_rf_sim(long icdev,unsigned char slen,unsigned char *cmd,unsigned char *rlen,unsigned char *Num_sim);

#if defined(__cplusplus)
}
#endif
