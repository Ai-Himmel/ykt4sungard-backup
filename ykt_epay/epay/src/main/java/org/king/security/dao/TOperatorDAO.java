package org.king.security.dao;

import org.king.framework.dao.DAO;
import org.king.security.domain.TOperator;

public interface TOperatorDAO extends DAO {

	//通过操作员代码获取操作员 信息
	public TOperator findOperBycode(String operCode);

}
