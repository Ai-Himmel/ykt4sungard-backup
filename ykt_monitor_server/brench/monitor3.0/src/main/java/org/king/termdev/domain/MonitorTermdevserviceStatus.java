package org.king.termdev.domain;

/**
 * MonitorTermdevserviceStatus entity. @author MyEclipse Persistence Tools
 */
public class MonitorTermdevserviceStatus extends
		AbstractMonitorTermdevserviceStatus implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorTermdevserviceStatus() {
	}

	/** minimal constructor */
	public MonitorTermdevserviceStatus(Integer devserviceId) {
		super(devserviceId);
	}

	/** full constructor */
	public MonitorTermdevserviceStatus(Integer devserviceId,
			String statusUpdateTime, String output, String perfdata,
			Integer currentState, Integer hasBeenChecked,
			Integer shouldBeScheduled, Integer currentCheckAttempt,
			Integer maxCheckAttempts, String lastCheck, String nextCheck,
			Integer checkType, String lastStateChange,
			String lastHardStateChange, Integer lastHardState,
			String lastTimeOk, String lastTimeWarning, String lastTimeUnknow,
			String lastTimeCritical, Integer stateType, String lastNotification,
			String nextNotification, Integer notificationsEnabled,
			Integer problemHasBeenAcknowledged,
			Integer acknowledgementType,
			Integer currentNotificationNumber,
			Integer passiveChecksEnabled, Integer activeChecksEnabled,
			Integer eventHandlerEnabled, Integer flapDetectionEnabled,
			Integer isFlapping, Double percentStateChange, Double latency,
			Double executionTime, String eventHandler, String checkCommand,
			Integer normalCheckInterval, Integer retryCheckInterval,
			Integer checkTimeperiodId) {
		super(devserviceId, statusUpdateTime, output, perfdata, currentState,
				hasBeenChecked, shouldBeScheduled, currentCheckAttempt,
				maxCheckAttempts, lastCheck, nextCheck, checkType,
				lastStateChange, lastHardStateChange, lastHardState,
				lastTimeOk, lastTimeWarning, lastTimeUnknow, lastTimeCritical,
				stateType, lastNotification, nextNotification,
				notificationsEnabled, problemHasBeenAcknowledged,
				acknowledgementType, currentNotificationNumber,
				passiveChecksEnabled, activeChecksEnabled, eventHandlerEnabled,
				flapDetectionEnabled, isFlapping, percentStateChange, latency,
				executionTime, eventHandler, checkCommand, normalCheckInterval,
				retryCheckInterval, checkTimeperiodId);
	}

}
