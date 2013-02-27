package org.king.support.domain;

import java.math.BigDecimal;

/**
 * MonitorContactgroupMembers entity. @author MyEclipse Persistence Tools
 */
public class MonitorContactgroupMembers extends
		AbstractMonitorContactgroupMembers implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorContactgroupMembers() {
	}

	/** full constructor */
	public MonitorContactgroupMembers(BigDecimal contactgroupId,
			BigDecimal contactObjectId) {
		super(contactgroupId, contactObjectId);
	}

}
