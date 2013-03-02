package org.king.check.service.impl;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.Constants;
import org.king.check.dao.DictionaryDao;
import org.king.check.dao.LeaveInfoDao;
import org.king.check.domain.Tleaveinfo;
import org.king.check.domain.Treportleave;
import org.king.check.domain.WebDictionary;
import org.king.check.service.LeaveInfoService;
import org.king.check.service.SysService;
import org.king.check.util.DateUtilExtend;
import org.king.check.util.MailSender;
import org.springframework.jdbc.core.JdbcTemplate;

public class LeaveInfoServiceImpl implements LeaveInfoService {

	private static final Log log = LogFactory
			.getLog(LeaveInfoServiceImpl.class);

	private LeaveInfoDao leaveInfoDao;
	
	private DictionaryDao dictionaryDao;

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
     
	 public void deleteDic(WebDictionary dic)throws Exception{
		dictionaryDao.delete(dic);
	 }
	 
	 public void saveEmail(WebDictionary dic)throws Exception{
		 dictionaryDao.save(dic);
	     
	 }

	
	  public boolean   updateEmail(WebDictionary dic)throws Exception{
		     dictionaryDao.update(dic);
		     return true;
	  }
	/**
	 * hanjiwei modify it 20060918
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
		.append("(select DICT_CAPTION from YKT_CUR.T_PIF_DICTIONARY where DICT_NO=1210 and DICT_VALUE=lea.LEAVE_TYPEID) leavetype")
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
		return null;
	}

	public Integer getLeaveDays(Map filter) throws Exception {
		return null;
	}

	public List getLeaveInfoDetail(Map filter) throws Exception {
		return null;
	}

	/**
	 * 查找要请假的人员
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
	 * 添加请假信息
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
	 * 取得请假信息
	 * hanjiwei modify it 20060918
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
		sql.append("select (select DICT_CAPTION from YKT_CUR.T_PIF_DICTIONARY where dict_no=1210 and DICT_VALUE=lea.LEAVE_TYPEID) leavetype,")
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
	 * 判断考勤天是否在请假时段中
	 */
	public List isInLeave(Map filter) throws Exception {
		return null;
	}
	
	/**
	 * 取得申请请假信息
	 * hanjiwei modify it 20061113
	 */
	public List getLeaveQuery(Map filter) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		Integer custId = (Integer)filter.get("custId");
		sql.append("select ID,CUST_ID, REPROT_DATE, REPORT_TIME, LEAVE_ID,LEAVE_BEGINDATE,")
		.append(" LEAVE_BEGINTIME, LEAVE_ENDDATE, LEAVE_ENDTIME, IFCHECK,IFAGREE,DEPT_ID,")
		.append(" COMMENTS,REPCUSTID from YKT_CK.T_REPORTLEAVE ")
		.append(" where (CUST_ID=").append(custId).append(" or REPCUSTID=").append(custId).append(")");
		if (StringUtils.isNotEmpty((String) filter.get("sDate"))) {
			sql.append(" and REPROT_DATE>='" + DateUtilExtend.formatDate2((String) filter.get("sDate")) + "'");
		}
		if (StringUtils.isNotEmpty((String) filter.get("eDate"))) {
			sql.append(" and REPROT_DATE<='" + DateUtilExtend.formatDate2((String) filter.get("eDate")) + "'");
		}
		if (!"-1".equals((String) filter.get("ifcheck"))) {
			sql.append(" and IFCHECK='" + (String) filter.get("ifcheck") + "'");
		}
		if (!"-1".equals((String) filter.get("ifagree"))) {
			sql.append(" and IFAGREE='" + (String) filter.get("ifagree") + "'");
		}
		if (StringUtils.isNotEmpty((String) filter.get("deptid"))) {
			sql.append(" and DEPT_ID='" + (String) filter.get("deptid") + "'");
		}
		//log.debug("sql:" + sql);
		List leaveQuery = jdbcTemplate.queryForList(sql.toString());
		List leaveList = new ArrayList();
		Iterator iter = leaveQuery.iterator();
		while (iter.hasNext()) {
			Map leaveMap = (Map)iter.next();
			HashMap leaveInfoList = new HashMap();
			Map custInfo = sysService.getCustInfoByCustId(Integer.parseInt(leaveMap.get("CUST_ID").toString()));
			leaveInfoList.put("ID",leaveMap.get("ID"));
			if (null==custInfo){
				leaveInfoList.put("CUST_NAME","无信息");
				leaveInfoList.put("STUEMP_NO","无信息");
			}else{
				leaveInfoList.put("CUST_NAME",custInfo.get("CUT_NAME"));
				leaveInfoList.put("STUEMP_NO",custInfo.get("STUEMP_NO"));
			}
			leaveInfoList.put("REPROT_DATE",DateUtilExtend.formatDateSelf(leaveMap.get("REPROT_DATE").toString()));
			leaveInfoList.put("REPORT_TIME",DateUtilExtend.formatTimeSelf(leaveMap.get("REPORT_TIME").toString()));
			leaveInfoList.put("LEAVE_ID",sysService.getLeaveTypeName(leaveMap.get("LEAVE_ID").toString()));
			leaveInfoList.put("LEAVE_BEGINDATE",DateUtilExtend.formatDateSelf(leaveMap.get("LEAVE_BEGINDATE").toString()));
			leaveInfoList.put("LEAVE_BEGINTIME",DateUtilExtend.formatTimeSelf(leaveMap.get("LEAVE_BEGINTIME").toString()));
			leaveInfoList.put("LEAVE_ENDDATE",DateUtilExtend.formatDateSelf(leaveMap.get("LEAVE_ENDDATE").toString()));
			leaveInfoList.put("LEAVE_ENDTIME",DateUtilExtend.formatTimeSelf(leaveMap.get("LEAVE_ENDTIME").toString()));
			leaveInfoList.put("IFCHECK",sysService.ifCheck(leaveMap.get("IFCHECK").toString()));
			leaveInfoList.put("IFAGREE",sysService.ifAgree(leaveMap.get("IFAGREE").toString()));
			leaveList.add(leaveInfoList);
		}
		return leaveList;
	}

	/**
	 * 根据登陆操作员号取得该部门所有的申请请假信息
	 * hanjiwei modify it 20061120
	 */
	public List getLeaveCheckQuery(Map filter) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		String operId = (String)filter.get("operId");
		sql.append("select ID,CUST_ID, REPROT_DATE, REPORT_TIME, LEAVE_ID,LEAVE_BEGINDATE,")
		.append(" LEAVE_BEGINTIME, LEAVE_ENDDATE, LEAVE_ENDTIME, IFCHECK,IFAGREE,DEPT_ID,")
		.append(" COMMENTS from YKT_CK.T_REPORTLEAVE ")
		.append(" where CUST_ID in (select cust_id from YKT_CK.T_CLERKINFO where DEPT_ID in ")
		.append(" (select dept_id from YKT_CK.T_OPER_LIMIT where oper_id='"+operId+"'))");
		if (StringUtils.isNotEmpty((String) filter.get("sDate"))) {
			sql.append(" and REPROT_DATE>='" + DateUtilExtend.formatDate2((String) filter.get("sDate")) + "'");
		}
		if (StringUtils.isNotEmpty((String) filter.get("eDate"))) {
			sql.append(" and REPROT_DATE<='" + DateUtilExtend.formatDate2((String) filter.get("eDate")) + "'");
		}
		if (!"-1".equals((String) filter.get("ifcheck"))) {
			sql.append(" and IFCHECK='" + (String) filter.get("ifcheck") + "'");
		}
		if (!"-1".equals((String) filter.get("ifagree"))) {
			sql.append(" and IFAGREE='" + (String) filter.get("ifagree") + "'");
		}
		if (StringUtils.isNotEmpty((String) filter.get("deptid"))) {
			sql.append(" and DEPT_ID='" + (String) filter.get("deptid") + "'");
		}
		sql.append(" order by REPROT_DATE desc");
		//log.debug("sql:" + sql);
		List leaveQuery = jdbcTemplate.queryForList(sql.toString());
		List leaveList = new ArrayList();
		Iterator iter = leaveQuery.iterator();
		while (iter.hasNext()) {
			Map leaveMap = (Map)iter.next();
			HashMap leaveInfoList = new HashMap();
			Map custInfo = sysService.getCustInfoByCustId(Integer.parseInt(leaveMap.get("CUST_ID").toString()));
			leaveInfoList.put("ID",leaveMap.get("ID"));
			if (null==custInfo){
				leaveInfoList.put("CUST_NAME","无信息");
				leaveInfoList.put("STUEMP_NO","无信息");
			}else{
				leaveInfoList.put("CUST_NAME",custInfo.get("CUT_NAME"));
				leaveInfoList.put("STUEMP_NO",custInfo.get("STUEMP_NO"));
			}
			leaveInfoList.put("REPROT_DATE",DateUtilExtend.formatDateSelf(leaveMap.get("REPROT_DATE").toString()));
			leaveInfoList.put("REPORT_TIME",DateUtilExtend.formatTimeSelf(leaveMap.get("REPORT_TIME").toString()));
			leaveInfoList.put("LEAVE_ID",sysService.getLeaveTypeName(leaveMap.get("LEAVE_ID").toString()));
			leaveInfoList.put("LEAVE_BEGINDATE",DateUtilExtend.formatDateSelf(leaveMap.get("LEAVE_BEGINDATE").toString()));
			leaveInfoList.put("LEAVE_BEGINTIME",DateUtilExtend.formatTimeSelf(leaveMap.get("LEAVE_BEGINTIME").toString()));
			leaveInfoList.put("LEAVE_ENDDATE",DateUtilExtend.formatDateSelf(leaveMap.get("LEAVE_ENDDATE").toString()));
			leaveInfoList.put("LEAVE_ENDTIME",DateUtilExtend.formatTimeSelf(leaveMap.get("LEAVE_ENDTIME").toString()));
			leaveInfoList.put("IFCHECK",sysService.ifCheck(leaveMap.get("IFCHECK").toString()));
			leaveInfoList.put("IFAGREE",sysService.ifAgree(leaveMap.get("IFAGREE").toString()));
			leaveList.add(leaveInfoList);
		}
		return leaveList;
	}

	/**
	 * 删除请假申请信息，如果已经批准请假则不能删除
	 * hanjiwei modify it 20061115
	 */
	public void deleteLeaveReport(String leaveInfoIds) throws Exception {
		//for (int i=0 ; i < leaveInfoIds.length;i++){
		leaveInfoDao.delete(getReportLeaveInfo(leaveInfoIds));
		//}
		
	}

	/**
	 * hanjiwei modify it 20061115
	 */
	public Treportleave getReportLeaveInfo(String reportLeaveId) throws Exception {
		return leaveInfoDao.getReportLeave(reportLeaveId);
	}

	public Map getReportLeaveDetailInfo(String reportLeaveId) throws Exception {
		Treportleave reportLeave = leaveInfoDao.getReportLeave(reportLeaveId);
		HashMap leaveInfoList = new HashMap();
		Map custInfo = sysService.getCustInfoByCustId(Integer.parseInt(reportLeave.getCustId().toString()));
		if (null==custInfo){
			leaveInfoList.put("CUST_NAME","无信息");
			leaveInfoList.put("STUEMP_NO","无信息");
		}else{
			leaveInfoList.put("CUST_NAME",custInfo.get("CUT_NAME"));
			leaveInfoList.put("STUEMP_NO",custInfo.get("STUEMP_NO"));
		}
		leaveInfoList.put("REPROT_DATE",DateUtilExtend.formatDateSelf(reportLeave.getReprotDate()));
		leaveInfoList.put("REPORT_TIME",DateUtilExtend.formatTimeSelf(reportLeave.getReportTime()));
		leaveInfoList.put("LEAVE_ID",sysService.getLeaveTypeName(reportLeave.getLeaveId()));
		leaveInfoList.put("LEAVE_BEGINDATE",DateUtilExtend.formatDateSelf(reportLeave.getLeaveBegindate()));
		leaveInfoList.put("LEAVE_BEGINTIME",DateUtilExtend.formatTimeSelf(reportLeave.getLeaveBegintime()));
		leaveInfoList.put("LEAVE_ENDDATE",DateUtilExtend.formatDateSelf(reportLeave.getLeaveEnddate()));
		leaveInfoList.put("LEAVE_ENDTIME",DateUtilExtend.formatTimeSelf(reportLeave.getLeaveEndtime()));
		leaveInfoList.put("IFCHECK",sysService.ifCheck(reportLeave.getIfcheck()));
		leaveInfoList.put("IFAGREE",sysService.ifAgree(reportLeave.getIfagree()));
		leaveInfoList.put("COMMENTS",reportLeave.getComments());
		if (reportLeave.getRepcustid()==null){
			leaveInfoList.put("repCustName","");
		}else{
			leaveInfoList.put("repCustName",sysService.getCustomerNameByCustomerId(reportLeave.getRepcustid()));
		}
		if (null==reportLeave.getCheckId()){
			leaveInfoList.put("CHECKNAME","");
		}else{
			leaveInfoList.put("CHECKNAME",sysService.getOperName(reportLeave.getCheckId().toString()));
		}
		
		leaveInfoList.put("CHECKDATE",DateUtilExtend.formatDateSelf(reportLeave.getCheckDate()));
		leaveInfoList.put("CHECKTIME",DateUtilExtend.formatTimeSelf(reportLeave.getCheckTime()));
		leaveInfoList.put("LEAVEINFO",reportLeave.getLeaveInfo());
		return leaveInfoList;
	}

	/**
	 * 手工考勤详细信息
	 */
	public Map getManualDetailInfo(String custId,String clerkDate,String maxTime,String minTime) throws Exception {
		StringBuffer sqlStr = new StringBuffer(1024);
		sqlStr.append("select CUST_ID, ATT_DATE, ATT_TIME,OPER_ID, OPER_DATE, OPER_TIME")
		.append(" from YKT_CK.T_ATTSERIAL_RECORD")
		.append(" where CUST_ID=").append(Integer.parseInt(custId)).append(" and ATT_DATE='")
		.append(clerkDate).append("'");
		Map manualList = (Map)jdbcTemplate.queryForList(sqlStr.toString()).get(0);
		HashMap manualMap = new HashMap();
		Map custInfo = sysService.getCustInfoByCustId(Integer.parseInt(manualList.get("CUST_ID").toString()));
		if (null==custInfo){
			manualMap.put("custName","无信息");
			manualMap.put("stuempNo","无信息");
		}else{
			manualMap.put("custName",custInfo.get("CUT_NAME"));
			manualMap.put("stuempNo",custInfo.get("STUEMP_NO"));
		}
		if (null==manualList.get("OPER_ID")){
			manualMap.put("operName","");
		}else{
			manualMap.put("operName",sysService.getOperName(manualList.get("OPER_ID").toString()));
		}
		manualMap.put("operDate",formatDate(manualList.get("OPER_DATE").toString(),""));
		manualMap.put("clerkDate",formatDate(clerkDate,""));
		manualMap.put("maxTime",formatDate("",maxTime));
		manualMap.put("minTime",formatDate("",minTime));
		return manualMap;
	}
	
	 //查询email的设置信息
	 public List QueryEmail(String dicNo) throws Exception {
		 StringBuffer sqlStr = new StringBuffer(1024)
		 .append(" select dic_no,dic_name,dic_value,dic_caption  from ykt_ck.dictionary ")
		 .append(" where dic_no ='")
		 .append(dicNo).append("'" )
		 .append("order by dic_value");
		  List mailList = jdbcTemplate.queryForList(sqlStr.toString());
		  ArrayList arrMailList = new ArrayList();
		  Iterator it =  mailList.iterator();
		  while(it.hasNext()){
			  Map mailMap = new HashMap();
			  mailMap = (Map)it.next();
			  arrMailList.add(mailMap);
		  }
		  return arrMailList;
	 }
	  


	/**
	 * 根据申请人员部门编号取得管理人员邮件列表
	 * @param deptId
	 * @return
	 * @throws Exception
	 */
	public List getMailList(String deptId) throws Exception {
		StringBuffer sqlStr = new StringBuffer(1024);
		sqlStr.append("select PERSON_CODE, PERSON_NAME,SEX, EMAIL")
		.append(" from YKT_CK.USR_PERSON")
		.append(" where email is not null and email<>'' and sex='1' and dept in(")
		.append(" select DEPT_ID from YKT_CK.DEPARTMENT where DEPT_ID='")
		.append(deptId).append("' or dept_id in (select DEPT_PARENTID")
		.append(" from YKT_CK.DEPARTMENT where DEPT_ID='").append(deptId).append("'))");
		List mailList = jdbcTemplate.queryForList(sqlStr.toString());
		return mailList;
	}
	
	public void sendMailToManager(String deptId,String custId)throws Exception{
		Iterator iter = getMailList(deptId).iterator();
		while(iter.hasNext()){
			Map mailMap = (Map)iter.next();
			Map custInfo = getCustInfo(Integer.parseInt(custId));
			String mail = mailMap.get("EMAIL").toString();
			//String mail = "qv15@yahoo.com.cn";
			StringBuffer leaveInfo = new StringBuffer(1024);
			leaveInfo.append("学/工号:").append(custInfo.get("STUEMP_NO"))
			.append("  姓名:").append(custInfo.get("CUT_NAME"))
			.append("提出请假申请,请到考勤系统中查看详细信息并审批. ")
			.append("地址").append(Constants.LINKADD);
			  List addressList = QueryEmail("001");
			  List emailList = QueryEmail("002");
			  List userList = QueryEmail("003");
	          List pwdList = QueryEmail("004");
	          List titList =QueryEmail("005");
			  String hostaddress=null;
			  if(addressList!=null && !addressList.isEmpty()){
				 hostaddress = (String)((Map)addressList.get(0)).get("dic_caption"); 
			  }
			 
			  String hostemail=null;
			  if(emailList!=null && !emailList.isEmpty()){
				hostemail  = (String)((Map)emailList.get(0)).get("dic_caption"); 
			  }
			  
			  String hostuserName=null;
			  if(userList != null && !userList.isEmpty()){
				  hostuserName= (String)((Map)userList.get(0)).get("dic_caption"); 
			  }
			  String hostpassword =null;
			  if(pwdList !=null && !pwdList.isEmpty()){
			      hostpassword = (String)((Map)pwdList.get(0)).get("dic_caption"); 
			  }
			  
			  String hostsignature =null;
			  if(titList != null && !titList.isEmpty()){
				  hostsignature = (String)((Map)titList.get(0)).get("dic_caption"); 
			  }
	         
	          
			MailSender.mailsSender(mail,hostaddress,hostemail,hostuserName,hostpassword,hostsignature,leaveInfo.toString());
		}
	}
	
	private Map getCustInfo(int custId) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select CUT_NAME,STUEMP_NO from YKT_CUR.T_CIF_CUSTOMER")
		.append(" where CUT_ID="+custId);
		List custInfo=jdbcTemplate.queryForList(sql.toString());
		Map custMap = new HashMap();
		if (!custInfo.isEmpty()){
			Map tempMap = (Map)custInfo.get(0);
			custMap.put("CUT_NAME",tempMap.get("CUT_NAME"));
			custMap.put("STUEMP_NO",tempMap.get("STUEMP_NO"));
			return custMap;
		}else{
			return null;
		}
	}
	
	/**
	 * hanjiwei modify it 20061115
	 */
	public void saveLeaveReport(Map filter) throws Exception {
		String startDate = (String) filter.get("startDate");
		String endDate = (String) filter.get("endDate");
		Integer custId = (Integer) filter.get("custId");
		Integer repCustId = (Integer) filter.get("repCustId");

		startDate = DateUtilExtend.formatDate2(startDate);
		endDate = DateUtilExtend.formatDate2(endDate);

		String startTime = (String) filter.get("startHour")+ (String) filter.get("startMin") + "00";
		String endTime = (String) filter.get("endHour")+ (String) filter.get("endMin") + "00";
		
		String deptId = (String) filter.get("deptId");
		String leaveId = (String) filter.get("leaveId");
		String leaveInfo = (String) filter.get("leaveInfo");
		
		String reportDate = DateUtilExtend.getNowDate2();
		String reportTime = DateUtilExtend.getNowTime();
		//判断该人员是否在该时间段请过假
		Treportleave getReportLeave = null;
		if ((null!=filter.get("reportLeaveId"))&&(!"".equals(filter.get("reportLeaveId").toString()))){
			getReportLeave = leaveInfoDao.getReportLeave((String)filter.get("reportLeaveId"));
		}
		
		if ((null==getReportLeave)){
			Treportleave reportLeave = new Treportleave();
			reportLeave.setCustId(custId);
			reportLeave.setReprotDate(reportDate);
			reportLeave.setReportTime(reportTime);
			reportLeave.setLeaveBegindate(startDate);
			reportLeave.setLeaveBegintime(startTime);
			reportLeave.setLeaveEnddate(endDate);
			reportLeave.setLeaveEndtime(endTime);
			reportLeave.setDeptId(deptId);
			reportLeave.setIfcheck("0");
			reportLeave.setIfagree("9");
			reportLeave.setLeaveId(leaveId);
			reportLeave.setLeaveInfo(leaveInfo);
			reportLeave.setRepcustid(repCustId);
			leaveInfoDao.save(reportLeave);
			sendMailToManager(deptId,custId.toString());
		}else{
			getReportLeave.setCustId(custId);
			getReportLeave.setReprotDate(reportDate);
			getReportLeave.setReportTime(reportTime);
			getReportLeave.setLeaveBegindate(startDate);
			getReportLeave.setLeaveBegintime(startTime);
			getReportLeave.setLeaveEnddate(endDate);
			getReportLeave.setLeaveEndtime(endTime);
			getReportLeave.setDeptId(deptId);
			getReportLeave.setIfcheck("0");
			getReportLeave.setIfagree("9");
			getReportLeave.setLeaveId(leaveId);
			getReportLeave.setLeaveInfo(leaveInfo);
			getReportLeave.setRepcustid(repCustId);
			leaveInfoDao.update(getReportLeave);
		}
	}

	/**
	 * 请假审批
	 */
	public void reportLeaveCheck(String reportLeaveId,Map filter) throws Exception {
		String agree = (String) filter.get("ifagree");
		String comments = (String) filter.get("comments");
		String operId = (String) filter.get("operid"); 
		String operDate = DateUtilExtend.getNowDate2();
		String operTime = DateUtilExtend.getNowTime();
		if ("1".equals(agree)){
			updateReportLeave(reportLeaveId, agree, comments, operDate, operTime, operId);
			reportLeaveCheck(reportLeaveId, operDate, operTime);
		}else{
			updateReportLeave(reportLeaveId, agree, comments, operDate, operTime, operId);
		}
		
	}

	private void reportLeaveCheck(
			String reportLeaveId,
			String operDate,
			String operTime)throws Exception{
		Treportleave reportLeave = getReportLeaveInfo(reportLeaveId);
		Tleaveinfo leaveinfo = new Tleaveinfo();
		leaveinfo.setLeaveId(reportLeaveId);
		leaveinfo.setCustId(reportLeave.getCustId());
		leaveinfo.setEnddate(reportLeave.getLeaveEnddate());
		leaveinfo.setEndtime(reportLeave.getLeaveEndtime());
		leaveinfo.setStartdate(reportLeave.getLeaveBegindate());
		leaveinfo.setStarttime(reportLeave.getLeaveBegintime());
		leaveinfo.setLeaveInfo(reportLeave.getLeaveInfo());
		leaveinfo.setOperId(reportLeave.getCheckId().toString());
		leaveinfo.setOperDate(operDate);
		leaveinfo.setOperTime(operTime);
		leaveinfo.setLeaveTypeid(reportLeave.getLeaveId());
		leaveinfo.setValidity("1");
		leaveInfoDao.save(leaveinfo);
	}


	private void updateReportLeave(
			String reportLeaveId,
			String agree,
			String comments,
			String operDate,
			String operTime,
			String operId)throws Exception{
		Treportleave reportLeave = getReportLeaveInfo(reportLeaveId);
		if (null!=reportLeave){
			reportLeave.setCheckDate(operDate);
			reportLeave.setCheckId(operId);
			reportLeave.setCheckTime(operTime);
			reportLeave.setIfagree(agree);
			reportLeave.setIfcheck("1");
			reportLeave.setComments(comments);
			leaveInfoDao.update(reportLeave);
		}
	}
	/**
	 * 请假审批取消保存
	 */
	public void reportLeaveCheckCancel(String reportLeaveIds, Map filter) throws Exception {
		//删除请假审批信息
		//把是否审批修改为没有审批
		reportLeaveCheckDelete(reportLeaveIds);
		updateReportLeaveCancel(reportLeaveIds);
	}

	private void updateReportLeaveCancel(
			String reportLeaveId)throws Exception{
		Treportleave reportLeave = getReportLeaveInfo(reportLeaveId);
		if (null!=reportLeave){
			reportLeave.setCheckDate("");
			reportLeave.setCheckId("");
			reportLeave.setCheckTime("");
			reportLeave.setIfagree("9");
			reportLeave.setIfcheck("0");
			reportLeave.setComments("");
			leaveInfoDao.update(reportLeave);
		}
	}
	private void reportLeaveCheckDelete(
			String reportLeaveId)throws Exception{
		Tleaveinfo leaveinfo = leaveInfoDao.getReportLeaveCheck(reportLeaveId);
		leaveInfoDao.delete(leaveinfo);
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


	public DictionaryDao getDictionaryDao() {
		return dictionaryDao;
	}


	public void setDictionaryDao(DictionaryDao dictionaryDao) {
		this.dictionaryDao = dictionaryDao;
	}
	
}
