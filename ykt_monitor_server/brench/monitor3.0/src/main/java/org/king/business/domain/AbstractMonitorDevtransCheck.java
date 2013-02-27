package org.king.business.domain;

/**
 * AbstractMonitorDevtransCheck entity provides the base persistence definition
 * of the MonitorDevtransCheck entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorDevtransCheck extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer deviceid;
	private Integer worktimeid;
	private String checkpoint;
	private String lasttransdate;
	private String lasttranstime;

	// Constructors

	/** default constructor */
	public AbstractMonitorDevtransCheck() {
	}

	/** full constructor */
	public AbstractMonitorDevtransCheck(Integer worktimeid,
			String checkpoint, String lasttransdate, String lasttranstime) {
		this.worktimeid = worktimeid;
		this.checkpoint = checkpoint;
		this.lasttransdate = lasttransdate;
		this.lasttranstime = lasttranstime;
	}

	// Property accessors

	public Integer getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(Integer deviceid) {
		this.deviceid = deviceid;
	}

	public Integer getWorktimeid() {
		return this.worktimeid;
	}

	public void setWorktimeid(Integer worktimeid) {
		this.worktimeid = worktimeid;
	}

	public String getCheckpoint() {
		return this.checkpoint;
	}

	public void setCheckpoint(String checkpoint) {
		this.checkpoint = checkpoint;
	}

	public String getLasttransdate() {
		return this.lasttransdate;
	}

	public void setLasttransdate(String lasttransdate) {
		this.lasttransdate = lasttransdate;
	}

	public String getLasttranstime() {
		return this.lasttranstime;
	}

	public void setLasttranstime(String lasttranstime) {
		this.lasttranstime = lasttranstime;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((checkpoint == null) ? 0 : checkpoint.hashCode());
		result = prime * result
				+ ((deviceid == null) ? 0 : deviceid.hashCode());
		result = prime * result
				+ ((lasttransdate == null) ? 0 : lasttransdate.hashCode());
		result = prime * result
				+ ((lasttranstime == null) ? 0 : lasttranstime.hashCode());
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
		AbstractMonitorDevtransCheck other = (AbstractMonitorDevtransCheck) obj;
		if (checkpoint == null) {
			if (other.checkpoint != null)
				return false;
		} else if (!checkpoint.equals(other.checkpoint))
			return false;
		if (deviceid == null) {
			if (other.deviceid != null)
				return false;
		} else if (!deviceid.equals(other.deviceid))
			return false;
		if (lasttransdate == null) {
			if (other.lasttransdate != null)
				return false;
		} else if (!lasttransdate.equals(other.lasttransdate))
			return false;
		if (lasttranstime == null) {
			if (other.lasttranstime != null)
				return false;
		} else if (!lasttranstime.equals(other.lasttranstime))
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
		return "AbstractMonitorDevtransCheck [checkpoint=" + checkpoint
				+ ", deviceid=" + deviceid + ", lasttransdate=" + lasttransdate
				+ ", lasttranstime=" + lasttranstime + ", worktimeid="
				+ worktimeid + "]";
	}
}