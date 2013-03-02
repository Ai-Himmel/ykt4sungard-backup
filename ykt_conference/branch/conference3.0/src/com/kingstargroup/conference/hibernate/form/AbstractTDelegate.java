package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTDelegate entity provides the base persistence definition of the
 * TDelegate entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDelegate implements java.io.Serializable {

	// Fields

	private long dlgtId;
	private String dlgtName;
	private String deptId;
	private String open;
	private String operId;
	private String comment;

	// Constructors

	/** default constructor */
	public AbstractTDelegate() {
	}

	/** minimal constructor */
	public AbstractTDelegate(String operId) {
		this.operId = operId;
	}

	/** full constructor */
	public AbstractTDelegate(String dlgtName, String deptId, String open,
			String operId, String comment) {
		this.dlgtName = dlgtName;
		this.deptId = deptId;
		this.open = open;
		this.operId = operId;
		this.comment = comment;
	}

	// Property accessors

	public long getDlgtId() {
		return this.dlgtId;
	}

	public void setDlgtId(long dlgtId) {
		this.dlgtId = dlgtId;
	}

	public String getDlgtName() {
		return this.dlgtName;
	}

	public void setDlgtName(String dlgtName) {
		this.dlgtName = dlgtName;
	}

	public String getDeptId() {
		return this.deptId;
	}

	public void setDeptId(String deptId) {
		this.deptId = deptId;
	}

	public String getOpen() {
		return this.open;
	}

	public void setOpen(String open) {
		this.open = open;
	}

	public String getOperId() {
		return this.operId;
	}

	public void setOperId(String operId) {
		this.operId = operId;
	}

	public String getComment() {
		return this.comment;
	}

	public void setComment(String comment) {
		this.comment = comment;
	}

}