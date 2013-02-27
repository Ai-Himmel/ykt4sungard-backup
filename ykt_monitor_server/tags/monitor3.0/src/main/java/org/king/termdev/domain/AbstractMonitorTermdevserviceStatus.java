package org.king.termdev.domain;

/**
 * AbstractMonitorTermdevserviceStatus entity provides the base persistence
 * definition of the MonitorTermdevserviceStatus entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorTermdevserviceStatus extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer devserviceId;
	private String statusUpdateTime;
	private String output;
	private String perfdata;
	private Integer currentState;
	private Integer hasBeenChecked;
	private Integer shouldBeScheduled;
	private Integer currentCheckAttempt;
	private Integer maxCheckAttempts;
	private String lastCheck;
	private String nextCheck;
	private Integer checkType;
	private String lastStateChange;
	private String lastHardStateChange;
	private Integer lastHardState;
	private String lastTimeOk;
	private String lastTimeWarning;
	private String lastTimeUnknow;
	private String lastTimeCritical;
	private Integer stateType;
	private String lastNotification;
	private String nextNotification;
	private Integer notificationsEnabled;
	private Integer problemHasBeenAcknowledged;
	private Integer acknowledgementType;
	private Integer currentNotificationNumber;
	private Integer passiveChecksEnabled;
	private Integer activeChecksEnabled;
	private Integer eventHandlerEnabled;
	private Integer flapDetectionEnabled;
	private Integer isFlapping;
	private Double percentStateChange;
	private Double latency;
	private Double executionTime;
	private String eventHandler;
	private String checkCommand;
	private Integer normalCheckInterval;
	private Integer retryCheckInterval;
	private Integer checkTimeperiodId;

	// Constructors

	/** default constructor */
	public AbstractMonitorTermdevserviceStatus() {
	}

	/** minimal constructor */
	public AbstractMonitorTermdevserviceStatus(Integer devserviceId) {
		this.devserviceId = devserviceId;
	}

	/** full constructor */
	public AbstractMonitorTermdevserviceStatus(Integer devserviceId,
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
		this.devserviceId = devserviceId;
		this.statusUpdateTime = statusUpdateTime;
		this.output = output;
		this.perfdata = perfdata;
		this.currentState = currentState;
		this.hasBeenChecked = hasBeenChecked;
		this.shouldBeScheduled = shouldBeScheduled;
		this.currentCheckAttempt = currentCheckAttempt;
		this.maxCheckAttempts = maxCheckAttempts;
		this.lastCheck = lastCheck;
		this.nextCheck = nextCheck;
		this.checkType = checkType;
		this.lastStateChange = lastStateChange;
		this.lastHardStateChange = lastHardStateChange;
		this.lastHardState = lastHardState;
		this.lastTimeOk = lastTimeOk;
		this.lastTimeWarning = lastTimeWarning;
		this.lastTimeUnknow = lastTimeUnknow;
		this.lastTimeCritical = lastTimeCritical;
		this.stateType = stateType;
		this.lastNotification = lastNotification;
		this.nextNotification = nextNotification;
		this.notificationsEnabled = notificationsEnabled;
		this.problemHasBeenAcknowledged = problemHasBeenAcknowledged;
		this.acknowledgementType = acknowledgementType;
		this.currentNotificationNumber = currentNotificationNumber;
		this.passiveChecksEnabled = passiveChecksEnabled;
		this.activeChecksEnabled = activeChecksEnabled;
		this.eventHandlerEnabled = eventHandlerEnabled;
		this.flapDetectionEnabled = flapDetectionEnabled;
		this.isFlapping = isFlapping;
		this.percentStateChange = percentStateChange;
		this.latency = latency;
		this.executionTime = executionTime;
		this.eventHandler = eventHandler;
		this.checkCommand = checkCommand;
		this.normalCheckInterval = normalCheckInterval;
		this.retryCheckInterval = retryCheckInterval;
		this.checkTimeperiodId = checkTimeperiodId;
	}

	// Property accessors

	public Integer getDevserviceId() {
		return this.devserviceId;
	}

	public void setDevserviceId(Integer devserviceId) {
		this.devserviceId = devserviceId;
	}

	public String getStatusUpdateTime() {
		return this.statusUpdateTime;
	}

	public void setStatusUpdateTime(String statusUpdateTime) {
		this.statusUpdateTime = statusUpdateTime;
	}

	public String getOutput() {
		return this.output;
	}

	public void setOutput(String output) {
		this.output = output;
	}

	public String getPerfdata() {
		return this.perfdata;
	}

	public void setPerfdata(String perfdata) {
		this.perfdata = perfdata;
	}

	public Integer getCurrentState() {
		return this.currentState;
	}

	public void setCurrentState(Integer currentState) {
		this.currentState = currentState;
	}

	public Integer getHasBeenChecked() {
		return this.hasBeenChecked;
	}

	public void setHasBeenChecked(Integer hasBeenChecked) {
		this.hasBeenChecked = hasBeenChecked;
	}

	public Integer getShouldBeScheduled() {
		return this.shouldBeScheduled;
	}

	public void setShouldBeScheduled(Integer shouldBeScheduled) {
		this.shouldBeScheduled = shouldBeScheduled;
	}

	public Integer getCurrentCheckAttempt() {
		return this.currentCheckAttempt;
	}

	public void setCurrentCheckAttempt(Integer currentCheckAttempt) {
		this.currentCheckAttempt = currentCheckAttempt;
	}

	public Integer getMaxCheckAttempts() {
		return this.maxCheckAttempts;
	}

	public void setMaxCheckAttempts(Integer maxCheckAttempts) {
		this.maxCheckAttempts = maxCheckAttempts;
	}

	public String getLastCheck() {
		return this.lastCheck;
	}

	public void setLastCheck(String lastCheck) {
		this.lastCheck = lastCheck;
	}

	public String getNextCheck() {
		return this.nextCheck;
	}

	public void setNextCheck(String nextCheck) {
		this.nextCheck = nextCheck;
	}

	public Integer getCheckType() {
		return this.checkType;
	}

	public void setCheckType(Integer checkType) {
		this.checkType = checkType;
	}

	public String getLastStateChange() {
		return this.lastStateChange;
	}

	public void setLastStateChange(String lastStateChange) {
		this.lastStateChange = lastStateChange;
	}

	public String getLastHardStateChange() {
		return this.lastHardStateChange;
	}

	public void setLastHardStateChange(String lastHardStateChange) {
		this.lastHardStateChange = lastHardStateChange;
	}

	public Integer getLastHardState() {
		return this.lastHardState;
	}

	public void setLastHardState(Integer lastHardState) {
		this.lastHardState = lastHardState;
	}

	public String getLastTimeOk() {
		return this.lastTimeOk;
	}

	public void setLastTimeOk(String lastTimeOk) {
		this.lastTimeOk = lastTimeOk;
	}

	public String getLastTimeWarning() {
		return this.lastTimeWarning;
	}

	public void setLastTimeWarning(String lastTimeWarning) {
		this.lastTimeWarning = lastTimeWarning;
	}

	public String getLastTimeUnknow() {
		return this.lastTimeUnknow;
	}

	public void setLastTimeUnknow(String lastTimeUnknow) {
		this.lastTimeUnknow = lastTimeUnknow;
	}

	public String getLastTimeCritical() {
		return this.lastTimeCritical;
	}

	public void setLastTimeCritical(String lastTimeCritical) {
		this.lastTimeCritical = lastTimeCritical;
	}

	public Integer getStateType() {
		return this.stateType;
	}

	public void setStateType(Integer stateType) {
		this.stateType = stateType;
	}

	public String getLastNotification() {
		return this.lastNotification;
	}

	public void setLastNotification(String lastNotification) {
		this.lastNotification = lastNotification;
	}

	public String getNextNotification() {
		return this.nextNotification;
	}

	public void setNextNotification(String nextNotification) {
		this.nextNotification = nextNotification;
	}

	public Integer getNotificationsEnabled() {
		return this.notificationsEnabled;
	}

	public void setNotificationsEnabled(Integer notificationsEnabled) {
		this.notificationsEnabled = notificationsEnabled;
	}

	public Integer getProblemHasBeenAcknowledged() {
		return this.problemHasBeenAcknowledged;
	}

	public void setProblemHasBeenAcknowledged(
			Integer problemHasBeenAcknowledged) {
		this.problemHasBeenAcknowledged = problemHasBeenAcknowledged;
	}

	public Integer getAcknowledgementType() {
		return this.acknowledgementType;
	}

	public void setAcknowledgementType(Integer acknowledgementType) {
		this.acknowledgementType = acknowledgementType;
	}

	public Integer getCurrentNotificationNumber() {
		return this.currentNotificationNumber;
	}

	public void setCurrentNotificationNumber(
			Integer currentNotificationNumber) {
		this.currentNotificationNumber = currentNotificationNumber;
	}

	public Integer getPassiveChecksEnabled() {
		return this.passiveChecksEnabled;
	}

	public void setPassiveChecksEnabled(Integer passiveChecksEnabled) {
		this.passiveChecksEnabled = passiveChecksEnabled;
	}

	public Integer getActiveChecksEnabled() {
		return this.activeChecksEnabled;
	}

	public void setActiveChecksEnabled(Integer activeChecksEnabled) {
		this.activeChecksEnabled = activeChecksEnabled;
	}

	public Integer getEventHandlerEnabled() {
		return this.eventHandlerEnabled;
	}

	public void setEventHandlerEnabled(Integer eventHandlerEnabled) {
		this.eventHandlerEnabled = eventHandlerEnabled;
	}

	public Integer getFlapDetectionEnabled() {
		return this.flapDetectionEnabled;
	}

	public void setFlapDetectionEnabled(Integer flapDetectionEnabled) {
		this.flapDetectionEnabled = flapDetectionEnabled;
	}

	public Integer getIsFlapping() {
		return this.isFlapping;
	}

	public void setIsFlapping(Integer isFlapping) {
		this.isFlapping = isFlapping;
	}

	public Double getPercentStateChange() {
		return this.percentStateChange;
	}

	public void setPercentStateChange(Double percentStateChange) {
		this.percentStateChange = percentStateChange;
	}

	public Double getLatency() {
		return this.latency;
	}

	public void setLatency(Double latency) {
		this.latency = latency;
	}

	public Double getExecutionTime() {
		return this.executionTime;
	}

	public void setExecutionTime(Double executionTime) {
		this.executionTime = executionTime;
	}

	public String getEventHandler() {
		return this.eventHandler;
	}

	public void setEventHandler(String eventHandler) {
		this.eventHandler = eventHandler;
	}

	public String getCheckCommand() {
		return this.checkCommand;
	}

	public void setCheckCommand(String checkCommand) {
		this.checkCommand = checkCommand;
	}

	public Integer getNormalCheckInterval() {
		return this.normalCheckInterval;
	}

	public void setNormalCheckInterval(Integer normalCheckInterval) {
		this.normalCheckInterval = normalCheckInterval;
	}

	public Integer getRetryCheckInterval() {
		return this.retryCheckInterval;
	}

	public void setRetryCheckInterval(Integer retryCheckInterval) {
		this.retryCheckInterval = retryCheckInterval;
	}

	public Integer getCheckTimeperiodId() {
		return this.checkTimeperiodId;
	}

	public void setCheckTimeperiodId(Integer checkTimeperiodId) {
		this.checkTimeperiodId = checkTimeperiodId;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime
				* result
				+ ((acknowledgementType == null) ? 0 : acknowledgementType
						.hashCode());
		result = prime
				* result
				+ ((activeChecksEnabled == null) ? 0 : activeChecksEnabled
						.hashCode());
		result = prime * result
				+ ((checkCommand == null) ? 0 : checkCommand.hashCode());
		result = prime
				* result
				+ ((checkTimeperiodId == null) ? 0 : checkTimeperiodId
						.hashCode());
		result = prime * result
				+ ((checkType == null) ? 0 : checkType.hashCode());
		result = prime
				* result
				+ ((currentCheckAttempt == null) ? 0 : currentCheckAttempt
						.hashCode());
		result = prime
				* result
				+ ((currentNotificationNumber == null) ? 0
						: currentNotificationNumber.hashCode());
		result = prime * result
				+ ((currentState == null) ? 0 : currentState.hashCode());
		result = prime * result
				+ ((devserviceId == null) ? 0 : devserviceId.hashCode());
		result = prime * result
				+ ((eventHandler == null) ? 0 : eventHandler.hashCode());
		result = prime
				* result
				+ ((eventHandlerEnabled == null) ? 0 : eventHandlerEnabled
						.hashCode());
		result = prime * result
				+ ((executionTime == null) ? 0 : executionTime.hashCode());
		result = prime
				* result
				+ ((flapDetectionEnabled == null) ? 0 : flapDetectionEnabled
						.hashCode());
		result = prime * result
				+ ((hasBeenChecked == null) ? 0 : hasBeenChecked.hashCode());
		result = prime * result
				+ ((isFlapping == null) ? 0 : isFlapping.hashCode());
		result = prime * result
				+ ((lastCheck == null) ? 0 : lastCheck.hashCode());
		result = prime * result
				+ ((lastHardState == null) ? 0 : lastHardState.hashCode());
		result = prime
				* result
				+ ((lastHardStateChange == null) ? 0 : lastHardStateChange
						.hashCode());
		result = prime
				* result
				+ ((lastNotification == null) ? 0 : lastNotification.hashCode());
		result = prime * result
				+ ((lastStateChange == null) ? 0 : lastStateChange.hashCode());
		result = prime
				* result
				+ ((lastTimeCritical == null) ? 0 : lastTimeCritical.hashCode());
		result = prime * result
				+ ((lastTimeOk == null) ? 0 : lastTimeOk.hashCode());
		result = prime * result
				+ ((lastTimeUnknow == null) ? 0 : lastTimeUnknow.hashCode());
		result = prime * result
				+ ((lastTimeWarning == null) ? 0 : lastTimeWarning.hashCode());
		result = prime * result + ((latency == null) ? 0 : latency.hashCode());
		result = prime
				* result
				+ ((maxCheckAttempts == null) ? 0 : maxCheckAttempts.hashCode());
		result = prime * result
				+ ((nextCheck == null) ? 0 : nextCheck.hashCode());
		result = prime
				* result
				+ ((nextNotification == null) ? 0 : nextNotification.hashCode());
		result = prime
				* result
				+ ((normalCheckInterval == null) ? 0 : normalCheckInterval
						.hashCode());
		result = prime
				* result
				+ ((notificationsEnabled == null) ? 0 : notificationsEnabled
						.hashCode());
		result = prime * result + ((output == null) ? 0 : output.hashCode());
		result = prime
				* result
				+ ((passiveChecksEnabled == null) ? 0 : passiveChecksEnabled
						.hashCode());
		result = prime
				* result
				+ ((percentStateChange == null) ? 0 : percentStateChange
						.hashCode());
		result = prime * result
				+ ((perfdata == null) ? 0 : perfdata.hashCode());
		result = prime
				* result
				+ ((problemHasBeenAcknowledged == null) ? 0
						: problemHasBeenAcknowledged.hashCode());
		result = prime
				* result
				+ ((retryCheckInterval == null) ? 0 : retryCheckInterval
						.hashCode());
		result = prime
				* result
				+ ((shouldBeScheduled == null) ? 0 : shouldBeScheduled
						.hashCode());
		result = prime * result
				+ ((stateType == null) ? 0 : stateType.hashCode());
		result = prime
				* result
				+ ((statusUpdateTime == null) ? 0 : statusUpdateTime.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorTermdevserviceStatus))
			return false;
		AbstractMonitorTermdevserviceStatus other = (AbstractMonitorTermdevserviceStatus) obj;
		if (acknowledgementType == null) {
			if (other.acknowledgementType != null)
				return false;
		} else if (!acknowledgementType.equals(other.acknowledgementType))
			return false;
		if (activeChecksEnabled == null) {
			if (other.activeChecksEnabled != null)
				return false;
		} else if (!activeChecksEnabled.equals(other.activeChecksEnabled))
			return false;
		if (checkCommand == null) {
			if (other.checkCommand != null)
				return false;
		} else if (!checkCommand.equals(other.checkCommand))
			return false;
		if (checkTimeperiodId == null) {
			if (other.checkTimeperiodId != null)
				return false;
		} else if (!checkTimeperiodId.equals(other.checkTimeperiodId))
			return false;
		if (checkType == null) {
			if (other.checkType != null)
				return false;
		} else if (!checkType.equals(other.checkType))
			return false;
		if (currentCheckAttempt == null) {
			if (other.currentCheckAttempt != null)
				return false;
		} else if (!currentCheckAttempt.equals(other.currentCheckAttempt))
			return false;
		if (currentNotificationNumber == null) {
			if (other.currentNotificationNumber != null)
				return false;
		} else if (!currentNotificationNumber
				.equals(other.currentNotificationNumber))
			return false;
		if (currentState == null) {
			if (other.currentState != null)
				return false;
		} else if (!currentState.equals(other.currentState))
			return false;
		if (devserviceId == null) {
			if (other.devserviceId != null)
				return false;
		} else if (!devserviceId.equals(other.devserviceId))
			return false;
		if (eventHandler == null) {
			if (other.eventHandler != null)
				return false;
		} else if (!eventHandler.equals(other.eventHandler))
			return false;
		if (eventHandlerEnabled == null) {
			if (other.eventHandlerEnabled != null)
				return false;
		} else if (!eventHandlerEnabled.equals(other.eventHandlerEnabled))
			return false;
		if (executionTime == null) {
			if (other.executionTime != null)
				return false;
		} else if (!executionTime.equals(other.executionTime))
			return false;
		if (flapDetectionEnabled == null) {
			if (other.flapDetectionEnabled != null)
				return false;
		} else if (!flapDetectionEnabled.equals(other.flapDetectionEnabled))
			return false;
		if (hasBeenChecked == null) {
			if (other.hasBeenChecked != null)
				return false;
		} else if (!hasBeenChecked.equals(other.hasBeenChecked))
			return false;
		if (isFlapping == null) {
			if (other.isFlapping != null)
				return false;
		} else if (!isFlapping.equals(other.isFlapping))
			return false;
		if (lastCheck == null) {
			if (other.lastCheck != null)
				return false;
		} else if (!lastCheck.equals(other.lastCheck))
			return false;
		if (lastHardState == null) {
			if (other.lastHardState != null)
				return false;
		} else if (!lastHardState.equals(other.lastHardState))
			return false;
		if (lastHardStateChange == null) {
			if (other.lastHardStateChange != null)
				return false;
		} else if (!lastHardStateChange.equals(other.lastHardStateChange))
			return false;
		if (lastNotification == null) {
			if (other.lastNotification != null)
				return false;
		} else if (!lastNotification.equals(other.lastNotification))
			return false;
		if (lastStateChange == null) {
			if (other.lastStateChange != null)
				return false;
		} else if (!lastStateChange.equals(other.lastStateChange))
			return false;
		if (lastTimeCritical == null) {
			if (other.lastTimeCritical != null)
				return false;
		} else if (!lastTimeCritical.equals(other.lastTimeCritical))
			return false;
		if (lastTimeOk == null) {
			if (other.lastTimeOk != null)
				return false;
		} else if (!lastTimeOk.equals(other.lastTimeOk))
			return false;
		if (lastTimeUnknow == null) {
			if (other.lastTimeUnknow != null)
				return false;
		} else if (!lastTimeUnknow.equals(other.lastTimeUnknow))
			return false;
		if (lastTimeWarning == null) {
			if (other.lastTimeWarning != null)
				return false;
		} else if (!lastTimeWarning.equals(other.lastTimeWarning))
			return false;
		if (latency == null) {
			if (other.latency != null)
				return false;
		} else if (!latency.equals(other.latency))
			return false;
		if (maxCheckAttempts == null) {
			if (other.maxCheckAttempts != null)
				return false;
		} else if (!maxCheckAttempts.equals(other.maxCheckAttempts))
			return false;
		if (nextCheck == null) {
			if (other.nextCheck != null)
				return false;
		} else if (!nextCheck.equals(other.nextCheck))
			return false;
		if (nextNotification == null) {
			if (other.nextNotification != null)
				return false;
		} else if (!nextNotification.equals(other.nextNotification))
			return false;
		if (normalCheckInterval == null) {
			if (other.normalCheckInterval != null)
				return false;
		} else if (!normalCheckInterval.equals(other.normalCheckInterval))
			return false;
		if (notificationsEnabled == null) {
			if (other.notificationsEnabled != null)
				return false;
		} else if (!notificationsEnabled.equals(other.notificationsEnabled))
			return false;
		if (output == null) {
			if (other.output != null)
				return false;
		} else if (!output.equals(other.output))
			return false;
		if (passiveChecksEnabled == null) {
			if (other.passiveChecksEnabled != null)
				return false;
		} else if (!passiveChecksEnabled.equals(other.passiveChecksEnabled))
			return false;
		if (percentStateChange == null) {
			if (other.percentStateChange != null)
				return false;
		} else if (!percentStateChange.equals(other.percentStateChange))
			return false;
		if (perfdata == null) {
			if (other.perfdata != null)
				return false;
		} else if (!perfdata.equals(other.perfdata))
			return false;
		if (problemHasBeenAcknowledged == null) {
			if (other.problemHasBeenAcknowledged != null)
				return false;
		} else if (!problemHasBeenAcknowledged
				.equals(other.problemHasBeenAcknowledged))
			return false;
		if (retryCheckInterval == null) {
			if (other.retryCheckInterval != null)
				return false;
		} else if (!retryCheckInterval.equals(other.retryCheckInterval))
			return false;
		if (shouldBeScheduled == null) {
			if (other.shouldBeScheduled != null)
				return false;
		} else if (!shouldBeScheduled.equals(other.shouldBeScheduled))
			return false;
		if (stateType == null) {
			if (other.stateType != null)
				return false;
		} else if (!stateType.equals(other.stateType))
			return false;
		if (statusUpdateTime == null) {
			if (other.statusUpdateTime != null)
				return false;
		} else if (!statusUpdateTime.equals(other.statusUpdateTime))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorTermdevserviceStatus [acknowledgementType="
				+ acknowledgementType + ", activeChecksEnabled="
				+ activeChecksEnabled + ", checkCommand=" + checkCommand
				+ ", checkTimeperiodId=" + checkTimeperiodId + ", checkType="
				+ checkType + ", currentCheckAttempt=" + currentCheckAttempt
				+ ", currentNotificationNumber=" + currentNotificationNumber
				+ ", currentState=" + currentState + ", devserviceId="
				+ devserviceId + ", eventHandler=" + eventHandler
				+ ", eventHandlerEnabled=" + eventHandlerEnabled
				+ ", executionTime=" + executionTime
				+ ", flapDetectionEnabled=" + flapDetectionEnabled
				+ ", hasBeenChecked=" + hasBeenChecked + ", isFlapping="
				+ isFlapping + ", lastCheck=" + lastCheck + ", lastHardState="
				+ lastHardState + ", lastHardStateChange="
				+ lastHardStateChange + ", lastNotification="
				+ lastNotification + ", lastStateChange=" + lastStateChange
				+ ", lastTimeCritical=" + lastTimeCritical + ", lastTimeOk="
				+ lastTimeOk + ", lastTimeUnknow=" + lastTimeUnknow
				+ ", lastTimeWarning=" + lastTimeWarning + ", latency="
				+ latency + ", maxCheckAttempts=" + maxCheckAttempts
				+ ", nextCheck=" + nextCheck + ", nextNotification="
				+ nextNotification + ", normalCheckInterval="
				+ normalCheckInterval + ", notificationsEnabled="
				+ notificationsEnabled + ", output=" + output
				+ ", passiveChecksEnabled=" + passiveChecksEnabled
				+ ", percentStateChange=" + percentStateChange + ", perfdata="
				+ perfdata + ", problemHasBeenAcknowledged="
				+ problemHasBeenAcknowledged + ", retryCheckInterval="
				+ retryCheckInterval + ", shouldBeScheduled="
				+ shouldBeScheduled + ", stateType=" + stateType
				+ ", statusUpdateTime=" + statusUpdateTime + "]";
	}

}