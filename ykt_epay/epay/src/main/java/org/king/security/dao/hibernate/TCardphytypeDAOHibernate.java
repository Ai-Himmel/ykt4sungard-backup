package org.king.security.dao.hibernate;

import java.util.List;

import org.king.framework.dao.BaseDAO;
import org.king.security.dao.TCardphytypeDAO;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class TCardphytypeDAOHibernate implements TCardphytypeDAO{

	private static final Logger log = LoggerFactory.getLogger(TCardphytypeDAOHibernate.class);
    private BaseDAO baseDAO;
	
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	
	public List getAvailCardPhytype() {
		log.debug("getting Avail CardPhytype");
	    String hql = "from TCardphytype t where t.useflag = 1 ";
	    return baseDAO.findEntity(hql);
	}

}
