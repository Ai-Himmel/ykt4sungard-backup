package org.king.check.service.impl;

import java.io.Serializable;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.DepartConfDAO;
import org.king.check.domain.Departconf;
import org.king.check.service.DepartConfService;
import org.springframework.jdbc.core.JdbcTemplate;

public class DepartConfServiceImpl implements DepartConfService {
	private static final Log log = LogFactory.getLog(DepartConfServiceImpl.class);
	
	DepartConfDAO departConfDAO;
	private JdbcTemplate jdbcTemplate;
	
	public void setDepartConfDAO(DepartConfDAO departConfDAO) {
		this.departConfDAO = departConfDAO;
	}
	
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}



	public List find(String query)
	{
		return null;
	}
	 
	public Departconf get(Serializable id)
	{
		return departConfDAO.get(id);
	}
	
	public List getAll()
	{
		return departConfDAO.getAll();
	}
	
	public void save(Departconf transientInstance)
	{
		departConfDAO.save(transientInstance);
	}
	
    public void update(Departconf transientInstance)
    {
    	departConfDAO.update(transientInstance);
    }
    
    public void delete(Departconf persistentInstance)
    {
    	departConfDAO.delete(persistentInstance);
    }
    public List getDepartConfByDptId(String dptId)
    {
    	List dptConfList;
    	String hql="from Departconf departconf where departconf.department.id='"+dptId+"' order by departconf.enddate desc";
    	dptConfList=departConfDAO.find(hql);
    	return dptConfList;
    }
    public List isExist(Map filter)throws Exception
    {    	
    	String sql="select " +
    			" d.STARTDATE as startdate, d.ENDDATE as enddate, " +
    			" wconf.CONFNAME as wconfname ,tconf.CONFNAME as tconfname,dpt.DEPT_NAME as dptname " +
    			" from YKT_CK.DEPARTCONF d ,YKT_CK.WORKCONF wconf,YKT_CK.WORKTIMECONF tconf,YKT_CK.DEPARTMENT dpt" +
    			" where d.STARTDATE<='" +(String)filter.get("startDate")+"'" +
    			" and d.ENDDATE>='" +(String)filter.get("startDate")+"'" +
    			" and d.DEPARTMENTID='" +(String)filter.get("dptId")+"'"+	
    			" and wconf.WORKCONFID=d.WORKCONFID" +
    			" and tconf.WORKTIMECONFID=d.WORKTIMECONFID" +
    			" and dpt.DEPT_ID=d.DEPARTMENTID" +
    			" union " +
    			"select " +
    			" d.STARTDATE as startdate, d.ENDDATE as enddate, " +
    			" wconf.CONFNAME as wconfname ,tconf.CONFNAME as tconfname,dpt.DEPT_NAME as dptname " +
    			" from YKT_CK.DEPARTCONF d ,YKT_CK.WORKCONF wconf,YKT_CK.WORKTIMECONF tconf,YKT_CK.DEPARTMENT dpt" +
    			" where d.STARTDATE<='" +(String)filter.get("endDate")+"'" +
    			" and d.ENDDATE>='" +(String)filter.get("endDate")+"'" +
    			" and d.DEPARTMENTID='" +(String)filter.get("dptId")+"'"+	
    			" and wconf.WORKCONFID=d.WORKCONFID" +
    			" and tconf.WORKTIMECONFID=d.WORKTIMECONFID" +
    			" and dpt.DEPT_ID=d.DEPARTMENTID" +
    			" union " +
    			"select " +
    			" d.STARTDATE as startdate, d.ENDDATE as enddate, " +
    			" wconf.CONFNAME as wconfname ,tconf.CONFNAME as tconfname,dpt.DEPT_NAME as dptname " +
    			" from YKT_CK.DEPARTCONF d ,YKT_CK.WORKCONF wconf,YKT_CK.WORKTIMECONF tconf,YKT_CK.DEPARTMENT dpt" +
    			" where d.STARTDATE>='" +(String)filter.get("startDate")+"'" +
    			" and d.ENDDATE<='" +(String)filter.get("endDate")+"'" +
    			" and d.DEPARTMENTID='" +(String)filter.get("dptId")+"'"+	
    			" and wconf.WORKCONFID=d.WORKCONFID" +
    			" and tconf.WORKTIMECONFID=d.WORKTIMECONFID" +
    			" and dpt.DEPT_ID=d.DEPARTMENTID";
    	log.debug("sql:"+sql);
    	List tmpList=jdbcTemplate.queryForList(sql);

    	return tmpList;
    }
    public List search(Map filter)throws Exception
    {
    	/*
    	 * 将日期格式化与数据库一致
    	 */
    	String startDate=(String)filter.get("startDate");
    	startDate=startDate.substring(0,4)+startDate.substring(5,7)+startDate.substring(8);
		String endDate=(String)filter.get("endDate");
    	endDate=endDate.substring(0,4)+endDate.substring(5,7)+endDate.substring(8);
    	
    	String sql="select " +
		" d.STARTDATE as startdate, d.ENDDATE as enddate, " +
		" wconf.CONFNAME as wconfname ,tconf.CONFNAME as tconfname,dpt.DEPT_NAME as dptname " +
		" from YKT_CK.DEPARTCONF d ,YKT_CK.WORKCONF wconf,YKT_CK.WORKTIMECONF tconf,YKT_CK.DEPARTMENT dpt" +
		" where d.STARTDATE<='" +startDate+"'" +
		" and d.ENDDATE>='" +startDate+"'" ;
    	sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and d.DEPARTMENTID='"+(String)filter.get("deptId")+"'":"";
    	sql+=" and wconf.WORKCONFID=d.WORKCONFID" +
		" and tconf.WORKTIMECONFID=d.WORKTIMECONFID" +
		" and dpt.DEPT_ID=d.DEPARTMENTID" +
		" union " +
		"select " +
		" d.STARTDATE as startdate, d.ENDDATE as enddate, " +
		" wconf.CONFNAME as wconfname ,tconf.CONFNAME as tconfname,dpt.DEPT_NAME as dptname " +
		" from YKT_CK.DEPARTCONF d ,YKT_CK.WORKCONF wconf,YKT_CK.WORKTIMECONF tconf,YKT_CK.DEPARTMENT dpt" +
		" where d.STARTDATE<='" +endDate+"'" +
		" and d.ENDDATE>='" +endDate+"'" ;
		sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and d.DEPARTMENTID='"+(String)filter.get("deptId")+"'":"";		
		sql+=" and wconf.WORKCONFID=d.WORKCONFID" +
		" and tconf.WORKTIMECONFID=d.WORKTIMECONFID" +
		" and dpt.DEPT_ID=d.DEPARTMENTID" +
		" union " +
		"select " +
		" d.STARTDATE as startdate, d.ENDDATE as enddate, " +
		" wconf.CONFNAME as wconfname ,tconf.CONFNAME as tconfname,dpt.DEPT_NAME as dptname " +
		" from YKT_CK.DEPARTCONF d ,YKT_CK.WORKCONF wconf,YKT_CK.WORKTIMECONF tconf,YKT_CK.DEPARTMENT dpt" +
		" where d.STARTDATE>='" +startDate+"'" +
		" and d.ENDDATE<='" +endDate+"'";
		sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and d.DEPARTMENTID='"+(String)filter.get("deptId")+"'":"";
		sql+=" and wconf.WORKCONFID=d.WORKCONFID" +
		" and tconf.WORKTIMECONFID=d.WORKTIMECONFID" +
		" and dpt.DEPT_ID=d.DEPARTMENTID";
    	
    	log.debug("sql:"+sql);
    	List tmpList=jdbcTemplate.queryForList(sql);
    	

    	return tmpList;
    }
}
