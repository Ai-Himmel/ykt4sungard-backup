package org.king.check.service.impl;

import java.io.Serializable;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.DepartConfDAO;
import org.king.check.domain.TCheckWorkconfinfo;
import org.king.check.service.DepartConfService;
import org.king.check.util.DateUtilExtend;
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
	 
	public TCheckWorkconfinfo get(Serializable id)
	{
		return departConfDAO.get(id);
	}
	
	public List getAll()
	{
		return departConfDAO.getAll();
	}
	
	public void save(TCheckWorkconfinfo transientInstance)
	{
		departConfDAO.save(transientInstance);
	}
	
    public void update(TCheckWorkconfinfo transientInstance)
    {
    	departConfDAO.update(transientInstance);
    }
    
    public void delete(TCheckWorkconfinfo persistentInstance)
    {
    	departConfDAO.delete(persistentInstance);
    }
    public List getDepartConfByDptId(String dptId)
    {
    	List dptConfList;
    	String hql="from TCheckWorkconfinfo departconf where departconf.department.id='"+dptId+"' order by departconf.enddate desc";
    	dptConfList=departConfDAO.find(hql);
    	return dptConfList;
    }
    public List isExist(Map filter)throws Exception
    {    	
    	return null;
    }
    
    /**
     * 判断是否存在考勤制度,存在返回true,不存在返回false
     */
    public boolean ifExistDeptConf(String deptId, String workDate) {
		StringBuffer querySql = new StringBuffer(1024);
		querySql.append("select count(*) workConfNum from YKT_CK.T_CHECK_WORKCONFINFO")
		.append(" where CHECK_TYPEID=?")
		.append(" and BEGINDATE =?");
		Map queryResult = jdbcTemplate.queryForMap(querySql.toString(),new Object[]{deptId,workDate});
		int workConfNum = Integer.parseInt(queryResult.get("workConfNum").toString());
		if (workConfNum!=0){
			return true;
		}else{
			return false;
		}
	}

	/**
     * hanjiwei rewrite it 20061009
     * :>	:>	:>	:}
     */
    public List search(Map filter)throws Exception
    {
    	String startDate=DateUtilExtend.formatDate2((String)filter.get("startDate"));
		String endDate=DateUtilExtend.formatDate2(((String)filter.get("endDate")));
		StringBuffer querySql = new StringBuffer(1024);
		querySql.append("select deptconf.CHECK_TYPEID,type.TYPE_NAME,deptconf.BEGINDATE, deptconf.WORKINFO_ID, ")
		.append(" deptconf.WORKTIME_ID, deptconf.IFWORK,conf.WORKCONF_NAME,time.WORKTIME_NAME")
		.append(" from YKT_CK.T_CHECK_WORKCONFINFO deptconf ")
		.append(" left join YKT_CK.T_WORKCONFINFO conf on conf.WORKCONF_ID=deptconf.WORKINFO_ID")
		.append(" left join YKT_CK.T_WORKTIMEINTO time on time.WORKTIME_ID=deptconf.WORKTIME_ID")
		.append(" left join YKT_CK.T_CHECKTYPE type on type.TYPE_ID=deptconf.CHECK_TYPEID")
		.append(" where deptconf.BEGINDATE>='"+startDate+"' and deptconf.BEGINDATE<='"+endDate+"'");
		if (StringUtils.isNotEmpty((String)filter.get("typeId"))){
			querySql.append(" and deptconf.CHECK_TYPEID='"+(String)filter.get("typeId")+"'");
		}
		querySql.append(" order by deptconf.BEGINDATE");
    	//log.debug("sql:"+querySql);
    	List tmpList=jdbcTemplate.queryForList(querySql.toString());
    	

    	return tmpList;
    }

    
    /*
     * 根据部门编号和考勤日期取得考勤制度编号和考勤时间编号
     * @see org.king.check.service.DepartConfService#getConfAndTimeId(java.lang.String, java.lang.String)
     */
	public Map getConfAndTimeId(String deptId, String confDate) {
		StringBuffer querySql = new StringBuffer(1024);
		querySql.append("select deptconf.WORKINFO_ID,deptconf.WORKTIME_ID,type.TYPE_NAME,deptconf.IFWORK, ")
		.append(" deptconf.CHECK_TYPEID,deptconf.BEGINDATE")
		.append(" from YKT_CK.T_CHECK_WORKCONFINFO deptconf")
		.append(" left join YKT_CK.T_CHECKTYPE type on type.TYPE_ID=deptconf.CHECK_TYPEID")
		.append(" where deptconf.CHECK_TYPEID=?")
		.append(" and deptconf.BEGINDATE=?");
		log.debug("------"+querySql);
		Map queryResult = jdbcTemplate.queryForMap(querySql.toString(),new Object[]{deptId,confDate});
		return queryResult;
	}
    
    
}
