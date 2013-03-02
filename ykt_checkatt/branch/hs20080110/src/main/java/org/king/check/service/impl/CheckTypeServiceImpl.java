package org.king.check.service.impl;

import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.king.check.dao.CheckTypeDAO;
import org.king.check.domain.TChecktype;
import org.king.check.service.CheckTypeService;

public class CheckTypeServiceImpl implements CheckTypeService {
	// private static final Log log =
	// LogFactory.getLog(WorkConfServiceImpl.class);

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

}
