package org.king.check.service.impl;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.king.check.dao.WorkTimeConfDao;
import org.king.check.domain.Tworktimeinfo;
import org.king.check.service.WorkTimeConfService;
import org.king.check.util.StringUtil;

public class WorkTimeConfImpl implements WorkTimeConfService {
	// private static final Log log = LogFactory.getLog(WorkTimeConfImpl.class);

	private WorkTimeConfDao worktimeconfDAO;

	public void setWorktimeconfDAO(WorkTimeConfDao worktimeconfDAO) {
		this.worktimeconfDAO = worktimeconfDAO;
	}

	public void saveWorkTimeConf(Tworktimeinfo workTimeConf) {
		worktimeconfDAO.save(workTimeConf);
	}

	public void updateWorkTimeConf(Tworktimeinfo workTimeConf) {
		worktimeconfDAO.update(workTimeConf);
	}

	public void deleteWorkTimeConf(String workTimeConfId) {
		worktimeconfDAO.delete(getWorkTimeConf(workTimeConfId));
	}

	public Tworktimeinfo getWorkTimeConf(String workTimeConfId) {
		Tworktimeinfo worktimeconf = worktimeconfDAO.get(workTimeConfId);
		return worktimeconf;
	}

	/*
	 * 取得考勤时间详细信息 hanjiwei add it 20061009
	 */
	public String getWorkTimeInfo(String workTimeId) {
		Tworktimeinfo workTimeConf = worktimeconfDAO.get(workTimeId);
		StringBuffer workTimeInfo = new StringBuffer(1024);
		if ((null!=workTimeConf.getOntime1())&&(!"".equals(workTimeConf.getOntime1()))){
			workTimeInfo.append("上班时间1["+StringUtil.formatTime(workTimeConf.getOntime1())+"]  ")
			.append("下班时间1["+StringUtil.formatTime(workTimeConf.getOfftime1())+"]  ");
			
		}
		if ((null!=workTimeConf.getOntime2())&&(!"".equals(workTimeConf.getOntime2()))){
			workTimeInfo.append("上班时间2["+StringUtil.formatTime(workTimeConf.getOntime2())+"]  ")
			.append("下班时间2["+StringUtil.formatTime(workTimeConf.getOfftime2())+"]  ");
			
		}
		if ((null!=workTimeConf.getOntime3())&&(!"".equals(workTimeConf.getOntime3()))){
			workTimeInfo.append("上班时间3["+StringUtil.formatTime(workTimeConf.getOntime3())+"]  ")
			.append("下班时间3["+StringUtil.formatTime(workTimeConf.getOfftime3())+"]  ");
			
		}
		if ((null!=workTimeConf.getOntime4())&&(!"".equals(workTimeConf.getOntime4()))){
			workTimeInfo.append("上班时间4["+StringUtil.formatTime(workTimeConf.getOntime4())+"]  ")
			.append("下班时间4["+StringUtil.formatTime(workTimeConf.getOfftime4())+"]  ");
			
		}
		return workTimeInfo.toString();
	}

	public List getAll() {
		return worktimeconfDAO.getAll();
	}

	public List getWorkTimeConfParasByWorkTimeConfName(String workTimeConfName) {
		return null;
	}

	public List getWorkTimeConfParasByWorkTimeConfId(String workTimeConfId) {
		return null;
	}

	public List search(Map filter) throws Exception {
		String hql = "from Tworktimeinfo worktimeconf where 1=1";
		hql += StringUtils.isNotEmpty((String) filter.get("workTimeName")) ? " and worktimeconf.worktimeName like '%"
				+ (String) filter.get("workTimeName") + "%' "
				: "";
		List res = worktimeconfDAO.find(hql);
		return res;
	}

	/**
	 * hanjiwei modify it 20061206
	 * 格式话时间显示
	 */
	public List reForMatWorkTimeList(List workTimeList) throws Exception {
		
		List newWorkTimeList = new ArrayList();

		Iterator workTimeIte = workTimeList.iterator();

		while (workTimeIte.hasNext()) {
			Tworktimeinfo worktimeconf = (Tworktimeinfo) workTimeIte.next();
			String temp = worktimeconf.getOntime1();
			if (StringUtils.isNotEmpty(temp))
				worktimeconf.setOntime1(temp.substring(0, 2) + ":"
						+ temp.substring(2));

			temp = worktimeconf.getOntime2();
			if (StringUtils.isNotEmpty(temp))
				worktimeconf.setOntime2(temp.substring(0, 2) + ":"
						+ temp.substring(2));

			temp = worktimeconf.getOntime3();
			if (StringUtils.isNotEmpty(temp))
				worktimeconf.setOntime3(temp.substring(0, 2) + ":"
						+ temp.substring(2));

			temp = worktimeconf.getOntime4();
			if (StringUtils.isNotEmpty(temp))
				worktimeconf.setOntime4(temp.substring(0, 2) + ":"
						+ temp.substring(2));

			temp = worktimeconf.getOfftime1();
			if (StringUtils.isNotEmpty(temp))
				worktimeconf.setOfftime1(temp.substring(0, 2) + ":"
						+ temp.substring(2));

			temp = worktimeconf.getOfftime2();
			if (StringUtils.isNotEmpty(temp))
				worktimeconf.setOfftime2(temp.substring(0, 2) + ":"
						+ temp.substring(2));

			temp = worktimeconf.getOfftime3();
			if (StringUtils.isNotEmpty(temp))
				worktimeconf.setOfftime3(temp.substring(0, 2) + ":"
						+ temp.substring(2));

			temp = worktimeconf.getOfftime4();
			if (StringUtils.isNotEmpty(temp))
				worktimeconf.setOfftime1(temp.substring(0, 2) + ":"
						+ temp.substring(2));

			newWorkTimeList.add(worktimeconf);
		}

		return newWorkTimeList;
		
		//return null;
	}

}
