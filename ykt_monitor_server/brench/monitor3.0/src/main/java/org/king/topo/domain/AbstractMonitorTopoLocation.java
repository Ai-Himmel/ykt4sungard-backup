package org.king.topo.domain;

/**
 * AbstractMonitorTopoLocation entity provides the base persistence definition
 * of the MonitorTopoLocation entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorTopoLocation extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer locationid;
	private String locationname;
	private Integer locationindex;

	// Constructors

	/** default constructor */
	public AbstractMonitorTopoLocation() {
	}

	/** full constructor */
	public AbstractMonitorTopoLocation(String locationname,
			Integer locationindex) {
		this.locationname = locationname;
		this.locationindex = locationindex;
	}

	// Property accessors

	public Integer getLocationid() {
		return this.locationid;
	}

	public void setLocationid(Integer locationid) {
		this.locationid = locationid;
	}

	public String getLocationname() {
		return this.locationname;
	}

	public void setLocationname(String locationname) {
		this.locationname = locationname;
	}

	public Integer getLocationindex() {
		return this.locationindex;
	}

	public void setLocationindex(Integer locationindex) {
		this.locationindex = locationindex;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((locationid == null) ? 0 : locationid.hashCode());
		result = prime * result
				+ ((locationindex == null) ? 0 : locationindex.hashCode());
		result = prime * result
				+ ((locationname == null) ? 0 : locationname.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (getClass() != obj.getClass())
			return false;
		AbstractMonitorTopoLocation other = (AbstractMonitorTopoLocation) obj;
		if (locationid == null) {
			if (other.locationid != null)
				return false;
		} else if (!locationid.equals(other.locationid))
			return false;
		if (locationindex == null) {
			if (other.locationindex != null)
				return false;
		} else if (!locationindex.equals(other.locationindex))
			return false;
		if (locationname == null) {
			if (other.locationname != null)
				return false;
		} else if (!locationname.equals(other.locationname))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorTopoLocation [locationid=" + locationid
				+ ", locationindex=" + locationindex + ", locationname="
				+ locationname + "]";
	}
}