package org.king.hostservice.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * MonitorSrvScheduleddowntime entity. @author MyEclipse Persistence Tools
 */
public class MonitorSrvScheduleddowntime extends
		AbstractMonitorSrvScheduleddowntime implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorSrvScheduleddowntime() {
	}

	/** full constructor */
	public MonitorSrvScheduleddowntime(Integer downtimeType,
			Integer serviceId, String entryTime, String authorName,
			String commentData, Integer isFixed, Integer duration,
			String scheduledStartTime, String scheduledEndTime,
			Integer wasStarted, String actualStartTime, String actualEndTime,
			Integer wasCancelled) {
		super(downtimeType, serviceId, entryTime, authorName, commentData,
				isFixed, duration, scheduledStartTime, scheduledEndTime,
				wasStarted, actualStartTime, actualEndTime, wasCancelled);
	}

}
