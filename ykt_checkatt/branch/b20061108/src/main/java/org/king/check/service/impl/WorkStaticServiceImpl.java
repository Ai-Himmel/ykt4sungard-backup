package org.king.check.service.impl;

import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.config.CommonConfig;
import org.king.check.service.WorkStaticService;
import org.king.framework.service.impl.BaseService;
import org.springframework.jdbc.core.JdbcTemplate;

public class WorkStaticServiceImpl extends BaseService implements WorkStaticService{
	private static final Log log = LogFactory.getLog(WorkInfoServiceImpl.class);
	
	private  JdbcTemplate jdbcTemplate;
	
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}
	
	public List checklogByFilter(Map filter)throws Exception
	  {
		  List checklogList= new ArrayList();		  
		  String sql="";	
		  String startDate="";
		  String endDate="";
		  Date sDate=null;
		  Date eDate=null;
		  
		  java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat("yyyy-MM-dd");
		  java.text.SimpleDateFormat sdf1 = new java.text.SimpleDateFormat("yyyyMMdd");
		  
		  if(StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))){
			  String date=(String)filter.get(CommonConfig.startDate);
			  startDate=date.substring(0,4)+date.substring(5,7)+date.substring(8);
			  sDate=sdf.parse(date);
		  } 
		  
		  if(StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))){
			  String date=(String)filter.get(CommonConfig.endDate);
			  endDate=date.substring(0,4)+date.substring(5,7)+date.substring(8);
			  eDate=sdf.parse(date);
		  }
		  
		  sql="select CLERKID,CARDNUMBER,(info.CHECKDATE||' '||detail.DUTYCHECKDATE) as CHECKTIME,detail.INFOTYPE,dict.DICT_CAPTION as DESCRIPTION,detail.EXCEPTIONMINS from YKT_CK.WORKINFODETAILMAP map,YKT_CK.WORKINFODETAIL detail,YKT_CK.WORKINFO info,YKT_CK.COM_DICTIONARY dict where detail.DETAILID=map.DETAILID and info.WORKINFOID=map.WORKINFOID and dict.DICT_NO=1003 and dict.DICT_VALUE=detail.INFOTYPE";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and info.CHECKDATE >='"+startDate+"'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and info.CHECKDATE  <='"+endDate+"'":"";
	      sql+=" order by CLERKID,CHECKTIME";
	      
		  log.debug("sql:"+sql);
		  List workInfoList=jdbcTemplate.queryForList(sql);//出勤信息
		  
		  sql="select CLERKID,cust.CUT_NAME as clerkName,DEPT_NAME as deptName,cust.STUEMP_NO as STUNUMBER,CONFNAME,dict.DICT_CAPTION as isseatNAME from YKT_CUR.T_CIF_CUSTOMER cust,YKT_CK.CLERK clerk,YKT_CK.DEPARTMENT,YKT_CK.WORKTIMECONF worktimeconf,YKT_CK.COM_DICTIONARY dict where CLERKID=CUT_ID and DEPARTMENTID=DEPT_ID and clerk.WORKTIMECONFID=worktimeconf.WORKTIMECONFID and ISSEAT=dict.DICT_VALUE and dict.DICT_NO=1002 order by CLERKID";
		  		  
		  log.debug("sql:"+sql);
		  List clerkInfoList=jdbcTemplate.queryForList(sql);//考勤人员信息
		  
		  if(workInfoList!=null&&workInfoList.size()>0){
			  int k=0;
			  for(int i=0;i<workInfoList.size();i++){
				  Map colMap=(Map)workInfoList.get(i);
				  Integer clerkid=(Integer)colMap.get("CLERKID");
				  if(clerkInfoList!=null&&clerkInfoList.size()>0){
					  int j=k;
					  for(j=k;j<clerkInfoList.size();j++){
						  Map cMap=(Map)clerkInfoList.get(j);
						  Integer cid=(Integer)cMap.get("CLERKID");
						  if(cid.equals(clerkid)){
							  colMap.put("clerkName",cMap.get("clerkName"));
							  colMap.put("deptName",cMap.get("deptName"));
							  colMap.put("STUNUMBER",cMap.get("STUNUMBER"));
							  colMap.put("CONFNAME",cMap.get("CONFNAME"));
							  colMap.put("isseatName",cMap.get("isseatName"));
							  k=j;
							  break;
						  }
					  }
					  if(j==clerkInfoList.size()||j>clerkInfoList.size()){
						  colMap.put("clerkName","");
						  colMap.put("deptName","");
						  colMap.put("STUNUMBER","");
						  colMap.put("CONFNAME","");
						  colMap.put("isseatName","");
					  }
				  }
				  else{
					  colMap.put("clerkName","");
					  colMap.put("deptName","");
					  colMap.put("STUNUMBER","");
					  colMap.put("CONFNAME","");
					  colMap.put("isseatName","");
				  }
				  checklogList.add(colMap);

			  }
			  return checklogList;
		  }
		  else		  
		     return null;
		  
	  }
	
	public List clerkstaticByFilter(Map filter)throws Exception
	  {
		  List clerkstaticList= new ArrayList();		  
		  String sql="";	
		  String startDate="";
		  String endDate="";
		  Date sDate=null;
		  Date eDate=null;
		  
		  java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat("yyyy-MM-dd");
		  java.text.SimpleDateFormat sdf1 = new java.text.SimpleDateFormat("yyyyMMdd");
		  
		  if(StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))){
			  String date=(String)filter.get(CommonConfig.startDate);
			  startDate=date.substring(0,4)+date.substring(5,7)+date.substring(8);
			  sDate=sdf.parse(date);
		  } 
		  
		  if(StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))){
			  String date=(String)filter.get(CommonConfig.endDate);
			  endDate=date.substring(0,4)+date.substring(5,7)+date.substring(8);
			  eDate=sdf.parse(date);
		  }
		  
		  sql="select WORKINFOID,CHECKDATE,CHECKDATE as STARTDATE,DESCRIPTION,WORKINFOTYPE,CLERKID from YKT_CK.WORKINFO where 1>0";
		  sql+=StringUtils.isNotEmpty((String)filter.get("personCode"))?" and CLERKID ="+(String)filter.get("personCode"):"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and CHECKDATE >='"+startDate+"'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and CHECKDATE  <='"+endDate+"'":"";
	      sql+=" order by CHECKDATE";
	      
		  log.debug("sql:"+sql);
		  List workInfoList=jdbcTemplate.queryForList(sql);//出勤信息
		  
		  sql="select info.EXTRAINFOID,'加班' as DESCRIPTION,DATE(STARTDATE) as STARTDATE,DATE(ENDDATE) as ENDDATE,char(DATE(STARTDATE))||' '||char(TIME(STARTDATE))||'-'||char(DATE(ENDDATE))||' '||char(TIME(ENDDATE)) as CHECKPERIOD, RECORDDATE,CLERKID,OPERATORID from YKT_CK.EXTRAWORKINFO info,YKT_CK.EXTRAWORKINFOMAP map where info.EXTRAINFOID=map.EXTRAINFOID";
		  sql+=StringUtils.isNotEmpty((String)filter.get("personCode"))?" and CLERKID ="+(String)filter.get("personCode"):"";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and (STARTDATE <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and ENDDATE  >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00')":"";
	      sql+=" order by STARTDATE";
		  
	      log.debug("sql:"+sql);
		  List extraInfoList=jdbcTemplate.queryForList(sql);//加班信息
		  
		  sql="select rest.IRREGULARRESTID,'特殊休息' as DESCRIPTION, DATE(STARTDATE) as STARTDATE,DATE(ENDDATE) as ENDDATE,char(DATE(STARTDATE))||' '||char(TIME(STARTDATE))||'-'||char(DATE(ENDDATE))||' '||char(TIME(ENDDATE)) as CHECKPERIOD,CLERKID,OPERATORID, RECORDDATE from YKT_CK.IRREGULARREST rest,YKT_CK.IRREGULARRESTMAP map where rest.IRREGULARRESTID=map.IRREGULARRESTID";
		  sql+=StringUtils.isNotEmpty((String)filter.get("personCode"))?" and CLERKID ="+(String)filter.get("personCode"):"";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and (STARTDATE <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and ENDDATE  >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00')":"";
	      sql+=" order by STARTDATE";
		  
	      log.debug("sql:"+sql);
		  List irregularInfoList=jdbcTemplate.queryForList(sql);//特殊休息信息
		  
		  sql="select LEAVEINFOID,'请假' as DESCRIPTION, DATE(STARTDATE) as STARTDATE,DATE(ENDDATE) as ENDDATE,char(DATE(STARTDATE))||' '||char(TIME(STARTDATE))||'-'||char(DATE(ENDDATE))||' '||char(TIME(ENDDATE)) as CHECKPERIOD, RECORDDATE, OPERATORID,CLERKID,DEPARTID,FLAG from YKT_CK.LEAVEINFO where FLAG='0'";
		  sql+=StringUtils.isNotEmpty((String)filter.get("personCode"))?" and CLERKID ="+(String)filter.get("personCode"):"";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and (STARTDATE <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and ENDDATE  >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00')":"";
	      sql+=" order by STARTDATE";
		  
	      log.debug("sql:"+sql);
		  List leaveInfoList=jdbcTemplate.queryForList(sql);//请假信息
		  
		  sql="select LEAVEINFOID, '出差' as DESCRIPTION, DATE(STARTDATE) as STARTDATE,DATE(ENDDATE) as ENDDATE,char(DATE(STARTDATE))||' '||char(TIME(STARTDATE))||'-'||char(DATE(ENDDATE))||' '||char(TIME(ENDDATE)) as CHECKPERIOD, RECORDDATE, OPERATORID,CLERKID,DEPARTID,FLAG from YKT_CK.LEAVEINFO where FLAG='1'";
		  sql+=StringUtils.isNotEmpty((String)filter.get("personCode"))?" and CLERKID ="+(String)filter.get("personCode"):"";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and (STARTDATE <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and ENDDATE  >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00')":"";
	      sql+=" order by STARTDATE";
		  
	      log.debug("sql:"+sql);
		  List outInfoList=jdbcTemplate.queryForList(sql);//出差信息
		  
		  if(!workInfoList.isEmpty())
		   {  //System.out.println("workInfoList size:"+workInfoList.size());
			  for(int i=0;i<workInfoList.size();i++){
				   Map colMap=(Map)workInfoList.get(i);
				   clerkstaticList.add(colMap);				   
			   }
		   }
		  if(!extraInfoList.isEmpty())
		   {
			  Iterator staticIte=extraInfoList.iterator();
			   while(staticIte.hasNext())
			   {
				   Map colMap=(Map)staticIte.next();				   
				  
				   String osd=colMap.get("STARTDATE").toString();
				   String oed=colMap.get("ENDDATE").toString();
				   	
			       Date sd = sdf.parse(osd);
			       Date ed=sdf.parse(oed);
			       Calendar calendar = Calendar.getInstance();
			       calendar.setTime(sd);
			       
			       String nsd=sdf1.format(sd);			       			       
			       while(!sd.after(ed)&&!sd.after(eDate)){//拆分日期段，每天生成一条记录
			    	   Map newMap=new HashMap(colMap); 			    	   
			    	   if(sd.before(sDate)){
			    		   sd=sDate;
			    		   calendar.setTime(sd);
			    		   nsd=sdf1.format(sDate);
			    	   }
			    	   newMap.put("CHECKDATE",nsd);				    	   
			    	   clerkstaticList.add(newMap);	
			    	   
			    	   calendar.add(Calendar.DATE,1);
			    	   sd=calendar.getTime();
			    	   nsd=sdf1.format(sd);			    	   			    	   
			       }				   
			   } 
		   }
		  if(!irregularInfoList.isEmpty())
		   {
			  Iterator staticIte=irregularInfoList.iterator();
			   while(staticIte.hasNext())
			   {
				   Map colMap=(Map)staticIte.next();				   
				  
				   String osd=colMap.get("STARTDATE").toString();
				   String oed=colMap.get("ENDDATE").toString();
				   	
			       Date sd = sdf.parse(osd);
			       Date ed=sdf.parse(oed);
			       Calendar calendar = Calendar.getInstance();
			       calendar.setTime(sd);
			       
			       String nsd=sdf1.format(sd);			       			       
			       while(!sd.after(ed)&&!sd.after(eDate)){//拆分日期段，每天生成一条记录
			    	   Map newMap=new HashMap(colMap); 			    	   
			    	   if(sd.before(sDate)){
			    		   sd=sDate;
			    		   calendar.setTime(sd);
			    		   nsd=sdf1.format(sDate);
			    	   }
			    	   newMap.put("CHECKDATE",nsd);				    	   
			    	   clerkstaticList.add(newMap);	
			    	   
			    	   calendar.add(Calendar.DATE,1);
			    	   sd=calendar.getTime();
			    	   nsd=sdf1.format(sd);			    	   			    	   
			       }				   
			   }
		   }
		  if(!leaveInfoList.isEmpty())
		   {
			  Iterator staticIte=leaveInfoList.iterator();
			   while(staticIte.hasNext())
			   {
				   Map colMap=(Map)staticIte.next();				   
				  
				   String osd=colMap.get("STARTDATE").toString();
				   String oed=colMap.get("ENDDATE").toString();
				   	
			       Date sd = sdf.parse(osd);
			       Date ed=sdf.parse(oed);
			       Calendar calendar = Calendar.getInstance();
			       calendar.setTime(sd);
			       
			       String nsd=sdf1.format(sd);			       			       
			       while(!sd.after(ed)&&!sd.after(eDate)){//拆分日期段，每天生成一条记录
			    	   Map newMap=new HashMap(colMap); 			    	   
			    	   if(sd.before(sDate)){
			    		   sd=sDate;
			    		   calendar.setTime(sd);
			    		   nsd=sdf1.format(sDate);
			    	   }
			    	   newMap.put("CHECKDATE",nsd);				    	   
			    	   clerkstaticList.add(newMap);	
			    	   
			    	   calendar.add(Calendar.DATE,1);
			    	   sd=calendar.getTime();
			    	   nsd=sdf1.format(sd);			    	   			    	   
			       }			   
			   }
		   }
		  if(!outInfoList.isEmpty())
		   {
			  Iterator staticIte=outInfoList.iterator();
			   while(staticIte.hasNext())
			   {
				   Map colMap=(Map)staticIte.next();				   
				  
				   String osd=colMap.get("STARTDATE").toString();
				   String oed=colMap.get("ENDDATE").toString();
				   	
			       Date sd = sdf.parse(osd);
			       Date ed=sdf.parse(oed);
			       Calendar calendar = Calendar.getInstance();
			       calendar.setTime(sd);
			       
			       String nsd=sdf1.format(sd);			       			       
			       while(!sd.after(ed)&&!sd.after(eDate)){//拆分日期段，每天生成一条记录
			    	   Map newMap=new HashMap(colMap); 			    	   
			    	   if(sd.before(sDate)){
			    		   sd=sDate;
			    		   calendar.setTime(sd);
			    		   nsd=sdf1.format(sDate);
			    	   }
			    	   newMap.put("CHECKDATE",nsd);				    	   
			    	   clerkstaticList.add(newMap);	
			    	   
			    	   calendar.add(Calendar.DATE,1);
			    	   sd=calendar.getTime();
			    	   nsd=sdf1.format(sd);			    	   			    	   
			       }			   
			   }
		   }
		  
		  //按CHECKDATE日期排序
		  Comparator comp1 = new Comparator() { 
				 public int compare(Object o1, Object o2){ 
				 Map m1 = (Map)o1; 
				 Map m2 = (Map)o2; 
				 String d1 = m1.get("CHECKDATE").toString(); 
				 String d2 = m2.get("CHECKDATE").toString(); 
				
				 return d1.compareTo(d2); 
				 
				 } 
				} ;				
			 Collections.sort(clerkstaticList, comp1);
		 
		if(!clerkstaticList.isEmpty())
		     return clerkstaticList;
		else
			return null;
	  }
	
	public List clerkstaticDetail(String checkdate,String clerkid,String flag)throws Exception
	  {
		String sql="";
		String cdate=checkdate.substring(0,4)+"-"+checkdate.substring(4,6)+"-"+checkdate.substring(6);
		
		if(flag.equals("0"))//出勤
		    sql="select info.CLERKID,(info.CHECKDATE||' '||detail.DUTYCHECKDATE) as CHECKDATE,detail.INFOTYPE,dict.DICT_CAPTION as DESCRIPTION,detail.EXCEPTIONMINS from YKT_CK.WORKINFODETAILMAP map,YKT_CK.WORKINFODETAIL detail,YKT_CK.WORKINFO info,YKT_CK.COM_DICTIONARY dict where detail.DETAILID=map.DETAILID and info.WORKINFOID=map.WORKINFOID and dict.DICT_NO=1003 and dict.DICT_VALUE=detail.INFOTYPE and info.CLERKID="+clerkid+" and info.CHECKDATE='"+checkdate+"'";
		else if(flag.equals("1"))//加班
			sql="select info.EXTRAINFOID,'"+checkdate+"' as CHECKDATE,char(DATE(STARTDATE))||' '||char(TIME(STARTDATE))||'-'||char(DATE(ENDDATE))||' '||char(TIME(ENDDATE))||'加班' as DESCRIPTION,'---' as EXCEPTIONMINS,RECORDDATE,CLERKID,OPERATORID from YKT_CK.EXTRAWORKINFO info,YKT_CK.EXTRAWORKINFOMAP map where info.EXTRAINFOID=map.EXTRAINFOID and CLERKID ="+clerkid+" and STARTDATE <='"+cdate+" 23:59:59' and ENDDATE  >='"+cdate+" 00:00:00'";
		else if(flag.equals("2"))//特殊休息
			sql="select rest.IRREGULARRESTID,'"+checkdate+"' as CHECKDATE,char(DATE(STARTDATE))||' '||char(TIME(STARTDATE))||'-'||char(DATE(ENDDATE))||' '||char(TIME(ENDDATE))||'特殊休息' as DESCRIPTION,'---' as EXCEPTIONMINS,RECORDDATE,CLERKID,OPERATORID from YKT_CK.IRREGULARREST rest,YKT_CK.IRREGULARRESTMAP map where rest.IRREGULARRESTID=map.IRREGULARRESTID and CLERKID ="+clerkid+" and STARTDATE <='"+cdate+" 23:59:59' and ENDDATE  >='"+cdate+" 00:00:00'";
		else if(flag.equals("3"))//请假
			sql="select LEAVEINFOID,'"+checkdate+"' as CHECKDATE,DESCRIPTION,'---' as EXCEPTIONMINS,RECORDDATE, OPERATORID,CLERKID,DEPARTID,FLAG from YKT_CK.LEAVEINFO where FLAG='0' and CLERKID ="+clerkid+" and STARTDATE <='"+cdate+" 23:59:59' and ENDDATE  >='"+cdate+" 00:00:00'";		
		else if(flag.equals("4"))//出差
			sql="select LEAVEINFOID,'"+checkdate+"' as CHECKDATE,DESCRIPTION,'---' as EXCEPTIONMINS,RECORDDATE, OPERATORID,CLERKID,DEPARTID,FLAG from YKT_CK.LEAVEINFO where FLAG='1' and CLERKID ="+clerkid+" and STARTDATE <='"+cdate+" 23:59:59' and ENDDATE  >='"+cdate+" 00:00:00'";
		
		log.debug("sql:"+sql);
		List detailInfoList=jdbcTemplate.queryForList(sql);//详细信息
		
		return detailInfoList;
	  }
	
	public List getclerkInfo(String clerkid)throws Exception	
	  {
		String sql="";
		sql="select CLERKID, cust.CUT_NAME as clerkName,DEPT_ID,DEPT_NAME as deptName,card.CARD_ID as cardId from YKT_CUR.T_CIF_CUSTOMER cust,YKT_CK.CLERK,YKT_CK.DEPARTMENT,YKT_CUR.T_PIF_CARD card ,YKT_CUR.T_AIF_ACCOUNT account	where CLERKID=CUT_ID and DEPARTMENTID=DEPT_ID and card.CARD_ID=account.CARD_ID and account.CUSTOMER_ID=cust.CUT_ID and card.STATE_ID='1000' and CLERKID="+clerkid;
		
		log.debug("sql:"+sql);
		List clerkInfoList=jdbcTemplate.queryForList(sql);
		
		if(!clerkInfoList.isEmpty())
			return clerkInfoList;
		else
			return null;
	  }
	
	public String getclerkId(String stuNo)throws Exception	
	  {
		String sql="";
		sql="select CUT_ID as CLERKID,STUEMP_NO as STUNUMBER from YKT_CUR.T_CIF_CUSTOMER where STUEMP_NO='"+stuNo+"'";
		
		log.debug("sql:"+sql);
		List clerkInfoList=jdbcTemplate.queryForList(sql);
		
		if(!clerkInfoList.isEmpty())
			return ((Integer)((Map)clerkInfoList.get(0)).get("CLERKID")).toString();		
		else
			return null;
	  }
	  
	public Map sumstaticByFilter(Map filter)throws Exception
	  {
		  Map sumstaticList= new HashMap();		  
		  String sql="";	
		  String startDate="";
		  String endDate="";
		  Date sDate=null;
		  Date eDate=null;	
		  
		  java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat("yyyy-MM-dd");
		   
		  if(StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))){
			  String date=(String)filter.get(CommonConfig.startDate);
			  startDate=date.substring(0,4)+date.substring(5,7)+date.substring(8);
			  sDate=sdf.parse(date);
		  } 
		  
		  if(StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))){
			  String date=(String)filter.get(CommonConfig.endDate);
			  endDate=date.substring(0,4)+date.substring(5,7)+date.substring(8);
			  eDate=sdf.parse(date);
		  }
			  
		  sql="select count(WORKINFOID) as workNum from YKT_CK.WORKINFO where (not WORKINFOTYPE='4')";
		  sql+=StringUtils.isNotEmpty((String)filter.get("personCode"))?" and CLERKID ="+(String)filter.get("personCode"):"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and CHECKDATE >='"+startDate+"'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and CHECKDATE  <='"+endDate+"'":"";	      
	      
		  log.debug("sql:"+sql);
		  List workInfoList=jdbcTemplate.queryForList(sql);//出勤天数
		  
		  if(!workInfoList.isEmpty())
			  sumstaticList.put("workNum",((Map)workInfoList.get(0)).get("workNum"));
		  
		  sql="select count(WORKINFOID) as notworkNum from YKT_CK.WORKINFO where WORKINFOTYPE='4'";
		  sql+=StringUtils.isNotEmpty((String)filter.get("personCode"))?" and CLERKID ="+(String)filter.get("personCode"):"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and CHECKDATE >='"+startDate+"'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and CHECKDATE  <='"+endDate+"'":"";	      
	      
		  log.debug("sql:"+sql);
		  List notworkInfoList=jdbcTemplate.queryForList(sql);//旷工天数
		  
		  if(!notworkInfoList.isEmpty())
			  sumstaticList.put("notworkNum",((Map)notworkInfoList.get(0)).get("notworkNum"));
		  
		  List tempInfoList=new ArrayList();		  
		  
		  sql="select info.EXTRAINFOID, CLERKID,DATE(STARTDATE) as STARTDATE,DATE(ENDDATE) as ENDDATE, RECORDDATE, OPERATORID from YKT_CK.EXTRAWORKINFO info,YKT_CK.EXTRAWORKINFOMAP map where info.EXTRAINFOID=map.EXTRAINFOID";
		  sql+=StringUtils.isNotEmpty((String)filter.get("personCode"))?" and CLERKID ="+(String)filter.get("personCode"):"";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and (STARTDATE <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and ENDDATE  >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00')":"";
	      	      
		  log.debug("sql:"+sql);
		  tempInfoList=jdbcTemplate.queryForList(sql);//加班记录
		  
		  if(!tempInfoList.isEmpty()){
			  int totalNum=0;			  
			  Iterator staticIte=tempInfoList.iterator();			  
			   while(staticIte.hasNext())
			   {
				   Map colMap=(Map)staticIte.next();
				   Date sd=(Date)colMap.get("STARTDATE");
				   Date ed=(Date)colMap.get("ENDDATE");
				   
				   if(sd.before(sDate)&&!ed.before(sDate)&&!ed.after(eDate)){
					   int num=(int)((ed.getTime()-sDate.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;
				   }
				   if(sd.after(sDate)&&!ed.after(eDate)||!sd.before(sDate)&&ed.before(eDate)){
					   int num=(int)((ed.getTime()-sd.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;					   
				   }				   
				   if(!sd.before(sDate)&&!sd.after(eDate)&&ed.after(eDate)){
					   int num=(int)((eDate.getTime()-sd.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;
				   }
				   if(sd.before(sDate)&&ed.after(eDate)||sd.equals(sDate)&&ed.equals(eDate)){
					   int num=(int)((eDate.getTime()-sDate.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;
				   }  
				   
			   }
			   sumstaticList.put("extraNum",new Integer(totalNum));
			   
		  }
		  
		  sql="select rest.IRREGULARRESTID, DATE(STARTDATE) as STARTDATE,DATE(ENDDATE) as ENDDATE,OPERATORID, RECORDDATE from YKT_CK.IRREGULARREST rest,YKT_CK.IRREGULARRESTMAP map where rest.IRREGULARRESTID=map.IRREGULARRESTID";
		  sql+=StringUtils.isNotEmpty((String)filter.get("personCode"))?" and CLERKID ="+(String)filter.get("personCode"):"";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and (STARTDATE <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and ENDDATE  >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00')":"";
	      	      
		  log.debug("sql:"+sql);
		  tempInfoList=jdbcTemplate.queryForList(sql);//特殊休息记录
		  
		  if(!tempInfoList.isEmpty()){
			  int totalNum=0;			  
			  Iterator staticIte=tempInfoList.iterator();			  
			   while(staticIte.hasNext())
			   {
				   Map colMap=(Map)staticIte.next();
				   Date sd=(Date)colMap.get("STARTDATE");
				   Date ed=(Date)colMap.get("ENDDATE");
				   
				   if(sd.before(sDate)&&!ed.before(sDate)&&!ed.after(eDate)){
					   int num=(int)((ed.getTime()-sDate.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;
				   }
				   if(sd.after(sDate)&&!ed.after(eDate)||!sd.before(sDate)&&ed.before(eDate)){
					   int num=(int)((ed.getTime()-sd.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;					   
				   }				   
				   if(!sd.before(sDate)&&!sd.after(eDate)&&ed.after(eDate)){
					   int num=(int)((eDate.getTime()-sd.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;
				   }
				   if(sd.before(sDate)&&ed.after(eDate)||sd.equals(sDate)&&ed.equals(eDate)){
					   int num=(int)((eDate.getTime()-sDate.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;
				   }
				   
			   }
			   sumstaticList.put("irregularNum",new Integer(totalNum));
			   
		  }
		  
		  sql="select LEAVEINFOID,CLERKID,DATE(STARTDATE) as STARTDATE,DATE(ENDDATE) as ENDDATE, RECORDDATE, OPERATORID from YKT_CK.LEAVEINFO where FLAG='0'";
		  sql+=StringUtils.isNotEmpty((String)filter.get("personCode"))?" and CLERKID ="+(String)filter.get("personCode"):"";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and (STARTDATE <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and ENDDATE  >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00')":"";
	      	      
		  log.debug("sql:"+sql);
		  tempInfoList=jdbcTemplate.queryForList(sql);//请假记录
		  
		  if(!tempInfoList.isEmpty()){
			  int totalNum=0;			  
			  Iterator staticIte=tempInfoList.iterator();			  
			   while(staticIte.hasNext())
			   {
				   Map colMap=(Map)staticIte.next();
				   Date sd=(Date)colMap.get("STARTDATE");
				   Date ed=(Date)colMap.get("ENDDATE");
				   
				   if(sd.before(sDate)&&!ed.before(sDate)&&!ed.after(eDate)){
					   int num=(int)((ed.getTime()-sDate.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;
				   }
				   if(sd.after(sDate)&&!ed.after(eDate)||!sd.before(sDate)&&ed.before(eDate)){
					   int num=(int)((ed.getTime()-sd.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;					   
				   }				   
				   if(!sd.before(sDate)&&!sd.after(eDate)&&ed.after(eDate)){
					   int num=(int)((eDate.getTime()-sd.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;
				   }
				   if(sd.before(sDate)&&ed.after(eDate)||sd.equals(sDate)&&ed.equals(eDate)){
					   int num=(int)((eDate.getTime()-sDate.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;
				   }  
				   
			   }
			   sumstaticList.put("leaveNum",new Integer(totalNum));
			   
		  }
		  
		  sql="select LEAVEINFOID,CLERKID,DATE(STARTDATE) as STARTDATE,DATE(ENDDATE) as ENDDATE, RECORDDATE, OPERATORID from YKT_CK.LEAVEINFO where FLAG='1'";
		  sql+=StringUtils.isNotEmpty((String)filter.get("personCode"))?" and CLERKID ="+(String)filter.get("personCode"):"";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and (STARTDATE <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and ENDDATE  >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00')":"";
	      	      
		  log.debug("sql:"+sql);
		  tempInfoList=jdbcTemplate.queryForList(sql);//出差记录
		  
		  if(!tempInfoList.isEmpty()){
			  int totalNum=0;			  
			  Iterator staticIte=tempInfoList.iterator();			  
			   while(staticIte.hasNext())
			   {
				   Map colMap=(Map)staticIte.next();
				   Date sd=(Date)colMap.get("STARTDATE");
				   Date ed=(Date)colMap.get("ENDDATE");
				   
				   if(sd.before(sDate)&&!ed.before(sDate)&&!ed.after(eDate)){
					   int num=(int)((ed.getTime()-sDate.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;
				   }
				   if(sd.after(sDate)&&!ed.after(eDate)||!sd.before(sDate)&&ed.before(eDate)){
					   int num=(int)((ed.getTime()-sd.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;					   
				   }				   
				   if(!sd.before(sDate)&&!sd.after(eDate)&&ed.after(eDate)){
					   int num=(int)((eDate.getTime()-sd.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;
				   }
				   if(sd.before(sDate)&&ed.after(eDate)||sd.equals(sDate)&&ed.equals(eDate)){
					   int num=(int)((eDate.getTime()-sDate.getTime())/(1000*60*60*24)+0.5)+1;
					   totalNum+=num;
				   }  
				   
			   }
			   sumstaticList.put("outNum",new Integer(totalNum));
			   
		  }
		  
		  if(!sumstaticList.isEmpty())
			  return sumstaticList;
		  else		  
		      return null;
	  }
	
	public List deptstaticByFilter(Map filter)throws Exception
	  {
		  List deptstaticList= new ArrayList();		  
		  String sql="";	
		  String startDate="";
		  String endDate="";
		  Date sDate=null;
		  Date eDate=null;
		  double datePeriod=0.00;
		  
		  java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat("yyyy-MM-dd");
		  java.text.SimpleDateFormat sdf1 = new java.text.SimpleDateFormat("yyyyMMdd");
		  NumberFormat nf = NumberFormat.getInstance();
		  nf.setMaximumFractionDigits(0);
		  
		  if(StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))){
			  String date=(String)filter.get(CommonConfig.startDate);
			  startDate=date.substring(0,4)+date.substring(5,7)+date.substring(8);
			  sDate=sdf.parse(date);
		  } 
		  
		  if(StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))){
			  String date=(String)filter.get(CommonConfig.endDate);
			  endDate=date.substring(0,4)+date.substring(5,7)+date.substring(8);
			  eDate=sdf.parse(date);
		  }
		  
	  if(sDate!=null&&eDate!=null){
		  
		  datePeriod=((eDate.getTime()-sDate.getTime())/(1000*60*60*24)+0.5)+1;//统计天数
		  
		  sql="select CLERKID,count(CHECKDATE) as checkNum,count(CHECKDATE)*100/"+datePeriod+" as checkPer from YKT_CK.WORKINFO where not WORKINFOTYPE='4'";
		  sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and DEPTID ='"+(String)filter.get("deptId")+"'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and CHECKDATE >='"+startDate+"'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and CHECKDATE  <='"+endDate+"'":"";
	      sql+=" group by CLERKID";
	      
		  log.debug("sql:"+sql);
		  List workInfoList=jdbcTemplate.queryForList(sql);//出勤统计
		  
		  sql="select CLERKID,count(CHECKDATE) as notcheckNum,count(CHECKDATE)*100/"+datePeriod+" as notcheckPer from YKT_CK.WORKINFO where WORKINFOTYPE='4'";
		  sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and DEPTID ='"+(String)filter.get("deptId")+"'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and CHECKDATE >='"+startDate+"'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and CHECKDATE  <='"+endDate+"'":"";
	      sql+=" group by CLERKID";
	      
		  log.debug("sql:"+sql);
		  List notworkInfoList=jdbcTemplate.queryForList(sql);//旷工统计
		  
		  sql="select info.CLERKID,count(info.CHECKDATE) as lateNum,count(info.CHECKDATE)*100/"+datePeriod+" as latePer from YKT_CK.WORKINFODETAILMAP map,YKT_CK.WORKINFODETAIL detail,YKT_CK.WORKINFO info where detail.DETAILID=map.DETAILID and info.WORKINFOID=map.WORKINFOID and detail.INFOTYPE='1'";
		  sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and DEPTID ='"+(String)filter.get("deptId")+"'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and info.CHECKDATE >='"+startDate+"'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and info.CHECKDATE  <='"+endDate+"'":"";
	      sql+=" group by info.CLERKID";
	      
		  log.debug("sql:"+sql);
		  List lateInfoList=jdbcTemplate.queryForList(sql);//迟到统计
		  
		  sql="select info.CLERKID,count(info.CHECKDATE) as earlyNum,count(info.CHECKDATE)*100/"+datePeriod+" as earlyPer from YKT_CK.WORKINFODETAILMAP map,YKT_CK.WORKINFODETAIL detail,YKT_CK.WORKINFO info where detail.DETAILID=map.DETAILID and info.WORKINFOID=map.WORKINFOID and detail.INFOTYPE='2'";
		  sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and DEPTID ='"+(String)filter.get("deptId")+"'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and info.CHECKDATE >='"+startDate+"'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and info.CHECKDATE  <='"+endDate+"'":"";
	      sql+=" group by info.CLERKID";
	      
		  log.debug("sql:"+sql);
		  List earlyInfoList=jdbcTemplate.queryForList(sql);//早退统计
		  
		  sql="select map.CLERKID,DATE(STARTDATE) as STARTDATE,DATE(ENDDATE) as ENDDATE from YKT_CK.EXTRAWORKINFO info,YKT_CK.EXTRAWORKINFOMAP map,YKT_CK.CLERK clerk where info.EXTRAINFOID=map.EXTRAINFOID and map.CLERKID=clerk.CLERKID";
		  sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and DEPARTMENTID ='"+(String)filter.get("deptId")+"'":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and (STARTDATE <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and ENDDATE  >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00')":"";
	      	      
		  log.debug("sql:"+sql);
		  List extraInfoList=jdbcTemplate.queryForList(sql);//加班信息
		  
		  sql="select map.CLERKID,DATE(STARTDATE) as STARTDATE,DATE(ENDDATE) as ENDDATE from YKT_CK.IRREGULARREST rest,YKT_CK.IRREGULARRESTMAP map,YKT_CK.CLERK clerk where rest.IRREGULARRESTID=map.IRREGULARRESTID and map.CLERKID=clerk.CLERKID";
		  sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and DEPARTMENTID ='"+(String)filter.get("deptId")+"'":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and (STARTDATE <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and ENDDATE  >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00')":"";
	      	      
		  log.debug("sql:"+sql);
		  List irregularInfoList=jdbcTemplate.queryForList(sql);//特休信息
		  
		  sql="select CLERKID,DATE(STARTDATE) as STARTDATE,DATE(ENDDATE) as ENDDATE from YKT_CK.LEAVEINFO where FLAG='0'";
		  sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and DEPARTID ='"+(String)filter.get("deptId")+"'":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and (STARTDATE <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and ENDDATE  >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00')":"";
	      	      
		  log.debug("sql:"+sql);
		  List leaveInfoList=jdbcTemplate.queryForList(sql);//请假信息
		  
		  sql="select CLERKID,DATE(STARTDATE) as STARTDATE,DATE(ENDDATE) as ENDDATE from YKT_CK.LEAVEINFO where FLAG='1'";
		  sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and DEPARTID ='"+(String)filter.get("deptId")+"'":"";
		  sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.startDate))?" and (STARTDATE <='"+(String)filter.get(CommonConfig.endDate)+" 23:59:59'":"";
	      sql+=StringUtils.isNotEmpty((String)filter.get(CommonConfig.endDate))?" and ENDDATE  >='"+(String)filter.get(CommonConfig.startDate)+" 00:00:00')":"";
	      	      
		  log.debug("sql:"+sql);
		  List outInfoList=jdbcTemplate.queryForList(sql);//出差信息
		  
		  //部门中的所有clerk信息
		  deptstaticList=getAllClerkinDept((String)filter.get("deptId"));
		  
		  if(deptstaticList!=null&&deptstaticList.size()>0){
			  
			 for(int i=0;i<deptstaticList.size();i++){
			   Map colMap=(Map)deptstaticList.get(i);
			   Integer clerkid=(Integer)colMap.get("CLERKID");
					   
			   if(!workInfoList.isEmpty()){
				       int j=0;
					   for(j=0;j<workInfoList.size();j++){
						   Map cMap=(Map)workInfoList.get(j);
						   Integer cid=(Integer)cMap.get("CLERKID");
						   if(cid.equals(clerkid)){
							   colMap.put("checkNum",cMap.get("checkNum"));							   
							   colMap.put("checkPer",nf.format(cMap.get("checkPer"))+"%");
							   break;
						   }
							   
					   }
					   if(j>=workInfoList.size()){
						   colMap.put("checkNum",new Integer(0));
						   colMap.put("checkPer","0%");
					   }
				}
			   else{
				   colMap.put("checkNum",new Integer(0));
				   colMap.put("checkPer","0%");
			   }
			   
				if(!notworkInfoList.isEmpty()){
					      int j=0;
						  for(j=0;j<notworkInfoList.size();j++){
							   Map cMap=(Map)notworkInfoList.get(j);
							   Integer cid=(Integer)cMap.get("CLERKID");
							   if(cid.equals(clerkid)){
								   colMap.put("notcheckNum",cMap.get("notcheckNum"));								   
								   colMap.put("notcheckPer",nf.format(cMap.get("notcheckPer"))+"%");
								   break;
							   }			   
						   }
						  if(j>=notworkInfoList.size()){
							   colMap.put("notcheckNum",new Integer(0));
							   colMap.put("notcheckPer","0%");
						   }
				}
				else{
					colMap.put("notcheckNum",new Integer(0));
					colMap.put("notcheckPer","0%");
				}
					  
				if(!lateInfoList.isEmpty()){ 
					      int j=0;
						  for(j=0;j<lateInfoList.size();j++){
							   Map cMap=(Map)lateInfoList.get(j);
							   Integer cid=(Integer)cMap.get("CLERKID");
							   if(cid.equals(clerkid)){
								   colMap.put("lateNum",cMap.get("lateNum"));								   
								   colMap.put("latePer",nf.format(cMap.get("latePer"))+"%");
								   break;
							   }			   
						   }
						  if(j>=lateInfoList.size()){
							   colMap.put("lateNum",new Integer(0));
							   colMap.put("latePer","0%");
						   }
				}
				else{
					colMap.put("lateNum",new Integer(0));
					colMap.put("latePer","0%");
				}
					  
				if(!earlyInfoList.isEmpty()){ 
					      int j=0;
						  for(j=0;j<earlyInfoList.size();j++){
							   Map cMap=(Map)earlyInfoList.get(j);
							   Integer cid=(Integer)cMap.get("CLERKID");
							   if(cid.equals(clerkid)){
								   colMap.put("earlyNum",cMap.get("earlyNum"));								 
								   colMap.put("earlyPer",nf.format(cMap.get("earlyPer"))+"%");
								   break;
							   }			   
						   }
						  if(j>=earlyInfoList.size()){
							   colMap.put("earlyNum",new Integer(0));
							   colMap.put("earlyPer","0%");
						   }
				}
				else{
					colMap.put("earlyNum",new Integer(0));
					colMap.put("earlyPer","0%");
				}
				
				if(!extraInfoList.isEmpty()){
						  Iterator staticIte=extraInfoList.iterator();
						  int extraNum=0;
						  while(staticIte.hasNext()){
							  
							 Map cMap=(Map)staticIte.next();				   
							 Integer cid=(Integer)cMap.get("CLERKID");
							 
							 if(cid.equals(clerkid)){
							   String osd=cMap.get("STARTDATE").toString();
							   String oed=cMap.get("ENDDATE").toString();
							   	
						       Date sd = sdf.parse(osd);
						       Date ed=sdf.parse(oed);
						       Calendar calendar = Calendar.getInstance();
						       calendar.setTime(sd);
						       
						       String nsd=sdf1.format(sd);			       			       
						       while(!sd.after(ed)&&!sd.after(eDate)){//拆分日期段，每天生成一条记录
						    	    			    	   
						    	   if(sd.before(sDate)){
						    		   sd=sDate;
						    		   calendar.setTime(sd);
						    		   nsd=sdf1.format(sDate);
						    	   }
						    	   extraNum++;	
						    	   
						    	   calendar.add(Calendar.DATE,1);
						    	   sd=calendar.getTime();
						    	   nsd=sdf1.format(sd);			    	   			    	   
						       }	
						       
						     }
						  }
						  colMap.put("extraNum",new Integer(extraNum));
						  double per=extraNum*100/datePeriod;						  
						  colMap.put("extraPer",nf.format(per)+"%");
				}
				else{
					colMap.put("extraNum",new Integer(0));
					colMap.put("extraPer","0%");
				}
				if(!irregularInfoList.isEmpty()){
						  Iterator staticIte=irregularInfoList.iterator();
						  int irregularNum=0;
						  while(staticIte.hasNext()){
							  
								 Map cMap=(Map)staticIte.next();				   
								 Integer cid=(Integer)cMap.get("CLERKID");
								 
								 if(cid.equals(clerkid)){
								   String osd=cMap.get("STARTDATE").toString();
								   String oed=cMap.get("ENDDATE").toString();
								   	
							       Date sd = sdf.parse(osd);
							       Date ed=sdf.parse(oed);
							       Calendar calendar = Calendar.getInstance();
							       calendar.setTime(sd);
							       
							       String nsd=sdf1.format(sd);			       			       
							       while(!sd.after(ed)&&!sd.after(eDate)){//拆分日期段，每天生成一条记录
							    	    			    	   
							    	   if(sd.before(sDate)){
							    		   sd=sDate;
							    		   calendar.setTime(sd);
							    		   nsd=sdf1.format(sDate);
							    	   }
							    	   irregularNum++;	
							    	   
							    	   calendar.add(Calendar.DATE,1);
							    	   sd=calendar.getTime();
							    	   nsd=sdf1.format(sd);			    	   			    	   
							       }	
							       
							     }
							  }
							  colMap.put("irregularNum",new Integer(irregularNum));
							  double per=irregularNum*100/datePeriod;
							  colMap.put("irregularPer",nf.format(per)+"%");
				}
				else{
					colMap.put("irregularNum",new Integer(0));
					colMap.put("irregularPer","0%");
				}
				if(!leaveInfoList.isEmpty()){
						  Iterator staticIte=leaveInfoList.iterator();
						  int leaveNum=0;
						  while(staticIte.hasNext()){
							  
								 Map cMap=(Map)staticIte.next();				   
								 Integer cid=(Integer)cMap.get("CLERKID");
								 
								 if(cid.equals(clerkid)){
								   String osd=cMap.get("STARTDATE").toString();
								   String oed=cMap.get("ENDDATE").toString();
								   	
							       Date sd = sdf.parse(osd);
							       Date ed=sdf.parse(oed);
							       Calendar calendar = Calendar.getInstance();
							       calendar.setTime(sd);
							       
							       String nsd=sdf1.format(sd);			       			       
							       while(!sd.after(ed)&&!sd.after(eDate)){//拆分日期段，每天生成一条记录
							    	    			    	   
							    	   if(sd.before(sDate)){
							    		   sd=sDate;
							    		   calendar.setTime(sd);
							    		   nsd=sdf1.format(sDate);
							    	   }
							    	   leaveNum++;	
							    	   
							    	   calendar.add(Calendar.DATE,1);
							    	   sd=calendar.getTime();
							    	   nsd=sdf1.format(sd);			    	   			    	   
							       }	
							       
							     }
							  }
							  colMap.put("leaveNum",new Integer(leaveNum));
							  double per=leaveNum*100/datePeriod;
							  colMap.put("leavePer",nf.format(per)+"%");
				}
				else{
					colMap.put("leaveNum",new Integer(0));
					colMap.put("leavePer","0%");
				}
				if(!outInfoList.isEmpty()){
						  Iterator staticIte=outInfoList.iterator();
						  int outNum=0;
						  while(staticIte.hasNext()){
							  
								 Map cMap=(Map)staticIte.next();				   
								 Integer cid=(Integer)cMap.get("CLERKID");
								 
								 if(cid.equals(clerkid)){
								   String osd=cMap.get("STARTDATE").toString();
								   String oed=cMap.get("ENDDATE").toString();
								   	
							       Date sd = sdf.parse(osd);
							       Date ed=sdf.parse(oed);
							       Calendar calendar = Calendar.getInstance();
							       calendar.setTime(sd);
							       
							       String nsd=sdf1.format(sd);			       			       
							       while(!sd.after(ed)&&!sd.after(eDate)){//拆分日期段，每天生成一条记录
							    	    			    	   
							    	   if(sd.before(sDate)){
							    		   sd=sDate;
							    		   calendar.setTime(sd);
							    		   nsd=sdf1.format(sDate);
							    	   }
							    	   outNum++;	
							    	   
							    	   calendar.add(Calendar.DATE,1);
							    	   sd=calendar.getTime();
							    	   nsd=sdf1.format(sd);			    	   			    	   
							       }	
							       
							     }
							  }
							  colMap.put("outNum",new Integer(outNum));							  
							  double per=outNum*100/datePeriod;
							  colMap.put("outPer",nf.format(per)+"%");
				}
				else{
					colMap.put("outNum",new Integer(0));
					colMap.put("outPer","0%");
				}
			 }
			 return deptstaticList;	  
		  }
		  else
			  return null;
		  
	  }		  
		  return null;
	  }
	
	public List getAllClerkinDept(String deptid)throws Exception	
	  {
		String sql="";
		sql="select CLERKID,cust.STUEMP_NO as STUNUMBER,cust.CUT_NAME as clerkName,DEPT_ID,DEPT_NAME as deptName,card.CARD_ID as cardId from YKT_CUR.T_CIF_CUSTOMER cust,YKT_CK.CLERK,YKT_CK.DEPARTMENT,YKT_CUR.T_PIF_CARD card ,YKT_CUR.T_AIF_ACCOUNT account	where CLERKID=CUT_ID and DEPARTMENTID=DEPT_ID and card.CARD_ID=account.CARD_ID and account.CUSTOMER_ID=cust.CUT_ID and card.STATE_ID='1000' and DEPT_ID='"+deptid+"'";
		sql+=" order by STUNUMBER";
		
		log.debug("sql:"+sql);
		List clerkInfoList=jdbcTemplate.queryForList(sql);
		
		if(!clerkInfoList.isEmpty())
			return clerkInfoList;
		else
			return null;
	  }
	
	public List getdeptInfo(String deptid)throws Exception	
	  {
		String sql="";
		sql="select DEPT_ID, DEPT_NAME as deptName, DEPT_PARENTID from YKT_CK.DEPARTMENT where DEPT_ID='"+deptid+"'";
		
		log.debug("sql:"+sql);
		List deptInfoList=jdbcTemplate.queryForList(sql);
		
		if(!deptInfoList.isEmpty())
			return deptInfoList;
		else
			return null;
	  }
	
	public String getDepartment()throws Exception	
	  {
		String sql="";
		sql="select DEPT_ID, DEPT_NAME, DEPT_PARENTID from YKT_CK.DEPARTMENT";
		
		log.debug("sql:"+sql);
		List clerkInfoList=jdbcTemplate.queryForList(sql);
		
		if(!clerkInfoList.isEmpty())
			return ((Integer)((Map)clerkInfoList.get(0)).get("CLERKID")).toString();		
		else
			return null;
	  }
}
