/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.service.impl.DictionaryServiceImpl.java
 * 创建日期： 2006-6-20 13:23:44
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-20 13:23:44      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.security.service.impl;

import java.util.List;

import org.king.security.dao.DictionaryDAO;
import org.king.security.service.DictionaryService;

/**
 * <p> DictionaryServiceImpl.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="DictionaryServiceImpl.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-20
 * 
 *
 */
public class DictionaryServiceImpl implements DictionaryService {

	private DictionaryDAO dictionaryDAO;
	
	
	public void setDictionaryDAO(DictionaryDAO dictionaryDAO) {
		this.dictionaryDAO = dictionaryDAO;
	}


	/* (non-Javadoc)
	 * @see org.king.security.service.DictionaryService#findDictionaryByNo(java.lang.String)
	 */
	public List findDictionaryByNo(String dictNo) {
		String hql = "from Dictionary d where d.id.dictNo = "+dictNo+" order by d.dictOrder";
		return dictionaryDAO.find(hql);
	}

}
