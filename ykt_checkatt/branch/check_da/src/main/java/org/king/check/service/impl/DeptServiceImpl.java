package org.king.check.service.impl;
import java.util.List;

import org.apache.commons.lang.StringUtils;
import org.king.check.dao.DeptDAO;
import org.king.check.domain.TDept;
import org.king.check.service.DeptService;

public class DeptServiceImpl implements DeptService{
	
	private DeptDAO deptDAO;

	public void setDeptDAO(DeptDAO deptDAO) {
		this.deptDAO = deptDAO;
	}

	public List findDept(TDept dept) throws Exception{
		
	   StringBuffer query = new StringBuffer("from  TDept d where 1=1 ");
	   if(StringUtils.isNotEmpty(dept.getDeptcode())){
		   query.append(" and  d.deptcode ='").append(dept.getDeptcode()).append("'");
	   }
	   return deptDAO.findDept(query.toString());
	}

    public TDept getDeptByCode(String deptcode) {
        if (StringUtils.isBlank(deptcode)) {
            return null;
        }
        String query = "from TDept d where d.deptcode='" + deptcode + "'";
        List result = deptDAO.findDept(query);
        if (result != null && result.size() > 0) {
            return (TDept) result.get(0);
        }
        return null;
    }
	
}
