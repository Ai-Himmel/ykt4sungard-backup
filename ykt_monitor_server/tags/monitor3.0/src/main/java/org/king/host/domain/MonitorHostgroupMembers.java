package org.king.host.domain;

import java.math.BigDecimal;

/**
 * MonitorHostgroupMembers entity. @author MyEclipse Persistence Tools
 */
public class MonitorHostgroupMembers extends AbstractMonitorHostgroupMembers
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorHostgroupMembers() {
	}

	/** full constructor */
	public MonitorHostgroupMembers(BigDecimal hostgroupId, BigDecimal hostId) {
		super(hostgroupId, hostId);
	}

}
