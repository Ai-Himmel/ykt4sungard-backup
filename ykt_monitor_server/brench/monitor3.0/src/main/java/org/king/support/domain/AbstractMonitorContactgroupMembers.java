package org.king.support.domain;

import java.math.BigDecimal;

/**
 * AbstractMonitorContactgroupMembers entity provides the base persistence
 * definition of the MonitorContactgroupMembers entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorContactgroupMembers extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private BigDecimal contactgroupMemberId;
	private BigDecimal contactgroupId;
	private BigDecimal contactObjectId;

	// Constructors

	/** default constructor */
	public AbstractMonitorContactgroupMembers() {
	}

	/** full constructor */
	public AbstractMonitorContactgroupMembers(BigDecimal contactgroupId,
			BigDecimal contactObjectId) {
		this.contactgroupId = contactgroupId;
		this.contactObjectId = contactObjectId;
	}

	// Property accessors

	public BigDecimal getContactgroupMemberId() {
		return this.contactgroupMemberId;
	}

	public void setContactgroupMemberId(BigDecimal contactgroupMemberId) {
		this.contactgroupMemberId = contactgroupMemberId;
	}

	public BigDecimal getContactgroupId() {
		return this.contactgroupId;
	}

	public void setContactgroupId(BigDecimal contactgroupId) {
		this.contactgroupId = contactgroupId;
	}

	public BigDecimal getContactObjectId() {
		return this.contactObjectId;
	}

	public void setContactObjectId(BigDecimal contactObjectId) {
		this.contactObjectId = contactObjectId;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((contactObjectId == null) ? 0 : contactObjectId.hashCode());
		result = prime * result
				+ ((contactgroupId == null) ? 0 : contactgroupId.hashCode());
		result = prime
				* result
				+ ((contactgroupMemberId == null) ? 0 : contactgroupMemberId
						.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorContactgroupMembers))
			return false;
		AbstractMonitorContactgroupMembers other = (AbstractMonitorContactgroupMembers) obj;
		if (contactObjectId == null) {
			if (other.contactObjectId != null)
				return false;
		} else if (!contactObjectId.equals(other.contactObjectId))
			return false;
		if (contactgroupId == null) {
			if (other.contactgroupId != null)
				return false;
		} else if (!contactgroupId.equals(other.contactgroupId))
			return false;
		if (contactgroupMemberId == null) {
			if (other.contactgroupMemberId != null)
				return false;
		} else if (!contactgroupMemberId.equals(other.contactgroupMemberId))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorContactgroupMembers [contactObjectId="
				+ contactObjectId + ", contactgroupId=" + contactgroupId
				+ ", contactgroupMemberId=" + contactgroupMemberId + "]";
	}

}