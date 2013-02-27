package org.king.termdev.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * MonitorDevscheduleddowntime entity. @author MyEclipse Persistence Tools
 */
public class MonitorDevscheduleddowntime extends
		AbstractMonitorDevscheduleddowntime implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorDevscheduleddowntime() {
	}

	/** full constructor */
	public MonitorDevscheduleddowntime(Integer downtimeType,
			Integer deviceId, String entryTime, String authorName,
			String commentData, Integer isFixed, Integer duration,
			String scheduledStartTime, String scheduledEndTime,
			Integer wasStarted, String actualStartTime, String actualEndTime,
			Integer wasCancelled) {
		super(downtimeType, deviceId, entryTime, authorName, commentData,
				isFixed, duration, scheduledStartTime, scheduledEndTime,
				wasStarted, actualStartTime, actualEndTime, wasCancelled);
	}

}
