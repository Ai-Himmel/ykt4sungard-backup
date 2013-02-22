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
// 通用接口
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
* 函数名：    Open
* 参数：      [in] (char *filename)文件名称
* 功能描述:   打开指定的INI文件
* 返回值：    bool, 成功为true, 错误为false
================================================================*/ 
bool CIni::Open(char *filename)
{
	strcpy(m_str_file_name, filename);

	SAFE_FREE( m_str_data );

	//获取文件长度
	int fh;
	fh = _open( filename, _O_RDONLY );
	if (fh == ERROR_FILE_LENGTH)
	{
		m_data_length = -1;
	}
	m_data_length = _filelength(fh);
	_close(fh);
	
	//文件存在
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

		fread(m_str_data, m_data_length, 1, fp);		//读数据

		fclose(fp);

		//初始化索引
		InitIndex();
		return true;
	}
	else	// 文件不存在
	{
		// 找不到文件
		m_data_length=1;
		m_str_data = new char[m_data_length];
		memset(m_str_data, 0, 1);
		InitIndex();
	}

	return false;
}

/*================================================================ 
* 函数名：    Close
* 参数：      [in] ()
* 功能描述:   关闭指定的INI文件
* 返回值：    void
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
* 函数名：    Save
* 参数：      [in] (char *filename)文件名称
* 功能描述:   保存文件
* 返回值：    bool, 成功为true, 错误为false
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
* 函数名：    GetData
* 参数：      [in] ()
* 功能描述:   返回文件内容
* 返回值：    文件字符串文本
================================================================*/
char *CIni::GetData()
{
	return m_str_data;
}

/*================================================================ 
* 函数名：    GetLines
* 参数：      [in] (int file_cur)文件位置
* 功能描述:   获取文件从当前文件指针位置开始的行数
* 返回值：    文件行数(char *)
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
// 内部函数
////////////////////////////////////////////////

/*================================================================ 
* 函数名：    InitIndex
* 参数：      [in] ()
* 功能描述:   初始化INI文件索引
* 返回值：    void
================================================================*/
void CIni::InitIndex()
{
	m_index_num = 0;

	for (int i = 0; i < m_data_length; i++)
	{
		//找到
		if (m_str_data[i] == '[' && (m_str_data[i - 1] == '\n' || i == 0))
		{
			m_index_num++;
		}
	}

	//申请内存
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
* 函数名：    FindIndex
* 参数：      [in] (char *string)文件索引名称
* 功能描述:   返回指定标题位置
* 返回值：    成功则返回文件索引的当前位置, 否则返回-10
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
* 函数名：    FindData
* 参数：      [in] (int index)文件索引的当前位置
*             [in] (char *string)文件KEY的名称
* 功能描述:   返回指定数据的位置
* 返回值：    成功则返回指定数据的当前位置, 否则返回-10
================================================================*/
int CIni::FindData(int index, char *string)
{
	int data_pos = index;	//指针

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
* 函数名：    GotoNextLine
* 参数：      [in] (int file_pos)文件当前位置
* 功能描述:   返回当前位置到下一行开头数据的文件位置的长度
* 返回值：    成功则返回当前文件位置到下一行开始位置的长度, 
*             否则返回当前位置到文件结尾之间的长度
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
* 函数名：    ReadKeyName
* 参数：      [in] (int &data_pos)文件的当前位置
* 功能描述:   在指定位置读一KEY名称
* 返回值：    成功则返回KEY名称, 否则返回空
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

		//结束
		if (chr == '\n')
		{
			data_pos = i + 1;
			return key_name;
		}
		
		//结束
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
* 函数名：    ReadText
* 参数：      [in] (int file_pos)文件的当前位置
* 功能描述:   在指定位置读一NAME字符串
* 返回值：    成功则返回NAME字符串, 否则返回空
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

		//结束
		if (chr == ';' || chr == ' ' || chr == ']' || chr == '\n' || chr == '\r') { return value_name; }

		value_name[i] = chr;
		index_start++;
	}

	return value_name;
}


/*================================================================ 
* 函数名：    AddIndex
* 参数：      [in] (char *index_name)索引名称
* 功能描述:   加入一个索引
* 返回值：    成功则返回true, 否则返false
================================================================*/
bool CIni::AddIndex(char *index_name)
{
	char str[256] = "";
	int n = FindIndex(index_name);

	if (n == ERROR_DATA_POS)	//新建索引
	{
		sprintf(str,"[%s]", index_name);
		m_str_data = (char *)realloc(m_str_data, m_data_length + strlen(str));	//重新分配内存
		sprintf(&m_str_data[m_data_length], "%s", str);
		m_data_length += strlen(str);
		InitIndex();
		return true;
	}
	
	return false;	//已经存在
}

/*================================================================ 
* 函数名：    AddData
* 参数：      [in] (int pos)当前文件位置
*		      [in] (char *key_name)KEY名称
*             [in] (char *value_name)VALUE名称
* 功能描述:   在当前位置加入一个数据
* 返回值：    成功则返回true, 否则返false
================================================================*/
bool CIni::AddData(int pos, char *key_name, char *value_name)
{
	char *str = NULL;
	int len = strlen(value_name);
	str = new char[len + 256];
	memset(str, 0, len + 256);
	sprintf(str,"%s=%s", key_name, value_name);
	len = strlen(str);

	pos = GotoNextLine(pos);	//提行
	m_str_data = (char *)realloc(m_str_data, m_data_length + len);	//重新分配内存

	char *temp = new char[m_data_length - pos];
	memcpy(temp, &m_str_data[pos], m_data_length - pos);
	memcpy(&m_str_data[pos + len], temp, m_data_length - pos);	//把后面的搬到末尾
	memcpy(&m_str_data[pos], str, len);
	m_data_length += len;

	SAFE_DELETE(temp);
	SAFE_DELETE(str);
	return true;
}

/*================================================================ 
* 函数名：    ModityData
* 参数：      [in] (int file_pos)当前文件位置
*		      [in] (char *key_name)KEY名称
*             [in] (char *value_name)VALUE名称
* 功能描述:   在当前位置修改一个数据的值
* 返回值：    成功则返回true, 否则返false
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

	m_str_data = (char *)realloc(m_str_data, m_data_length + newlen - oldlen);	// 重新分配内存

	char *temp = new char[m_data_length - file_pos];
	memcpy(temp, &m_str_data[file_pos], m_data_length - file_pos);
	memcpy(&m_str_data[data_pos + newlen], temp, m_data_length - file_pos);		// 把后面的搬到末尾
	memcpy(&m_str_data[data_pos], value_name, newlen);
	m_data_length += newlen - oldlen;
	
	m_file_step = (newlen - oldlen);											// 增加下一个索引位置
//	m_file_pos = file_pos;														// 修改后的文件位置		

	SAFE_DELETE(temp);

	while (index < m_index_num)														// 修改后的所有数据索引位置移动 
	{ 
		if (m_index_list[index] >= file_pos) { m_index_list[index] += m_file_step; }

		index++;
	}		

	return true;
}

/*================================================================ 
* 函数名：    GotoLastLine
* 参数：      [in] (int index_name)当前索引名称
* 功能描述:   把指针移动到本INDEX的最后一行
* 返回值：    成功则返回true, 否则返false
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
// 对外接口
/////////////////////////////////////////////////////////////////////

/*================================================================ 
* 函数名：    ReadText
* 参数：      [in] (char *index_name)当前索引名称
*             [in] (char *key_name)KEY名称
* 功能描述:   以普通方式读一字符串数据
* 返回值：    成功则返回文本数据, 否则返空
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
* 函数名：    ReadText
* 参数：      [in] (int index_name)当前索引名称
*             [in] (int lines)指定的行
* 功能描述:   在指定的行读一字符串
* 返回值：    成功则返回文本数据, 否则返空
================================================================*/
char *CIni::ReadText(char *index_name, int lines)
{
	int data_pos = FindIndex(index_name);

	if (ERROR_DATA_POS == data_pos)
		return "";

	// 跳到指定行数
	data_pos = GotoNextLine(data_pos);
	for (int i = 0; i < lines; i++)
	{
		if (data_pos < m_data_length)
			data_pos = GotoNextLine(data_pos);
	}

	// 读数据
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
* 函数名：    ReadInt
* 参数：      [in] (int index_name)当前索引名称
*             [in] (char *key_name)KEY名称
* 功能描述:   以普通方式读一整数
* 返回值：    成功则返回整形数据, 否则返0
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
* 函数名：    ReadInt
* 参数：      [in] (int index_name)当前索引名称
*             [in] (int lines)指定的行
* 功能描述:   在指定的行读一整数
* 返回值：    成功则返回整形数据, 否则返0
================================================================*/
int CIni::ReadInt(char *index_name, int lines)
{
	int data_pos = FindIndex(index_name);

	//跳到指定行数
	data_pos = GotoNextLine(data_pos);
	for (int i = 0; i < lines; i++)
	{
		if (data_pos < m_data_length)
			data_pos = GotoNextLine(data_pos);
	}

	//读数据
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
* 函数名：    ReadInt
* 参数：      [in] (int index_name)当前索引名称
*             [in] (int lines)指定的行
* 功能描述:   在指定的行读一KEY名称
* 返回值：    成功则返回整形数据, 否则返0
================================================================*/
char *CIni::ReadCaption(char *index_name, int lines)
{
	int data_pos = FindIndex(index_name);
	if (ERROR_DATA_POS == data_pos)
		return "";

	//跳到指定行数
	data_pos = GotoNextLine(data_pos);
	for (int i = 0; i < lines; i++)
	{
		if (data_pos < m_data_length) { data_pos = GotoNextLine(data_pos); }		
	}

	return ReadKeyName(data_pos);
}

/*================================================================ 
* 函数名：    Write
* 参数：      [in] (char *index_name)当前索引名称
*             [in] (char *key_name)KEY名称
*             [in] (char *value_name)VALUE名称
* 功能描述:   以普通方式写一字符串数据
* 返回值：    成功则返回true, 否则返false
================================================================*/
bool CIni::Write(char *index_name, char *key_name, char *value_name)
{
	int data_pos = FindIndex(index_name);
	if (data_pos == ERROR_DATA_POS)	//新建索引
	{
		AddIndex(index_name);
		data_pos = FindIndex(index_name);
		data_pos = GotoLastLine(index_name);
		AddData(data_pos, key_name, value_name);	//在当前位置n加一个数据
		return true;
	}

	//存在索引
	int data_pos2 = FindData(data_pos, key_name);
	if (data_pos2 == ERROR_DATA_POS)		//新建数据
	{
		data_pos = GotoLastLine(index_name);
		AddData(data_pos, key_name, value_name);	//在当前位置n加一个数据
		return true;
	}

	//存在数据
	ModityData(data_pos, key_name, value_name);	//修改一个数据

	return true;
}

/*================================================================ 
* 函数名：    Write
* 参数：      [in] (char *index_name)当前索引名称
*             [in] (char *key_name)KEY名称
*             [in] (int int_num)整型值
* 功能描述:   以普通方式写一整数
* 返回值：    成功则返回true, 否则返false
================================================================*/
bool CIni::Write(char *index_name, char *key_name, int int_num)
{
	char string[32];
	sprintf(string, "%d", int_num);

	int data_pos = FindIndex(index_name);
	if (data_pos == ERROR_DATA_POS)	//新建索引
	{
		AddIndex(index_name);
		data_pos = FindIndex(index_name);
		data_pos = GotoLastLine(index_name);
		AddData(data_pos, key_name, string);	//在当前位置n加一个数据
		return true;
	}

	//存在索引
	int data_pos2 = FindData(data_pos, key_name);
	if (data_pos2 == ERROR_DATA_POS)		//新建数据
	{
		data_pos = GotoLastLine(index_name);
		AddData(data_pos, key_name, string);	//在当前位置n加一个数据
		return true;
	}

	//存在数据
	ModityData(data_pos, key_name, string);	//修改一个数据

	return true;
}

/*================================================================ 
* 函数名：    GetContinueDataNum
* 参数：      [in] (char *index_name)当前索引名称
* 功能描述:   返回连续的行数
* 返回值：    成功则返回连续的行数, 否则返0
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
