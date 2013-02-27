package org.king.topo.domain;

import java.math.BigDecimal;
import java.sql.Clob;

/**
 * AbstractmonitorTopoGroupInfo entity provides the base persistence definition
 * of the monitorTopoGroupInfo entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorTopoGroupInfo extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer devicegroupid;
	private Integer groupwidth;
	private Integer groupheight;
	private String groupvml;
	private String lastupdate;

	// Constructors

	/** default constructor */
	public AbstractMonitorTopoGroupInfo() {
	}

	/** minimal constructor */
	public AbstractMonitorTopoGroupInfo(Integer devicegroupid) {
		this.devicegroupid = devicegroupid;
	}

	/** full constructor */
	public AbstractMonitorTopoGroupInfo(Integer devicegroupid,
			Integer groupwidth, Integer groupheight, String groupvml,
			String lastupdate) {
		this.devicegroupid = devicegroupid;
		this.groupwidth = groupwidth;
		this.groupheight = groupheight;
		this.groupvml = groupvml;
		this.lastupdate = lastupdate;
	}

	// Property accessors

	public Integer getDevicegroupid() {
		return this.devicegroupid;
	}

	public void setDevicegroupid(Integer devicegroupid) {
		this.devicegroupid = devicegroupid;
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

	public String getGroupvml() {
		return this.groupvml;
	}

	public void setGroupvml(String groupvml) {
		this.groupvml = groupvml;
	}

	public String getLastupdate() {
		return this.lastupdate;
	}

	public void setLastupdate(String lastupdate) {
		this.lastupdate = lastupdate;
	}

	@Override
	public String toString() {
		return "AbstractmonitorTopoGroupInfo [devicegroupid=" + devicegroupid
				+ ", groupheight=" + groupheight + ", groupvml=" + groupvml
				+ ", groupwidth=" + groupwidth + ", lastupdate=" + lastupdate
				+ "]";
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((devicegroupid == null) ? 0 : devicegroupid.hashCode());
		result = prime * result
				+ ((groupheight == null) ? 0 : groupheight.hashCode());
		result = prime * result
				+ ((groupwidth == null) ? 0 : groupwidth.hashCode());
		result = prime * result
				+ ((lastupdate == null) ? 0 : lastupdate.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorTopoGroupInfo))
			return false;
		AbstractMonitorTopoGroupInfo other = (AbstractMonitorTopoGroupInfo) obj;
		if (devicegroupid == null) {
			if (other.devicegroupid != null)
				return false;
		} else if (!devicegroupid.equals(other.devicegroupid))
			return false;
		if (groupheight == null) {
			if (other.groupheight != null)
				return false;
		} else if (!groupheight.equals(other.groupheight))
			return false;
		if (groupwidth == null) {
			if (other.groupwidth != null)
				return false;
		} else if (!groupwidth.equals(other.groupwidth))
			return false;
		if (lastupdate == null) {
			if (other.lastupdate != null)
				return false;
		} else if (!lastupdate.equals(other.lastupdate))
			return false;
		return true;
	}

}