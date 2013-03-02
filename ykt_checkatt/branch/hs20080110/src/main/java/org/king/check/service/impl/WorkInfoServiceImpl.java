package org.king.check.service.impl;

import java.io.Serializable;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.commons.lang.StringUtils;
import org.king.check.Constants;
import org.king.check.config.ClerkConfig;
import org.king.check.dao.DutyTimeDAO;
import org.king.check.dao.WorkInfoDao;
import org.king.check.domain.Tattserial;
import org.king.check.domain.TattserialId;
import org.king.check.domain.Tattserialrecord;
import org.king.check.domain.Tcheckattinfo;
import org.king.check.domain.TcheckattinfoId;
import org.king.check.domain.Tcheckattreport;
import org.king.check.domain.TcheckattreportId;
import org.king.check.service.SysService;
import org.king.check.service.WorkInfoService;
import org.king.check.util.DateUtilExtend;
import org.king.check.util.GetPropertiesUtil;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.springframework.jdbc.core.JdbcTemplate;
import org.apache.commons.lang.builder.EqualsBuilder;
import org.apache.commons.lang.builder.HashCodeBuilder;
import org.apache.commons.lang.builder.ToStringBuilder;
import org.apache.commons.lang.builder.CompareToBuilder;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.springframework.jdbc.core.PreparedStatementSetter;

public class WorkInfoServiceImpl extends BaseService implements Comparable,
		WorkInfoService {
	private static final Log log = LogFactory.getLog(WorkInfoServiceImpl.class);

	private WorkInfoDao workInfodao;

	private DutyTimeDAO dutytimedao;

	private JdbcTemplate jdbcTemplate;

	private SysService sysService;
	
	

	private static SimpleDateFormat formatter_yyyymmdd = new SimpleDateFormat(
			"yyyyMM");

	public void setWorkInfodao(WorkInfoDao workInfodao) {
		this.workInfodao = workInfodao;
	}

	public void setDutytimedao(DutyTimeDAO dutytimedao) {
		this.dutytimedao = dutytimedao;
	}

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	public void saveWorkInfo(Tattserialrecord workInfo)
			throws BusinessException {
		this.workInfodao.save(workInfo);
	}

	public void updateWorkInfo(Tattserialrecord workInfo)
			throws BusinessException {
		this.workInfodao.update(workInfo);
	}

	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}


	/**
	 * 取得已经手工考勤过的列表
	 */
	public List getManualCheckList(int custId, String attDate) throws Exception {
		StringBuffer querySql = new StringBuffer(1024);
		querySql
				.append(" select rec.CUST_ID, rec.ATT_DATE,info.IFOFFICE")
				.append(" from YKT_CK.T_ATTSERIAL_RECORD rec")
				.append(
						" left join YKT_CK.T_CLERKINFO info on rec.CUST_ID=info.CUST_ID")
				.append(" where rec.ATT_DATE='").append(attDate).append(
						"' and rec.CUST_ID=").append(custId);
		List manualCehck = jdbcTemplate.queryForList(querySql.toString());
		return manualCehck;
	}

	/**
	 * 根据人员编号和考勤日期取得该人员的所有考勤流水记录
	 * 
	 * @param custId
	 * @param signDate
	 * @return
	 */
	private List getCustWorkSerial(String custId, String signDate) {
		StringBuffer querySql = new StringBuffer(1024);
		querySql.append(
				" select ATT_DATE , ATT_TIME  from YKT_CK.T_ATTSERIAL_RECORD")
				.append(" where cust_id=? and ATT_DATE=?").append(" union all")
				.append(" select ATT_DATE, ATT_TIME from YKT_CK.T_ATTSERIAL")
				.append(" where cust_id=? and ATT_DATE=?");
		List CustWorkSerialMap = jdbcTemplate.queryForList(querySql.toString(),
				new Object[] { Integer.valueOf(custId), signDate,
						Integer.valueOf(custId), signDate });
		return CustWorkSerialMap;
	}

	private String getDeptIdByCustId(String custId) {
		String querySql = "select DEPT_ID from YKT_CK.T_CLERKINFO where CUST_ID=?";
		List deptList = jdbcTemplate.queryForList(querySql,
				new Object[] { Integer.valueOf(custId) });
		String deptId = null;
		if (null != deptList) {
			Map tmpMap = (Map) deptList.get(0);
			deptId = tmpMap.get("DEPT_ID").toString();
		}
		return deptId;
	}

	/**
	 * 非坐班人员考勤信息 hanjiwei modify it 20061019
	 */
	private void dealWithNoSeatClerk(Map filter) throws Exception {
		String signDate = (String) filter.get("signDate");
		String custId = String.valueOf(filter.get("custId"));

		List cardList = getCustWorkSerial(custId, signDate);
		String deptId = getDeptIdByCustId(custId);
		String minTime = "235959";
		String maxTime = "000000";
		if (!cardList.isEmpty()) {
			Iterator checkTime = cardList.iterator();
			String currentTime = "000000";
			while (checkTime.hasNext()) {
				Map queryMap = (Map) checkTime.next();
				currentTime = (String) queryMap.get("ATT_TIME");
				if (DateUtilExtend.timeDiff1(currentTime, minTime) > 0) {
					minTime = currentTime;
				}
				if (DateUtilExtend.timeDiff1(currentTime, maxTime) < 0) {
					maxTime = currentTime;
				}
			}
		} else {
			minTime = "000000";
			maxTime = "000000";
		}
		TcheckattinfoId attInfoId = new TcheckattinfoId();
		Tcheckattinfo attInfo = new Tcheckattinfo();
		attInfoId.setCustId(new Integer(Integer.parseInt(custId)));
		attInfoId.setCheckDate(signDate);
		attInfo.setId(attInfoId);
		attInfo.setDeptId(deptId);
		attInfo.setFactOntime(minTime);
		attInfo.setFactOfftime(maxTime);
		attInfo.setIfoffice("2");
		if (exitRecordByCustId(custId, signDate)) {
			dutytimedao.update(attInfo);
		} else {
			dutytimedao.save(attInfo);
		}
	}

	/**
	 * 取得个人考勤详细信息
	 * 
	 * @param custId
	 * @return
	 */
	public List getOneCheckDetail(int custId, String beginDate, String endDate)
			throws Exception {
		StringBuffer custSql = new StringBuffer(1024);
		custSql.append("select CUT_NAME,  STUEMP_NO ").append(
				" from YKT_CUR.T_CIF_CUSTOMER where CUT_ID=" + custId);
		Map cust = jdbcTemplate.queryForMap(custSql.toString());
		String checkDate = endDate;
		List personalCheckDetail = new ArrayList();
		while (DateUtilExtend.diffDate(beginDate, checkDate) >= 0) {
			StringBuffer seriSql = new StringBuffer();
			seriSql
					.append("select CUST_ID, CARD_ID, ATT_DATE, ATT_TIME")
					.append(" from YKT_CK.T_ATTSERIAL")
					.append(" where cust_id=")
					.append(custId)
					.append(" and ATT_DATE='")
					.append(checkDate)
					.append("'")
					.append(" union select CUST_ID, CARD_ID,ATT_DATE, ATT_TIME")
					.append(" from YKT_CK.T_ATTSERIAL_RECORD").append(
							" where cust_id=").append(custId).append(
							" and ATT_DATE='").append(checkDate).append("'");
			List resList = jdbcTemplate.queryForList(seriSql.toString());
			String minTime = "235959";
			String maxTime = "000000";
			String currTime = "000000";
			Iterator dutyIter = resList.iterator();
			while (dutyIter.hasNext()) {
				Map attS = (Map) dutyIter.next();
				currTime = attS.get("ATT_TIME").toString();
				if (DateUtilExtend.timeDiff1(maxTime, currTime) > 0) {
					maxTime = currTime;
				}
				if (DateUtilExtend.timeDiff1(minTime, currTime) < 0) {
					minTime = currTime;
				}
			}
			Map checkDetail = new HashMap();
			checkDetail.put("STUEMP_NO", cust.get("STUEMP_NO"));
			checkDetail.put("CUT_NAME", cust.get("CUT_NAME"));
			checkDetail.put("IFOFFICE", "0");
			checkDetail.put("CHECK_DATE", DateUtilExtend
					.formatDateSelf(checkDate));
			checkDetail.put("FACT_ONTIME", formatTime(minTime));
			checkDetail.put("FACT_OFFTIME", formatTime(maxTime));

			personalCheckDetail.add(checkDetail);
			checkDate = DateUtilExtend.addDate2(checkDate, -1);
		}

		/*
		 * StringBuffer querySql = new StringBuffer(1024);querySql.append(
		 * "select CUST_ID, CHECK_DATE, IFOFFICE, FACT_ONTIME, FACT_OFFTIME,")
		 * .append(
		 * "FACT_ONTIME1, FACT_OFFTIME1, FACT_ONTIME2, FACT_OFFTIME2, FACT_ONTIME3, "
		 * ).append(
		 * "FACT_OFFTIME3, FACT_ONTIME4, FACT_OFFTIME4 from YKT_CK.T_CHECKATT_INFO"
		 * )
		 * .append(" where CUST_ID=").append(custId).append(" and CHECK_DATE>='"
		 * ).append(beginDate)
		 * .append("' and CHECK_DATE<='").append(endDate).append
		 * ("' order by CHECK_DATE desc");
		 * 
		 * List result = jdbcTemplate.queryForList(querySql.toString());
		 * StringBuffer custSql = new StringBuffer(1024);
		 * custSql.append("select CUT_NAME,  STUEMP_NO ")
		 * .append(" from YKT_CUR.T_CIF_CUSTOMER where CUT_ID="+custId); Map
		 * cust = jdbcTemplate.queryForMap(custSql.toString());
		 * 
		 * List personalCheckDetail = new ArrayList(); Iterator iter =
		 * result.iterator(); while (iter.hasNext()){ Map checkDetail = new
		 * HashMap(); Map queryMap = (Map) iter.next();
		 * 
		 * checkDetail.put("STUEMP_NO",cust.get("STUEMP_NO"));
		 * checkDetail.put("CUT_NAME",cust.get("CUT_NAME"));
		 * checkDetail.put("CHECK_DATE",queryMap.get("CHECK_DATE"));
		 * checkDetail.put("IFOFFICE",queryMap.get("IFOFFICE").toString()); if
		 * (null==queryMap.get("FACT_ONTIME")){
		 * checkDetail.put("FACT_ONTIME",""); }else{
		 * checkDetail.put("FACT_ONTIME"
		 * ,formatTime(queryMap.get("FACT_ONTIME").toString())); } if
		 * (null==queryMap.get("FACT_OFFTIME")){
		 * checkDetail.put("FACT_OFFTIME",""); }else{
		 * checkDetail.put("FACT_OFFTIME"
		 * ,formatTime(queryMap.get("FACT_OFFTIME").toString())); } if
		 * (null==queryMap.get("FACT_ONTIME1")){
		 * checkDetail.put("FACT_ONTIME1",""); }else{
		 * checkDetail.put("FACT_ONTIME1"
		 * ,formatTime(queryMap.get("FACT_ONTIME1").toString())); } if
		 * (null==queryMap.get("FACT_OFFTIME1")){
		 * checkDetail.put("FACT_OFFTIME1",""); }else{
		 * checkDetail.put("FACT_OFFTIME1"
		 * ,formatTime(queryMap.get("FACT_OFFTIME1").toString())); } if
		 * (null==queryMap.get("FACT_ONTIME2")){
		 * checkDetail.put("FACT_ONTIME2",""); }else{
		 * checkDetail.put("FACT_ONTIME2"
		 * ,formatTime(queryMap.get("FACT_ONTIME2").toString())); } if
		 * (null==queryMap.get("FACT_OFFTIME2")){
		 * checkDetail.put("FACT_OFFTIME2",""); }else{
		 * checkDetail.put("FACT_OFFTIME2"
		 * ,formatTime(queryMap.get("FACT_OFFTIME2").toString())); } if
		 * (null==queryMap.get("FACT_ONTIME3")){
		 * checkDetail.put("FACT_ONTIME3",""); }else{
		 * checkDetail.put("FACT_ONTIME3"
		 * ,formatTime(queryMap.get("FACT_ONTIME3").toString())); } if
		 * (null==queryMap.get("FACT_OFFTIME3")){
		 * checkDetail.put("FACT_OFFTIME3",""); }else{
		 * checkDetail.put("FACT_OFFTIME3"
		 * ,formatTime(queryMap.get("FACT_OFFTIME3").toString())); } if
		 * (null==queryMap.get("FACT_ONTIME4")){
		 * checkDetail.put("FACT_ONTIME4",""); }else{
		 * checkDetail.put("FACT_ONTIME4"
		 * ,formatTime(queryMap.get("FACT_ONTIME4").toString())); } if
		 * (null==queryMap.get("FACT_OFFTIME4")){
		 * checkDetail.put("FACT_OFFTIME4",""); }else{
		 * checkDetail.put("FACT_OFFTIME4"
		 * ,formatTime(queryMap.get("FACT_OFFTIME4").toString())); }
		 * 
		 * checkDetail.put("STUEMP_NO",cust.get("STUEMP_NO"));
		 * checkDetail.put("CUT_NAME",cust.get("CUT_NAME"));
		 * checkDetail.put("IFOFFICE","0");
		 * checkDetail.put("CHECK_DATE",queryMap.get("att_date"));
		 * checkDetail.put
		 * ("FACT_ONTIME",formatTime(queryMap.get("startTime").toString()));
		 * checkDetail
		 * .put("FACT_OFFTIME",formatTime(queryMap.get("endTime").toString()));
		 * 
		 * personalCheckDetail.add(checkDetail); }
		 */

		return personalCheckDetail;
	}

	/**
	 * 为手工打卡搜索考勤人员 hanjiwei modify it 20060918
	 */
	public List searchClerkForReg(Map filter) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql
				.append(
						"select cust.CUT_ID, cust.CUT_NAME,  cust.STUEMP_NO, cust.CLASSDEPT_NO,")
				.append(
						" dept.DEPT_NAME,clerk.IFOFFICE,dict.DICT_CAPTION from YKT_CK.T_CLERKINFO clerk ")
				.append(
						" left join YKT_CUR.T_CIF_CUSTOMER cust on clerk.CUST_ID=cust.CUT_ID")
				.append(
						" left join YKT_CK.DEPARTMENT dept on dept.DEPT_ID=clerk.DEPT_ID")
				.append(
						" left join YKT_CUR.T_PIF_DICTIONARY dict on dict.DICT_VALUE=clerk.IFOFFICE")
				.append(" where dict.DICT_NO=1200");
		if (StringUtils.isNotEmpty((String) filter.get("trueName"))) {
			sql.append(" and cust.CUT_NAME like '%"
					+ (String) filter.get("trueName") + "%'");
		}
		if (StringUtils.isNotEmpty((String) filter.get("stuNumber"))) {
			sql.append(" and cust.STUEMP_NO='"
					+ (String) filter.get("stuNumber") + "'");
		}
		if ((!"".equals((String) filter.get("deptId")))
				&& (!"all".equals(filter.get("deptId")))) {
			sql.append(" and clerk.dept_id='" + (String) filter.get("deptId")
					+ "'");
		} else {
			sql.append(" and clerk.dept_id in("
					+ getDeptStrByAccountId((String) filter.get("accountId"))
					+ ")");
		}

		if (StringUtils.isNotEmpty((String) filter.get("clerkType"))) {
			sql.append(" and clerk.IFOFFICE='"
					+ (String) filter.get("clerkType") + "'");
		}
		List clerkList = jdbcTemplate.queryForList(sql.toString());

		return clerkList;
	}

	/**
	 * 手工打卡修改记录查找 hanjiwei modify it 20060918
	 */
	public List searchClerkForModify(Map filter) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql
				.append(
						"select cust.CUT_NAME,cust.STUEMP_NO, cust.CLASSDEPT_NO, manual.CUST_ID,")
				.append(
						" manual.ATT_DATE,manual.ATT_TIME,dept.DEPT_NAME,manual.serial_id")
				.append(" from YKT_CK.T_ATTSERIAL_RECORD manual")
				.append(
						" left join YKT_CK.T_CLERKINFO clerk on clerk.CUST_ID=manual.CUST_ID")
				.append(
						" left join YKT_CUR.T_CIF_CUSTOMER cust on manual.CUST_ID=cust.CUT_ID")
				.append(
						" left join YKT_CK.DEPARTMENT dept on dept.DEPT_ID=clerk.DEPT_ID")
				.append(" where manual.ATT_DATE>='").append(
						filter.get("beginDate").toString()).append(
						"' and manual.ATT_DATE<='").append(
						filter.get("endDate").toString()).append("'");
		if (StringUtils.isNotEmpty((String) filter.get("trueName"))) {
			sql.append(" and cust.CUT_NAME like '%"
					+ (String) filter.get("trueName") + "%'");
		}
		if (StringUtils.isNotEmpty((String) filter.get("stuNumber"))) {
			sql.append(" and cust.STUEMP_NO='"
					+ (String) filter.get("stuNumber") + "'");
		}
		if (!"".equals((String) filter.get("deptId"))) {
			sql.append(" and clerk.dept_id='" + (String) filter.get("deptId")
					+ "'");
		} else {
			sql.append(" and clerk.dept_id in("
					+ getDeptStrByAccountId((String) filter.get("accountId"))
					+ ")");
		}
		// log.debug("sql:" + sql);
		sql.append(" order by manual.ATT_DATE desc");
		List clerkList = jdbcTemplate.queryForList(sql.toString());
		List clerkManual = new ArrayList();
		if (clerkList.size() > 0) {
			Iterator iter = clerkList.iterator();
			while (iter.hasNext()) {
				Map clerkMap = (Map) iter.next();
				Map resultMap = new HashMap();
				resultMap.put("CUT_NAME", clerkMap.get("CUT_NAME"));
				resultMap.put("STUEMP_NO", clerkMap.get("STUEMP_NO"));
				resultMap.put("CLASSDEPT_NO", clerkMap.get("CLASSDEPT_NO"));
				resultMap.put("CUST_ID", clerkMap.get("CUST_ID"));
				resultMap.put("ATT_DATE", DateUtilExtend
						.formatDateSelf(clerkMap.get("ATT_DATE").toString()));
				resultMap.put("ATT_TIME", DateUtilExtend
						.formatTimeSelf(clerkMap.get("ATT_TIME").toString()));
				resultMap.put("DEPT_NAME", clerkMap.get("DEPT_NAME"));
				resultMap.put("serial_id", clerkMap.get("serial_id"));
				clerkManual.add(resultMap);
			}
		}
		return clerkManual;
	}

	/**
	 * 打卡流水记录查找 hanjiwei modify it 20060918
	 */
	public List searchCardClerk(Map filter) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql
				.append(
						"select cust.CUT_NAME,cust.STUEMP_NO, cust.CLASSDEPT_NO, att.CUST_ID,")
				.append(
						" att.ATT_DATE,att.ATT_TIME,dept.DEPT_NAME,att.serial_id,att.status,")
				.append(" att.device_id from YKT_CK.T_ATTSERIAL att")
				.append(
						" left join YKT_CK.T_CLERKINFO clerk on clerk.CUST_ID=att.CUST_ID")
				.append(
						" left join YKT_CUR.T_CIF_CUSTOMER cust on att.CUST_ID=cust.CUT_ID")
				.append(
						" left join YKT_CK.DEPARTMENT dept on dept.DEPT_ID=clerk.DEPT_ID")
				.append(" where att.ATT_DATE>='").append(
						filter.get("beginDate").toString()).append(
						"' and att.ATT_DATE<='").append(
						filter.get("endDate").toString()).append("'");
		if (StringUtils.isNotEmpty((String) filter.get("trueName"))) {
			sql.append(" and cust.CUT_NAME like '%"
					+ (String) filter.get("trueName") + "%'");
		}
		if (StringUtils.isNotEmpty((String) filter.get("stuNumber"))) {
			sql.append(" and cust.STUEMP_NO='"
					+ (String) filter.get("stuNumber") + "'");
		}
		if (!"".equals((String) filter.get("deptId"))) {
			sql.append(" and clerk.dept_id='" + (String) filter.get("deptId")
					+ "'");
		} else {
			sql.append(" and clerk.dept_id in("
					+ getDeptStrByAccountId((String) filter.get("accountId"))
					+ ")");
		}
		// log.debug("sql:" + sql);
		sql.append(" order by att.ATT_DATE desc");
		List clerkList = jdbcTemplate.queryForList(sql.toString());
		List clerkManual = new ArrayList();
		if (clerkList.size() > 0) {
			Iterator iter = clerkList.iterator();
			while (iter.hasNext()) {
				Map clerkMap = (Map) iter.next();
				Map resultMap = new HashMap();
				resultMap.put("CUT_NAME", clerkMap.get("CUT_NAME"));
				resultMap.put("STUEMP_NO", clerkMap.get("STUEMP_NO"));
				resultMap.put("CLASSDEPT_NO", clerkMap.get("CLASSDEPT_NO"));
				resultMap.put("CUST_ID", clerkMap.get("CUST_ID"));
				resultMap.put("ATT_DATE", DateUtilExtend
						.formatDateSelf(clerkMap.get("ATT_DATE").toString()));
				resultMap.put("ATT_TIME", DateUtilExtend
						.formatTimeSelf(clerkMap.get("ATT_TIME").toString()));
				resultMap.put("STATUS", getStatus(clerkMap.get("status")
						.toString()));
				resultMap.put("STAT", clerkMap.get("status"));
				resultMap.put("DEVICE_ID", clerkMap.get("device_id"));
				resultMap.put("DEPT_NAME", clerkMap.get("DEPT_NAME"));
				resultMap.put("serial_id", clerkMap.get("serial_id"));
				clerkManual.add(resultMap);
			}
		}
		return clerkManual;
	}

	private String getStatus(String status) {
		if ("1".equals(status)) {
			return "有效";
		} else {
			return "*无效*";
		}
	}

	public Tattserial getAttSerial(int seriId, int devId) {
		/*
		 * StringBuffer sql = new StringBuffer(512);
		 * sql.append(" from Tattserial where serialId=? and deviceId=?"); Map
		 * seriMap = jdbcTemplate.queryForMap(sql.toString(),new Object[]{new
		 * Integer(seriId),new Integer(devId)}); return (Tattserial)seriMap;
		 */
		TattserialId attSerId = new TattserialId();
		attSerId.setDeviceId(new Integer(devId));
		attSerId.setSerialId(new Integer(seriId));
		return workInfodao.getAttSeri(attSerId);
	}

	public Map searchClerkForModify(int seriId) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql
				.append(
						"select cust.CUT_NAME,cust.STUEMP_NO, cust.CLASSDEPT_NO, manual.CUST_ID,")
				.append(
						" manual.ATT_DATE,manual.ATT_TIME,dept.DEPT_NAME,manual.serial_id,")
				.append(" manual.OPER_DATE,manual.OPER_TIME,per.person_name")
				.append(" from YKT_CK.T_ATTSERIAL_RECORD manual")
				.append(
						" left join YKT_CK.T_CLERKINFO clerk on clerk.CUST_ID=manual.CUST_ID")
				.append(
						" left join YKT_CUR.T_CIF_CUSTOMER cust on manual.CUST_ID=cust.CUT_ID")
				.append(
						" left join YKT_CK.DEPARTMENT dept on dept.DEPT_ID=clerk.DEPT_ID")
				.append(
						" left join ykt_ck.usr_person per on manual.oper_id=per.id ")
				.append(" where manual.serial_id=").append(seriId);
		// log.debug("sql:" + sql);
		Map clerkMap = jdbcTemplate.queryForMap(sql.toString());
		Map resultMap = new HashMap();
		String operDate = DateUtilExtend.formatDateSelf(clerkMap.get(
				"OPER_DATE").toString())
				+ "--"
				+ DateUtilExtend.formatTimeSelf(clerkMap.get("OPER_TIME")
						.toString());
		resultMap.put("CUT_NAME", clerkMap.get("CUT_NAME"));
		resultMap.put("STUEMP_NO", clerkMap.get("STUEMP_NO"));
		resultMap.put("CLASSDEPT_NO", clerkMap.get("CLASSDEPT_NO"));
		resultMap.put("CUST_ID", clerkMap.get("CUST_ID"));
		resultMap.put("ATT_DATE", DateUtilExtend.formatDate3(clerkMap.get(
				"ATT_DATE").toString()));
		resultMap.put("ATT_HOUR", DateUtilExtend.getHour(clerkMap.get(
				"ATT_TIME").toString()));
		resultMap.put("ATT_MIN", DateUtilExtend.getMin(clerkMap.get("ATT_TIME")
				.toString()));
		resultMap.put("DEPT_NAME", clerkMap.get("DEPT_NAME"));
		resultMap.put("serial_id", clerkMap.get("serial_id"));
		resultMap.put("oper_name", clerkMap.get("person_name"));
		resultMap.put("oper_date", operDate);
		return resultMap;
	}

	/**
	 * 根据登陆操作员编号取得其所拥有权限的部门
	 * 
	 * @param accountId
	 * @return
	 */
	private String getDeptStrByAccountId(String accountId) {
		List departList = null;
		StringBuffer deptStr = new StringBuffer(1024);
		try {
			departList = sysService.getDeptList(accountId);
			if (departList.size() > 0) {
				for (int i = 0; i < departList.size(); i++) {
					Map deptMap = (Map) departList.get(i);
					if (i == departList.size() - 1) {
						deptStr.append("'" + deptMap.get("deptId") + "'");
					} else {
						deptStr.append("'" + deptMap.get("deptId") + "',");
					}
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return deptStr.toString();
	}

	/**
	 * 手工打卡 hanjiwei modify it 20060918
	 */
	public void manualRegister(List filter) throws Exception {
		if (filter != null && !filter.isEmpty()) {
			for (int i = 0; i < filter.size(); i++) {
				Tattserialrecord clerk = (Tattserialrecord) filter.get(i);
				workInfodao.save(clerk);
			}
		}
	}

	public Tattserialrecord get(Serializable id) {
		return workInfodao.get(id);
	}

	/**
	 * 手工打卡删除 hanjiwei add it 20061227
	 */
	public void deleteRegister(Tattserialrecord att) throws Exception {
		workInfodao.delete(att);
	}

	/**
	 * 修改手工打卡信息 hanjiwei add it 20061227
	 */
	public void updateRegister(Tattserialrecord att) throws Exception {
		workInfodao.update(att);
	}

	public void updateSeri(Tattserial att) {
		workInfodao.update(att);
	}

	// 根据客户号查出卡号
	public Integer getCardIdByCustId(String custId) throws Exception {
		String sql = "select CARD_ID from YKT_CUR.T_PIF_CARD where  STATE_ID='1000' and COSUMER_ID="
				+ custId;
		List tempList = jdbcTemplate.queryForList(sql);
		Integer cardId = new Integer(0);
		if (tempList.size() > 0) {
			Map tmpMap = (Map) tempList.get(0);
			cardId = new Integer(tmpMap.get("CARD_ID").toString());
		}
		return cardId;
	}

	// 根据客户号查出物理卡号
	public String getPhyCardIdByCustId(String custId) throws Exception {
		String sql = "select PHYSICAL_NO from YKT_CUR.T_PIF_CARD where  STATE_ID='1000' and COSUMER_ID="
				+ custId;
		List tempList = jdbcTemplate.queryForList(sql);
		String phyCardId = null;
		if (tempList.size() > 0) {
			Map tmpMap = (Map) tempList.get(0);
			phyCardId = (String) tmpMap.get("PHYSICAL_NO");
		}
		return phyCardId;
	}

	// 判断考勤人员的卡号是否有效
	public String[] judgeIsOwnValidCardByClerkId(String[] clerkIds)
			throws Exception {
		String sql = "";
		sql = "select CARD_ID from YKT_CUR.T_PIF_CARD where  STATE_ID='1000'";
		String card_number[] = new String[clerkIds.length];

		for (int i = 0; i < clerkIds.length; i++) {
			String tempStr = "  and COSUMER_ID=" + clerkIds[i];
			// log.debug("sql:" + sql + tempStr);
			List tempList = jdbcTemplate.queryForList(sql + tempStr);
			if (tempList.isEmpty()) {
				return null;
			} else {
				Map map = (Map) tempList.get(0);
				Integer temp = (Integer) map.get("card_id");
				card_number[i] = temp.toString();
			}
		}
		return card_number;
	}

	/**
	 * 判断是否存在考勤记录，存在返回true hanjiwei add it 20061020
	 * 
	 * @param custId
	 * @param workDate
	 * @return
	 */
	private boolean exitRecordByCustId(String custId, String workDate) {
		StringBuffer querySql = new StringBuffer(1024);
		querySql.append("select * from YKT_CK.T_CHECKATT_INFO").append(
				" where CHECK_DATE='" + workDate + "'" + " and CUST_ID="
						+ custId);
		List workConfInfoList = jdbcTemplate.queryForList(querySql.toString());
		if (workConfInfoList.isEmpty()) {
			return false;
		} else {
			return true;
		}
	}

	/**
	 * 判断是否存在考勤报表，存在返回true hanjiwei modify it 20061020
	 * 
	 * @param custId
	 * @param workDate
	 * @return
	 */
	private boolean exitReportByCustId(String custId, String workDate) {
		StringBuffer querySql = new StringBuffer(1024);
		querySql.append("select * from YKT_CK.T_CHECKATT_REPORT").append(
				" where CHECK_DATE='" + workDate + "'" + " and CUST_ID="
						+ custId);
		List workConfInfoList = jdbcTemplate.queryForList(querySql.toString());
		if (workConfInfoList.isEmpty()) {
			return false;
		} else {
			return true;
		}
	}

	/**
	 * 根据客户号和日期取得该人员的考勤制度信息 hanjiwei modify it 20061019
	 * 
	 * @param custId
	 * @return
	 */
	private List getWorkConfInfoByCustId(String custId, String workDate) {
		StringBuffer querySql = new StringBuffer(1024);
		querySql
				.append(
						"select clerk.CUST_ID,clerk.DEPT_ID,clerk.IFOFFICE,clerk.AHEAD_OVERTIME,")
				.append(
						"clerk.DELAY_OVERTIME,clerk.OVERTIME_VALUE,clerk.TWOREST_OVERTIME,clerk.HOLIDAY_OVERTIME,")
				.append(
						"workConf.WORKCONF_ID,workConf.WORKCONF_NAME,workConf.OVERDUE_TIME,workConf.LEAVEEARLY_TIME,")
				.append(
						"workConf.OVER_TIME, workConf.DELAY_TIME, workConf.CHECK_TIME, workTime.WORKTIME_ID,")
				.append(
						"workTime.WORKTIME_NAME, workTime.ONTIME1, workTime.OFFTIME1, workTime.ONTIME2,")
				.append(
						"workTime.OFFTIME2, workTime.ONTIME3, workTime.OFFTIME3,workTime.ONTIME4, workTime.OFFTIME4")
				.append(" from YKT_CK.T_CLERKINFO clerk ")
				.append(
						" left join YKT_CK.T_DEPT_WORKCONFINFO deptWork on deptWork.DEPT_ID=clerk.DEPT_ID")
				.append(
						" left join YKT_CK.T_WORKCONFINFO workConf on workConf.WORKCONF_ID = deptWork.WORKINFO_ID")
				.append(
						" left join YKT_CK.T_WORKTIMEINTO workTime on workTime.WORKTIME_ID = deptWork.WORKTIME_ID")
				.append(
						" where deptWork.BEGINDATE='" + workDate + "'"
								+ " and clerk.CUST_ID=" + custId);
		List workConfInfoList = jdbcTemplate.queryForList(querySql.toString());
		return workConfInfoList;
	}

	/**
	 * 判断时间大小，结束时间大于开始时间返回true hanjiwei add it 20061020
	 * 
	 * @param beginTime
	 * @param endTime
	 * @return
	 */
	private boolean diffTime(String beginTime, String endTime) {
		if (DateUtilExtend.timeDiff1(beginTime, endTime) >= 0) {
			return true;
		} else {
			return false;
		}

	}

	/**
	 * 时间比较，结束时间和开始时间的差值小于给定的值返回true hanjiwei add it 20061020
	 * 
	 * @param beginTime
	 * @param endTime
	 * @return
	 */
	private boolean diffTime(String beginTime, String endTime, int overTime) {
		if (DateUtilExtend.timeDiff1(beginTime, endTime) <= overTime) {
			return true;
		} else {
			return false;
		}
	}

	private String formatWorkTime2(String inTime) {
		if ("".equals(inTime) || null == inTime) {
			return "";
		} else if (inTime.length() == 4) {
			return inTime + "00";
		} else {
			return "";
		}
	}

	/**
	 * 生成个人考勤信息 hanjiwei modify it 20061019
	 */
	private void createPersonWorkInfo(Map filter) throws Exception {
		String signDate = (String) filter.get("signDate");
		String custId = String.valueOf(filter.get("custId"));

		List cardList = getCustWorkSerial(custId, signDate);
		String deptId = getDeptIdByCustId(custId);
		// 根据人员编号取得考勤制度信息
		if (!getWorkConfInfoByCustId(custId, signDate).isEmpty()) {
			Map workTime = (Map) getWorkConfInfoByCustId(custId, signDate).get(
					0);
			// 取得考勤工作时间
			String onTime1 = formatWorkTime2(workTime.get("ONTIME1").toString());
			String offTime1 = formatWorkTime2(workTime.get("OFFTIME1")
					.toString());
			String onTime2 = formatWorkTime2(workTime.get("ONTIME2").toString());
			String offTime2 = formatWorkTime2(workTime.get("OFFTIME2")
					.toString());
			String onTime3 = formatWorkTime2(workTime.get("ONTIME3").toString());
			String offTime3 = formatWorkTime2(workTime.get("OFFTIME3")
					.toString());
			String onTime4 = formatWorkTime2(workTime.get("ONTIME4").toString());
			String offTime4 = formatWorkTime2(workTime.get("OFFTIME4")
					.toString());

			// 允许上班提前打卡时间和下班延后打卡时间
			int overTime = Integer.parseInt(workTime.get("OVER_TIME")
					.toString());
			int delayTime = Integer.parseInt(workTime.get("DELAY_TIME")
					.toString());

			Map factWorkTime = getFactWorkTime(cardList, onTime1, offTime1,
					onTime2, offTime2, onTime3, offTime3, onTime4, offTime4,
					overTime, delayTime);
			TcheckattinfoId attInfoId = new TcheckattinfoId();
			Tcheckattinfo attInfo = new Tcheckattinfo();
			attInfoId.setCustId(new Integer(Integer.parseInt(custId)));
			attInfoId.setCheckDate(signDate);
			attInfo.setId(attInfoId);
			attInfo.setDeptId(deptId);
			attInfo.setFactOntime1(factWorkTime.get("onTime1").toString());
			attInfo.setFactOfftime1(factWorkTime.get("offTime1").toString());
			attInfo.setFactOntime2(factWorkTime.get("onTime2").toString());
			attInfo.setFactOfftime2(factWorkTime.get("offTime2").toString());
			attInfo.setFactOntime3(factWorkTime.get("onTime3").toString());
			attInfo.setFactOfftime3(factWorkTime.get("offTime3").toString());
			attInfo.setFactOntime4(factWorkTime.get("onTime4").toString());
			attInfo.setFactOfftime4(factWorkTime.get("offTime4").toString());
			attInfo.setIfoffice("1");
			// 先查询是否存在记录，存在则更新，否则保存
			if (exitRecordByCustId(custId, signDate)) {
				dutytimedao.update(attInfo);
			} else {
				dutytimedao.save(attInfo);
			}
		}
	}

	/**
	 * hanjiwei modify it 200610 统计出实际工作时间
	 * 
	 * @param cardList
	 * @param onTime1
	 * @param offTime1
	 * @param onTime2
	 * @param offTime2
	 * @param onTime3
	 * @param offTime3
	 * @param onTime4
	 * @param offTime4
	 * @param overTime
	 * @param delayTime
	 * @return
	 */
	private Map getFactWorkTime(List cardList, String onTime1, String offTime1,
			String onTime2, String offTime2, String onTime3, String offTime3,
			String onTime4, String offTime4, int overTime, int delayTime) {
		// 定义实际上班时间并初始化
		String workOnTime1 = "235959";
		String workOffTime1 = "000000";
		String workOnTime2 = "235959";
		String workOffTime2 = "000000";
		String workOnTime3 = "235959";
		String workOffTime3 = "000000";
		String workOnTime4 = "235959";
		String workOffTime4 = "000000";
		String currentTime = "";
		if (cardList.size() != 0) {
			Iterator checkTime = cardList.iterator();
			while (checkTime.hasNext()) {
				Map queryMap = (Map) checkTime.next();
				currentTime = (String) queryMap.get("ATT_TIME").toString();

				if (!"".equals(onTime1)) {
					// ontime1<currenttime
					if (diffTime(currentTime, onTime1)) {
						if (diffTime(currentTime, onTime1, overTime)) {
							if (diffTime(currentTime, workOnTime1)) {
								workOnTime1 = currentTime;
							}
						}
					}
					// onTime1<currentTime<offTime1
					if (diffTime(onTime1, currentTime)
							&& diffTime(currentTime, offTime1)) {
						if (diffTime(currentTime, workOnTime1)) {
							workOnTime1 = currentTime;
						}
						if (diffTime(workOffTime1, currentTime)) {
							workOffTime1 = currentTime;
						}
					}
					// currentTime-workoffTime<30有效考勤，正常下班
					if (diffTime(offTime1, currentTime, delayTime)) {
						if (diffTime(workOffTime1, currentTime)) {
							workOffTime1 = currentTime;
						}
					}
				}
				if (!"".equals(onTime2)) {
					// offtime1<currenttime<offtime2
					if (diffTime(offTime1, currentTime)
							&& diffTime(currentTime, onTime2)) {
						// workontime2-currentTime<30有效考勤，上班考勤2早到
						if (diffTime(currentTime, onTime2, overTime)) {
							if (diffTime(currentTime, workOnTime2)) {
								workOnTime2 = currentTime;
							}
						}
					}
					// ontime2<currenttime<offtime2
					if (diffTime(onTime2, currentTime)
							&& diffTime(currentTime, offTime2)) {
						// 迟到
						if (diffTime(currentTime, workOnTime2)) {
							workOnTime2 = currentTime;
						}
						// 早退
						if (diffTime(workOffTime2, currentTime)) {
							workOffTime2 = currentTime;
						}
					}
					if (diffTime(offTime2, currentTime, delayTime)) {
						if (diffTime(workOffTime2, currentTime)) {
							workOffTime2 = currentTime;
						}
					}
				}
				if (!"".equals(onTime3)) {
					if (diffTime(offTime2, currentTime)
							&& diffTime(currentTime, onTime3)) {
						if (diffTime(onTime3, currentTime, overTime)) {
							if (diffTime(currentTime, workOnTime3)) {
								workOnTime3 = currentTime;
							}
						}
					}
					if (diffTime(onTime3, currentTime)
							&& diffTime(currentTime, offTime3)) {
						if (diffTime(currentTime, workOnTime3)) {
							workOnTime3 = currentTime;
						}
						if (diffTime(currentTime, workOffTime3)) {
							workOffTime3 = currentTime;
						}
					}
					if (diffTime(offTime3, currentTime, delayTime)) {
						if (diffTime(workOffTime3, currentTime)) {
							workOffTime3 = currentTime;
						}
					}
				}
				if (!"".equals(onTime4)) {
					if (diffTime(offTime3, currentTime)
							&& diffTime(currentTime, onTime4)) {
						if (diffTime(onTime4, currentTime, overTime)) {
							if (diffTime(currentTime, workOnTime4)) {
								workOnTime4 = currentTime;
							}
						}
					}
					if (diffTime(onTime4, currentTime)
							&& diffTime(currentTime, offTime4)) {
						if (diffTime(currentTime, workOnTime4)) {
							workOnTime4 = currentTime;
						}
						if (diffTime(currentTime, workOffTime4)) {
							workOffTime4 = currentTime;
						}
					}
					if (diffTime(offTime4, currentTime)) {
						if (diffTime(offTime4, currentTime, delayTime)) {
							if (diffTime(workOffTime4, currentTime)) {
								workOffTime4 = currentTime;
							}
						}
					}
				}
			}
		}
		Map returnMap = new HashMap();
		returnMap.put("onTime1", formatWorkTime(workOnTime1));
		returnMap.put("offTime1", formatWorkTime(workOffTime1));
		returnMap.put("onTime2", formatWorkTime(workOnTime2));
		returnMap.put("offTime2", formatWorkTime(workOffTime2));
		returnMap.put("onTime3", formatWorkTime(workOnTime3));
		returnMap.put("offTime3", formatWorkTime(workOffTime3));
		returnMap.put("onTime4", formatWorkTime(workOnTime4));
		returnMap.put("offTime4", formatWorkTime(workOffTime4));
		return returnMap;
	}

	/**
	 * 显示工作时间，如果工作时间“235959”，返回“000000”
	 * 
	 * @param workTime
	 * @return
	 */
	private String formatWorkTime(String workTime) {
		if ("235959".equals(workTime)) {
			return "000000";
		} else {
			return workTime;
		}
	}

	/**
	 * 生成所有考勤人员信息，并把考勤信息写入到考勤数据表中 32017669 hanjiwei modify it 20061019
	 */
	public void createAllWorkInfoByDptConf(Map filter) throws Exception {
		String startDate = (String) filter.get("startDate");
		String endDate = (String) filter.get("endDate");
		String deptId = (String) filter.get("deptId");
		String stuEmpNo = (String) filter.get("stuEmpNo");
		StringBuffer querySql = new StringBuffer(1024);
		querySql
				.append(
						"select clerk.CUST_ID, clerk.DEPT_ID,clerk.IFOFFICE from YKT_CK.T_CLERKINFO clerk")
				.append(
						" left join YKT_CUR.T_CIF_CUSTOMER cust on cust.CUT_ID=clerk.CUST_ID")
				.append(" where 1>0");
		if ((!"".equals(deptId)) && !(null == deptId)) {
			querySql.append(" and clerk.DEPT_ID='" + deptId + "'");
		}
		if ((!"".equals(stuEmpNo)) && !(null == stuEmpNo)) {
			querySql.append(" and cust.STUEMP_NO='" + stuEmpNo + "'");
		}
		// System.out.println(querySql);
		List custList = jdbcTemplate.queryForList(querySql.toString());

		Map custInfo = new HashMap();

		long diffDate = DateUtilExtend.diffDate(startDate, endDate);
		for (long diffDay = 0; diffDay <= diffDate; diffDay++) {
			String workDate = DateUtilExtend.addDate2(startDate, (int) diffDay);
			custInfo.put("signDate", workDate);
			custInfo.put("deptId", deptId);
			if (!custList.isEmpty()) {
				Iterator tmpList = custList.iterator();
				String ifOffice = "";
				while (tmpList.hasNext()) {
					Map custInfoList = (Map) tmpList.next();
					ifOffice = custInfoList.get("IFOFFICE").toString();
					custInfo.put("custId", custInfoList.get("CUST_ID"));
					custInfo.put("deptId", custInfoList.get("DEPT_ID"));
					// 非坐班人员考勤信息
					if ("2".equals(ifOffice)) {
						// 取得考勤人员的实际上班时间和下班时间
						dealWithNoSeatClerk(custInfo);
						// 完成后把考勤信息加入报表中去
						dealWithNoSeatReport(custInfo);
						// 坐班人员考勤信息
					} else if ("1".equals(ifOffice)) {
						// 取得考勤人员的实际上班时间和下班时间
						createPersonWorkInfo(custInfo);
						// 完成后把考勤信息加入报表中去
						dealWithSeatReport(custInfo);
					}
				}
			}
		}
	}

	/**
	 * 生成非坐班人员报表
	 * 
	 * @param filter
	 *            hanjiwe modify it 20061201
	 */
	private void dealWithNoSeatReport(Map filter) {
		String signDate = (String) filter.get("signDate");
		String custId = String.valueOf(filter.get("custId"));
		List attinfo = getCheckInfoByCustAndDate(signDate, custId);
		String deptId = String.valueOf(filter.get("deptId"));
		String onTime = "000000";
		String offTime = "000000";
		int workTime = 0;
		int leaveTime = 0;
		String ifOffice = "2";
		String week = DateUtilExtend.getWeekByDate(signDate);
		// 如果没有找到考勤记录，并且不是双休日，而且没有请假，那么该考勤人员算是缺席，缺席时间按规定时间算
		if (attinfo.size() == 0) {
			if (!"6".equals(week) && !"7".equals(week)
					&& leaveList(signDate, custId).size() == 0) {
				leaveTime = (int) DateUtilExtend.timeDiff1(
						ClerkConfig.WORKONTIME, ClerkConfig.WORKOFFTIME);
			}
		} else {
			Map attMap = (Map) attinfo.get(0);
			deptId = attMap.get("DEPT_ID").toString();
			onTime = attMap.get("FACT_ONTIME").toString();
			offTime = attMap.get("FACT_OFFTIME").toString();
			workTime = getWorkTimeValue(onTime, offTime);
			ifOffice = attMap.get("IFOFFICE").toString();
		}
		Tcheckattreport attReport = new Tcheckattreport();
		TcheckattreportId attReportId = new TcheckattreportId();
		attReportId.setCheckDate(signDate);
		attReportId.setCustId(Integer.valueOf(custId));
		attReport.setId(attReportId);
		attReport.setDeptId(deptId);
		attReport.setIfoffice(ifOffice);
		attReport.setFactValue(new Integer(workTime));
		attReport.setLeaveValue(new Integer(leaveTime));

		if ("6".equals(week) || "7".equals(week)) {
			attReport.setTworestValue(new Integer(workTime));
		}
		Map leaveInfoMap = getLeaveInfoMap(signDate, custId);
		attReport.setLeaveType(leaveInfoMap.get("leaveType").toString());
		attReport.setLeaveTime(Integer.valueOf(leaveInfoMap.get("leaveTime")
				.toString()));
		if (exitReportByCustId(custId, signDate)) {
			workInfodao.update(attReport);
		} else {
			workInfodao.save(attReport);
		}

	}

	/**
	 * 生成坐班人员报表
	 * 
	 * @param filter
	 *            hanjiwei add it 20061201
	 */
	private void dealWithSeatReport(Map filter) {
		String signDate = (String) filter.get("signDate");
		String custId = String.valueOf(filter.get("custId"));
		String deptId = String.valueOf(filter.get("deptId"));
		List workConf = getCheckWorkInfo(custId, signDate);
		if (workConf.size() > 0) {
			Map workConfMap = (Map) workConf.get(0);
			List attinfo = getCheckInfoByCustAndDate(signDate, custId);
			int factWorkTime = 0;
			int workConfTime = calcWorkConfTime(workConfMap);
			int leaveTime = 0;
			int overTime = 0;
			int lateTime = 0;
			int earlyLeaveTime = 0;
			String ifOffice = "1";
			String week = DateUtilExtend.getWeekByDate(signDate);
			// 如果没有找到考勤记录，并且不是双休日，而且没有请假，那么该考勤人员算是缺席，缺席时间按规定时间算
			if (attinfo.size() == 0) {
				if (!"6".equals(week) && !"7".equals(week)
						&& leaveList(signDate, custId).size() == 0) {
					leaveTime = (int) DateUtilExtend.timeDiff1(
							ClerkConfig.WORKONTIME, ClerkConfig.WORKOFFTIME);
				}
			} else {
				Map attMap = (Map) attinfo.get(0);
				factWorkTime = calcFactWorkTime(attMap);
				if (factWorkTime - workConfTime >= 0) {
					overTime = factWorkTime - workConfTime;
				} else {
					leaveTime = workConfTime - factWorkTime;
				}
				ifOffice = attMap.get("IFOFFICE").toString();
				lateTime = calcLateTime(workConfMap, attMap);
				earlyLeaveTime = calcEarlyLeaveTime(workConfMap, attMap);
			}
			Tcheckattreport attReport = new Tcheckattreport();
			TcheckattreportId attReportId = new TcheckattreportId();
			attReportId.setCheckDate(signDate);
			attReportId.setCustId(Integer.valueOf(custId));
			attReport.setId(attReportId);
			attReport.setWorktimeValue(new Integer(workConfTime));
			attReport.setOvertimeValue(new Integer(overTime));
			// attReport.setLeaveTime(new Integer(leaveTime));
			attReport.setLeaveEarly(new Integer(earlyLeaveTime));
			attReport.setDelayValue(new Integer(lateTime));
			attReport.setDeptId(deptId);
			attReport.setIfoffice(ifOffice);
			attReport.setFactValue(new Integer(factWorkTime));

			if ("6".equals(week) || "7".equals(week)) {
				attReport.setTworestValue(new Integer(factWorkTime));
			}

			Map leaveInfoMap = getLeaveInfoMap(signDate, custId);
			String leaveMapTime = leaveInfoMap.get("leaveTime").toString();
			if ("0".equals(leaveMapTime)) {
				attReport.setLeaveValue(new Integer(leaveTime));
			} else {
				attReport.setLeaveValue(new Integer(0));
			}
			attReport.setLeaveType(leaveInfoMap.get("leaveType").toString());
			attReport.setLeaveTime(Integer.valueOf(leaveMapTime));
			if (exitReportByCustId(custId, signDate)) {
				workInfodao.update(attReport);
			} else {
				workInfodao.save(attReport);
			}
		}

	}

	/**
	 * 计算考勤上班时间和下班时间的差值
	 * 
	 * @param onTime
	 * @param offTime
	 * @return hanjiwei add it 20061201
	 */
	private int getWorkTimeValue(String onTime, String offTime) {
		if ("".equals(onTime) || "".equals(offTime) || null == onTime
				|| null == offTime || onTime.length() != 6
				|| offTime.length() != 6) {
			return 0;
		} else if ("000000".equals(onTime) || "000000".equals(offTime)) {
			return 0;
		} else {
			return (int) DateUtilExtend.timeDiff1(onTime, offTime);
		}
	}

	/**
	 * 计算应该工作时间
	 * 
	 * @return
	 */
	private int calcWorkConfTime(Map workConfMap) {
		String onTime1 = "000000";
		String offTime1 = "000000";
		String onTime2 = "000000";
		String offTime2 = "000000";
		String onTime3 = "000000";
		String offTime3 = "000000";
		String onTime4 = "000000";
		String offTime4 = "000000";
		int workTime = 0;
		onTime1 = formatWorkTime2(workConfMap.get("ONTIME1").toString());
		offTime1 = formatWorkTime2(workConfMap.get("OFFTIME1").toString());
		onTime2 = formatWorkTime2(workConfMap.get("ONTIME2").toString());
		offTime2 = formatWorkTime2(workConfMap.get("OFFTIME2").toString());
		onTime3 = formatWorkTime2(workConfMap.get("ONTIME3").toString());
		offTime3 = formatWorkTime2(workConfMap.get("OFFTIME3").toString());
		onTime4 = formatWorkTime2(workConfMap.get("ONTIME4").toString());
		offTime4 = formatWorkTime2(workConfMap.get("OFFTIME4").toString());
		workTime = getWorkTimeValue(onTime1, offTime1)
				+ getWorkTimeValue(onTime2, offTime2)
				+ getWorkTimeValue(onTime3, offTime3)
				+ getWorkTimeValue(onTime4, offTime4);
		return workTime;
	}

	/**
	 * 计算实际工作时间
	 * 
	 * @param attMap
	 * @return hanjiwei add it 20061201
	 */
	private int calcFactWorkTime(Map attMap) {
		String onTime1 = "000000";
		String offTime1 = "000000";
		String onTime2 = "000000";
		String offTime2 = "000000";
		String onTime3 = "000000";
		String offTime3 = "000000";
		String onTime4 = "000000";
		String offTime4 = "000000";
		int workTime = 0;
		onTime1 = attMap.get("FACT_ONTIME1").toString();
		offTime1 = attMap.get("FACT_OFFTIME1").toString();
		onTime2 = attMap.get("FACT_ONTIME2").toString();
		offTime2 = attMap.get("FACT_OFFTIME2").toString();
		onTime3 = attMap.get("FACT_ONTIME3").toString();
		offTime3 = attMap.get("FACT_OFFTIME3").toString();
		onTime4 = attMap.get("FACT_ONTIME4").toString();
		offTime4 = attMap.get("FACT_OFFTIME4").toString();
		workTime = getWorkTimeValue(onTime1, offTime1)
				+ getWorkTimeValue(onTime2, offTime2)
				+ getWorkTimeValue(onTime3, offTime3)
				+ getWorkTimeValue(onTime4, offTime4);
		return workTime;
	}

	/**
	 * 计算迟到时间
	 * 
	 * @param workConfMap
	 * @param attMap
	 * @return hanjiwei add it 20061201
	 */
	private int calcLateTime(Map workConfMap, Map attMap) {
		String workOnTime1 = "000000";
		String workOnTime2 = "000000";
		String workOnTime3 = "000000";
		String workOnTime4 = "000000";
		String onTime1 = "000000";
		String onTime2 = "000000";
		String onTime3 = "000000";
		String onTime4 = "000000";
		int time1 = 0;
		int time2 = 0;
		int time3 = 0;
		int time4 = 0;
		workOnTime1 = formatWorkTime2(workConfMap.get("ONTIME1").toString());
		workOnTime2 = formatWorkTime2(workConfMap.get("ONTIME2").toString());
		workOnTime3 = formatWorkTime2(workConfMap.get("ONTIME3").toString());
		workOnTime4 = formatWorkTime2(workConfMap.get("ONTIME4").toString());
		onTime1 = attMap.get("FACT_ONTIME1").toString();
		onTime2 = attMap.get("FACT_ONTIME2").toString();
		onTime3 = attMap.get("FACT_ONTIME3").toString();
		onTime4 = attMap.get("FACT_ONTIME4").toString();
		if (getWorkTimeValue(workOnTime1, onTime1) > 0) {
			time1 = getWorkTimeValue(workOnTime1, onTime1);
		}
		if (getWorkTimeValue(workOnTime2, onTime2) > 0) {
			time2 = getWorkTimeValue(workOnTime2, onTime2);
		}
		if (getWorkTimeValue(workOnTime3, onTime3) > 0) {
			time3 = getWorkTimeValue(workOnTime3, onTime3);
		}
		if (getWorkTimeValue(workOnTime4, onTime4) > 0) {
			time4 = getWorkTimeValue(workOnTime4, onTime4);
		}
		return time1 + time2 + time3 + time4;
	}

	/**
	 * 计算早退时间
	 * 
	 * @param workConfMap
	 * @param attMap
	 * @return hanjiwei add it 20061201
	 */
	private int calcEarlyLeaveTime(Map workConfMap, Map attMap) {
		String workOffTime1 = "000000";
		String workOffTime2 = "000000";
		String workOffTime3 = "000000";
		String workOffTime4 = "000000";
		String offTime1 = "000000";
		String offTime2 = "000000";
		String offTime3 = "000000";
		String offTime4 = "000000";
		int time1 = 0;
		int time2 = 0;
		int time3 = 0;
		int time4 = 0;
		workOffTime1 = formatWorkTime2(workConfMap.get("OFFTIME1").toString());
		workOffTime2 = formatWorkTime2(workConfMap.get("OFFTIME2").toString());
		workOffTime3 = formatWorkTime2(workConfMap.get("OFFTIME3").toString());
		workOffTime4 = formatWorkTime2(workConfMap.get("OFFTIME4").toString());
		offTime1 = attMap.get("FACT_OFFTIME1").toString();
		offTime2 = attMap.get("FACT_OFFTIME2").toString();
		offTime3 = attMap.get("FACT_OFFTIME3").toString();
		offTime4 = attMap.get("FACT_OFFTIME4").toString();
		if (getWorkTimeValue(workOffTime1, offTime1) < 0) {
			time1 = getWorkTimeValue(offTime1, workOffTime1);
		}
		if (getWorkTimeValue(workOffTime2, offTime2) < 0) {
			time2 = getWorkTimeValue(offTime2, workOffTime2);
		}
		if (getWorkTimeValue(workOffTime3, offTime3) < 0) {
			time3 = getWorkTimeValue(offTime3, workOffTime3);
		}
		if (getWorkTimeValue(workOffTime4, offTime4) < 0) {
			time4 = getWorkTimeValue(offTime4, workOffTime4);
		}
		return time1 + time2 + time3 + time4;
	}

	/**
	 * 取得请假信息列表
	 * 
	 * @param signDate
	 * @param custId
	 * @return hanjiwei add it 20061201
	 */
	private List leaveList(String signDate, String custId) {
		StringBuffer queryStr = new StringBuffer(1024);
		queryStr
				.append(
						"select LEAVE_TYPEID, VALIDITY, STARTDATE,ENDDATE, STARTTIME, ENDTIME")
				.append(" from YKT_CK.T_LEAVEINFO where STARTDATE<=?").append(
						"' and ENDDATE>=? and CUST_ID=?").append(
						" and VALIDITY='1'");
		List leaveList = jdbcTemplate.queryForList(queryStr.toString(),
				new Object[] { signDate, signDate, Integer.valueOf(custId) });
		return leaveList;
	}

	/**
	 * 设置请假信息到报表中去
	 * 
	 * @param signDate
	 * @param custId
	 *            hanjiwei add it 20061201
	 */
	private Map getLeaveInfoMap(String signDate, String custId) {
		StringBuffer queryStr = new StringBuffer(1024);
		queryStr
				.append(
						"select LEAVE_TYPEID, VALIDITY, STARTDATE,ENDDATE, STARTTIME, ENDTIME")
				.append(" from YKT_CK.T_LEAVEINFO where STARTDATE<=?").append(
						"' and ENDDATE>=?").append("' and CUST_ID=?").append(
						" and VALIDITY='1'");
		List leaveList = jdbcTemplate.queryForList(queryStr.toString(),
				new Object[] { signDate, signDate, Integer.valueOf(custId) });
		int leaveTime = 0;
		String leaveType = "";
		if (leaveList.size() > 0) {
			Map leaveMap = (Map) leaveList.get(0);
			leaveType = leaveMap.get("LEAVE_TYPEID").toString();
			String startDate = leaveMap.get("STARTDATE").toString();
			String endDate = leaveMap.get("ENDDATE").toString();
			String startTime = leaveMap.get("STARTTIME").toString();
			String endTime = leaveMap.get("ENDTIME").toString();
			if (startDate.equals(endDate)) {
				leaveTime = (int) DateUtilExtend.timeDiff1(startTime, endTime);
			} else {
				if (signDate.equals(startDate)) {
					leaveTime = (int) DateUtilExtend.timeDiff1(startTime,
							ClerkConfig.WORKOFFTIME);
				} else if (signDate.equals(endDate)) {
					leaveTime = (int) DateUtilExtend.timeDiff1(
							ClerkConfig.WORKONTIME, endTime);
				} else {
					leaveTime = (int) DateUtilExtend.timeDiff1(
							ClerkConfig.WORKONTIME, ClerkConfig.WORKOFFTIME);
				}
			}
		}
		Map leaveInfoMap = new HashMap();
		leaveInfoMap.put("leaveTime", new Integer(leaveTime));
		leaveInfoMap.put("leaveType", leaveType);
		return leaveInfoMap;
	}

	/**
	 * 取得考勤人员实际考勤信息
	 * 
	 * @param signDate
	 * @param custId
	 * @return hanjiwei add it 20061130
	 */
	private List getCheckInfoByCustAndDate(String signDate, String custId) {
		StringBuffer querySql = new StringBuffer(512);
		querySql
				.append(
						"select CUST_ID, CHECK_DATE, DEPT_ID, IFOFFICE, FACT_ONTIME, FACT_OFFTIME,")
				.append(
						" FACT_ONTIME1, FACT_OFFTIME1, FACT_ONTIME2, FACT_OFFTIME2, FACT_ONTIME3, ")
				.append(
						" FACT_OFFTIME3, FACT_ONTIME4, FACT_OFFTIME4 from YKT_CK.T_CHECKATT_INFO")
				.append(" where CUST_ID=? and CHECK_DATE=?");
		List attInfo = jdbcTemplate.queryForList(querySql.toString(),
				new Object[] { Integer.valueOf(custId), signDate });
		return attInfo;
	}

	/**
	 * 取得考勤人员规定考勤信息
	 * 
	 * @param custId
	 * @return hanjiwei add it 20061130
	 */
	private List getCheckWorkInfo(String custId, String signDate) {
		StringBuffer querySql = new StringBuffer(1024);
		querySql
				.append(
						"select workmap.DEPT_ID, workmap.BEGINDATE, workmap.WORKINFO_ID, workmap.WORKTIME_ID,")
				.append(
						" workmap.IFWORK,workconf.WORKCONF_NAME, workconf.OVERDUE_TIME, workconf.LEAVEEARLY_TIME,")
				.append(
						" workconf.OVER_TIME,workconf.DELAY_TIME, workconf.CHECK_TIME, worktime.WORKTIME_NAME, ")
				.append(
						" worktime.ONTIME1,worktime.OFFTIME1, worktime.ONTIME2, worktime.OFFTIME2, worktime.ONTIME3,")
				.append(
						" worktime.OFFTIME3, worktime.ONTIME4, worktime.OFFTIME4")
				.append(" from YKT_CK.T_CHECKATT_INFO checkatt ")
				.append(
						" left join YKT_CK.T_DEPT_WORKCONFINFO workmap on workmap.DEPT_ID=checkatt.DEPT_ID")
				.append(
						" left join YKT_CK.T_WORKCONFINFO workconf on workconf.WORKCONF_ID=workmap.WORKINFO_ID")
				.append(
						" left join YKT_CK.T_WORKTIMEINTO worktime on worktime.WORKTIME_ID=workmap.WORKTIME_ID")
				.append(" where CUST_ID=? and CHECK_DATE=?").append(
						" and workmap.BEGINDATE=?");
		List workInfo = jdbcTemplate.queryForList(querySql.toString(),
				new Object[] { Integer.valueOf(custId), signDate, signDate });
		return workInfo;
	}

	/**
	 * 查询考勤人员在一段时间内的工作时间,并按列表返回
	 * 
	 * @param deptId
	 * @return
	 */
	public List getCustWorkTime(String deptId, String beginDate, String endDate) {
		Iterator iter = queryClerk(deptId).iterator();
		// List custWorkTime = null;
		List returnWorkList = new ArrayList();
		while (iter.hasNext()) {
			Map custInfo = (Map) iter.next();
			int custId = Integer.parseInt(custInfo.get("CUT_ID").toString());
			StringBuffer querySql = new StringBuffer(512);
			querySql
					.append(
							"select CUST_ID,ATT_DATE, min(ATT_TIME) onTime,max(ATT_TIME) offTime from (")
					.append(
							" select CUST_ID,ATT_DATE, ATT_TIME from YKT_CK.T_ATTSERIAL")
					.append(" where cust_id=").append(custId).append(
							" and ATT_DATE>='").append(beginDate).append("'")
					.append(" and ATT_DATE<='").append(endDate).append("'")
					.append(" union").append(
							" select CUST_ID, ATT_DATE, ATT_TIME").append(
							" from YKT_CK.T_ATTSERIAL_RECORD ").append(
							" where cust_id=").append(custId).append(
							" and ATT_DATE>='").append(beginDate).append("'")
					.append(" and ATT_DATE<='").append(endDate).append("'")
					.append(" )t group by att_date,cust_id order by att_date");
			// System.out.println(querySql.toString());
			List custWorkTime = jdbcTemplate.queryForList(querySql.toString());
			// 把查询出的人员考勤记录相加放入到list中
			Map workTime = new HashMap();
			String workTimeM = getCustWorkTime(custWorkTime);
			String pubRest = getCustRestTime(
					getCustPubRest(custId, beginDate, endDate)).toString();
			String personRest = getCustRestTime(
					getCustPersonRest(custId, beginDate, endDate)).toString();
			float totleTime = 0;
			totleTime = Float.parseFloat(workTimeM) + Float.parseFloat(pubRest)
					+ Float.parseFloat(personRest);
			// 计算考勤人员的公事请假时间和私事请假时间
			workTime.put("pubRest", pubRest);
			workTime.put("pubRestH", new Float(Float.parseFloat(pubRest) / 60));
			workTime.put("personRest", personRest);
			workTime.put("personRestH", new Float(
					Float.parseFloat(personRest) / 60));
			workTime.put("custId", custInfo.get("CUT_ID"));
			workTime.put("stuempId", custInfo.get("STUEMPID"));
			workTime.put("custName", custInfo.get("STUEMPNAME"));
			workTime.put("deptName", custInfo.get("DEPT_NAME"));
			workTime.put("workTimeM", workTimeM);
			workTime.put("workTime",
					new Float(Float.parseFloat(workTimeM) / 60));
			workTime.put("totleTime", new Float(totleTime / 60));
			returnWorkList.add(workTime);
		}

		return returnWorkList;
	}

	/**
	 * 计算考勤人员在一段时间内的工作时间
	 * 
	 * @param custWorkTime
	 * @return
	 */
	private String getCustWorkTime(List custWorkTime) {
		Iterator timeIter = custWorkTime.iterator();
		int time = 0;
		// DecimalFormat df = new DecimalFormat("0.000");

		while (timeIter.hasNext()) {
			Map custTime = (Map) timeIter.next();
			String onTime = custTime.get("onTime").toString();
			String offTime = custTime.get("offTime").toString();
			time = time + getWorkTimeValue(onTime, offTime);
		}
		// String reTime = df.format(new Float(time/60));
		String reTime = (new Integer(time)).toString();
		return reTime;
	}

	/**
	 * 私假时间
	 * 
	 * @param custId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	private String getCustPersonRest(int custId, String beginDate,
			String endDate) {
		StringBuffer sql = new StringBuffer(2048);
		sql
				.append(
						"select CUST_ID, LEAVE_TYPEID,STARTDATE,ENDDATE, STARTTIME, ENDTIME")
				.append(" from YKT_CK.T_LEAVEINFO").append(" where cust_id=")
				.append(custId).append(" and startdate>='").append(beginDate)
				.append("' and enddate<='").append(endDate).append(
						"' and LEAVE_TYPEID not in (")
				.append(Constants.PUBREST).append(")");
		return sql.toString();
	}

	/**
	 * 公假时间
	 * 
	 * @param custId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	private String getCustPubRest(int custId, String beginDate, String endDate) {
		StringBuffer sql = new StringBuffer(2048);
		sql
				.append(
						"select CUST_ID, LEAVE_TYPEID,STARTDATE,ENDDATE, STARTTIME, ENDTIME")
				.append(" from YKT_CK.T_LEAVEINFO").append(" where cust_id=")
				.append(custId).append(" and startdate>='").append(beginDate)
				.append("' and enddate<='").append(endDate).append(
						"' and LEAVE_TYPEID in (").append(Constants.PUBREST)
				.append(")");
		return sql.toString();
	}

	private Integer getCustRestTime(String sql) {
		List custPersonRestTime = jdbcTemplate.queryForList(sql.toString());
		long time = 0;
		Iterator iter = custPersonRestTime.iterator();
		while (iter.hasNext()) {
			Map iterMap = (Map) iter.next();
			String bDate = iterMap.get("STARTDATE").toString();
			String eDate = iterMap.get("ENDDATE").toString();
			String bTime = iterMap.get("STARTTIME").toString();
			String eTime = iterMap.get("ENDTIME").toString();
			long diffDate = 0;
			long diffTime = 0;
			diffDate = DateUtilExtend.diffDate(bDate, eDate);
			diffTime = DateUtilExtend.timeDiff1(bTime, eTime);
			if (diffDate > 0) {
				time = time + diffDate * diffTime;
			} else {
				time = time + diffTime;
			}
		}
		return Integer.valueOf(new Long(time).toString());
	}

	private List queryClerk(String deptId) {
		StringBuffer sql = new StringBuffer(2048);
		sql
				.append(
						"SELECT B.CUT_ID CUT_ID,B.STUEMP_NO STUEMPID,B.CUT_NAME STUEMPNAME,")
				.append(" C.DEPT_NAME FROM YKT_CK.T_CLERKINFO A ")
				.append(
						" LEFT JOIN YKT_CUR.T_CIF_CUSTOMER B ON A.CUST_ID=B.CUT_ID")
				.append(" LEFT  JOIN YKT_CK.DEPARTMENT C").append(
						" ON A.DEPT_ID=C.DEPT_ID WHERE 1=1 ");
		// 参数处理
		if ((deptId != null) && (!"all".equals(deptId))) {
			sql.append(" AND A.DEPT_ID = '" + deptId + "'");
		}
		sql.append(" order by C.DEPT_ID");
		// log.debug("Sql--------------->"+sql.toString());
		List clerkList = jdbcTemplate.queryForList(sql.toString());
		return clerkList;
	}

	private String formatTime(String inTime) {
		if ("".equals(inTime) || null == inTime) {
			return "";
		} else if ("000000".equals(inTime)) {
			return "----";
		} else if ("235959".equals(inTime)) {
			return "----";
		} else {
			return inTime.substring(0, 2) + ":" + inTime.substring(2, 4);
		}

	}

	/**
	 * 生成考勤记录报表 20071031
	 */
	public List makeCheckReport(String statMonth, String deptId)
			throws Exception {
		PropertiesConfiguration config = GetPropertiesUtil.getInstance();
		int patchA = config.getInt("check.patchA");// 金额为85
		int patchB = config.getInt("check.patchB");// 金额为40
		int patchC = config.getInt("check.patchC");// 金额为45
		Iterator checkIter = sysService.getClerkInfo(deptId).iterator();
		List checkInfoList = new ArrayList();
		while (checkIter.hasNext()) {
			Map checkMap = (Map) checkIter.next();
			Map checkInfoMap = new HashMap();
			// 取得人员信息和考勤信息并放入到list中
			String deptName = checkMap.get("dept_name").toString();
			String stuempNo = checkMap.get("stuemp_no").toString();
			String custId = checkMap.get("cust_id").toString();
			String custName = checkMap.get("cut_name").toString();
			String custType = checkMap.get("dict_caption").toString();
			String dictValue = checkMap.get("dict_value").toString();
			int totCheckNum = 0;
			// 如果手工考勤里面有信息,手工考勤为*,打卡考勤为√,未考勤为空
			checkInfoMap.put("deptName", deptName);
			checkInfoMap.put("stuempNo", stuempNo);
			checkInfoMap.put("custName", custName);
			checkInfoMap.put("custType", custType);
			checkInfoMap.put("custId", custId);
			Iterator dayIter = sysService.getWeekByDate(statMonth).iterator();
			while (dayIter.hasNext()) {
				Map dayMap = (Map) dayIter.next();
				// 取得当前日期和当前周
				StringBuffer statDate = new StringBuffer(8);
				statDate.append(statMonth.substring(0, 4)).append(
						statMonth.substring(5, 7)).append(dayMap.get("date"));
				// checkInfoMap.put(statDate.toString(),statDate.toString());
				if (sysService.getManCheck(custId, statDate.toString()) > 0) {
					checkInfoMap.put(dayMap.get("date"), "*");
					totCheckNum = totCheckNum + 1;
				} else if (sysService.getManCheckWeb(custId, statDate
						.toString()) > 0) {
					checkInfoMap.put(dayMap.get("date"), "#");
					totCheckNum = totCheckNum + 1;
				} else if (sysService.getCardCheck(custId, statDate.toString()) > 0) {
					checkInfoMap.put(dayMap.get("date"), "√");
					totCheckNum = totCheckNum + 1;
				} else if (sysService.getCardCheckCancel(custId, statDate
						.toString()) > 0) {
					checkInfoMap.put(dayMap.get("date"), "○");

				} else {
					checkInfoMap.put(dayMap.get("date"), " ");

				}
			}
			if ("1".equals(dictValue)) {
				// 坐班
				// 如果是专职教师，补助计算方法
				// 补贴数=每月实际出勤天数*85
				checkInfoMap.put("totMoney", new Integer(totCheckNum * patchA));

                log.debug("dictValue is "+ dictValue + ",stuemp_no is " + stuempNo + ", money is " + totCheckNum * patchA);
			} else if("3".equals(dictValue)){
				//该教师属于职工，每刷卡考勤天40元
				checkInfoMap.put("totMoney", new Integer(totCheckNum * patchB));
				log.debug("dictValue is "+ dictValue + ",stuemp_no is " + stuempNo + ", money is " + totCheckNum * patchB);
			} else {
				/*
				 * 其他类型教师的补助计算方法 二． 教师性质为专职教师
				 * 按自然周划分：每月要求为完整周数，原则上上月未满一周的日期计入本月，本月后面未满一周的日期计入下月，
				 * 如针对08年1月计算补贴时，从12月31日开始到1月27日结束。 补贴数＝出勤补贴+交通补贴
				 * 
				 * 2.1出勤补贴下发规则： 按每个周分别计算后累积，每周都按以下规则计算出勤补贴。
				 * 
				 * 每周考勤实际天数 1)大于等于一天同时小于三天： 出勤补贴＝每周出勤实际天数*45 2)大于等于三天同时小于等于五天：
				 * 出勤补贴＝5*45 3)大于五天同时小于等于七天： 出勤补贴＝每周出勤实际天数*45
				 * 
				 * 2.2交通补贴下发规则： 交通补贴＝每月实际出勤天数*40
				 */
				Map patchNum = getPatchNum(statMonth, custId);
                log.debug("----patchNum is " + patchNum);
				int totBusMoney = Integer.parseInt(patchNum.get("busPatchNum")
						.toString())
						* patchB;
                log.debug("----busPatchNum is " + patchNum.get("busPatchNum").toString() + ",patchB is " + patchB);
				int totPatchMoney = Integer.parseInt(patchNum.get("patchNum")
						.toString())
						* patchC;// 按规则计算考勤天数
                log.debug("----patchNum is " + patchNum.get("patchNum").toString() + ",patchC is " + patchC);
				int totMoney = totBusMoney + totPatchMoney;
				checkInfoMap.put("totMoney", new Integer(totMoney));
                log.debug("****dictValue is "+ dictValue + ",stuemp_no is " + stuempNo + ", money is " + totMoney);

			}

			checkInfoMap.put("totNum", new Integer(totCheckNum));
			checkInfoList.add(checkInfoMap);
		}
		return checkInfoList;
	}

	/**
	 * 返回专职教师考勤当月的考勤次数和车贴次数
	 * 
	 * @param statMonth
	 * @return
	 */
	private Map getPatchNum(String statMonth, String custId) throws Exception {
		Map patchDate = sysService.getPatchDate(statMonth);
		String patchBDate = patchDate.get("beginDate").toString();// 补助开始日期
        log.debug("##############  begin date is " + patchBDate);
		String patchEDate = patchDate.get("endDate").toString();// 补助结束日期
        log.debug("##############  end date is " + patchEDate);
		int patchNum = 0;
		int temp = 0;
		int checkNum = 0;
		int busPatchNum = 0;// 车贴补助
		int dateDiff = Integer.parseInt(String.valueOf(DateUtilExtend.diffDate(
				patchBDate, patchEDate)));
		for (int i = 0; i < dateDiff + 1; i++) {
			String statDate = DateUtilExtend.addDate2(patchBDate, i);
			/**
			 * 计算每周的考勤次数并根据考勤次数判断实际考勤天数， 如果考勤天数小于3或大于5，则取实际考勤天数
			 * 如果考勤天数大于3小于5，则实际考勤天数等于5 把实际的考勤天数累加后置周考勤次数为0
			 */
			if ((sysService.getManCheck(custId, statDate) > 0)
					|| (sysService.getCardCheck(custId, statDate) > 0)
					||(sysService.getManCheckWeb(custId, statDate) > 0)) {
				checkNum++;
				busPatchNum++;
			}

			if (temp == 7) {
				temp = 0;
			}
			temp++;
			if ((temp == 7) || (i == dateDiff)) {
				if ((checkNum < 3) || (checkNum > 5)) {
					patchNum = patchNum + checkNum;
				} else if ((checkNum >= 3) && (checkNum <= 5)) {
					patchNum = patchNum + 5;
				}
				checkNum = 0;
			}
		}
		Map checkNumMap = new HashMap();
		checkNumMap.put("patchNum", new Integer(patchNum));
		checkNumMap.put("busPatchNum", new Integer(busPatchNum));
		return checkNumMap;
	}

	/**
	 * @see java.lang.Object#equals(Object)
	 */
	public boolean equals(Object object) {
		if (!(object instanceof WorkInfoServiceImpl)) {
			return false;
		}
		WorkInfoServiceImpl rhs = (WorkInfoServiceImpl) object;
		return new EqualsBuilder().appendSuper(super.equals(object)).append(
				this.sysService, rhs.sysService).append(this.jdbcTemplate,
				rhs.jdbcTemplate).append(this.dutytimedao, rhs.dutytimedao)
				.append(this.workInfodao, rhs.workInfodao).isEquals();
	}

	/**
	 * @see java.lang.Object#hashCode()
	 */
	public int hashCode() {
		return new HashCodeBuilder(1800224375, -877638869).appendSuper(
				super.hashCode()).append(this.sysService).append(
				this.jdbcTemplate).append(this.dutytimedao).append(
				this.workInfodao).toHashCode();
	}

	/**
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		return new ToStringBuilder(this).toString();
	}

	/**
	 * @see java.lang.Comparable#compareTo(Object)
	 */
	public int compareTo(Object object) {
		WorkInfoServiceImpl myClass = (WorkInfoServiceImpl) object;
		return new CompareToBuilder().append(this.sysService,
				myClass.sysService).append(this.jdbcTemplate,
				myClass.jdbcTemplate).append(this.dutytimedao,
				myClass.dutytimedao).append(this.workInfodao,
				myClass.workInfodao).toComparison();
	}

	public void deleteRecords(String ny) {
		final String deleteNy = ny;
        log.debug("delete from ykt_ck.t_kq_result_month where ny=" + ny);
		jdbcTemplate.update("delete from ykt_ck.t_kq_result_month where ny=?",
				new PreparedStatementSetter() {
					public void setValues(PreparedStatement ps)
							throws SQLException {
						ps.setString(1, deleteNy);
					}
				});
	}

	public void deleteHistoryRecords() {
		Calendar cal = Calendar.getInstance();
		cal.add(Calendar.MONTH, -5);
		final String hisDate = formatter_yyyymmdd.format(cal.getTime());

		try {
			jdbcTemplate
					.update(
							"insert into ykt_ck.t_attserial_his select * from ykt_ck.t_attserial where att_date<?",
							new PreparedStatementSetter() {
								public void setValues(PreparedStatement ps)
										throws SQLException {
									ps.setString(1, hisDate + "01");
								}
							});
		} catch (Exception e) {
			e.printStackTrace();
		}
		jdbcTemplate.update("delete from ykt_ck.t_attserial where att_date<?",
				new PreparedStatementSetter() {
					public void setValues(PreparedStatement ps)
							throws SQLException {
						ps.setString(1, hisDate + "01");
					}
				});

	}

	public void insertRecords(String ny, Map kqMap) {
		final String insertNy = ny;
		final Map insertMap = kqMap;
		jdbcTemplate.update(
				"insert into ykt_ck.t_kq_result_month(ny,bm,gh,xm,kqlb,"
						+ "day01,day02,day03,day04,day05,day06,day07,"
						+ "day08,day09,day10,day11,day12,day13,day14,"
						+ "day15,day16,day17,day18,day19,day20,day21,"
						+ "day22,day23,day24,day25,day26,day27,day28,"
						+ "day29,day30,day31,cs,bt) values(?,?,?,?,?,"
						+ "?,?,?,?,?,?,?," + "?,?,?,?,?,?,?,"
						+ "?,?,?,?,?,?,?," + "?,?,?,?,?,?,?," + "?,?,?,?,?)",
				new PreparedStatementSetter() {
					public void setValues(PreparedStatement ps)
							throws SQLException {
						ps.setString(1, insertNy);
						ps.setString(2, insertMap.get("deptName").toString());
						ps.setString(3, insertMap.get("stuempNo").toString());
						ps.setString(4, insertMap.get("custName").toString());
						ps.setString(5, insertMap.get("custType").toString());

						List dayList = sysService.getWeekByDate(insertNy);
						Iterator dayIter = dayList.iterator();
						if (dayList.size() == 28) {
							int i = 6;
							while (dayIter.hasNext()) {
								Map dayMap = (Map) dayIter.next();
								ps.setString(i, insertMap.get(
										dayMap.get("date").toString())
										.toString());
								i++;
							}
							ps.setString(34, "");
							ps.setString(35, "");
							ps.setString(36, "");
						}
						if (dayList.size() == 29) {
							int i = 6;
							while (dayIter.hasNext()) {
								Map dayMap = (Map) dayIter.next();
								ps.setString(i, insertMap.get(
										dayMap.get("date").toString())
										.toString());
								i++;
							}
							ps.setString(35, "");
							ps.setString(36, "");
						}
						if (dayList.size() == 30) {
							int i = 6;
							while (dayIter.hasNext()) {
								Map dayMap = (Map) dayIter.next();
								ps.setString(i, insertMap.get(
										dayMap.get("date").toString())
										.toString());
								i++;
							}
							ps.setString(36, "");
						}
						if (dayList.size() == 31) {
							int i = 6;
							while (dayIter.hasNext()) {
								Map dayMap = (Map) dayIter.next();
								ps.setString(i, insertMap.get(
										dayMap.get("date").toString())
										.toString());
								i++;
							}
						}

						ps.setString(37, insertMap.get("totNum").toString());
						ps.setString(38, insertMap.get("totMoney").toString());

                        System.out.println(insertNy + "," + insertMap.get("stuempNo").toString() + ","+insertMap.get("custName").toString() + ","+insertMap.get("totNum").toString() +"," + insertMap.get("totMoney").toString());
					}
				});
	}

	public List getDeptListForKQService() throws Exception {
		StringBuffer sql = new StringBuffer();
		sql
				.append(
						"select DEPT_ID deptId, DEPT_NAME deptName from YKT_CK.DEPARTMENT")
				.append(
						" where dept_id not in(select dept_id from ykt_ck.DEPARTMENT where dept_id in (")
				.append(
						" select distinct dept_parentid from ykt_ck.DEPARTMENT))")
				.append(
						" and  dept_id in (select distinct DEPT_ID from YKT_CK.T_OPER_LIMIT)");
		// .append(" where 1=?)");
		log.debug(sql);
		List deptList = jdbcTemplate.queryForList(sql.toString());

		return deptList;
	}

	public List getCheckReportByMonth(String deptId, List detpList ,String statMonth)
			throws Exception {
		StringBuffer sql=  new StringBuffer(1024);
		//显示所有权限的部门
		if(deptId!=null && "".equals(deptId)){
		  String deptNameString =	getDeptNameString(detpList);
		  if(deptNameString==null){
			  return new ArrayList();
		  }else{
			
			 sql.append(" select  *  from   ykt_ck.t_kq_result_month r where  r.bm in ('").append(deptNameString).append("')");
			 if (statMonth != null && !statMonth.equals("")) {
				 sql.append(" and r.ny ='" + statMonth + "'");
			 }
			 sql.append(" order by  bm,gh");
		  }	
			
		}else{
        //显示选择的部门
		sql.append(" select  *  from   ykt_ck.t_kq_result_month  r").append(
				   " where 1=1 ");
		
		String  deptname =  sysService.getDeptname(deptId);
		
		if (deptname != null && !deptname.equals("")) {
			sql.append(" and  r.bm ='" + deptname + "'");
		}
		if (statMonth != null && !statMonth.equals("")) {
			sql.append(" and r.ny ='" + statMonth + "'");
		}
		sql.append(" order by  bm,gh");
		}
        
		//log.debug(sql.toString());
		//log.debug("deptname is : " + deptname);
		List checkList = jdbcTemplate.queryForList(sql.toString());

		return checkList;
	}
	
	private String getDeptNameString(List deptList){
		if(deptList == null ||deptList.isEmpty() ){
			return null;
		}
		StringBuffer deptStr = new StringBuffer(512);
		for (int i=0;i<deptList.size();i++){
			Map deptMap = (Map)deptList.get(i);
			String dep = deptMap.get("deptName").toString();
			if(deptList.size()==1){
				deptStr.append(dep);
			}else{
			if (i==0){
				deptStr.append(dep).append("',");
			}else if (i==deptList.size()-1){
				deptStr.append("'").append(dep);
			}else{
				deptStr.append("'").append(dep).append("',");
			}
			}
		}
		return deptStr.toString();
	}


}
