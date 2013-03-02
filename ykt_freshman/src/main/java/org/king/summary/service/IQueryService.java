/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    IQueryService.java
 * 创建日期： 2007-7-6 11:38:27
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-7-6 11:38:27     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.summary.service;

import java.util.List;

import org.king.summary.web.action.QueryInfo;

public interface IQueryService {

	public int queryGraduateInfos(List res,QueryInfo condition,int pageNo,int pageSize);
}
