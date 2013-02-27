package org.king.support.domain;

import java.math.BigDecimal;

/**
 * AbstractMonitorConfigvariables entity provides the base persistence
 * definition of the MonitorConfigvariables entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorConfigvariables extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private BigDecimal configvariableId;
	private String varname;
	private String varnameZh;
	private String varvalue;

	// Constructors

	/** default constructor */
	public AbstractMonitorConfigvariables() {
	}

	/** full constructor */
	public AbstractMonitorConfigvariables(String varname, String varnameZh,
			String varvalue) {
		this.varname = varname;
		this.varnameZh = varnameZh;
		this.varvalue = varvalue;
	}

	// Property accessors

	public BigDecimal getConfigvariableId() {
		return this.configvariableId;
	}

	public void setConfigvariableId(BigDecimal configvariableId) {
		this.configvariableId = configvariableId;
	}

	public String getVarname() {
		return this.varname;
	}

	public void setVarname(String varname) {
		this.varname = varname;
	}

	public String getVarnameZh() {
		return this.varnameZh;
	}

	public void setVarnameZh(String varnameZh) {
		this.varnameZh = varnameZh;
	}

	public String getVarvalue() {
		return this.varvalue;
	}

	public void setVarvalue(String varvalue) {
		this.varvalue = varvalue;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime
				* result
				+ ((configvariableId == null) ? 0 : configvariableId.hashCode());
		result = prime * result + ((varname == null) ? 0 : varname.hashCode());
		result = prime * result
				+ ((varnameZh == null) ? 0 : varnameZh.hashCode());
		result = prime * result
				+ ((varvalue == null) ? 0 : varvalue.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorConfigvariables))
			return false;
		AbstractMonitorConfigvariables other = (AbstractMonitorConfigvariables) obj;
		if (configvariableId == null) {
			if (other.configvariableId != null)
				return false;
		} else if (!configvariableId.equals(other.configvariableId))
			return false;
		if (varname == null) {
			if (other.varname != null)
				return false;
		} else if (!varname.equals(other.varname))
			return false;
		if (varnameZh == null) {
			if (other.varnameZh != null)
				return false;
		} else if (!varnameZh.equals(other.varnameZh))
			return false;
		if (varvalue == null) {
			if (other.varvalue != null)
				return false;
		} else if (!varvalue.equals(other.varvalue))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorConfigvariables [configvariableId="
				+ configvariableId + ", varname=" + varname + ", varnameZh="
				+ varnameZh + ", varvalue=" + varvalue + "]";
	}

}