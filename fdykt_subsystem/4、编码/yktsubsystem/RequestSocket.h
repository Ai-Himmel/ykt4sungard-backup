#if !defined(AFX_REQUESTSOCKET_H__6B775461_DD55_45C0_B66B_594E533CAFC4__INCLUDED_)
#define AFX_REQUESTSOCKET_H__6B775461_DD55_45C0_B66B_594E533CAFC4__INCLUDED_
/** 
 * 模块名						外接子系统
 * 文件名						RequestSocket.h
 * 文件实现功能					处理网络请求的Socket
 * 作者							汤成
 * 版本							V0.1
 * 日期							2005-07-02
 * 备注
 * $Id: RequestSocket.h 15 2005-08-22 02:39:12Z cash $
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RequestSocket.h : header file
//
#include "yktsubsystemDoc.h"

// 数据缓存Buf大小
#define DEFAULT_BUF_SIZE 4096 << 1  // 8K
// 暂不使用
#define MAX_BUFFER_SIZE 1024 << 16  // 1M
/////////////////////////////////////////////////////////////////////////////
// CRequestSocket command target

/** 
 * @brief 处理网络接收的数据
 */
class CRequestSocket : public CAsyncSocket
{
// Attributes
public:
	/** 
	 * @brief 业务处理状态变量
	 */
	enum REQSTATUS {
		REQ_REQUEST = 0,	// 接收数据
		REQ_GET_NEXT_PACK , // 等待接收下一数据包
		REQ_DONE,			// 接收处理数据完成
		REQ_ERROR,			// 接收失败
		REQ_RECV_OK			// 接收数据完成
		};
private:
	/** 
	 * @brief 当前业务处理状态
	 */
	REQSTATUS m_reqStatus;
	/** 
	 * @brief Document 类指针
	 */
	CYktsubsystemDoc * m_pDoc;
	//CByteArray m_buf;
	/** 
	 * @brief 数据缓存
	 */
	BYTE m_buf[DEFAULT_BUF_SIZE];
	/** 
	 * @brief Buf中数据长度
	 */
	long m_buf_len;
	/** 
	 * @brief 该业务运行开始的时间
	 */
	long m_startTick;
	/** 
	 * @brief 系统是否正在处理业务
	 */
	BOOL m_IsRunning;

	/** 
	 * @brief 处理接收到的数据
	 */
	void DoGetData();
	/** 
	 * @brief 将数据结构做进一步处理
	 * 
	 * @param card_info - 数据结构
	 * 
	 * @return - 成功返回 0 ，失败返回 -1
	 */
	int ProcessRequest(ksf_card_info * card_info);
	/** 
	 * @brief 发送处理结果给通用前置
	 * 
	 * @param res - 处理结果结构
	 */
	void SendResult(ksf_card_result * res);
	/** 
	 * @brief 解密数据包，返回的解密后的数据包必须手动释放内存
	 * 
	 * @param info - 加密的数据包结构
	 * 
	 * @return - 成功解密返回解密后的数据包，失败返回 NULL
	 */
	ksf_xml_data * DecryptData(ksf_card_info * info);
	/** 
	 * @brief 使用 AES 128 位加密算法进行解密
	 * 
	 * @param info - [in out]加密的数据包,解密后的数据包也存放在这里
	 * 
	 * @return - 成功返回0，失败返回 -1
	 */
	int DecryptAES128(ksf_card_info* info);

	/** 
	 * @brief 初始化接收状态
	 */
	void ResetReceive();
	/** 
	 * @brief 保存从网络接收的数据到缓存中
	 * 
	 * @param buf - 数据Buf
	 * @param len - Buf 长度
	 */
	void SaveData(BYTE * buf,int len);
// Operations
public:
	/** 
	 * @brief 构造函数
	 */
	CRequestSocket();
	/** 
	 * @brief 构造函数
	 * 
	 * @param pDoc - Document 类
	 */
	CRequestSocket(CYktsubsystemDoc * pDoc);
	/** 
	 * @brief 析构函数
	 */
	virtual ~CRequestSocket();
	/** 
	 * @brief 处理数据，<b>不使用</b>
	 * 
	 * @return - 成功返回0 ，失败返回 -1
	 */
	int ProcessRequest();
	/** 
	 * @brief 释放自己
	 */
	void Release();
	/** 
	 * @brief 取得该业务开始运行时间
	 * 
	 * @return - 开始运行时间
	 */
	inline long GetStartTick()
	{
		return m_startTick;
	}
	/** 
	 * @brief 当前业务是否正在运行
	 * 
	 * @return - 正在运行返回 True，否则返回 False
	 */
	inline BOOL IsRunning()
	{
		return m_IsRunning;
	}
// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRequestSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CRequestSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REQUESTSOCKET_H__6B775461_DD55_45C0_B66B_594E533CAFC4__INCLUDED_)
