package org.king.check.service.impl;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.WorkconfmapDao;
import org.king.check.domain.Workconfmap;
import org.king.check.service.WorkConfMapService;
import org.king.framework.dao.MyQuery;

public class WorkConfMapServiveImpl implements WorkConfMapService {
	private static final Log log = LogFactory.getLog(WorkConfMapServiveImpl.class);

	private WorkconfmapDao workconfmapDAO;
	
	
    public void setWorkconfmapDAO(WorkconfmapDao workconfmapDAO) {
		this.workconfmapDAO = workconfmapDAO;
	}

	public List find(MyQuery myQuery)
    {
    	return null;
    }
	
	public List find(String query)
	{
		return null;
	}
	 
	public Workconfmap get(Serializable id)
	{
		return null;
	}
	
	public List getAll()
	{
		return null;
	}
	
	public void save(Workconfmap transientInstance)
	{
		workconfmapDAO.save(transientInstance);
	}
	
    public void update(Workconfmap transientInstance)
    {
    	workconfmapDAO.update(transientInstance);
    }
    
    public void delete(Workconfmap persistentInstance)
    {
    	
    }
    
    public Workconfmap getWorkconfmapByClerkId(Integer clerkId)
    {
    	String hql="from Workconfmap workconfmap where workconfmap.clerkid="+clerkId;
    	List judgeList=workconfmapDAO.find(hql);
    	if(judgeList.isEmpty())
    		return null;
    	else {
    		return (Workconfmap)judgeList.get(0);
    	}
    	
    }
}
