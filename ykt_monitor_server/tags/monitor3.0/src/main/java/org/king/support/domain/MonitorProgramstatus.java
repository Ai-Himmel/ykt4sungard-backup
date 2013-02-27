package org.king.support.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * MonitorProgramstatus entity. @author MyEclipse Persistence Tools
 */
public class MonitorProgramstatus extends AbstractMonitorProgramstatus
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorProgramstatus() {
	}

	/** full constructor */
	public MonitorProgramstatus(Date statusUpdateTime, Date programStartTime,
			Date programEndTime, BigDecimal isCurrentlyRunning,
			Date lastCommandCheck, Date lastLogRotation,
			BigDecimal notificationsEnabled,
			BigDecimal activeServiceChecksEnabled,
			BigDecimal passiveServiceChecksEnabled,
			BigDecimal activeHostChecksEnabled,
			BigDecimal passiveHostChecksEnabled,
			BigDecimal eventHandlersEnabled, BigDecimal flapDetectionEnabled) {
		super(statusUpdateTime, programStartTime, programEndTime,
				isCurrentlyRunning, lastCommandCheck, lastLogRotation,
				notificationsEnabled, activeServiceChecksEnabled,
				passiveServiceChecksEnabled, activeHostChecksEnabled,
				passiveHostChecksEnabled, eventHandlersEnabled,
				flapDetectionEnabled);
	}

}
