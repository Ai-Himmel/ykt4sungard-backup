package org.king.check.service.impl;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.LeaveInfoDao;
import org.king.check.domain.Tleaveinfo;
import org.king.check.service.LeaveInfoService;
import org.king.check.service.SysService;
import org.king.check.util.DateUtilExtend;
import org.springframework.jdbc.core.JdbcTemplate;
import org.apache.commons.lang.StringUtils;

public class LeaveInfoServiceImpl implements LeaveInfoService {

	private static final Log log = LogFactory
			.getLog(LeaveInfoServiceImpl.class);

	private LeaveInfoDao leaveInfoDao;

	private JdbcTemplate jdbcTemplate;
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

	public void saveLeaveInfo(Tleaveinfo leaveInfo) {

	}

	public Tleaveinfo getLeaveInfoById(String leaveInfoId) {
		return leaveInfoDao.get(leaveInfoId);
	}

	public List getLeaveInfosByUserId(String userId) {
		return null;
	}

	public List getLeaveInfosByTime(Date startDate, Date endDate) {
		return null;
	}

	/**
	 * hanjiwei add it 20060918
	 * 检查数据库中是否存在该人员的交叉请假信息
	 */
	public String checkIsLeaveByClerkId(Integer clerkId,String inStart,String inEnd) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select cust.CUT_NAME,lea.CUST_ID, lea.STARTDATE,lea.ENDDATE, lea.STARTTIME, lea.ENDTIME ")
		.append(" from YKT_CK.T_LEAVEINFO lea left join YKT_CUR.T_CIF_CUSTOMER cust")
		.append(" on cust.CUT_ID=lea.CUST_ID")
		.append(" where validity='1' and CUST_ID="+clerkId);
		List clerkList = jdbcTemplate.queryForList(sql.toString());
		Iterator iter = clerkList.iterator();
		String beginTime="";
		String endTime="";
		while (iter.hasNext()){
			Map tmpMap=(Map)iter.next();
			beginTime = (String)tmpMap.get("STARTDATE")+(String)tmpMap.get("STARTTIME");
			endTime = (String)tmpMap.get("ENDDATE")+(String)tmpMap.get("ENDTIME");
			if (((DateUtilExtend.diffDate2(beginTime,inStart)<0)
				&&(DateUtilExtend.diffDate2(endTime,inEnd)>0))||
				((DateUtilExtend.diffDate2(endTime,inStart)<0)
				&&(DateUtilExtend.diffDate2(endTime,inEnd)>0))||
				((DateUtilExtend.diffDate2(inStart,beginTime)<0)
				&&(DateUtilExtend.diffDate2(inStart,endTime)>0))||
				((DateUtilExtend.diffDate2(inEnd,beginTime)<0)
				&&(DateUtilExtend.diffDate2(inEnd,endTime)>0))
				){
					return (String)tmpMap.get("CUT_NAME")+"在"+(String)tmpMap.get("STARTDATE")+"－"+(String)tmpMap.get("ENDDATE")+"存在请假信息！";
			}
		}
		
		return "";
	}

	/*
	 * hanjiwei modify it 20060918
	 * @see org.king.check.service.LeaveInfoService#searchLeaveInfo(java.util.Map)
	 */
	public List searchLeaveInfo(Map filter) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select lea.LEAVE_ID,lea.CUST_ID, lea.STARTDATE,lea.ENDDATE, lea.STARTTIME, lea.ENDTIME,")
		.append("lea.OPER_ID, lea.OPER_DATE, lea.OPER_TIME,cust.CUT_NAME,dept.DEPT_NAME,cust.STUEMP_NO,")
		.append("(select DICT_CAPTION from YKT_CUR.T_PIF_DICTIONARY where DICT_NO=1210 and DICT_VALUE=lea.LEAVE_TYPEID) as leavetype")
		.append(" from YKT_CK.T_LEAVEINFO lea ")
		.append(" left join YKT_CUR.T_CIF_CUSTOMER cust on cust.CUT_ID=lea.CUST_ID")
		.append(" left join YKT_CK.T_CLERKINFO clerk on clerk.CUST_ID=lea.CUST_ID")
		.append(" left join YKT_CK.DEPARTMENT dept on dept.DEPT_ID=clerk.DEPT_ID")
		.append(" where lea.VALIDITY='1'");
		if (StringUtils.isNotEmpty((String) filter.get("startDate"))){
			sql.append(" and lea.STARTDATE>='"+DateUtilExtend.formatDate2((String) filter.get("startDate"))+"'");
		}
		if (StringUtils.isNotEmpty((String) filter.get("endDate"))){
			sql.append(" and lea.ENDDATE<='"+DateUtilExtend.formatDate2((String) filter.get("endDate"))+"'");
		}
		if (StringUtils.isNotEmpty((String) filter.get("deptId"))){
			sql.append(" and dept.DEPT_ID='"+(String) filter.get("deptId")+"'");
		}
		if (StringUtils.isNotEmpty((String) filter.get("trueName"))){
			sql.append(" and cust.CUT_NAME like '%"+(String) filter.get("trueName")+"%'");
		}
		List infoList = jdbcTemplate.queryForList(sql.toString());
		List leaveList = new ArrayList();
		Iterator iter = infoList.iterator();
		while (iter.hasNext()) {
			Map leaveMap = (Map)iter.next();
			HashMap leaveInfoList = new HashMap();
			leaveInfoList.put("leaveId",leaveMap.get("LEAVE_ID"));
			leaveInfoList.put("custId",leaveMap.get("CUST_ID"));
			leaveInfoList.put("custName",leaveMap.get("CUT_NAME"));
			leaveInfoList.put("deptName",leaveMap.get("DEPT_NAME"));
			leaveInfoList.put("stuempNo",leaveMap.get("STUEMP_NO"));
			leaveInfoList.put("leaveType",leaveMap.get("leavetype"));
			leaveInfoList.put("startTime",formatDate(leaveMap.get("STARTDATE").toString(),leaveMap.get("STARTTIME").toString()));
			leaveInfoList.put("endTime",formatDate(leaveMap.get("ENDDATE").toString(),leaveMap.get("ENDTIME").toString()));
			leaveInfoList.put("operName",sysService.getOperName(leaveMap.get("OPER_ID").toString()));
			leaveInfoList.put("operTime",formatDate(leaveMap.get("OPER_DATE").toString(),leaveMap.get("OPER_TIME").toString()));
			leaveList.add(leaveInfoList);
		}

		return leaveList;
	}

	public List staticLeaveInfoByFilter(Map filter) throws Exception {
		/**
		List leaveInfoList = new ArrayList();
		String hql = "from ";
		String sql = "";
		String lastValue = "ini";

		sql = "select "
				+ " leave.STARTDATE as startDate ,"
				+ "leave.ENDDATE as endDate, "
				+ "dpart.DEPT_NAME AS departname ,"
				+ " 0 as tatol ,"
				+ "dpart.DEPT_ID AS dept_id,"
				+ "cust.CUT_NAME AS clerkname ,"
				+ "cust.CUT_ID as cut_id,"
				+ "dict.DICT_CAPTION as isseat,conf.CONFNAME as confname "
				+ " from YKT_CK.LEAVEINFO leave ,YKT_CK.DEPARTMENT dpart ,YKT_CK.CLERK clerk,YKT_CK.WORKCONF conf ,YKT_CUR.T_CIF_CUSTOMER cust,"
				+ " YKT_CK.COM_DICTIONARY dict ,YKT_CK.WORKCONFMAP  map "
				+ " where leave.DEPARTID=dpart.DEPT_ID AND clerk.CLERKID=leave.CLERKID AND conf.WORKCONFID = "
				+ "  map.WORKCONFID and  map.CLERKID=clerk.CLERKID "
				+ " and  cust.CUT_ID=leave.CLERKID "
				+ " AND dict.DICT_NO=1002 AND dict.DICT_VALUE=clerk.ISSEAT ";

		sql += StringUtils.isNotEmpty((String) filter
				.get(CommonConfig.trueName)) ? " and cust.CUT_NAME like '%"
				+ (String) filter.get(CommonConfig.trueName) + "%' " : " ";
		sql += StringUtils.isNotEmpty((String) filter
				.get(CommonConfig.startDate)) ? " and leave.STARTDATE >='"
				+ (String) filter.get(CommonConfig.startDate) + " 00:00:00"
				+ "' " : "";
		sql += StringUtils
				.isNotEmpty((String) filter.get(CommonConfig.endDate)) ? " and leave.ENDDATE  <='"
				+ (String) filter.get(CommonConfig.endDate)
				+ " 23:59:59"
				+ "' "
				: "";
		sql += StringUtils.isNotEmpty((String) filter.get("deptId")) ? " and dpart.DEPT_ID='"
				+ (String) filter.get("deptId") + "' "
				: "";

		sql += " and leave.ENDDATE>=leave.STARTDATE"
				+ " group by cust.CUT_ID,cust.CUT_NAME,leave.STARTDATE,leave.ENDDATE,dpart.DEPT_NAME,dpart.DEPT_ID,dict.DICT_CAPTION,conf.CONFNAME ";

		log.debug("sql:" + sql);
		List staticInfoList = jdbcTemplate.queryForList(sql);
		if (!staticInfoList.isEmpty()) {
			Iterator staticIte = staticInfoList.iterator();
			while (staticIte.hasNext()) {
				Map colMap = (Map) staticIte.next();

				if (lastValue.equals(((Integer) colMap.get("cut_id"))
						.toString()))
					continue;
				else
					lastValue = ((Integer) colMap.get("cut_id")).toString();

				colMap.put("terminateDay", (String) filter
						.get(CommonConfig.endDate));
				colMap.put("beginDay", (String) filter
						.get(CommonConfig.startDate));

				Integer tatol = getLeaveDays(colMap);

				colMap.put("tatol", tatol);

				leaveInfoList.add(colMap);
			}
		}

		return leaveInfoList;
		**/
		return null;
	}

	public Integer getLeaveDays(Map filter) throws Exception {
		/**
		Integer tatol;
		int temp = 0;
		String sql = "select leave.STARTDATE AS startDate ,leave.ENDDATE as endDate from YKT_CK.LEAVEINFO leave where leave.CLERKID="
				+ filter.get("cut_id")
				+ " and leave.ENDDATE<='"
				+ (String) filter.get("terminateDay")
				+ " 23:59:59"
				+ "' "
				+ " and leave.STARTDATE>='"
				+ (String) filter.get("beginDay")
				+ " 00:00:00" + "' " + " and leave.STARTDATE<=leave.ENDDATE ";
		Calendar calStart = Calendar.getInstance();
		Calendar calEnd = Calendar.getInstance();

		log.debug("sql:" + sql);

		List tatolList = jdbcTemplate.queryForList(sql);

		if (!tatolList.isEmpty()) {
			Iterator tatolIte = tatolList.iterator();
			while (tatolIte.hasNext()) {
				Map colMap = (Map) tatolIte.next();

				Date startDate = (Date) colMap.get("startDate");
				Date endDate = (Date) colMap.get("endDate");
				calStart.setTime(startDate);
				calEnd.setTime(endDate);

				int startDay, endDay, startYear, endYear;// 得到起始月以便计算天数
				startYear = calStart.get(Calendar.YEAR);
				endYear = calEnd.get(Calendar.YEAR);

				startDay = calStart.get(Calendar.DAY_OF_YEAR);
				endDay = calEnd.get(Calendar.DAY_OF_YEAR);

				if (startYear == endYear) {
					temp += endDay - startDay + 1;
				} else {
					int sum = (endYear - startYear - 1) * 365
							+ (365 - startYear) + endYear;
					temp += sum;
				}
			}
		}

		tatol = new Integer(temp);

		return tatol;
		**/
		return null;
	}

	public List getLeaveInfoDetail(Map filter) throws Exception {
		/**
		String sql = "select leave.STARTDATE as startDate,leave.ENDDATE as endDate,c.CUT_NAME as clerkname "
				+ " from "
				+ " YKT_CK.LEAVEINFO leave,YKT_CUR.T_CIF_CUSTOMER  c "
				+ "where c.CUT_ID=leave.CLERKID ";
		sql += StringUtils.isNotEmpty((String) filter
				.get(CommonConfig.startDate)) ? " and leave.STARTDATE >='"
				+ (String) filter.get(CommonConfig.startDate) + " 00:00:00"
				+ "' " : "";
		sql += StringUtils
				.isNotEmpty((String) filter.get(CommonConfig.endDate)) ? " and leave.ENDDATE  <='"
				+ (String) filter.get(CommonConfig.endDate)
				+ " 23:59:59"
				+ "' "
				: "";
		sql += StringUtils.isNotEmpty(((Integer) filter.get("clerkId"))
				.toString()) ? " and leave.CLERKID  ="
				+ (Integer) filter.get("clerkId") : "";

		sql += " order by startDate asc ";

		log.debug("sql:" + sql);

		List leaveDetailList = jdbcTemplate.queryForList(sql);

		return leaveDetailList;
		**/
		return null;
	}

	/**
	 * hanjiwei modify it 20060918
	 */
	public List searchClerkForRegister(Map filter) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select cust.CUT_ID, cust.CUT_NAME,  cust.STUEMP_NO, cust.CLASSDEPT_NO,")
		.append(" dept.DEPT_NAME,clerk.IFOFFICE,dict.DICT_CAPTION from YKT_CK.T_CLERKINFO clerk ")
		.append(" left join YKT_CUR.T_CIF_CUSTOMER cust on clerk.CUST_ID=cust.CUT_ID")
		.append(" left join YKT_CK.DEPARTMENT dept on dept.DEPT_ID=clerk.DEPT_ID")
		.append(" left join YKT_CUR.T_PIF_DICTIONARY dict on dict.DICT_VALUE=clerk.IFOFFICE")
		.append(" where dict.DICT_NO=1200");
		if (StringUtils.isNotEmpty((String) filter.get("trueName"))) {
			sql.append(" and cust.CUT_NAME like '%"
					+ (String) filter.get("trueName") + "%'");
		}
		if (StringUtils.isNotEmpty((String) filter.get("stuNumber"))) {
			sql.append(" and cust.STUEMP_NO='"
					+ (String) filter.get("stuNumber") + "'");
		}
		if (StringUtils.isNotEmpty((String) filter.get("deptId"))) {
			sql.append(" and cust.CLASSDEPT_NO='"
					+ (String) filter.get("deptId") + "'");
		}
		if (StringUtils.isNotEmpty((String) filter.get("clerkType"))) {
			sql.append(" and clerk.IFOFFICE='"
					+ (String) filter.get("clerkType") + "'");
		}
		log.debug("sql:" + sql);
		List clerkList = jdbcTemplate.queryForList(sql.toString());

		return clerkList;
	}

	/*
	 * hanjiwei modify it 20060918
	 * @see org.king.check.service.LeaveInfoService#addLeaveInfo(java.util.Map)
	 */
	public void addLeaveInfo(Map filter) throws Exception {
		String[] checkValues;
		checkValues = (String[]) filter.get("checkValues");
		String startDate = (String) filter.get("startDate");
		String endDate = (String) filter.get("endDate");

		startDate = DateUtilExtend.formatDate2(startDate);
		endDate = DateUtilExtend.formatDate2(endDate);

		String startTime = (String) filter.get("startHour")+ (String) filter.get("startMin") + "00";
		String endTime = (String) filter.get("endHour")+ (String) filter.get("endMin") + "00";
		for (int i = 0; i < checkValues.length; i++) {
			//判断该人员是否在该时间段请过假
			
			Tleaveinfo leaveinfo = new Tleaveinfo();
			leaveinfo.setCustId(new Integer(checkValues[i]));
			leaveinfo.setEnddate(endDate);
			leaveinfo.setEndtime(endTime);
			leaveinfo.setStartdate(startDate);
			leaveinfo.setStarttime(startTime);
			leaveinfo.setLeaveInfo((String) filter.get("description"));
			leaveinfo.setOperId((String) filter.get("operatorid"));
			leaveinfo.setOperDate((String) filter.get("operDate"));
			leaveinfo.setOperTime((String) filter.get("operTime"));
			leaveinfo.setLeaveTypeid((String) filter.get("type"));
			leaveinfo.setValidity("1");
			leaveInfoDao.save(leaveinfo);
		}
	}

	/*
	 * hanjiwei add it 20060918
	 * @see org.king.check.service.LeaveInfoService#deleteLeaveInfo(java.lang.String[])
	 */
	public List getLeaveInfo(String[] custIds) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		StringBuffer custStr = new StringBuffer();
		for (int i=0;i<custIds.length;i++){
			custStr.append(custIds[i]);
			if (i<custIds.length-1){
				custStr.append(",");
			}
		}
		sql.append("select (select DICT_CAPTION from YKT_CUR.T_PIF_DICTIONARY where dict_no=1210 and DICT_VALUE=lea.LEAVE_TYPEID)as leavetype,")
		.append(" lea.OPER_DATE, lea.OPER_TIME,")
		.append(" lea.CUST_ID, lea.STARTDATE, lea.ENDDATE, lea.STARTTIME, lea.ENDTIME,cust.CUT_NAME,cust.STUEMP_NO ")
		.append(" from YKT_CK.T_LEAVEINFO lea left join YKT_CUR.T_CIF_CUSTOMER cust on cust.cut_id=lea.cust_id")
		.append(" where cust_id in ("+custStr.toString()+")");
		//log.debug(sql.toString());
		List leaveList = jdbcTemplate.queryForList(sql.toString());

		return leaveList;
	}
	
	
	/**
	 * hanjiwei modify it 20060920
	 */
	public void deleteLeaveInfo(String[] leaveInfoIds) throws Exception {
		 for(int i=0;i<leaveInfoIds.length;i++) { 
			 Tleaveinfo leaveinfo=leaveInfoDao.get(leaveInfoIds[i]);
			 leaveinfo.setValidity("0");
			 //leaveinfo.setOperId();
			 leaveinfo.setOperDate(DateUtilExtend.getNowDate2());
			 leaveinfo.setOperTime(DateUtilExtend.getNowTime());
			 leaveInfoDao.update(leaveinfo); 
		 }
		
	}

	/**
	 * hanjiwei modify it 20060920
	 */
	public void updateLeaveInfo(Map filter) throws Exception {
		String startTime = (String)filter.get("startHour")+(String)filter.get("startMin")+"00";
		String endTime = (String)filter.get("endHour")+(String)filter.get("endMin")+"00";
		Tleaveinfo leaveinfo=leaveInfoDao.get((String)filter.get("leaveInfoId"));
		leaveinfo.setEnddate(DateUtilExtend.formatDate2((String)filter.get("endDate")));
		leaveinfo.setEndtime(endTime);
		leaveinfo.setLeaveInfo((String)filter.get("description"));
		leaveinfo.setLeaveTypeid((String)filter.get("type"));
		leaveinfo.setOperDate(DateUtilExtend.getNowDate2());
		leaveinfo.setOperId((String) filter.get("operatorid"));
		leaveinfo.setOperTime(DateUtilExtend.getNowTime());
		leaveinfo.setStartdate(DateUtilExtend.formatDate2((String)filter.get("startDate")));
		leaveinfo.setStarttime(startTime);
		leaveInfoDao.update(leaveinfo);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.check.service.LeaveInfoService#isInLeave(java.util.Map)
	 *      判断考勤天是否在请假时段中
	 */
	public List isInLeave(Map filter) throws Exception {
		/**
		String sql = "select leave.STARTDATE as startDate,leave.ENDDATE as endDate,c.CUT_NAME as clerkname "
				+ " from "
				+ " YKT_CK.LEAVEINFO leave,YKT_CUR.T_CIF_CUSTOMER  c "
				+ "where c.CUT_ID=leave.CLERKID ";
		sql += StringUtils.isNotEmpty((String) filter
				.get(CommonConfig.startDate)) ? " and leave.STARTDATE <='"
				+ (String) filter.get(CommonConfig.startDate) + " 23:59:59"
				+ "' " : "";
		sql += StringUtils
				.isNotEmpty((String) filter.get(CommonConfig.endDate)) ? " and leave.ENDDATE  >='"
				+ (String) filter.get(CommonConfig.endDate)
				+ " 00:00:00"
				+ "' "
				: "";
		sql += StringUtils.isNotEmpty(((Integer) filter.get("clerkId"))
				.toString()) ? " and leave.CLERKID  ="
				+ (Integer) filter.get("clerkId") : "";

		sql += " order by startDate asc ";

		log.debug("sql:" + sql);

		List leaveDetailList = jdbcTemplate.queryForList(sql);

		return leaveDetailList;
		**/
		return null;
	}

	/**
	 * hanjiwei add it 20060919
	 * @param date
	 * @param time
	 * @return
	 */
	private String formatDate(String date,String time){
		String fTime = "";
		String fDate = "";
		if ("".equals(date)){
			fDate = "";
		}else{
			fDate = date.substring(0,4)+"-"+date.substring(4,6)+"-"+date.substring(6,8);
		}
		if ("".equals(time)){
			fTime = "";
		}else{
			fTime = time.substring(0,2)+":"+time.substring(2,4);
		}
		return fDate+" "+fTime;
	}
}
