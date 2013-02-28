package org.king.security.dao.hibernate;

import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.security.dao.TEpayRecordDAO;
import org.king.security.domain.TEpayRecord;
import org.king.utils.PaginationUtil;

public class TEpayRecordDAOHibernate implements TEpayRecordDAO{
	
	private BaseDAO baseDAO;
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	public List find(MyQuery myQuery) {
		// TODO Auto-generated method stub
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		// TODO Auto-generated method stub
		return baseDAO.findEntity(query);
	}
	public void findByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }
	public void delete(TEpayRecord persistentInstance) {
		// TODO Auto-generated method stub
		baseDAO.removeEntity(persistentInstance);
	}
	public void save(TEpayRecord transientInstance) {
		// TODO Auto-generated method stub
		baseDAO.saveEntity(transientInstance);
	}
	public void update(TEpayRecord transientInstance) {
		// TODO Auto-generated method stub
		baseDAO.updateEntity(transientInstance);
	}
}
