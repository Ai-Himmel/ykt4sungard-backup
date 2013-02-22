/*! \file Trf32.h
 *  \brief �û��ӿ�����ͷ�ļ�
 *
 *  ���ļ������û�����ʹ�õĶ��塢���������������
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

	/*! \brief ��ʼ��ͨѶ��
	 *  \par ˵��:
	 *  ������ʼ��ͨѶ�ڣ��ɹ��󷵻ص�ͨѶ�豸��ʶ�����ڲ�ʹ�õ�ʱ�������DC_exit_comm����رա�
	 *  \param[in] DeviceName ͨѶ�豸���ƣ�һ��Ϊ"COM1"��"COM2"......��
	 *  \param[in] Baudrate ͨѶ�����ʣ�ȡֵΪ9600��115200��
	 *  \return ���<0��ʾʧ�ܣ�����ΪͨѶ�豸��ʶ����
	 *  \par ʾ��:
	 *  \code
	 *  long icdev;
	 *  icdev = DC_init_comm("COM1", 115200);
	 *  \endcode
	 */
	long __stdcall DC_init_comm(const char *DeviceName, unsigned long Baudrate);

	/*! \brief �ر�ͨѶ��
	 *  \par ˵��:
	 *  �����ر�֮ǰ�ɹ�����DC_init_comm�򿪵�ͨѶ�ڡ�
	 *  \param[in] DeviceHandle ͨѶ�豸��ʶ����
	 *  \return ���<0��ʾʧ�ܣ������ʾ�ɹ���
	 *  \par ʾ��:
	 *  \code
	 *  long result;
	 *  result = DC_exit_comm(icdev);
	 *  \endcode
	 */
	long __stdcall DC_exit_comm(long DeviceHandle);

	/*! \brief ��ѯ���֤��
	 *  \par ˵��:
	 *  ��ѯ���֤���Ƿ���ڡ�
	 *  \param[in] DeviceHandle ͨѶ�豸��ʶ����
	 *  \return ���<0��ʾʧ�ܣ������ʾ�ɹ���
	 *  \par ʾ��:
	 *  \code
	 *  long result;
	 *  result = DC_find_i_d(icdev);
	 *  \endcode
	 */
	long __stdcall DC_find_i_d(long DeviceHandle);

	/*! \brief ��ʼ�����֤������
	 *  \par ˵��:
	 *  ���ڶ�ȡ���֤����Ϣ�����óɹ��󣬶��������֤����Ϣ�������ڿ��ڲ��洢�У�����ʹ����DC_i_d_query_��ͷ�ĺ���ȥ��ȡ��Щ�ڲ��洢�е���Ϣ������ʹ���ڲ��洢�е���Ϣʱ�������DC_end_i_d�����ͷš�
	 *  \param[in] DeviceHandle ͨѶ�豸��ʶ����
	 *  \return ���=-1��ʾʧ�ܣ�����Ϊ���֤����Ϣ��ʶ����
	 *  \par ʾ��:
	 *  \code
	 *  long IdHandle;
	 *  IdHandle = DC_start_i_d(icdev);
	 *  \endcode
	 */
	long __stdcall DC_start_i_d(long DeviceHandle);

	/*! \brief ȡ���֤������
	 *  \par ˵��:
	 *  �ӿ��ڲ��洢��ȡ���֤��������Ϣ
	 *  \param[in] IdHandle ���֤����Ϣ��ʶ����
	 *  \return ���=0��ʾʧ�ܣ�����ָ�����֤��������Ϣ��
	 *  \par ʾ��:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_name(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_name(long IdHandle);
	
	/*! \brief ȡ���֤���Ա�
	 *  \par ˵��:
	 *  �ӿ��ڲ��洢��ȡ���֤���Ա���Ϣ
	 *  \param[in] IdHandle ���֤����Ϣ��ʶ����
	 *  \return ���=0��ʾʧ�ܣ�����ָ�����֤���Ա���Ϣ��
	 *  \par ʾ��:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_sex(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_sex(long IdHandle);
	
	/*! \brief ȡ���֤������
	 *  \par ˵��:
	 *  �ӿ��ڲ��洢��ȡ���֤��������Ϣ
	 *  \param[in] IdHandle ���֤����Ϣ��ʶ����
	 *  \return ���=0��ʾʧ�ܣ�����ָ�����֤��������Ϣ��
	 *  \par ʾ��:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_nation(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_nation(long IdHandle);
	
	/*! \brief ȡ���֤����������
	 *  \par ˵��:
	 *  �ӿ��ڲ��洢��ȡ���֤������������Ϣ
	 *  \param[in] IdHandle ���֤����Ϣ��ʶ����
	 *  \return ���=0��ʾʧ�ܣ�����ָ�����֤������������Ϣ��
	 *  \par ʾ��:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_birth(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_birth(long IdHandle);
	
	/*! \brief ȡ���֤��סַ
	 *  \par ˵��:
	 *  �ӿ��ڲ��洢��ȡ���֤��סַ��Ϣ
	 *  \param[in] IdHandle ���֤����Ϣ��ʶ����
	 *  \return ���=0��ʾʧ�ܣ�����ָ�����֤��סַ��Ϣ��
	 *  \par ʾ��:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_address(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_address(long IdHandle);
	
	/*! \brief ȡ���֤��֤������
	 *  \par ˵��:
	 *  �ӿ��ڲ��洢��ȡ���֤��֤��������Ϣ
	 *  \param[in] IdHandle ���֤����Ϣ��ʶ����
	 *  \return ���=0��ʾʧ�ܣ�����ָ�����֤��֤��������Ϣ��
	 *  \par ʾ��:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_id_number(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_id_number(long IdHandle);
	
	/*! \brief ȡ���֤��ǩ������
	 *  \par ˵��:
	 *  �ӿ��ڲ��洢��ȡ���֤��ǩ��������Ϣ
	 *  \param[in] IdHandle ���֤����Ϣ��ʶ����
	 *  \return ���=0��ʾʧ�ܣ�����ָ�����֤��ǩ��������Ϣ��
	 *  \par ʾ��:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_department(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_department(long IdHandle);
	
	/*! \brief ȡ���֤����Ч����
	 *  \par ˵��:
	 *  �ӿ��ڲ��洢��ȡ���֤����Ч������Ϣ
	 *  \param[in] IdHandle ���֤����Ϣ��ʶ����
	 *  \return ���=0��ʾʧ�ܣ�����ָ�����֤����Ч������Ϣ��
	 *  \par ʾ��:
	 *  \code
	 *  char *p;
	 *  p = DC_i_d_query_expire_day(IdHandle);
	 *  \endcode
	 */
	char* __stdcall DC_i_d_query_expire_day(long IdHandle);
	
	/*! \brief ȡ���֤����Ƭ������Ϣ
	 *  \par ˵��:
	 *  �ӿ��ڲ��洢��ȡ���֤����Ƭ������Ϣ����������DC_i_d_query_photo_lenһ��ʹ�á�
	 *  \param[in] IdHandle ���֤����Ϣ��ʶ����
	 *  \return ���=0��ʾʧ�ܣ�����ָ�����֤����Ƭ������Ϣ��
	 *  \par ʾ��:
	 *  \code
	 *  unsigned char *p;
	 *  p = DC_i_d_query_photo(IdHandle);
	 *  \endcode
	 */
	unsigned char* __stdcall DC_i_d_query_photo(long IdHandle);
	
	/*! \brief ȡ���֤����Ƭ���ݳ�����Ϣ
	 *  \par ˵��:
	 *  �ӿ��ڲ��洢��ȡ���֤����Ƭ���ݳ�����Ϣ����������DC_i_d_query_photoһ��ʹ�á�
	 *  \param[in] IdHandle ���֤����Ϣ��ʶ����
	 *  \return ���=0��ʾʧ�ܣ�����ָ�����֤����Ƭ���ݳ�����Ϣ��
	 *  \par ʾ��:
	 *  \code
	 *  unsigned char *p;
	 *  p = DC_i_d_query_photo_len(IdHandle);
	 *  \endcode
	 */
	unsigned long __stdcall DC_i_d_query_photo_len(long IdHandle);

	/*! \brief ȡ���֤����Ƭ�ļ�
	 *  \par ˵��:
	 *  �ӿ��ڲ��洢��ȡ���֤����Ƭ���ݲ��Ҵ洢ΪBMP�ļ���
	 *  \param[in] IdHandle ���֤����Ϣ��ʶ����
	 *  \param[in] FileName Ҫ�����BMP�ļ�����
	 *  \return ���<0��ʾʧ�ܣ������ʾ�ɹ���
	 *  \par ʾ��:
	 *  \code
	 *  long result;
	 *  result = DC_i_d_query_photo_file(IdHandle, "C:\\me.bmp");
	 *  \endcode
	 */
	long __stdcall DC_i_d_query_photo_file(long IdHandle, const char *FileName);

	/*! \brief ȡ���֤����Ƭ�ļ���BMP��ʽ����
	 *  \par ˵��:
	 *  �ӿ��ڲ��洢��ȡ���֤����Ƭ���ݲ��Ҵ洢ΪBMP��ʽ��
	 *  \param[in] IdHandle ���֤����Ϣ��ʶ����
	 *  \param[in] BmpBuffer Ҫ�����BMP��ʽ��������
	 *  \param[in,out] BmpLength ���뻺������С�����óɹ��󷵻�ʵ��ʹ�õĴ�С��
	 *  \return ���<0��ʾʧ�ܣ������ʾ�ɹ���
	 *  \par ʾ��:
	 *  \code
	 *  long result;
	 *  unsigned char BmpBuffer[4096];
	 *  unsigned long BmpLength;
	 *  result = DC_i_d_query_photo_file(IdHandle, BmpBuffer, &BmpLength);
	 *  \endcode
	 */
	long __stdcall DC_i_d_query_photo_bmp_buffer(long IdHandle, unsigned char *BmpBuffer, unsigned long *BmpLength);
	
	
	/*! \brief ������ȡ���֤������
	 *  \par ˵��:
	 *  �����ͷ�֮ǰ�ɹ�����DC_start_i_d�������Դ��
	 *  \param[in] IdHandle ���֤����Ϣ��ʶ����
	 *  \par ʾ��:
	 *  \code
	 *  DC_end_i_d(IdHandle);
	 *  \endcode
	 */
	void __stdcall DC_end_i_d(long IdHandle);

	/*! \brief ��ʼ��ͨѶ��
	 *  \par ˵��:
	 *  ������ʼ��ͨѶ�ڣ��ɹ��󷵻ص�ͨѶ�豸��ʶ�����ڲ�ʹ�õ�ʱ�������dc_exit����رա�
	 *  \param[in] port ȡֵΪ0��19ʱ����ʾ����1��20��Ϊ100ʱ����ʾUSB��ͨѶ����ʱ��������Ч��
	 *  \param[in] baud ͨѶ�����ʣ�ȡֵΪ9600��115200��
	 *  \return ���<0��ʾʧ�ܣ�����ΪͨѶ�豸��ʶ����
	 *  \par ʾ��:
	 *  \code
	 *  long icdev;
	 *  icdev = dc_init(0, 115200);
	 *  \endcode
	 */
	long __stdcall dc_init(long port, unsigned long baud);
	
	/*! \brief �ر�ͨѶ��
	 *  \par ˵��:
	 *  �����ر�֮ǰ�ɹ�����dc_init�򿪵�ͨѶ�ڡ�
	 *  \param[in] icdev ͨѶ�豸��ʶ����
	 *  \return ���<0��ʾʧ�ܣ������ʾ�ɹ���
	 *  \par ʾ��:
	 *  \code
	 *  long result;
	 *  result = dc_exit(icdev);
	 *  \endcode
	 */
	long __stdcall dc_exit(long icdev);
	
	/*! \brief ����
	 *  \par ˵��:
	 *  �����豸������
	 *  \param[in] icdev ͨѶ�豸��ʶ����
	 *  \param[in] ms ����ʱ�䣬��10����Ϊ��λ��
	 *  \return ���<0��ʾʧ�ܣ������ʾ�ɹ���
	 *  \par ʾ��:
	 *  \code
	 *  long result;
	 *  result = dc_beep(icdev, 10);
	 *  \endcode
	 */
	long __stdcall dc_beep(long icdev, unsigned short ms);
	
	/*! \brief ��ȡ�豸�洢
	 *  \par ˵��:
	 *  �豸�ڲ�����һ��洢�������ʹ�ã������С�ɲμ�Ӳ����񣬴˺������ڶ�ȡ�ⲿ������
	 *  \param[in] icdev ͨѶ�豸��ʶ����
	 *  \param[in] offset ƫ�Ƶ�ַ��offset+len����С���豸�洢����Ĵ�С����
	 *  \param[in] len ���ȣ�offset+len����С���豸�洢����Ĵ�С����
	 *  \param[out] data_buffer ��ȡ������Ϣ��
	 *  \return ���<0��ʾʧ�ܣ������ʾ�ɹ���
	 *  \par ʾ��:
	 *  \code
	 *  long result;
	 *  unsigned char data_buffer[4];
	 *  result = dc_srd_eeprom(icdev, 0, 4, data_buffer);
	 *  \endcode
	 */
	long __stdcall dc_srd_eeprom(long icdev, unsigned long offset, unsigned long len, unsigned char *data_buffer);
	
	/*! \brief ��ȡ�豸�洢��HEX��ʽ��
	 *  \par ˵��:
	 *  dc_srd_eeprom������HEX��ʽ���ַ������ݽ���HEX��ʽ���ݡ�
	 */
	long __stdcall dc_srd_eepromhex(long icdev, unsigned long offset, unsigned long len, unsigned char *data_buffer);

	/*! \brief д���豸�洢
	 *  \par ˵��:
	 *  �豸�ڲ�����һ��洢�������ʹ�ã������С�ɲμ�Ӳ����񣬴˺�������д���ⲿ������
	 *  \param[in] icdev ͨѶ�豸��ʶ����
	 *  \param[in] offset ƫ�Ƶ�ַ��offset+len����С���豸�洢����Ĵ�С����
	 *  \param[in] len ���ȣ�offset+len����С���豸�洢����Ĵ�С����
	 *  \param[in] data_buffer Ҫд�����Ϣ��
	 *  \return ���<0��ʾʧ�ܣ������ʾ�ɹ���
	 *  \par ʾ��:
	 *  \code
	 *  long result;
	 *  unsigned char data_buffer[4] = {0x31, 0x32, 0x33, 0x34};
	 *  result = dc_swr_eeprom(icdev, 0, 4, data_buffer);
	 *  \endcode
	 */
	long __stdcall dc_swr_eeprom(long icdev, unsigned long offset, unsigned long len, const unsigned char *data_buffer);
	
	/*! \brief д���豸�洢��HEX��ʽ��
	 *  \par ˵��:
	 *  dc_swr_eeprom������HEX��ʽ���ַ������ݽ���HEX��ʽ���ݡ�
	 */
	long __stdcall dc_swr_eepromhex(long icdev, unsigned long offset, unsigned long len, const unsigned char *data_buffer);
	
	/*! \brief ���Ӳ���汾��
	 *  \par ˵��:
	 *  �豸��ά����һ��Ӳ���汾�ţ���ʾ��ǰ�豸�İ汾���ô˺������Ի������汾�š�
	 *  \param[in] icdev ͨѶ�豸��ʶ����
	 *  \param[out] data_buffer ��Ű汾�ŵĻ����������ȹ̶�Ϊ4�ֽڣ����������ַ���\\0������
	 *  \return ���<0��ʾʧ�ܣ������ʾ�ɹ���
	 *  \par ʾ��:
	 *  \code
	 *  long result;
	 *  unsigned char data_buffer[4];
	 *  result = dc_getver(icdev, data_buffer);
	 *  \endcode
	 */
	long __stdcall dc_getver(long icdev, unsigned char *data_buffer);
	
	/*! \brief �����豸������
	 *  \par ˵��:
	 *  �豸֧���Բ�ͬ�Ĳ�����ͨѶ��ͨ���˺������óɹ��󣬱���ر�ͨѶ������������Ӧ�Ĳ����ʳ�ʼ��ͨѶ�ڲ������������豸��
	 *  \param[in] icdev ͨѶ�豸��ʶ����
	 *  \param[in] baud ͨѶ�����ʣ�ȡֵΪ9600��115200��
	 *  \return ���<0��ʾʧ�ܣ������ʾ�ɹ���
	 *  \par ʾ��:
	 *  \code
	 *  long result;
	 *  result = dc_set_baudrate(icdev, 9600);
	 *  \endcode
	 */
	long __stdcall dc_set_baudrate(long icdev, unsigned long baud);

	/*! \brief Ѱ������
	 *  \par ˵��:
	 *  ��Ѱ��Ӧ���ڵĿ�Ƭ��dc_request��dc_anticoll��dc_selectͨ�����ʹ�ã����������Ҳ����ʹ��dc_card������
	 *  \param[in] icdev ͨѶ�豸��ʶ����
	 *  \param[in] _Mode 0��ʾIDLEģʽ��һ��ֻ��һ�ſ�������1��ʾALLģʽ��һ�οɶԶ��ſ�������
	 *  \param[out] TagType ������ֵ��
	 *  \return ���<0��ʾʧ�ܣ������ʾ�ɹ��������޿�=1���п�=0����
	 *  \par ʾ��:
	 *  \code
	 *  long result;
	 *  unsigned short TagType;
	 *  result = dc_request(icdev, 0, &TagType);
	 *  \endcode
	 */
	long __stdcall dc_request(long icdev, unsigned char _Mode, unsigned short *TagType);
	
	/*! \brief ������ͻ
	 *  \par ˵��:
	 *  �˺����������ؿ�Ƭ�����кš�dc_request��dc_anticoll��dc_selectͨ�����ʹ�ã����������Ҳ����ʹ��dc_card������
	 *  \param[in] icdev ͨѶ�豸��ʶ����
	 *  \param[in] _Bcnt �̶�Ϊ0��
	 *  \param[out] _Snr �����кš�
	 *  \return ���<0��ʾʧ�ܣ������ʾ�ɹ���
	 *  \par ʾ��:
	 *  \code
	 *  long result;
	 *  unsigned long _Snr;
	 *  result = dc_anticoll(icdev, 0, &_Snr);
	 *  \endcode
	 */
	long __stdcall dc_anticoll(long icdev, unsigned char _Bcnt, unsigned long *_Snr);
	
	/*! \brief ѡȡ��Ƭ
	 *  \par ˵��:
	 *  ѡȡһ���������кŵĿ���dc_request��dc_anticoll��dc_selectͨ�����ʹ�ã����������Ҳ����ʹ��dc_card������
	 *  \param[in] icdev ͨѶ�豸��ʶ����
	 *  \param[in] _Snr �����кš�
	 *  \param[out] _Size ��������
	 *  \return ���<0��ʾʧ�ܣ������ʾ�ɹ���
	 *  \par ʾ��:
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
	
	/*! \brief Ѱ��
	 *  \par ˵��:
	 *	�����ڹ���������ĳ�ſ������к�(�ú���������de_request��dc_anticoll��dc_select�����幦��)��
	 *  \param[in] icdev ͨѶ�豸��ʶ����
	 *	\param[in] _Mode 0��ʾIDLEģʽ��һ��ֻ��һ�ſ�������1��ʾALLģʽ��һ�οɶԶ��ſ�������
	 *	\param[out] _Snr �����кš�
	 *	\return ���<0ʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	int st;
	 *	unsigned long snr;
	 *	st = dc_card(icdev, 0, &snr);
	 *	\endcode
	 *	\par ע��:
	 *	ѡ��IDLEģʽ���ڶԿ����ж�д������ִ��dc_halt()ָ����ֹ��������
	 *	ֻ�е��ÿ��뿪���ٴν��������ʱ����д�����ܹ��ٴζ������в�����
	 */
	long __stdcall dc_card(long icdev,unsigned char _Mode,unsigned long *_Snr);
	
	/*! \brief �����豸����
	 *	\par ˵��:
	 *	������װ���дģ��RAM�С�
	 *	\param[in] icdev ͨѶ�豸��ʶ����
	 *	\param[in] _Mode 0��ʾA���룻4��ʾB����,��˶����뺯����Ӧ��
	 *	\param[in] _SecNr ������(M1��:0~15)��
	 *	\param[in] _NKey д���д���еĿ����롣
	 *	\return ���<0ʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ����
	 *	\code
	 *	unsigned char password[7] = {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5};		//KeyA ����KeyB;
	 *	if(dc_load_key(icdev, 0, 1, password) != 0)		//װ��1������A���룻
	 *	{
	 *		printf("Load Key Error!");
	 *		dc_exit(icdev);
	 * 	}
	 *	\endcode
	 */
	long __stdcall dc_load_key(long icdev,unsigned char _Mode,unsigned char _SecNr,unsigned char *_NKey);
	
  /*! \brief �����豸���루HEX��ʽ��
	 *  \par ˵��:
	 *  dc_load_key������HEX��ʽ���ַ������ݽ���HEX��ʽ���ݡ�
	 */
	long __stdcall dc_load_key_hex(long icdev,unsigned char _Mode,unsigned char _SecNr,unsigned char *_NKey);
	
	/*! \brief �˶�����
	 *	\par ˵��:
	 *	�˶������е����롣
	 *	\param[in] icdev ͨѶ�豸��ʶ����
	 *	\param[in] _Mode 0��ʾA���룻4��ʾB���룬�������豸���뺯����Ӧ��
	 *	\param[in] _SecNr Ҫ�˶�����������š�
	 *	\return ���< 0ʧ�ܣ������ʾ�ɹ���
	 */
	long __stdcall dc_authentication(long icdev,unsigned char _Mode,unsigned char _SecNr);
	
	/*! \brief �˶�����
	 *	\par ˵��:
	 *	�ô˺���ʱ�����Բ�ִ��dc_load_key����(ֻ֧��M1��S70��)��
	 *	\param[in] icdev ͨѶ�豸��ʶ����
	 *	\param[in] _Mode 0��ʾA���룬4��ʾB���롣
 	 *	\param[in] _SecAddr Ҫ�˶Ե������������Ŀ�š�
 	 *	\param[in] passbuff �����ַ�����
	 *	\return ���< 0ʧ�ܣ������ʾ�ɹ���
	 */
	long __stdcall dc_authentication_pass(long icdev,unsigned char _Mode,
										  unsigned char _SecAddr,unsigned char *passbuff);
										  
  /*! \brief ��ֹ����
   *	\par ˵��:
   *	��ֹ�Կ��Ĳ�����
   *	\param[in] icdev ͨѶ�豸��ʶ����
   *	\return �ɹ��򷵻�0��
   *	\par ʾ��:
   *	\code
   *	int st;
   *	st = dc_halt(icdev);
   *	\endcode
   *	\par ˵��:
   *	ʹ��dc_card(icdev)����ʱ���и�_Mode���������_Mode = 0,��Կ����в�����Ϻ�
   *	ִ��dc_halt(icdev);��ÿ�����HALTģʽ�������ѿ��ƿ���Ӧ������Ѱ�����ſ���
   */
	long __stdcall dc_halt(long icdev);
	
	/*! \brief ����
	 *	\par ˵��:
	 *	��ȡ�������ݣ�һ�ζ�ȡһ��������ݣ�Ϊ16���ֽڡ�
	 *	\param[in] icdev ͨѶ�豸��ʶ����
	 *	\param[in] _Adr ���ַ��M1��(0~63), MS70��(0~255)����
	 *	\param[in] _Data �������ݡ�
	 *	\return ���<0��ʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	int st;
	 *	unsigned char data[16];
	 *	st = dc_read(icdev, 4, data);		//��M1����4�����ݣ�
	 *	\endcode
	 */
	long __stdcall dc_read(long icdev,unsigned char _Adr,unsigned char *_Data);
	
	/*! \brief ����(HEX��ʽ)
	 *	\par ˵��:
	 *	dc_read������HEX��ʽ���ַ������ݽ���HEX��ʽ���ݡ�
	 */
	long __stdcall dc_read_hex(long icdev,unsigned char _Adr,unsigned char *_Data);
	
	/*! \brief д��
	 *	\par ˵��:
	 *	����д�����ݡ�һ�α���дһ���飬Ϊ16���ֽڡ�
	 *	\param[in] icdev ͨѶ�豸��ʶ�š�
	 *	\param[in] _Adr ���ַ��M1��(0~63), MS70��(0~255)����
	 *	\param[in] _Data Ҫд������ݡ�
	 *	\return ���<0��ʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	int st;
	 *	unsigned char *data = "1234567890123456";
	 *	st = dc_write(icdev, 4, data);		//д���Ŀ顣
	 *	\endcode
	 */
	long __stdcall dc_write(long icdev,unsigned char _Adr,unsigned char *_Data);
	
	/*! \brief д����HEX��ʽ��
	 *	\par ˵��:
	 *	����д�����ݡ�������HEX��ʽ���ݡ�
	 */
	long __stdcall dc_write_hex(long icdev,unsigned char _Adr,unsigned char *_Data);
	
	/*! \brief ��ʼ����ֵ
	 *	\par ˵��:
	 *	��ʼ�����ֵ��
	 *	\param[in] icdev ͨѶ�豸��ʶ����
	 *	\param[in] _Adr ��ַ�顣
	 *	\param[in] _Value ��ʼֵ��
	 *	\return ���<0��ʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	int st;
	 *	unsigned long value;
	 *	value = 1000;		//��value��ֵ��
	 *	st = dc_initval(icdev, 1, value);		//����1��ֵ��ʼΪ1000��
	 *	\endcode
	 *	\par ע��:
	 *	�ڽ���ֵ����ʱ��������ִ�г�ʼ��������Ȼ��ſ��Զ��������ӵĲ�����
	 */
	long __stdcall dc_initval(long icdev,unsigned char _Adr,unsigned long _Value);
	
	/*!	\brief ��ֵ
	 *	\par ˵��:
	 *	���ֵ
	 *	\param[in] icdev ͨѶ�豸��ʶ����
	 *	\param[in] _Adr ���ַ��
	 *	\param[in] _Value Ҫ���ӵ�ֵ��
	 *	\return ���<0��ʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	int st;
	 *	unsigned long value;
	 *	value = 10;
	 *	st = dc_increment(icdev, 1, value);		//����1��ֵ����10��
	 *	\endcode
	 */
	long __stdcall dc_increment(long icdev,unsigned char _Adr,unsigned long _Value);
	
	/*!	\brief ��ֵ
	 *	\par ˵��:
	 *	���ֵ
	 *	\param[in] icdev ͨѶ�豸��־��
	 *	\param[in] _Adr ���ַ��
	 *	\param[in] _Value Ҫ����ֵ��
	 *	\return ���<0��ʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	int st;
	 *	unsigned long value;
	 *	value = 10;
	 *	st = dc_decrement(icdev, 1, value);		//����1��ֵ����10��
	 *	\endcode
	 */
	long __stdcall dc_decrement(long icdev,unsigned char _Adr,unsigned long _Value);
	
	/*!	\brief ����ֵ
	 *	\par ˵��:
	 *	�������ֵ��
	 *	\param[in] icdev ͨѶ��ʶ����
	 *	\param[in] _Adr ���ַ��
	 *	\param[out] _Value ����ֵ�ĵ�ַ��
	 *	\return ���< 0��ʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	int st;
	 *	unsigned long value;
	 *	st = dc_readval(icdev, 1, &value);		//������1��ֵ������value�С�
	 *	\endcode
	 */
	long __stdcall dc_readval(long icdev,unsigned char _Adr,unsigned long *_Value);
	long __stdcall dc_valuebackup(long icdev,unsigned char _OriginalAdr,unsigned char _BackupAdr);
	
	/*! \brief ���ÿ���
	 *	\par ˵��:
	 *	����Ҫ������SAM������
	 *	\param[in] icdev ͨѶ�豸��ʶ����
	 *	\param[in] Cardtype Ҫ�����Ŀ����š���0x0c��ʾ������,0x0d��ʾΪSAM1,0x0e��ʾΪSAM2��
	 *	\return ���< 0��ʧ�ܣ������ʾ�ɹ���
	 */
	long __stdcall dc_setcpu(long icdev,unsigned char Cardtype);
	
	/*! \brief �ϵ縴λ
	 *	\par ˵��:
	 *	CPU���ϵ縴λ��������λ���Զ��жϿ�ƬЭ�顣
	 *	\param[in] icdev ͨѶ�豸��ʶ����
	 *	\param[in] cardtype Ҫ�����Ŀ����š���1��ʾSIM1,2��ʾSIM2,3��ʾ��������		//ע���dc_setcpu����ֵ����Ĳ�ͬ��
	 *	\param[in] baudrate 1��ʾ9600��2��ʾ14400��3��ʾ19200��4��ʾ38400��5��ʾ57600��6��ʾ115200��
	 *	\param[in] Volt 2��ʾ3.3V, 3��ʾ5.0V��
	 *	\param[out] rlen ���ظ�λ��Ϣ�ĳ��ȡ�
	 *	\param[out] databuffer ��ŷ��صĸ�λ��Ϣ��
	 *	\param[in]	protocol ���ؿ�ƬЭ�飨0��ʾT = 0, 1��ʾ T = 1����
	 *	\return ���< 0���ʾʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	int st;
	 *	unsigned char *rlen, DataBuffer;
	 *	st = dc_cpureset(icdev, 3, 1, 2, rlen, DataBuffer, 0);		//��λ������
	 *	\endcode
	 */
	long __stdcall dc_cpureset(long icdev,unsigned char cardtype,unsigned char baudrate,
							   unsigned char Volt,unsigned char *rlen,unsigned char *databuffer,unsigned char *protocol);
							   
	/*! \brief CPU�ϵ縴λ(HEX��ʽ)
	 *	\par ˵��:
	 *	dc_setcpu������HEX��ʽ���ַ������ݽ���HEX��ʽ���ݡ�
	 */
	long __stdcall dc_cpureset_hex(long icdev,unsigned char cardtype,unsigned char baudrate,
								   unsigned char Volt,unsigned char *rlen,unsigned char *databuffer,unsigned char *protocol);
			 					   
	/*! \brief ��Ϣ����������δ��װ��
	 *	\par ˵��:
	 *	CPU��APDU��Ӧ��Э�����ݵ�Ԫ����Ϣ�����������ú���δ��װ���û��������ж�Э�����Ͳ���֯���ݷ��͡�
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\param[in] Cardtype Ҫ�����Ŀ����š���0x0c��ʾ������,0x0d��ʾΪSAM1,0x0e��ʾΪSAM2����
	 *	\param[in] slen ���͵���Ϣ���ȡ�
	 *	\param[in] sendbuffer ���Ҫ���͵���Ϣ��
	 *	\param[out] rlen ������Ϣ�ĳ��ȡ�
	 *	\param[out] databuffer ��ŷ��ص���Ϣ��
	 *	\param[in] protocol ��ŷ��صĿ�ƬЭ�顣��0��ʾT = 0, 1��ʾT = 1��
	 *	\return ���< 0��ʾʧ�ܣ�= 0��ʾ�ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	int i, st;
	 *	unsigned char slen, rlen, sdata[100], rdata[100];
	 *	slen = 5;
	 *	sdata[0] = nad;	 sdata[1] = pcd;  sdata[2] = 5;
	 *	sdata[3] = 0x00; sdata[4] = 0x84; sdata[5] =0x00;
	 *	sdata[6] = 0x00; sdata[7] = 0x08;
	 *	for(i = 0; i < 8; i++)
	 *      {
	 *        sdata[8] ^= sdata[i];		//�������͡�
	 *       };
	 *	st = dc_cpuapdusource(icdev, slen, sdata, &rlen, rdata, 0);
	 *	\endcode
	 */
	long __stdcall dc_cpuapdusource(long icdev,unsigned char Cardtype,unsigned char slen,unsigned char * sendbuffer,
									unsigned char *rlen,unsigned char * databuffer,unsigned char protocol);
									
	/*! \brief ��Ϣ����������δ��װHEX��ʽ��
	 *	\par ˵��:
	 *	CPU��APDU��Ӧ��Э�����ݵ�Ԫ����Ϣ�����������ú���δ��װ���û��������ж�Э�����Ͳ���֯���ݷ��͡�
	 *	�ַ������ݽ���HEX��ʽ���ݡ�
	 */
	long __stdcall dc_cpuapdusource_hex(long icdev,unsigned char Cardtype,unsigned char slen,unsigned char * sendbuffer,
										unsigned char *rlen,unsigned char * databuffer,unsigned char protocol);
										
	/*!	\brief ��Ϣ��������
	 *	\par ˵��:
	 *	CPU��APDU��Ӧ��Э�����ݵ�Ԫ����Ϣ�����������ú�����װ��T = 0��T = 1������
	 *	\param[in]	icdev �豸�˿ڱ�ʶ����
	 *	\param[in]	Cardtype Ҫ�����Ŀ����š���0x0c��ʾ������,0x0d��ʾΪSAM1,0x0e��ʾΪSAM2����
	 *	\param[in]	slen ���͵���Ϣ���ȡ�
	 *	\param[in]	sendbuffer ���Ҫ���͵���Ϣ��
	 * 	\param[out]	rlen ������Ϣ�ĳ��ȡ�
	 *	\param[out]	databuffer ��ŷ��ص���Ϣ��
	 *	\param[in]	protocol ��ŷ��صĿ�ƬЭ�顣��0��ʾT = 0, 1��ʾT = 1����
	 *	\return ���<0��ʾʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	int st;
	 *	unsigned char slen, rlen, sdata[100], rdata[100];
	 *	slen = 5;
	 *	sdata[0] = 0x00; sdata[1] = 0x84; sdata[2] = 0x00; sdata[3] = 0x00; sdata[4] = 0x04;
	 *	st = dc_cpuapdu(icdev, slen, sdata, &rlen, rdata, 0);		//�Կ���ȡ��������
	 *	\endcode
	 */
	long __stdcall dc_cpuapdu(long icdev,unsigned char Cardtype,unsigned char slen,unsigned char * sendbuffer,
							  unsigned char *rlen,unsigned char * databuffer,unsigned char protocol);
							  
	/*!	\brief ��Ϣ����������HEX��ʽ��
	 *	\par ˵��:
	 *	CPU��APDU��Ӧ��Э�����ݵ�Ԫ����Ϣ����������HEX��ʽ���ַ������ݽ���HEX��ʽ���ݡ�
	 */
	long __stdcall dc_cpuapdu_hex(long icdev,unsigned char Cardtype,unsigned char slen,unsigned char * sendbuffer,
								  unsigned char *rlen,unsigned char * databuffer,unsigned char protocol);
								  
	/*!	\brief ��Ƶ��λ
	 *	\par ˵��:
	 *	��λ��Ƶ������
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\return �ɹ��򷵻�0�������ʾʧ�ܡ�
	 *	\par ʾ��:
	 *	\code
	 *	int st;
	 *	st = dc_reset(icdev);
	 *	\endcode
	 */
	long __stdcall dc_reset(long icdev);

	/*!	\brief ���ÿ���
	 *	\par ˵��:
	 *	���ö�д��Ҫ����һ�ֿ�������
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\param[in] cardtype ���ÿ��ͣ�A��ʾ��TYPEA��������B��ʾ��TYPEB����������
	 *	\return �ɹ��򷵻�0�������ʾʧ�ܡ�
	 *	\par ʾ��:
	 *	\code
	 *	int st;
	 *	st = dc_config_card(icdev, 'B');		//���ö�TYPEB�Ϳ����в�����
	 *	\endcode
	 */
	long __stdcall dc_config_card(long icdev,unsigned char cardtype);
	
	/*!	\brief Ѱ������
	 *	\par ˵��:
	 *	CPU��Ѱ������
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\param[out] rlen ���ؿ��ŵĳ��ȡ�
	 *	\param[out] _Snr ����16���ƵĿ��š�
	 *	\return ��� = 0 ��ʾ�ɹ���< 0 ��ʾʧ�ܡ�
	 *	\par ʾ��:
	 *	\code
	 *	long st;
	 *	unsigned char rlen;
	 *	unsigned char snr[32] = {0};
	 *	st = dc_card_pro(icdev, &rlen, snr);
	 *	\endcode
	 */
	long __stdcall dc_card_pro(long icdev,unsigned char *rlen,unsigned char *_Snr);
	
	/*! \brief Ѱ��������HEX��ʽ��
	 *	\par ˵��:
	 *	CPU��Ѱ��������HEX��ʽ���ַ������ݽ���HEX��ʽ���ݡ�
	 */
	long __stdcall dc_card_prohex(long icdev,unsigned char *rlen,unsigned char *_Snr);
	
	/*!	\brief �ϵ縴λ
	 *	\par ˵��:
	 *	TypeA���ϵ縴λ
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\param[out] rlen ���صĸ�λ��Ϣ�ĳ��ȡ�
	 *	\param[out] databuf ��ŷ��صĸ�λ��Ϣ��
	 *	\return ���= 0��ʾ�ɹ���< 0��ʾʧ�ܡ�
	 *	\par ʾ��:
	 *	\code
	 *	long st;
	 *	unsigned char rlen;
	 *	unsigned char databuf[64] = {0};
	 *	st = dc_pro_reset(icdev, &rlen, databuf);
	 *	\endcode
	 */
	long __stdcall dc_pro_reset(long icdev,unsigned char *rlen,unsigned char *databuf);
	
	/*! \brief �ϵ縴λ��HEX��ʽ��
	 *	\par ˵��:
	 *	TypeA���ϵ縴λ������HEX��ʽ���ַ������ݽ���HEX��ʽ���ݡ�
	 */
	long __stdcall dc_pro_resethex(long icdev,unsigned char *rlen,unsigned char *databuf);
	
	/*!	\brief ��Ϣ��������
	 *	\par ˵��:
	 *	TypeA��TypeB CPU��APDU��Ӧ��Э�����ݵ�Ԫ����Ϣ����������
	 *	\param[in] icdev �豸�˿ڱ�־��
	 *	\param[in] slen ������Ϣ�ĳ��ȡ�
	 *	\param[in] sendbuffer ���Ҫ���͵���Ϣ��
	 *	\param[out] rlen ������Ϣ�ĳ��ȡ�
	 *	\param[out] databuffer ��ŷ��ص���Ϣ��
	 *	\param[in] timeout �ӳ�ʱ�䣬��λΪ:10ms��
	 *	\param[in] FG �ָ�ȣ������ֵ< 64��
	 *	\return ���= 0��ʾ�ɹ���< 0���ʾʧ�ܡ�
	 *	\par ʾ��:
	 *	\code
	 *	long st;
	 *	unsigned char slen, rlen, sdata[100], rdata[100];
	 *	slen = 5;
	 *	sdata[0] = 0x00; sdata[1] = 0x84; sdata[2] = 0x00; sdata[3] = 0x00; sdata[4] = 0x04;
	 *	st = dc_pro_commandlink(icdev, slen, sdata, &rlen, rdata, 7, 56);		//�Կ�����ȡ��������
	 *	\endcode
	 */
	long __stdcall dc_pro_commandlink(long icdev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,
									  unsigned char * databuffer,unsigned char timeout,unsigned char FG);
									  
	/*! \brief ��Ϣ����������HEX��ʽ��
	 *	\par ˵��:
	 *	TypeA��TypeB CPU��APDC��Ӧ��Э�����ݵ�Ԫ����Ϣ����������HEX��ʽ���ַ������ݽ���HEX��ʽ���ݡ�
	 */
	long __stdcall dc_pro_commandlink_hex(long icdev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,
										  unsigned char * databuffer,unsigned char timeout,unsigned char FG);
	
	long __stdcall dc_pro_commandsource(long icdev,unsigned char slen,unsigned char * sendbuffer,
							 unsigned char *rlen,unsigned char * databuffer,unsigned char time);

	/*!	\brief ��ȡ����������
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\param[in] ctime �ȴ��û�ˢ���ĳ�ʱʱ�䣬��secondΪ��Ԫ�����255s����С1s��������ʱ���˳���
	 *	\param[out] pTrack1Data��pTrack1Len ���ع��1�����ݺͳ��ȡ�
	 *	\param[out] pTrack2Data��pTrack2Len ���ع��2�����ݺͳ��ȡ�
	 *	\param[out] pTrack3Data��pTrack3Len ���ع��3�����ݺͳ��ȡ�
	 *	\return ���< 0��ʾʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	long result;
	 *	unsigned char rlen1, rlen2, rlen3;
	 *	unsigned char track1[64], track2[64], track3[64];
	 *	result = dc_readmagcardall(icdev, 2, track1, &rlen1, track2, &rlen2, track3, &rlen3);
	 *	\endcode
	 */
	long __stdcall dc_readmagcardall(long icdev, unsigned char ctime, unsigned char *pTrack1Data, unsigned long *pTrack1Len,
									 unsigned char *pTrack2Data, unsigned long *pTrack2Len, unsigned char *pTrack3Data, unsigned long *pTrack3Len);
	
	/*! \brief ��ȡ��������
	 *	\par ˵��:
	 *	��ȡ�û�������������룬�ú�����һֱ�ȴ��û�����ֱ����ʱ��
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\param[in] ctime �ȴ��û�ˢ���ĳ�ʱʱ�䣬��secondΪ��λ�����255s����С1s��������ʱ���˳���
	 *	\param[out] rlen �û���������ĳ��ȡ�
	 *	\param[out] cpass ����û���������롣
	 *	\return ���< 0��ʾʧ�ܣ�����ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	long result;
	 *	unsigned char rlen, pass[64];
	 *	result = dc_getinputpass(icdev, 20, &rlen, pass);
	 *	\endcode
	 */
	long __stdcall dc_getinputpass(long icdev,unsigned char ctime,unsigned char *rlen,unsigned char * cpass);
	
	/*! \brief LED���ƺ���
	 *	\par ˵��:
	 *	����3��LEDָʾ�Ƶ�������
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\param[in] LedSel LED��ʶ�ţ�0��ʾLED1��1��ʾLED2��2��ʾLED3����
	 *	\param[in] LedCtr LED���Ʊ�־��1��ʾ����0��ʾ�𣩡�
	 *	\return ���< 0 ��ʾʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	int st;
	 *	st = dc_ctlled(icdev, 1, 1);		//����LED2����
	 *	\endcode
	 */
	long __stdcall dc_ctlled(long icdev,unsigned char LedSel,unsigned char LedCtr);	
	/*!	\brief LCD�������ú���
	 *	\par ˵��:
	 *	����LCD�ı�����ʾ�����Դ򿪻�رձ��⡣
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\param[in] OpenFlag ������Ʊ�־��0��ʾ�����⣬1��ʾ�ر��⣩��
	 *	\return ���< 0��ʾʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	int st;
	 *	st = dc_ctlbacklight(icdev, 0);		//�����⡣
	 *	\endcode
	 */
	long __stdcall dc_ctlbacklight(long icdev,unsigned char OpenFlag);
	
	/*!	\brief LCD��������
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\param[in] LineFlag �б�־��0��ʾ��һ�У�1��ʾ�ڶ��У�2��ʾ�����У�3��ʾ�����У�4��ʾ��ȫ������
	 *	\return ���< 0��ʾʧ�ܣ������ʾ�ɹ���
	 */
	long __stdcall dc_lcdclrscrn(long icdev,unsigned char LineFlag);
	
	/*!	\brief Ƕ��ʽ�ַ���ʾ
	 *	\par ˵��:
	 *	Ƕ��ʽ�ַ���ʾ�Ŀ��ƺ�����
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\param[in] line ��ʾ��ѡ��ȡֵ��Χ0~3��
	 *	\param[in] offset ��ʾ��ѡ��ȡֵ��Χ0~15��
	 *	\param[in] info Ҫ��ʾ�����ݡ����֣�0~9�����ַ���a~z,A~Z����
	 *	\return ���< 0��ʾʧ�ܣ������ʾ�ɹ���
	 */
	long __stdcall dc_dispsingle(long icdev,unsigned char line,unsigned char offset,unsigned char info);
	
	/*!	\brief ȫ���ַ���ʾ
	 *	\par ˵��:
	 *	ȫ���ַ���ASC���֣�һ���ַ�ռ��2���ֽڣ���ʾ���ơ�
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\param[in] line ��ʾ��ѡ�񣬷�Χ0~3��
	 *	\param[in] offset ��ʾ��ѡ�񣬷�Χ0~15��
	 *	\param[in] length ��ʾ�ַ��ĸ�������Χ1~8��
	 *	\param[in] data Ҫ��ʾ�����ݣ����б��룬����16 * 8��
	 *	\return ���< 0��ʾʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	long st;
	 *	st = dc_dispinfo(icdev, 0, 2, 3, "CAT");		//�ӵ�0�С���2�С���ʼ��ʾ����Ϊ3��ȫ���ַ�CAT��
	 *	\endcode
	 */ 
	long  __stdcall  dc_dispinfo(long icdev,unsigned char line,unsigned char offset,
								 unsigned char length,unsigned  char *data);
	
	/*! \brief ��������ַ���ʾ
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\param[in] line ��ʾ��ѡ�񣬷�Χ0~3��
	 *	\param[in] offset ��ʾ��ѡ��0~15��
	 *	\param[in] info Ҫ��ʾ�����ݡ�
	 */						
	long  __stdcall dc_dispsingleinfo(long icdev,unsigned char line,unsigned char offset,const char *info);
	
	/*!	\brief ���ö�д��ʱ��
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\param[in] year,month,date,hour,minute,second ����ʱ��:�ꡢ�¡��ա�Сʱ�����ӡ��롣
	 *	\return ���< 0ʧ�ܣ�����ɹ���
	 *	\par ʾ��:
	 *	\code
	 *	int st;
	 *	st = dc_setreadertime(icdev, 08, 06, 23, 12, 00, 00);		//���ö�д��ʱ��Ϊ:2008��6��23��12������
	 *	\endcode
	 */
	long __stdcall dc_setreadertime(long icdev,unsigned short year,unsigned short month,unsigned short date,
							        unsigned short hour,unsigned short minute,unsigned short second);
	
	/*!	\brief ��ȡ��д��ʱ��
	 *	\param[in] icdev �豸�˿ڱ�ʶ����
	 *	\param[out] year ��õĶ�д��ʱ������<100;
	 *	\param[out] month,date,hour,minute,second ��õĶ�д��ʱ����¡��ա�Сʱ�����ӡ��롣
	 *	\return ���< 0��ʾʧ�ܣ������ʾ�ɹ���
	 *	\par ʾ��:
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
//����IDģ��
long  __stdcall  dc_setID(long icdev,unsigned char *sdata,unsigned long slen);
//�����ֻ�
long __stdcall  dc_rf_sim(long icdev,unsigned char slen,unsigned char *cmd,unsigned char *rlen,unsigned char *Num_sim);

#if defined(__cplusplus)
}
#endif
