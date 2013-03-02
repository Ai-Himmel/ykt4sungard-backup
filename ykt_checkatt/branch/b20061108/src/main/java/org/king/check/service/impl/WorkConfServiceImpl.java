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
	 * ȡ�ÿ����ƶ���ϸ��Ϣ
	 * hanjiwei add it 20061009
	 */
	public String getWorkConfInfo(String workConfId) {
		Tworkconfinfo workConf = workconfDAO.get(workConfId);
		StringBuffer confInfo = new StringBuffer(1024);
		confInfo.append("��������:"+workConf.getLeaveearlyTime()+"����  ")
		.append("����ٵ�:" + workConf.getOverdueTime() + "����  ")
		.append("�ϰ���ǰ�򿨲�������:" + workConf.getOverTime() + "����  ")
		.append("�°�������ͺ�:" + workConf.getDelayTime()+ "����");
		
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
