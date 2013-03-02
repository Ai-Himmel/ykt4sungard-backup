/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.check.service.impl.CheckTotalServiceImpl.java
 * 创建日期： 2006-6-15 10:10:51
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-15 10:10:51      ljf        创建文件，实现基本功能
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
 * <p> {功能说明} </p>
 *
 * <p><a href="CheckTotalServiceImpl.java.html"><i>查看源代码</i></a></p>  
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
