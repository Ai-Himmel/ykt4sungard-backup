package org.king.termdev.domain;

import org.king.common.displaytag.DBPaginatedList;
import org.king.support.domain.MonitorCommands;
import org.king.template.domain.MonitorTimePeriods;

/**
 * MonitorTermdevService entity. @author MyEclipse Persistence Tools
 */
public class MonitorTermdevService extends AbstractMonitorTermdevService
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorTermdevService() {
	}

	/** full constructor */
	public MonitorTermdevService(Integer deviceId, String devserviceName,
			MonitorCommands checkCommand, String checkCommandArgs,
			Integer eventhandlerCommandId, String eventhandlerCommandArgs,
			MonitorTimePeriods notificationTimeperiod, MonitorTimePeriods checkTimeperiod,
			Double checkInterval, Double retryInterval,
			Integer maxCheckAttempts, Double notificationInterval,
			Integer notifyOnWarning, Integer notifyOnUnknown,
			Integer notifyOnCritical, Integer notifyOnRecovery,
			Integer notifyOnFlapping, Integer notifyOnDowntime,
			Integer flapDetectionEnabled, Integer flapDetectionOnOk,
			Integer flapDetectionOnWarning,
			Integer flapDetectionOnUnknown,
			Integer flapDetectionOnCritical, Double lowFlapThreshold,
			Double highFlapThreshold, Integer freshnessChecksEnabled,
			Integer freshnessThreshold, Integer passiveChecksEnabled,
			Integer eventHandlerEnabled, Integer activeChecksEnabled,
			Integer retainStatusInformation,
			Integer retainNonstatusInformation,
			Integer notificationsEnabled, String notes, String notesUrl,
			String actionurl) {
		super(deviceId, devserviceName, checkCommand, checkCommandArgs,
				eventhandlerCommandId, eventhandlerCommandArgs,
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
				notificationsEnabled, notes, notesUrl, actionurl);
	}
}
