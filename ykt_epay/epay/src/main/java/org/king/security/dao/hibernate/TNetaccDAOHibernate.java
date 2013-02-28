package org.king.security.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.common.query.QueryTranslate;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.framework.util.MyUtils;
import org.king.security.dao.TNetaccDAO;
import org.king.security.domain.TNetacc;
import org.king.utils.PaginationUtil;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class TNetaccDAOHibernate implements TNetaccDAO {
	private static final Logger log = LoggerFactory
	.getLogger(TNetaccDAOHibernate.class);
	private BaseDAO baseDAO;
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	public void delete(TNetacc persistentInstance) {
		baseDAO.removeEntity(persistentInstance);
	}

	public List find(MyQuery myQuery) {
		// TODO Auto-generated method stub
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		// TODO Auto-generated method stub
		return baseDAO.findEntity(query);
	}

	public TNetacc get(Serializable id) {
		// TODO Auto-generated method stub
		return (TNetacc)baseDAO.getEntity(TNetacc.class, id);
	}

	public List getAll() {
		// TODO Auto-generated method stub
		return this.find("from TNetacc");
	}

	public void save(TNetacc transientInstance) {
		// TODO Auto-generated method stub
		baseDAO.saveEntity(transientInstance);
	}

	public void update(TNetacc transientInstance) {
		// TODO Auto-generated method stub
		baseDAO.updateEntity(transientInstance);
	}
	
	public TNetacc findNetaccByAccno(String accno) {
		if (MyUtils.isBlank(accno)) {
			return null;
		}
		TNetacc netacc = null;
		try {
			netacc = (TNetacc)baseDAO.getEntity(TNetacc.class, accno);
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
		
		return netacc;
	}
	
	public void findByPage(DBPaginatedList page, QueryTranslate queryTranslate) {
		PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, queryTranslate);
		
	}

}
