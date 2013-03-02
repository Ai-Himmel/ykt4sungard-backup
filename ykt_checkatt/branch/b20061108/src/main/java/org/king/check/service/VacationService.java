package org.king.check.service;

import java.io.Serializable;
import java.util.Calendar;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Vacation;

public interface VacationService {
	public void save(Vacation vacation)throws Exception;
	
	public void delete(Vacation vacation)throws Exception;
	
	public Vacation get(Serializable id)throws Exception;
	
	public boolean isGlobeVacation(Calendar cal)throws Exception;
	
	public List getAll();
	
	public List searchByFilter(Map filter)throws Exception;
	
	public void update(Vacation vacation);
	
	public boolean isDepartVacation(String departId,Calendar cal)throws Exception;
	
	public List getVacationsByDeptId(String departId)throws Exception;
	
	public List getGlobeVacation()throws Exception;
}
