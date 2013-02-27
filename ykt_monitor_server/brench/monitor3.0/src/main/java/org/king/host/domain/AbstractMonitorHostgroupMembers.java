package org.king.host.domain;

import java.math.BigDecimal;

/**
 * AbstractMonitorHostgroupMembers entity provides the base persistence
 * definition of the MonitorHostgroupMembers entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorHostgroupMembers extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private BigDecimal hostgroupMemberId;
	private BigDecimal hostgroupId;
	private BigDecimal hostId;

	// Constructors

	/** default constructor */
	public AbstractMonitorHostgroupMembers() {
	}

	/** full constructor */
	public AbstractMonitorHostgroupMembers(BigDecimal hostgroupId,
			BigDecimal hostId) {
		this.hostgroupId = hostgroupId;
		this.hostId = hostId;
	}

	// Property accessors

	public BigDecimal getHostgroupMemberId() {
		return this.hostgroupMemberId;
	}

	public void setHostgroupMemberId(BigDecimal hostgroupMemberId) {
		this.hostgroupMemberId = hostgroupMemberId;
	}

	public BigDecimal getHostgroupId() {
		return this.hostgroupId;
	}

	public void setHostgroupId(BigDecimal hostgroupId) {
		this.hostgroupId = hostgroupId;
	}

	public BigDecimal getHostId() {
		return this.hostId;
	}

	public void setHostId(BigDecimal hostId) {
		this.hostId = hostId;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result + ((hostId == null) ? 0 : hostId.hashCode());
		result = prime * result
				+ ((hostgroupId == null) ? 0 : hostgroupId.hashCode());
		result = prime
				* result
				+ ((hostgroupMemberId == null) ? 0 : hostgroupMemberId
						.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorHostgroupMembers))
			return false;
		AbstractMonitorHostgroupMembers other = (AbstractMonitorHostgroupMembers) obj;
		if (hostId == null) {
			if (other.hostId != null)
				return false;
		} else if (!hostId.equals(other.hostId))
			return false;
		if (hostgroupId == null) {
			if (other.hostgroupId != null)
				return false;
		} else if (!hostgroupId.equals(other.hostgroupId))
			return false;
		if (hostgroupMemberId == null) {
			if (other.hostgroupMemberId != null)
				return false;
		} else if (!hostgroupMemberId.equals(other.hostgroupMemberId))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorHostgroupMembers [hostId=" + hostId
				+ ", hostgroupId=" + hostgroupId + ", hostgroupMemberId="
				+ hostgroupMemberId + "]";
	}

}