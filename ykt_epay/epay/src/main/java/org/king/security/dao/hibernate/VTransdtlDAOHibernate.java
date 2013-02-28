package org.king.security.dao.hibernate;

import org.king.common.displaytag.DBPaginatedList;
import org.king.common.query.QueryTranslate;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.security.dao.VTransdtlDAO;
import org.king.utils.PaginationUtil;

public class VTransdtlDAOHibernate implements VTransdtlDAO {
	
	private BaseDAO baseDAO;
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public void findByPage(DBPaginatedList page, QueryTranslate queryTranslate) {
		PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, queryTranslate);
	}

}
