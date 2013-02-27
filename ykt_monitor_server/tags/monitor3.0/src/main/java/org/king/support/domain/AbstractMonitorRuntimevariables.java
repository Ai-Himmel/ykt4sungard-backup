package org.king.support.domain;

/**
 * AbstractMonitorRuntimevariables entity provides the base persistence
 * definition of the MonitorRuntimevariables entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorRuntimevariables extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer runtimevariableId;
	private String varname;
	private String varnameZh;
	private String varvalue;

	// Constructors

	/** default constructor */
	public AbstractMonitorRuntimevariables() {
	}

	/** full constructor */
	public AbstractMonitorRuntimevariables(String varname, String varnameZh,
			String varvalue) {
		this.varname = varname;
		this.varnameZh = varnameZh;
		this.varvalue = varvalue;
	}

	// Property accessors

	public Integer getRuntimevariableId() {
		return this.runtimevariableId;
	}

	public void setRuntimevariableId(Integer runtimevariableId) {
		this.runtimevariableId = runtimevariableId;
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
				+ ((runtimevariableId == null) ? 0 : runtimevariableId
						.hashCode());
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
		if (!(obj instanceof AbstractMonitorRuntimevariables))
			return false;
		AbstractMonitorRuntimevariables other = (AbstractMonitorRuntimevariables) obj;
		if (runtimevariableId == null) {
			if (other.runtimevariableId != null)
				return false;
		} else if (!runtimevariableId.equals(other.runtimevariableId))
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
		return "AbstractMonitorRuntimevariables [runtimevariableId="
				+ runtimevariableId + ", varname=" + varname + ", varnameZh="
				+ varnameZh + ", varvalue=" + varvalue + "]";
	}
	

}