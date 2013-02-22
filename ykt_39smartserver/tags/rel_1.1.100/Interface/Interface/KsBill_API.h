/*
 *	szFileType指定需要复制的文件类型：如果为txt文件，则szFileType为"txt"
 *  将szSrcPath中的指定文件类型的文件复制到szDestPath的szDate目录下
 *  如果szDate目录不存在，则创建，如果szDate存在，则需要查看nOperType（nOperType为操作类别）
 *  如果类别为1，则表示覆盖方式，直接将指定文件类型的文件覆盖到szDate目录下面就可以了，
 *  如果类别为2，则表示重建方式，这时候需要将szDate目录下文件全部清空后，然后从szSrcPath下面复制指定文件类型的文件过来

 *  返回值0，表示成功，其他表示失败，如果失败，在szMsg中返回失败原因  
 */
extern "C"  int WINAPI CopyFileToDest(int nOperType, 
											   char *szFileType,
											   char *szDate,
											   char *szSrcPath,
											   char *szDestPath,
											   char *szMsg);


/*
 *	从szSrcPath目录下的szDate目录中读取文件名为szCustNo后缀为szFileType的文件内容。
 *  一次读取指定的一行的内容，将一行内容依次放入szContent0,szContent1,szContent2,szContent3中
 *  每个content最多能够放入253个字符（包含结束符\0），如果一行内容大于(253-1)*4，则报错，
 *  pnLen0~pnLen3中存放对应的content中存放的真实的字符个数（同样也包含结束符\0）
 *  pnCurLine指定需要读取某行的内容,读取成功后，将pnCurLine加1
 *  如果下一行为文件末尾，则设置pEndFlag为1，否则为0
 *  pdwLowDateTime和pdwHighDateTime表示文件最后修改日期时间，
 *  如果输入都为0，则不做校验，将需要读取的文件的最后修改日期时间输出就可以了；
 *  如果其中有一个不为0，则需要校验输入的时间和读取的文件的最后修改日期时间是否一致，
 *  如果不一致，返回错误
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

