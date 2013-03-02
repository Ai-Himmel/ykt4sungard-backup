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
import org.king.check.util.StringUtil;
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
	 * �ù���ɾ������������Ա������־��ѯʹ��getNoSeatList������ʹ�ô˹���20080107
	 * hanjiwei save it 
	 */
	public Map searchForNewFormat(Map filter) throws Exception {
		//getNoSeatList(filter);
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

		String title = "<td width='90' align='center'   bgcolor='#A8D1E6'>����</td>  <td><table border='1'  cellpadding='1'"
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
						// ����һ�����ŵ�����Ա��
						while (clerkIte.hasNext()) {
							String checkDate = startDate;
							
							final Tclerkinfo clerk = (Tclerkinfo) clerkIte.next();
							String clerkName = "";
							clerkName = sysService.getCustomerNameByCustomerId(clerk.getCustId());
							//��ʾ��������Դ
							resExist = true;
							if (null == clerkName) {
								clerkName = "&nbsp; ";
							}

							dutyInfo += "<tr>";
							dutyInfo += "<td width='90' align='center'  class='tdHeader1'>" + clerkName + "</td>";

							if (token) {
								title += "<td width='90' align='center' class='tdHeader1' rowspan='2'>&nbsp;&nbsp;&nbsp;&nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;</td>";
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
								//����������Ϣ������ʾ�Ѿ����
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
									//����������Ϣ�����Բ�ͬ����ɫ��ʾ
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
									dutySingal += "<td align='center' valign='middle' class='tableHeader6' >�ϰ�&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;�°�</td>";
								}
								checkDate = DateUtilExtend.addDate2(checkDate,1);
								*/
								
								/*
								StringBuffer seriSql = new StringBuffer();
								seriSql.append("select CUST_ID, CARD_ID, ATT_DATE, ATT_TIME")
								.append(" from YKT_CK.T_ATTSERIAL")
								.append(" where cust_id=").append(clerk.getCustId())
								.append(" and ATT_DATE='").append(checkDate).append("'")
								.append(" union select CUST_ID, CARD_ID,ATT_DATE, ATT_TIME")
								.append(" from YKT_CK.T_ATTSERIAL_RECORD")
								.append(" where cust_id=").append(clerk.getCustId())
								.append(" and ATT_DATE='").append(checkDate).append("'");
								*/
								StringBuffer seriSql = new StringBuffer();
								seriSql.append("select CUST_ID, CARD_ID, ATT_DATE, ATT_TIME")
								.append(" from YKT_CK.T_ATTSERIAL")
								.append(" where cust_id=?")
								.append(" and ATT_DATE=?")
								.append(" union select CUST_ID, CARD_ID,ATT_DATE, ATT_TIME")
								.append(" from YKT_CK.T_ATTSERIAL_RECORD")
								.append(" where cust_id=?")
								.append(" and ATT_DATE=?");
								
								List resList = jdbcTemplate.queryForList(seriSql.toString(),
										new Object[]{clerk.getCustId(),checkDate,clerk.getCustId(),checkDate});
								//List resList = jdbcTemplate.queryForList(seriSql.toString());
								List leaveList = getLeaveList(checkDate,clerk.getCustId());
								//List manualList = getManualRecordList(checkDate,clerk);
								boolean haveManual = getIfHaveManual(checkDate,clerk.getCustId());
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
									// ��ȡ�������ݽ��бȽϣ�ȡ���쿼��ʱ������ֵ����Сֵ
									
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
									//����������Ϣ�����Բ�ͬ����ɫ��ʾ
									if ((leaveList.size()==0)&&(!haveManual)){
										dutyInfo += "<td width='95' align='center'  class='tableHeader6'>"
											+ formatTime(minTime)
											+ "--"
											+ ""
											+ formatTime(maxTime)
											+ "</td>";
									}else if ((leaveList.size()>0)&&(!haveManual)){
										Map leaveMap = (Map)leaveList.get(0);
										//������
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
										//�ֹ�ǩ��
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
									dutySingal += "<td align='center' valign='middle' class='tableHeader6' >�ϰ�&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;�°�</td>";
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
			title = "<td width='100' bgcolor='#A8D1E6' align='center'>û������<td>";

		resMap.put(CommonConfig.titleStr, title);
		resMap.put(CommonConfig.dutyStrs, newFormatList);

		return resMap;
	}
	
	/*
	 * ȡ�÷����࿼����Ա������Ϣ�б�
	 */
	public List getNoSeatList(Map filter)throws Exception{
		String startDate = DateUtilExtend.formatDate2((String) filter.get(CommonConfig.startDate));
		String endDate = DateUtilExtend.formatDate2((String) filter.get(CommonConfig.endDate));
		//String accountId = (String) filter.get("accountId");
		String deptId = "";
		if (StringUtils.isNotEmpty((String) filter.get("deptId"))) {
			deptId = (String) filter.get("deptId");
		}
		Iterator checkIter = sysService.getClerkInfo(deptId).iterator();
		//����ʱ��
		Map checkTimeMap = getCheckTime(deptId,startDate,endDate);
		//����������ٱ��Ϊ��ٶ�Ӧ��ID
		Map leaveMap = getLeaveList(deptId,startDate,endDate);
		//�ֹ�����������ֹ����ڱ��Ϊ1
		Map manualMap = getIfHaveManual(deptId,startDate,endDate);
		
		
		List checkInfoList = new ArrayList(); 
		while (checkIter.hasNext()){
			Map checkMap = (Map)checkIter.next();
			Map checkInfoMap = new HashMap();
			//ȡ����Ա��Ϣ�Ϳ�����Ϣ�����뵽list��
			Integer custId = Integer.valueOf(checkMap.get("cust_id").toString());
			checkInfoMap.put("deptName",checkMap.get("dept_name").toString());
			checkInfoMap.put("stuempNo",checkMap.get("stuemp_no").toString());
			checkInfoMap.put("custName",checkMap.get("cut_name").toString());
			checkInfoMap.put("custType",checkMap.get("dict_caption").toString());
			checkInfoMap.put("custId",custId);
			
			String checkDate = startDate;
			while (DateUtilExtend.diffDate(endDate, checkDate) <= 0) {
				String key = custId.toString()+"-"+checkDate;
				
				Object checkTimeObj = checkTimeMap.get(key);
				String checkTime;
				if(checkTimeObj==null){
					checkTime = "--";
				} else {
					checkTime = checkTimeObj.toString();
				}
				
				Object leaveFlag = leaveMap.get(key);
				Object manualFlag = manualMap.get(key);
				
				StringBuffer chkTimeStr = new StringBuffer(512);
				
				if (leaveFlag==null && manualFlag==null){
					//û���ֹ����ں���ټ�¼
					chkTimeStr.append(checkTime).append("/-1/~");
				}else if (leaveFlag!=null && manualFlag==null){
					//����ټ�¼
					chkTimeStr.append(checkTime)
					.append("/").append(CommonConfig.leave)
					.append("/").append(CommonConfig.leaveDetail)
					.append(leaveFlag);
				}else if (leaveFlag==null && manualFlag!=null){
					//���ֹ�ǩ����¼
					String[] sTime = StringUtil.split(checkTime,"--");
					chkTimeStr.append(checkTime)
					.append("/").append(CommonConfig.manual)
					.append("/").append(CommonConfig.manualDetail)
					.append(custId)
					.append("&clerkDate=").append(checkDate)
					.append("&minTime=").append(sTime[0]);
					if (sTime.length>1){
						chkTimeStr.append("&maxTime=").append(sTime[1]);
					}else{
						chkTimeStr.append("&maxTime=").append("");
					}
				}else if (leaveFlag!=null && manualFlag!=null){
					//����ټ�¼���������ֹ����ڼ�¼
					chkTimeStr.append(checkTime)
					.append("/").append(CommonConfig.leaveManual)
					.append("/").append(CommonConfig.leaveManualDetail)
					.append(leaveFlag);
				}
				checkInfoMap.put(checkDate,chkTimeStr.toString());
				
				//��������һ��
				checkDate = DateUtilExtend.addDate2(checkDate,1);
			}
			checkInfoList.add(checkInfoMap);
		}
		return checkInfoList;
	}
	
	/*
	 * ȡ��ĳһ��Ŀ��ڿ�ʼʱ��ͽ���ʱ��
	 */
	private String getCheckTime(String checkDate,Integer custId){
		StringBuffer seriSql = new StringBuffer();
		seriSql.append("select CUST_ID, CARD_ID, ATT_DATE, ATT_TIME")
		.append(" from YKT_CK.T_ATTSERIAL")
		.append(" where cust_id=?")
		.append(" and ATT_DATE=?")
		.append(" union select CUST_ID, CARD_ID,ATT_DATE, ATT_TIME")
		.append(" from YKT_CK.T_ATTSERIAL_RECORD")
		.append(" where cust_id=?")
		.append(" and ATT_DATE=?");
		
		List resList = jdbcTemplate.queryForList(seriSql.toString(),
				new Object[]{custId,checkDate,custId,checkDate});
		if (resList.isEmpty()){
			return "--";
		}else{
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
			return formatTime(minTime)+"--"+formatTime(maxTime);
		}
	}
	
	/**
	 * ����ָ��ʱ��ε�customerÿ�տ���ʱ��(���翼��ʱ��--������ʱ��)
	 * @param deptId
	 * @param startDate
	 * @param endDate
	 * @return
	 */
	private Map getCheckTime(String deptId,String startDate,String endDate){
		StringBuffer seriSql = new StringBuffer();
		seriSql.append("select t.cust_id, t.card_id, t.att_date, t.att_time");
		seriSql.append(" from ykt_ck.t_clerkinfo cle,ykt_cur.t_cif_customer cust,ykt_ck.department dept,ykt_cur.t_pif_dictionary cap,");
		seriSql.append("(select cust_id, card_id, att_date, att_time");
		seriSql.append(" from ykt_ck.t_attserial att");
		seriSql.append(" where att.att_date between '").append(startDate).append("' and '").append(endDate).append("'");
		seriSql.append(" union");
		seriSql.append(" select cust_id, card_id, att_date, att_time");
		seriSql.append(" from ykt_ck.t_attserial_record attr");
		seriSql.append(" where attr.att_date between '").append(startDate).append("' and '").append(endDate).append("') t");
		seriSql.append(" where cle.cust_id = cust.cut_id and cle.dept_id = dept.dept_id");
		seriSql.append(" and cle.ifoffice = cap.dict_value and cap.dict_no = 1200");
		seriSql.append(" and cust.cut_id = t.cust_id");
		if (StringUtils.isNotBlank(deptId)){
			seriSql.append(" and cle.dept_id='").append(deptId).append("'");
		}
		seriSql.append(" order by cle.dept_id, t.cust_id, t.att_date");
		
		List resList = jdbcTemplate.queryForList(seriSql.toString());
		
		Iterator iterator = resList.iterator();
		String custId = null;
		String attDate = null;
		String minTime = "235959";
		String maxTime = "000000";
		String currTime = "000000";
		//key cust_id-att_date,value checkTime
		Map checkTimeMap = new HashMap();
		while (iterator.hasNext()){
			Map timeMap = (Map)iterator.next();
			String currentCustId = timeMap.get("cust_id")==null?"":timeMap.get("cust_id").toString();
			String currentAttDate = timeMap.get("att_date")==null?"":timeMap.get("att_date").toString();
			
			//��Ϊ����ǰ�dept_id��cust_id��att_date����ģ����ԣ�����һ����¼��cust_id��att_date����һ����ͬʱ����һ����¼��Ӧ��cust_id��checkTime������ϣ����Խ��б���
			if((!currentCustId.equals(custId) || !currentAttDate.equals(attDate))&& custId!=null){
				if (maxTime.equals(minTime)){
					maxTime = "";
				}
				checkTimeMap.put(custId+"-"+attDate, formatTime(minTime)+"--"+formatTime(maxTime));
				//��ʼ��
				minTime = "235959";
				maxTime = "000000";
				currTime = "000000";
			}
			
			attDate = currentAttDate;
			custId = currentCustId;
			//�Ƚ�ʱ�䣬����������Сʱ��
			currTime = timeMap.get("ATT_TIME").toString();
			if (DateUtilExtend.timeDiff1(maxTime,currTime) > 0) {
				maxTime = currTime;
			}
			if (DateUtilExtend.timeDiff1(minTime,currTime) < 0) {
				minTime = currTime;
			}
		}
		
		//�洢���һ��ˢ����¼
		if(custId!=null){
			if (maxTime.equals(minTime)){
				maxTime = "";
			}
			checkTimeMap.put(custId+"-"+attDate, formatTime(minTime)+"--"+formatTime(maxTime));
		}
		
		return checkTimeMap;
	}
	
	/**
	 * ����ָ����Χ�ڵ�������
	 * @param deptId
	 * @param startDate
	 * @param endDate
	 * @return
	 */
	private Map getLeaveList(String deptId,String startDate,String endDate){
		StringBuffer queryStr = new StringBuffer(1024);
		queryStr.append("select rl.id,cust.cut_id, rl.leave_begindate, rl.leave_enddate");
		queryStr.append(" from ykt_ck.t_clerkinfo cle,ykt_cur.t_cif_customer cust,ykt_ck.department dept,ykt_cur.t_pif_dictionary cap,ykt_ck.t_reportleave rl");
		queryStr.append(" where cle.cust_id = cust.cut_id and cle.dept_id = dept.dept_id and cle.ifoffice = cap.dict_value");
		queryStr.append(" and cap.dict_no = 1200 and cust.cut_id = rl.cust_id and rl.ifagree = '1'");
		queryStr.append(" and ((rl.leave_begindate < ? and rl.leave_enddate >= ?) or");
		queryStr.append(" (rl.leave_begindate >= ? and rl.leave_begindate <= ?))");
		if (StringUtils.isNotBlank(deptId)){
			queryStr.append(" and cle.dept_id='").append(deptId).append("'");
		}
		
		List leaveList = jdbcTemplate.queryForList(queryStr.toString(),new Object[]{startDate,startDate,startDate,endDate});
		Iterator iterator = leaveList.iterator();
		Map leaveMap = new HashMap();
		while (iterator.hasNext()){
			Map row = (Map)iterator.next();
			String checkDate = startDate;
			String leaveBeginDate = row.get("leave_begindate").toString();
			String leaveEndDate = row.get("leave_enddate").toString();
			String custId = row.get("cut_id").toString();
			String id = row.get("id").toString();
			while (DateUtilExtend.diffDate(endDate, checkDate) <= 0) {
				//�����ǰ������leaveBeginDate��leaveEndDate֮�䣬��ô˵����һ���Ӧ�û����
				if(DateUtilExtend.diffDate(leaveBeginDate, checkDate) >= 0 && DateUtilExtend.diffDate(leaveEndDate, checkDate) <= 0){
					//����򽫱�Ǽ�Ϊ��ٶ�Ӧ��ID
					leaveMap.put(custId+"-"+checkDate, id);
				}
				
				//��������һ��
				checkDate = DateUtilExtend.addDate2(checkDate,1);
			}
		}
		return leaveMap;
	}
	
	private List getLeaveList(String checkDate,Integer custId){
		StringBuffer queryStr = new StringBuffer(1024);
		queryStr.append("select ID, REPROT_DATE, REPORT_TIME, CUST_ID, DEPT_ID, LEAVE_ID")
		.append(" from YKT_CK.T_REPORTLEAVE where LEAVE_BEGINDATE<=?")
		.append(" and LEAVE_ENDDATE>=?").append(" and CUST_ID=?")
		.append(" and IFAGREE='1'");
		List leaveList = jdbcTemplate.queryForList(queryStr.toString(),new Object[]{checkDate,checkDate,custId});
		return leaveList;
	}
	
	/**
	 * ����ָ����Χ�ε��ֹ��������
	 * @param deptId
	 * @param startDate
	 * @param endDate
	 * @return
	 */
	private Map getIfHaveManual(String deptId,String startDate,String endDate){
		StringBuffer queryStr = new StringBuffer(1024);
		queryStr.append("select attr.cust_id, attr.att_date, count(attr.cust_id) check_count");
		queryStr.append(" from ykt_ck.t_clerkinfo cle,ykt_cur.t_cif_customer cust,ykt_ck.department dept,ykt_cur.t_pif_dictionary cap,ykt_ck.t_attserial_record attr");
		queryStr.append(" where cle.cust_id = cust.cut_id and cle.dept_id = dept.dept_id and cle.ifoffice = cap.dict_value");
		queryStr.append(" and cap.dict_no = 1200 and cust.cut_id = attr.cust_id");
		queryStr.append(" and attr.att_date between '").append(startDate).append("' and '").append(endDate).append("'");
		if (StringUtils.isNotBlank(deptId)){
			queryStr.append(" and cle.dept_id='").append(deptId).append("'");
		}
		queryStr.append(" group by attr.cust_id, attr.att_date");
		
		List resList = jdbcTemplate.queryForList(queryStr.toString());
		Iterator iterator = resList.iterator();
		Map manualMap = new HashMap();
		while (iterator.hasNext()){
			Map row = (Map)iterator.next();
			String custId = row.get("cust_id").toString();
			String attDate = row.get("att_date").toString();
			//������ֹ����ڣ���ô���Ϊ1
			manualMap.put(custId+"-"+attDate, "1");
		}
		return manualMap;
	}
	
	private boolean getIfHaveManual(String checkDate,Integer custId){
		StringBuffer queryStr = new StringBuffer(1024);
		queryStr.append("select count(*) as num")
		.append(" from YKT_CK.T_ATTSERIAL_RECORD")
		.append(" where cust_id=?")
		.append(" and ATT_DATE=?");
		int resList = jdbcTemplate.queryForInt(queryStr.toString(),new Object[]{custId,checkDate});
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
			return "";
		}else{
			hour = inTime.substring(0,2);
			second = inTime.substring(2,4);
			return hour+":"+second;
		}
	}

}
