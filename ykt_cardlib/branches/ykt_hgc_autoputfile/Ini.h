//********************************************
//	Ini.h
//********************************************
//#include "stdafx.h"

#ifndef _INI_H_
#define _INI_H_

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x)!=NULL ) { delete (x); (x)=NULL; }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if( (x)!=NULL ) { delete[] (x); (x)=NULL; }
#endif

#ifndef SAFE_FREE
#define SAFE_FREE(x)	if( (x)!=NULL ) { free(x); (x)=NULL; }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	if( (x)!=NULL ) { (x)->Release(); (x)=NULL; }
#endif

#define ERROR_DATA -99999999
#define FILE_MAX_PATH 1024
#define ERROR_DATA_POS -10
#define ERROR_FILE_LENGTH -1

// �����ļ���
class CIni
{
////////////////////////////////////////////////
// �ڲ�����
////////////////////////////////////////////////
private:
	char m_str_file_name[FILE_MAX_PATH];	// �ļ���
	long m_data_length;						// �ļ�����
	char *m_str_data;						// �ļ�����
	int  m_index_num;						// ������Ŀ([]����Ŀ)
	int  *m_index_list;						// ������λ���б�
	int  m_point;							// ��ǰָ��
	int  m_line, m_word;					// ��ǰ����
	int  m_file_step;						// д�ļ����ļ�����������С
//	int  m_file_pos;						// �ļ�ָ��λ��(�����޸��ļ��Ժ�ʹ��)

////////////////////////////////////////////////
// ͨ�ýӿ�
////////////////////////////////////////////////
public:
	CIni();
	CIni(char*);							// ��ʼ���������ļ�
	virtual ~CIni();						// �ͷ��ڴ�
	char *GetData();						// �����ļ�����
	int GetLines(int);						// �����ļ�������
	bool Open(char *);						// �������ļ�
	void Close();							// �ر������ļ�
	bool Save(char *filename = NULL);		// ���������ļ�

////////////////////////////////////////////////
// �ڲ�����
////////////////////////////////////////////////
private:
	void InitIndex();						// ��ʼ������
	int FindIndex(char *);					// ���ر���λ��
	int FindData(int, char *);				// ��������λ��
	int GotoNextLine(int); 					// ����
	char *ReadKeyName(int &);				// ��ָ��λ�ö�һ��������
	char *ReadText(int);					// ��ָ��λ�ö��ַ���
	bool AddIndex(char *);					// ����һ������
	bool AddData(int, char *, char *);		// �ڵ�ǰλ�ü���һ������
	bool ModityData(int, char *, char *);	// �ڵ�ǰλ���޸�һ�����ݵ�ֵ
	int GotoLastLine(char *index);			// ��ָ���ƶ�����INDEX�����һ��

////////////////////////////////////////////////
// ���ýӿ�
////////////////////////////////////////////////
public:
	int ReadInt(char *, char *);			//��һ������
	int ReadInt(char *, int );				//��ָ�����ж�һ����
	char *ReadText(char *, char *);			//��һ���ַ���
	char *ReadText(char *, int);			//��ָ�����ж�һ�ַ���
	char *ReadCaption(char *, int);			//��ָ���ж�һ�ַ�����
	bool Write(char *, char *, int);		//дһ������
	bool Write(char *, char *, char *);		//дһ���ַ���
	int GetContinueDataNum(char *);			//������������������INDEX����һ�����У�
};

#endif /*_INI_H_*/