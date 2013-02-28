package org.king.security.dao.hibernate;

import org.king.framework.dao.BaseDAO;
import org.king.framework.util.MyUtils;
import org.king.security.dao.TOperatorDAO;
import org.king.security.domain.TOperator;

public class TOperatorDAOHibernate implements TOperatorDAO {
	
	private BaseDAO baseDAO;
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	
	public TOperator findOperBycode(String operCode) {
		if (MyUtils.isBlank(operCode)) {
			return null;
		}
		
		TOperator operator = null;
		try {
			operator = (TOperator)baseDAO.getEntity(TOperator.class, operCode);
		} catch (Exception e) {
			return null;
		}
		
		return operator;
	}

}
