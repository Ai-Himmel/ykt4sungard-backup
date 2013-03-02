package org.king.check.dao;

import org.king.check.domain.TUnplanstudent;
import org.king.framework.dao.DAO;

public interface UnplanStudentDAO extends DAO{
	
	public void update(TUnplanstudent unplanstudent);

}
