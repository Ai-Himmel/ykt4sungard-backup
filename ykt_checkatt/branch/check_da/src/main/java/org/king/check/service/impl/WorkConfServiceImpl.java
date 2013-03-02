package org.king.check.service.impl;

import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.king.check.dao.WorkConfDao;
import org.king.check.domain.Tworkconfinfo;
import org.king.check.service.WorkConfService;

public class WorkConfServiceImpl implements WorkConfService {
	// private static final Log log =
	// LogFactory.getLog(WorkConfServiceImpl.class);

	private WorkConfDao workconfDAO;

	public void setWorkconfDAO(WorkConfDao workconfDAO) {
		this.workconfDAO = workconfDAO;
	}

	public void saveWorkConf(Tworkconfinfo workConf) {
		workconfDAO.save(workConf);
	}

	public void updateWorkConf(Tworkconfinfo workConf) {
		workconfDAO.update(workConf);
	}

	public void deleteWorkConf(String confId) {
		workconfDAO.delete(getWorkConf(confId));
	}

	public Tworkconfinfo getWorkConf(String workConfId) {
		Tworkconfinfo workconf = workconfDAO.get(workConfId);

		return workconf;
	}

	/*
	 * 取得考勤制度详细信息
	 * hanjiwei add it 20061009
	 */
	public String getWorkConfInfo(String workConfId) {
		Tworkconfinfo workConf = workconfDAO.get(workConfId);
		StringBuffer confInfo = new StringBuffer(1024);
		confInfo.append("允许早退:"+workConf.getLeaveearlyTime()+"分钟  ")
		.append("允许迟到:" + workConf.getOverdueTime() + "分钟  ")
		.append("上班提前打卡不允许超过:" + workConf.getOverTime() + "分钟  ")
		.append("下班打卡允许滞后:" + workConf.getDelayTime()+ "分钟");
		
		return confInfo.toString();
	}
	
	public List getAll() {
		return workconfDAO.getAll();
	}

	public List search(Map filter) throws Exception {
		String hql = "from Tworkconfinfo workconf where 1=1";
		hql += StringUtils.isNotEmpty((String) filter.get("workConfName")) ? " and workconf.workconfName like '%"
				+ (String) filter.get("workConfName") + "%' "
				: "";
		List res = workconfDAO.find(hql);
		return res;
	}

}
