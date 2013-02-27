package org.king.topo.domain;

/**
 * AbstractMonitorWorktimeRange entity provides the base persistence definition
 * of the MonitorWorktimeRange entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorWorktimeRange extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer worktimeid;
	private String formtime;
	private String totime;
	private String displaytime;
	private Boolean enable;

	// Constructors

	/** default constructor */
	public AbstractMonitorWorktimeRange() {
	}

	/** full constructor */
	public AbstractMonitorWorktimeRange(String formtime, String totime,
			String displaytime, Boolean enable) {
		this.formtime = formtime;
		this.totime = totime;
		this.displaytime = displaytime;
		this.enable = enable;
	}

	// Property accessors

	public Integer getWorktimeid() {
		return this.worktimeid;
	}

	public void setWorktimeid(Integer worktimeid) {
		this.worktimeid = worktimeid;
	}

	public String getFormtime() {
		return this.formtime;
	}

	public void setFormtime(String formtime) {
		this.formtime = formtime;
	}

	public String getTotime() {
		return this.totime;
	}

	public void setTotime(String totime) {
		this.totime = totime;
	}

	public String getDisplaytime() {
		return this.displaytime;
	}

	public void setDisplaytime(String displaytime) {
		this.displaytime = displaytime;
	}

	public Boolean getEnable() {
		return this.enable;
	}

	public void setEnable(Boolean enable) {
		this.enable = enable;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((displaytime == null) ? 0 : displaytime.hashCode());
		result = prime * result + ((enable == null) ? 0 : enable.hashCode());
		result = prime * result
				+ ((formtime == null) ? 0 : formtime.hashCode());
		result = prime * result + ((totime == null) ? 0 : totime.hashCode());
		result = prime * result
				+ ((worktimeid == null) ? 0 : worktimeid.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (getClass() != obj.getClass())
			return false;
		AbstractMonitorWorktimeRange other = (AbstractMonitorWorktimeRange) obj;
		if (displaytime == null) {
			if (other.displaytime != null)
				return false;
		} else if (!displaytime.equals(other.displaytime))
			return false;
		if (enable == null) {
			if (other.enable != null)
				return false;
		} else if (!enable.equals(other.enable))
			return false;
		if (formtime == null) {
			if (other.formtime != null)
				return false;
		} else if (!formtime.equals(other.formtime))
			return false;
		if (totime == null) {
			if (other.totime != null)
				return false;
		} else if (!totime.equals(other.totime))
			return false;
		if (worktimeid == null) {
			if (other.worktimeid != null)
				return false;
		} else if (!worktimeid.equals(other.worktimeid))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorWorktimeRange [displaytime=" + displaytime
				+ ", enable=" + enable + ", formtime=" + formtime + ", totime="
				+ totime + ", worktimeid=" + worktimeid + "]";
	}
}