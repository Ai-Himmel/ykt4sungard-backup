package org.king.topo.domain;

/**
 * AbstractMonitorTopoDevgroupInfo entity provides the base persistence
 * definition of the MonitorTopoDevgroupInfo entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorTopoDevgroupInfo extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer id;
	private Integer devicegroupid;
	private Integer devphytype;
	private String devtypecode;
	private Integer devtypenum;
	private String lastupdate;

	// Constructors

	/** default constructor */
	public AbstractMonitorTopoDevgroupInfo() {
	}

	/** full constructor */
	public AbstractMonitorTopoDevgroupInfo(Integer devicegroupid,
			Integer devphytype, String devtypecode,Integer devtypenum,String lastupdate) {
		this.devicegroupid = devicegroupid;
		this.devphytype = devphytype;
		this.devtypecode = devtypecode;
		this.devtypenum = devtypenum;
		this.lastupdate = lastupdate;
	}

	// Property accessors

	public Integer getId() {
		return this.id;
	}

	public void setId(Integer id) {
		this.id = id;
	}

	public Integer getDevicegroupid() {
		return this.devicegroupid;
	}

	public void setDevicegroupid(Integer devicegroupid) {
		this.devicegroupid = devicegroupid;
	}

	public Integer getDevphytype() {
		return this.devphytype;
	}

	public void setDevphytype(Integer devphytype) {
		this.devphytype = devphytype;
	}

	public String getDevtypecode() {
		return this.devtypecode;
	}

	public void setDevtypecode(String devtypecode) {
		this.devtypecode = devtypecode;
	}

	public Integer getDevtypenum() {
		return devtypenum;
	}

	public void setDevtypenum(Integer devtypenum) {
		this.devtypenum = devtypenum;
	}
	

	public String getLastupdate() {
		return lastupdate;
	}

	public void setLastupdate(String lastupdate) {
		this.lastupdate = lastupdate;
	}

	@Override
	public String toString() {
		return "AbstractMonitorTopoDevgroupInfo [devicegroupid="
				+ devicegroupid + ", devphytype=" + devphytype
				+ ", devtypecode=" + devtypecode + ", devtypenum=" + devtypenum
				+ ", id=" + id + ", lastupdate=" + lastupdate + "]";
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((devicegroupid == null) ? 0 : devicegroupid.hashCode());
		result = prime * result
				+ ((devphytype == null) ? 0 : devphytype.hashCode());
		result = prime * result
				+ ((devtypecode == null) ? 0 : devtypecode.hashCode());
		result = prime * result
				+ ((devtypenum == null) ? 0 : devtypenum.hashCode());
		result = prime * result + ((id == null) ? 0 : id.hashCode());
		result = prime * result
				+ ((lastupdate == null) ? 0 : lastupdate.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorTopoDevgroupInfo))
			return false;
		AbstractMonitorTopoDevgroupInfo other = (AbstractMonitorTopoDevgroupInfo) obj;
		if (devicegroupid == null) {
			if (other.devicegroupid != null)
				return false;
		} else if (!devicegroupid.equals(other.devicegroupid))
			return false;
		if (devphytype == null) {
			if (other.devphytype != null)
				return false;
		} else if (!devphytype.equals(other.devphytype))
			return false;
		if (devtypecode == null) {
			if (other.devtypecode != null)
				return false;
		} else if (!devtypecode.equals(other.devtypecode))
			return false;
		if (devtypenum == null) {
			if (other.devtypenum != null)
				return false;
		} else if (!devtypenum.equals(other.devtypenum))
			return false;
		if (id == null) {
			if (other.id != null)
				return false;
		} else if (!id.equals(other.id))
			return false;
		if (lastupdate == null) {
			if (other.lastupdate != null)
				return false;
		} else if (!lastupdate.equals(other.lastupdate))
			return false;
		return true;
	}


}