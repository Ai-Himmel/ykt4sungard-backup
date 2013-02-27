package org.king.support.domain;

import java.math.BigDecimal;

/**
 * AbstractMonitorNotifications entity provides the base persistence definition
 * of the MonitorNotifications entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorNotifications extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer notificationId;
	private Integer notificationType;
	private Integer objectId;
	private String notificationTime;
	private Integer state;
	private String output;
    private MonitorContactgroups contactGroup = new MonitorContactgroups();
	private Integer sendOrNot;

	// Constructors

	/** default constructor */
	public AbstractMonitorNotifications() {
	}

	/** full constructor */
	public AbstractMonitorNotifications(Integer notificationType,
			Integer objectId, String notificationTime, Integer state,
			String output, Integer sendOrNot) {
		this.notificationType = notificationType;
		this.objectId = objectId;
		this.notificationTime = notificationTime;
		this.state = state;
		this.output = output;
		this.sendOrNot = sendOrNot;
	}

	// Property accessors

	public Integer getNotificationId() {
		return this.notificationId;
	}

	public void setNotificationId(Integer notificationId) {
		this.notificationId = notificationId;
	}

	public Integer getNotificationType() {
		return this.notificationType;
	}

	public void setNotificationType(Integer notificationType) {
		this.notificationType = notificationType;
	}

	public Integer getObjectId() {
		return this.objectId;
	}

	public void setObjectId(Integer objectId) {
		this.objectId = objectId;
	}

	public String getNotificationTime() {
		return this.notificationTime;
	}

	public void setNotificationTime(String notificationTime) {
		this.notificationTime = notificationTime;
	}

	public Integer getState() {
		return this.state;
	}

	public void setState(Integer state) {
		this.state = state;
	}

	public String getOutput() {
		return this.output;
	}

	public void setOutput(String output) {
		this.output = output;
	}



	public MonitorContactgroups getContactGroup() {
		return contactGroup;
	}

	public void setContactGroup(MonitorContactgroups contactGroup) {
		this.contactGroup = contactGroup;
	}

	public Integer getSendOrNot() {
		return this.sendOrNot;
	}

	public void setSendOrNot(Integer sendOrNot) {
		this.sendOrNot = sendOrNot;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((contactGroup == null) ? 0 : contactGroup.hashCode());
		result = prime * result
				+ ((notificationId == null) ? 0 : notificationId.hashCode());
		result = prime
				* result
				+ ((notificationTime == null) ? 0 : notificationTime.hashCode());
		result = prime
				* result
				+ ((notificationType == null) ? 0 : notificationType.hashCode());
		result = prime * result
				+ ((objectId == null) ? 0 : objectId.hashCode());
		result = prime * result + ((output == null) ? 0 : output.hashCode());
		result = prime * result
				+ ((sendOrNot == null) ? 0 : sendOrNot.hashCode());
		result = prime * result + ((state == null) ? 0 : state.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorNotifications))
			return false;
		AbstractMonitorNotifications other = (AbstractMonitorNotifications) obj;
		if (contactGroup == null) {
			if (other.contactGroup != null)
				return false;
		} else if (!contactGroup.equals(other.contactGroup))
			return false;
		if (notificationId == null) {
			if (other.notificationId != null)
				return false;
		} else if (!notificationId.equals(other.notificationId))
			return false;
		if (notificationTime == null) {
			if (other.notificationTime != null)
				return false;
		} else if (!notificationTime.equals(other.notificationTime))
			return false;
		if (notificationType == null) {
			if (other.notificationType != null)
				return false;
		} else if (!notificationType.equals(other.notificationType))
			return false;
		if (objectId == null) {
			if (other.objectId != null)
				return false;
		} else if (!objectId.equals(other.objectId))
			return false;
		if (output == null) {
			if (other.output != null)
				return false;
		} else if (!output.equals(other.output))
			return false;
		if (sendOrNot == null) {
			if (other.sendOrNot != null)
				return false;
		} else if (!sendOrNot.equals(other.sendOrNot))
			return false;
		if (state == null) {
			if (other.state != null)
				return false;
		} else if (!state.equals(other.state))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorNotifications [contactGroup=" + contactGroup
				+ ", notificationId=" + notificationId + ", notificationTime="
				+ notificationTime + ", notificationType=" + notificationType
				+ ", objectId=" + objectId + ", output=" + output
				+ ", sendOrNot=" + sendOrNot + ", state=" + state + "]";
	}

}