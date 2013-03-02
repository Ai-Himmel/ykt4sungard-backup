/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2007
 * �ļ���    PersonServiceImpl.java
 * �������ڣ� 2007-6-8 ����11:14:21
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 *  2007-6-8 ����11:14:21     ��ʤ        �����ļ���ʵ�ֻ�������
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
