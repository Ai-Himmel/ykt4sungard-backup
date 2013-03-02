package org.king.check.service.impl;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.king.check.dao.ClerkDAO;
import org.king.check.domain.Tclerkinfo;
import org.king.check.service.DutyTimeService;
import org.king.check.service.SysService;
import org.king.check.util.DateUtilExtend;
import org.king.check.vo.DutyTimeVo;
import org.king.framework.dao.MyQuery;
import org.king.check.config.*;
import org.springframework.jdbc.core.JdbcTemplate;

public class DutyTimeServiceImpl implements DutyTimeService {

	//private static final Log log = LogFactory.getLog(DutyTimeServiceImpl.class); 

	private JdbcTemplate jdbcTemplate;

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}
	private ClerkDAO clerkDAO;

	private SysService sysService;

	public void setClerkDAO(ClerkDAO clerkDAO) {
		this.clerkDAO = clerkDAO;
	}

	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}

	public List find(MyQuery myQuery) {
		return null;
	}

	public List find(String query) {
		return null;
	}

	public List getAll() {
		return null;
	}

	/**
	 * hanjiwei save it 
	 */
	public Map searchForNewFormat(Map filter) throws Exception {
		List departList;
		List clerkList;
		String startDate = DateUtilExtend.formatDate2((String) filter
				.get(CommonConfig.startDate));
		String endDate = DateUtilExtend.formatDate2((String) filter
				.get(CommonConfig.endDate));
		
		String accountId = (String) filter.get("accountId");
		boolean token = true;
		boolean resExist = false;
		String dutySingal = " <tr align='center' valign=center>";

		String title = "<td width='90' align='center'   bgcolor='#A8D1E6'>部门</td>  <td><table border='1'  cellpadding='1'"
				+ "  cellspacing='1'  bgcolor='#F6F4F5' > <tr>";
		Map resMap = new HashMap();
		String lastStr = "</table></td></tr>";

		List newFormatList = new ArrayList();

		if (StringUtils.isNotEmpty((String) filter.get(CommonConfig.deptId))) {
			if (((String) filter.get(CommonConfig.deptId)).equals("all")) {
				departList = sysService.getDeptList(accountId);//departmentDao.getAll();
			} else {
				departList = sysService.getDeptInfo((String) filter.get(CommonConfig.deptId));//departmentDao.find(dpthql);
			}
			if (!departList.isEmpty()) {
				Iterator departIte = departList.iterator();
				while (departIte.hasNext()) {
					Map department = (Map) departIte.next();
					String hql = "from Tclerkinfo c where c.deptId='"
							+ department.get("deptId") + "' and c.ifoffice='2'";

					clerkList = clerkDAO.find(hql);
					if (!clerkList.isEmpty()) {
						Iterator clerkIte = clerkList.iterator();

						DutyTimeVo dutyTimeVo = new DutyTimeVo();
						String preDutyStrs = "<tr><td width='90' align='center' bgcolor='#A8D1E6' >"
								+ department.get("deptName")
								+ "</td><td>"
								+ "<table border='1'  cellpadding='1'  cellspacing='1' >"
								+ "";
						String dutyInfo = "";
						// 遍历一个部门的所有员工
						while (clerkIte.hasNext()) {
							String checkDate = startDate;
							
							Tclerkinfo clerk = (Tclerkinfo) clerkIte.next();
							String clerkName = "";
							clerkName = sysService.getCustomerNameByCustomerId(clerk.getCustId());
							//表示有搜索资源
							resExist = true;
							if (null == clerkName) {
								clerkName = "&nbsp; ";
							}

							dutyInfo += "<tr>";
							dutyInfo += "<td width='90' align='center'  class='tdHeader1'>" + clerkName + "</td>";

							if (token) {
								title += "<td width='90' align='center' class='tdHeader1' rowspan='2'>&nbsp;&nbsp;&nbsp;&nbsp;姓&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;名&nbsp;&nbsp;&nbsp;&nbsp;</td>";
							}

							while (DateUtilExtend.diffDate(endDate, checkDate) <= 0) {
								/*
								StringBuffer seriSql = new StringBuffer(1024);
								seriSql.append("select CUST_ID, CHECK_DATE, DEPT_ID, IFOFFICE, FACT_ONTIME,")
								.append(" FACT_OFFTIME from YKT_CK.T_CHECKATT_INFO where CUST_ID=")
								.append(clerk.getCustId())
								.append(" and CHECK_DATE='").append(checkDate).append("'");
								List resList = jdbcTemplate.queryForList(seriSql.toString());
								List leaveList = getLeaveList(checkDate,clerk);
								boolean haveManual = getIfHaveManual(checkDate,clerk);
								//如果有请假信息，则显示已经请假
								if (resList.size()==0) {
									if (leaveList.size()==0){
										dutyInfo += "<td width='95' align='center'>&nbsp;&nbsp;&nbsp;</td>";
									}else{
										Map leaveMap = (Map)leaveList.get(0);
										dutyInfo += "<td width='95' align='center' style='background-color: #FACDE4'>"
												+"<a href='searchNoSeatWorkInfo.do?method=goLeaveDetailInfo&leaveReportId="
												+leaveMap.get("ID").toString()+"'>"+sysService.getLeaveTypeName(leaveMap.get("LEAVE_ID").toString())
												+"</a></td>";
									}
									
								} else {
									Map checkMap =(Map)resList.get(0);
									String onTime = checkMap.get("FACT_ONTIME").toString();
									String offTime = checkMap.get("FACT_OFFTIME").toString();
									if (onTime.equals(offTime)){
										offTime = "";
									}
									//如果有请假信息，则以不同的颜色显示
									if (leaveList.size()==0){
										dutyInfo += "<td width='95' align='center'  class='tableHeader6'>"
											+ formatTime(onTime)
											+ "--"
											+ ""
											+ formatTime(offTime)
											+ "</td>";
									}else if ((leaveList.size()>0)&&(!haveManual)){
										Map leaveMap = (Map)leaveList.get(0);
										dutyInfo += "<td width='95' align='center' style='background-color: #F9F4B9'>"
											+ "<a href='searchNoSeatWorkInfo.do?method=goLeaveDetailInfo&leaveReportId="
											+leaveMap.get("ID").toString()+"'>"
											+ formatTime(onTime)
											+ "--"
											+ ""
											+ formatTime(offTime)
											+ "</a></td>";
									}else if ((leaveList.size()==0)&&(haveManual)){
										dutyInfo += "<td width='95' align='center' style='background-color: #B6D8FE'>" 
											+ formatTime(onTime)
											+ "--"
											+ ""
											+ formatTime(offTime)
											+ "</td>";
									}else if ((leaveList.size()>0)&&(haveManual)){
										Map leaveMap = (Map)leaveList.get(0);
										dutyInfo += "<td width='95' align='center' style='background-color: #F9F4B9'>*"
											+ "<a href='searchNoSeatWorkInfo.do?method=goLeaveDetailInfo&leaveReportId="
											+leaveMap.get("ID").toString()+"'>"
											+ formatTime(onTime)
											+ "--"
											+ ""
											+ formatTime(offTime)
											+ "</a>*</td>";
									}
								}
								if (token) {
									title += "<td width='95' align='center'  class='tableHeader6'>"
											+ checkDate + "</td>";
									dutySingal += "<td align='center' valign='middle' class='tableHeader6' >上班&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;下班</td>";
								}
								checkDate = DateUtilExtend.addDate2(checkDate,1);
								*/
								
								StringBuffer seriSql = new StringBuffer();
								seriSql.append("select CUST_ID, CARD_ID, ATT_DATE, ATT_TIME")
								.append(" from YKT_CK.T_ATTSERIAL")
								.append(" where cust_id=").append(clerk.getCustId())
								.append(" and ATT_DATE='").append(checkDate).append("'")
								.append(" union select CUST_ID, CARD_ID,ATT_DATE, ATT_TIME")
								.append(" from YKT_CK.T_ATTSERIAL_RECORD")
								.append(" where cust_id=").append(clerk.getCustId())
								.append(" and ATT_DATE='").append(checkDate).append("'");
								List resList = jdbcTemplate.queryForList(seriSql.toString());
								List leaveList = getLeaveList(checkDate,clerk);
								List manualList = getManualRecordList(checkDate,clerk);
								boolean haveManual = getIfHaveManual(checkDate,clerk);
								if (resList.isEmpty()) {
									if (leaveList.size()==0){
										dutyInfo += "<td width='95' align='center'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>";
									}else{
										Map leaveMap = (Map)leaveList.get(0);
										dutyInfo += "<td width='95' align='center' style='background-color: #FACDE4'>"
												+"<a href='searchNoSeatWorkInfo.do?method=goLeaveDetailInfo&leaveReportId="
												+leaveMap.get("ID").toString()+"'>"+sysService.getLeaveTypeName(leaveMap.get("LEAVE_ID").toString())
												+"</a></td>";
									}
								} else {
									// add by hanjiwei20060831
									// 把取出的数据进行比较，取当天考勤时间的最大值和最小值
									
									String minTime = "235959";
									String maxTime = "000000";
									String currTime = "000000";
									Iterator dutyIter = resList.iterator();
									while (dutyIter.hasNext()) {
										Map attS = (Map) dutyIter.next();
										
										currTime = attS.get("ATT_TIME").toString();
										if (DateUtilExtend.timeDiff1(maxTime,currTime) > 0) {
											maxTime = currTime;
										}
										if (DateUtilExtend.timeDiff1(minTime,currTime) < 0) {
											minTime = currTime;
										}
									}
									if (maxTime.equals(minTime)){
										maxTime = "";
									}
									//如果有请假信息，则以不同的颜色显示
									if ((leaveList.size()==0)&&(!haveManual)){
										dutyInfo += "<td width='95' align='center'  class='tableHeader6'>"
											+ formatTime(minTime)
											+ "--"
											+ ""
											+ formatTime(maxTime)
											+ "</td>";
									}else if ((leaveList.size()>0)&&(!haveManual)){
										Map leaveMap = (Map)leaveList.get(0);
										//请半天假
										dutyInfo += "<td width='95' align='center' style='background-color: #F9F4B9'>"
											+ "<a href='searchNoSeatWorkInfo.do?method=goLeaveDetailInfo&leaveReportId="
											+leaveMap.get("ID").toString()+"'>"
											+ formatTime(minTime)
											+ "--"
											+ ""
											+ formatTime(maxTime)
											+ "</a></td>";
									}else if ((leaveList.size()==0)&&(haveManual)){
										//Map manualMap = (Map)manualList.get(0);
										//手工签到
										dutyInfo += "<td width='95' align='center' style='background-color: #B6D8FE'>" 
											+ "<a href='searchNoSeatWorkInfo.do?method=goManualDetailInfo&custId="
											+ clerk.getCustId()+"&clerkDate="+checkDate+"&minTime="+minTime+"&maxTime="+maxTime+"'>"
											+ formatTime(minTime)
											+ "--"
											+ ""
											+ formatTime(maxTime)
											+ "</td>";
									}else if ((leaveList.size()>0)&&(haveManual)){
										Map leaveMap = (Map)leaveList.get(0);
										dutyInfo += "<td width='95' align='center' style='background-color: #F9F4B9'>*"
											+ "<a href='searchNoSeatWorkInfo.do?method=goLeaveDetailInfo&leaveReportId="
											+leaveMap.get("ID").toString()+"'>"
											+ formatTime(minTime)
											+ "--"
											+ ""
											+ formatTime(maxTime)
											+ "</a>*</td>";
									}
								}
								if (token) {
									title += "<td width='90' align='center'  class='tableHeader6'>&nbsp;&nbsp;&nbsp;&nbsp;"
											+ checkDate + "&nbsp;&nbsp;&nbsp;&nbsp;</td>";
									dutySingal += "<td align='center' valign='middle' class='tableHeader6' >上班&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;下班</td>";
								}
								checkDate = DateUtilExtend.addDate2(checkDate,1);
								
							}
							dutyInfo += "</tr>";
							token = false;
						}
						dutyTimeVo.setDutyTimeStr(preDutyStrs + dutyInfo + lastStr);
						//log.debug(dutyTimeVo.getDutyTimeStr());
						newFormatList.add(dutyTimeVo);
					}
				}
			}
		}
		//log.debug("before");

		dutySingal += "</tr>";
		title += "</tr>";
		title += dutySingal + "</table></td>";

		if (!resExist)
			title = "<td width='100' bgcolor='#A8D1E6' align='center'>没有数据<td>";

		resMap.put(CommonConfig.titleStr, title);
		resMap.put(CommonConfig.dutyStrs, newFormatList);

		return resMap;
	}
	
	private List getLeaveList(String checkDate,Tclerkinfo clerk){
		StringBuffer queryStr = new StringBuffer(1024);
		queryStr.append("select ID, REPROT_DATE, REPORT_TIME, CUST_ID, DEPT_ID, LEAVE_ID")
		.append(" from YKT_CK.T_REPORTLEAVE where LEAVE_BEGINDATE<='").append(checkDate)
		.append("' and LEAVE_ENDDATE>='").append(checkDate).append("' and CUST_ID=")
		.append(clerk.getCustId()).append(" and IFAGREE='1'");
		List leaveList = jdbcTemplate.queryForList(queryStr.toString());
		return leaveList;
	}
	
	private List getManualRecordList(String checkDate,Tclerkinfo clerk){
		StringBuffer queryStr = new StringBuffer(1024);
		queryStr.append("select CUST_ID, ATT_DATE, ATT_TIME,OPER_ID, OPER_DATE, OPER_TIME")
		.append(" from YKT_CK.T_ATTSERIAL_RECORD where ATT_DATE='").append(checkDate)
		.append("' and CUST_ID=").append(clerk.getCustId());
		List leaveList = jdbcTemplate.queryForList(queryStr.toString());
		return leaveList;
	}
	
	private boolean getIfHaveManual(String checkDate,Tclerkinfo clerk){
		StringBuffer queryStr = new StringBuffer(1024);
		queryStr.append("select count(*) as num")
		.append(" from YKT_CK.T_ATTSERIAL_RECORD")
		.append(" where cust_id=").append(clerk.getCustId())
		.append(" and ATT_DATE='").append(checkDate).append("'");
		int resList = jdbcTemplate.queryForInt(queryStr.toString());
		if (resList>0){
			return true;
		}else{
			return false;
		}
	}
	private String formatTime(String inTime){
		String hour = "";
		String second = "";
		if ("".equals(inTime)){
			return "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
		}else{
			hour = inTime.substring(0,2);
			second = inTime.substring(2,4);
			return hour+":"+second;
		}
	}

}
