package org.king.topo.domain;

/**
 * AbstractMonitorDevWorktime entity provides the base persistence definition of
 * the MonitorDevWorktime entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorDevWorktime extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer id;
	private Integer worktimeid;
	private Integer deviceid;

	// Constructors

	/** default constructor */
	public AbstractMonitorDevWorktime() {
	}

	/** full constructor */
	public AbstractMonitorDevWorktime(Integer worktimeid, Integer deviceid) {
		this.worktimeid = worktimeid;
		this.deviceid = deviceid;
	}

	// Property accessors

	public Integer getId() {
		return this.id;
	}

	public void setId(Integer id) {
		this.id = id;
	}

	public Integer getWorktimeid() {
		return this.worktimeid;
	}

	public void setWorktimeid(Integer worktimeid) {
		this.worktimeid = worktimeid;
	}

	public Integer getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(Integer deviceid) {
		this.deviceid = deviceid;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((deviceid == null) ? 0 : deviceid.hashCode());
		result = prime * result + ((id == null) ? 0 : id.hashCode());
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
		AbstractMonitorDevWorktime other = (AbstractMonitorDevWorktime) obj;
		if (deviceid == null) {
			if (other.deviceid != null)
				return false;
		} else if (!deviceid.equals(other.deviceid))
			return false;
		if (id == null) {
			if (other.id != null)
				return false;
		} else if (!id.equals(other.id))
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
		return "AbstractMonitorDevWorktime [deviceid=" + deviceid + ", id="
				+ id + ", worktimeid=" + worktimeid + "]";
	}
}