/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    PersonServiceImpl.java
 * 创建日期： 2007-6-8 上午11:14:21
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-8 上午11:14:21     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.security.service.impl;

import java.util.List;

import org.king.common.dao.AllDAO;
import org.king.security.domain.Person;
import org.king.security.service.IPersonService;

public class PersonServiceImpl implements IPersonService {

	/* (non-Javadoc)
	 * @see org.king.security.service.IPersonService#getPersonByPersonNo(java.lang.String)
	 */
	private AllDAO allDAO;
	public void setAllDAO(AllDAO allDAO) {
		this.allDAO = allDAO;
	}
	public Person getPersonByPersonNo(String no) {
		List l = allDAO.getHibernateTemplate().findByNamedParam("from Person p where p.personCode=:no","no",no);
		if (l != null && l.size() > 0) return (Person)l.get(0);
		return null;
	}

}
