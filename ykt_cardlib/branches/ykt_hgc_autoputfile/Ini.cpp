//********************************************
//	Ini.cpp
//********************************************

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>
#include "Ini.h"

////////////////////////////////////////////////
// ͨ�ýӿ�
////////////////////////////////////////////////

CIni::CIni()
{
	m_data_length = 0;
	m_str_data = NULL;
	m_index_num = 0;
	m_index_list = NULL;
	m_file_step = 0;
}

CIni::CIni(char *filename)
{
	m_data_length = 0;
	m_str_data = NULL;
	m_index_num = 0;
	m_index_list = NULL;
	m_file_step = 0;
	Open(filename);
}

CIni::~CIni()
{
	if( m_data_length != 0 )
	{
		SAFE_DELETE( m_str_data );
		m_data_length = 0;
	}

	if( m_index_num != 0 )
	{
		SAFE_DELETE( m_index_list );
		m_index_num = 0;
	}
}

/*================================================================ 
* ��������    Open
* ������      [in] (char *filename)�ļ�����
* ��������:   ��ָ����INI�ļ�
* ����ֵ��    bool, �ɹ�Ϊtrue, ����Ϊfalse
================================================================*/ 
bool CIni::Open(char *filename)
{
	strcpy(m_str_file_name, filename);

	SAFE_FREE( m_str_data );

	//��ȡ�ļ�����
	int fh;
	fh = _open( filename, _O_RDONLY );
	if (fh == ERROR_FILE_LENGTH)
	{
		m_data_length = -1;
	}
	m_data_length = _filelength(fh);
	_close(fh);
	
	//�ļ�����
	if( m_data_length > 0 )
	{
		m_str_data = new char[m_data_length];

		FILE *fp;
		fp = fopen(filename, "rb");
		if (NULL == fp)
		{
			SAFE_DELETE(m_str_data);
			return false;
		}

		fread(m_str_data, m_data_length, 1, fp);		//������

		fclose(fp);

		//��ʼ������
		InitIndex();
		return true;
	}
	else	// �ļ�������
	{
		// �Ҳ����ļ�
		m_data_length=1;
		m_str_data = new char[m_data_length];
		memset(m_str_data, 0, 1);
		InitIndex();
	}

	return false;
}

/*================================================================ 
* ��������    Close
* ������      [in] ()
* ��������:   �ر�ָ����INI�ļ�
* ����ֵ��    void
================================================================*/
void CIni::Close()
{
	if( m_data_length != 0 )
	{
		SAFE_DELETE(m_str_data);
		m_data_length = 0;
	}

	if( m_index_num != 0 )
	{
		SAFE_DELETE(m_index_list);
		m_index_num = 0;
	}
}

/*================================================================ 
* ��������    Save
* ������      [in] (char *filename)�ļ�����
* ��������:   �����ļ�
* ����ֵ��    bool, �ɹ�Ϊtrue, ����Ϊfalse
================================================================*/ 
bool CIni::Save(char *filename)
{
	if( filename == NULL )
	{
		filename = m_str_file_name;
	}

	FILE *fp;
	fp = fopen(filename, "wb");
	if (NULL == fp)
		return false;

	fwrite(m_str_data, m_data_length, 1, fp);
	fclose(fp);

	return true;
}

/*================================================================ 
* ��������    GetData
* ������      [in] ()
* ��������:   �����ļ�����
* ����ֵ��    �ļ��ַ����ı�
================================================================*/
char *CIni::GetData()
{
	return m_str_data;
}

/*================================================================ 
* ��������    GetLines
* ������      [in] (int file_cur)�ļ�λ��
* ��������:   ��ȡ�ļ��ӵ�ǰ�ļ�ָ��λ�ÿ�ʼ������
* ����ֵ��    �ļ�����(char *)
================================================================*/
int CIni::GetLines(int file_cur)
{
	int lines = 1;
	for(int i = 0; i < file_cur; i++)
	{
		if (m_str_data[i] == '\n') { lines++; }
	}
	return lines;
}

////////////////////////////////////////////////
// �ڲ�����
////////////////////////////////////////////////

/*================================================================ 
* ��������    InitIndex
* ������      [in] ()
* ��������:   ��ʼ��INI�ļ�����
* ����ֵ��    void
================================================================*/
void CIni::InitIndex()
{
	m_index_num = 0;

	for (int i = 0; i < m_data_length; i++)
	{
		//�ҵ�
		if (m_str_data[i] == '[' && (m_str_data[i - 1] == '\n' || i == 0))
		{
			m_index_num++;
		}
	}

	//�����ڴ�
	SAFE_DELETE(m_index_list);
	if ( m_index_num > 0 )
		m_index_list = new int[m_index_num];

	int n = 0;

	for (i = 0; i < m_data_length; i++)
	{
		if (m_str_data[i] == '[' && (m_str_data[i - 1] == '\n' || i == 0 ))
		{
			m_index_list[n] = i + 1;
			n++;
		}
	}
}

/*================================================================ 
* ��������    FindIndex
* ������      [in] (char *string)�ļ���������
* ��������:   ����ָ������λ��
* ����ֵ��    �ɹ��򷵻��ļ������ĵ�ǰλ��, ���򷵻�-10
================================================================*/
int CIni::FindIndex(char *string)
{
	for (int i = 0; i < m_index_num; i++)
	{
		char *str = ReadText(m_index_list[i]);
		if (strcmp(string, str) == 0)
		{
			SAFE_FREE(str);
			return m_index_list[i];
		}
		SAFE_FREE(str);
	}
	return ERROR_DATA_POS;
}

/*================================================================ 
* ��������    FindData
* ������      [in] (int index)�ļ������ĵ�ǰλ��
*             [in] (char *string)�ļ�KEY������
* ��������:   ����ָ�����ݵ�λ��
* ����ֵ��    �ɹ��򷵻�ָ�����ݵĵ�ǰλ��, ���򷵻�-10
================================================================*/
int CIni::FindData(int index, char *string)
{
	int data_pos = index;	//ָ��

	while(1)
	{
		data_pos = GotoNextLine(data_pos);
		char *name = ReadKeyName(data_pos);
		if (strcmp(string, name) == 0)
		{
			SAFE_FREE(name);
			return data_pos;
		}

		SAFE_FREE( name );
		if (data_pos >= m_data_length) 
			return ERROR_DATA_POS;
	}
	return ERROR_DATA_POS;
}

/*================================================================ 
* ��������    GotoNextLine
* ������      [in] (int file_pos)�ļ���ǰλ��
* ��������:   ���ص�ǰλ�õ���һ�п�ͷ���ݵ��ļ�λ�õĳ���
* ����ֵ��    �ɹ��򷵻ص�ǰ�ļ�λ�õ���һ�п�ʼλ�õĳ���, 
*             ���򷵻ص�ǰλ�õ��ļ���β֮��ĳ���
================================================================*/
int CIni::GotoNextLine(int file_pos)
{
	for (int i = file_pos; i < m_data_length; i++)
	{
		if (m_str_data[i] == '\n') { return (++i); }
	}
	return (++i);
}

/*================================================================ 
* ��������    ReadKeyName
* ������      [in] (int &data_pos)�ļ��ĵ�ǰλ��
* ��������:   ��ָ��λ�ö�һKEY����
* ����ֵ��    �ɹ��򷵻�KEY����, ���򷵻ؿ�
================================================================*/
char *CIni::ReadKeyName(int &data_pos)
{
	char chr = NULL;
	char *key_name= NULL;
	int pos = 0;

	key_name = new char[64];
	memset(key_name, 0, 64);

	for (int i = data_pos; i < m_data_length; i++)
	{
		chr = m_str_data[i];

		//����
		if (chr == '\n')
		{
			data_pos = i + 1;
			return key_name;
		}
		
		//����
		if( chr == '=' || chr == ';' )
		{
			data_pos = i + 1;
			return key_name;
		}
		
		key_name[pos] = chr;
		pos++;
	}
	return key_name;
}

/*================================================================ 
* ��������    ReadText
* ������      [in] (int file_pos)�ļ��ĵ�ǰλ��
* ��������:   ��ָ��λ�ö�һNAME�ַ���
* ����ֵ��    �ɹ��򷵻�NAME�ַ���, ���򷵻ؿ�
================================================================*/
char *CIni::ReadText(int file_pos)
{
	char chr = NULL;
	char *value_name = NULL;
	int index_start = file_pos;

	int line_num = GotoNextLine(file_pos) - file_pos;
	value_name = new char[line_num];
	memset(value_name, 0, line_num);

	for (int i = 0; i < m_data_length - file_pos; i++)
	{
		chr = m_str_data[index_start];

		//����
		if (chr == ';' || chr == ' ' || chr == ']' || chr == '\n' || chr == '\r') { return value_name; }

		value_name[i] = chr;
		index_start++;
	}

	return value_name;
}


/*================================================================ 
* ��������    AddIndex
* ������      [in] (char *index_name)��������
* ��������:   ����һ������
* ����ֵ��    �ɹ��򷵻�true, ����false
================================================================*/
bool CIni::AddIndex(char *index_name)
{
	char str[256] = "";
	int n = FindIndex(index_name);

	if (n == ERROR_DATA_POS)	//�½�����
	{
		sprintf(str,"[%s]", index_name);
		m_str_data = (char *)realloc(m_str_data, m_data_length + strlen(str));	//���·����ڴ�
		sprintf(&m_str_data[m_data_length], "%s", str);
		m_data_length += strlen(str);
		InitIndex();
		return true;
	}
	
	return false;	//�Ѿ�����
}

/*================================================================ 
* ��������    AddData
* ������      [in] (int pos)��ǰ�ļ�λ��
*		      [in] (char *key_name)KEY����
*             [in] (char *value_name)VALUE����
* ��������:   �ڵ�ǰλ�ü���һ������
* ����ֵ��    �ɹ��򷵻�true, ����false
================================================================*/
bool CIni::AddData(int pos, char *key_name, char *value_name)
{
	char *str = NULL;
	int len = strlen(value_name);
	str = new char[len + 256];
	memset(str, 0, len + 256);
	sprintf(str,"%s=%s", key_name, value_name);
	len = strlen(str);

	pos = GotoNextLine(pos);	//����
	m_str_data = (char *)realloc(m_str_data, m_data_length + len);	//���·����ڴ�

	char *temp = new char[m_data_length - pos];
	memcpy(temp, &m_str_data[pos], m_data_length - pos);
	memcpy(&m_str_data[pos + len], temp, m_data_length - pos);	//�Ѻ���İᵽĩβ
	memcpy(&m_str_data[pos], str, len);
	m_data_length += len;

	SAFE_DELETE(temp);
	SAFE_DELETE(str);
	return true;
}

/*================================================================ 
* ��������    ModityData
* ������      [in] (int file_pos)��ǰ�ļ�λ��
*		      [in] (char *key_name)KEY����
*             [in] (char *value_name)VALUE����
* ��������:   �ڵ�ǰλ���޸�һ�����ݵ�ֵ
* ����ֵ��    �ɹ��򷵻�true, ����false
================================================================*/
bool CIni::ModityData(int file_pos, char *key_name, char *value_name)
{
	int index = 0;

	int data_pos = FindData(file_pos, key_name);

	char *index_name = ReadText(data_pos);
	file_pos = data_pos + strlen(index_name);
	if (strlen(index_name) > 0) 
		free(index_name);

	int newlen = strlen(value_name);
	int oldlen = file_pos - data_pos;

	m_str_data = (char *)realloc(m_str_data, m_data_length + newlen - oldlen);	// ���·����ڴ�

	char *temp = new char[m_data_length - file_pos];
	memcpy(temp, &m_str_data[file_pos], m_data_length - file_pos);
	memcpy(&m_str_data[data_pos + newlen], temp, m_data_length - file_pos);		// �Ѻ���İᵽĩβ
	memcpy(&m_str_data[data_pos], value_name, newlen);
	m_data_length += newlen - oldlen;
	
	m_file_step = (newlen - oldlen);											// ������һ������λ��
//	m_file_pos = file_pos;														// �޸ĺ���ļ�λ��		

	SAFE_DELETE(temp);

	while (index < m_index_num)														// �޸ĺ��������������λ���ƶ� 
	{ 
		if (m_index_list[index] >= file_pos) { m_index_list[index] += m_file_step; }

		index++;
	}		

	return true;
}

/*================================================================ 
* ��������    GotoLastLine
* ������      [in] (int index_name)��ǰ��������
* ��������:   ��ָ���ƶ�����INDEX�����һ��
* ����ֵ��    �ɹ��򷵻�true, ����false
================================================================*/
int CIni::GotoLastLine(char *index_name)
{
	int data_pos = FindIndex(index_name);
	data_pos = GotoNextLine(data_pos);
	while(1)
	{
		if (m_str_data[data_pos] == '\n'		|| 
			m_str_data[data_pos] == EOF			||
			m_str_data[data_pos] == ' '			|| 
			m_str_data[data_pos] == '/'			|| 
			m_str_data[data_pos] == '	'	
			)
		{
			return data_pos;
		}
		else
		{
			data_pos = GotoNextLine(data_pos);

			if (data_pos >= m_data_length) { return data_pos; }
		}
	}
}

/////////////////////////////////////////////////////////////////////
// ����ӿ�
/////////////////////////////////////////////////////////////////////

/*================================================================ 
* ��������    ReadText
* ������      [in] (char *index_name)��ǰ��������
*             [in] (char *key_name)KEY����
* ��������:   ����ͨ��ʽ��һ�ַ�������
* ����ֵ��    �ɹ��򷵻��ı�����, ���򷵿�
================================================================*/
char *CIni::ReadText(char *index_name, char *key_name)
{
	int data_pos = FindIndex(index_name);
	if (ERROR_DATA_POS == data_pos)
		return "";

	int data_pos2 = FindData(data_pos, key_name);

	if (ERROR_DATA_POS == data_pos)
		return "";

	return ReadText(data_pos2);
}

/*================================================================ 
* ��������    ReadText
* ������      [in] (int index_name)��ǰ��������
*             [in] (int lines)ָ������
* ��������:   ��ָ�����ж�һ�ַ���
* ����ֵ��    �ɹ��򷵻��ı�����, ���򷵿�
================================================================*/
char *CIni::ReadText(char *index_name, int lines)
{
	int data_pos = FindIndex(index_name);

	if (ERROR_DATA_POS == data_pos)
		return "";

	// ����ָ������
	data_pos = GotoNextLine(data_pos);
	for (int i = 0; i < lines; i++)
	{
		if (data_pos < m_data_length)
			data_pos = GotoNextLine(data_pos);
	}

	// ������
	while (data_pos <= m_data_length)
	{
		if (m_str_data[data_pos] == '=')
		{
			data_pos++;
			return ReadText(data_pos);
		}
		if (m_str_data[data_pos] == '\n')
		{
			return "";
		}
		data_pos++;
	}

	return "";
}

/*================================================================ 
* ��������    ReadInt
* ������      [in] (int index_name)��ǰ��������
*             [in] (char *key_name)KEY����
* ��������:   ����ͨ��ʽ��һ����
* ����ֵ��    �ɹ��򷵻���������, ����0
================================================================*/
int CIni::ReadInt(char *index_name, char *key_name)
{
	int ret = 0;
	int data_pos2 = 0;
	int data_pos = FindIndex(index_name);
	if (ERROR_DATA_POS == data_pos)
		return 0;

	data_pos2 = FindData(data_pos, key_name);
	if (ERROR_DATA_POS == data_pos)
		return 0;

	char *str = ReadText(data_pos2);
	ret = atoi(str);
	free(str);

	return ret;
}

/*================================================================ 
* ��������    ReadInt
* ������      [in] (int index_name)��ǰ��������
*             [in] (int lines)ָ������
* ��������:   ��ָ�����ж�һ����
* ����ֵ��    �ɹ��򷵻���������, ����0
================================================================*/
int CIni::ReadInt(char *index_name, int lines)
{
	int data_pos = FindIndex(index_name);

	//����ָ������
	data_pos = GotoNextLine(data_pos);
	for (int i = 0; i < lines; i++)
	{
		if (data_pos < m_data_length)
			data_pos = GotoNextLine(data_pos);
	}

	//������
	while (data_pos < m_data_length)
	{
		if (m_str_data[data_pos] == '=')
		{
			data_pos++;
			char *str = ReadText(data_pos);
			int ret = atoi(str);
			free(str);
			return ret;
		}
		if (m_str_data[data_pos] == '\n')
		{
			return ERROR_DATA;
		}
		data_pos++;
	}

	return ERROR_DATA;
}

/*================================================================ 
* ��������    ReadInt
* ������      [in] (int index_name)��ǰ��������
*             [in] (int lines)ָ������
* ��������:   ��ָ�����ж�һKEY����
* ����ֵ��    �ɹ��򷵻���������, ����0
================================================================*/
char *CIni::ReadCaption(char *index_name, int lines)
{
	int data_pos = FindIndex(index_name);
	if (ERROR_DATA_POS == data_pos)
		return "";

	//����ָ������
	data_pos = GotoNextLine(data_pos);
	for (int i = 0; i < lines; i++)
	{
		if (data_pos < m_data_length) { data_pos = GotoNextLine(data_pos); }		
	}

	return ReadKeyName(data_pos);
}

/*================================================================ 
* ��������    Write
* ������      [in] (char *index_name)��ǰ��������
*             [in] (char *key_name)KEY����
*             [in] (char *value_name)VALUE����
* ��������:   ����ͨ��ʽдһ�ַ�������
* ����ֵ��    �ɹ��򷵻�true, ����false
================================================================*/
bool CIni::Write(char *index_name, char *key_name, char *value_name)
{
	int data_pos = FindIndex(index_name);
	if (data_pos == ERROR_DATA_POS)	//�½�����
	{
		AddIndex(index_name);
		data_pos = FindIndex(index_name);
		data_pos = GotoLastLine(index_name);
		AddData(data_pos, key_name, value_name);	//�ڵ�ǰλ��n��һ������
		return true;
	}

	//��������
	int data_pos2 = FindData(data_pos, key_name);
	if (data_pos2 == ERROR_DATA_POS)		//�½�����
	{
		data_pos = GotoLastLine(index_name);
		AddData(data_pos, key_name, value_name);	//�ڵ�ǰλ��n��һ������
		return true;
	}

	//��������
	ModityData(data_pos, key_name, value_name);	//�޸�һ������

	return true;
}

/*================================================================ 
* ��������    Write
* ������      [in] (char *index_name)��ǰ��������
*             [in] (char *key_name)KEY����
*             [in] (int int_num)����ֵ
* ��������:   ����ͨ��ʽдһ����
* ����ֵ��    �ɹ��򷵻�true, ����false
================================================================*/
bool CIni::Write(char *index_name, char *key_name, int int_num)
{
	char string[32];
	sprintf(string, "%d", int_num);

	int data_pos = FindIndex(index_name);
	if (data_pos == ERROR_DATA_POS)	//�½�����
	{
		AddIndex(index_name);
		data_pos = FindIndex(index_name);
		data_pos = GotoLastLine(index_name);
		AddData(data_pos, key_name, string);	//�ڵ�ǰλ��n��һ������
		return true;
	}

	//��������
	int data_pos2 = FindData(data_pos, key_name);
	if (data_pos2 == ERROR_DATA_POS)		//�½�����
	{
		data_pos = GotoLastLine(index_name);
		AddData(data_pos, key_name, string);	//�ڵ�ǰλ��n��һ������
		return true;
	}

	//��������
	ModityData(data_pos, key_name, string);	//�޸�һ������

	return true;
}

/*================================================================ 
* ��������    GetContinueDataNum
* ������      [in] (char *index_name)��ǰ��������
* ��������:   ��������������
* ����ֵ��    �ɹ��򷵻�����������, ����0
================================================================*/
int CIni::GetContinueDataNum(char *index_name)
{
	int num = 0;
	int data_pos = FindIndex(index_name);
	data_pos = GotoNextLine(data_pos);
	while(1)
	{
		if (m_str_data[data_pos] == '\n'	|| 
			m_str_data[data_pos] == EOF		||
			m_str_data[data_pos] == ' '		|| 
			m_str_data[data_pos] == '/'		||
			m_str_data[data_pos] == '['		||
			m_str_data[data_pos] == '	'	
			)
		{
			return num;
		}
		else
		{
			num++;
			data_pos = GotoNextLine(data_pos);
			if (data_pos >= m_data_length) { return num; }
				
		}
	}
	return num;
}
