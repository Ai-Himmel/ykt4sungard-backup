package org.king.check.domain;

/**
 * TTerm entity. @author MyEclipse Persistence Tools
 */
public class TTerm extends AbstractTTerm  {

	// Constructors

	/** default constructor */
	public TTerm() {
	}

	/** minimal constructor */
	public TTerm(String termId) {
		super(termId);
	}

	/** full constructor */
	public TTerm(String termId, String termName, String beginDate,
			String endDate, String creator, String createDate,
			String createTime, String enable) {
		super(termId, termName, beginDate, endDate, creator, createDate,
				createTime, enable);
	}

}
