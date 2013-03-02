/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.service.DictionaryService.java
 * 创建日期： 2006-6-20 13:19:11
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-20 13:19:11      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.security.service;

import java.util.List;

import org.king.framework.service.Service;

/**
 * <p> DictionaryService.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="DictionaryService.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-20
 * 
 *
 */
public interface DictionaryService extends Service {

	/**
	 * 通过字典编号查找字典
	 * @param dictNo
	 * @return
	 */
	public List findDictionaryByNo(String dictNo);
}
