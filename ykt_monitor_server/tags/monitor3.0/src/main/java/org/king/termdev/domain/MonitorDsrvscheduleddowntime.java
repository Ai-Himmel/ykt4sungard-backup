package org.king.termdev.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * MonitorDsrvscheduleddowntime entity. @author MyEclipse Persistence Tools
 */
public class MonitorDsrvscheduleddowntime extends
		AbstractMonitorDsrvscheduleddowntime implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorDsrvscheduleddowntime() {
	}

	/** full constructor */
	public MonitorDsrvscheduleddowntime(Integer downtimeType,
			Integer devserviceId, String entryTime, String authorName,
			String commentData, Integer isFixed, Integer duration,
			String scheduledStartTime, String scheduledEndTime,
			Integer wasStarted, String actualStartTime, String actualEndTime,
			Integer wasCancelled) {
		super(downtimeType, devserviceId, entryTime, authorName, commentData,
				isFixed, duration, scheduledStartTime, scheduledEndTime,
				wasStarted, actualStartTime, actualEndTime, wasCancelled);
	}

}
