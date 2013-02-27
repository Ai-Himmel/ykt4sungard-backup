package com.kingstargroup.form;

import java.util.Date;

/**
 * AbstractMonitors entity provides the base persistence definition of the
 * Monitors entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitors implements java.io.Serializable {

	// Fields

	private MonitorsId id;
	private String valuestr;
	 private Date modified;

	// Constructors

	/** default constructor */
	public AbstractMonitors() {
	}

	/** minimal constructor */
	public AbstractMonitors(MonitorsId id, Date modified) {
		this.id = id;
		this.modified = modified;
	}

	/** full constructor */
	public AbstractMonitors(MonitorsId id, String valuestr, Date modified) {
		this.id = id;
		this.valuestr = valuestr;
		this.modified = modified;
	}

	// Property accessors

	public MonitorsId getId() {
		return this.id;
	}

	public void setId(MonitorsId id) {
		this.id = id;
	}

	public String getValuestr() {
		return this.valuestr;
	}

	public void setValuestr(String valuestr) {
		this.valuestr = valuestr;
	}

	public Date getModified() {
		return this.modified;
	}

	public void setModified(Date modified) {
		this.modified = modified;
	}

}