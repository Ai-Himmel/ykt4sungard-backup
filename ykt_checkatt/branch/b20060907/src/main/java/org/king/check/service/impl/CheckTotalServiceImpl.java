/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.check.service.impl.CheckTotalServiceImpl.java
 * �������ڣ� 2006-6-15 10:10:51
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-15 10:10:51      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.check.service.impl;


import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.hibernate.Criteria;
import org.hibernate.criterion.Restrictions;
import org.king.check.domain.Workinfo;
import org.king.check.service.CheckTotalService;
import org.king.framework.common.BaseHibernateDao;
import org.king.framework.common.support.Page;
import org.king.framework.util.DateUtil;

/**
 * <p> CheckTotalServiceImpl.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="CheckTotalServiceImpl.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-15
 * 
 *
 */
public class CheckTotalServiceImpl extends BaseHibernateDao implements
		CheckTotalService {

	 protected Class getEntityClass() {
	        return Workinfo.class;
	 }
	 

	/* (non-Javadoc)
	 * @see org.king.check.service.CheckTotalService#findBy(java.util.Map)
	 */
	public Page findBy(Map filterMap, Map sortMap, int pageNo, int pageSize) {
		   return super.findAllBy(filterMap,sortMap,pageNo,pageSize);
	}
	
	
	protected void filterCriteria(Criteria criteria, Map filter) {
		if (filter != null && !filter.isEmpty()) {
			 String beginDate = (String)filter.get("beginDate");
		        if (StringUtils.isNotEmpty(beginDate))
		            criteria.add(Restrictions.ge("recordtime", DateUtil.parse(beginDate,"yyyy-MM-DD")));

		        String endDate   = (String)filter.get("endDate");
		        if (StringUtils.isNotEmpty(endDate))
		            criteria.add(Restrictions.le("recordtime", DateUtil.parse(endDate,"yyyy-MM-DD")));

		        //criteria.addOrder(org.hibernate.criterion.Order.asc("serialid"));
			
			
		}
		
	}

}
