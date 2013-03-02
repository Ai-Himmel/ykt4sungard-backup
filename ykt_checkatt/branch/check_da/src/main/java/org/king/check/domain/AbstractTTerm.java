package org.king.check.domain;

/**
 * AbstractTTerm entity provides the base persistence definition of the TTerm
 * entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTTerm  implements java.io.Serializable {

	// Fields

	private String termId;
	private String termName;
	private String beginDate;
	private String endDate;
	private String creator;
	private String createDate;
	private String createTime;
	private String enable;

	// Constructors

	/** default constructor */
	public AbstractTTerm() {
	}

	/** minimal constructor */
	public AbstractTTerm(String termId) {
		this.termId = termId;
	}

	/** full constructor */
	public AbstractTTerm(String termId, String termName, String beginDate,
			String enddate, String creator, String createDate,
			String createTime, String enable) {
		this.termId = termId;
		this.termName = termName;
		this.beginDate = beginDate;
		this.endDate = enddate;
		this.creator = creator;
		this.createDate = createDate;
		this.createTime = createTime;
		this.enable = enable;
	}

	public String getTermId() {
		return termId;
	}

	public void setTermId(String termId) {
		this.termId = termId;
	}

	public String getTermName() {
		return termName;
	}

	public void setTermName(String termName) {
		this.termName = termName;
	}

	public String getBeginDate() {
		return beginDate;
	}

	public void setBeginDate(String beginDate) {
		this.beginDate = beginDate;
	}

	public String getEndDate() {
		return endDate;
	}

	public void setEndDate(String endDate) {
		this.endDate = endDate;
	}

	public String getCreator() {
		return creator;
	}

	public void setCreator(String creator) {
		this.creator = creator;
	}

	public String getCreateDate() {
		return createDate;
	}

	public void setCreateDate(String createDate) {
		this.createDate = createDate;
	}

	public String getCreateTime() {
		return createTime;
	}

	public void setCreateTime(String createTime) {
		this.createTime = createTime;
	}

	public String getEnable() {
		return enable;
	}

	public void setEnable(String enable) {
		this.enable = enable;
	}

	// Property accessors



}