package org.king.topo.domain;

/**
 * AbstractMonitorTopoGroup entity provides the base persistence definition of
 * the MonitorTopoGroup entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorTopoGroup extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer devicegroupid;
	private String devicegroupname;
	private Integer groupxindex;
	private Integer groupyindex;
	private Integer groupwidth;
	private Integer groupheight;
    private MonitorTopoLocation location = new MonitorTopoLocation();

	// Constructors

	/** default constructor */
	public AbstractMonitorTopoGroup() {
	}

    protected AbstractMonitorTopoGroup(Integer devicegroupid, String devicegroupname, Integer groupxindex, Integer groupyindex, Integer groupwidth, Integer groupheight, MonitorTopoLocation location) {
        this.devicegroupid = devicegroupid;
        this.devicegroupname = devicegroupname;
        this.groupxindex = groupxindex;
        this.groupyindex = groupyindex;
        this.groupwidth = groupwidth;
        this.groupheight = groupheight;
        this.location = location;
    }

    /** full constructor */


	// Property accessors

	public Integer getDevicegroupid() {
		return this.devicegroupid;
	}

	public void setDevicegroupid(Integer devicegroupid) {
		this.devicegroupid = devicegroupid;
	}

	public String getDevicegroupname() {
		return this.devicegroupname;
	}

	public void setDevicegroupname(String devicegroupname) {
		this.devicegroupname = devicegroupname;
	}

	public Integer getGroupxindex() {
		return this.groupxindex;
	}

	public void setGroupxindex(Integer groupxindex) {
		this.groupxindex = groupxindex;
	}

	public Integer getGroupyindex() {
		return this.groupyindex;
	}

	public void setGroupyindex(Integer groupyindex) {
		this.groupyindex = groupyindex;
	}

	public Integer getGroupwidth() {
		return this.groupwidth;
	}

	public void setGroupwidth(Integer groupwidth) {
		this.groupwidth = groupwidth;
	}

	public Integer getGroupheight() {
		return this.groupheight;
	}

	public void setGroupheight(Integer groupheight) {
		this.groupheight = groupheight;
	}

    public MonitorTopoLocation getLocation() {
        return location;
    }

    public void setLocation(MonitorTopoLocation location) {
        this.location = location;
    }

    @Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((devicegroupid == null) ? 0 : devicegroupid.hashCode());
		result = prime * result
				+ ((devicegroupname == null) ? 0 : devicegroupname.hashCode());
		result = prime * result
				+ ((groupheight == null) ? 0 : groupheight.hashCode());
		result = prime * result
				+ ((location == null) ? 0 : location.hashCode());
		result = prime * result
				+ ((groupwidth == null) ? 0 : groupwidth.hashCode());
		result = prime * result
				+ ((groupxindex == null) ? 0 : groupxindex.hashCode());
		result = prime * result
				+ ((groupyindex == null) ? 0 : groupyindex.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (getClass() != obj.getClass())
			return false;
		AbstractMonitorTopoGroup other = (AbstractMonitorTopoGroup) obj;
		if (devicegroupid == null) {
			if (other.devicegroupid != null)
				return false;
		} else if (!devicegroupid.equals(other.devicegroupid))
			return false;
		if (devicegroupname == null) {
			if (other.devicegroupname != null)
				return false;
		} else if (!devicegroupname.equals(other.devicegroupname))
			return false;
		if (groupheight == null) {
			if (other.groupheight != null)
				return false;
		} else if (!groupheight.equals(other.groupheight))
			return false;
		if (location == null) {
			if (other.location != null)
				return false;
		} else if (!location.equals(other.location))
			return false;
		if (groupwidth == null) {
			if (other.groupwidth != null)
				return false;
		} else if (!groupwidth.equals(other.groupwidth))
			return false;
		if (groupxindex == null) {
			if (other.groupxindex != null)
				return false;
		} else if (!groupxindex.equals(other.groupxindex))
			return false;
		if (groupyindex == null) {
			if (other.groupyindex != null)
				return false;
		} else if (!groupyindex.equals(other.groupyindex))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorTopoGroup [devicegroupid=" + devicegroupid
				+ ", devicegroupname=" + devicegroupname + ", groupheight="
				+ groupheight + ", location=" + location
				+ ", groupwidth=" + groupwidth + ", groupxindex=" + groupxindex
				+ ", groupyindex=" + groupyindex + "]";
	}
}