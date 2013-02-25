/****************************************************************************
*
*�ļ�(File):         usbprog.h
*
*�޸�(Modify):       2011/8/9 11:38:49
*
*����(Author):       USER
*
*����(Compile):      ����ƽ̨(Smart Platform)
*
*����(Description):
*
*
*
----------------------------------------------------------------------------
|
| Version | Datetime             |   Author    | Description
| --------+----------------------+-------------+----------------------------
|
| V1.00  2011/8/9 11:38:49           USER 
----------------------------------------------------------------------------
****************************************************************************/


 #ifndef   usbprog_h_2011_08_09_14_38_49_INCLUDED
 #define   usbprog_h_2011_08_09_14_38_49_INCLUDED
 #ifndef	_USBPROG_H_
#define	_USBPROG_H_

//��ʾ���ݰ�Ϊ��������		
#define	USB_CMD_REQ								0x01

//��ʾ���ݰ�Ϊ��������ķ��ش���
#define	USB_CMD_RTC								0x02

//��ʾ���ݰ�Ϊ��������ķ�������
#define	USB_CMD_RTD								0x03

//��ѯĳ��ļ�¼��
#define	USB_CMD_DATA_COUNT				0x03	

//�����ֳֻ���ʱ��
#define	USB_CMD_SET_TIME					0x04	

//PC������ͨѶ���
#define	USB_CMD_DISCONNECT				0x05	

//ɾ��ĳһ���������
#define USB_CMD_DEL_FSID					   0x0A  

//ɾ�����б������
#define USB_CMD_DEL_ALLFS				 	0x0B  

//У���ֳֻ�ĳ��������Ч��
#define USB_CMD_VERIFY_TAB				   0x0C  

//�õ������Ϣ
#define USB_CMD_TABLE_INFO   				0x0d

//����ʧ�ܱ�־
#define USB_CMD_OPER_ERR     					0x0e

//�����������
#define	USB_CMD_RECV_DATA					0x0F

//����������
#define	USB_CMD_SEND_DATA					0x10	

//�ϴ��ֳֻ�����
#define	USB_CMD_SENDMACHINEPARA    0x11

extern int Usb_Data_Transmit(void);

extern int	 USBDownLongString(unsigned char *DataBuffer, unsigned int *DataLen);

extern int USBUpLongString(unsigned char *DataBuffer, unsigned int DataLen);

#endif 


 #endif   /*usbprog_h_2011_08_09_14_38_49_INCLUDED*/
