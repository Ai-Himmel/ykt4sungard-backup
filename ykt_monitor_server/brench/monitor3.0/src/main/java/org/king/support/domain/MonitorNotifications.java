package org.king.support.domain;

import java.math.BigDecimal;

/**
 * MonitorNotifications entity. @author MyEclipse Persistence Tools
 */
public class MonitorNotifications extends AbstractMonitorNotifications
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorNotifications() {
	}

	/** full constructor */
	public MonitorNotifications(Integer notificationType,
			Integer objectId, String notificationTime, Integer state,
			String output, Integer sendOrNot) {
		super(notificationType, objectId, notificationTime, state, output, sendOrNot);
	}

}
