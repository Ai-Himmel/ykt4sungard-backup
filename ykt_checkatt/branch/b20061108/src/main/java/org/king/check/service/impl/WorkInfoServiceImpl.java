package org.king.check.service.impl;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.DutyTimeDAO;
import org.king.check.dao.WorkInfoDao;
import org.king.check.domain.Tattserialrecord;
import org.king.check.domain.Tcheckattinfo;
import org.king.check.domain.TcheckattinfoId;
import org.king.check.service.WorkInfoService;
import org.king.check.util.DateUtilExtend;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.springframework.jdbc.core.JdbcTemplate;

public class WorkInfoServiceImpl extends BaseService implements WorkInfoService {
	private static final Log log = LogFactory.getLog(WorkInfoServiceImpl.class);

	private WorkInfoDao workInfodao;

	private DutyTimeDAO dutytimedao;

	private JdbcTemplate jdbcTemplate;

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

	/**
	 * 根据人员编号和考勤日期取得该人员的所有考勤流水记录
	 * @param custId
	 * @param signDate
	 * @return
	 */
	private List getCustWorkSerial(String custId,String signDate){
		StringBuffer querySql = new StringBuffer(1024);
		querySql.append("select ATT_DATE , ATT_TIME  from YKT_CK.T_ATTSERIAL_RECORD")
				.append(" where cust_id=" + custId + " and ATT_DATE='" + signDate + "'")
				.append(" union all")
				.append(" select ATT_DATE, ATT_TIME from YKT_CK.T_ATTSERIAL")
				.append(" where cust_id=" + custId + " and ATT_DATE='" + signDate + "'");
		List CustWorkSerialList = jdbcTemplate.queryForList(querySql.toString());
		return CustWorkSerialList;
	}
	/**
	 * 非坐班人员考勤信息 
	 * hanjiwei modify it 20061019
	 */
	private void dealWithNoSeatClerk(Map filter) throws Exception {
		String signDate = (String) filter.get("signDate");
		String custId = String.valueOf(filter.get("custId"));

		List cardList = getCustWorkSerial(custId,signDate);

		if (!cardList.isEmpty()) {
			Iterator checkTime = cardList.iterator();
			String minTime = "235959";
			String maxTime = "000001";
			String currentTime = "";
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
			TcheckattinfoId attInfoId = new TcheckattinfoId();
			Tcheckattinfo attInfo = new Tcheckattinfo();
			attInfoId.setCustId(new Integer(Integer.parseInt(custId)));
			attInfoId.setCheckDate(signDate);
			attInfo.setFactOntime(minTime);
			attInfo.setFactOfftime(maxTime);
			attInfo.setIfoffice("2");
			dutytimedao.save(attInfo);
		}
	}
	
	/**
	 * 取得个人考勤详细信息
	 * @param stuempNo
	 * @return
	 */
	public List getOneCheckDetail(int custId,String beginDate,String endDate) throws Exception{
		StringBuffer querySql = new StringBuffer(1024);
		querySql.append("select att_date,max(ATT_TIME) as endTime,min(att_time) as startTime")
		.append(" from YKT_CK.T_ATTSERIAL where cust_id="+custId)
		.append(" and att_date>='"+beginDate+"' and att_date<='"+endDate+"'")
		.append(" group by  att_date order by att_date desc");
		List result = jdbcTemplate.queryForList(querySql.toString());
		StringBuffer custSql = new StringBuffer(1024);
		custSql.append("select CUT_NAME,  STUEMP_NO ")
		.append(" from YKT_CUR.T_CIF_CUSTOMER where CUT_ID="+custId);
		Map cust = jdbcTemplate.queryForMap(custSql.toString());
		
		List personalCheckDetail = new ArrayList();
		Iterator iter = result.iterator();
		while (iter.hasNext()){
			Map checkDetail = new HashMap();
			Map queryMap = (Map) iter.next();
			checkDetail.put("STUEMP_NO",cust.get("STUEMP_NO"));
			checkDetail.put("CUT_NAME",cust.get("CUT_NAME"));
			checkDetail.put("att_date",queryMap.get("att_date"));
			checkDetail.put("startTime",formatTime(queryMap.get("startTime").toString()));
			checkDetail.put("endTime",formatTime(queryMap.get("endTime").toString()));
			personalCheckDetail.add(checkDetail);
		}
		
		return personalCheckDetail;
	}

	/**
	 * 为手工打卡搜索考勤人员 
	 * hanjiwei modify it 20060918
	 */
	public List searchClerkForReg(Map filter) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql
				.append("select cust.CUT_ID, cust.CUT_NAME,  cust.STUEMP_NO, cust.CLASSDEPT_NO,")
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

	/**
	 * 手工打卡 
	 * hanjiwei modify it 20060918
	 */
	public void manualRegister(List filter) throws Exception {
		if (filter != null && !filter.isEmpty()) {
			for (int i = 0; i < filter.size(); i++) {
				Tattserialrecord clerk = (Tattserialrecord) filter.get(i);
				workInfodao.save(clerk);
			}
		}
	}

	// 根据客户号查出卡号
	public Integer getCardIdByCustId(String custId) throws Exception {
		String sql = "select CARD_ID from YKT_CUR.T_PIF_CARD where  STATE_ID='1000' and COSUMER_ID="
				+ custId;
		List tempList = jdbcTemplate.queryForList(sql);
		Integer cardId = null;
		if (null != tempList) {
			Map tmpMap = (Map) tempList.get(0);
			cardId = (Integer) tmpMap.get("CARD_ID");
		}
		return cardId;
	}

	// 根据客户号查出物理卡号
	public String getPhyCardIdByCustId(String custId) throws Exception {
		String sql = "select PHYSICAL_NO from YKT_CUR.T_PIF_CARD where  STATE_ID='1000' and COSUMER_ID="
				+ custId;
		List tempList = jdbcTemplate.queryForList(sql);
		String phyCardId = null;
		if (null != tempList) {
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
			log.debug("sql:" + sql + tempStr);
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
	 * 判断是否存在考勤记录，存在返回true
	 * hanjiwei add it 20061020
	 * @param custId
	 * @param workDate
	 * @return
	 */
	private boolean exitRecordByCustId(String custId,String workDate){
		StringBuffer querySql = new StringBuffer(1024);
		querySql.append("select * from YKT_CK.T_CHECKATT_INFO")
		.append(" where CHECK_DATE='"+workDate+"'"+" and CUST_ID="+custId);
		List workConfInfoList = jdbcTemplate.queryForList(querySql.toString()); 
		if (workConfInfoList.isEmpty()){
			return false;
		}else{
			return true;
		}
	}
	
	/**
	 * 根据客户号和日期取得该人员的考勤制度信息
	 * hanjiwei add it 20061019
	 * @param custId
	 * @return
	 */
	private List getWorkConfInfoByCustId(String custId,String workDate){
		StringBuffer querySql = new StringBuffer(1024);
		querySql.append("select clerk.CUST_ID,clerk.DEPT_ID,clerk.IFOFFICE,clerk.AHEAD_OVERTIME,")
		.append("clerk.DELAY_OVERTIME,clerk.OVERTIME_VALUE,clerk.TWOREST_OVERTIME,clerk.HOLIDAY_OVERTIME,")
		.append("workConf.WORKCONF_ID,workConf.WORKCONF_NAME,workConf.OVERDUE_TIME,workConf.LEAVEEARLY_TIME,")
		.append("workConf.OVER_TIME, workConf.DELAY_TIME, workConf.CHECK_TIME, workTime.WORKTIME_ID,")
		.append("workTime.WORKTIME_NAME, workTime.ONTIME1, workTime.OFFTIME1, workTime.ONTIME2,")
		.append("workTime.OFFTIME2, workTime.ONTIME3, workTime.OFFTIME3,workTime.ONTIME4, workTime.OFFTIME4")
		.append(" from YKT_CK.T_CLERKINFO clerk ")
		.append(" left join YKT_CK.T_DEPT_WORKCONFINFO deptWork on deptWork.DEPT_ID=clerk.DEPT_ID")
		.append(" left join YKT_CK.T_WORKCONFINFO workConf on workConf.WORKCONF_ID = deptWork.WORKINFO_ID")
		.append(" left join YKT_CK.T_WORKTIMEINTO workTime on workTime.WORKTIME_ID = deptWork.WORKTIME_ID")
		.append(" where deptWork.BEGINDATE='"+workDate+"'"+" and clerk.CUST_ID="+custId);
		List workConfInfoList = jdbcTemplate.queryForList(querySql.toString()); 
		return workConfInfoList;
	}
	
	/**
	 * 判断时间大小，结束时间大于开始时间返回true
	 * hanjiwei add it 20061020
	 * @param currTime
	 * @param onTime
	 * @return
	 */
	private boolean diffTime(String beginTime,String endTime){
		if (DateUtilExtend.timeDiff1(beginTime, endTime) > 0){
			return true;
		}else{
			return false;
		}

	}
	/**
	 * 时间比较，结束时间和开始时间的差值小于给定的值返回true
	 * hanjiwei add it 20061020
	 * @param currTime
	 * @param onTime
	 * @return
	 */
	private boolean diffTime(String beginTime,String endTime,int overTime){
		if (DateUtilExtend.timeDiff1(beginTime, endTime) < overTime){
			return true;
		}else{
			return false;
		}
	}

	private String formatWorkTime2(String inTime){
		if ("".equals(inTime)|| null==inTime){
			return "";
		}else{
			return inTime+"00";
		}
	}
	/**
	 * 生成个人考勤信息 
	 * hanjiwei modify it 20061019
	 */
	private void createPersonWorkInfo(Map filter) throws Exception {
		String signDate = (String) filter.get("signDate");
		String custId = String.valueOf(filter.get("custId"));

		List cardList = getCustWorkSerial(custId,signDate);
		
		//根据人员编号取得考勤制度信息
		if (!getWorkConfInfoByCustId(custId,signDate).isEmpty() && (!cardList.isEmpty())){
			Map workTime = (Map)getWorkConfInfoByCustId(custId,signDate).get(0);
			String onTime1 = formatWorkTime2(workTime.get("ONTIME1").toString());
			String offTime1 = formatWorkTime2(workTime.get("OFFTIME1").toString());
			String onTime2 = formatWorkTime2(workTime.get("ONTIME2").toString());
			String offTime2 = formatWorkTime2(workTime.get("OFFTIME2").toString());
			String onTime3 = formatWorkTime2(workTime.get("ONTIME3").toString());
			String offTime3 = formatWorkTime2(workTime.get("OFFTIME3").toString());
			String onTime4 = formatWorkTime2(workTime.get("ONTIME4").toString());
			String offTime4 = formatWorkTime2(workTime.get("OFFTIME4").toString());
			
			int overTime = Integer.parseInt(workTime.get("OVER_TIME").toString());
			int delayTime = Integer.parseInt(workTime.get("DELAY_TIME").toString());

			Iterator checkTime = cardList.iterator();
			String workOnTime1 = "";
			String workOffTime1 = "";
			String workOnTime2 = "";
			String workOffTime2 = "";
			String workOnTime3 = "";
			String workOffTime3 = "";
			String workOnTime4 = "";
			String workOffTime4 = "";
			
			String varOnTime1 = "235959";
			String varOffTime1 = "235959";
			String varOnTime2 = "235959";
			String varOffTime2 = "235959";
			String varOnTime3 = "235959";
			String varOffTime3 = "235959";
			String varOnTime4 = "235959";
			String varOffTime4 = "235959";
			
			String currentTime = "";
			
			while (checkTime.hasNext()) {
				Map queryMap = (Map) checkTime.next();
				currentTime = (String) queryMap.get("ATT_TIME");
				//如果工作时间一不为空
				if (!"".equals(onTime1)){
					varOnTime1 = getWorkOnTime(currentTime,onTime1,offTime1,varOnTime1,overTime,"000001");
					varOffTime1 = getWorkOffTime(currentTime,onTime1,offTime1,varOffTime1,delayTime);
				}
				//工作时间2不为空
				if (!"".equals(onTime2)){
					varOnTime2 = getWorkOnTime(currentTime,onTime2,offTime2,varOnTime2,overTime,varOffTime1);
					varOffTime2 = getWorkOffTime(currentTime,onTime2,offTime2,varOffTime2,delayTime);
					
				}
				if (!"".equals(onTime3)){
					varOnTime3 = getWorkOnTime(currentTime,onTime3,offTime3,varOnTime3,overTime,varOffTime2);
					varOffTime3 = getWorkOffTime(currentTime,onTime3,offTime3,varOffTime3,delayTime);
					
				}
				if (!"".equals(onTime4)){
					varOnTime4 = getWorkOnTime(currentTime,onTime4,offTime4,varOnTime4,overTime,varOffTime3);
					varOffTime4 = getWorkOffTime(currentTime,onTime4,offTime4,varOffTime4,delayTime);
					
				}
			}
			workOnTime1 = formatWorkTime(varOnTime1);
			workOffTime1 = formatWorkTime(varOffTime1);
			workOnTime2 = formatWorkTime(varOnTime2);
			workOffTime2 = formatWorkTime(varOffTime2);
			workOnTime3 = formatWorkTime(varOnTime3);
			workOffTime3 = formatWorkTime(varOffTime3);
			workOnTime4 = formatWorkTime(varOnTime4);
			workOffTime4 = formatWorkTime(varOffTime4);
			
			TcheckattinfoId attInfoId = new TcheckattinfoId();
			Tcheckattinfo attInfo = new Tcheckattinfo();
			attInfoId.setCustId(new Integer(Integer.parseInt(custId)));
			attInfoId.setCheckDate(signDate);
			attInfo.setId(attInfoId);
			attInfo.setFactOntime1(workOnTime1);
			attInfo.setFactOfftime1(workOffTime1);
			attInfo.setFactOntime2(workOnTime2);
			attInfo.setFactOfftime2(workOffTime2);
			attInfo.setFactOntime3(workOnTime3);
			attInfo.setFactOfftime3(workOffTime3);
			attInfo.setFactOntime4(workOnTime4);
			attInfo.setFactOfftime4(workOffTime4);
			attInfo.setIfoffice("1");
			//先查询是否存在记录，存在则更新，否则保存
			if (exitRecordByCustId(custId,signDate)){
				dutytimedao.update(attInfo);
			}else{
				dutytimedao.save(attInfo);
			}
			
		}
	}
	
	/**
	 * 显示工作时间，如果工作时间“235959”，返回“000000”
	 * @param workTime
	 * @return
	 */
	private String formatWorkTime(String workTime){
		if ("235959".equals(workTime)){
			return "000000";
		}else{
			return workTime;
		}
	}

	/**
	 * 取得上班时间
	 * hanjiwei add it 20061020
	 * @param currTime
	 * @param onTime
	 * @param offTime
	 * @param varOnTime
	 * @param overTime
	 * @param varTime
	 * @return
	 */
	private String getWorkOnTime(String currTime,String onTime,String offTime,String varOnTime,int overTime,String varTime){
		String ronTime = "235959";
		//正常上班，提前打卡不能超过规定时间
		if (diffTime(currTime,onTime) && diffTime(currTime,onTime,overTime) && diffTime(varTime,currTime)){
			if (diffTime(currTime,varOnTime)){
				ronTime = currTime;
			}
		}
		//上班迟到处理，打卡时间必须在上班时间和结束时间之间
		if (diffTime(onTime,currTime)&&diffTime(currTime,offTime)){
			if (diffTime(currTime,varOnTime)){
				ronTime = currTime;
			}
		}
		return ronTime;
	}
	
	/**
	 * 取得下班时间信息
	 * hanjiwei add it 20061020
	 * @param currTime
	 * @param onTime
	 * @param offTime
	 * @param varOffTime
	 * @param delayTime
	 * @return
	 */
	private String getWorkOffTime(String currTime,String onTime,String offTime,String varOffTime,int delayTime){
		String roffTime = "235959";
		//正常下班，下班延迟时间不超过规定时间
		if (diffTime(offTime,currTime) && diffTime(offTime,currTime,delayTime)){
			if (diffTime(currTime,varOffTime)){
				roffTime = currTime;
			}
		}
		//早退，打卡时间必须在上班时间和下班时间之间才生效
		if (diffTime(onTime,currTime)&&diffTime(currTime,offTime)){
			if ("235959".equals(varOffTime)){
				if (diffTime(currTime,varOffTime)){
					roffTime = currTime;
				}
			}else{
				if (diffTime(varOffTime,currTime)){
					roffTime = currTime;
				}
			}
		}
		return roffTime;
	}
	/**
	 * 生成所有考勤人员信息，并把考勤信息写入到考勤数据表中 
	 * hanjiwei modify it 20061019
	 */
	public void createAllWorkInfoByDptConf(Map filter) throws Exception {
		String startDate = (String) filter.get("startDate");
		String endDate = (String) filter.get("endDate");
		String deptId = (String) filter.get("deptId");
		String stuEmpNo = (String) filter.get("stuEmpNo");
		StringBuffer querySql = new StringBuffer(1024);
		querySql.append("select clerk.CUST_ID, clerk.DEPT_ID,clerk.IFOFFICE from YKT_CK.T_CLERKINFO clerk")
		.append(" left join YKT_CUR.T_CIF_CUSTOMER cust on cust.CUT_ID=clerk.CUST_ID")
		.append(" where 1>0");
		if ((!"".equals(deptId))&& !(null==deptId)){
			querySql.append(" and clerk.DEPT_ID='"+deptId+"'");
		}
		if ((!"".equals(stuEmpNo))&& !(null==stuEmpNo)){
			querySql.append(" and cust.STUEMP_NO='"+stuEmpNo+"'");
		}
		List custList = jdbcTemplate.queryForList(querySql.toString());
		
		Map custInfo = new HashMap();
		
		long diffDate = DateUtilExtend.diffDate(startDate,endDate);
		for (long diffDay = 0;diffDay<=diffDate;diffDay++){
			String workDate = DateUtilExtend.addDate2(startDate,(int)diffDay);
			custInfo.put("signDate",workDate);
			if (!custList.isEmpty()){
				Iterator tmpList = custList.iterator();
				String ifOffice = "";
				while (tmpList.hasNext()){
					Map custInfoList = (Map) tmpList.next();
					ifOffice = custInfoList.get("IFOFFICE").toString();
					custInfo.put("custId",custInfoList.get("CUST_ID"));
					if ("2".equals(ifOffice)){
						dealWithNoSeatClerk(custInfo);
					}else if ("1".equals(ifOffice)){
						createPersonWorkInfo(custInfo);
					}
				}
			}
		}		
	}
	
	private String formatTime(String inTime){
		if ("".equals(inTime) || null==inTime){
			return "";
		}else{
			return inTime.substring(0,2)+":"+inTime.substring(2,4);
		}
		
	}
}
