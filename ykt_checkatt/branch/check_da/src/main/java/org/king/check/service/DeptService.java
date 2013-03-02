package org.king.check.service;

import java.util.List;

import org.king.check.domain.TDept;

public interface  DeptService{
	
	public List findDept(TDept dept)throws Exception;
	
	public TDept getDeptByCode(String deptcode);

}
