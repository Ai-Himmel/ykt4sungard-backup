package org.king.topo.domain;

import java.math.BigDecimal;
import java.sql.Clob;

import org.king.host.domain.MonitorHost;

/**
 * AbstractMonitorTopoServerStatistic entity provides the base persistence
 * definition of the MonitorTopoServerStatistic entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorTopoServerStatistic extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer hostid;
	private String hintinfo;
	private Integer status;
	private String lastupdate;
	private MonitorHost monitorHost=new MonitorHost();

	// Constructors

	/** default constructor */
	public AbstractMonitorTopoServerStatistic() {
	}

	/** full constructor */
	public AbstractMonitorTopoServerStatistic(String hintinfo, Integer status,
			String lastupdate) {
		this.hintinfo = hintinfo;
		this.status = status;
		this.lastupdate = lastupdate;
	}

	// Property accessors

	public Integer getHostid() {
		return this.hostid;
	}

	public void setHostid(Integer hostid) {
		this.hostid = hostid;
	}

	public String getHintinfo() {
		return this.hintinfo;
	}

	public void setHintinfo(String hintinfo) {
		this.hintinfo = hintinfo;
	}

	public Integer getStatus() {
		return this.status;
	}

	public void setStatus(Integer status) {
		this.status = status;
	}

	public String getLastupdate() {
		return this.lastupdate;
	}

	public void setLastupdate(String lastupdate) {
		this.lastupdate = lastupdate;
	}
	
	

	public MonitorHost getMonitorHost() {
		return monitorHost;
	}

	public void setMonitorHost(MonitorHost monitorHost) {
		this.monitorHost = monitorHost;
	}

	@Override
	public String toString() {
		return "AbstractMonitorTopoServerStatistic [hintinfo=" + hintinfo
				+ ", hostid=" + hostid + ", lastupdate=" + lastupdate
				+ ", status=" + status + "]";
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((hintinfo == null) ? 0 : hintinfo.hashCode());
		result = prime * result + ((hostid == null) ? 0 : hostid.hashCode());
		result = prime * result
				+ ((lastupdate == null) ? 0 : lastupdate.hashCode());
		result = prime * result + ((status == null) ? 0 : status.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorTopoServerStatistic))
			return false;
		AbstractMonitorTopoServerStatistic other = (AbstractMonitorTopoServerStatistic) obj;
		if (hintinfo == null) {
			if (other.hintinfo != null)
				return false;
		} else if (!hintinfo.equals(other.hintinfo))
			return false;
		if (hostid == null) {
			if (other.hostid != null)
				return false;
		} else if (!hostid.equals(other.hostid))
			return false;
		if (lastupdate == null) {
			if (other.lastupdate != null)
				return false;
		} else if (!lastupdate.equals(other.lastupdate))
			return false;
		if (status == null) {
			if (other.status != null)
				return false;
		} else if (!status.equals(other.status))
			return false;
		return true;
	}

}