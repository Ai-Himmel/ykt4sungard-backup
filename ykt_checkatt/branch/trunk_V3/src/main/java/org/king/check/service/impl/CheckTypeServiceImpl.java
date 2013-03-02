package org.king.check.service.impl;

import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.king.check.dao.CheckTypeDAO;
import org.king.check.domain.TChecktype;
import org.king.check.service.CheckTypeService;
import org.springframework.jdbc.core.JdbcTemplate;

public class CheckTypeServiceImpl implements CheckTypeService {
	// private static final Log log =
	// LogFactory.getLog(WorkConfServiceImpl.class);

	private JdbcTemplate jdbcTemplate;
	
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}
	private CheckTypeDAO checktypeDAO;

	public void setCheckTypeDAO(CheckTypeDAO checktypeDAO) {
		this.checktypeDAO = checktypeDAO;
	}

	public void saveCheckType(TChecktype checkType) {
		checktypeDAO.save(checkType);
	}

	public void updateCheckType(TChecktype checkType) {
		checktypeDAO.update(checkType);
	}

	public void deleteCheckType(String confId) {
		checktypeDAO.delete(getCheckType(confId));
	}

	public TChecktype getCheckType(String workConfId) {
		TChecktype workconf = checktypeDAO.get(workConfId);

		return workconf;
	}
	
	public List getAll() {
		return checktypeDAO.getAll();
	}

	public List search(Map filter) throws Exception {
		String hql = "from TChecktype checktype where 1=1";
		hql += StringUtils.isNotEmpty((String) filter.get("typeName")) ? " and checktype.typeName like '%"
				+ (String) filter.get("typeName") + "%' "
				: "";
		List res = checktypeDAO.find(hql);
		return res;
	}
	
	public List getUsedCheckType(String workTimes) throws Exception{
		StringBuffer tempTimes = new StringBuffer(128);
		tempTimes.append("select check_typeid,begindate,worktime_id from ykt_ck.t_check_workconfinfo")
		.append(" where check_typeid in (").append(workTimes).append(")");
		List retu = jdbcTemplate.queryForList(tempTimes.toString());
		return retu;
	}


}
