#if !defined(AFX_REQUESTSOCKET_H__6B775461_DD55_45C0_B66B_594E533CAFC4__INCLUDED_)
#define AFX_REQUESTSOCKET_H__6B775461_DD55_45C0_B66B_594E533CAFC4__INCLUDED_
/** 
 * ģ����						�����ϵͳ
 * �ļ���						RequestSocket.h
 * �ļ�ʵ�ֹ���					�������������Socket
 * ����							����
 * �汾							V0.1
 * ����							2005-07-02
 * ��ע
 * $Id: RequestSocket.h 15 2005-08-22 02:39:12Z cash $
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RequestSocket.h : header file
//
#include "yktsubsystemDoc.h"

// ���ݻ���Buf��С
#define DEFAULT_BUF_SIZE 4096 << 1  // 8K
// �ݲ�ʹ��
#define MAX_BUFFER_SIZE 1024 << 16  // 1M
/////////////////////////////////////////////////////////////////////////////
// CRequestSocket command target

/** 
 * @brief ����������յ�����
 */
class CRequestSocket : public CAsyncSocket
{
// Attributes
public:
	/** 
	 * @brief ҵ����״̬����
	 */
	enum REQSTATUS {
		REQ_REQUEST = 0,	// ��������
		REQ_GET_NEXT_PACK , // �ȴ�������һ���ݰ�
		REQ_DONE,			// ���մ����������
		REQ_ERROR,			// ����ʧ��
		REQ_RECV_OK			// �����������
		};
private:
	/** 
	 * @brief ��ǰҵ����״̬
	 */
	REQSTATUS m_reqStatus;
	/** 
	 * @brief Document ��ָ��
	 */
	CYktsubsystemDoc * m_pDoc;
	//CByteArray m_buf;
	/** 
	 * @brief ���ݻ���
	 */
	BYTE m_buf[DEFAULT_BUF_SIZE];
	/** 
	 * @brief Buf�����ݳ���
	 */
	long m_buf_len;
	/** 
	 * @brief ��ҵ�����п�ʼ��ʱ��
	 */
	long m_startTick;
	/** 
	 * @brief ϵͳ�Ƿ����ڴ���ҵ��
	 */
	BOOL m_IsRunning;

	/** 
	 * @brief ������յ�������
	 */
	void DoGetData();
	/** 
	 * @brief �����ݽṹ����һ������
	 * 
	 * @param card_info - ���ݽṹ
	 * 
	 * @return - �ɹ����� 0 ��ʧ�ܷ��� -1
	 */
	int ProcessRequest(ksf_card_info * card_info);
	/** 
	 * @brief ���ʹ�������ͨ��ǰ��
	 * 
	 * @param res - �������ṹ
	 */
	void SendResult(ksf_card_result * res);
	/** 
	 * @brief �������ݰ������صĽ��ܺ�����ݰ������ֶ��ͷ��ڴ�
	 * 
	 * @param info - ���ܵ����ݰ��ṹ
	 * 
	 * @return - �ɹ����ܷ��ؽ��ܺ�����ݰ���ʧ�ܷ��� NULL
	 */
	ksf_xml_data * DecryptData(ksf_card_info * info);
	/** 
	 * @brief ʹ�� AES 128 λ�����㷨���н���
	 * 
	 * @param info - [in out]���ܵ����ݰ�,���ܺ�����ݰ�Ҳ���������
	 * 
	 * @return - �ɹ�����0��ʧ�ܷ��� -1
	 */
	int DecryptAES128(ksf_card_info* info);

	/** 
	 * @brief ��ʼ������״̬
	 */
	void ResetReceive();
	/** 
	 * @brief �����������յ����ݵ�������
	 * 
	 * @param buf - ����Buf
	 * @param len - Buf ����
	 */
	void SaveData(BYTE * buf,int len);
// Operations
public:
	/** 
	 * @brief ���캯��
	 */
	CRequestSocket();
	/** 
	 * @brief ���캯��
	 * 
	 * @param pDoc - Document ��
	 */
	CRequestSocket(CYktsubsystemDoc * pDoc);
	/** 
	 * @brief ��������
	 */
	virtual ~CRequestSocket();
	/** 
	 * @brief �������ݣ�<b>��ʹ��</b>
	 * 
	 * @return - �ɹ�����0 ��ʧ�ܷ��� -1
	 */
	int ProcessRequest();
	/** 
	 * @brief �ͷ��Լ�
	 */
	void Release();
	/** 
	 * @brief ȡ�ø�ҵ��ʼ����ʱ��
	 * 
	 * @return - ��ʼ����ʱ��
	 */
	inline long GetStartTick()
	{
		return m_startTick;
	}
	/** 
	 * @brief ��ǰҵ���Ƿ���������
	 * 
	 * @return - �������з��� True�����򷵻� False
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
