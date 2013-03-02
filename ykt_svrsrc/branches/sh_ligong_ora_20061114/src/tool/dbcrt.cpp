//*******************************************************************
//                  esql代码自动生成器 v3.0
//
//              SHANGHAI FUDAN KINGSTAR COMPUTER CO. LTD
//                      Department Of Infomation
//
// FileName					:dbcrt_v3.c
// ModelNumber				:UnIndexed
// ModelName				:esql代码自动生成器 v3.0
// Revision History			:孔令国				Remark
// ChangeHistory			:
// ---------------------------------------------------------
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 数据库字段结构,包括字段名,字段类型,字段长度
typedef struct
{
	char fieldname[50];
	char type[100];
	char length[10];
}fieldnode;

// 操作类型,包括操作类型,和由操作名和各个参数组成的字段列表,以end结束
typedef struct
{
	char actionname[40];
	char field[10][100];
	int  actiontype;
}action;
typedef int boolean;
#define TRUE  1;
#define FALSE 0;

/*********************************************
操作字典
#define MODENAME						0
#define READ_BY							1
#define READ_OR_BY						2
#define UPDATE_BY						3
#define DEL_BY							4
#define READ_LOCK_BY					5
#define UPDATE_LOCK_BY					6
#define FREE_LOCK_BY					7
#define OPEN_SELECT_BY					8
#define FETCH_SELECT_BY					9
#define CLOSE_SELECT_BY					10
#define ADD								11
#define OPEN_SELECT_BETWEEN				12
#define OPEN_SELECT_FOR_UPDATE_BY		13
#define READ_BLUR_BY					14
#define INSERT							15
#define UPDATE_GEN_BY					16
#define UPDATE_GEN_LOCK_BY				17
*********************************************/

// 最多支持100个字段的表结构
#define MAXFIELDNUM			100

fieldnode VarList[MAXFIELDNUM];
int nodeIdx =0;
action ActList[255];
int actIdx = 0;
int i =0;

// 格式化后的标准配置文件
FILE *tempFile;
// 配置文件扩展名为act
FILE *iniFile;

// 生成的h返回结构定义文件
FILE *headFile;

// 生成的sqc函数文件
FILE *funcList;

char tablename[50];
char filename[54];
char output_filename[128];
char ffilename[54];
char modename[50];
char tabelnameforcur[10];
char bigtabelname[52];
char *tabelnametemp;

int format();
int read_ini();
int gen_head();
int gen_code();
char *trim(char*);
char *trim2(char*);

void gen_modename(void);
void gen_add(void);
void gen_read_by(void);
void gen_read_or_by(void);
void gen_update_by(void);
void gen_del_by(void);
void gen_del_all();
void gen_read_lock_by(void);
void gen_update_lock_by(void);
void gen_free_lock_by(void);
void gen_open_select_by(void);
void gen_open_with_hold_select_by(void);
void gen_fetch_select_by(void);
void gen_close_select_by(void);
void gen_open_select_between(void);
void gen_open_select_for_update_by(void);
void gen_read_blur_by(void);
void gen_insert(void);
void gen_update_gen_by(void);
void gen_update_gen_lock_by(void);
void gen_fields_name(void);
//void gen_debug_printf(void);

// 函数trim()
// 编程:闻剑 2004-08-10 09:23:09
// 描述:去除字符串尾特殊符号
// 参数:待处理字符串
// 返回:处理后字符串
char *trim(char *str)
{
    char *p1=str;
    char *p2=str+strlen(str)-1;
    if(str==NULL)
		return NULL;
    while((*p2==' ')||(*p2=='\t')||(*p2=='\n'))//||*p2=='\r')
    {
        *p2=0;
        p2--;
    }
    strcpy(str,p1);
    return str;
}

// 函数trim2()
// 编程:闻剑 2004-08-10 09:23:09
// 描述:去除字符串首尾特殊符号
// 参数:待处理字符串
// 返回:处理后字符串
char *trim2(char *str)
{
    char *p1=str;
    char *p2=str+strlen(str)-1;
    if(str==NULL)
		return NULL;
    while(*p1==' '||*p1=='\t'||*p1=='\n'||*p1=='\r')
        p1++;
    while((*p2==' ')||(*p2=='\t')||(*p2=='\n')||(*p2=='\r'))
    {
        *p2=0;
        p2--;
    }
    strcpy(str,p1);
    return str;
}
/*
int get_tableinfo(tbList *tblist)
{
	int bRet = 0;
	int row = 0;
	int i = 0;
	EXEC SQL BEGIN DECLARE SECTION;
		char tb_name1[129]="";
		char tb_creator1[129]="";
		char ho_col_name1[129]="";
		char ho_col_type1[10]="";
		char ho_col_remarks1[255]="";
		char ho_col_nulls[2]="";
		sqlint16 ho_keyseq=0;
		sqlint16  ho_col_length1=0;
		sqlint16  indicator1=0;
	EXEC SQL END DECLARE SECTION;

	SQLCODE = 0;
	toupper_word(tblist->sTbCreator);
	toupper_word(tblist->sTbName);
	strcpy(tb_name1,tblist->sTbName);
	strcpy(tb_creator1,tblist->sTbCreator);
	strcpy(tblist->sLowShortTbName,tblist->sTbName+6);
	tolower_word(tblist->sLowShortTbName);
	EXEC SQL DECLARE column_cur1 CURSOR FOR
	SELECT name,coltype,length,remarks,nulls,keyseq
 	FROM sysibm.syscolumns
	WHERE tbcreator=:tb_creator1 and tbname=:tb_name1 order by colno;
	bRet = SQLCODE;
	if (bRet)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		goto ERR;
	}

	EXEC SQL OPEN column_cur1;
	bRet = SQLCODE;
	if (bRet)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		goto ERR;
	}
	while(0==SQLCODE)
	{
		memset(ho_col_name1,0,sizeof(ho_col_name1));
		memset(ho_col_type1,0,sizeof(ho_col_type1));
		memset(ho_col_remarks1,0,sizeof(ho_col_remarks1));
		memset(ho_col_nulls,0,sizeof(ho_col_nulls));
		ho_col_length1=0;
		ho_keyseq=0;

		EXEC SQL FETCH column_cur1 INTO
		:ho_col_name1:indicator1,
		:ho_col_type1:indicator1,
		:ho_col_length1:indicator1 ,
		:ho_col_remarks1:indicator1,
		:ho_col_nulls:indicator1,
		:ho_keyseq:indicator1;
		bRet = SQLCODE;
		if (bRet)
		{
			db_chk_err(__FILE__,__LINE__,&sqlca);
			EXEC SQL CLOSE column_cur1;
			if(100==bRet)
			{
			   if(row)
				break;
			   else
			   {
			      syslog(LOG_ERR,"fetch no data");
			      printf("fetch no data");
			   }
			}
			else
				goto ERR;
		}
		//printf("%s,%s,%d,%s\n",ho_col_name,ho_col_type,ho_col_length,ho_col_remarks);
		if(MAX_COL==row)
		{
			printf("table column number beyond MAX COLUMNS");
			goto ERR;
		}
		trim(ho_col_name1);
		tolower_word(ho_col_name1);
		trim(ho_col_type1);
		trim(ho_col_remarks1);
		strcpy(tblist->arrlist[row].sColName,ho_col_name1);
		strcpy(tblist->arrlist[row].sColType,ho_col_type1);
		tblist->arrlist[row].iColLength=ho_col_length1;
		strcpy(tblist->arrlist[row].sColRemarks,ho_col_remarks1);
		strcpy(tblist->arrlist[row].sIsNull,ho_col_nulls);
		tblist->arrlist[row].iIsKey=ho_keyseq;
		// trans type db2_type to c type
		for(i=BIGINT;i<=VARCHAR;i++)
		{
		   if(strcmp(db_type[i],ho_col_type1)==0)
		   {
			      tblist->arrlist[row].iDbType=i;
			      break;
		   }
		}
		if(i>VARCHAR)
		{
		      printf("db_type[%s]ho_col_type[%s]i[%d]row[%d]ho_col_name[%s]\n",db_type[i],ho_col_type1,i,row,ho_col_name1);
			goto ERR;
		}
		row++;
	}
	return 0;
ERR:
	EXEC SQL CLOSE column_cur1;
	return -1;
}

int gen_struct_file(FILE *fp,tbList *tblist)
{
	int i=0;
	int end=0;
	char tmp[256]="";
	fprintf(fp, "#ifndef  __T_%s_H_\n",tblist->sTbName);
	fprintf(fp, "#define  __T_%s_H_\n",tblist->sTbName);
	fprintf(fp, "typedef struct \n");
	fprintf(fp, "{\n");
	for(i=0;i<MAX_COL;i++)
	{
		if((tblist->arrlist[i].iInFlag+tblist->arrlist[i].iOutFlag)==0)
			continue;

		switch(tblist->arrlist[i].iDbType)
		{
		case BIGINT:
			sprintf(tmp,"%s;",tblist->arrlist[i].sColName);
			fprintf(fp,"\t\tlong    \t%-30s\t//%-s\n",tmp,tblist->arrlist[i].sColRemarks);
			break;
		case BLOB:
//			fprintf(fp,"\t\tSQL TYPE IS BLOB(%d+1) %s=\"\";\t//%-s\n",tblist->arrlist[i].iColLength,tblist->arrlist[i].sColName,tblist->arrlist[i].sColRemarks);
			break;
		case CHAR:
			sprintf(tmp,"%s[%d+1];",tblist->arrlist[i].sColName,tblist->arrlist[i].iColLength);
			fprintf(fp,"\t\tchar    \t%-30s\t//%-s\n",tmp,tblist->arrlist[i].sColRemarks);
			break;
		case CLOB:
			//fprintf(fp,"\t\tSQL TYPE IS CLOB(%d+1) %s=\"\";\t//%-s\n",tblist->arrlist[i].iColLength,tblist->arrlist[i].sColName,tblist->arrlist[i].sColRemarks);
			break;
		case DATE:
			sprintf(tmp,"%s[11];",tblist->arrlist[i].sColName);
			fprintf(fp,"\t\tchar    \t%-30s\t//%-s\n",tmp,tblist->arrlist[i].sColRemarks);
			break;
		case DECIMAL:
		case DOUBLE:
			sprintf(tmp,"%s;",tblist->arrlist[i].sColName);
			fprintf(fp,"\t\tdouble  \t%-30s\t//%-s\n",tmp,tblist->arrlist[i].sColRemarks);
			break;
		case INTEGER:
			sprintf(tmp,"%s;",tblist->arrlist[i].sColName);
			fprintf(fp,"\t\tint     \t%-30s\t//%-s\n",tmp,tblist->arrlist[i].sColRemarks);
			break;
		case LONGVAR:
			sprintf(tmp,"%s[%d+1];",tblist->arrlist[i].sColName,tblist->arrlist[i].iColLength);
			fprintf(fp,"\t\tchar    \t%-30s\t//%-s\n",tmp,tblist->arrlist[i].sColRemarks);
			break;
		case SMALLINT:
			sprintf(tmp,"%s",tblist->arrlist[i].sColName);
       		fprintf(fp,"\t\tshort   \t%-30s\t//%-s\n",tmp,tblist->arrlist[i].sColRemarks);
			break;
		case TIME:
			sprintf(tmp,"%s[16];",tblist->arrlist[i].sColName);
			fprintf(fp,"\t\tchar    \t%-30s\t//%-s\n",tmp,tblist->arrlist[i].sColRemarks);
			break;
		case TIMESTMP:
			sprintf(tmp,"%s[27];",tblist->arrlist[i].sColName);
			fprintf(fp,"\t\tchar    \t%-30s\t//%-s\n",tmp,tblist->arrlist[i].sColRemarks);
			break;
		case VARCHAR:
			sprintf(tmp,"%s[%d+1] ;",tblist->arrlist[i].sColName,tblist->arrlist[i].iColLength);
			fprintf(fp,"\t\tchar    \t%-30s\t//%-s\n",tmp,tblist->arrlist[i].sColRemarks);
			break;
		default:
			//printf("col[%d]type[%d]\n",i,tblist->arrlist[i].iDbType);
			end=1;
			break;
		}
		if(end)
		   break;
	}
 	fprintf(fp "}T_%s;\n",tblist->sTbName);
	return 0;
}
*/
// 函数format()
// 编程:孔令国 2004-08-09 17:23:09
// 描述:格式化输入,去处无用字符
// 参数:空
// 返回:0表示成功,其它表示失败
int format()
{
	int current;
	int history;
	int flag = 0;
	int flag2 = 1;
	char afilename[54] = "";
	sprintf(afilename,"%s.act",filename);
	if((iniFile = fopen(afilename,"r")) == NULL)
	{
		printf("%s\n","Error when opening act script.");
		return 1;
	}
	sprintf(ffilename,"temp.act");
	if((tempFile = fopen(ffilename,"w")) == NULL)
	{
		printf("%s","Error when writing temptory act script.");
		return 1;
	}
	current = getc(iniFile);
	history = current;
	if (current == ' ' || current == '\t')
		while(current == ' ' || current == '\t')
			current= getc(iniFile);
		history = current;
		if (history!=' ' && history != '\t')
		{
			putc(current,tempFile);
		}
		while(current != EOF)
		{
			current = getc(iniFile);
			if (history == '(')
				flag = 1;
			if (current == ',')
				flag2 = -1;
			if (current == '\n')
				flag2 = flag2*(-1);
			if ((current == '\n') && (flag2 == -1)) flag=0;
			if (flag == 1)
			{
				if ((history == '\n') && (current != ' ') && (current != '\t'))
				{
					putc(' ',tempFile);
				}
			}
			if (current != ' ' && current != '\t')
				putc(current,tempFile);
			else
			{
				if (flag == 0)
					if (history != ' '&& history != '\t' && history != '\n')
						putc(' ',tempFile);
					else
					{
					}
					else
						if (flag == 1)
							if (history != ' '&& history != '\t')
								putc(' ',tempFile);
			}
			history = current;
		}
		fclose(tempFile);
		return 0;
}

// 函数read_ini()
// 编程:孔令国 2004-08-05 8:45:09
// 描述:读取配置文件中的表结构,生成相应的字段结构表,读取相应的操作语句,生成相应的操作表
// 参数:空
// 返回:0表示成功,其它表示失败

int read_ini()
{
	char buf[1024];
	// 当前状态标识:是否在读字段表
	boolean  readVar = FALSE;
	// 当前状态标识:是否在读操作表
	boolean  readAct = FALSE;
	// 读取字段时标识,当前读到的是否是类型
	int isType = -1;
	int fieldIdx = 0;
	int init = 1;
	int flag_readtbname = 0;
	sprintf(ffilename,"temp.act");
	if((iniFile = fopen(ffilename,"r")) == NULL)
	{
		printf("%s","Error when opening act script.");
		return 1;
	}
	while(1)
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),iniFile);
		if (strncmp(buf,"#",1) == 0)
			continue;
		strcpy(buf,trim(buf));
		if (strncmp(buf,"end",3) == 0)
		{
			//if (ActList[actIdx].actionname != NULL) printf("%s",ActList[actIdx].actionname);
			strcpy(ActList[actIdx].actionname,"end");
			return 0;
		}
		char *temp=strstr(buf," ");
		char word[100] = "";
		if (temp != NULL)
		{
			strncpy(word,buf,strlen(buf)-strlen(temp));
			word[strlen(word)] = '\0';
		}
		else
		{
			strncpy(word,buf,strlen(buf));
			word[strlen(word)] = '\0';
		}
		//printf("%s\n",word);
		strcpy(word,trim2(word));
		for (unsigned int lll = 0; lll <= strlen(word); lll++)
		{
			word[lll] = tolower(word[lll]);
		}

		if (strncmp(buf,"#",1) == 0)
			continue;
		if (strncmp(word,"(",1) == 0)
		{
			printf("%s","Starting ESQL Auto generator v3.0 by Lingguo.Kong...\n\n\n");
			printf("%s","Begin analysing table structure...\n\n");
			readVar = TRUE;
		}
		if (strncmp(word,")",1) == 0)
		{
			printf("%s","Finish analysing table structure\n\n");
			readVar = FALSE;
		}
		if (strncmp(word,"begin",5) == 0)
		{
			printf("%s","Begin generating code\n");
			readAct = TRUE;
		}
		memset(word,'\0',sizeof(word));
		while(temp != NULL)
		{
			unsigned int j = 0;
			for (j=0;j <= strlen(buf); j++)
			{
				buf[j] = buf[j+1];
			}
			if (temp != NULL)
				strcpy(buf,temp);
			temp = strstr(buf," ");
			if (temp != NULL)
			{
				memset(word,'\0',sizeof(word));
				strncpy(word,buf,strlen(buf)-strlen(temp));
				word[strlen(buf)-strlen(temp)] = '\0';
			}
			else
			{
				memset(word,'\0',sizeof(word));
				strncpy(word,buf,strlen(buf));
				word[strlen(buf)] = '\0';
			}
			//printf("%s",word);
			for (unsigned int mmm = 0; mmm <= strlen(word); mmm++)
			{
				word[mmm] = tolower(word[mmm]);
			}
			if (strncmp(word,"table",5) == 0)
			{
				flag_readtbname = 1;
				continue;
			}
			if (flag_readtbname == 1)
			{
				strcpy(tablename,word);
				tabelnametemp = strrchr(tablename,'_');
				if (tabelnametemp != NULL)
				{
					tabelnametemp++;
					strncpy(tabelnameforcur,tabelnametemp,sizeof(tabelnameforcur));
				}
				else
				{
					strncpy(tabelnameforcur,tablename,sizeof(tabelnameforcur));
				}
				flag_readtbname = 0;
			}
			// 读字段表
			if (readVar == 1)
			{
				// 注释,跳过
				if (strncmp(word,"#",1) ==0)
				{
					break;
				}
				if (strncmp(word,"constraint",10) == 0)
				{
					break;
				}
				if (strncmp(word,"primary",7) == 0)
				{
					break;
				}
				if (strncmp(word,"not",3) == 0)
				{
					break;
				}
				if (strncmp(word,"null",4) == 0)
				{
					break;
				}
				// field name part
				// 是字段名
				if (isType < 0)
				{
					strcpy(VarList[nodeIdx].fieldname,word);
					VarList[nodeIdx].fieldname[strlen(word)]='\0';
					isType = isType*(-1);
					continue;
				}
				// field type part
				// 是字段类型
				if (isType > 0)
				{
					char dbtype[100];
					char* len;
					strcpy(dbtype,word);
					if (dbtype[strlen(word)-2]==',')
						dbtype[strlen(word)-2]='\0';
					if (dbtype[strlen(word)-1]=='\n')
						dbtype[strlen(word)-1]='\0';
					if ((strncmp(dbtype,"char",4) == 0||strncmp(dbtype,"varchar",7) == 0) && strncmp(dbtype,"character",9) != 0)
					{
						strcpy(VarList[nodeIdx].type,"char");
						len = strstr(dbtype,"char");
						if (len != NULL)
							strcpy(dbtype,len);
						int i = 5;
						int j = 1;
						VarList[nodeIdx].length[0] = '[';
						while((dbtype[i]!=')') && (dbtype[i]!='\0'))
						{
							VarList[nodeIdx].length[j] = dbtype[i];
							j++;
							i++;
						}
						VarList[nodeIdx].length[j] = '+';
						VarList[nodeIdx].length[j+1] = '1';
						VarList[nodeIdx].length[j+2] = ']';
						VarList[nodeIdx].length[j+3] = '\0';
						//printf("%s\n",dbtype);
					}
					else if (strncmp(dbtype,"character",9) == 0)
					{
						strcpy(VarList[nodeIdx].type,"char");
						len = strstr(dbtype,"char");
						if (len != NULL)
							strcpy(dbtype,len);
						int i = 10;
						j = 1;
						VarList[nodeIdx].length[0] = '[';
						while((dbtype[i]!=')') && (dbtype[i]!='\0'))
						{
							VarList[nodeIdx].length[j] = dbtype[i];
							j++;
							i++;
						}
						VarList[nodeIdx].length[j] = '+';
						VarList[nodeIdx].length[j+1] = '1';
						VarList[nodeIdx].length[j+2] = ']';
						VarList[nodeIdx].length[j+3] = '\0';
					}
					else if (strncmp(dbtype,"float",5) ==0)
					{
						strcpy(VarList[nodeIdx].type,"float");
					}
					else if (strncmp(dbtype,"int",3) == 0)
					{
						strcpy(VarList[nodeIdx].type,"sqlint32");
					}
					else if (strncmp(dbtype,"smallint",8) == 0)
					{
						strcpy(VarList[nodeIdx].type,"sqlint16");
					}
					else if (strncmp(dbtype,"bigint",6) == 0)
					{
						strcpy(VarList[nodeIdx].type,"sqlint64");
					}
					else if( (strncmp(dbtype,"num",3) == 0) || (strncmp(dbtype,"dec",3) == 0))
					{
						strcpy(VarList[nodeIdx].type,"double");
					}
					else	if (strncmp(dbtype,"timestamp",9) == 0)
					{
						strcpy(VarList[nodeIdx].type,"char");
						VarList[nodeIdx].length[0] = '[';
						VarList[nodeIdx].length[1] = '2';
						VarList[nodeIdx].length[2] = '7';
						VarList[nodeIdx].length[3] = '+';
						VarList[nodeIdx].length[4] = '1';
						VarList[nodeIdx].length[5] = ']';
						VarList[nodeIdx].length[6] = '\0';
					}
					else if (strncmp(dbtype,"date",4) == 0)
					{
						strcpy(VarList[nodeIdx].type,"char");
						VarList[nodeIdx].length[0] = '[';
						VarList[nodeIdx].length[1] = '1';
						VarList[nodeIdx].length[2] = '1';
						VarList[nodeIdx].length[3] = '+';
						VarList[nodeIdx].length[4] = '1';
						VarList[nodeIdx].length[5] = ']';
						VarList[nodeIdx].length[6] = '\0';
					}
					else	if (strncmp(dbtype,"time",4) == 0)
					{
						strcpy(VarList[nodeIdx].type,"char");
						VarList[nodeIdx].length[0] = '[';
						VarList[nodeIdx].length[1] = '1';
						VarList[nodeIdx].length[2] = '6';
						VarList[nodeIdx].length[3] = '+';
						VarList[nodeIdx].length[4] = '1';
						VarList[nodeIdx].length[5] = ']';
						VarList[nodeIdx].length[6] = '\0';
					}
					else	if (strncmp(dbtype,"double",6) == 0)
					{
						strcpy(VarList[nodeIdx].type,"double");
					}
					else
					{
						printf("Error! Unknown type!");
						exit(1);
					}
					isType = isType*(-1);
					nodeIdx = nodeIdx+1;

					continue;
				}
			}

			// 读操作表
			if (readAct == 1)
			{
				//printf("%s\n",word);
				if (strncmp(word,"#",1) ==0)
				{
					break;
				}
				if (init == 1)
				{

					strcpy(ActList[actIdx].actionname,word);
					if (strncmp(word,"modename",8) == 0)
					{
						ActList[actIdx].actiontype = 0;
					}
					else if (strncmp(word,"read_by",7) == 0)
					{
						ActList[actIdx].actiontype = 1;
					}
					else if (strncmp(word,"read_or_by",10) == 0)
					{
						ActList[actIdx].actiontype = 2;
					}
					else if (strncmp(word,"update_by",9) == 0)
					{
						ActList[actIdx].actiontype = 3;
					}
					else if (strncmp(word,"del_by",6) == 0)
					{
						ActList[actIdx].actiontype = 4;
					}
					else if (strncmp(word,"read_lock_by",12) == 0)
					{
						ActList[actIdx].actiontype = 5;
					}
					else if (strncmp(word,"update_lock_by",14) == 0)
					{
						ActList[actIdx].actiontype = 6;
					}
					else if (strncmp(word,"free_lock",9) == 0)
					{
						ActList[actIdx].actiontype = 7;
					}
					else if (strncmp(word,"open_select_by",14) == 0)
					{
						ActList[actIdx].actiontype = 8;
					}
					else if (strncmp(word,"fetch_select_by",15) == 0)
					{
						ActList[actIdx].actiontype = 9;
					}
					else if (strncmp(word,"close_select_by",15) == 0)
					{
						ActList[actIdx].actiontype = 10;
					}
					else if (strncmp(word,"add",3) == 0)
					{
						ActList[actIdx].actiontype = 11;
					}
					else if (strncmp(word,"open_select_between",19) == 0)
					{
						ActList[actIdx].actiontype = 12;
					}
					else if (strncmp(word,"open_select_for_update_by",25) == 0)
					{
						ActList[actIdx].actiontype = 13;
					}
					else if (strncmp(word,"read_blur_by",12) == 0)
					{
						ActList[actIdx].actiontype = 14;
					}
					else if (strncmp(word,"insert",6) == 0)
					{
						ActList[actIdx].actiontype = 15;
					}
					else if (strncmp(word,"update_gen_by",13) == 0)
					{
						ActList[actIdx].actiontype = 16;
					}
					else if (strncmp(word,"update_gen_lock_by",18) == 0)
					{
						ActList[actIdx].actiontype = 17;
					}
					else if (strncmp(word,"del_all",7) == 0)
					{
						ActList[actIdx].actiontype = 18;
					}
					else if (strncmp(word,"open_with_hold_select_by",24) == 0)
					{
						ActList[actIdx].actiontype = 19;
					}
					else if (strncmp(word,"end",3) == 0)
						break;
					/*else
					{
						printf("Unsupported action:%s!\n",ActList[i].actionname);
						exit(1);
					}*/
					init++;
				}
				if (init == 2)
				{
					strcpy(ActList[actIdx].field[fieldIdx],word);
					fieldIdx++;
				}
				if (strncmp(word,"end",3) == 0)
				{
					init=1;
					actIdx++;
					fieldIdx = 0;
				}
				continue;
			}
			memset(word,'\0',sizeof(word));
		}
	}
	return 0;
}

// 函数gen_head()
// 编程:孔令国 2004-08-06 14:26:09
// 描述:生成返回结构定义头文件
// 参数:空
// 返回:0表示成功,其它表示失败

int gen_head()
{
	char hfilename[54] = "";
	int j = 0;
	sprintf(hfilename,"%s_stru.h",filename);
	if((headFile = fopen(hfilename,"w")) == NULL)
	{
		printf("%s","Error when generating header file.");
		return 1;
	}
	fprintf(headFile, "#ifndef  __T_%s_H_\n",filename);
	fprintf(headFile, "#define  __T_%s_H_\n",filename);
	fprintf(headFile, "typedef struct \n");
	fprintf(headFile, "{\n");
	for (j = 0;j < nodeIdx; j++)
	{
		if ( strncmp(VarList[j].type,"char",4) == 0)
		{
			fprintf(headFile, "\t\t%s\t%s%s;\n",VarList[j].type,VarList[j].fieldname,VarList[j].length);
		}
		else
			if ( strncmp(VarList[j].type,"sqlint",6) == 0)
			{
				fprintf(headFile, "\t\tint\t%s;\n",VarList[j].fieldname);
			}
			else
				fprintf(headFile, "\t\t%s\t%s%s;\n",VarList[j].type,VarList[j].fieldname,VarList[j].length);
	}
	fprintf(headFile, "}T_%s;\n",tablename);

	return 0;
}

void gen_modename(void)
{
	strcpy(modename,ActList[i].field[1]);
	i++;
}

void gen_add(void)
{
	int j = 0;

	fprintf(funcList, "int DB_%s_%s",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s",tablename,ActList[i].actionname);
	fprintf(funcList, "(");
	fprintf(headFile, "(");
	fprintf(funcList, "T_%s *p%s)",tablename,tablename);
	fprintf(headFile, "T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	for (j = 0;j < nodeIdx; j++)
	{
		if ( strncmp(VarList[j].type,"char",4) == 0)
		{
			fprintf(funcList, "\t\t%s\t%s_%d%s=\"\";\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
		}
		else
			fprintf(funcList, "\t\t%s\t%s_%d%s=0;\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
	}
	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");
	for (int q = 0;q < nodeIdx; q++)
	{
		if (strncmp(VarList[q].type,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(%s_%d,p%s->%s,sizeof(%s_%d)-1);\n",VarList[q].fieldname,i,tablename,VarList[q].fieldname,VarList[q].fieldname,i);
			fprintf(funcList, "\tdb_trim(%s_%d);\n",VarList[q].fieldname,i);
		}
		else
			fprintf(funcList, "\t%s_%d=p%s->%s;\n",VarList[q].fieldname,i,tablename,VarList[q].fieldname);
	}
	fprintf(funcList,"\n\tEXEC SQL INSERT INTO %s.%s\n",modename,tablename);
	//wen jian add
	fprintf(funcList,"\t(");
	/*
	for (j = 0;j < nodeIdx; j++)
	{
		fprintf(funcList, "%s,",VarList[j].fieldname);
	}
	fseek(funcList,-1L,SEEK_CUR);
	*/
	gen_fields_name();
	fprintf(funcList,")\n");
	//wen jian add end
	fprintf(funcList,"\tVALUES(\n");
	for (j = 0;j < nodeIdx; j++)
	{
		if (j <nodeIdx-1)
			fprintf(funcList, "\t\t:%s_%d,\n",VarList[j].fieldname,i);
		else
			fprintf(funcList, "\t\t:%s_%d\n",VarList[j].fieldname,i);
	}
	fprintf(funcList, "\t)");
	fprintf(funcList, ";\n");
	fprintf(funcList, "\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}

void gen_read_by(void)
{
	int iIdx = 0;
	int j = 0;
	char vartypeToTrans[100] = "";
	int anIdx = 1;

	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);

	iIdx = 1;
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
		{
			fprintf(funcList, "_and_");
			fprintf(headFile, "_and_");
		}
		iIdx++;
	}
	iIdx = 1;
	fprintf(funcList, "(");
	fprintf(headFile, "(");
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		char vartype[100] = "";
		for (int iloop = 0; iloop <= nodeIdx; iloop++)
		{
			if (strcmp(VarList[iloop].fieldname,ActList[i].field[iIdx]) == 0)
			{
				strcpy(vartype,VarList[iloop].type);
				break;
			}
		}
		trim2(vartype);
		if(strncmp(vartype,"sqlint",6) == 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "int v_%s,",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s,",ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "int v_%s",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s",ActList[i].field[iIdx]);
			}
		}
		else
		{
			if (strncmp(vartype,"char",4) != 0)
			{
				if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
				{
					fprintf(funcList, "%s v_%s,",vartype,ActList[i].field[iIdx]);
					fprintf(headFile, "%s v_%s,",vartype,ActList[i].field[iIdx]);
				}
				else
				{

					fprintf(funcList, "%s v_%s",vartype,ActList[i].field[iIdx]);
					fprintf(headFile, "%s v_%s",vartype,ActList[i].field[iIdx]);
				}
			}
			else
			{
				if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
				{
					fprintf(headFile, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
					fprintf(funcList, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
				}
				else
				{
					fprintf(headFile, "%s *v_%s",vartype,ActList[i].field[iIdx]);
					fprintf(funcList, "%s *v_%s",vartype,ActList[i].field[iIdx]);
				}
			}
		}
		iIdx++;
	}

	fprintf(funcList, ",T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ",T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	for (j = 0;j < nodeIdx; j++)
	{
		if ( strncmp(VarList[j].type,"char",4) == 0)
		{
			fprintf(funcList, "\t\t%s\t%s_%d%s=\"\";\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
		}
		else
			fprintf(funcList, "\t\t%s\t%s_%d%s=0;\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
	}
	fprintf(funcList, "\t\tsqlint16 indicator_%d;\n",i);
	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");

	while(strncmp(ActList[i].field[anIdx],"end",3) != 0)
	{
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx]) == 0)
			{
				strcpy(vartypeToTrans,VarList[iloop1].type);
				break;
			}
		}
		if ( strncmp(vartypeToTrans,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(%s_%d,v_%s,sizeof(%s_%d)-1);\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx],ActList[i].field[anIdx],i);
			fprintf(funcList, "\tdb_trim(%s_%d);\n",ActList[i].field[anIdx],i);
		}
		else
		{
			fprintf(funcList, "\t%s_%d=v_%s;\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx]);
		}
		anIdx++;
	}
	/*
	fprintf(funcList,"\n\tEXEC SQL SELECT * INTO\n");
	*/
	//wen jian add
	fprintf(funcList,"\n\tEXEC SQL SELECT\n");
	/*
	for (j = 0;j < nodeIdx; j++)
	{
			fprintf(funcList, "\t\t%s,\n",VarList[j].fieldname);
	}
	fseek(funcList,-2L,SEEK_CUR);
	*/
	gen_fields_name();
	fprintf(funcList,"\n\tINTO \n");
	//wenjian add end
	for (j = 0;j < nodeIdx; j++)
	{
		if (j <nodeIdx-1)
			fprintf(funcList, "\t\t:%s_%d:%s_%d,\n",VarList[j].fieldname,i,"indicator",i);
		else
			fprintf(funcList, "\t\t:%s_%d:%s_%d\n",VarList[j].fieldname,i,"indicator",i);
	}
	fprintf(funcList, "\tFROM %s.%s\n",modename,tablename);
	fprintf(funcList, "\tWHERE\n");
	int fieldindex = 1;
	while(strncmp(ActList[i].field[fieldindex],"end",3) != 0)
	{
		fprintf(funcList, "\t\t%s = :%s_%d",ActList[i].field[fieldindex],ActList[i].field[fieldindex],i);
		if (strncmp(ActList[i].field[fieldindex+1],"end",3) != 0)
			fprintf(funcList,"\tand");
		fieldindex++;
	}
	fprintf(funcList,";\n");
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	for (int k = 0;k < nodeIdx; k++)
	{
		if (strncmp(VarList[k].type,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(p%s->%s,%s_%d,sizeof(p%s->%s)-1);\n",tablename,VarList[k].fieldname,VarList[k].fieldname,i,tablename,VarList[k].fieldname);
			fprintf(funcList, "\tdb_trim(p%s->%s);\n",tablename,VarList[k].fieldname);
		}
		else
			fprintf(funcList, "\tp%s->%s=%s_%d;\n",tablename,VarList[k].fieldname,VarList[k].fieldname,i);
	}
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}
void gen_del_by(void)
{
	int iIdx = 0;
//	int j = 0;
	char vartypeToTrans[100] = "";
	int anIdx = 1;

	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);

	iIdx = 1;
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
		{
			fprintf(funcList, "_and_");
			fprintf(headFile, "_and_");
		}
		iIdx++;
	}
	iIdx = 1;
	fprintf(funcList, "(");
	fprintf(headFile, "(");
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		char vartype[100] = "";
		for (int iloop = 0; iloop <= nodeIdx; iloop++)
		{
			if (strcmp(VarList[iloop].fieldname,ActList[i].field[iIdx]) == 0)
			{
				strcpy(vartype,VarList[iloop].type);
				break;
			}
		}
		trim2(vartype);
		if(strncmp(vartype,"sqlint",6) == 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "int v_%s,",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s,",ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "int v_%s",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s",ActList[i].field[iIdx]);
			}
		}
		else
		{
			if (strncmp(vartype,"char",4) != 0)
			{
				if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
				{
					fprintf(funcList, "%s v_%s,",vartype,ActList[i].field[iIdx]);
					fprintf(headFile, "%s v_%s,",vartype,ActList[i].field[iIdx]);
				}
				else
				{

					fprintf(funcList, "%s v_%s",vartype,ActList[i].field[iIdx]);
					fprintf(headFile, "%s v_%s",vartype,ActList[i].field[iIdx]);
				}
			}
			else
			{
				if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
				{
					fprintf(headFile, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
					fprintf(funcList, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
				}
				else
				{
					fprintf(headFile, "%s *v_%s",vartype,ActList[i].field[iIdx]);
					fprintf(funcList, "%s *v_%s",vartype,ActList[i].field[iIdx]);
				}
			}
		}
		iIdx++;
	}
	fprintf(funcList, ")");
	fprintf(headFile, ")");
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
/*
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	for (j = 0;j < nodeIdx; j++)
	{
		if ( strncmp(VarList[j].type,"char",4) == 0)
		{
			fprintf(funcList, "\t\t%s\t%s_%d%s=\"\";\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
		}
		else
			fprintf(funcList, "\t\t%s\t%s_%d%s=0;\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
	}
	fprintf(funcList, "\t\tsqlint16 indicator_%d;\n",i);
	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
*/
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	char vartypeToTrans2[100] = "";
	char lengthtoTrans2[100] = "";
	char name2[100] = "";
	int	 anIdx2 = 1;
	while(strncmp(ActList[i].field[anIdx2],"end",3) != 0)
	{
		// 查对应类型
		for (int iloop2 = 0; iloop2 <= nodeIdx; iloop2++)
		{
			if (strcmp(VarList[iloop2].fieldname,ActList[i].field[anIdx2]) == 0)
			{
				strcpy(vartypeToTrans2,VarList[iloop2].type);
				strcpy(lengthtoTrans2,VarList[iloop2].length);
				strcpy(name2,VarList[iloop2].fieldname);
				break;
			}
		}
		if ( strncmp(vartypeToTrans2,"char",4) == 0)
		{
			fprintf(funcList, "\tchar %s_%d%s = \"\";\n",name2,i,lengthtoTrans2);
		}
		else
		{
			fprintf(funcList, "\t%s %s_%d = 0;\n",vartypeToTrans2,name2,i);
		}
		anIdx2++;
	}
	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");

	fprintf(funcList, "\n\tSQLCODE = 0;\n");

	while(strncmp(ActList[i].field[anIdx],"end",3) != 0)
	{
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx]) == 0)
			{
				strcpy(vartypeToTrans,VarList[iloop1].type);
				break;
			}
		}
		if ( strncmp(vartypeToTrans,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(%s_%d,v_%s,sizeof(%s_%d)-1);\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx],ActList[i].field[anIdx],i);
			fprintf(funcList, "\tdb_trim(%s_%d);\n",ActList[i].field[anIdx],i);
		}
		else
		{
			fprintf(funcList, "\t%s_%d=v_%s;\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx]);
		}
		anIdx++;
	}
/*
	for (j = 0;j < nodeIdx; j++)
	{
		if (j <nodeIdx-1)
			fprintf(funcList, "\t\t:%s_%d:%s_%d,\n",VarList[j].fieldname,i,"indicator",i);
		else
			fprintf(funcList, "\t\t:%s_%d:%s_%d\n",VarList[j].fieldname,i,"indicator",i);
	}
*/
	fprintf(funcList, "\tEXEC SQL DELETE FROM %s.%s\n",modename,tablename);
	fprintf(funcList, "\tWHERE\n");
	int fieldindex = 1;
	while(strncmp(ActList[i].field[fieldindex],"end",3) != 0)
	{
		fprintf(funcList, "\t\t%s = :%s_%d",ActList[i].field[fieldindex],ActList[i].field[fieldindex],i);
		if (strncmp(ActList[i].field[fieldindex+1],"end",3) != 0)
			fprintf(funcList,"\tand");
		fieldindex++;
	}
	fprintf(funcList,";\n");
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}

void gen_read_or_by()
{
	int iIdx = 0;
	int j = 0;
	char vartypeToTrans[100] = "";
	int anIdx;
	int u = 1;
	anIdx = 1;

	fprintf(funcList, "int DB_%s_read_by_",tablename);
	fprintf(headFile, "int DB_%s_read_by_",tablename);

	iIdx = 1;
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
		{
			fprintf(funcList, "_or_");
			fprintf(headFile, "_or_");
		}
		iIdx++;
	}
	iIdx = 1;
	fprintf(funcList, "(");
	fprintf(headFile, "(");
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		char vartype[100] = "";
		for (int iloop = 0; iloop <= nodeIdx; iloop++)
		{
			if (strcmp(VarList[iloop].fieldname,ActList[i].field[iIdx]) == 0)
			{
				strcpy(vartype,VarList[iloop].type);
				break;
			}
		}
		trim2(vartype);
		if(strncmp(vartype,"sqlint",6) == 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "int v_%s,",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s,",ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "int v_%s",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s",ActList[i].field[iIdx]);
			}
		}
		else
		{
			if (strncmp(vartype,"char",4) != 0)
			{
				if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
				{
					fprintf(funcList, "%s v_%s,",vartype,ActList[i].field[iIdx]);
					fprintf(headFile, "%s v_%s,",vartype,ActList[i].field[iIdx]);
				}
				else
				{

					fprintf(funcList, "%s v_%s",vartype,ActList[i].field[iIdx]);
					fprintf(headFile, "%s v_%s",vartype,ActList[i].field[iIdx]);
				}
			}
			else
			{
				if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
				{
					fprintf(headFile, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
					fprintf(funcList, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
				}
				else
				{
					fprintf(headFile, "%s *v_%s",vartype,ActList[i].field[iIdx]);
					fprintf(funcList, "%s *v_%s",vartype,ActList[i].field[iIdx]);
				}
			}
		}
		iIdx++;
	}

	fprintf(funcList, ",T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ",T_%s *p%s)",tablename,tablename);
	fprintf(funcList, ")");
	fprintf(headFile, ")");
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	for (j = 0;j < nodeIdx; j++)
	{
		if ( strncmp(VarList[j].type,"char",4) == 0)
		{
			fprintf(funcList, "\t\t%s\t%s_%d%s=\"\";\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
		}
		else
			fprintf(funcList, "\t\t%s\t%s_%d%s=0;\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
	}
	fprintf(funcList, "\t\tsqlint16 indicator_%d;\n",i);
	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");

	while(strncmp(ActList[i].field[anIdx],"end",3) != 0)
	{
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx]) == 0)
			{
				strcpy(vartypeToTrans,VarList[iloop1].type);
				break;
			}
		}
		if ( strncmp(vartypeToTrans,"char",4) == 0)
		{
			if (strncmp(ActList[i].actionname,"open_select_between",19) != 0)
			{
				fprintf(funcList, "\tstrncpy(%s_%d,v_%s,sizeof(%s_%d)-1);\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx],ActList[i].field[anIdx],i);
				fprintf(funcList, "\tdb_trim(%s_%d);\n",ActList[i].field[anIdx],i);
			}
			else
			{
				fprintf(funcList, "\tstrncpy(%s_%d_%d,v_%s_%d,sizeof(%s_%d_%d)-1);\n",ActList[i].field[anIdx],i,u,ActList[i].field[anIdx],anIdx,ActList[i].field[anIdx],i,u);
				fprintf(funcList, "\tdb_trim(%s_%d_%d);\n",ActList[i].field[anIdx],i,u);
				u++;
			}
		}
		else
		{
			fprintf(funcList, "\t%s_%d=v_%s;\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx]);
		}
		anIdx++;
	}

	/*
	fprintf(funcList,"\n\tEXEC SQL SELECT * INTO\n");
	*/
	//wen jian add
	fprintf(funcList,"\n\tEXEC SQL SELECT\n");
	/*
	for (j = 0;j < nodeIdx; j++)
	{
			fprintf(funcList, "\t\t%s,\n",VarList[j].fieldname);
	}
	fseek(funcList,-2L,SEEK_CUR);
	*/
	gen_fields_name();
	fprintf(funcList,"\n\tINTO \n");
	//wenjian add end
	for (j = 0;j < nodeIdx; j++)
	{
		if (j <nodeIdx-1)
			fprintf(funcList, "\t\t:%s_%d:%s_%d,\n",VarList[j].fieldname,i,"indicator",i);
		else
			fprintf(funcList, "\t\t:%s_%d:%s_%d\n",VarList[j].fieldname,i,"indicator",i);
	}
	fprintf(funcList, "\tFROM %s.%s\n",modename,tablename);
	fprintf(funcList, "\tWHERE\n");
	int fieldindex = 1;
	while(strncmp(ActList[i].field[fieldindex],"end",3) != 0)
	{
		fprintf(funcList, "\t\t%s = :%s_%d",ActList[i].field[fieldindex],ActList[i].field[fieldindex],i);
		if (strncmp(ActList[i].field[fieldindex+1],"end",3) != 0)
			fprintf(funcList,"\tor");
		fieldindex++;
	}
	fprintf(funcList,";\n");
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	for (int k = 0;k < nodeIdx; k++)
	{
		if (strncmp(VarList[k].type,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(p%s->%s,%s_%d,sizeof(p%s->%s)-1);\n",tablename,VarList[k].fieldname,VarList[k].fieldname,i,tablename,VarList[k].fieldname);
			fprintf(funcList, "\tdb_trim(p%s->%s);\n",tablename,VarList[k].fieldname);
		}
		else
			fprintf(funcList, "\tp%s->%s=%s_%d;\n",tablename,VarList[k].fieldname,VarList[k].fieldname,i);
	}
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}
void gen_update_by()
{
	int iIdx = 1;
	char vartypeToTrans1[100] = "";
	char lengthtoTrans[100] = "";
	char name1[100] = "";
	int anIdx1 = 1;
	int j = 0;

	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);

	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
		{
			fprintf(funcList, "_and_");
			fprintf(headFile, "_and_");
		}
		iIdx++;
	}
	iIdx = 1;
	fprintf(funcList, "(");
	fprintf(headFile, "(");
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		char vartype[100] = "";
		for (int iloop = 0; iloop <= nodeIdx; iloop++)
		{
			if (strcmp(VarList[iloop].fieldname,ActList[i].field[iIdx]) == 0)
			{
				strcpy(vartype,VarList[iloop].type);
				break;
			}
		}
		trim2(vartype);
		if(strncmp(vartype,"sqlint",6) == 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "int v_%s,",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s,",ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "int v_%s",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s",ActList[i].field[iIdx]);
			}
		}
		else
		if (strncmp(vartype,"char",4) != 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(funcList, "%s v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s,",vartype,ActList[i].field[iIdx]);
			}
			else
			{

				fprintf(funcList, "%s v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		else
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
			}

			else
			{
				fprintf(headFile, "%s *v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		iIdx++;
	}
	fprintf(funcList, ",T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ",T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");

	for (j = 0;j < nodeIdx; j++)
	{
		if ( strncmp(VarList[j].type,"char",4) == 0)
		{
			fprintf(funcList, "\t\t%s\t%s_%d%s=\"\";\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
		}
		else
			fprintf(funcList, "\t\t%s\t%s_%d%s=0;\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
	}

	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");


	while(strncmp(ActList[i].field[anIdx1],"end",3) != 0)
	{
		// 查对应类型
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx1]) == 0)
			{
				strcpy(vartypeToTrans1,VarList[iloop1].type);
				strcpy(lengthtoTrans,VarList[iloop1].length);
				strcpy(name1,VarList[iloop1].fieldname);
				break;
			}
		}
		if ( strncmp(vartypeToTrans1,"char",4) == 0)
		{
			fprintf(funcList, "\tchar vv_%s%d_%d%s = \"\";\n",name1,anIdx1,i,lengthtoTrans);
		}
		else
		{
			fprintf(funcList, "\t%s vv_%s%d_%d = 0;\n",vartypeToTrans1,name1,anIdx1,i);
		}
		anIdx1++;
	}


	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n\n");

	char vartypeToTrans[100] = "";
	int anIdx = 1;
	while(strncmp(ActList[i].field[anIdx],"end",3) != 0)
	{
		// 查对应类型
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx]) == 0)
			{
				strcpy(vartypeToTrans,VarList[iloop1].type);
				break;
			}
		}
		if ( strncmp(vartypeToTrans,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(vv_%s%d_%d,v_%s,sizeof(vv_%s%d_%d)-1);\n",ActList[i].field[anIdx],anIdx,i,ActList[i].field[anIdx],ActList[i].field[anIdx],anIdx,i);
			fprintf(funcList, "\tdb_trim(vv_%s%d_%d);\n",ActList[i].field[anIdx],anIdx,i);
		}
		else
		{
			fprintf(funcList, "\tvv_%s%d_%d=v_%s;\n",ActList[i].field[anIdx],anIdx,i,ActList[i].field[anIdx]);
		}
		anIdx++;
	}

	for (int q = 0;q < nodeIdx; q++)
	{
		if (strncmp(VarList[q].type,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(%s_%d,p%s->%s,sizeof(%s_%d)-1);\n",VarList[q].fieldname,i,tablename,VarList[q].fieldname,VarList[q].fieldname,i);
			fprintf(funcList, "\tdb_trim(%s_%d);\n",VarList[q].fieldname,i);
		}
		else
			fprintf(funcList, "\t%s_%d=p%s->%s;\n",VarList[q].fieldname,i,tablename,VarList[q].fieldname);
	}
	fprintf(funcList,"\n\tEXEC SQL UPDATE %s.%s SET\n",modename,tablename);

	int fieldindex = 1;
	for (j = 0;j < nodeIdx; j++)
	{
		if(strcasecmp("level",VarList[j].fieldname) == 0)
			fprintf(funcList, "\t\t\"LEVEL\"=:%s_%d",VarList[j].fieldname,i);
		else
			fprintf(funcList, "\t\t%s=:%s_%d",VarList[j].fieldname,VarList[j].fieldname,i);
		if (j <nodeIdx-1)
			fprintf(funcList,",\n");
		else
			fprintf(funcList,"\n");
		/*
		else
		{
			fprintf(funcList, "\t\t%s=:%s_%d\n",VarList[j].fieldname,VarList[j].fieldname,i);
		}
		*/
	}
	fprintf(funcList,"\tWHERE\n");
	while(strncmp(ActList[i].field[fieldindex],"end",3) != 0)
	{
		fprintf(funcList, "\t\t%s = :vv_%s%d_%d",ActList[i].field[fieldindex],ActList[i].field[fieldindex],fieldindex,i);
		if (strncmp(ActList[i].field[fieldindex+1],"end",3) != 0)
			fprintf(funcList,"\tand");
		fieldindex++;
	}
	fprintf(funcList,";\n");
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}
/*
void gen_del_by()
{
	char vartypeToTrans2[100] = "";
	char lengthtoTrans2[100] = "";
	char name2[100] = "";
	int	 anIdx2;
	int  u =1;
	int iIdx = 1;
	char vartypeToTrans[100] = "";
	int anIdx;

	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);

	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
		{
			fprintf(funcList, "_and_");
			fprintf(headFile, "_and_");
		}
		iIdx++;
	}
	iIdx = 1;
	fprintf(funcList, "(");
	fprintf(headFile, "(");

	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		char vartype[100] = "";
		for (int iloop = 0; iloop <= nodeIdx; iloop++)
		{
			if (strcmp(VarList[iloop].fieldname,ActList[i].field[iIdx]) == 0)
			{
				strcpy(vartype,VarList[iloop].type);
				break;
			}
		}
		trim2(vartype);
		if(strncmp(vartype,"sqlint",6) == 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "int v_%s,",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s,",ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "int v_%s",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s",ActList[i].field[iIdx]);
			}
		}
		else if (strncmp(vartype,"char",4) != 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(funcList, "%s v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s,",vartype,ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(funcList, "%s v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		else
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "%s *v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		iIdx++;
	}
	fprintf(funcList, ")");
	fprintf(headFile, ")");
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	anIdx2 = 1;
	while(strncmp(ActList[i].field[anIdx2],"end",3) != 0)
	{
		// 查对应类型
		for (int iloop2 = 0; iloop2 <= nodeIdx; iloop2++)
		{
			if (strcmp(VarList[iloop2].fieldname,ActList[i].field[anIdx2]) == 0)
			{
				strcpy(vartypeToTrans2,VarList[iloop2].type);
				strcpy(lengthtoTrans2,VarList[iloop2].length);
				strcpy(name2,VarList[iloop2].fieldname);
				break;
			}
		}
		if ( strncmp(vartypeToTrans2,"char",4) == 0)
		{
			fprintf(funcList, "\tchar %s_%d%s = \"\";\n",name2,i,lengthtoTrans2);
		}
		else
		{
			fprintf(funcList, "\t%s %s_%d = 0;\n",vartypeToTrans2,name2,i);
		}
		anIdx2++;
	}
	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");

	u = 1;
	anIdx = 1;
	while(strncmp(ActList[i].field[anIdx],"end",3) != 0)
	{
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx]) == 0)
			{
				strcpy(vartypeToTrans,VarList[iloop1].type);
				break;
			}
		}
		if ( strncmp(vartypeToTrans,"char",4) == 0)
		{
			if (strncmp(ActList[i].actionname,"open_select_between",19) != 0)
			{
				fprintf(funcList, "\tstrncpy(%s_%d,v_%s,sizeof(%s_%d)-1);\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx],ActList[i].field[anIdx],i);
				fprintf(funcList, "\tdb_trim(%s_%d);\n",ActList[i].field[anIdx],i);
			}
			else
			{
				fprintf(funcList, "\tstrncpy(%s_%d_%d,v_%s_%d,sizeof(%s_%d_%d)-1);\n",ActList[i].field[anIdx],i,u,ActList[i].field[anIdx],anIdx,ActList[i].field[anIdx],i,u);
				fprintf(funcList, "\tdb_trim(%s_%d_%d);\n",ActList[i].field[anIdx],i,u);
				u++;
			}
		}
		anIdx++;
	}
	fprintf(funcList,"\n\tEXEC SQL DELETE FROM\n");
	fprintf(funcList, "\t%s.%s\n",modename,tablename);
	fprintf(funcList, "\tWHERE\n");
	int fieldindex = 1;
	while(strncmp(ActList[i].field[fieldindex],"end",3) != 0)
	{
		fprintf(funcList, "\t\t%s = :%s_%d",ActList[i].field[fieldindex],ActList[i].field[fieldindex],i);
		if (strncmp(ActList[i].field[fieldindex+1],"end",3) != 0)
			fprintf(funcList,"\tand");
		fieldindex++;
	}
	fprintf(funcList,";\n");
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}
*/
void gen_del_all()
{
	fprintf(funcList, "int DB_%s_%s()\n",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s();\n",tablename,ActList[i].actionname);

	fprintf(funcList, "{\n");
	fprintf(funcList, "\tSQLCODE = 0;\n");
	fprintf(funcList,"\n\tEXEC SQL DELETE FROM %s.%s WHERE 1=1;\n",modename,tablename);
	fprintf(funcList, "\tif (SQLCODE)\n");
	fprintf(funcList, "\t{\n");
	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\treturn(SQLCODE);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}

void gen_read_lock_by(void)
{
	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);

	int iIdx = 1;
	int j = 0;
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
		{
			fprintf(funcList, "_and_");
			fprintf(headFile, "_and_");
		}
		iIdx++;
	}
	iIdx = 2;
	fprintf(funcList, "(");
	fprintf(headFile, "(");
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		char vartype[100] = "";
		for (int iloop = 0; iloop <= nodeIdx; iloop++)
		{
			if (strcmp(VarList[iloop].fieldname,ActList[i].field[iIdx]) == 0)
			{
				strcpy(vartype,VarList[iloop].type);
				break;
			}
		}
		trim2(vartype);
		if(strncmp(vartype,"sqlint",6) == 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "int v_%s,",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s,",ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "int v_%s",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s",ActList[i].field[iIdx]);
			}
		}
		else if (strncmp(vartype,"char",4) != 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(funcList, "%s v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s,",vartype,ActList[i].field[iIdx]);
			}
			else
			{

				fprintf(funcList, "%s v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		else
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s,",vartype,ActList[i].field[iIdx]);

			}
			else
			{
				fprintf(headFile, "%s *v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		iIdx++;
	}
	fprintf(funcList, ",T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ",T_%s *p%s)",tablename,tablename);

	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	for (j = 0;j < nodeIdx; j++)
	{
		if ( strncmp(VarList[j].type,"char",4) == 0)
		{
			fprintf(funcList, "\t\t%s\t%s_%d%s=\"\";\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
		}
		else
			fprintf(funcList, "\t\t%s\t%s_%d%s=0;\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
	}
	fprintf(funcList, "\t\tsqlint16 indicator_%d;\n",i);
	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");

	char vartypeToTrans[100] = "";
	int anIdx;
	int u = 1;
	anIdx = 2;
	while(strncmp(ActList[i].field[anIdx],"end",3) != 0)
	{
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx]) == 0)
			{
				strcpy(vartypeToTrans,VarList[iloop1].type);
				break;
			}
		}
		if ( strncmp(vartypeToTrans,"char",4) == 0)
		{
			if (strncmp(ActList[i].actionname,"open_select_between",19) != 0)
			{
				fprintf(funcList, "\tstrncpy(%s_%d,v_%s,sizeof(%s_%d)-1);\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx],ActList[i].field[anIdx],i);
				fprintf(funcList, "\tdb_trim(%s_%d);\n",ActList[i].field[anIdx],i);
			}
			else
			{
				fprintf(funcList, "\tstrncpy(%s_%d_%d,v_%s_%d,sizeof(%s_%d_%d)-1);\n",ActList[i].field[anIdx],i,u,ActList[i].field[anIdx],anIdx,ActList[i].field[anIdx],i,u);
				fprintf(funcList, "\tdb_trim(%s_%d_%d);\n",ActList[i].field[anIdx],i,u);
				u++;
			}
		}
		else
		{
			fprintf(funcList, "\t%s_%d=v_%s;\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx]);
		}
		anIdx++;
	}
	/*
	fprintf(funcList,"\n\tEXEC SQL DECLARE %s_%s CURSOR FOR SELECT *\n",tabelnameforcur,ActList[i].field[1]);
	*/
	//wen jian add
	fprintf(funcList,"\n\tEXEC SQL DECLARE %s_%s CURSOR FOR SELECT \n",tabelnameforcur,ActList[i].field[1]);
	/*
	for ( j = 0;j < nodeIdx; j++)
	{
			fprintf(funcList, "\t\t%s,\n",VarList[j].fieldname);
	}
	fseek(funcList,-2L,SEEK_CUR);
	*/
	gen_fields_name();
	fprintf(funcList,"\n");
	//wenjian add end

	fprintf(funcList, "\tFROM %s.%s\n",modename,tablename);
	fprintf(funcList, "\tWHERE\n");
	int fieldindex = 2;
	while(strncmp(ActList[i].field[fieldindex],"end",3) != 0)
	{
		fprintf(funcList, "\t\t%s = :%s_%d",ActList[i].field[fieldindex],ActList[i].field[fieldindex],i);
		if (strncmp(ActList[i].field[fieldindex+1],"end",3) != 0)
			fprintf(funcList,"\tand");
		fieldindex++;
	}
	fprintf(funcList,"\n\tFOR UPDATE;\n");
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList,"\n\tEXEC SQL OPEN %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	// end of cursur
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList,"\n\tEXEC SQL FETCH %s_%s INTO\n",tabelnameforcur,ActList[i].field[1]);
	for (j = 0;j < nodeIdx; j++)
	{
		if (j <nodeIdx-1)
			fprintf(funcList, "\t\t:%s_%d:%s_%d,\n",VarList[j].fieldname,i,"indicator",i);
		else
			fprintf(funcList, "\t\t:%s_%d:%s_%d\n",VarList[j].fieldname,i,"indicator",i);
	}
	fprintf(funcList, ";\n");
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	for (int k = 0;k < nodeIdx; k++)
	{
		if (strncmp(VarList[k].type,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(p%s->%s,%s_%d,sizeof(p%s->%s)-1);\n",tablename,VarList[k].fieldname,VarList[k].fieldname,i,tablename,VarList[k].fieldname);
			fprintf(funcList, "\tdb_trim(p%s->%s);\n",tablename,VarList[k].fieldname);
		}
		else
			fprintf(funcList, "\tp%s->%s=%s_%d;\n",tablename,VarList[k].fieldname,VarList[k].fieldname,i);
	}
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}

void gen_update_lock_by(void)
{
	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);
	int iIdx = 1;
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		if ( (strncmp(ActList[i].field[iIdx+1],"end",3) != 0) && (strncmp(ActList[i].actionname,"read_or_by",10) == 0))
		{
			fprintf(funcList, "_or_");
			fprintf(headFile, "_or_");
		}
		else
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(funcList, "_and_");
				fprintf(headFile, "_and_");
			}
			iIdx++;
	}
	iIdx = 2;
	int j = 0;
	fprintf(funcList, "(");
	fprintf(headFile, "(");
	fprintf(funcList, "T_%s *p%s)",tablename,tablename);
	fprintf(headFile, "T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	for (j = 0;j < nodeIdx; j++)
	{
		if ( strncmp(VarList[j].type,"char",4) == 0)
		{
			fprintf(funcList, "\t\t%s\t%s_%d%s=\"\";\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
		}
		else
			fprintf(funcList, "\t\t%s\t%s_%d%s=0;\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
	}

	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");
	for (int q = 0;q < nodeIdx; q++)
	{
		if (strncmp(VarList[q].type,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(%s_%d,p%s->%s,sizeof(%s_%d)-1);\n",VarList[q].fieldname,i,tablename,VarList[q].fieldname,VarList[q].fieldname,i);
			fprintf(funcList, "\tdb_trim(%s_%d);\n",VarList[q].fieldname,i);
		}
		else
			fprintf(funcList, "\t%s_%d=p%s->%s;\n",VarList[q].fieldname,i,tablename,VarList[q].fieldname);
	}

	fprintf(funcList,"\n\tEXEC SQL UPDATE %s.%s SET\n",modename,tablename);
	for (j = 0;j < nodeIdx; j++)
	{
		if(strcasecmp("level",VarList[j].fieldname) == 0)
			fprintf(funcList, "\t\t\"LEVEL\"=:%s_%d",VarList[j].fieldname,i);
		else
			fprintf(funcList, "\t\t%s=:%s_%d",VarList[j].fieldname,VarList[j].fieldname,i);
		if (j <nodeIdx-1)
			fprintf(funcList,",\n");
		else
			fprintf(funcList,"\n");
	}
	/*
	for (j = 0;j < nodeIdx; j++)
	{
		if (j <nodeIdx-1)
			fprintf(funcList, "\t\t%s=:%s_%d,\n",VarList[j].fieldname,VarList[j].fieldname,i);
		else
			fprintf(funcList, "\t\t%s=:%s_%d\n",VarList[j].fieldname,VarList[j].fieldname,i);
	}
	*/
	fprintf(funcList,"\tWHERE\n");

	fprintf(funcList, "\tcurrent of %s_%s;\n\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	/*for (int k = 0;k < nodeIdx; k++)
	{
		if (strncmp(VarList[k].type,"char",4) == 0)
			fprintf(funcList, "\tstrncpy(p%s->%s,%s_%d,sizeof(p%s->%s)-1);\n",tablename,VarList[k].fieldname,VarList[k].fieldname,i,tablename,VarList[k].fieldname);
		else
			fprintf(funcList, "\tp%s->%s=%s_%d;\n",tablename,VarList[k].fieldname,VarList[k].fieldname,i);
	}*/
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}
void gen_free_lock_by(void)
{
	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);

	int iIdx = 1;

	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		iIdx ++;
	}
	iIdx = 2;
	fprintf(funcList, "(");
	fprintf(headFile, "(");
	fprintf(funcList, ")");
	fprintf(headFile, ")");
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");
	fprintf(funcList,"\n\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}
void gen_open_select_by(void)
{
	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);
	int iIdx = 1;

	char vartypeToTrans[100] = "";
	int anIdx = 0;
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
		{
			fprintf(funcList, "_and_");
			fprintf(headFile, "_and_");
		}
		iIdx++;
	}
	iIdx = 2;
	fprintf(funcList, "(");
	fprintf(headFile, "(");

	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		char vartype[100] = "";
		for (int iloop = 0; iloop <= nodeIdx; iloop++)
		{
			if (strcmp(VarList[iloop].fieldname,ActList[i].field[iIdx]) == 0)
			{
				strcpy(vartype,VarList[iloop].type);
				break;
			}
		}
		trim2(vartype);
		if(strncmp(vartype,"sqlint",6) == 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "int v_%s,",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s,",ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "int v_%s",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s",ActList[i].field[iIdx]);
			}
		}
		else if (strncmp(vartype,"char",4) != 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(funcList, "%s v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s,",vartype,ActList[i].field[iIdx]);
			}
			else
			{

				fprintf(funcList, "%s v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		else
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "%s *v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		iIdx++;
	}
	fprintf(funcList, ")");
	fprintf(headFile, ")");
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	char vartypeToTrans2[100] = "";
	char lengthtoTrans2[100] = "";
	char name2[100] = "";
	int	 anIdx2 = 2;
	while(strncmp(ActList[i].field[anIdx2],"end",3) != 0)
	{
		// 查对应类型
		for (int iloop2 = 0; iloop2 <= nodeIdx; iloop2++)
		{
			if (strcmp(VarList[iloop2].fieldname,ActList[i].field[anIdx2]) == 0)
			{
				strcpy(vartypeToTrans2,VarList[iloop2].type);
				strcpy(lengthtoTrans2,VarList[iloop2].length);
				strcpy(name2,VarList[iloop2].fieldname);
				break;
			}
		}
		if ( strncmp(vartypeToTrans2,"char",4) == 0)
		{
			fprintf(funcList, "\tchar %s_%d%s = \"\";\n",name2,i,lengthtoTrans2);
		}
		else
		{
			fprintf(funcList, "\t%s %s_%d = 0;\n",vartypeToTrans2,name2,i);
		}
		anIdx2++;
	}
	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");

	anIdx = 2;
	while(strncmp(ActList[i].field[anIdx],"end",3) != 0)
	{
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx]) == 0)
			{
				strcpy(vartypeToTrans,VarList[iloop1].type);
				break;
			}
		}
		if ( strncmp(vartypeToTrans,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(%s_%d,v_%s,sizeof(%s_%d)-1);\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx],ActList[i].field[anIdx],i);
			fprintf(funcList, "\tdb_trim(%s_%d);\n",ActList[i].field[anIdx],i);
		}
		else
		{
			fprintf(funcList, "\t%s_%d=v_%s;\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx]);
		}
		anIdx++;
	}
	/*
	fprintf(funcList,"\n\tEXEC SQL DECLARE %s_%s CURSOR FOR SELECT *\n",tabelnameforcur,ActList[i].field[1]);
	*/
	//wen jian add
	fprintf(funcList,"\n\tEXEC SQL DECLARE %s_%s CURSOR FOR SELECT \n",tabelnameforcur,ActList[i].field[1]);
	/*
	for (int j = 0;j < nodeIdx; j++)
	{
			fprintf(funcList, "\t\t%s,\n",VarList[j].fieldname);
	}
	fseek(funcList,-2L,SEEK_CUR);
	*/
	gen_fields_name();
	fprintf(funcList,"\n");
	//wenjian add end

	fprintf(funcList, "\tFROM %s.%s\n",modename,tablename);
	if (strncmp(ActList[i].field[2],"end",3) != 0)
		fprintf(funcList, "\tWHERE\n");
	int fieldindex = 2;
	while(strncmp(ActList[i].field[fieldindex],"end",3) != 0)
	{
		fprintf(funcList, "\t\t%s = :%s_%d",ActList[i].field[fieldindex],ActList[i].field[fieldindex],i);
		if (strncmp(ActList[i].field[fieldindex+1],"end",3) != 0)
			fprintf(funcList,"\tand");
		fieldindex++;
	}
//	fprintf(funcList,"\n\tFOR READ ONLY;\n");
	fprintf(funcList,";\n");
//	fprintf(funcList,";\n");
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList,"\n\tEXEC SQL OPEN %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}
void gen_fetch_select_by(void)
{
	int j = 0;
	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);
	int iIdx = 1;
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		iIdx++;
	}
	iIdx = 2;
	fprintf(funcList, "(");
	fprintf(headFile, "(");
	fprintf(funcList, "T_%s *p%s)",tablename,tablename);
	fprintf(headFile, "T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	for (j = 0;j < nodeIdx; j++)
	{
		if ( strncmp(VarList[j].type,"char",4) == 0)
		{
			fprintf(funcList, "\t\t%s\t%s_%d%s=\"\";\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
		}
		else
			fprintf(funcList, "\t\t%s\t%s_%d%s=0;\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
	}
	fprintf(funcList, "\t\tsqlint16 indicator_%d;\n",i);
	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");
	fprintf(funcList,"\n\tEXEC SQL FETCH %s_%s INTO\n",tabelnameforcur,ActList[i].field[1]);
	for (j = 0;j < nodeIdx; j++)
	{
		if (j <nodeIdx-1)
			fprintf(funcList, "\t\t:%s_%d:%s_%d,\n",VarList[j].fieldname,i,"indicator",i);
		else
			fprintf(funcList, "\t\t:%s_%d:%s_%d\n",VarList[j].fieldname,i,"indicator",i);
	}
	fprintf(funcList,";\n");
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	for (int k = 0;k < nodeIdx; k++)
	{
		if (strncmp(VarList[k].type,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(p%s->%s,%s_%d,sizeof(p%s->%s)-1);\n",tablename,VarList[k].fieldname,VarList[k].fieldname,i,tablename,VarList[k].fieldname);
			fprintf(funcList, "\tdb_trim(p%s->%s);\n",tablename,VarList[k].fieldname);
		}
		else
			fprintf(funcList, "\tp%s->%s=%s_%d;\n",tablename,VarList[k].fieldname,VarList[k].fieldname,i);
	}
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}
void gen_close_select_by(void)
{
	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);
	int iIdx = 1;
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		iIdx++;
	}
	iIdx = 2;
	fprintf(funcList, "(");
	fprintf(headFile, "(");
	fprintf(funcList, ")");
	fprintf(headFile, ")");
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");
	fprintf(funcList,"\n\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");



	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}
void gen_open_select_between(void)
{
	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);
	int iIdx = 1;
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
		{
			fprintf(funcList, "_and_");
			fprintf(headFile, "_and_");
		}
		iIdx++;
	}
		iIdx = 2;
	fprintf(funcList, "(");
	fprintf(headFile, "(");

	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		char vartype[100] = "";
		for (int iloop = 0; iloop <= nodeIdx; iloop++)
		{
			if (strcmp(VarList[iloop].fieldname,ActList[i].field[iIdx]) == 0)
			{
				strcpy(vartype,VarList[iloop].type);
				break;
			}
		}
		trim2(vartype);
		if(strncmp(vartype,"sqlint",6) == 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "int v_%s,",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s,",ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "int v_%s",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s",ActList[i].field[iIdx]);
			}
		}
		else
			if (strncmp(vartype,"char",4) != 0)
			{
				if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
				{
					fprintf(funcList, "%s v_%s,",vartype,ActList[i].field[iIdx]);
					fprintf(headFile, "%s v_%s,",vartype,ActList[i].field[iIdx]);
				}
				else
				{
					fprintf(funcList, "%s v_%s",vartype,ActList[i].field[iIdx]);
					fprintf(headFile, "%s v_%s",vartype,ActList[i].field[iIdx]);
				}
			}
			else
			{
				if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
				{
					fprintf(headFile, "%s *v_%s_%d,",vartype,ActList[i].field[iIdx],iIdx);
					fprintf(funcList, "%s *v_%s_%d,",vartype,ActList[i].field[iIdx],iIdx);
				}
				else
				{
					fprintf(headFile, "%s *v_%s_%d",vartype,ActList[i].field[iIdx],iIdx);
					fprintf(funcList, "%s *v_%s_%d",vartype,ActList[i].field[iIdx],iIdx);
				}
			}
		iIdx++;
	}
	fprintf(funcList, ")");
	fprintf(headFile, ")");
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	char vartypeToTrans2[100] = "";
	char lengthtoTrans2[100] = "";
	char name2[100] = "";
	int	 anIdx2;
	int  u =1;
	anIdx2 = 2;
	while(strncmp(ActList[i].field[anIdx2],"end",3) != 0)
	{
		// 查对应类型
		for (int iloop2 = 0; iloop2 <= nodeIdx; iloop2++)
		{
			if (strcmp(VarList[iloop2].fieldname,ActList[i].field[anIdx2]) == 0)
			{
				strcpy(vartypeToTrans2,VarList[iloop2].type);
				strcpy(lengthtoTrans2,VarList[iloop2].length);
				strcpy(name2,VarList[iloop2].fieldname);
				break;
			}
		}
		if ( strncmp(vartypeToTrans2,"char",4) == 0)
		{
			fprintf(funcList, "\tchar %s_%d_%d%s = \"\";\n",name2,i,u,lengthtoTrans2);
			u++;
		}
		else
		{
			fprintf(funcList, "\t%s %s_%d = 0;\n",vartypeToTrans2,name2,i);
		}
		anIdx2++;
	}
	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");
	char vartypeToTrans[100] = "";
	int anIdx;
	u = 1;
	if ((strncmp(ActList[i].actionname,"open_select",11) == 0) || (strncmp(ActList[i].actionname,"read_lock",9) == 0))
		anIdx = 2;
	else
		anIdx = 1;
	while(strncmp(ActList[i].field[anIdx],"end",3) != 0)
	{
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx]) == 0)
			{
				strcpy(vartypeToTrans,VarList[iloop1].type);
				break;
			}
		}
		if ( strncmp(vartypeToTrans,"char",4) == 0)
		{
			if (strncmp(ActList[i].actionname,"open_select_between",19) != 0)
			{
				fprintf(funcList, "\tstrncpy(%s_%d,v_%s,sizeof(%s_%d)-1);\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx],ActList[i].field[anIdx],i);
				fprintf(funcList, "\tdb_trim(%s_%d);\n",ActList[i].field[anIdx],i);
			}
			else
			{
				fprintf(funcList, "\tstrncpy(%s_%d_%d,v_%s_%d,sizeof(%s_%d_%d)-1);\n",ActList[i].field[anIdx],i,u,ActList[i].field[anIdx],anIdx,ActList[i].field[anIdx],i,u);
				fprintf(funcList, "\tdb_trim(%s_%d_%d);\n",ActList[i].field[anIdx],i,u);
				u++;
			}
		}
		else
		{
			fprintf(funcList, "\t%s_%d=v_%s;\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx]);
		}
		anIdx++;
	}
	fprintf(funcList,"\n\tEXEC SQL DECLARE %s_%s CURSOR FOR SELECT *\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\tFROM %s.%s\n",modename,tablename);
	if (strncmp(ActList[i].field[2],"end",3) != 0)
		fprintf(funcList, "\tWHERE\n");
	int fieldindex = 2;
	fprintf(funcList, "\t\t%s > :%s_%d_1",ActList[i].field[fieldindex],ActList[i].field[fieldindex],i);
	fprintf(funcList,"\tand");
	fieldindex++;
	fprintf(funcList, "\t\t%s < :%s_%d_2",ActList[i].field[fieldindex],ActList[i].field[fieldindex],i);
	fprintf(funcList,"\n\tFOR UPDATE;\n");
fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList,"\n\tEXEC SQL OPEN %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");

	i++;
}

void gen_open_select_for_update_by()
{

	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);
	int iIdx = 1;

	char vartypeToTrans[100] = "";
	int anIdx = 0;
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
		{
			fprintf(funcList, "_and_");
			fprintf(headFile, "_and_");
		}
		iIdx++;
	}
	iIdx = 2;
	fprintf(funcList, "(");
	fprintf(headFile, "(");

	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		char vartype[100] = "";
		for (int iloop = 0; iloop <= nodeIdx; iloop++)
		{
			if (strcmp(VarList[iloop].fieldname,ActList[i].field[iIdx]) == 0)
			{
				strcpy(vartype,VarList[iloop].type);
				break;
			}
		}
		trim2(vartype);
		if(strncmp(vartype,"sqlint",6) == 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "int v_%s,",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s,",ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "int v_%s",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s",ActList[i].field[iIdx]);
			}
		}
		else if (strncmp(vartype,"char",4) != 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(funcList, "%s v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s,",vartype,ActList[i].field[iIdx]);
			}
			else
			{

				fprintf(funcList, "%s v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		else
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "%s *v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		iIdx++;
	}
	fprintf(funcList, ")");
	fprintf(headFile, ")");
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	char vartypeToTrans2[100] = "";
	char lengthtoTrans2[100] = "";
	char name2[100] = "";
	int	 anIdx2 = 2;
	while(strncmp(ActList[i].field[anIdx2],"end",3) != 0)
	{
		// 查对应类型
		for (int iloop2 = 0; iloop2 <= nodeIdx; iloop2++)
		{
			if (strcmp(VarList[iloop2].fieldname,ActList[i].field[anIdx2]) == 0)
			{
				strcpy(vartypeToTrans2,VarList[iloop2].type);
				strcpy(lengthtoTrans2,VarList[iloop2].length);
				strcpy(name2,VarList[iloop2].fieldname);
				break;
			}
		}
		if ( strncmp(vartypeToTrans2,"char",4) == 0)
		{
			fprintf(funcList, "\tchar %s_%d%s = \"\";\n",name2,i,lengthtoTrans2);
		}
		else
		{
			fprintf(funcList, "\t%s %s_%d = 0;\n",vartypeToTrans2,name2,i);
		}
		anIdx2++;
	}
	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");

	anIdx = 2;
	while(strncmp(ActList[i].field[anIdx],"end",3) != 0)
	{
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx]) == 0)
			{
				strcpy(vartypeToTrans,VarList[iloop1].type);
				break;
			}
		}
		if ( strncmp(vartypeToTrans,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(%s_%d,v_%s,sizeof(%s_%d)-1);\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx],ActList[i].field[anIdx],i);
			fprintf(funcList, "\tdb_trim(%s_%d);\n",ActList[i].field[anIdx],i);
		}
		else
		{
			fprintf(funcList, "\t%s_%d=v_%s;\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx]);
		}
		anIdx++;
	}
	/*
	fprintf(funcList,"\n\tEXEC SQL DECLARE %s_%s CURSOR FOR SELECT *\n",tabelnameforcur,ActList[i].field[1]);
	*/
	//wen jian add
	fprintf(funcList,"\n\tEXEC SQL DECLARE %s_%s CURSOR FOR SELECT \n",tabelnameforcur,ActList[i].field[1]);
	/*
	for (int j = 0;j < nodeIdx; j++)
	{
			fprintf(funcList, "\t\t%s,\n",VarList[j].fieldname);
	}
	fseek(funcList,-2L,SEEK_CUR);
	*/
	gen_fields_name();
	fprintf(funcList,"\n");
	//wenjian add end
	fprintf(funcList, "\tFROM %s.%s\n",modename,tablename);
	if (strncmp(ActList[i].field[2],"end",3) != 0)
		fprintf(funcList, "\tWHERE\n");
	int fieldindex = 2;
	while(strncmp(ActList[i].field[fieldindex],"end",3) != 0)
	{
		fprintf(funcList, "\t\t%s = :%s_%d",ActList[i].field[fieldindex],ActList[i].field[fieldindex],i);
		if (strncmp(ActList[i].field[fieldindex+1],"end",3) != 0)
			fprintf(funcList,"\tand");
		fieldindex++;
	}
	fprintf(funcList,"\n\tFOR UPDATE;\n");
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");	fprintf(funcList,"\n\tEXEC SQL OPEN %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}
void gen_open_with_hold_select_by(void)
{
	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);
	int iIdx = 1;

	char vartypeToTrans[100] = "";
	int anIdx = 0;
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
		{
			fprintf(funcList, "_and_");
			fprintf(headFile, "_and_");
		}
		iIdx++;
	}
	iIdx = 2;
	fprintf(funcList, "(");
	fprintf(headFile, "(");

	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		char vartype[100] = "";
		for (int iloop = 0; iloop <= nodeIdx; iloop++)
		{
			if (strcmp(VarList[iloop].fieldname,ActList[i].field[iIdx]) == 0)
			{
				strcpy(vartype,VarList[iloop].type);
				break;
			}
		}
		trim2(vartype);
		if(strncmp(vartype,"sqlint",6) == 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "int v_%s,",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s,",ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "int v_%s",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s",ActList[i].field[iIdx]);
			}
		}
		else if (strncmp(vartype,"char",4) != 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(funcList, "%s v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s,",vartype,ActList[i].field[iIdx]);
			}
			else
			{

				fprintf(funcList, "%s v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		else
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "%s *v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		iIdx++;
	}
	fprintf(funcList, ")");
	fprintf(headFile, ")");
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	char vartypeToTrans2[100] = "";
	char lengthtoTrans2[100] = "";
	char name2[100] = "";
	int	 anIdx2 = 2;
	while(strncmp(ActList[i].field[anIdx2],"end",3) != 0)
	{
		// 查对应类型
		for (int iloop2 = 0; iloop2 <= nodeIdx; iloop2++)
		{
			if (strcmp(VarList[iloop2].fieldname,ActList[i].field[anIdx2]) == 0)
			{
				strcpy(vartypeToTrans2,VarList[iloop2].type);
				strcpy(lengthtoTrans2,VarList[iloop2].length);
				strcpy(name2,VarList[iloop2].fieldname);
				break;
			}
		}
		if ( strncmp(vartypeToTrans2,"char",4) == 0)
		{
			fprintf(funcList, "\tchar %s_%d%s = \"\";\n",name2,i,lengthtoTrans2);
		}
		else
		{
			fprintf(funcList, "\t%s %s_%d = 0;\n",vartypeToTrans2,name2,i);
		}
		anIdx2++;
	}
	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");

	anIdx = 2;
	while(strncmp(ActList[i].field[anIdx],"end",3) != 0)
	{
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx]) == 0)
			{
				strcpy(vartypeToTrans,VarList[iloop1].type);
				break;
			}
		}
		if ( strncmp(vartypeToTrans,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(%s_%d,v_%s,sizeof(%s_%d)-1);\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx],ActList[i].field[anIdx],i);
			fprintf(funcList, "\tdb_trim(%s_%d);\n",ActList[i].field[anIdx],i);
		}
		else
		{
			fprintf(funcList, "\t%s_%d=v_%s;\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx]);
		}
		anIdx++;
	}
	/*
	fprintf(funcList,"\n\tEXEC SQL DECLARE %s_%s CURSOR FOR SELECT *\n",tabelnameforcur,ActList[i].field[1]);
	*/
	//wen jian add
	fprintf(funcList,"\n\tEXEC SQL DECLARE %s_%s CURSOR WITH HOLD  FOR SELECT \n",tabelnameforcur,ActList[i].field[1]);
	/*
	for (int j = 0;j < nodeIdx; j++)
	{
			fprintf(funcList, "\t\t%s,\n",VarList[j].fieldname);
	}
	fseek(funcList,-2L,SEEK_CUR);
	*/
	gen_fields_name();
	fprintf(funcList,"\n");
	//wenjian add end

	fprintf(funcList, "\tFROM %s.%s\n",modename,tablename);
	if (strncmp(ActList[i].field[2],"end",3) != 0)
		fprintf(funcList, "\tWHERE\n");
	int fieldindex = 2;
	while(strncmp(ActList[i].field[fieldindex],"end",3) != 0)
	{
		fprintf(funcList, "\t\t%s = :%s_%d",ActList[i].field[fieldindex],ActList[i].field[fieldindex],i);
		if (strncmp(ActList[i].field[fieldindex+1],"end",3) != 0)
			fprintf(funcList,"\tand");
		fieldindex++;
	}
//	fprintf(funcList,"\n\tFOR READ ONLY;\n");
	fprintf(funcList,";\n");
//	fprintf(funcList,";\n");
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList,"\n\tEXEC SQL OPEN %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}


void gen_read_blur_by()
{
	int iIdx = 1;
	char vartypeToTrans1[100] = "";
	char lengthtoTrans[100] = "";
	char name1[100] = "";
	int anIdx1 = 1;
	int j = 0;

	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);

	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
		{
			fprintf(funcList, "_and_");
			fprintf(headFile, "_and_");
		}
		iIdx++;
	}
	iIdx = 1;
	fprintf(funcList, "(");
	fprintf(headFile, "(");
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		char vartype[100] = "";
		for (int iloop = 0; iloop <= nodeIdx; iloop++)
		{
			if (strcmp(VarList[iloop].fieldname,ActList[i].field[iIdx]) == 0)
			{
				strcpy(vartype,VarList[iloop].type);
				break;
			}
		}
		trim2(vartype);
		if(strncmp(vartype,"sqlint",6) == 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "int v_%s,",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s,",ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "int v_%s",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s",ActList[i].field[iIdx]);
			}
		}
		else
		if (strncmp(vartype,"char",4) != 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(funcList, "%s v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s,",vartype,ActList[i].field[iIdx]);
			}
			else
			{

				fprintf(funcList, "%s v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		else
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
			}

			else
			{
				fprintf(headFile, "%s *v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		iIdx++;
	}
	fprintf(funcList, ",T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ",T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");

	for (j = 0;j < nodeIdx; j++)
	{
		if ( strncmp(VarList[j].type,"char",4) == 0)
		{
			fprintf(funcList, "\t\t%s\t%s_%d%s=\"\";\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
		}
		else
			fprintf(funcList, "\t\t%s\t%s_%d%s=0;\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
	}

	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");


	while(strncmp(ActList[i].field[anIdx1],"end",3) != 0)
	{
		// 查对应类型
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx1]) == 0)
			{
				strcpy(vartypeToTrans1,VarList[iloop1].type);
				strcpy(lengthtoTrans,VarList[iloop1].length);
				strcpy(name1,VarList[iloop1].fieldname);
				break;
			}
		}
		if ( strncmp(vartypeToTrans1,"char",4) == 0)
		{
			fprintf(funcList, "\tchar vv_%s%d_%d%s = \"%%\";\n",name1,anIdx1,i,lengthtoTrans);
		}
		else
		{
			fprintf(funcList, "\t%s vv_%s%d_%d = 0;\n",vartypeToTrans1,name1,anIdx1,i);
		}
		anIdx1++;
	}


	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n\n");
	int anIdx = 1;
	char vartypeToTrans[20] = "";
	while(strncmp(ActList[i].field[anIdx],"end",3) != 0)
	{
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx]) == 0)
			{
				strcpy(vartypeToTrans,VarList[iloop1].type);
				break;
			}
		}
		if ( strncmp(vartypeToTrans,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(%s_%d,v_%s,sizeof(%s_%d)-1);\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx],ActList[i].field[anIdx],i);
			fprintf(funcList, "\tstrcat(vv_%s_%d,%s_%d);\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx],i);
			fprintf(funcList, "\tstrcat(vv_%s_%d,\"%%\");\n",ActList[i].field[anIdx],i);
		}
		else
		{
			fprintf(funcList, "\tvv_%s_%d=v_%s;\n",ActList[i].field[anIdx],i,ActList[i].field[anIdx]);
		}
		anIdx++;
	}
	fprintf(funcList,"\n\tEXEC SQL SELECT * INTO\n");
	for (j = 0;j < nodeIdx; j++)
	{
		if (j <nodeIdx-1)
			fprintf(funcList, "\t\t:%s_%d:%s_%d,\n",VarList[j].fieldname,i,"indicator",i);
		else
			fprintf(funcList, "\t\t:%s_%d:%s_%d\n",VarList[j].fieldname,i,"indicator",i);
	}
	fprintf(funcList, "\tFROM %s.%s\n",modename,tablename);
	fprintf(funcList, "\tWHERE\n");
	int fieldindex = 1;
	anIdx = 1;
	while(strncmp(ActList[i].field[fieldindex],"end",3) != 0)
	{
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx]) == 0)
			{
				strcpy(vartypeToTrans,VarList[iloop1].type);
				//printf("%s",VarList[iloop1].type);
				break;
			}
		}
		//printf("%s\n",ActList[i].field[fieldindex]);
		//printf("%s\n",vartypeToTrans);
		if ( strncmp(vartypeToTrans,"char",4) == 0)
		{
			fprintf(funcList, "\t\t:%s_%d = \'\' or %s like :vv_%s_%d",ActList[i].field[fieldindex],i,ActList[i].field[fieldindex],ActList[i].field[fieldindex],i);
		}
		else
		{
			fprintf(funcList, "\t\t:%s_%d = 0 or %s = :vv_%s_%d",ActList[i].field[fieldindex],i,ActList[i].field[fieldindex],ActList[i].field[fieldindex],i);
		}
		if (strncmp(ActList[i].field[fieldindex+1],"end",3) != 0)
			fprintf(funcList,"\tand");
		anIdx++;
		fieldindex++;
	}
	fprintf(funcList,";\n");
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	for (int k = 0;k < nodeIdx; k++)
	{
		if (strncmp(VarList[k].type,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(p%s->%s,%s_%d,sizeof(p%s->%s)-1);\n",tablename,VarList[k].fieldname,VarList[k].fieldname,i,tablename,VarList[k].fieldname);
			fprintf(funcList, "\tstrncpy(p%s->%s);\n",tablename,VarList[k].fieldname);
	}
		else
			fprintf(funcList, "\tp%s->%s=%s_%d;\n",tablename,VarList[k].fieldname,VarList[k].fieldname,i);
	}
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}

void gen_insert()
{
	int j = 0;

	fprintf(funcList, "int DB_%s_%s",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s",tablename,ActList[i].actionname);
	fprintf(funcList, "(");
	fprintf(headFile, "(");
	fprintf(funcList, "T_%s *p%s)",tablename,tablename);
	fprintf(headFile, "T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	for (j = 1;j < nodeIdx; j++)
	{
		if ( strncmp(VarList[j].type,"char",4) == 0)
		{
			fprintf(funcList, "\t\t%s\t%s_%d%s=\"\";\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
		}
		else
			fprintf(funcList, "\t\t%s\t%s_%d%s=0;\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
	}
	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");
	for (int q = 1;q < nodeIdx; q++)
	{
		if (strncmp(VarList[q].type,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(%s_%d,p%s->%s,sizeof(%s_%d)-1);\n",VarList[q].fieldname,i,tablename,VarList[q].fieldname,VarList[q].fieldname,i);
			fprintf(funcList, "\tdb_trim(%s_%d);\n",VarList[q].fieldname,i);
		}
		else
			fprintf(funcList, "\t%s_%d=p%s->%s;\n",VarList[q].fieldname,i,tablename,VarList[q].fieldname);
	}
	fprintf(funcList,"\n\tEXEC SQL INSERT INTO %s.%s\n",modename,tablename);
	fprintf(funcList,"\t(");
	/*
	for (j = 1;j <nodeIdx-1; j++)
	{
		fprintf(funcList, "%s,",VarList[j].fieldname);
	}
	fprintf(funcList, "%s",VarList[j].fieldname);
	*/
	gen_fields_name();
	fprintf(funcList, ")\n");
	fprintf(funcList,"\tVALUES(\n");
	for (j = 1;j < nodeIdx; j++)
	{
		if (j <nodeIdx-1)
			fprintf(funcList, "\t\t:%s_%d,\n",VarList[j].fieldname,i);
		else
			fprintf(funcList, "\t\t:%s_%d\n",VarList[j].fieldname,i);
	}
	fprintf(funcList, "\t)");
	fprintf(funcList, ";\n");
	fprintf(funcList, "\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}

void gen_update_gen_by()
{
	int iIdx = 1;
	char vartypeToTrans1[100] = "";
	char lengthtoTrans[100] = "";
	char name1[100] = "";
	int anIdx1 = 1;
	int j = 0;

	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);

	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
		{
			fprintf(funcList, "_and_");
			fprintf(headFile, "_and_");
		}
		iIdx++;
	}
	iIdx = 1;
	fprintf(funcList, "(");
	fprintf(headFile, "(");
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		char vartype[100] = "";
		for (int iloop = 0; iloop <= nodeIdx; iloop++)
		{
			if (strcmp(VarList[iloop].fieldname,ActList[i].field[iIdx]) == 0)
			{
				strcpy(vartype,VarList[iloop].type);
				break;
			}
		}
		trim2(vartype);
		if(strncmp(vartype,"sqlint",6) == 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "int v_%s,",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s,",ActList[i].field[iIdx]);
			}
			else
			{
				fprintf(headFile, "int v_%s",ActList[i].field[iIdx]);
				fprintf(funcList, "int v_%s",ActList[i].field[iIdx]);
			}
		}
		else
		if (strncmp(vartype,"char",4) != 0)
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(funcList, "%s v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s,",vartype,ActList[i].field[iIdx]);
			}
			else
			{

				fprintf(funcList, "%s v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(headFile, "%s v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		else
		{
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(headFile, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s,",vartype,ActList[i].field[iIdx]);
			}

			else
			{
				fprintf(headFile, "%s *v_%s",vartype,ActList[i].field[iIdx]);
				fprintf(funcList, "%s *v_%s",vartype,ActList[i].field[iIdx]);
			}
		}
		iIdx++;
	}
	fprintf(funcList, ",T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ",T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");

	for (j = 1;j < nodeIdx; j++)
	{
		if ( strncmp(VarList[j].type,"char",4) == 0)
		{
			fprintf(funcList, "\t\t%s\t%s_%d%s=\"\";\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
		}
		else
			fprintf(funcList, "\t\t%s\t%s_%d%s=0;\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
	}

	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");


	while(strncmp(ActList[i].field[anIdx1],"end",3) != 0)
	{
		// 查对应类型
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx1]) == 0)
			{
				strcpy(vartypeToTrans1,VarList[iloop1].type);
				strcpy(lengthtoTrans,VarList[iloop1].length);
				strcpy(name1,VarList[iloop1].fieldname);
				break;
			}
		}
		if ( strncmp(vartypeToTrans1,"char",4) == 0)
		{
			fprintf(funcList, "\tchar vv_%s%d_%d%s = \"\";\n",name1,anIdx1,i,lengthtoTrans);
		}
		else
		{
			fprintf(funcList, "\t%s vv_%s%d_%d = 0;\n",vartypeToTrans1,name1,anIdx1,i);
		}
		anIdx1++;
	}


	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n\n");

	char vartypeToTrans[100] = "";
	int anIdx = 1;
	while(strncmp(ActList[i].field[anIdx],"end",3) != 0)
	{
		// 查对应类型
		for (int iloop1 = 0; iloop1 <= nodeIdx; iloop1++)
		{
			if (strcmp(VarList[iloop1].fieldname,ActList[i].field[anIdx]) == 0)
			{
				strcpy(vartypeToTrans,VarList[iloop1].type);
				break;
			}
		}
		if ( strncmp(vartypeToTrans,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(vv_%s%d_%d,v_%s,sizeof(vv_%s%d_%d)-1);\n",ActList[i].field[anIdx],anIdx,i,ActList[i].field[anIdx],ActList[i].field[anIdx],anIdx,i);
			fprintf(funcList, "\tdb_trim(vv_%s%d_%d);\n",ActList[i].field[anIdx],anIdx,i);
		}
		else
		{
			fprintf(funcList, "\tvv_%s%d_%d=v_%s;\n",ActList[i].field[anIdx],anIdx,i,ActList[i].field[anIdx]);
		}
		anIdx++;
	}

	for (int q = 1;q < nodeIdx; q++)
	{
		if (strncmp(VarList[q].type,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(%s_%d,p%s->%s,sizeof(%s_%d)-1);\n",VarList[q].fieldname,i,tablename,VarList[q].fieldname,VarList[q].fieldname,i);
			fprintf(funcList, "\tdb_trim(%s_%d);\n",VarList[q].fieldname,i);
		}
		else
			fprintf(funcList, "\t%s_%d=p%s->%s;\n",VarList[q].fieldname,i,tablename,VarList[q].fieldname);
	}
	fprintf(funcList,"\n\tEXEC SQL UPDATE %s.%s SET\n",modename,tablename);

	int fieldindex = 1;
	/*
	for (j = 1;j < nodeIdx; j++)
	{
		if (j <nodeIdx-1)
			fprintf(funcList, "\t\t%s=:%s_%d,\n",VarList[j].fieldname,VarList[j].fieldname,i);
		else
			fprintf(funcList, "\t\t%s=:%s_%d\n",VarList[j].fieldname,VarList[j].fieldname,i);
	}
	*/
	for (j = 1;j < nodeIdx; j++)
	{
		if(strcasecmp("level",VarList[j].fieldname) == 0)
			fprintf(funcList, "\t\t\"LEVEL\"=:%s_%d",VarList[j].fieldname,i);
		else
			fprintf(funcList, "\t\t%s=:%s_%d",VarList[j].fieldname,VarList[j].fieldname,i);
		if (j <nodeIdx-1)
			fprintf(funcList,",\n");
		else
			fprintf(funcList,"\n");
	}
	fprintf(funcList,"\tWHERE\n");
	while(strncmp(ActList[i].field[fieldindex],"end",3) != 0)
	{
		fprintf(funcList, "\t\t%s = :vv_%s%d_%d",ActList[i].field[fieldindex],ActList[i].field[fieldindex],fieldindex,i);
		if (strncmp(ActList[i].field[fieldindex+1],"end",3) != 0)
			fprintf(funcList,"\tand");
		fieldindex++;
	}
	fprintf(funcList,";\n");
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}
/*
void gen_debug_printf(void)
{
	int i=0;
	fprintf(funcList, "int DB_%s_debug_print",tablename);
	fprintf(headFile, "int DB_%s_debug_print",tablename);
	for (i = 0;i< nodeIdx; i++)
	{
		if(strcmp(VarList[i].type,"char")==0)
			fprintf(funcList, "\tprintf(%s_%d:%s_%d,\n",VarList[i].fieldname,i,"indicator",i);
		else if(strcmp(VarList[i].type,"char")==0)
			fprintf(funcList, "\tprintf(%s_%d:%s_%d,\n",VarList[i].fieldname,i,"indicator",i);
		else if(strcmp(VarList[i].type,"char")==0)
			fprintf(funcList, "\tprintf(%s_%d:%s_%d,\n",VarList[i].fieldname,i,"indicator",i);

	}
}
*/
void gen_update_gen_lock_by()
{
	fprintf(funcList, "int DB_%s_%s_",tablename,ActList[i].actionname);
	fprintf(headFile, "int DB_%s_%s_",tablename,ActList[i].actionname);
	int iIdx = 1;
	while(strncmp(ActList[i].field[iIdx],"end",3) != 0)
	{
		fprintf(funcList, "%s",ActList[i].field[iIdx]);
		fprintf(headFile, "%s",ActList[i].field[iIdx]);
		if ( (strncmp(ActList[i].field[iIdx+1],"end",3) != 0) && (strncmp(ActList[i].actionname,"read_or_by",10) == 0))
		{
			fprintf(funcList, "_or_");
			fprintf(headFile, "_or_");
		}
		else
			if (strncmp(ActList[i].field[iIdx+1],"end",3) != 0)
			{
				fprintf(funcList, "_and_");
				fprintf(headFile, "_and_");
			}
			iIdx++;
	}
	iIdx = 2;
	int j = 0;
	fprintf(funcList, "(");
	fprintf(headFile, "(");
	fprintf(funcList, "T_%s *p%s)",tablename,tablename);
	fprintf(headFile, "T_%s *p%s)",tablename,tablename);
	fprintf(headFile, ";\n");
	fprintf(funcList, "\n{\n");
	fprintf(funcList,"\tint bRet = 0;\n");
	fprintf(funcList, "\tEXEC SQL BEGIN DECLARE SECTION;\n");
	for (j = 1;j < nodeIdx; j++)
	{
		if ( strncmp(VarList[j].type,"char",4) == 0)
		{
			fprintf(funcList, "\t\t%s\t%s_%d%s=\"\";\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
		}
		else
			fprintf(funcList, "\t\t%s\t%s_%d%s=0;\n",VarList[j].type,VarList[j].fieldname,i,VarList[j].length);
	}

	fprintf(funcList, "\tEXEC SQL END DECLARE SECTION;\n");
	fprintf(funcList, "\n\tSQLCODE = 0;\n");
	for (int q = 1;q < nodeIdx; q++)
	{
		if (strncmp(VarList[q].type,"char",4) == 0)
		{
			fprintf(funcList, "\tstrncpy(%s_%d,p%s->%s,sizeof(%s_%d)-1);\n",VarList[q].fieldname,i,tablename,VarList[q].fieldname,VarList[q].fieldname,i);
			fprintf(funcList, "\tdb_trim(%s_%d);\n",VarList[q].fieldname,i);
		}
		else
			fprintf(funcList, "\t%s_%d=p%s->%s;\n",VarList[q].fieldname,i,tablename,VarList[q].fieldname);
	}

	fprintf(funcList,"\n\tEXEC SQL UPDATE %s.%s SET\n",modename,tablename);
	/*
	for (j = 1;j < nodeIdx; j++)
	{
		if (j <nodeIdx-1)
			fprintf(funcList, "\t\t%s=:%s_%d,\n",VarList[j].fieldname,VarList[j].fieldname,i);
		else
			fprintf(funcList, "\t\t%s=:%s_%d\n",VarList[j].fieldname,VarList[j].fieldname,i);
	}
	*/
	for (j = 1;j < nodeIdx; j++)
	{
		if(strcasecmp("level",VarList[j].fieldname) == 0)
			fprintf(funcList, "\t\t\"LEVEL\"=:%s_%d",VarList[j].fieldname,i);
		else
			fprintf(funcList, "\t\t%s=:%s_%d",VarList[j].fieldname,VarList[j].fieldname,i);
		if (j <nodeIdx-1)
			fprintf(funcList,",\n");
		else
			fprintf(funcList,"\n");
	}
	fprintf(funcList,"\tWHERE\n");

	fprintf(funcList, "\tcurrent of %s_%s;\n\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList,"\tbRet = SQLCODE;\n");
	fprintf(funcList, "\tif (bRet)\n");
	fprintf(funcList, "\t{\n");


	fprintf(funcList, "\t\tdb_chk_err(__FILE__,__LINE__,&sqlca);\n");
	fprintf(funcList, "\t\tEXEC SQL CLOSE %s_%s;\n",tabelnameforcur,ActList[i].field[1]);
	fprintf(funcList, "\t\treturn(bRet);\n");
	fprintf(funcList, "\t}\n");
	fprintf(funcList, "\treturn 0;\n");
	fprintf(funcList, "}\n\n");
	i++;
}
// 函数gen_code()
// 编程:孔令国 2004-08-05 15:45:09
// 描述:根据字段列表和操作列表生成相应的sqc代码文件
// 参数:空
// 返回:0表示成功,其它表示失败

int gen_code()
{
	char cfilename[54] = "";
	//sprintf(cfilename,"%s.sqc",filename);
	strcpy(cfilename,output_filename);
	if((funcList = fopen(cfilename,"w")) == NULL)
	{
		printf("%s\n","Error when writing sqc code file");
		return 1;
	}
	fprintf(funcList, "/*************************************************************************/\n");
	fprintf(funcList, "/*          Auto ESQL code generator v3.0 by Lingguo.Kong   WenJian       */\n");
	fprintf(funcList, "/*          CopyRight Kingstar Group All right reserved.                 */\n");
	fprintf(funcList, "/*          input : *.act  the script                                    */\n");
	fprintf(funcList, "/*          return : the sqlca.sqlcode                                   */\n");
	fprintf(funcList, "/*          mode name:                                                   */\n");
	fprintf(funcList, "/*          func name:                                                   */\n");
	fprintf(funcList, "/*          author:                                                      */\n");
	fprintf(funcList, "/*************************************************************************/\n\n");
	fprintf(funcList, "#include <stdio.h>\n");
	fprintf(funcList, "#include <stdlib.h>\n");
	fprintf(funcList, "#include <string.h>\n");
	fprintf(funcList, "#include \"esqlc.h\"\n");
   	fprintf(funcList, "#include \"%s_stru.h\"\n",filename);

//	fprintf(funcList, "EXEC SQL INCLUDE SQLCA;\n\n");

	fprintf(funcList, "int db_chk_err(char file[],int line,struct sqlca *caPointer);\n");
	fprintf(funcList, "void db_trim(char *str);\n");
	while (strncmp(ActList[i].actionname,"end",3) != 0)
	{
		printf("Current operation: %s\n",ActList[i].actionname);
		if (strncmp(ActList[i].actionname,"end",3) == 0)
			break;
		switch (ActList[i].actiontype)
		{
		case 0:
			gen_modename();
			break;
		case 1:
			gen_read_by();
			break;
		case 2:
			gen_read_or_by();
			break;
		case 3:
			gen_update_by();
			break;
		case 4:
			gen_del_by();
			break;
		case 5:
			gen_read_lock_by();
			break;
		case 6:
			gen_update_lock_by();
			break;
		case 7:
			gen_free_lock_by();
			break;
		case 8:
			gen_open_select_by();
			break;
		case 9:
			gen_fetch_select_by();
			break;
		case 10:
			gen_close_select_by();
			break;
		case 11:
			gen_add();
			break;
		case 12:
			gen_open_select_between();
			break;
		case 13:
			gen_open_select_for_update_by();
			break;
		case 14:
			gen_read_blur_by();
			break;
		case 15:
			gen_insert();
			break;
		case 16:
			gen_update_gen_by();
			break;
		case 17:
			gen_update_gen_lock_by();
			break;
		case 18:
			gen_del_all();
			break;
		case 19:
			gen_open_with_hold_select_by();
			break;
		default:
			printf("Un supported act type!");
			break;
		};
		fflush(funcList);
		fflush(headFile);
	}
	//gen_debug_printf();
	return 0;
}

void gen_fields_name(void)
{
	int j;
	for (j = 0;j <nodeIdx-1; j++)
	{
		//printf(VarList[j].fieldname);
		if( strcasecmp("level",VarList[j].fieldname) == 0)
		{
			fprintf(funcList,"\"LEVEL\",\n");
		}
		else
			fprintf(funcList, "%s,\n",VarList[j].fieldname);
	}
	if( strcasecmp("level",VarList[j].fieldname) == 0)
	{
		fprintf(funcList,"\"LEVEL\"");
	}
	else
		fprintf(funcList, "%s",VarList[j].fieldname);
}

int main(int argc,char **argv)
{
	char *p=NULL;
	if (argc < 2)
	{
		printf("%s","Usage:dbcrt_v3 <tablename.act>\n");
		return 0;
	}
	p=strchr(argv[1],'.');
	if(!p)
	{
		printf("%s","Usage:dbcrt_v3 <tablename.act>\n");
	    return  -1;
	}
	memcpy(filename,argv[1],p-argv[1]);

	if(argc >= 3)
	{
		sprintf(output_filename,"%s",argv[2]);		
	}
	else
	{
		sprintf(output_filename,"%s.sqc",filename);
	}
	if (format() != 0)
	{
		printf("%s\n","Error Occured when formatting script");
		exit(1);
	}
	if (read_ini() != 0)
	{
		printf("%s\n","Error Occured when reading formatted script");
		exit(2);
	}
	if (gen_head() != 0)
	{
		printf("%s\n","Error Occured when generating header");
		exit(3);
	}
	if (gen_code() != 0)
	{
		printf("%s\n","Error Occured when generating code");
		exit(4);
	}
	fclose(iniFile);
	fclose(funcList);
	fprintf(headFile, "#endif\n");
	fclose(headFile);
	printf("\n%s\n","finished generating code.");
	printf("%s\n","finished reading act script file");
	printf("Generate Procedure succeeded!\n");
	exit(0);
}

