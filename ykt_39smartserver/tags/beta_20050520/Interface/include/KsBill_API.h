/*
 *	szFileTypeָ����Ҫ���Ƶ��ļ����ͣ����Ϊtxt�ļ�����szFileTypeΪ"txt"
 *  ��szSrcPath�е�ָ���ļ����͵��ļ����Ƶ�szDestPath��szDateĿ¼��
 *  ���szDateĿ¼�����ڣ��򴴽������szDate���ڣ�����Ҫ�鿴nOperType��nOperTypeΪ�������
 *  ������Ϊ1�����ʾ���Ƿ�ʽ��ֱ�ӽ�ָ���ļ����͵��ļ����ǵ�szDateĿ¼����Ϳ����ˣ�
 *  ������Ϊ2�����ʾ�ؽ���ʽ����ʱ����Ҫ��szDateĿ¼���ļ�ȫ����պ�Ȼ���szSrcPath���渴��ָ���ļ����͵��ļ�����

 *  ����ֵ0����ʾ�ɹ���������ʾʧ�ܣ����ʧ�ܣ���szMsg�з���ʧ��ԭ��  
 */
extern "C"  int WINAPI CopyFileToDest(int nOperType, 
											   char *szFileType,
											   char *szDate,
											   char *szSrcPath,
											   char *szDestPath,
											   char *szMsg);


/*
 *	��szSrcPathĿ¼�µ�szDateĿ¼�ж�ȡ�ļ���ΪszCustNo��׺ΪszFileType���ļ����ݡ�
 *  һ�ζ�ȡָ����һ�е����ݣ���һ���������η���szContent0,szContent1,szContent2,szContent3��
 *  ÿ��content����ܹ�����253���ַ�������������\0�������һ�����ݴ���(253-1)*4���򱨴�
 *  pnLen0~pnLen3�д�Ŷ�Ӧ��content�д�ŵ���ʵ���ַ�������ͬ��Ҳ����������\0��
 *  pnCurLineָ����Ҫ��ȡĳ�е�����,��ȡ�ɹ��󣬽�pnCurLine��1
 *  �����һ��Ϊ�ļ�ĩβ��������pEndFlagΪ1������Ϊ0
 *  pdwLowDateTime��pdwHighDateTime��ʾ�ļ�����޸�����ʱ�䣬
 *  ������붼Ϊ0������У�飬����Ҫ��ȡ���ļ�������޸�����ʱ������Ϳ����ˣ�
 *  ���������һ����Ϊ0������ҪУ�������ʱ��Ͷ�ȡ���ļ�������޸�����ʱ���Ƿ�һ�£�
 *  �����һ�£����ش���
 */
extern "C"  int WINAPI ReadOneLineFromFile(char *szFileType,
													char *szCustNo,
													char *szDate,
													char *szSrcPath,
													int  *pnCurLine,
													unsigned int *pdwLowDateTime,
													unsigned int *pdwHighDateTime,
													int  *pEndFlag,
													char *szContent0,
													int  *pnLen0,
													char *szContent1,
													int  *pnLen1,
													char *szContent2,
													int  *pnLen2,
													char *szContent3,
													int  *pnLen3,
													char *szMsg);

