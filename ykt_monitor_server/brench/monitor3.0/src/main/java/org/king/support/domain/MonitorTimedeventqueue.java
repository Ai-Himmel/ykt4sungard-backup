package org.king.support.domain;

import java.util.Date;

/**
 * MonitorTimedeventqueue entity. @author MyEclipse Persistence Tools
 */
public class MonitorTimedeventqueue extends AbstractMonitorTimedeventqueue
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorTimedeventqueue() {
	}

	/** full constructor */
	public MonitorTimedeventqueue(Integer eventType, String queueTime,
			String scheduledTime, Integer recurringEvent, Integer objectId) {
		super(eventType, queueTime, scheduledTime, recurringEvent, objectId);
	}

}
