package org.king.termdev.domain;

import org.king.support.domain.MonitorCommands;
import org.king.template.domain.MonitorTimePeriods;

/**
 * AbstractMonitorTermdevService entity provides the base persistence definition
 * of the MonitorTermdevService entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorTermdevService extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer devserviceId;
	private Integer deviceId;
	private String devserviceName;
	private MonitorCommands checkCommand = new MonitorCommands();
	private String checkCommandArgs;
	private Integer eventhandlerCommandId;
	private String eventhandlerCommandArgs;
	private MonitorTimePeriods notificationTimeperiod = new MonitorTimePeriods();
	private MonitorTimePeriods checkTimeperiod = new MonitorTimePeriods();
	private Double checkInterval;
	private Double retryInterval;
	private Integer maxCheckAttempts;
	private Double notificationInterval;
	private Integer notifyOnWarning;
	private Integer notifyOnUnknown;
	private Integer notifyOnCritical;
	private Integer notifyOnRecovery;
	private Integer notifyOnFlapping;
	private Integer notifyOnDowntime;
	private Integer flapDetectionEnabled;
	private Integer flapDetectionOnOk;
	private Integer flapDetectionOnWarning;
	private Integer flapDetectionOnUnknown;
	private Integer flapDetectionOnCritical;
	private Double lowFlapThreshold;
	private Double highFlapThreshold;
	private Integer freshnessChecksEnabled;
	private Integer freshnessThreshold;
	private Integer passiveChecksEnabled;
	private Integer eventHandlerEnabled;
	private Integer activeChecksEnabled;
	private Integer retainStatusInformation;
	private Integer retainNonstatusInformation;
	private Integer notificationsEnabled;
	private String notes;
	private String notesUrl;
	private String actionurl;

    // Constructors

	/** default constructor */
	public AbstractMonitorTermdevService() {
	}

	/** full constructor */
	public AbstractMonitorTermdevService(Integer deviceId,
			String devserviceName, MonitorCommands checkCommand,
			String checkCommandArgs, Integer eventhandlerCommandId,
			String eventhandlerCommandArgs,
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
		this.deviceId = deviceId;
		this.devserviceName = devserviceName;
		this.checkCommand = checkCommand;
		this.checkCommandArgs = checkCommandArgs;
		this.eventhandlerCommandId = eventhandlerCommandId;
		this.eventhandlerCommandArgs = eventhandlerCommandArgs;
		this.notificationTimeperiod = notificationTimeperiod;
		this.checkTimeperiod = checkTimeperiod;
		this.checkInterval = checkInterval;
		this.retryInterval = retryInterval;
		this.maxCheckAttempts = maxCheckAttempts;
		this.notificationInterval = notificationInterval;
		this.notifyOnWarning = notifyOnWarning;
		this.notifyOnUnknown = notifyOnUnknown;
		this.notifyOnCritical = notifyOnCritical;
		this.notifyOnRecovery = notifyOnRecovery;
		this.notifyOnFlapping = notifyOnFlapping;
		this.notifyOnDowntime = notifyOnDowntime;
		this.flapDetectionEnabled = flapDetectionEnabled;
		this.flapDetectionOnOk = flapDetectionOnOk;
		this.flapDetectionOnWarning = flapDetectionOnWarning;
		this.flapDetectionOnUnknown = flapDetectionOnUnknown;
		this.flapDetectionOnCritical = flapDetectionOnCritical;
		this.lowFlapThreshold = lowFlapThreshold;
		this.highFlapThreshold = highFlapThreshold;
		this.freshnessChecksEnabled = freshnessChecksEnabled;
		this.freshnessThreshold = freshnessThreshold;
		this.passiveChecksEnabled = passiveChecksEnabled;
		this.eventHandlerEnabled = eventHandlerEnabled;
		this.activeChecksEnabled = activeChecksEnabled;
		this.retainStatusInformation = retainStatusInformation;
		this.retainNonstatusInformation = retainNonstatusInformation;
		this.notificationsEnabled = notificationsEnabled;
		this.notes = notes;
		this.notesUrl = notesUrl;
		this.actionurl = actionurl;
	}

    // Property accessors

	public Integer getDevserviceId() {
		return this.devserviceId;
	}

	public void setDevserviceId(Integer devserviceId) {
		this.devserviceId = devserviceId;
	}

	public Integer getDeviceId() {
		return this.deviceId;
	}

	public void setDeviceId(Integer deviceId) {
		this.deviceId = deviceId;
	}

	public String getDevserviceName() {
		return this.devserviceName;
	}

	public void setDevserviceName(String devserviceName) {
		this.devserviceName = devserviceName;
	}

	public MonitorCommands getCheckCommand() {
		return this.checkCommand;
	}

	public void setCheckCommand(MonitorCommands checkCommand) {
		this.checkCommand = checkCommand;
	}

	public String getCheckCommandArgs() {
		return this.checkCommandArgs;
	}

	public void setCheckCommandArgs(String checkCommandArgs) {
		this.checkCommandArgs = checkCommandArgs;
	}

	public Integer getEventhandlerCommandId() {
		return this.eventhandlerCommandId;
	}

	public void setEventhandlerCommandId(Integer eventhandlerCommandId) {
		this.eventhandlerCommandId = eventhandlerCommandId;
	}

	public String getEventhandlerCommandArgs() {
		return this.eventhandlerCommandArgs;
	}

	public void setEventhandlerCommandArgs(String eventhandlerCommandArgs) {
		this.eventhandlerCommandArgs = eventhandlerCommandArgs;
	}

	public MonitorTimePeriods getNotificationTimeperiod() {
		return this.notificationTimeperiod;
	}

	public void setNotificationTimeperiod(MonitorTimePeriods notificationTimeperiod) {
		this.notificationTimeperiod = notificationTimeperiod;
	}

	public MonitorTimePeriods getCheckTimeperiod() {
		return this.checkTimeperiod;
	}

	public void setCheckTimeperiod(MonitorTimePeriods checkTimeperiod) {
		this.checkTimeperiod = checkTimeperiod;
	}

	public Double getCheckInterval() {
		return this.checkInterval;
	}

	public void setCheckInterval(Double checkInterval) {
		this.checkInterval = checkInterval;
	}

	public Double getRetryInterval() {
		return this.retryInterval;
	}

	public void setRetryInterval(Double retryInterval) {
		this.retryInterval = retryInterval;
	}

	public Integer getMaxCheckAttempts() {
		return this.maxCheckAttempts;
	}

	public void setMaxCheckAttempts(Integer maxCheckAttempts) {
		this.maxCheckAttempts = maxCheckAttempts;
	}

	public Double getNotificationInterval() {
		return this.notificationInterval;
	}

	public void setNotificationInterval(Double notificationInterval) {
		this.notificationInterval = notificationInterval;
	}

	public Integer getNotifyOnWarning() {
		return this.notifyOnWarning;
	}

	public void setNotifyOnWarning(Integer notifyOnWarning) {
		this.notifyOnWarning = notifyOnWarning;
	}

	public Integer getNotifyOnUnknown() {
		return this.notifyOnUnknown;
	}

	public void setNotifyOnUnknown(Integer notifyOnUnknown) {
		this.notifyOnUnknown = notifyOnUnknown;
	}

	public Integer getNotifyOnCritical() {
		return this.notifyOnCritical;
	}

	public void setNotifyOnCritical(Integer notifyOnCritical) {
		this.notifyOnCritical = notifyOnCritical;
	}

	public Integer getNotifyOnRecovery() {
		return this.notifyOnRecovery;
	}

	public void setNotifyOnRecovery(Integer notifyOnRecovery) {
		this.notifyOnRecovery = notifyOnRecovery;
	}

	public Integer getNotifyOnFlapping() {
		return this.notifyOnFlapping;
	}

	public void setNotifyOnFlapping(Integer notifyOnFlapping) {
		this.notifyOnFlapping = notifyOnFlapping;
	}

	public Integer getNotifyOnDowntime() {
		return this.notifyOnDowntime;
	}

	public void setNotifyOnDowntime(Integer notifyOnDowntime) {
		this.notifyOnDowntime = notifyOnDowntime;
	}

	public Integer getFlapDetectionEnabled() {
		return this.flapDetectionEnabled;
	}

	public void setFlapDetectionEnabled(Integer flapDetectionEnabled) {
		this.flapDetectionEnabled = flapDetectionEnabled;
	}

	public Integer getFlapDetectionOnOk() {
		return this.flapDetectionOnOk;
	}

	public void setFlapDetectionOnOk(Integer flapDetectionOnOk) {
		this.flapDetectionOnOk = flapDetectionOnOk;
	}

	public Integer getFlapDetectionOnWarning() {
		return this.flapDetectionOnWarning;
	}

	public void setFlapDetectionOnWarning(Integer flapDetectionOnWarning) {
		this.flapDetectionOnWarning = flapDetectionOnWarning;
	}

	public Integer getFlapDetectionOnUnknown() {
		return this.flapDetectionOnUnknown;
	}

	public void setFlapDetectionOnUnknown(Integer flapDetectionOnUnknown) {
		this.flapDetectionOnUnknown = flapDetectionOnUnknown;
	}

	public Integer getFlapDetectionOnCritical() {
		return this.flapDetectionOnCritical;
	}

	public void setFlapDetectionOnCritical(Integer flapDetectionOnCritical) {
		this.flapDetectionOnCritical = flapDetectionOnCritical;
	}

	public Double getLowFlapThreshold() {
		return this.lowFlapThreshold;
	}

	public void setLowFlapThreshold(Double lowFlapThreshold) {
		this.lowFlapThreshold = lowFlapThreshold;
	}

	public Double getHighFlapThreshold() {
		return this.highFlapThreshold;
	}

	public void setHighFlapThreshold(Double highFlapThreshold) {
		this.highFlapThreshold = highFlapThreshold;
	}

	public Integer getFreshnessChecksEnabled() {
		return this.freshnessChecksEnabled;
	}

	public void setFreshnessChecksEnabled(Integer freshnessChecksEnabled) {
		this.freshnessChecksEnabled = freshnessChecksEnabled;
	}

	public Integer getFreshnessThreshold() {
		return this.freshnessThreshold;
	}

	public void setFreshnessThreshold(Integer freshnessThreshold) {
		this.freshnessThreshold = freshnessThreshold;
	}

	public Integer getPassiveChecksEnabled() {
		return this.passiveChecksEnabled;
	}

	public void setPassiveChecksEnabled(Integer passiveChecksEnabled) {
		this.passiveChecksEnabled = passiveChecksEnabled;
	}

	public Integer getEventHandlerEnabled() {
		return this.eventHandlerEnabled;
	}

	public void setEventHandlerEnabled(Integer eventHandlerEnabled) {
		this.eventHandlerEnabled = eventHandlerEnabled;
	}

	public Integer getActiveChecksEnabled() {
		return this.activeChecksEnabled;
	}

	public void setActiveChecksEnabled(Integer activeChecksEnabled) {
		this.activeChecksEnabled = activeChecksEnabled;
	}

	public Integer getRetainStatusInformation() {
		return this.retainStatusInformation;
	}

	public void setRetainStatusInformation(Integer retainStatusInformation) {
		this.retainStatusInformation = retainStatusInformation;
	}

	public Integer getRetainNonstatusInformation() {
		return this.retainNonstatusInformation;
	}

	public void setRetainNonstatusInformation(
			Integer retainNonstatusInformation) {
		this.retainNonstatusInformation = retainNonstatusInformation;
	}

	public Integer getNotificationsEnabled() {
		return this.notificationsEnabled;
	}

	public void setNotificationsEnabled(Integer notificationsEnabled) {
		this.notificationsEnabled = notificationsEnabled;
	}

	public String getNotes() {
		return this.notes;
	}

	public void setNotes(String notes) {
		this.notes = notes;
	}

	public String getNotesUrl() {
		return this.notesUrl;
	}

	public void setNotesUrl(String notesUrl) {
		this.notesUrl = notesUrl;
	}

	public String getActionurl() {
		return this.actionurl;
	}

	public void setActionurl(String actionurl) {
		this.actionurl = actionurl;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((actionurl == null) ? 0 : actionurl.hashCode());
		result = prime
				* result
				+ ((activeChecksEnabled == null) ? 0 : activeChecksEnabled
						.hashCode());
		result = prime
				* result
				+ ((checkCommandArgs == null) ? 0 : checkCommandArgs.hashCode());
		result = prime * result
				+ ((checkCommand == null) ? 0 : checkCommand.hashCode());
		result = prime * result
				+ ((checkInterval == null) ? 0 : checkInterval.hashCode());
		result = prime
				* result
				+ ((checkTimeperiod == null) ? 0 : checkTimeperiod
						.hashCode());
		result = prime * result
				+ ((deviceId == null) ? 0 : deviceId.hashCode());
		result = prime * result
				+ ((devserviceId == null) ? 0 : devserviceId.hashCode());
		result = prime * result
				+ ((devserviceName == null) ? 0 : devserviceName.hashCode());
		result = prime
				* result
				+ ((eventHandlerEnabled == null) ? 0 : eventHandlerEnabled
						.hashCode());
		result = prime
				* result
				+ ((eventhandlerCommandArgs == null) ? 0
						: eventhandlerCommandArgs.hashCode());
		result = prime
				* result
				+ ((eventhandlerCommandId == null) ? 0 : eventhandlerCommandId
						.hashCode());
		result = prime
				* result
				+ ((flapDetectionEnabled == null) ? 0 : flapDetectionEnabled
						.hashCode());
		result = prime
				* result
				+ ((flapDetectionOnCritical == null) ? 0
						: flapDetectionOnCritical.hashCode());
		result = prime
				* result
				+ ((flapDetectionOnOk == null) ? 0 : flapDetectionOnOk
						.hashCode());
		result = prime
				* result
				+ ((flapDetectionOnUnknown == null) ? 0
						: flapDetectionOnUnknown.hashCode());
		result = prime
				* result
				+ ((flapDetectionOnWarning == null) ? 0
						: flapDetectionOnWarning.hashCode());
		result = prime
				* result
				+ ((freshnessChecksEnabled == null) ? 0
						: freshnessChecksEnabled.hashCode());
		result = prime
				* result
				+ ((freshnessThreshold == null) ? 0 : freshnessThreshold
						.hashCode());
		result = prime
				* result
				+ ((highFlapThreshold == null) ? 0 : highFlapThreshold
						.hashCode());
		result = prime
				* result
				+ ((lowFlapThreshold == null) ? 0 : lowFlapThreshold.hashCode());
		result = prime
				* result
				+ ((maxCheckAttempts == null) ? 0 : maxCheckAttempts.hashCode());
		result = prime * result + ((notes == null) ? 0 : notes.hashCode());
		result = prime * result
				+ ((notesUrl == null) ? 0 : notesUrl.hashCode());
		result = prime
				* result
				+ ((notificationInterval == null) ? 0 : notificationInterval
						.hashCode());
		result = prime
				* result
				+ ((notificationTimeperiod == null) ? 0
						: notificationTimeperiod.hashCode());
		result = prime
				* result
				+ ((notificationsEnabled == null) ? 0 : notificationsEnabled
						.hashCode());
		result = prime
				* result
				+ ((notifyOnCritical == null) ? 0 : notifyOnCritical.hashCode());
		result = prime
				* result
				+ ((notifyOnDowntime == null) ? 0 : notifyOnDowntime.hashCode());
		result = prime
				* result
				+ ((notifyOnFlapping == null) ? 0 : notifyOnFlapping.hashCode());
		result = prime
				* result
				+ ((notifyOnRecovery == null) ? 0 : notifyOnRecovery.hashCode());
		result = prime * result
				+ ((notifyOnUnknown == null) ? 0 : notifyOnUnknown.hashCode());
		result = prime * result
				+ ((notifyOnWarning == null) ? 0 : notifyOnWarning.hashCode());
		result = prime
				* result
				+ ((passiveChecksEnabled == null) ? 0 : passiveChecksEnabled
						.hashCode());
		result = prime
				* result
				+ ((retainNonstatusInformation == null) ? 0
						: retainNonstatusInformation.hashCode());
		result = prime
				* result
				+ ((retainStatusInformation == null) ? 0
						: retainStatusInformation.hashCode());
		result = prime * result
				+ ((retryInterval == null) ? 0 : retryInterval.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorTermdevService))
			return false;
		AbstractMonitorTermdevService other = (AbstractMonitorTermdevService) obj;
		if (actionurl == null) {
			if (other.actionurl != null)
				return false;
		} else if (!actionurl.equals(other.actionurl))
			return false;
		if (activeChecksEnabled == null) {
			if (other.activeChecksEnabled != null)
				return false;
		} else if (!activeChecksEnabled.equals(other.activeChecksEnabled))
			return false;
		if (checkCommandArgs == null) {
			if (other.checkCommandArgs != null)
				return false;
		} else if (!checkCommandArgs.equals(other.checkCommandArgs))
			return false;
		if (checkCommand == null) {
			if (other.checkCommand != null)
				return false;
		} else if (!checkCommand.equals(other.checkCommand))
			return false;
		if (checkInterval == null) {
			if (other.checkInterval != null)
				return false;
		} else if (!checkInterval.equals(other.checkInterval))
			return false;
		if (checkTimeperiod == null) {
			if (other.checkTimeperiod != null)
				return false;
		} else if (!checkTimeperiod.equals(other.checkTimeperiod))
			return false;
		if (deviceId == null) {
			if (other.deviceId != null)
				return false;
		} else if (!deviceId.equals(other.deviceId))
			return false;
		if (devserviceId == null) {
			if (other.devserviceId != null)
				return false;
		} else if (!devserviceId.equals(other.devserviceId))
			return false;
		if (devserviceName == null) {
			if (other.devserviceName != null)
				return false;
		} else if (!devserviceName.equals(other.devserviceName))
			return false;
		if (eventHandlerEnabled == null) {
			if (other.eventHandlerEnabled != null)
				return false;
		} else if (!eventHandlerEnabled.equals(other.eventHandlerEnabled))
			return false;
		if (eventhandlerCommandArgs == null) {
			if (other.eventhandlerCommandArgs != null)
				return false;
		} else if (!eventhandlerCommandArgs
				.equals(other.eventhandlerCommandArgs))
			return false;
		if (eventhandlerCommandId == null) {
			if (other.eventhandlerCommandId != null)
				return false;
		} else if (!eventhandlerCommandId.equals(other.eventhandlerCommandId))
			return false;
		if (flapDetectionEnabled == null) {
			if (other.flapDetectionEnabled != null)
				return false;
		} else if (!flapDetectionEnabled.equals(other.flapDetectionEnabled))
			return false;
		if (flapDetectionOnCritical == null) {
			if (other.flapDetectionOnCritical != null)
				return false;
		} else if (!flapDetectionOnCritical
				.equals(other.flapDetectionOnCritical))
			return false;
		if (flapDetectionOnOk == null) {
			if (other.flapDetectionOnOk != null)
				return false;
		} else if (!flapDetectionOnOk.equals(other.flapDetectionOnOk))
			return false;
		if (flapDetectionOnUnknown == null) {
			if (other.flapDetectionOnUnknown != null)
				return false;
		} else if (!flapDetectionOnUnknown.equals(other.flapDetectionOnUnknown))
			return false;
		if (flapDetectionOnWarning == null) {
			if (other.flapDetectionOnWarning != null)
				return false;
		} else if (!flapDetectionOnWarning.equals(other.flapDetectionOnWarning))
			return false;
		if (freshnessChecksEnabled == null) {
			if (other.freshnessChecksEnabled != null)
				return false;
		} else if (!freshnessChecksEnabled.equals(other.freshnessChecksEnabled))
			return false;
		if (freshnessThreshold == null) {
			if (other.freshnessThreshold != null)
				return false;
		} else if (!freshnessThreshold.equals(other.freshnessThreshold))
			return false;
		if (highFlapThreshold == null) {
			if (other.highFlapThreshold != null)
				return false;
		} else if (!highFlapThreshold.equals(other.highFlapThreshold))
			return false;
		if (lowFlapThreshold == null) {
			if (other.lowFlapThreshold != null)
				return false;
		} else if (!lowFlapThreshold.equals(other.lowFlapThreshold))
			return false;
		if (maxCheckAttempts == null) {
			if (other.maxCheckAttempts != null)
				return false;
		} else if (!maxCheckAttempts.equals(other.maxCheckAttempts))
			return false;
		if (notes == null) {
			if (other.notes != null)
				return false;
		} else if (!notes.equals(other.notes))
			return false;
		if (notesUrl == null) {
			if (other.notesUrl != null)
				return false;
		} else if (!notesUrl.equals(other.notesUrl))
			return false;
		if (notificationInterval == null) {
			if (other.notificationInterval != null)
				return false;
		} else if (!notificationInterval.equals(other.notificationInterval))
			return false;
		if (notificationTimeperiod == null) {
			if (other.notificationTimeperiod != null)
				return false;
		} else if (!notificationTimeperiod
				.equals(other.notificationTimeperiod))
			return false;
		if (notificationsEnabled == null) {
			if (other.notificationsEnabled != null)
				return false;
		} else if (!notificationsEnabled.equals(other.notificationsEnabled))
			return false;
		if (notifyOnCritical == null) {
			if (other.notifyOnCritical != null)
				return false;
		} else if (!notifyOnCritical.equals(other.notifyOnCritical))
			return false;
		if (notifyOnDowntime == null) {
			if (other.notifyOnDowntime != null)
				return false;
		} else if (!notifyOnDowntime.equals(other.notifyOnDowntime))
			return false;
		if (notifyOnFlapping == null) {
			if (other.notifyOnFlapping != null)
				return false;
		} else if (!notifyOnFlapping.equals(other.notifyOnFlapping))
			return false;
		if (notifyOnRecovery == null) {
			if (other.notifyOnRecovery != null)
				return false;
		} else if (!notifyOnRecovery.equals(other.notifyOnRecovery))
			return false;
		if (notifyOnUnknown == null) {
			if (other.notifyOnUnknown != null)
				return false;
		} else if (!notifyOnUnknown.equals(other.notifyOnUnknown))
			return false;
		if (notifyOnWarning == null) {
			if (other.notifyOnWarning != null)
				return false;
		} else if (!notifyOnWarning.equals(other.notifyOnWarning))
			return false;
		if (passiveChecksEnabled == null) {
			if (other.passiveChecksEnabled != null)
				return false;
		} else if (!passiveChecksEnabled.equals(other.passiveChecksEnabled))
			return false;
		if (retainNonstatusInformation == null) {
			if (other.retainNonstatusInformation != null)
				return false;
		} else if (!retainNonstatusInformation
				.equals(other.retainNonstatusInformation))
			return false;
		if (retainStatusInformation == null) {
			if (other.retainStatusInformation != null)
				return false;
		} else if (!retainStatusInformation
				.equals(other.retainStatusInformation))
			return false;
		if (retryInterval == null) {
			if (other.retryInterval != null)
				return false;
		} else if (!retryInterval.equals(other.retryInterval))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorTermdevService [actionurl=" + actionurl
				+ ", activeChecksEnabled=" + activeChecksEnabled
				+ ", checkCommandArgs=" + checkCommandArgs
				+ ", checkCommand=" + checkCommand + ", checkInterval="
				+ checkInterval + ", checkTimeperiod=" + checkTimeperiod
				+ ", deviceId=" + deviceId + ", devserviceId=" + devserviceId
				+ ", devserviceName=" + devserviceName
				+ ", eventHandlerEnabled=" + eventHandlerEnabled
				+ ", eventhandlerCommandArgs=" + eventhandlerCommandArgs
				+ ", eventhandlerCommandId=" + eventhandlerCommandId
				+ ", flapDetectionEnabled=" + flapDetectionEnabled
				+ ", flapDetectionOnCritical=" + flapDetectionOnCritical
				+ ", flapDetectionOnOk=" + flapDetectionOnOk
				+ ", flapDetectionOnUnknown=" + flapDetectionOnUnknown
				+ ", flapDetectionOnWarning=" + flapDetectionOnWarning
				+ ", freshnessChecksEnabled=" + freshnessChecksEnabled
				+ ", freshnessThreshold=" + freshnessThreshold
				+ ", highFlapThreshold=" + highFlapThreshold
				+ ", lowFlapThreshold=" + lowFlapThreshold
				+ ", maxCheckAttempts=" + maxCheckAttempts + ", notes=" + notes
				+ ", notesUrl=" + notesUrl + ", notificationInterval="
				+ notificationInterval + ", notificationTimeperiod="
				+ notificationTimeperiod + ", notificationsEnabled="
				+ notificationsEnabled + ", notifyOnCritical="
				+ notifyOnCritical + ", notifyOnDowntime=" + notifyOnDowntime
				+ ", notifyOnFlapping=" + notifyOnFlapping
				+ ", notifyOnRecovery=" + notifyOnRecovery
				+ ", notifyOnUnknown=" + notifyOnUnknown + ", notifyOnWarning="
				+ notifyOnWarning + ", passiveChecksEnabled="
				+ passiveChecksEnabled + ", retainNonstatusInformation="
				+ retainNonstatusInformation + ", retainStatusInformation="
				+ retainStatusInformation + ", retryInterval=" + retryInterval
				+ "]";
	}

}