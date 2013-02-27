package org.king.template.domain;

import org.king.support.domain.MonitorContactgroups;

/**
 * AbstractMonitorTermdevTemplate entity provides the base persistence
 * definition of the MonitorTermdevTemplate entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorTermdevTemplate extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer templateId;
	private String templateName;
	private Integer notificationsEnabled;
	private MonitorTimePeriods notificationPeriod = new MonitorTimePeriods();
	private MonitorTimePeriods checkPeriod = new MonitorTimePeriods();
	private Double checkInterval;
	private Double retryInterval;
	private Integer maxCheckAttempts;
	private String checkCommand;
	private Integer notificationInterval;
	private String notificationOptions;
	private MonitorContactgroups contactGroups = new MonitorContactgroups();
	private Integer activeChecksEnabled;
	private Integer passiveChecksEnabled;
	private Integer notifyOnDown;
	private Integer notifyOnRecovery;

	// Constructors

	/**
	 * default constructor
	 */
	public AbstractMonitorTermdevTemplate() {
	}

	/**
	 * full constructor
	 */
	public AbstractMonitorTermdevTemplate(String templateName,
			Integer notificationsEnabled,
			MonitorTimePeriods notificationPeriod,
			MonitorTimePeriods checkPeriod, Double checkInterval,
			Double retryInterval, Integer maxCheckAttempts,
			String checkCommand, Integer notificationInterval,
			String notificationOptions, MonitorContactgroups contactGroups,
			Integer activeChecksEnabled,Integer passiveChecksEnabled, Integer notifyOnDown,
			Integer notifyOnRecovery) {
		this.templateName = templateName;
		this.notificationsEnabled = notificationsEnabled;
		this.notificationPeriod = notificationPeriod;
		this.checkPeriod = checkPeriod;
		this.checkInterval = checkInterval;
		this.retryInterval = retryInterval;
		this.maxCheckAttempts = maxCheckAttempts;
		this.checkCommand = checkCommand;
		this.notificationInterval = notificationInterval;
		this.notificationOptions = notificationOptions;
		this.contactGroups = contactGroups;
		this.activeChecksEnabled = activeChecksEnabled;
		this.passiveChecksEnabled = passiveChecksEnabled;
		this.notifyOnDown = notifyOnDown;
		this.notifyOnRecovery = notifyOnRecovery;
	}

	// Property accessors

	public Integer getTemplateId() {
		return this.templateId;
	}


	public void setTemplateId(Integer templateId) {
		this.templateId = templateId;
	}

	public String getTemplateName() {
		return this.templateName;
	}

	public void setTemplateName(String templateName) {
		this.templateName = templateName;
	}

	public Integer getNotificationsEnabled() {
		return this.notificationsEnabled;
	}

	public void setNotificationsEnabled(Integer notificationsEnabled) {
		this.notificationsEnabled = notificationsEnabled;
	}

	public MonitorTimePeriods getNotificationPeriod() {
		return this.notificationPeriod;
	}

	public void setNotificationPeriod(MonitorTimePeriods notificationPeriod) {
		this.notificationPeriod = notificationPeriod;
	}

	public MonitorTimePeriods getCheckPeriod() {
		return this.checkPeriod;
	}

	public void setCheckPeriod(MonitorTimePeriods checkPeriod) {
		this.checkPeriod = checkPeriod;
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

	public String getCheckCommand() {
		return this.checkCommand;
	}

	public void setCheckCommand(String checkCommand) {
		this.checkCommand = checkCommand;
	}

	public Integer getNotificationInterval() {
		return this.notificationInterval;
	}

	public void setNotificationInterval(Integer notificationInterval) {
		this.notificationInterval = notificationInterval;
	}

	public String getNotificationOptions() {
		return this.notificationOptions;
	}

	public void setNotificationOptions(String notificationOptions) {
		this.notificationOptions = notificationOptions;
	}

	public MonitorContactgroups getContactGroups() {
		return this.contactGroups;
	}

	public void setContactGroups(MonitorContactgroups contactGroups) {
		this.contactGroups = contactGroups;
	}

	public Integer getNotifyOnDown() {
		return notifyOnDown;
	}

	public void setNotifyOnDown(Integer notifyOnDown) {
		this.notifyOnDown = notifyOnDown;
	}

	public Integer getNotifyOnRecovery() {
		return notifyOnRecovery;
	}

	public void setNotifyOnRecovery(Integer notifyOnRecovery) {
		this.notifyOnRecovery = notifyOnRecovery;
	}


	public Integer getActiveChecksEnabled() {
		return activeChecksEnabled;
	}

	public void setActiveChecksEnabled(Integer activeChecksEnabled) {
		this.activeChecksEnabled = activeChecksEnabled;
	}

	public Integer getPassiveChecksEnabled() {
		return passiveChecksEnabled;
	}

	public void setPassiveChecksEnabled(Integer passiveChecksEnabled) {
		this.passiveChecksEnabled = passiveChecksEnabled;
	}

	@Override
	public String toString() {
		return "AbstractMonitorTermdevTemplate [activeChecksEnabled="
				+ activeChecksEnabled + ", checkCommand=" + checkCommand
				+ ", checkInterval="
				+ checkInterval + ", checkPeriod=" + checkPeriod
				+ ", contactGroups=" + contactGroups + ", maxCheckAttempts="
				+ maxCheckAttempts + ", notificationInterval="
				+ notificationInterval + ", notificationOptions="
				+ notificationOptions + ", notificationPeriod="
				+ notificationPeriod + ", notificationsEnabled="
				+ notificationsEnabled + ", notifyOnDown=" + notifyOnDown
				+ ", notifyOnRecovery=" + notifyOnRecovery
				+ ", passiveChecksEnabled=" + passiveChecksEnabled
				+ ", retryInterval=" + retryInterval + ", templateId="
				+ templateId + ", templateName=" + templateName + "]";
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime
				* result
				+ ((activeChecksEnabled == null) ? 0 : activeChecksEnabled
						.hashCode());
		result = prime * result
				+ ((checkCommand == null) ? 0 : checkCommand.hashCode());

		result = prime * result
				+ ((checkInterval == null) ? 0 : checkInterval.hashCode());
		result = prime * result
				+ ((checkPeriod == null) ? 0 : checkPeriod.hashCode());
		result = prime * result
				+ ((contactGroups == null) ? 0 : contactGroups.hashCode());
		result = prime
				* result
				+ ((maxCheckAttempts == null) ? 0 : maxCheckAttempts.hashCode());
		result = prime
				* result
				+ ((notificationInterval == null) ? 0 : notificationInterval
						.hashCode());
		result = prime
				* result
				+ ((notificationOptions == null) ? 0 : notificationOptions
						.hashCode());
		result = prime
				* result
				+ ((notificationPeriod == null) ? 0 : notificationPeriod
						.hashCode());
		result = prime
				* result
				+ ((notificationsEnabled == null) ? 0 : notificationsEnabled
						.hashCode());
		result = prime * result
				+ ((notifyOnDown == null) ? 0 : notifyOnDown.hashCode());
		result = prime
				* result
				+ ((notifyOnRecovery == null) ? 0 : notifyOnRecovery.hashCode());
		result = prime
				* result
				+ ((passiveChecksEnabled == null) ? 0 : passiveChecksEnabled
						.hashCode());
		result = prime * result
				+ ((retryInterval == null) ? 0 : retryInterval.hashCode());
		result = prime * result
				+ ((templateId == null) ? 0 : templateId.hashCode());
		result = prime * result
				+ ((templateName == null) ? 0 : templateName.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorTermdevTemplate))
			return false;
		AbstractMonitorTermdevTemplate other = (AbstractMonitorTermdevTemplate) obj;
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
		if (checkInterval == null) {
			if (other.checkInterval != null)
				return false;
		} else if (!checkInterval.equals(other.checkInterval))
			return false;
		if (checkPeriod == null) {
			if (other.checkPeriod != null)
				return false;
		} else if (!checkPeriod.equals(other.checkPeriod))
			return false;
		if (contactGroups == null) {
			if (other.contactGroups != null)
				return false;
		} else if (!contactGroups.equals(other.contactGroups))
			return false;
		if (maxCheckAttempts == null) {
			if (other.maxCheckAttempts != null)
				return false;
		} else if (!maxCheckAttempts.equals(other.maxCheckAttempts))
			return false;
		if (notificationInterval == null) {
			if (other.notificationInterval != null)
				return false;
		} else if (!notificationInterval.equals(other.notificationInterval))
			return false;
		if (notificationOptions == null) {
			if (other.notificationOptions != null)
				return false;
		} else if (!notificationOptions.equals(other.notificationOptions))
			return false;
		if (notificationPeriod == null) {
			if (other.notificationPeriod != null)
				return false;
		} else if (!notificationPeriod.equals(other.notificationPeriod))
			return false;
		if (notificationsEnabled == null) {
			if (other.notificationsEnabled != null)
				return false;
		} else if (!notificationsEnabled.equals(other.notificationsEnabled))
			return false;
		if (notifyOnDown == null) {
			if (other.notifyOnDown != null)
				return false;
		} else if (!notifyOnDown.equals(other.notifyOnDown))
			return false;
		if (notifyOnRecovery == null) {
			if (other.notifyOnRecovery != null)
				return false;
		} else if (!notifyOnRecovery.equals(other.notifyOnRecovery))
			return false;
		if (passiveChecksEnabled == null) {
			if (other.passiveChecksEnabled != null)
				return false;
		} else if (!passiveChecksEnabled.equals(other.passiveChecksEnabled))
			return false;
		if (retryInterval == null) {
			if (other.retryInterval != null)
				return false;
		} else if (!retryInterval.equals(other.retryInterval))
			return false;
		if (templateId == null) {
			if (other.templateId != null)
				return false;
		} else if (!templateId.equals(other.templateId))
			return false;
		if (templateName == null) {
			if (other.templateName != null)
				return false;
		} else if (!templateName.equals(other.templateName))
			return false;
		return true;
	}



}