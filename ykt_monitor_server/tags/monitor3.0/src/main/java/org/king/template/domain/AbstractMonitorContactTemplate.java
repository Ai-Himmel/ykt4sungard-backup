package org.king.template.domain;

/**
 * AbstractMonitorContactTemplate entity provides the base persistence
 * definition of the MonitorContactTemplate entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorContactTemplate extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer templateId;
	private String templateName;
	private MonitorTimePeriods serviceNotificationPeriod = new MonitorTimePeriods();
	private MonitorTimePeriods hostNotificationPeriod = new MonitorTimePeriods();
	private String serviceNotificationOptions;
	private String hostNotificationOptions;
	private String serviceNotificationCommands;
	private String hostNotificationCommands;

	// Constructors

	/** default constructor */
	public AbstractMonitorContactTemplate() {
	}

	/** full constructor */
	public AbstractMonitorContactTemplate(String templateName,
			MonitorTimePeriods serviceNotificationPeriod,
			MonitorTimePeriods hostNotificationPeriod,
			String serviceNotificationOptions, String hostNotificationOptions,
			String serviceNotificationCommands, String hostNotificationCommands) {
		this.templateName = templateName;
		this.serviceNotificationPeriod = serviceNotificationPeriod;
		this.hostNotificationPeriod = hostNotificationPeriod;
		this.serviceNotificationOptions = serviceNotificationOptions;
		this.hostNotificationOptions = hostNotificationOptions;
		this.serviceNotificationCommands = serviceNotificationCommands;
		this.hostNotificationCommands = hostNotificationCommands;
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

	public MonitorTimePeriods getServiceNotificationPeriod() {
		return this.serviceNotificationPeriod;
	}

	public void setServiceNotificationPeriod(
			MonitorTimePeriods serviceNotificationPeriod) {
		this.serviceNotificationPeriod = serviceNotificationPeriod;
	}

	public MonitorTimePeriods getHostNotificationPeriod() {
		return this.hostNotificationPeriod;
	}

	public void setHostNotificationPeriod(MonitorTimePeriods hostNotificationPeriod) {
		this.hostNotificationPeriod = hostNotificationPeriod;
	}

	public String getServiceNotificationOptions() {
		return this.serviceNotificationOptions;
	}

	public void setServiceNotificationOptions(String serviceNotificationOptions) {
		this.serviceNotificationOptions = serviceNotificationOptions;
	}

	public String getHostNotificationOptions() {
		return this.hostNotificationOptions;
	}

	public void setHostNotificationOptions(String hostNotificationOptions) {
		this.hostNotificationOptions = hostNotificationOptions;
	}

	public String getServiceNotificationCommands() {
		return this.serviceNotificationCommands;
	}

	public void setServiceNotificationCommands(
			String serviceNotificationCommands) {
		this.serviceNotificationCommands = serviceNotificationCommands;
	}

	public String getHostNotificationCommands() {
		return this.hostNotificationCommands;
	}

	public void setHostNotificationCommands(String hostNotificationCommands) {
		this.hostNotificationCommands = hostNotificationCommands;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime
				* result
				+ ((hostNotificationCommands == null) ? 0
						: hostNotificationCommands.hashCode());
		result = prime
				* result
				+ ((hostNotificationOptions == null) ? 0
						: hostNotificationOptions.hashCode());
		result = prime
				* result
				+ ((hostNotificationPeriod == null) ? 0
						: hostNotificationPeriod.hashCode());
		result = prime
				* result
				+ ((serviceNotificationCommands == null) ? 0
						: serviceNotificationCommands.hashCode());
		result = prime
				* result
				+ ((serviceNotificationOptions == null) ? 0
						: serviceNotificationOptions.hashCode());
		result = prime
				* result
				+ ((serviceNotificationPeriod == null) ? 0
						: serviceNotificationPeriod.hashCode());
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
		if (!(obj instanceof AbstractMonitorContactTemplate))
			return false;
		AbstractMonitorContactTemplate other = (AbstractMonitorContactTemplate) obj;
		if (hostNotificationCommands == null) {
			if (other.hostNotificationCommands != null)
				return false;
		} else if (!hostNotificationCommands
				.equals(other.hostNotificationCommands))
			return false;
		if (hostNotificationOptions == null) {
			if (other.hostNotificationOptions != null)
				return false;
		} else if (!hostNotificationOptions
				.equals(other.hostNotificationOptions))
			return false;
		if (hostNotificationPeriod == null) {
			if (other.hostNotificationPeriod != null)
				return false;
		} else if (!hostNotificationPeriod.equals(other.hostNotificationPeriod))
			return false;
		if (serviceNotificationCommands == null) {
			if (other.serviceNotificationCommands != null)
				return false;
		} else if (!serviceNotificationCommands
				.equals(other.serviceNotificationCommands))
			return false;
		if (serviceNotificationOptions == null) {
			if (other.serviceNotificationOptions != null)
				return false;
		} else if (!serviceNotificationOptions
				.equals(other.serviceNotificationOptions))
			return false;
		if (serviceNotificationPeriod == null) {
			if (other.serviceNotificationPeriod != null)
				return false;
		} else if (!serviceNotificationPeriod
				.equals(other.serviceNotificationPeriod))
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

	@Override
	public String toString() {
		return "AbstractMonitorContactTemplate [hostNotificationCommands="
				+ hostNotificationCommands + ", hostNotificationOptions="
				+ hostNotificationOptions + ", hostNotificationPeriod="
				+ hostNotificationPeriod + ", serviceNotificationCommands="
				+ serviceNotificationCommands + ", serviceNotificationOptions="
				+ serviceNotificationOptions + ", serviceNotificationPeriod="
				+ serviceNotificationPeriod + ", templateId=" + templateId
				+ ", templateName=" + templateName + "]";
	}

}