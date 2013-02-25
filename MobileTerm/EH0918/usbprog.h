/****************************************************************************
*
*文件(File):         usbprog.h
*
*修改(Modify):       2011/8/9 11:38:49
*
*作者(Author):       USER
*
*编绎(Compile):      智能平台(Smart Platform)
*
*描述(Description):
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

//表示数据包为操作请求		
#define	USB_CMD_REQ								0x01

//表示数据包为操作请求的返回代码
#define	USB_CMD_RTC								0x02

//表示数据包为操作请求的返回数据
#define	USB_CMD_RTD								0x03

//查询某表的记录数
#define	USB_CMD_DATA_COUNT				0x03	

//设置手持机的时钟
#define	USB_CMD_SET_TIME					0x04	

//PC机数据通讯完毕
#define	USB_CMD_DISCONNECT				0x05	

//删除某一个表的数据
#define USB_CMD_DEL_FSID					   0x0A  

//删除所有表的数据
#define USB_CMD_DEL_ALLFS				 	0x0B  

//校验手持机某表数据有效性
#define USB_CMD_VERIFY_TAB				   0x0C  

//得到表的信息
#define USB_CMD_TABLE_INFO   				0x0d

//操作失败标志
#define USB_CMD_OPER_ERR     					0x0e

//请求接收数据
#define	USB_CMD_RECV_DATA					0x0F

//请求发送数据
#define	USB_CMD_SEND_DATA					0x10	

//上传手持机参数
#define	USB_CMD_SENDMACHINEPARA    0x11

extern int Usb_Data_Transmit(void);

extern int	 USBDownLongString(unsigned char *DataBuffer, unsigned int *DataLen);

extern int USBUpLongString(unsigned char *DataBuffer, unsigned int DataLen);

#endif 


 #endif   /*usbprog_h_2011_08_09_14_38_49_INCLUDED*/
