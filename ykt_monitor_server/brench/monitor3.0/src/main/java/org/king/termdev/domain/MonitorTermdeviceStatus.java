package org.king.termdev.domain;

/**
 * MonitorTermdeviceStatus entity. @author MyEclipse Persistence Tools
 */
public class MonitorTermdeviceStatus extends AbstractMonitorTermdeviceStatus
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorTermdeviceStatus() {
	}

	/** minimal constructor */
	public MonitorTermdeviceStatus(Integer deviceId) {
		super(deviceId);
	}

	/** full constructor */
	public MonitorTermdeviceStatus(Integer deviceId, String statusUpdateTime,
			String output, String perfdata, Integer currentState,
			Integer hasBeenChecked, Integer shouldBeScheduled,
			Integer currentCheckAttempt, Integer maxCheckAttempts,
			String lastCheck, String nextCheck, Integer checkType,
			String lastStateChange, String lastHardStateChange,
			Integer lastHardState, String lastTimeUp, String lastTimeDown,
			String lastTimeUnreachable, Integer stateType,
			String lastNotification, String nextNotification,
			Integer notificationsEnabled,
			Integer problemHasBeenAcknowledged,
			Integer acknowledgementType,
			Integer currentNotificationNumber,
			Integer passiveChecksEnabled, Integer activeChecksEnabled,
			Integer eventHandlerEnabled, Integer flapDetectionEnabled,
			Integer isFlapping, Double percentStateChange, Double latency,
			Double executionTime, String eventHandler, String checkCommand,
			Double normalCheckInterval, Double retryCheckInterval,
			Integer checkTimeperiodId) {
		super(deviceId, statusUpdateTime, output, perfdata, currentState,
				hasBeenChecked, shouldBeScheduled, currentCheckAttempt,
				maxCheckAttempts, lastCheck, nextCheck, checkType,
				lastStateChange, lastHardStateChange, lastHardState,
				lastTimeUp, lastTimeDown, lastTimeUnreachable, stateType,
				lastNotification, nextNotification, notificationsEnabled,
				problemHasBeenAcknowledged, acknowledgementType,
				currentNotificationNumber, passiveChecksEnabled,
				activeChecksEnabled, eventHandlerEnabled, flapDetectionEnabled,
				isFlapping, percentStateChange, latency, executionTime,
				eventHandler, checkCommand, normalCheckInterval,
				retryCheckInterval, checkTimeperiodId);
	}

}
