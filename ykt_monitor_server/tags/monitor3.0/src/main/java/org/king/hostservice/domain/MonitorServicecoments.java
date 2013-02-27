package org.king.hostservice.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * MonitorServicecoments entity. @author MyEclipse Persistence Tools
 */
public class MonitorServicecoments extends AbstractMonitorServicecoments
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorServicecoments() {
	}

	/** full constructor */
	public MonitorServicecoments(Date entryTime, BigDecimal entryType,
			BigDecimal serviceId, String authorName, String commentData,
			BigDecimal isPersistent, BigDecimal commentSource,
			BigDecimal expires, Date expirationTime, BigDecimal isDeleted,
			Date deletionTime) {
		super(entryTime, entryType, serviceId, authorName, commentData,
				isPersistent, commentSource, expires, expirationTime,
				isDeleted, deletionTime);
	}

}
