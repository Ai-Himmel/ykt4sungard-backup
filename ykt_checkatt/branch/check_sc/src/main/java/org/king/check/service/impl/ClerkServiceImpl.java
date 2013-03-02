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
import org.king.check.util.DateUtilExtend;
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

	/* hanjiwei modify it 20060918
	 * @see org.king.check.service.ClerkService#queryClerk(java.util.Map)
	 * 
	 */
	public List queryClerk(Map filterMap) {
		StringBuffer sql = new StringBuffer(2048);
		sql.append("SELECT B.CUT_ID CUT_ID,B.STUEMP_NO STUEMPID,B.CUT_NAME STUEMPNAME,typeInfo.type_name,")
		.append(" C.DEPT_NAME,D.DICT_CAPTION IFOFFICE FROM YKT_CK.T_CLERKINFO A ")
		.append(" LEFT JOIN YKT_CUR.T_CIF_CUSTOMER B ON A.CUST_ID=B.CUT_ID")
		.append(" left join ykt_ck.t_checktype typeInfo on A.checktype_id = typeInfo.type_id")
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
				sql.append(" AND A.DEPT_ID = '"+department+"'");
		}
		//log.debug("Sql--------------->"+sql.toString());
		//log.info("Sql--------------->"+sql.toString());
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
	 * 考勤情况汇总表
	 * hanjiwei add it 20061218
	 * @see org.king.check.service.ClerkService#getCheckReportByStuempNo()
	 */
	public List getCheckReportStat(String stuempNo,String beginDate,String endDate,String deptId) throws Exception {
		StringBuffer sql = new StringBuffer(2048);
		sql.append("select att.cust_id,cust.cut_name,cust.stuemp_no,dept.dept_name,")
		.append(" sum(att.WORKTIME_VALUE)workTime,sum(att.FACT_VALUE)factValue,sum(att.HAND_TIMES)handNum,")
		.append(" sum(att.OVERTIME_VALUE)overTime,sum(att.DELAY_VALUE)delayValue,sum(att.LEAVE_EARLY)leaveEarly, ")
		.append(" sum(att.LEAVE_VALUE)leaveValue,sum(att.LEAVE_TIME)leaveTime,sum(att.CHECK_NUM)checkNum,")
		.append(" sum(att.DELAY_NUM)delayNum,sum(att.EARLY_NUM)earlyNum,sum(att.LEAVE_NUM)leaveNum,")
		.append(" sum(att.EXTCHECK_NUM)extcheckNum,sum(att.WORKTIME_NUM)worktimeNum")
		.append(" from ykt_ck.t_clerkinfo info left join ykt_cur.t_cif_customer cust")
		.append(" on info.cust_id = cust.cut_id left join ykt_ck.t_checkatt_report att")
		.append(" on info.cust_id = att.cust_id left join ykt_ck.department dept")
		.append(" on info.dept_id = dept.dept_id where att.ifoffice=1")
		.append(" and att.check_date>=").append(beginDate).append(" and att.check_date<=").append(endDate);
		if (!"".equals(deptId)){
			sql.append(" and info.dept_id='").append(deptId).append("'");
		}
		if (!"".equals(stuempNo)){
			sql.append(" and cust.stuemp_no='").append(stuempNo).append("'");
		}
		sql.append(" group by att.cust_id,cust.cut_name,cust.stuemp_no,dept.dept_name")
		.append(" order by dept.dept_name");
		List clerkReportList = jdbcTemplate.queryForList(sql.toString());
		return clerkReportList;
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
	
	/**
	 * 坐班人员考勤情况明细报表
	 * @param stuempNo
	 * @return
	 */
	public List getCheckDetail(String stuempNo,String beginDate,String endDate,String deptId) throws Exception{
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select att.cust_id,att.check_date,cust.cut_name,cust.stuemp_no,dept.dept_name,")
		.append(" (att.WORKTIME_VALUE)workTime,(att.FACT_VALUE)factValue,(att.HAND_TIMES)handNum,")
		.append(" (att.OVERTIME_VALUE)overTime,(att.DELAY_VALUE)delayValue,(att.LEAVE_EARLY)leaveEarly, ")
		.append(" (att.LEAVE_VALUE)leaveValue,(att.LEAVE_TIME)leaveTime,(att.CHECK_NUM)checkNum,")
		.append(" (att.DELAY_NUM)delayNum,(att.EARLY_NUM)earlyNum,(att.LEAVE_NUM)leaveNum,")
		.append(" (att.EXTCHECK_NUM)extcheckNum,(att.WORKTIME_NUM)worktimeNum")
		.append(" from ykt_ck.t_clerkinfo info left join ykt_cur.t_cif_customer cust")
		.append(" on info.cust_id = cust.cut_id left join ykt_ck.t_checkatt_report att")
		.append(" on info.cust_id = att.cust_id left join ykt_ck.department dept")
		.append(" on info.dept_id = dept.dept_id where att.ifoffice=1")
		.append(" and att.check_date>=").append(beginDate).append(" and att.check_date<=").append(endDate);
		if (!"".equals(deptId)){
			sql.append(" and info.dept_id='").append(deptId).append("'");
		}
		if (!"".equals(stuempNo)){
			sql.append(" and cust.stuemp_no='").append(stuempNo).append("'");
		}
		sql.append(" order by dept.dept_name,att.cust_id,att.check_date");
		List clerkDetailList = jdbcTemplate.queryForList(sql.toString());
		if (clerkDetailList.size()==0){
			return null;
		}else{
			List checkSerialList = new ArrayList();
			Iterator serialIter = clerkDetailList.iterator();
			while (serialIter.hasNext()){
				Map seriMap = (Map)serialIter.next();
				Map checkSerialMap = new HashMap();
				checkSerialMap.put("cust_id",seriMap.get("cust_id"));
				checkSerialMap.put("check_date",seriMap.get("check_date"));
				checkSerialMap.put("week",DateUtilExtend.getWeekByDate(seriMap.get("check_date").toString()));
				checkSerialMap.put("cut_name",seriMap.get("cut_name"));
				checkSerialMap.put("stuemp_no",seriMap.get("stuemp_no"));
				checkSerialMap.put("dept_name",seriMap.get("dept_name"));
				checkSerialMap.put("workTime",seriMap.get("workTime"));
				checkSerialMap.put("factValue",seriMap.get("factValue"));
				checkSerialMap.put("handNum",seriMap.get("handNum"));
				checkSerialMap.put("overTime",seriMap.get("overTime"));
				checkSerialMap.put("delayValue",seriMap.get("delayValue"));
				checkSerialMap.put("leaveEarly",seriMap.get("leaveEarly"));
				checkSerialMap.put("leaveValue",seriMap.get("leaveValue"));
				checkSerialMap.put("leaveTime",seriMap.get("leaveTime"));
				checkSerialMap.put("checkNum",seriMap.get("checkNum"));
				checkSerialMap.put("delayNum",seriMap.get("delayNum"));
				checkSerialMap.put("earlyNum",seriMap.get("earlyNum"));
				checkSerialMap.put("leaveNum",seriMap.get("leaveNum"));
				checkSerialMap.put("extcheckNum",seriMap.get("extcheckNum"));
				checkSerialMap.put("worktimeNum",seriMap.get("worktimeNum"));
				checkSerialList.add(checkSerialMap);
			}
			return checkSerialList;
		}
	}

	/**
	 * 坐班人员考勤流水查询
	 */
	public List getCheckSerial(String stuempNo,String beginDate,String endDate,String deptId) throws Exception{
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select info.cust_id,info.check_date,cust.cut_name,cust.stuemp_no,dept.dept_name,")
		.append(" info.fact_ontime1,info.fact_offtime1,")
		.append(" info.fact_ontime2,info.fact_offtime2,")
		.append(" info.fact_ontime3,info.fact_offtime3,")
		.append(" info.fact_ontime4,info.fact_offtime4")
		.append(" from ykt_ck.t_clerkinfo clerk left join ykt_ck.t_checkatt_info info")
		.append(" on clerk.cust_id = info.cust_id left join ykt_cur.t_cif_customer cust")
		.append(" on clerk.cust_id = cust.cut_id left join ykt_ck.department dept")
		.append(" on clerk.dept_id = dept.dept_id where info.ifoffice=1")
		.append(" and info.check_date>=").append(beginDate).append(" and info.check_date<=").append(endDate);
		if (!"".equals(deptId)){
			sql.append(" and clerk.dept_id='").append(deptId).append("'");
		}
		if (!"".equals(stuempNo)){
			sql.append(" and cust.stuemp_no='").append(stuempNo).append("'");
		}
		sql.append(" order by cust.stuemp_no,info.check_date");
		List clerkDetailList = jdbcTemplate.queryForList(sql.toString());
		if (clerkDetailList.size()==0){
			return null;
		}else{
			List checkSerialList = new ArrayList();
			Iterator serialIter = clerkDetailList.iterator();
			while (serialIter.hasNext()){
				Map seriMap = (Map)serialIter.next();
				Map checkSerialMap = new HashMap();
				checkSerialMap.put("cust_id",seriMap.get("cust_id"));
				checkSerialMap.put("check_date",seriMap.get("check_date"));
				checkSerialMap.put("week",DateUtilExtend.getWeekByDate(seriMap.get("check_date").toString()));
				checkSerialMap.put("cut_name",seriMap.get("cut_name"));
				checkSerialMap.put("stuemp_no",seriMap.get("stuemp_no"));
				checkSerialMap.put("dept_name",seriMap.get("dept_name"));
				checkSerialMap.put("fact_ontime1",oToString(seriMap.get("fact_ontime1")));
				checkSerialMap.put("fact_offtime1",oToString(seriMap.get("fact_offtime1")));
				checkSerialMap.put("fact_ontime2",oToString(seriMap.get("fact_ontime2")));
				checkSerialMap.put("fact_offtime2",oToString(seriMap.get("fact_offtime2")));
				checkSerialMap.put("fact_ontime3",oToString(seriMap.get("fact_ontime3")));
				checkSerialMap.put("fact_offtime3",oToString(seriMap.get("fact_offtime3")));
				checkSerialMap.put("fact_ontime4",oToString(seriMap.get("fact_ontime4")));
				checkSerialMap.put("fact_offtime4",oToString(seriMap.get("fact_offtime4")));
				checkSerialList.add(checkSerialMap);
			}
			return checkSerialList;
		}
	}


	/*
	 *  (non-Javadoc)
	 * @see org.king.check.service.ClerkService#makeReportRecord(java.lang.String, java.lang.String, java.lang.String)
	 */
	public void makeReportRecord(TMakereportrecord reportRecord) {
		String deptId = reportRecord.getId().getDeptId().toString();
		String statMonth = reportRecord.getId().getReportMonth().toString();
		if (sysService.getReportRecord(deptId,statMonth)>0){
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
	
	
	private String oToString(Object inValue){
		if (null==inValue){
			return "";
		}else if ("000000".equals(inValue.toString())){
			return "";
		}else{
			String sTime = inValue.toString();
			return sTime.substring(0,2)+":"+sTime.substring(2,4);
		}
	}
	
	/**
	private String formatFloat(float inValue){
		return new DecimalFormat("#.##").format(inValue);
	}
	**/
	
	/**
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		return new ToStringBuilder(this).toString();
	}
}
