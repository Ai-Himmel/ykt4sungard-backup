package org.king.hostservice.domain;

import org.king.host.domain.MonitorHost;
import org.king.support.domain.MonitorCommands;
import org.king.support.domain.MonitorContactgroups;
import org.king.template.domain.MonitorTimePeriods;

/**
 * MonitorService entity. @author MyEclipse Persistence Tools
 */
public class MonitorServiceAll extends AbstractMonitorServiceAll implements
		java.io.Serializable {

	// Constructors

	/**
	 * default constructor
	 */
	public MonitorServiceAll() {
	}

	/**
	 * minimal constructor
	 */
	public MonitorServiceAll(Integer serviceId) {
		super(serviceId);
	}

	/**
	 * full constructor
	 */
	public MonitorServiceAll(Integer serviceId, MonitorHost monitorHost,
			String serviceName, MonitorCommands checkCommand,
			String checkCommandArgs, MonitorCommands eventhandlerCommand,
			String eventhandlerCommandArgs,
			MonitorTimePeriods notificationTimeperiod,
			MonitorTimePeriods checkTimeperiod, Double checkInterval,
			Double retryInterval, Integer maxCheckAttempts,
			Double notificationInterval, Integer notifyOnWarning,
			Integer notifyOnUnknown, Integer notifyOnCritical,
			Integer notifyOnRecovery, Integer notifyOnFlapping,
			Integer notifyOnDowntime, Integer flapDetectionEnabled,
			Integer flapDetectionOnOk, Integer flapDetectionOnWarning,
			Integer flapDetectionOnUnknown, Integer flapDetectionOnCritical,
			Double lowFlapThreshold, Double highFlapThreshold,
			Integer freshnessChecksEnabled, Integer freshnessThreshold,
			Integer passiveChecksEnabled, Integer eventHandlerEnabled,
			Integer activeChecksEnabled, Integer retainStatusInformation,
			Integer retainNonstatusInformation, Integer notificationsEnabled,
			String notes, String notesUrl, String actionurl,
			String notificationOptions, MonitorContactgroups contactGroups,Integer checkFlag) {
		super(serviceId, monitorHost, serviceName, checkCommand,
				checkCommandArgs, eventhandlerCommand, eventhandlerCommandArgs,
				notificationTimeperiod, checkTimeperiod, checkInterval,
				retryInterval, maxCheckAttempts, notificationInterval,
				notifyOnWarning, notifyOnUnknown, notifyOnCritical,
				notifyOnRecovery, notifyOnFlapping, notifyOnDowntime,
				flapDetectionEnabled, flapDetectionOnOk,
				flapDetectionOnWarning, flapDetectionOnUnknown,
				flapDetectionOnCritical, lowFlapThreshold, highFlapThreshold,
				freshnessChecksEnabled, freshnessThreshold,
				passiveChecksEnabled, eventHandlerEnabled, activeChecksEnabled,
				retainStatusInformation, retainNonstatusInformation,
				notificationsEnabled, notes, notesUrl, actionurl,
				notificationOptions, contactGroups,checkFlag);
	}
}
