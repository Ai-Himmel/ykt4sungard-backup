package org.king.termdev.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * MonitorDevicecomments entity. @author MyEclipse Persistence Tools
 */
public class MonitorDevicecomments extends AbstractMonitorDevicecomments
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorDevicecomments() {
	}

	/** full constructor */
	public MonitorDevicecomments(Date entryTime, BigDecimal entryType,
			BigDecimal deviceId, String authorName, String commentData,
			BigDecimal isPersistent, BigDecimal commentSource,
			BigDecimal expires, Date expirationTime, BigDecimal isDeleted,
			Date deletionTime) {
		super(entryTime, entryType, deviceId, authorName, commentData,
				isPersistent, commentSource, expires, expirationTime,
				isDeleted, deletionTime);
	}

}
