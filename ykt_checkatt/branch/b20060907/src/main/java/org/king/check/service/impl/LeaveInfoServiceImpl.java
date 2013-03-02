package org.king.check.service.impl;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.config.CommonConfig;
import org.king.check.dao.ClerkDAO;
import org.king.check.dao.DepartmentDAO;
import org.king.check.dao.LeaveInfoDao;
import org.king.check.domain.Clerk;
import org.king.check.domain.Leaveinfo;
import org.king.check.service.LeaveInfoService;
import org.king.check.service.SysService;
import org.springframework.jdbc.core.JdbcTemplate;
import org.apache.commons.lang.StringUtils;


public class LeaveInfoServiceImpl implements LeaveInfoService{

	 private static final Log log = LogFactory.getLog(LeaveInfoServiceImpl.class);
	  private  LeaveInfoDao leaveInfoDao;
	  
	  private ClerkDAO clerkDAO;
	
	  private JdbcTemplate jdbcTemplate;
	  
	  private DepartmentDAO departmentDAO;
	  
	  private SysService sysService;
	  
	  
	  
	  public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}


	public void setLeaveInfoDao(LeaveInfoDao leaveInfoDao) {
		this.leaveInfoDao = leaveInfoDao;
	}
	  

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}


	public void setDepartmentDAO(DepartmentDAO departmentDAO) {
		this.departmentDAO = departmentDAO;
	}

	public void setClerkDAO(ClerkDAO clerkDAO) {
		this.clerkDAO = clerkDAO;
	}


	public void saveLeaveInfo(Leaveinfo leaveInfo)
	  {
		  
	  }

	  public Leaveinfo getLeaveInfoById(String leaveInfoId)
	  {
		  return leaveInfoDao.get(leaveInfoId);
	  }

	  public List getLeaveInfosByUserId(String userId)
	  {
		  return null;
	  }

	  public List getLeaveInfosByTime(Date startDate, Date endDate)
	  {
		  return null;
	  }
	  
	  public boolean checkIsLeaveByClerkId(Integer clerkId)throws Exception
	  {
		  Date date=new Date();
		  boolean flag=false;
		  String strCalendar=DateFormat.getDateInstance().format(date);

		  String sql=" from Leaveinfo linfo ,Leaveinfomap lmap where lmap.clerkid='"+clerkId+"'" +
		  		"and linfo.leaveinfoid=lmap.leaveinfoid " +
		  		"and linfo.startdate<='"+strCalendar+"' and linfo.enddate>='"+strCalendar+"'";
		  log.debug(sql);
		  List list=leaveInfoDao.find(sql);
		  if(list.isEmpty())
			  ;
		  else flag=true;
		  
		  
		  
		  return flag;
		  
	  }
	  public List searchLeaveInfo(Map filter)throws Exception
	  {
		  String hql;
		  hql=" from Leaveinfo  where  1=1 and clerk is not null and department is not null" ;
		  hql+=StringUtils.isNotEmpty((String)filter.get("startDate"))?" and startdate >='"+(String)filter.get("startDate")+"' ":"";
		  hql+=StringUtils.isNotEmpty((String)filter.get("endDate"))?" and enddate<='"+(String)filter.get("endDate")+"' ":"";
		  hql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and department.id='"+(String)filter.get("deptId")+"' ":"";
		  
		  hql+=" group by departid,leaveinfoid,description,startdate,enddate,clerkid order by enddate desc ";
		  
		  //log.debug("hql:"+hql);
		  
		  String sql;
		  sql="select " +
		  		"leave.STARTDATE as startdate ," +
		  		"leave.LEAVEINFOID as leaveinfoId," +
		  		"leave.ENDDATE as enddate, " +
		  		"leave.DESCRIPTION as description ," +
		  		"leave.RECORDDATE AS recordDate," +
		  		"dpart.DEPT_NAME AS departname ," +
		  		"dpart.DEPT_ID AS dept_id," +
		  		"cust.CUT_NAME AS clerkname ," +
		  		"(select card.CARD_ID from YKT_CUR.T_PIF_CARD card ,YKT_CUR.T_AIF_ACCOUNT account " +
		  		"where card.CARD_ID=account.CARD_ID and account.CUSTOMER_ID=cust.CUT_ID and card.STATE_ID='1000') AS cardnumber ," +
		  		"dict.DICT_CAPTION as isseat,conf.CONFNAME as confname ," +
		  		"(select a.account_name from YKT_CK.USR_ACCOUNT  a where a.id=leave.OPERATORID) as operatorName " +
		  		" from YKT_CK.LEAVEINFO leave ,YKT_CK.DEPARTMENT dpart ,YKT_CK.CLERK clerk,YKT_CK.WORKCONF conf ,YKT_CUR.T_CIF_CUSTOMER cust," +
		  		" YKT_CK.COM_DICTIONARY dict ,YKT_CK.WORKCONFMAP  map " +
		  		" where leave.DEPARTID=dpart.DEPT_ID AND clerk.CLERKID=leave.CLERKID AND  " +
		  		"   conf.WORKCONFID =map.WORKCONFID and  map.CLERKID=clerk.CLERKID " +
		  		" and  cust.CUT_ID=leave.CLERKID " +
		  		" AND dict.DICT_NO=1002 AND dict.DICT_VALUE=clerk.ISSEAT " ;
		  sql+=StringUtils.isNotEmpty((String)filter.get("startDate"))?" and leave.STARTDATE >='"+(String)filter.get("startDate")+" 00:00:00"+"' ":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get("endDate"))?" and leave.ENDDATE <='"+(String)filter.get("endDate")+" 23:59:59"+"' ":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and dpart.DEPT_ID='"+(String)filter.get("deptId")+"' ":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get("trueName"))?" and cust.CUT_NAME  like '%"+(String)filter.get("trueName")+"%' ":"";
		  
		  log.debug("sql:"+sql);
		  
		  List infoList2=jdbcTemplate.queryForList(sql);
		 
		  return infoList2;
	  }
	  
	  public List staticLeaveInfoByFilter(Map filter)throws Exception
	  {
		  List leaveInfoList= new ArrayList();
		  String hql="from ";
		  String sql="";
		  String lastValue="ini";
		  
		  
		  
		  sql="select " +
		  " leave.STARTDATE as startDate ,"+
		  		"leave.ENDDATE as endDate, " +
		  		"dpart.DEPT_NAME AS departname ," +
		  		" 0 as tatol ," +
		  		"dpart.DEPT_ID AS dept_id," +
		  		"cust.CUT_NAME AS clerkname ," +
		  		"cust.CUT_ID as cut_id," +
		  		"dict.DICT_CAPTION as isseat,conf.CONFNAME as confname " +
		  		" from YKT_CK.LEAVEINFO leave ,YKT_CK.DEPARTMENT dpart ,YKT_CK.CLERK clerk,YKT_CK.WORKCONF conf ,YKT_CUR.T_CIF_CUSTOMER cust," +
		  		" YKT_CK.COM_DICTIONARY dict ,YKT_CK.WORKCONFMAP  map " +
		  		" where leave.DEPARTID=dpart.DEPT_ID AND clerk.CLERKID=leave.CLERKID AND conf.WORKCONFID = " +
		  		"  map.WORKCONFID and  map.CLERKID=clerk.CLERKID " +
		  		" and  cust.CUT_ID=leave.CLERKID " +
		  		" AND dict.DICT_NO=1002 AND dict.DICT_VALUE=clerk.ISSEAT " ;
			  
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.trueName))?" and cust.CUT_NAME like '%"+(String)filter.get(CommonConfig.trueName)+"%' ":" ";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and leave.STARTDATE >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00"+"' ":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and leave.ENDDATE  <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59"+"' ":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and dpart.DEPT_ID='"+(String)filter.get("deptId")+"' ":"";
	      
	      sql+=" and leave.ENDDATE>=leave.STARTDATE" +
	      		" group by cust.CUT_ID,cust.CUT_NAME,leave.STARTDATE,leave.ENDDATE,dpart.DEPT_NAME,dpart.DEPT_ID,dict.DICT_CAPTION,conf.CONFNAME ";
	      
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
				   
				   Integer tatol=getLeaveDays(colMap);
				   
				   colMap.put("tatol",tatol);
				   
				   
				   leaveInfoList.add(colMap);				   
			   }
		   }

		  return leaveInfoList;
	  }
	  
	  public Integer getLeaveDays(Map filter)throws Exception
	  {
		  Integer tatol;
		  int temp=0;
		  String sql="select leave.STARTDATE AS startDate ,leave.ENDDATE as endDate from YKT_CK.LEAVEINFO leave where leave.CLERKID="+filter.get("cut_id")+
		  		" and leave.ENDDATE<='"+(String)filter.get("terminateDay")+" 23:59:59"+"' " +
		  		" and leave.STARTDATE>='"+(String)filter.get("beginDay")+" 00:00:00"+"' " +
		  		" and leave.STARTDATE<=leave.ENDDATE ";
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
	  
	  public List getLeaveInfoDetail(Map filter)throws Exception
	  {
		  String sql="select leave.STARTDATE as startDate,leave.ENDDATE as endDate,c.CUT_NAME as clerkname " +
		  		" from " +
		  		" YKT_CK.LEAVEINFO leave,YKT_CUR.T_CIF_CUSTOMER  c " +
		  		"where c.CUT_ID=leave.CLERKID ";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and leave.STARTDATE >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00"+"' ":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and leave.ENDDATE  <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59"+"' ":"";
	      sql+=StringUtils.isNotEmpty(((Integer)filter.get("clerkId")).toString())?" and leave.CLERKID  ="+(Integer)filter.get("clerkId"):"";
	      
	      sql+=" order by startDate asc ";
	      
	      log.debug("sql:"+sql);
	      
	      List leaveDetailList=jdbcTemplate.queryForList(sql);
	      
		  return leaveDetailList;
	  }
	  public List searchClerkForRegister(Map filter)throws Exception
	  {
		  String sql="select * from (" +
		  		"select " +
	  		"dpart.DEPT_NAME AS departname ," +
	  		"dpart.DEPT_ID AS dept_id," +
	  		"cust.CUT_NAME AS clerkname ," +
	  		"cust.CUT_ID AS cut_id," +
	  		"(select card.CARD_ID from YKT_CUR.T_PIF_CARD card ,YKT_CUR.T_AIF_ACCOUNT account " +
	  		"where card.CARD_ID=account.CARD_ID and account.CUSTOMER_ID=cust.CUT_ID and card.STATE_ID='1000') AS cardnumber ," +
	  		"dict.DICT_CAPTION as isseat,conf.CONFNAME as confname " +
	  		" from YKT_CK.DEPARTMENT dpart ,YKT_CK.CLERK clerk,YKT_CK.WORKCONF conf ,YKT_CUR.T_CIF_CUSTOMER cust," +
	  		" YKT_CK.COM_DICTIONARY dict  ,YKT_CK.WORKCONFMAP  map " +
	  		" where clerk.DEPARTMENTID=dpart.DEPT_ID  AND conf.WORKCONFID = " +
	  		"  map.WORKCONFID and  map.CLERKID=clerk.CLERKID " +
	  		" and  cust.CUT_ID=clerk.CLERKID " +
	  		" AND dict.DICT_NO=1002 AND dict.DICT_VALUE=clerk.ISSEAT) all where 1=1  " ;
		  
		  sql+=StringUtils.isNotEmpty((String)filter.get("trueName"))?" and all.clerkname like '%"+(String)filter.get("trueName")+"%' ":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get("cardNumber"))?" and all.cardnumber  ="+(String)filter.get("cardNumber")+" ":"";
		  
		  log.debug("sql:"+sql);
		  
		  List clerkList=jdbcTemplate.queryForList(sql);
		  
		  return clerkList;
	  }
	  public List addLeaveInfo(Map filter)throws Exception
	  {
		  log.debug("--------------->start_add<-----------");
		  String []checkValues;
		  log.debug("startDate------------------------------->");
		  log.debug("endDate--------------------------------->");
		  checkValues=(String[])filter.get("checkValues");
		  String startDate=(String)filter.get("startDate");
		  String endDate=(String)filter.get("endDate");
		  
		  startDate=startDate.replace('-','/');
		  endDate=endDate.replace('-','/');

		  
		  startDate=startDate+" "+(String)filter.get("startHour")+":"+(String)filter.get("startMin")+":00";
		  endDate=endDate+" "+(String)filter.get("endHour")+":"+(String)filter.get("endMin")+":00";
		  SimpleDateFormat sdf=new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
		  List leaveList=new ArrayList();
		  
		  
		  for(int i=0;i<checkValues.length;i++)
		  {
			  Map map=new HashMap();
			  Leaveinfo leaveinfo=new Leaveinfo();
			  Clerk clerk=clerkDAO.get(new Integer(checkValues[i]));
			  leaveinfo.setClerk(clerk);
			  leaveinfo.setDepartment(clerk.getDepartment());
			  leaveinfo.setDescription((String)filter.get("description"));
			  leaveinfo.setEnddate(sdf.parse(endDate));
			  leaveinfo.setStartdate(sdf.parse(startDate));
			  leaveinfo.setOperatorid((String)filter.get("operatorid"));
			  leaveinfo.setRecorddate(new Date());
			  leaveinfo.setFlag((String)filter.get("type"));
			  
			  map.put("clerkname",sysService.getCustomerNameByCustomerId(clerk.getClerkid()));
			  map.put("startdate",startDate);
			  map.put("enddate",endDate);
			  
			  leaveList.add(map);
			  
			  leaveInfoDao.save(leaveinfo);
		  }
		 
		  return leaveList;
	  }
	  
	  public void deleteLeaveInfo(String [] leaveInfoIds)throws Exception
	  {
		  log.debug("length------------------------------>"+leaveInfoIds.length);
		 for(int i=0;i<leaveInfoIds.length;i++)
		 {
			 Leaveinfo leaveinfo=leaveInfoDao.get(leaveInfoIds[i]);
			 leaveInfoDao.delete(leaveinfo);
		 }
	  }
	  public void updateLeaveInfo(Map filter)throws Exception
	  {
		  String startDate=(String)filter.get("startDate");
		  String endDate=(String)filter.get("endDate");
		  
		  startDate=startDate.replace('-','/');
		  endDate=endDate.replace('-','/');
		  
		  startDate=startDate+" "+(String)filter.get("startHour")+":"+(String)filter.get("startMin")+":00";
		  endDate=endDate+" "+(String)filter.get("endHour")+":"+(String)filter.get("endMin")+":00";
		  SimpleDateFormat sdf=new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
		  
		  Leaveinfo leaveinfo=leaveInfoDao.get((String)filter.get("leaveInfoId"));
		  leaveinfo.setEnddate(sdf.parse(endDate));
		  leaveinfo.setStartdate(sdf.parse(startDate));
		  leaveinfo.setDescription((String)filter.get("description"));
		  leaveinfo.setRecorddate(new Date());
		  
		  
		  leaveInfoDao.update(leaveinfo);
	  }
	  /*
	   *  (non-Javadoc)
	   * @see org.king.check.service.LeaveInfoService#isInLeave(java.util.Map)
	   * 判断考勤天是否在请假时段中
	   */
	  public List isInLeave(Map filter)throws Exception
	  {
		  String sql="select leave.STARTDATE as startDate,leave.ENDDATE as endDate,c.CUT_NAME as clerkname " +
	  		" from " +
	  		" YKT_CK.LEAVEINFO leave,YKT_CUR.T_CIF_CUSTOMER  c " +
	  		"where c.CUT_ID=leave.CLERKID ";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and leave.STARTDATE <='"+(String)filter.get(CommonConfig.startDate)+" 23:59:59"+"' ":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and leave.ENDDATE  >='"+(String)filter.get(CommonConfig.endDate)+" 00:00:00"+"' ":"";
		  sql+=StringUtils.isNotEmpty(((Integer)filter.get("clerkId")).toString())?" and leave.CLERKID  ="+(Integer)filter.get("clerkId"):"";
    
		  sql+=" order by startDate asc ";
    
		  log.debug("sql:"+sql);
    
		  List leaveDetailList=jdbcTemplate.queryForList(sql);
    
		  return leaveDetailList;
	  }
}
