package org.king.check.service.impl;

import java.io.Serializable;
import java.sql.Types;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.AttserialDAO;
import org.king.check.dao.ClerkDAO;
import org.king.check.dao.DepartmentDAO;
import org.king.check.dao.DutyTimeDAO;
import org.king.check.domain.Department;
import org.king.check.domain.DutyTime;
import org.king.check.domain.Tattserial;
import org.king.check.domain.Tclerkinfo;
import org.king.check.service.DutyTimeService;
import org.king.check.service.SysService;
import org.king.check.util.DateUtilExtend;
import org.king.check.vo.DutyTimeVo;
import org.king.framework.dao.MyQuery;
import org.king.check.config.*;

public class DutyTimeServiceImpl implements DutyTimeService {

	private static final Log log = LogFactory.getLog(DutyTimeServiceImpl.class);

	private DutyTimeDAO dutyTimeDao;

	private DepartmentDAO departmentDao;

	private ClerkDAO clerkDAO;

	private SysService sysService;

	private AttserialDAO attserialDao;

	public void setDutyTimeDao(DutyTimeDAO dutyTimeDao) {
		this.dutyTimeDao = dutyTimeDao;
	}

	public void setDepartmentDao(DepartmentDAO departmentDao) {
		this.departmentDao = departmentDao;
	}

	public DutyTimeDAO getDutyTimeDao() {
		return dutyTimeDao;
	}

	public void setClerkDAO(ClerkDAO clerkDAO) {
		this.clerkDAO = clerkDAO;
	}

	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}

	public AttserialDAO getAttserialDAO() {
		return attserialDao;
	}

	public void setAttserialDao(AttserialDAO attserialDao) {
		this.attserialDao = attserialDao;
	}

	public List find(MyQuery myQuery) {
		return null;
	}

	public List find(String query) {
		return null;
	}

	public DutyTime get(Serializable id) {
		return null;
	}

	public List getAll() {
		return null;
	}

	public void save(DutyTime transientInstance) {

	}

	public void update(DutyTime transientInstance) {

	}

	public void delete(DutyTime persistentInstance) {

	}

	public List searchInfo(Map filter) throws Exception {
		// MyQuery myQuery = new MyQuery();

		String hql = "from DutyTime d where 1=1 ";
		hql += StringUtils.isNotEmpty((String) filter.get(CommonConfig.deptId)) ? " and d.department.id='"
				+ (String) filter.get(CommonConfig.deptId) + "' "
				: " ";
		hql += StringUtils.isNotEmpty((String) filter
				.get(CommonConfig.startDate)) ? " and d.ondutytime>='"
				+ (String) filter.get(CommonConfig.startDate) + "' " : " ";
		hql += StringUtils
				.isNotEmpty((String) filter.get(CommonConfig.endDate)) ? " and d.offdutytime<='"
				+ (String) filter.get(CommonConfig.endDate)
				+ "' and d.ondutytime<d.offdutytime "
				: " ";
		hql += " group by departmentid ,timeid ,ondutytime,offdutytime,clerkid order by d.ondutytime ";

		log.debug(hql + (String) filter.get(CommonConfig.startDate));

		return dutyTimeDao.find(hql);

	}

	public Integer getRecordCount(Map filter) throws Exception {
		MyQuery myQuery = new MyQuery();
		Integer recordCount = new Integer(0);

		String hql = "select count (*) from DutyTime d where 1=1 ";
		hql += StringUtils.isNotEmpty((String) filter.get(CommonConfig.deptId)) ? " and d.departmentid=? "
				: " ";
		hql += StringUtils.isNotEmpty((String) filter
				.get(CommonConfig.startDate)) ? " and d.ondutytime>=? " : " ";
		hql += StringUtils
				.isNotEmpty((String) filter.get(CommonConfig.endDate)) ? " and d.offdutytime<=? and d.ondutytime<d.offdutytime "
				: " ";
		hql += StringUtils.isNotEmpty((String) filter.get(CommonConfig.deptId)) ? " and d.departmentid=?  "
				: " ";

		log.debug(hql);

		if (StringUtils.isNotEmpty((String) filter.get(CommonConfig.deptId)))
			myQuery.addPara(filter.get(CommonConfig.deptId), Types.VARCHAR);
		if (StringUtils.isNotEmpty((String) filter.get(CommonConfig.startDate)))
			myQuery.addPara(filter.get(CommonConfig.startDate), Types.VARCHAR);
		if (StringUtils.isNotEmpty((String) filter.get(CommonConfig.endDate)))
			myQuery.addPara(filter.get(CommonConfig.endDate), Types.VARCHAR);

		myQuery.setQueryString(hql);

		myQuery.setOffset(true);

		List temp = dutyTimeDao.find(myQuery);
		if (temp != null)
			recordCount = (Integer) temp.get(0);
		log.debug(recordCount);
		return recordCount;
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
		boolean token = true;
		boolean resExist = false;
		String dutySingal = " <tr align='center' valign=center>";

		String title = "<td width='100' align='center'   bgcolor='#A8D1E6'>部门</td>  <td><table border='1'  cellpadding='1'"
				+ "  cellspacing='1'  bgcolor='#F6F4F5' > <tr>";
		Map resMap = new HashMap();
		String lastStr = "</table></td></tr>";

		List newFormatList = new ArrayList();

		if (StringUtils.isNotEmpty((String) filter.get(CommonConfig.deptId))) {
			if (((String) filter.get(CommonConfig.deptId)).equals("all")) {
				departList = departmentDao.getAll();
			} else {
				String dpthql = "from Department department where department.id='"
						+ (String) filter.get(CommonConfig.deptId) + "'";
				departList = departmentDao.find(dpthql);
			}
			if (!departList.isEmpty()) {
				Iterator departIte = departList.iterator();
				while (departIte.hasNext()) {
					Department department = (Department) departIte.next();
					String hql = "from Tclerkinfo c where c.deptId='"
							+ department.getId() + "'";

					clerkList = clerkDAO.find(hql);
					if (!clerkList.isEmpty()) {
						Iterator clerkIte = clerkList.iterator();

						DutyTimeVo dutyTimeVo = new DutyTimeVo();
						String preDutyStrs = "<tr><td width='100' align='center' valign='middle' bgcolor='#A8D1E6' >"
								+ department.getName()
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
							dutyInfo += "<td  width='50' align='center'  class='tdHeader1'>" + clerkName + "</td>";

							if (token) {
								title += "<td  width='50' align='center' rowspan='2' class='tdHeader1'>姓名</td>";
							}

							while (DateUtilExtend.diffDate(endDate, checkDate) <= 0) {
								StringBuffer seriSql = new StringBuffer();
								seriSql.append("from Tattserial seri where seri.cardId="
												+ sysService.getCardNo(clerk.getCustId()))
								.append(" and seri.attDate='" + checkDate + "'");
	
								List resList = attserialDao.find(seriSql.toString());
	
								if (resList.isEmpty()) {
									dutyInfo += "<td width='95' align='center'>&nbsp;&nbsp;&nbsp;</td>";
								} else {
									// add by hanjiwei20060831
									// 把取出的数据进行比较，取当天考勤时间的最大值和最小值
									String minTime = "235959";
									String maxTime = "000000";
									String currTime = "000000";
									Iterator dutyIter = resList.iterator();
									while (dutyIter.hasNext()) {
										Tattserial attS = (Tattserial) dutyIter.next();
										currTime = attS.getAttTime();
										if (DateUtilExtend.timeDiff1(maxTime,currTime) > 0) {
											maxTime = currTime;
										}
										if (DateUtilExtend.timeDiff1(minTime,currTime) < 0) {
											minTime = currTime;
										}
									}
									dutyInfo += "<td width='95' align='center'  class='tableHeader6'>"
											+ formatTime(minTime)
											+ "--"
											+ ""
											+ formatTime(maxTime)
											+ "</td>";
								}
								if (token) {
									title += "<td width='95' align='center'  class='tableHeader6'>"
											+ checkDate + "</td>";
									dutySingal += "<td align='center' valign='middle' class='tableHeader6' >上班&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;下班</td>";
								}
								checkDate = DateUtilExtend.addDate2(checkDate,1);
							}
							dutyInfo += "</tr>";
							token = false;
						}
						dutyTimeVo.setDutyTimeStr(preDutyStrs + dutyInfo + lastStr);
						log.debug(dutyTimeVo.getDutyTimeStr());
						newFormatList.add(dutyTimeVo);
					}
				}
			}
		}
		log.debug("before");

		dutySingal += "</tr>";
		title += "</tr>";
		title += dutySingal + "</table></td>";

		if (!resExist)
			title = "<td width='100' bgcolor='#A8D1E6' align='center'>没有数据<td>";

		resMap.put(CommonConfig.titleStr, title);
		resMap.put(CommonConfig.dutyStrs, newFormatList);

		return resMap;
	}
	
	private String formatTime(String inTime){
		String hour = "";
		String second = "";
		//String min = "";
		hour = inTime.substring(0,2);
		second = inTime.substring(2,4);
		//min = inTime.substring(4,6);
		return hour+":"+second;
	}

}
