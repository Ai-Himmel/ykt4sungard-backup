/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.check.service.impl.ClerkServiceImpl.java
 * 创建日期： 2006-6-19 13:31:54
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-19 13:31:54      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.check.service.impl;

import java.io.Serializable;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.ClerkDAO;
import org.king.check.domain.TMakereportrecord;
import org.king.check.domain.Tclerkinfo;
import org.king.check.service.ClerkService;
import org.king.check.service.SysService;
import org.springframework.jdbc.core.JdbcTemplate;
import org.apache.commons.lang.builder.ToStringBuilder;

/**
 * <p> ClerkServiceImpl.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="ClerkServiceImpl.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-19
 *  
 *
 */
public class ClerkServiceImpl implements ClerkService {
	private static final Log log = LogFactory.getLog(ClerkServiceImpl.class);
	private JdbcTemplate jdbcTemplate;
	
	private ClerkDAO clerkDAO;
	
	private SysService sysService;
	
	
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	
	public void setClerkDAO(ClerkDAO clerkDAO) {
		this.clerkDAO = clerkDAO;
	}
	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}

	/**
	 * 个人当月考勤流水查询
	 */
	public List queryClerkCheckDetail(Integer custId,String beginDate,String endDate) {
		StringBuffer sql = new StringBuffer(2048);
		sql.append("select cust_id, cut_name,stuemp_no, att_date,count(*)attnum from(")
		.append(" select att.cust_id, cust.cut_name,cust.stuemp_no, att.att_date ")
		.append(" from ykt_ck.t_attserial att left join ykt_cur.t_cif_customer cust on att.cust_id=cust.cut_id")
		.append(" where att.cust_id=? and att.att_date>=? and att.att_date<=? ")
		.append(" union all")
		.append(" select rec.cust_id, cust.cut_name,cust.stuemp_no, rec.att_date")
		.append(" from ykt_ck.t_attserial_record rec left join ykt_cur.t_cif_customer cust on rec.cust_id=cust.cut_id")
		.append(" where rec.cust_id=? and rec.att_date>=? and rec.att_date<=?)")
		.append(" group by cust_id, cut_name,stuemp_no, att_date")
		.append(" order by att_date desc ");
		//log.debug("Sql--------------->"+sql.toString());
		List clerkList = jdbcTemplate.queryForList(sql.toString(),new Object[]{custId,beginDate,endDate,custId,beginDate,endDate});
		if (clerkList.isEmpty()){
			return clerkList;
		}else{
			List checkList = new ArrayList();
			Iterator checkIter = clerkList.iterator();
			while (checkIter.hasNext()){
				Map checkMap = (Map)checkIter.next();
				Map clerkMap = new HashMap();
				clerkMap.put("cust_id",checkMap.get("cust_id"));
				clerkMap.put("cut_name",checkMap.get("cut_name"));
				clerkMap.put("stuemp_no",checkMap.get("stuemp_no"));
				clerkMap.put("att_date",checkMap.get("att_date"));
				clerkMap.put("attnum",checkMap.get("attnum"));
				clerkMap.put("haveManual",haveManualCheck(custId,checkMap.get("att_date").toString()));
				checkList.add(clerkMap);
			}
			return checkList;
		}		
	}

	
	private Integer haveManualCheck(Integer custId,String checkDate){
		StringBuffer sql = new StringBuffer(128);
		sql.append("select count(*)num from ykt_ck.t_attserial_record t")
		.append(" where cust_id=? and att_date=?");
		List ss = jdbcTemplate.queryForList(sql.toString(),new Object[]{custId,checkDate});
		if (ss.isEmpty()){
			return new Integer(0);
		}else{
			Map ssMap = (Map)ss.get(0);
			return Integer.valueOf(ssMap.get("num").toString());
		}
	}
	/* hanjiwei modify it 20060918
	 * @see org.king.check.service.ClerkService#queryClerk(java.util.Map)
	 * 
	 */
	public List queryClerk(Map filterMap) {
		StringBuffer sql = new StringBuffer(2048);
		sql.append("SELECT B.CUT_ID CUT_ID,B.STUEMP_NO STUEMPID,B.CUT_NAME STUEMPNAME,")
		.append(" C.DEPT_NAME,D.DICT_CAPTION IFOFFICE FROM YKT_CK.T_CLERKINFO A ")
		.append(" LEFT JOIN YKT_CUR.T_CIF_CUSTOMER B ON A.CUST_ID=B.CUT_ID")
		.append(" LEFT JOIN (SELECT DICT.DICT_VALUE,DICT.DICT_CAPTION FROM ")
		.append(" YKT_CUR.T_PIF_DICTIONARY DICT WHERE DICT.DICT_NO=1200) D")
		.append(" ON A.IFOFFICE=D.DICT_VALUE LEFT  JOIN YKT_CK.DEPARTMENT C")
		.append(" ON A.DEPT_ID=C.DEPT_ID WHERE 1=1 ");
		//参数处理
		if(filterMap!=null&&!filterMap.isEmpty()){
			String personCode = (String)filterMap.get("personCode");
			if (StringUtils.isNotEmpty(personCode))
				sql.append(" AND B.STUEMP_NO LIKE "+"'%"+personCode+"%'");
			String personName = (String)filterMap.get("personName");
			if (StringUtils.isNotEmpty(personName))
				sql.append(" AND B.CUT_NAME LIKE "+"'%"+personName+"%'");			
			String department = (String)filterMap.get("department");
			if (StringUtils.isNotEmpty(department)&&!department.equals("all"))
				sql.append(" AND A.DEPT_ID in("+department+")");
		}
		//log.debug("Sql--------------->"+sql.toString());
		List clerkList = jdbcTemplate.queryForList(sql.toString());
		return clerkList;
	}

	/**
	 * 
	 */
	public List queryAvailableClerk(Map filterMap) {
		//查询sql
		String Sql = "SELECT * FROM (SELECT B.CARD,B.PERSON_CODE PERSON_CODE,B.PERSON_NAME PERSON_NAME,B.PERSON_TYPE,C.DEPT_NAME DEPT_NAME,'' is_seat,0 is_clerk,'否' is_clerk_title "+
		             "FROM (SELECT * FROM YKT_CK.usr_person A WHERE A.PERSON_CODE NOT IN (SELECT CLERKID FROM YKT_CK.CLERK)) B "+
		             "LEFT JOIN YKT_CK.DEPARTMENT C ON  B.DEPT=C.DEPT_ID) Z";
			 
		String sSqlUnion=" UNION "+
		"SELECT * FROM (SELECT B.CARD,B.PERSON_CODE PERSON_CODE,B.PERSON_NAME PERSON_NAME,B.PERSON_TYPE,E.DEPT_NAME DEPT_NAME,D.DICT_CAPTION IS_SEAT,1 is_clerk,'是' is_clerk_title "+
		"FROM  (SELECT A.CLERKID AS PERSON_CODE,C.PERSON_NAME,C.DEPT,A.ISSEAT,C.PERSON_TYPE,C.CARD FROM YKT_CK.CLERK A LEFT JOIN YKT_CK.USR_PERSON C ON A.CLERKID=C.PERSON_CODE ) B"+
	      " LEFT JOIN (SELECT DICT.DICT_VALUE,DICT.DICT_CAPTION FROM YKT_CK.COM_DICTIONARY DICT WHERE DICT.DICT_NO=1002) D ON B.ISSEAT=D.DICT_VALUE"+
	      " LEFT JOIN YKT_CK.DEPARTMENT E ON  B.DEPT=E.DEPT_ID) Z"
				;
		String sCod = " WHERE 1=1 ";
		
		//参数处理
		if(filterMap!=null&&!filterMap.isEmpty()){
			String personCode = (String)filterMap.get("personCode");
			if (StringUtils.isNotEmpty(personCode))
				sCod +=" AND Z.PERSON_CODE LIKE "+"'%"+personCode+"%'";
			String personName = (String)filterMap.get("personName");
			if (StringUtils.isNotEmpty(personName))
				sCod +=" AND Z.PERSON_NAME LIKE "+"'%"+personName+"%'";
			String card = (String)filterMap.get("card");
			if (StringUtils.isNotEmpty(card))
				sCod +=" AND Z.CARD LIKE "+"'%"+card+"%'";
			
			String personType = (String)filterMap.get("personType");
			if (StringUtils.isNotEmpty(personType)&&!personType.equals("all"))
				sCod +=" AND Z.PERSON_TYPE = '"+personType+"'";
			
			String department = (String)filterMap.get("department");
			if (StringUtils.isNotEmpty(department)&&!department.equals("all"))
				sCod +=" AND Z.DEPT_NAME = '"+department+"'";
			
		}
	
		Sql = Sql+sCod+sSqlUnion+sCod;
		
		
		List clerkList = jdbcTemplate.queryForList(Sql);
		return clerkList;
	}


	/**
	 * 
	 */
	public int setupClerk(List clerkList) {
		
		int count = 0;
		if(clerkList!=null&&!clerkList.isEmpty()){
			for(int i=0;i<clerkList.size();i++){
				Tclerkinfo clerk = (Tclerkinfo)clerkList.get(i);
				boolean flag = clerkDAO.isExist(clerk.getCustId());
				
				if(!flag){
					clerkDAO.save(clerk);
				}else{
					clerkDAO.update(clerk);
				}
				count ++;
			}
		}
		return count;
	}

	
	
	public void deleteClerk(String clerkId){
		
		if(clerkId!=null&&clerkId!=""){
			clerkDAO.delete(clerkDAO.get(Integer.valueOf(clerkId)));
		}		
	}
	
	public Tclerkinfo get(Serializable id)
	{
		return clerkDAO.get(id);
	}
	
	/*
	 * hanjiwei add it 20061218
	 * @see org.king.check.service.ClerkService#getCheckReportByStuempNo()
	 */
	public Map getCheckReportByStuempNo(int custId,String beginDate,String endDate) throws Exception {
		StringBuffer sql = new StringBuffer(2048);
		sql.append("select CUST_ID, CHECK_DATE, DEPT_ID, IFOFFICE, WORKTIME_VALUE, FACT_VALUE, ")
		.append(" HAND_TIMES, OVERTIME_VALUE, TWOREST_VALUE, HOLIDAY_VALUE, DELAY_VALUE, ")
		.append(" LEAVE_EARLY, LEAVE_VALUE, LEAVE_TYPE, LEAVE_TIME")
		.append(" from YKT_CK.T_CHECKATT_REPORT where CUST_ID=").append(custId)
		.append(" and CHECK_DATE>='").append(beginDate).append("' and CHECK_DATE<='")
		.append(endDate).append("'");
		//log.debug("Sql--------------->"+sql.toString());
		List clerkReportList = jdbcTemplate.queryForList(sql.toString());
		Map clerkReportMap = new HashMap();
		if (clerkReportList.size()>0){
			Iterator iter = clerkReportList.iterator();
			float factWorkValue = 0;
			float workValue = 0;
			float overValue = 0;
			float twoRestValue = 0;
			float holidayValue = 0;
			float delayValue = 0;
			float leaveEarlyValue = 0;
			float leaveTimeValue = 0;
			float leaveValue = 0;
			while (iter.hasNext()){
				Map reportMap = (Map)iter.next(); 
				factWorkValue = factWorkValue + Float.parseFloat(nullToString(reportMap.get("FACT_VALUE")));
				workValue = workValue + Float.parseFloat(nullToString(reportMap.get("WORKTIME_VALUE")));
				overValue = overValue + Float.parseFloat(nullToString(reportMap.get("OVERTIME_VALUE")));
				twoRestValue = twoRestValue + Float.parseFloat(nullToString(reportMap.get("TWOREST_VALUE")));
				holidayValue = holidayValue + Float.parseFloat(nullToString(reportMap.get("HOLIDAY_VALUE")));
				delayValue = delayValue + Float.parseFloat(nullToString(reportMap.get("DELAY_VALUE")));
				leaveEarlyValue = leaveEarlyValue + Float.parseFloat(nullToString(reportMap.get("LEAVE_EARLY")));
				leaveTimeValue = leaveTimeValue + Float.parseFloat(nullToString(reportMap.get("LEAVE_TIME")));
				leaveValue = leaveValue + Float.parseFloat(nullToString(reportMap.get("LEAVE_VALUE")));
			}
			clerkReportMap.put("factWorkValue",formatFloat(factWorkValue/60));
			clerkReportMap.put("workValue",formatFloat(workValue/60));
			clerkReportMap.put("overValue",formatFloat(overValue/60));
			clerkReportMap.put("twoRestValue",formatFloat(twoRestValue/60));
			clerkReportMap.put("holidayValue",formatFloat(holidayValue/60));
			clerkReportMap.put("delayValue",formatFloat(delayValue/60));
			clerkReportMap.put("leaveEarlyValue",formatFloat(leaveEarlyValue/60));
			clerkReportMap.put("leaveTimeValue",formatFloat(leaveTimeValue/60));
			clerkReportMap.put("leaveValue",formatFloat(leaveValue/60));
		}else{
			clerkReportMap.put("factWorkValue",new Float(0));
			clerkReportMap.put("workValue",new Float(0));
			clerkReportMap.put("overValue",new Float(0));
			clerkReportMap.put("twoRestValue",new Float(0));
			clerkReportMap.put("holidayValue",new Float(0));
			clerkReportMap.put("delayValue",new Float(0));
			clerkReportMap.put("leaveEarlyValue",new Float(0));
			clerkReportMap.put("leaveTimeValue",new Float(0));
			clerkReportMap.put("leaveValue",new Float(0));

		}
		return clerkReportMap;
	}


	/**
	 * hanjiwei modify it 20060914
	 */
	public Map getClerkDetailByClerkId(String  clerkId)throws Exception{
		Map infoMap=new HashMap();
		
		/*
		 * 得到员工姓名 部门
		 */
		List infoList = null;
		StringBuffer strSql = new StringBuffer(1024);
		strSql.append("SELECT B.CUT_ID  CUT_ID,B.STUEMP_NO STUEMPID,B.CUT_NAME STUEMPNAME,")
        .append(" A.DELAY_OVERTIME, A.OVERTIME_VALUE, A.TWOREST_OVERTIME, A.HOLIDAY_OVERTIME,")
		.append(" A.AHEAD_OVERTIME,C.DEPT_NAME DEPTNAME,C.DEPT_ID DEPTID,D.DICT_CAPTION IFOFFICE ")
		.append(" FROM YKT_CK.T_CLERKINFO A LEFT JOIN YKT_CUR.T_CIF_CUSTOMER B ON A.CUST_ID=B.CUT_ID")
		.append(" LEFT JOIN (SELECT DICT.DICT_VALUE,DICT.DICT_CAPTION FROM ")
		.append(" YKT_CUR.T_PIF_DICTIONARY DICT WHERE DICT.DICT_NO=1200) D")
		.append(" ON A.IFOFFICE=D.DICT_VALUE LEFT  JOIN YKT_CK.DEPARTMENT C")
		.append(" ON A.DEPT_ID=C.DEPT_ID WHERE B.CUT_ID="+clerkId);
        log.debug("sql:"+strSql.toString());
        infoList=jdbcTemplate.queryForList(strSql.toString());
        
        String deptId="";
        if(!infoList.isEmpty())
        {
        	Map tempMap=(Map)infoList.get(0);
        	deptId=tempMap.get("DEPTID").toString();
        	infoMap.put("custId",tempMap.get("CUT_ID"));
        	infoMap.put("stuempId",tempMap.get("STUEMPID"));
        	infoMap.put("stuempName",tempMap.get("STUEMPNAME"));
        	infoMap.put("deptName",tempMap.get("DEPTNAME"));
        	infoMap.put("deptId",tempMap.get("DEPTID"));
        	infoMap.put("ifOffice",tempMap.get("IFOFFICE"));
        	infoMap.put("aheadOverTime",tempMap.get("AHEAD_OVERTIME"));
        	infoMap.put("delayOverTime",tempMap.get("DELAY_OVERTIME"));
        	infoMap.put("overTime",tempMap.get("OVERTIME_VALUE"));       	
        	infoMap.put("twoReset",tempMap.get("TWOREST_OVERTIME"));
        	infoMap.put("holiday",tempMap.get("HOLIDAY_OVERTIME"));
        }
        /*
         * 得到员工工作制度
         */
        StringBuffer workTimeConf = new StringBuffer(1024);
        workTimeConf.append("select distinct WORKINFO_ID, WORKTIME_ID" )
        .append(" from YKT_CK.T_DEPT_WORKCONFINFO where DEPT_ID='"+deptId+"'");
        infoList=jdbcTemplate.queryForList(workTimeConf.toString());
        
        String workInfo = "";
        String workTime = "";
        if(!infoList.isEmpty())
        {
        	Map tempMap=(Map)infoList.get(0);
        	workInfo = tempMap.get("WORKINFO_ID").toString();
        	workTime = tempMap.get("WORKTIME_ID").toString();
        	infoMap.put("workInfo",tempMap.get("WORKINFO_ID"));
        	infoMap.put("workTime",tempMap.get("WORKTIME_ID"));
        }
        /*
         * 得到员工 工作制度
         */
        StringBuffer workConf = new StringBuffer(1024);
        workConf.append("select WORKCONF_NAME, OVERDUE_TIME, LEAVEEARLY_TIME,")
        .append(" OVER_TIME,DELAY_TIME, CHECK_TIME")
        .append(" from YKT_CK.T_WORKCONFINFO where WORKCONF_ID='"+workInfo+"'");
        infoList=jdbcTemplate.queryForList(workConf.toString());
        if(!infoList.isEmpty())
        {
        	Map tempMap=(Map)infoList.get(0);
        	infoMap.put("wordConfName",tempMap.get("WORKCONF_NAME"));
        	infoMap.put("overdueTime",tempMap.get("OVERDUE_TIME"));
        	infoMap.put("leaveEarlyTime",tempMap.get("LEAVEEARLY_TIME"));
        	infoMap.put("over",tempMap.get("OVER_TIME"));
        	infoMap.put("delay",tempMap.get("DELAY_TIME"));
        	infoMap.put("check",tempMap.get("CHECK_TIME"));
        }
        /*
         * 得到员工 工作时间制度
         */
        StringBuffer timeConf = new StringBuffer(1024);
        timeConf.append("select WORKTIME_NAME, ONTIME1, OFFTIME1, ONTIME2, OFFTIME2, ")
        .append(" ONTIME3, OFFTIME3, ONTIME4, OFFTIME4")
        .append(" from YKT_CK.T_WORKTIMEINTO where WORKTIME_ID='"+workTime+"'");
        infoList=jdbcTemplate.queryForList(timeConf.toString());
        if(!infoList.isEmpty())
        {
        	Map tempMap=(Map)infoList.get(0);
        	infoMap.put("workTimeName",tempMap.get("WORKTIME_NAME"));
        	infoMap.put("onTime1",formatTime(tempMap.get("ONTIME1").toString()));
        	infoMap.put("offTime1",formatTime(tempMap.get("OFFTIME1").toString()));
        	infoMap.put("onTime2",formatTime(tempMap.get("ONTIME2").toString()));
        	infoMap.put("offTime2",formatTime(tempMap.get("OFFTIME2").toString()));
        	infoMap.put("onTime3",formatTime(tempMap.get("ONTIME3").toString()));
        	infoMap.put("offTime3",formatTime(tempMap.get("OFFTIME3").toString()));
        	infoMap.put("onTime4",formatTime(tempMap.get("ONTIME4").toString()));
        	infoMap.put("offTime4",formatTime(tempMap.get("OFFTIME4").toString()));
        }
		return infoMap;
	}
	
	/*
	 *  (non-Javadoc)
	 * @see org.king.check.service.ClerkService#makeReportRecord(java.lang.String, java.lang.String, java.lang.String)
	 */
	public void makeReportRecord(TMakereportrecord reportRecord) {
		String deptId = reportRecord.getId().getDeptId().toString();
		String statMonth = reportRecord.getId().getReportMonth().toString();
		if (!"0".equals(sysService.getReportRecord(deptId,statMonth))){
			clerkDAO.delete(reportRecord);
			clerkDAO.save(reportRecord);
		}else{
			clerkDAO.save(reportRecord);
		}
		
	}


	private String formatTime(String time){
		String hh = "";
		String mm = "";
		if (("".equals(time))||(null==time)){
			return "";
		}else{
			hh = time.substring(0,2);
			mm = time.substring(2,4);
			return hh+":"+mm;
		}
	}
	
	private String nullToString(Object inValue){
		if (null==inValue){
			return "0";
		}else{
			return inValue.toString();
		}
	}
	
	private String formatFloat(float inValue){
		return new DecimalFormat("#.##").format(inValue);
	}
	
	/**
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		return new ToStringBuilder(this).toString();
	}
}
