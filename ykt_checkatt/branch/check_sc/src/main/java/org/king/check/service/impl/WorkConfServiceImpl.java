package org.king.check.service.impl;

import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.king.check.dao.WorkConfDao;
import org.king.check.domain.Tworkconfinfo;
import org.king.check.service.WorkConfService;
import org.springframework.jdbc.core.JdbcTemplate;

public class WorkConfServiceImpl implements WorkConfService {
	// private static final Log log =
	// LogFactory.getLog(WorkConfServiceImpl.class);

	private JdbcTemplate jdbcTemplate;
	
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}
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
		confInfo.append("上班提前打卡不允许超过:" + workConf.getOverTime() + "分钟  ")
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
	
	public List getUsedWorkConf(String workTimes) throws Exception{
		StringBuffer tempTimes = new StringBuffer(128);
		tempTimes.append("select check_typeid,begindate,worktime_id from ykt_ck.t_check_workconfinfo")
		.append(" where workinfo_id in (").append(workTimes).append(")");
		List retu = jdbcTemplate.queryForList(tempTimes.toString());
		return retu;
	}


}
