package org.king.host.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * MonitorHostscheduleddowntime entity. @author MyEclipse Persistence Tools
 */
public class MonitorHostscheduleddowntime extends
		AbstractMonitorHostscheduleddowntime implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorHostscheduleddowntime() {
	}

	/** full constructor */
	public MonitorHostscheduleddowntime(Integer downtimeType,
			Integer hostId, String entryTime, String authorName,
			String commentData, Integer isFixed, Integer duration,
			String scheduledStartTime, String scheduledEndTime,
			Integer wasStarted, String actualStartTime, String actualEndTime,
			Integer wasCancelled) {
		super(downtimeType, hostId, entryTime, authorName, commentData,
				isFixed, duration, scheduledStartTime, scheduledEndTime,
				wasStarted, actualStartTime, actualEndTime, wasCancelled);
	}

}
