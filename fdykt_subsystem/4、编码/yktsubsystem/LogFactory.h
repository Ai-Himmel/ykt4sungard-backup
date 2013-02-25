// LogFactory.h: interface for the KLogFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGFACTORY_H__CE52BE19_F63E_4C35_9D8A_7C01CD6E32D4__INCLUDED_)
#define AFX_LOGFACTORY_H__CE52BE19_F63E_4C35_9D8A_7C01CD6E32D4__INCLUDED_
/** 
 * ģ����					�����ϵͳ
 * �ļ���					LogFactory.h
 * �ļ�ʵ�ֹ���				��־�๤��������
 * ����						����
 * �汾						V0.1
 * ����						2005-08-01
 * ��ע
 * $Id: LogFactory.h 15 2005-08-22 02:39:12Z cash $
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include "KLogfile.h"

/** 
 * @brief ��־������
 */
class KLogFactory  
{
	/** 
	 * @brief ������
	 */
	class KMutex
	{
	private:
#ifdef WIN32
		/** 
		 * @brief ϵͳ�������
		 */
		CRITICAL_SECTION m_mutex;
#else
#endif
	public:
		/** 
		 * @brief ���뻥����������Ѿ��������߳̽����˻���������ú���������
		 * 
		 * @return - ʧ�ܷ��� -1 ���ɹ����� 0
		 */
		int Lock();
		/** 
		 * @brief �뿪������
		 * 
		 * @return - �ɹ����� 0��ʧ�ܷ��� -1
		 */
		int UnLock();
		/** 
		 * @brief ���캯��
		 */
		KMutex();
		/** 
		 * @brief ��������
		 */
		virtual ~KMutex();
	};
private:
	/** 
	 * @brief �������Ψһʵ��
	 */
	static KLogFactory* ms_Instance;
	/** 
	 * @brief �������
	 */
	static KMutex ms_Mutex;
	/** 
	 * @brief ��־�ļ���
	 */
	static std::string ms_LogFileName;
	/** 
	 * @brief ��־�ļ�·��
	 */
	static std::string ms_LogDir;

private:
	/** 
	 * @brief ��־�ļ���
	 */
	KLogfile m_logfile;
	/** 
	 * @brief ���캯��
	 */
	KLogFactory();
	/** 
	 * @brief ��ǰʱ��
	 */
	std::string m_CurrentDate;
	/** 
	 * @brief ��ȡ��ǰϵͳʱ��
	 * 
	 * @return - ����ϵͳʱ��
	 */
	std::string GetCurrentDateString();
	/** 
	 * @brief ���System  Tick��Count
	 * 
	 * @return - 
	 */
	long GetTickCount();
	/** 
	 * @brief ����ʱ�������µ���־�ļ���
	 * 
	 * @param timestampe - ʱ��
	 * 
	 * @return - �ɹ�����0��ʧ�ܷ��� -1
	 */
	int RenameFile(const std::string& timestampe);
	/** 
	 * @brief �����ļ���ǰ׺��ʱ��������־�ļ���
	 * 
	 * @param filename - �ļ���ǰ׺
	 * @param timestampe - ʱ��
	 */
	void GenLogFileName(std::string& filename,
		const std::string& timestampe);
public:
	/** 
	 * @brief ���õ�ǰ��־ϵͳ��·��
	 * 
	 * @param path - ·��
	 */
	static void SetLogFileDirectory(const std::string& path);
	/** 
	 * @brief ��ȡ�������Ψһʵ��
	 * 
	 * @return - ����Ψһʵ��
	 */
	static KLogFactory* GetInstance();
	/** 
	 * @brief �ͷŹ������Ψһʵ��
	 */
	static void Release();
public:
	/** 
	 * @brief ȡ�õ�ǰ����־�ļ���
	 * 
	 * @return - ��־�ļ����ָ��
	 */
	virtual KLogfile* GetLogSys();
	/** 
	 * @brief ��������
	 */
	virtual ~KLogFactory();
};

#endif // !defined(AFX_LOGFACTORY_H__CE52BE19_F63E_4C35_9D8A_7C01CD6E32D4__INCLUDED_)
