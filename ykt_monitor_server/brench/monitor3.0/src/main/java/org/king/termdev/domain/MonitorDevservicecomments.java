package org.king.termdev.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * MonitorDevservicecomments entity. @author MyEclipse Persistence Tools
 */
public class MonitorDevservicecomments extends
		AbstractMonitorDevservicecomments implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorDevservicecomments() {
	}

	/** full constructor */
	public MonitorDevservicecomments(Date entryTime, BigDecimal entryType,
			BigDecimal devserviceId, String authorName, String commentData,
			BigDecimal isPersistent, BigDecimal commentSource,
			BigDecimal expires, Date expirationTime, BigDecimal isDeleted,
			Date deletionTime) {
		super(entryTime, entryType, devserviceId, authorName, commentData,
				isPersistent, commentSource, expires, expirationTime,
				isDeleted, deletionTime);
	}

}
