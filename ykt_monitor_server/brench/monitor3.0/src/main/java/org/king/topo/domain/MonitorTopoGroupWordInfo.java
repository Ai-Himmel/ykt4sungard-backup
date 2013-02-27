package org.king.topo.domain;

/**
 * AbstractMonitorTopoDevgroupInfo entity provides the base persistence
 * definition of the MonitorTopoDevgroupInfo entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class MonitorTopoGroupWordInfo extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	private Integer devicegroupid;
	private Integer devphytype;
	private String devtypecode;
	private String devtypename;
	private Integer errornum;
	private Integer totalnum;
	private Integer status = 0;
	
	
	public MonitorTopoGroupWordInfo() {
		super();
	}

	public MonitorTopoGroupWordInfo(Integer devicegroupid, Integer devphytype,
			String devtypecode, String devtypename, Integer errornum,
			Integer totalnum, Integer status) {
		super();
		this.devicegroupid = devicegroupid;
		this.devphytype = devphytype;
		this.devtypecode = devtypecode;
		this.devtypename = devtypename;
		this.errornum = errornum;
		this.totalnum = totalnum;
		this.status = status;
	}
	
	public Integer getDevicegroupid() {
		return devicegroupid;
	}
	public void setDevicegroupid(Integer devicegroupid) {
		this.devicegroupid = devicegroupid;
	}
	public Integer getDevphytype() {
		return devphytype;
	}
	public void setDevphytype(Integer devphytype) {
		this.devphytype = devphytype;
	}
	public String getDevtypecode() {
		return devtypecode;
	}
	public void setDevtypecode(String devtypecode) {
		this.devtypecode = devtypecode;
	}
	public String getDevtypename() {
		return devtypename;
	}
	public void setDevtypename(String devtypename) {
		this.devtypename = devtypename;
	}
	public Integer getErrornum() {
		return errornum;
	}
	public void setErrornum(Integer errornum) {
		this.errornum = errornum;
	}
	public Integer getTotalnum() {
		return totalnum;
	}
	public void setTotalnum(Integer totalnum) {
		this.totalnum = totalnum;
	}
	public Integer getStatus() {
		return status;
	}
	public void setStatus(Integer status) {
		this.status = status;
	}

	@Override
	public String toString() {
		return "MonitorTopoGroupWordInfo [devicegroupid=" + devicegroupid
				+ ", devphytype=" + devphytype + ", devtypecode=" + devtypecode
				+ ", devtypename=" + devtypename + ", errornum=" + errornum
				+ ", status=" + status + ", totalnum=" + totalnum + "]";
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
				+ ((devtypename == null) ? 0 : devtypename.hashCode());
		result = prime * result
				+ ((errornum == null) ? 0 : errornum.hashCode());
		result = prime * result + ((status == null) ? 0 : status.hashCode());
		result = prime * result
				+ ((totalnum == null) ? 0 : totalnum.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof MonitorTopoGroupWordInfo))
			return false;
		MonitorTopoGroupWordInfo other = (MonitorTopoGroupWordInfo) obj;
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
		if (devtypename == null) {
			if (other.devtypename != null)
				return false;
		} else if (!devtypename.equals(other.devtypename))
			return false;
		if (errornum == null) {
			if (other.errornum != null)
				return false;
		} else if (!errornum.equals(other.errornum))
			return false;
		if (status == null) {
			if (other.status != null)
				return false;
		} else if (!status.equals(other.status))
			return false;
		if (totalnum == null) {
			if (other.totalnum != null)
				return false;
		} else if (!totalnum.equals(other.totalnum))
			return false;
		return true;
	}


}