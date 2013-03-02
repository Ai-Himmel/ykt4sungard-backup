#include "stdio.h"
#include "vector"
#include "memory.h"

typedef struct 
{
	char phyCardID[11];
	char date[9];
	char time[7];
}KQINFO;

class FileParse
{
public:
	FileParse(int termID):m_termID(termID),m_offset(0)
	{
		memset(m_fileName,0,sizeof(m_fileName));
		sprintf(m_fileName,"kq%d.txt",termID);
		memset(m_offsetFileName,0,sizeof(m_offsetFileName));
		sprintf(m_offsetFileName,"kq%d.ind",termID);
	}
	~FileParse()
	{
	}
	int getOffset();
	int setOffset(long offset);
	int getKqInfo(std::vector<KQINFO> &vecKqInfo);
	int writeLog(std::vector<KQINFO> &vecKqInfo);
private:
	char *getDate(char date[8]);
	int test_log_dir(const char *log_dir);
	int moveKqFile();
	int moveCardInfoDir();
	char m_fileName[16];
	char m_offsetFileName[16];
	int m_termID;
	unsigned long m_offset;
};
