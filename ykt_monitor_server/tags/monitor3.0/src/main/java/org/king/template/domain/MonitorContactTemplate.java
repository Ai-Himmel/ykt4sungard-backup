package org.king.template.domain;

/**
 * MonitorContactTemplate entity. @author MyEclipse Persistence Tools
 */
public class MonitorContactTemplate extends AbstractMonitorContactTemplate
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorContactTemplate() {
	}

	/** full constructor */
	public MonitorContactTemplate(String templateName,
			MonitorTimePeriods serviceNotificationPeriod,
			MonitorTimePeriods hostNotificationPeriod,
			String serviceNotificationOptions, String hostNotificationOptions,
			String serviceNotificationCommands, String hostNotificationCommands) {
		super(templateName, serviceNotificationPeriod, hostNotificationPeriod,
				serviceNotificationOptions, hostNotificationOptions,
				serviceNotificationCommands, hostNotificationCommands);
	}

}
