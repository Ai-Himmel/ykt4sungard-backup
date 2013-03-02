package org.king.check.service.impl;

import java.io.Serializable;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.IrregularrestDao;
import org.king.check.dao.IrregularrestmapDao;
import org.king.check.domain.Extraworkinfo;
import org.king.check.domain.Extraworkinfomap;
import org.king.check.domain.Irregularrest;
import org.king.check.domain.Irregularrestmap;
import org.king.check.service.IrregularRestService;
import org.king.check.service.SysService;
import org.king.framework.dao.MyQuery;
import org.springframework.jdbc.core.JdbcTemplate;

public class IrregularRestServiceImpl implements IrregularRestService{
	private static final Log log = LogFactory.getLog(IrregularRestServiceImpl.class);
	
	private IrregularrestDao irregularrestDao;
	
	private IrregularrestmapDao irregularrestmapDao;
	
	private SysService sysService;
	
    private JdbcTemplate jdbcTemplate;
	

	public void setIrregularrestDao(IrregularrestDao irregularrestDao) {
		this.irregularrestDao = irregularrestDao;
	}

	public void setIrregularrestmapDao(IrregularrestmapDao irregularrestmapDao) {
		this.irregularrestmapDao = irregularrestmapDao;
	}

	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}
	

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	public List find(MyQuery myQuery)
    {
    	return null;
    }
	
	public List find(String query)
	{
		return null;
	}
	 
	public Irregularrest get(Serializable id)
	{
		return irregularrestDao.get(id);
	}
	
	public List getAll()
	{
		return null;
	}
	
	public void save(Irregularrest transientInstance)
	{
		
	}
	
    public void update(Irregularrest transientInstance)
    {
    	
    }
    
    public void delete(Irregularrest persistentInstance)
    {
    	
    }
    
    public List register(Map filter)throws Exception
    {
    	String []checkValues;
		  checkValues=(String[])filter.get("checkValues");
		  String startDate=(String)filter.get("startDate");
		  String endDate=(String)filter.get("endDate");
		  
		  startDate=startDate.replace('-','/');
		  endDate=endDate.replace('-','/');

		  
		  startDate=startDate+" "+(String)filter.get("startHour")+":"+(String)filter.get("startMin")+":00";
		  endDate=endDate+" "+(String)filter.get("endHour")+":"+(String)filter.get("endMin")+":00";
		  SimpleDateFormat sdf=new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");//日期格式化
		  List irreList=new ArrayList();
		  
		  
		  
		  
		  for(int i=0;i<checkValues.length;i++)
		  {
			  Map map=new HashMap();
			  Irregularrest irregularrest=new Irregularrest();
			  Irregularrestmap irregularrestmap=new Irregularrestmap();
			  
			  irregularrest.setEnddate(sdf.parse(endDate));
			  irregularrest.setOperatorid((String)filter.get("operatorid"));
			  irregularrest.setRecorddate(new Date());
			  irregularrest.setStartdate(sdf.parse(startDate));
			  irregularrestDao.save(irregularrest);//生成特殊休息时间
			  
			  irregularrestmap.setClerkid(new Integer(checkValues[i]));
			  irregularrestmap.setIrregularrestid(irregularrest.getIrregularrestid());
			  irregularrestmapDao.save(irregularrestmap);//生成特殊休息关系影射
			  
			  map.put("clerkname",sysService.getCustomerNameByCustomerId(new Integer(checkValues[i])));
			  map.put("startdate",startDate);
			  map.put("enddate",endDate);
			  irreList.add(map);
		  }
		  
		  return irreList;
    }
    
    public List searchIrregular(Map filter)throws Exception
    {
    	String sql;
    	sql="select irregular.STARTDATE as startdate,irregular.ENDDATE as enddate,irregular.RECORDDATE as recorddate," +
    			" dpart.DEPT_NAME AS departname,cust.CUT_NAME AS clerkname ," +
    			" dict.DICT_CAPTION as isseat,conf.CONFNAME as confname ,irregular.IRREGULARRESTID as irregularid ," +
    			" (select card.CARD_ID from YKT_CUR.T_PIF_CARD card ,YKT_CUR.T_AIF_ACCOUNT account " +
		  		"where card.CARD_ID=account.CARD_ID and account.CUSTOMER_ID=cust.CUT_ID and card.STATE_ID='1000') AS cardnumber ," +
		  		"(select a.account_name from YKT_CK.USR_ACCOUNT  a where a.id=irregular.OPERATORID) as operatorname " +
    			"from YKT_CK.IRREGULARRESTMAP irregularmap,YKT_CK.IRREGULARREST irregular,YKT_CK.DEPARTMENT dpart ," +
    			"YKT_CK.CLERK clerk,YKT_CK.WORKCONF conf ,YKT_CUR.T_CIF_CUSTOMER cust," +
		  		" YKT_CK.COM_DICTIONARY dict ,YKT_CK.WORKCONFMAP  map" +
		  		" where irregular.IRREGULARRESTID=irregularmap.IRREGULARRESTID and irregularmap.CLERKID=clerk.CLERKID " +
		  		" and clerk.DEPARTMENTID=dpart.DEPT_ID and " +
		  		" conf.WORKCONFID =map.WORKCONFID and  map.CLERKID=clerk.CLERKID " +
		  		" and  cust.CUT_ID=clerk.CLERKID " +
		  		" AND dict.DICT_NO=1002 AND dict.DICT_VALUE=clerk.ISSEAT ";
    	sql+=StringUtils.isNotEmpty((String)filter.get("startDate"))?" and irregular.STARTDATE >='"+(String)filter.get("startDate")+" 00:00:00"+"' ":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get("endDate"))?" and irregular.ENDDATE <='"+(String)filter.get("endDate")+" 23:59:59"+"' ":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and dpart.DEPT_ID='"+(String)filter.get("deptId")+"' ":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get("trueName"))?" and cust.CUT_NAME  like '%"+(String)filter.get("trueName")+"%' ":"";
    	
    	log.debug("sql:"+sql);
    	
    	List irreInfoList=jdbcTemplate.queryForList(sql);
    	
    	return irreInfoList;
    }

    public void updateIrregular(Map filter)throws Exception
    {
    	String startDate=(String)filter.get("startDate");
		  String endDate=(String)filter.get("endDate");
		  
		  startDate=startDate.replace('-','/');
		  endDate=endDate.replace('-','/');
		  
//		格式化日期
		  startDate=startDate+" "+(String)filter.get("startHour")+":"+(String)filter.get("startMin")+":00";
		  endDate=endDate+" "+(String)filter.get("endHour")+":"+(String)filter.get("endMin")+":00";
		  SimpleDateFormat sdf=new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
		  
		  Irregularrest irregularrest=irregularrestDao.get((String)filter.get("irregularrestid"));
		  irregularrest.setEnddate(sdf.parse(endDate));
		  irregularrest.setStartdate(sdf.parse(startDate));
		  irregularrest.setRecorddate(new Date());
		  irregularrest.setOperatorid((String)filter.get("operatorid"));
		  
		  irregularrestDao.update(irregularrest);
    }
    public void deleteIrregular(String ids[])throws Exception
    {
    	for(int i=0;i<ids.length;i++)
    	{
    		irregularrestDao.delete(irregularrestDao.get(ids[i])); 		
    		String sql="delete from YKT_CK.IRREGULARRESTMAP ir where ir.IRREGULARRESTID='"+ids[i]+"'";
    		log.debug("sql:"+sql);
    		jdbcTemplate.execute(sql);
    	}
    }
}
