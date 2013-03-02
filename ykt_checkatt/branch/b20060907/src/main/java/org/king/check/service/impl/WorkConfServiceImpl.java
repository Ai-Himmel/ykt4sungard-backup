package org.king.check.service.impl;

import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.WorkConfDao;
import org.king.check.domain.Workconf;
import org.king.check.service.WorkConfService;

public class WorkConfServiceImpl implements WorkConfService{
	private static final Log log = LogFactory.getLog(WorkConfServiceImpl.class);
	
	private WorkConfDao workconfDAO; 
	
	
	 public void setWorkconfDAO(WorkConfDao workconfDAO) {
		this.workconfDAO = workconfDAO;
	}

	public void saveWorkConf(Workconf workConf)
	 {
		workconfDAO.save(workConf);
	 }

	  public void updateWorkConf(Workconf workConf)
	  {
		  workconfDAO.update(workConf);
	  }

	  public void deleteWorkConf(String confId)
	  {
		  workconfDAO.delete(getWorkConf(confId));
	  }

	  public Workconf getWorkConf(String workConfId)
	  {
		  Workconf workconf=workconfDAO.get(workConfId);
		  return workconf;
	  }

	  public List getAll()
	  {
		  return workconfDAO.getAll();
	  }
	  public List search(Map filter)throws Exception
	  {
		  String hql="from Workconf workconf where 1=1";
		  hql+=StringUtils.isNotEmpty((String)filter.get("workConfName"))?" and workconf.confname like '%"+(String)filter.get("workConfName")+"%' ":"";
		  List res=workconfDAO.find(hql);
		  return res;
	  }


}
