package org.king.check.service.impl;

import java.util.List;

import org.apache.commons.lang.StringUtils;
import org.king.check.dao.TermDAO;
import org.king.check.domain.TTerm;
import org.king.check.service.TermService;

public class TermServiceImpl implements TermService {

	private TermDAO termDAO;

	public void setTermDAO(TermDAO termDAO) {
		this.termDAO = termDAO;
	}

	public TTerm findTermByName(String termName) {
		StringBuffer query = new StringBuffer(
				" from TTerm t where t.enable='1' ");
		if (StringUtils.isNotEmpty(termName)) {
			query = query.append(" and t.termName ='").append(termName).append(
					"'");
		}
		List list = termDAO.find(query.toString());
		if (list != null && !list.isEmpty()) {
			TTerm term = (TTerm) list.get(0);
			return term;
		}
		return null;
	}

	public List findTerm(String termName) {
		StringBuffer query = new StringBuffer(
				"select new Map(t.termId as termId ,t.termName as termName ")
				.append(" ,t.beginDate  as beginDate ,t.endDate as endDate )from TTerm t where t.enable='1' ");
		if (StringUtils.isNotEmpty(termName)) {
			query = query.append(" and t.termName like '%").append(termName)
					.append("%'");
		}
		query = query
				.append(" order by t.createDate desc , t.createTime  desc");
		return termDAO.find(query.toString());
	}

	public List findAllTerm() {
		StringBuffer query = new StringBuffer(
				"select new Map(t.termId as termId ,t.termName as termName ")
				.append(" ,t.beginDate  as beginDate ,t.endDate as endDate )from TTerm t where t.enable='1' ");

		query = query.append(" order by t.beginDate desc");
		return termDAO.find(query.toString());
	}

	public void saveTerm(TTerm term) {
		termDAO.save(term);
	}

	public TTerm getTerm(String id) {
		return (TTerm) termDAO.get(id);
	}

	public void delteTerm(String id) {
		TTerm term = getTerm(id);
		term.setEnable("0");
		termDAO.save(term);
	}

	public void updateTerm(TTerm term) {
		termDAO.update(term);
	}

}
