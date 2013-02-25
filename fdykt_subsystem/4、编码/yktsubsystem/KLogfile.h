// KLogfile.h: interface for the KLogfile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KLOGFILE_H__4B754F84_0DC1_4BE0_8C3C_633FD0912786__INCLUDED_)
#define AFX_KLOGFILE_H__4B754F84_0DC1_4BE0_8C3C_633FD0912786__INCLUDED_
/** 
 * ģ����					�����ϵͳ
 * �ļ���					KLogfile.h
 * �ļ�ʵ�ֹ���				��־������
 * ����						����
 * �汾						V0.1
 * ����						2005-08-01
 * ��ע
 * $Id: KLogfile.h 15 2005-08-22 02:39:12Z cash $
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <fstream>

class KLogfile  
{
private:
	/** 
	 * @brief ��־�ļ���
	 */
	std::string m_LogFileName;
	/** 
	 * @brief ��־�����
	 */
	std::ofstream* m_logFileStream;
	/** 
	 * @brief ȡ�õ�ǰϵͳʱ��
	 * 
	 * @return ��ǰϵͳʱ��
	 */
	std::string GetCurrentTimeString();
	/** 
	 * @brief ��־�Ƿ��
	 */
	bool m_IsLogOpen;
public:
	/** 
	 * @brief Constructor
	 */
	KLogfile();
	/** 
	 * @brief Constructor��������־�ļ�������־
	 * 
	 * @param filename - ��־�ļ���
	 */
	KLogfile(const char* filename);
	/** 
	 * @brief ����־�������־�Ѿ��������ȹر�
	 * 
	 * @param logfile - ��־�ļ���
	 * 
	 * @return - �ɹ����� 0��ʧ�ܷ��� -1
	 */
	int OpenLogfile(const char * logfile);
	/** 
	 * @brief �ر���־
	 * 
	 * @return - �ɹ�����0��ʧ�ܷ��� -1
	 */
	int CloseLog();
	/** 
	 * @brief ˢ����־����
	 */
	void Flush();
	/** 
	 * @brief д���ַ�������־�ļ���
	 * 
	 * @param msg - ��־����
	 * 
	 * @return - ������־�������
	 */
	KLogfile& operator<<(const char* msg);
	/** 
	 * @brief д��־��Ϣ
	 * 
	 * @param fmt - ��־��ʽ���ַ�����ͬ printf
	 * @param ... - �ɱ����
	 * 
	 * @return - ������־�������
	 */
	KLogfile& WriteLog(const char* fmt,...);
	/** 
	 * @brief destructor,�ر���־
	 */
	virtual ~KLogfile();
};

#endif // !defined(AFX_KLOGFILE_H__4B754F84_0DC1_4BE0_8C3C_633FD0912786__INCLUDED_)
