package org.king.host.domain;


/**
 * MonitorHostStatus entity. @author MyEclipse Persistence Tools
 */
public class MonitorHostStatus extends AbstractMonitorHostStatus implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorHostStatus() {
	}

	/** minimal constructor */
	public MonitorHostStatus(Integer hostId) {
		super(hostId);
	}

	/** full constructor */
	public MonitorHostStatus(Integer hostId, String statusUpdateTime,
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
		super(hostId, statusUpdateTime, output, perfdata, currentState,
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
