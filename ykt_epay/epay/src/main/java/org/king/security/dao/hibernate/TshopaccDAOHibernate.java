package org.king.security.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.util.MyUtils;
import org.king.security.dao.TShopaccDAO;
import org.king.security.domain.TShopacc;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class TshopaccDAOHibernate implements TShopaccDAO {
	private static final Logger log = LoggerFactory.getLogger(TshopaccDAOHibernate.class);
	private BaseDAO baseDAO;
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	public void delete(TShopacc persistentInstance) {
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

	public TShopacc get(Serializable id) {
		// TODO Auto-generated method stub
		return (TShopacc)baseDAO.getEntity(TShopacc.class, id);
	}

	public List getAll() {
		// TODO Auto-generated method stub
		return this.find("from TShopacc");
	}

	public void save(TShopacc transientInstance) {
		// TODO Auto-generated method stub
		baseDAO.saveEntity(transientInstance);
	}

	public void update(TShopacc transientInstance) {
		// TODO Auto-generated method stub
		baseDAO.updateEntity(transientInstance);
	}
	
	public TShopacc findShopaccByAccno(String accno) {
		if (MyUtils.isBlank(accno)) {
			return null;
		}
		
		TShopacc shopacc = null;
		try {
			shopacc = (TShopacc)baseDAO.getEntity(TShopacc.class, accno);
		} catch (Exception e) {
			return null;
		}
		
		return shopacc;
	}

}
