package org.king.check.service.impl;

import java.io.Serializable;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.config.CommonConfig;
import org.king.check.dao.ClerkDAO;
import org.king.check.dao.ExtraWorkDAO;
import org.king.check.dao.ExtraworkinfomapDAO;
import org.king.check.domain.Clerk;
import org.king.check.domain.Extraworkinfo;
import org.king.check.domain.Extraworkinfomap;
import org.king.check.service.ExtraWorkService;
import org.king.check.service.SysService;
import org.king.framework.dao.MyQuery;
import org.springframework.jdbc.core.JdbcTemplate;

public class ExtraWorkServiceImpl implements ExtraWorkService{
	private static final Log log = LogFactory.getLog(ExtraWorkServiceImpl.class);
	
	private ExtraWorkDAO extraWorkDAO;	
	
	private ClerkDAO clerkDAO;
	
	private SysService sysService;
	
	private ExtraworkinfomapDAO extraworkinfomapDAO;
	
	private JdbcTemplate jdbcTemplate;
	
    public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}

	public void setClerkDAO(ClerkDAO clerkDAO) {
		this.clerkDAO = clerkDAO;
	}

	public void setExtraWorkDAO(ExtraWorkDAO extraWorkDAO) {
		this.extraWorkDAO = extraWorkDAO;
	}
	
	public void setExtraworkinfomapDAO(ExtraworkinfomapDAO extraworkinfomapDAO) {
		this.extraworkinfomapDAO = extraworkinfomapDAO;
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
	 
	public Extraworkinfo get(Serializable id)
	{
		return extraWorkDAO.get(id);
	}
	
	public List getAll()
	{
		return null;
	}
	
	public void save(Extraworkinfo transientInstance)
	{
		
	}
	
    public void update(Extraworkinfo transientInstance)
    {
    	extraWorkDAO.update(transientInstance);
    }
    
    public void delete(Extraworkinfo persistentInstance)
    {
    	
    }
    public List addExtraWork(Map filter)throws Exception//添加加班信息
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
		  List extraList=new ArrayList();
		  
		  
		  
		  
		  for(int i=0;i<checkValues.length;i++)
		  {
			  Map map=new HashMap();
			  Extraworkinfo extraworkinfo=new Extraworkinfo();
			  Extraworkinfomap extraworkinfomap=new Extraworkinfomap();
			  
			  extraworkinfo.setEnddate(sdf.parse(endDate));
			  extraworkinfo.setRecodedate(new Date());
			  extraworkinfo.setStartdate(sdf.parse(startDate));	
			  extraworkinfo.setOperatorid((String)filter.get("operatorid"));//设置操作人
			  extraWorkDAO.save(extraworkinfo);
			  
			  extraworkinfomap.setClerkid(new Integer(checkValues[i]));
			  extraworkinfomap.setExtrainfoid(extraworkinfo.getExtrainfoid());
			  extraworkinfomapDAO.save(extraworkinfomap);
			  
			  map.put("clerkname",sysService.getCustomerNameByCustomerId(new Integer(checkValues[i])));
			  map.put("startdate",startDate);
			  map.put("enddate",endDate);
			  extraList.add(map);
		  }
		  
		  return extraList;
    }
    public List searchExtraWork(Map filter)throws Exception
    {
    	String sql;
    	sql="select extrawork.STARTDATE as startdate,extrawork.ENDDATE as enddate,extrawork.RECORDDATE as recorddate," +
    			" dpart.DEPT_NAME AS departname,cust.CUT_NAME AS clerkname ," +
    			" dict.DICT_CAPTION as isseat,conf.CONFNAME as confname ,extrawork.EXTRAINFOID as extrainfoid ," +
    			" (select card.CARD_ID from YKT_CUR.T_PIF_CARD card ,YKT_CUR.T_AIF_ACCOUNT account " +
		  		"where card.CARD_ID=account.CARD_ID and account.CUSTOMER_ID=cust.CUT_ID and card.STATE_ID='1000') AS cardnumber ," +
		  		"(select a.account_name from YKT_CK.USR_ACCOUNT  a where a.id=extrawork.OPERATORID) as operatorname " +
    			"from YKT_CK.EXTRAWORKINFOMAP extramap,YKT_CK.EXTRAWORKINFO extrawork,YKT_CK.DEPARTMENT dpart ," +
    			"YKT_CK.CLERK clerk,YKT_CK.WORKCONF conf ,YKT_CUR.T_CIF_CUSTOMER cust," +
		  		" YKT_CK.COM_DICTIONARY dict ,YKT_CK.WORKCONFMAP  map" +
		  		" where extrawork.EXTRAINFOID=extramap.EXTRAINFOID and extramap.CLERKID=clerk.CLERKID " +
		  		" and clerk.DEPARTMENTID=dpart.DEPT_ID and " +
		  		" conf.WORKCONFID =map.WORKCONFID and  map.CLERKID=clerk.CLERKID " +
		  		" and  cust.CUT_ID=clerk.CLERKID " +
		  		" AND dict.DICT_NO=1002 AND dict.DICT_VALUE=clerk.ISSEAT ";
    	sql+=StringUtils.isNotEmpty((String)filter.get("startDate"))?" and extrawork.STARTDATE >='"+(String)filter.get("startDate")+" 00:00:00"+"' ":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get("endDate"))?" and extrawork.ENDDATE <='"+(String)filter.get("endDate")+" 23:59:59"+"' ":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and dpart.DEPT_ID='"+(String)filter.get("deptId")+"' ":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get("trueName"))?" and cust.CUT_NAME  like '%"+(String)filter.get("trueName")+"%' ":"";
    	
    	log.debug("sql:"+sql);
    	
    	List extraInfoList=jdbcTemplate.queryForList(sql);
    	
    	return extraInfoList;
    }
    public void updateExtraInfo(Map filter)throws Exception
    {
    	String startDate=(String)filter.get("startDate");
		  String endDate=(String)filter.get("endDate");
		  
		  startDate=startDate.replace('-','/');
		  endDate=endDate.replace('-','/');
		  
		  //格式化日期
		  startDate=startDate+" "+(String)filter.get("startHour")+":"+(String)filter.get("startMin")+":00";
		  endDate=endDate+" "+(String)filter.get("endHour")+":"+(String)filter.get("endMin")+":00";
		  SimpleDateFormat sdf=new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
		  
		  Extraworkinfo extraworkinfo=extraWorkDAO.get((String)filter.get("extrainfoid"));
		  extraworkinfo.setEnddate(sdf.parse(endDate));
		  extraworkinfo.setStartdate(sdf.parse(startDate));
		  extraworkinfo.setRecodedate(new Date());
		  extraworkinfo.setOperatorid((String)filter.get("operatorid"));
		  
		  update(extraworkinfo);
    }

    public void deleteExtraInfo(String ids[])throws Exception
    {
    	for(int i=0;i<ids.length;i++)
    	{
    		extraWorkDAO.delete(extraWorkDAO.get(ids[i])); 		
    	}
    }
    public List staticExtraInfo(Map filter)throws Exception
    {
    	List extraInfoList= new ArrayList();
		  String hql="from ";
		  String sql="";
		  String lastValue="ini";
		  
		  
		  
		  sql="select " +
		  " extra.STARTDATE as startDate ,"+
		  		"extra.ENDDATE as endDate, " +
		  		"dpart.DEPT_NAME AS departname ," +
		  		" 0 as tatol ," +
		  		"dpart.DEPT_ID AS dept_id," +
		  		"cust.CUT_NAME AS clerkname ," +
		  		"cust.CUT_ID as cut_id," +
		  		"dict.DICT_CAPTION as isseat,conf.CONFNAME as confname " +
		  		" from YKT_CK.EXTRAWORKINFO extra ,YKT_CK.EXTRAWORKINFOMAP extramap,YKT_CK.DEPARTMENT dpart ,YKT_CK.CLERK clerk,YKT_CK.WORKCONF conf ,YKT_CUR.T_CIF_CUSTOMER cust," +
		  		" YKT_CK.COM_DICTIONARY dict ,YKT_CK.WORKCONFMAP  map " +
		  		" where dpart.DEPT_ID=clerk.DEPARTMENTID  AND conf.WORKCONFID = " +
		  		"  map.WORKCONFID and  map.CLERKID=clerk.CLERKID " +
		  		" and  cust.CUT_ID=clerk.CLERKID " +
		  		" AND dict.DICT_NO=1002 AND dict.DICT_VALUE=clerk.ISSEAT " +
		  		" and extra.EXTRAINFOID=extramap.EXTRAINFOID and clerk.CLERKID=extramap.CLERKID " ;
			  
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.trueName))?" and cust.CUT_NAME like '%"+(String)filter.get(CommonConfig.trueName)+"%' ":" ";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and extra.STARTDATE >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00"+"' ":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and extra.ENDDATE  <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59"+"' ":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and clerk.DEPARTMENTID='"+(String)filter.get("deptId")+"' ":"";
	      
	      sql+=" and extra.ENDDATE>=extra.STARTDATE" +
	      		" group by cust.CUT_ID,cust.CUT_NAME,extra.STARTDATE,extra.ENDDATE,dpart.DEPT_NAME,dpart.DEPT_ID,dict.DICT_CAPTION,conf.CONFNAME ";
	      
		  log.debug("sql:"+sql);
		  List staticInfoList=jdbcTemplate.queryForList(sql);
		   if(!staticInfoList.isEmpty())
		   {
			   Iterator staticIte=staticInfoList.iterator();
			   while(staticIte.hasNext())
			   {
				   Map colMap=(Map)staticIte.next();
				   
				   if(lastValue.equals(((Integer)colMap.get("cut_id")).toString()))
						   continue;
				   else lastValue=((Integer)colMap.get("cut_id")).toString();
				   
				   colMap.put("terminateDay",(String)filter.get(CommonConfig.endDate));
				   colMap.put("beginDay",(String)filter.get(CommonConfig.startDate));
				   
				   Integer tatol=getExtraDays(colMap);
				   
				   colMap.put("tatol",tatol);
				   
				   
				   extraInfoList.add(colMap);				   
			   }
		   }

		  return extraInfoList;
    }
    public Integer getExtraDays(Map filter)throws Exception
	  {
		  Integer tatol;
		  int temp=0;
		  String sql="select extra.STARTDATE AS startDate ,extra.ENDDATE as endDate " +
		  		" from  YKT_CK.EXTRAWORKINFO extra ,YKT_CK.EXTRAWORKINFOMAP extramap" +
		  		" where extramap.CLERKID="+filter.get("cut_id")+" and extra.EXTRAINFOID=extramap.EXTRAINFOID "+
		  		" and extra.ENDDATE<='"+(String)filter.get("terminateDay")+" 23:59:59"+"' " +
		  		" and extra.STARTDATE>='"+(String)filter.get("beginDay")+" 00:00:00"+"' " +
		  		" and extra.STARTDATE<=extra.ENDDATE ";
		  Calendar calStart=Calendar.getInstance();
		  Calendar calEnd=Calendar.getInstance();
		  
		  
		  log.debug("sql:"+sql);
		  
		  List tatolList=jdbcTemplate.queryForList(sql);
		  
		  if(!tatolList.isEmpty())
		  {
			  Iterator tatolIte=tatolList.iterator();
			  while(tatolIte.hasNext())
			  {
				  Map colMap=(Map)tatolIte.next();
				  
				  Date startDate=(Date)colMap.get("startDate");
				   Date endDate=(Date)colMap.get("endDate");
				   calStart.setTime(startDate);
				   calEnd.setTime(endDate);
				   
				   int startDay,endDay,startYear,endYear;//得到起始月以便计算天数
				   startYear=calStart.get(Calendar.YEAR);
				   endYear=calEnd.get(Calendar.YEAR);
				   
				   startDay=calStart.get(Calendar.DAY_OF_YEAR);
				   endDay=calEnd.get(Calendar.DAY_OF_YEAR);
				   
				   if(startYear==endYear)
				   {
					   temp+=endDay-startDay+1;
				   }
				   else
				   {
					   int sum=(endYear-startYear-1)*365+(365-startYear)+endYear;
					   temp+=sum;
				   }
			  }
		  }
		  
		  tatol=new Integer(temp);
		  
		  return tatol;
	  }
    public List getExtraWorkDetail(Map filter)throws Exception
    {
    	 String sql="select extra.STARTDATE AS startDate ,extra.ENDDATE as endDate ," +
    	 		" c.CUT_NAME as clerkname " +
	  		" from  YKT_CK.EXTRAWORKINFO extra ,YKT_CK.EXTRAWORKINFOMAP extramap,YKT_CUR.T_CIF_CUSTOMER  c " +
	  		" where extramap.CLERKID="+filter.get("clerkId")+" and extra.EXTRAINFOID=extramap.EXTRAINFOID "+
	  		" and extra.ENDDATE<='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59"+"' " +
	  		" and extra.STARTDATE>='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00"+"' " +
	  		" and extra.STARTDATE<=extra.ENDDATE " +
	  		" and c.CUT_ID=extramap.CLERKID";
    	 
    	 sql+=" order by startDate asc ";
	      
	      log.debug("sql:"+sql);
	      
	      List extraDetailList=jdbcTemplate.queryForList(sql);
	      
		  return extraDetailList;
    }
}
