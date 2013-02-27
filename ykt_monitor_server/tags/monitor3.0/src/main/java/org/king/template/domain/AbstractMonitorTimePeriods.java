package org.king.template.domain;

import java.util.Set;

/**
 * AbstractMonitorTimePeriods entity provides the base persistence definition of
 * the MonitorTimePeriods entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorTimePeriods extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer timeperiodId;
	private String alias;
    private Set timerangers;

	// Constructors

	/** default constructor */
	public AbstractMonitorTimePeriods() {
	}

	/** full constructor */
	public AbstractMonitorTimePeriods(String alias) {
		this.alias = alias;
	}

	// Property accessors

	public Integer getTimeperiodId() {
		return this.timeperiodId;
	}

	public void setTimeperiodId(Integer timeperiodId) {
		this.timeperiodId = timeperiodId;
	}

	public String getAlias() {
		return this.alias;
	}

	public void setAlias(String alias) {
		this.alias = alias;
	}

    public Set getTimerangers() {
        return timerangers;
    }

    public void setTimerangers(Set timerangers) {
        this.timerangers = timerangers;
    }

    @Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result + ((alias == null) ? 0 : alias.hashCode());
		result = prime * result
				+ ((timeperiodId == null) ? 0 : timeperiodId.hashCode());
		return result;
	}

	@Override
	public String toString() {
		return "AbstractMonitorTimePeriods [alias=" + alias + ", timeperiodId="
				+ timeperiodId + "]";
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorTimePeriods))
			return false;
		AbstractMonitorTimePeriods other = (AbstractMonitorTimePeriods) obj;
		if (alias == null) {
			if (other.alias != null)
				return false;
		} else if (!alias.equals(other.alias))
			return false;
		if (timeperiodId == null) {
			if (other.timeperiodId != null)
				return false;
		} else if (!timeperiodId.equals(other.timeperiodId))
			return false;
		return true;
	}

}