/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    IQuartersNoticeService.java
 * 创建日期： 2007-6-14 10:13:59
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-14 10:13:59     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.quarters.service;

import java.util.List;

public interface IQuartersNoticeService {
	

	public int searchStudents(List res,String uId,NoticeInfo con,int pageNo,int pageSize);
	//
	public List getNoticeDataSource(String uId,List stuIds);
	
}
