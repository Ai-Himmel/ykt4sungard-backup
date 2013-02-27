package org.king.host.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * MonitorHostcomments entity. @author MyEclipse Persistence Tools
 */
public class MonitorHostcomments extends AbstractMonitorHostcomments implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorHostcomments() {
	}

	/** full constructor */
	public MonitorHostcomments(Date entryTime, BigDecimal entryType,
			BigDecimal hostId, String authorName, String commentData,
			BigDecimal isPersistent, BigDecimal commentSource,
			BigDecimal expires, Date expirationTime, BigDecimal isDeleted,
			Date deletionTime) {
		super(entryTime, entryType, hostId, authorName, commentData,
				isPersistent, commentSource, expires, expirationTime,
				isDeleted, deletionTime);
	}

}
