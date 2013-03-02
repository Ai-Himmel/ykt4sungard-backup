package org.king.check.service.impl;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.WorkTimeConfDao;
import org.king.check.domain.Worktimeconf;
import org.king.check.service.WorkTimeConfService;

public class WorkTimeConfImpl implements WorkTimeConfService{
	private static final Log log = LogFactory.getLog(WorkTimeConfImpl.class);
	
	private WorkTimeConfDao worktimeconfDAO;
	
	
	public void setWorktimeconfDAO(WorkTimeConfDao worktimeconfDAO) {
		this.worktimeconfDAO = worktimeconfDAO;
	}

	public void saveWorkTimeConf(Worktimeconf workTimeConf)
	{
		worktimeconfDAO.save(workTimeConf);
	}

	  public void updateWorkTimeConf(Worktimeconf workTimeConf)
	  {
		  worktimeconfDAO.update(workTimeConf);
	  }

	  public void deleteWorkTimeConf(String workTimeConfId)
	  {
		  worktimeconfDAO.delete(getWorkTimeConf(workTimeConfId));
	  }

	  public Worktimeconf getWorkTimeConf(String workTimeConfId)
	  {
		  Worktimeconf worktimeconf=worktimeconfDAO.get(workTimeConfId);
		  return worktimeconf;
	  }

	  public List getAll()
	  {
		  return worktimeconfDAO.getAll();
	  }

	  public List getWorkTimeConfParasByWorkTimeConfName(String workTimeConfName)
	  {
		  return null;
	  }
	  public List getWorkTimeConfParasByWorkTimeConfId(String workTimeConfId)
	  {
		return null;  
	  }
	  public List search(Map filter)throws Exception
	  {
		  String hql="from Worktimeconf worktimeconf where 1=1";
		  hql+=StringUtils.isNotEmpty((String)filter.get("workTimeName"))?" and worktimeconf.confname like '%"+(String)filter.get("workTimeName")+"%' ":"";
		  List res=worktimeconfDAO.find(hql);
		  return res;
	  }
	  public List reForMatWorkTimeList(List workTimeList)throws Exception
	  {
		  List newWorkTimeList=new ArrayList();
		  
		  Iterator workTimeIte=workTimeList.iterator();
		  
		  while(workTimeIte.hasNext())
		  {
			  Worktimeconf worktimeconf=(Worktimeconf)workTimeIte.next();
			  String temp=worktimeconf.getOndutytime1();
			  if(StringUtils.isNotEmpty(temp))
			  worktimeconf.setOndutytime1(temp.substring(0,2)+":"+temp.substring(2));
			  
			  temp=worktimeconf.getOndutytime2();
			  if(StringUtils.isNotEmpty(temp))
			  worktimeconf.setOndutytime2(temp.substring(0,2)+":"+temp.substring(2));
			  
			  temp=worktimeconf.getOndutytime3();
			  if(StringUtils.isNotEmpty(temp))
			  worktimeconf.setOndutytime3(temp.substring(0,2)+":"+temp.substring(2));
			  
			  temp=worktimeconf.getOndutytime4();
			  if(StringUtils.isNotEmpty(temp))
			  worktimeconf.setOndutytime4(temp.substring(0,2)+":"+temp.substring(2));
			  
			  temp=worktimeconf.getOffdutytime1();
			  if(StringUtils.isNotEmpty(temp))
			  worktimeconf.setOffdutytime1(temp.substring(0,2)+":"+temp.substring(2));
			  
			  temp=worktimeconf.getOffdutytime2();
			  if(StringUtils.isNotEmpty(temp))
			  worktimeconf.setOffdutytime2(temp.substring(0,2)+":"+temp.substring(2));
			  
			  temp=worktimeconf.getOffdutytime3();
			  if(StringUtils.isNotEmpty(temp))
			  worktimeconf.setOffdutytime3(temp.substring(0,2)+":"+temp.substring(2));
			  
			  temp=worktimeconf.getOffdutytime4();
			  if(StringUtils.isNotEmpty(temp))
			  worktimeconf.setOffdutytime1(temp.substring(0,2)+":"+temp.substring(2));
			  
			  newWorkTimeList.add(worktimeconf);
		  }
		  
		  return newWorkTimeList;
	  }

}
