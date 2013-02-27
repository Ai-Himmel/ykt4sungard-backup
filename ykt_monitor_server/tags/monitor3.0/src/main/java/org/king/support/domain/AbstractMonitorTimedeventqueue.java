package org.king.support.domain;

import java.util.Date;

/**
 * AbstractMonitorTimedeventqueue entity provides the base persistence
 * definition of the MonitorTimedeventqueue entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorTimedeventqueue extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer timedeventqueueId;
	private Integer eventType;
	private String queueTime;
	private String scheduledTime;
	private Integer recurringEvent;
	private Integer objectId;

	// Constructors

	/** default constructor */
	public AbstractMonitorTimedeventqueue() {
	}

	/** full constructor */
	public AbstractMonitorTimedeventqueue(Integer eventType, String queueTime,
			String scheduledTime, Integer recurringEvent, Integer objectId) {
		this.eventType = eventType;
		this.queueTime = queueTime;
		this.scheduledTime = scheduledTime;
		this.recurringEvent = recurringEvent;
		this.objectId = objectId;
	}

	// Property accessors

	public Integer getTimedeventqueueId() {
		return this.timedeventqueueId;
	}

	public void setTimedeventqueueId(Integer timedeventqueueId) {
		this.timedeventqueueId = timedeventqueueId;
	}

	public Integer getEventType() {
		return this.eventType;
	}

	public void setEventType(Integer eventType) {
		this.eventType = eventType;
	}

	public String getQueueTime() {
		return this.queueTime;
	}

	public void setQueueTime(String queueTime) {
		this.queueTime = queueTime;
	}

	public String getScheduledTime() {
		return this.scheduledTime;
	}

	public void setScheduledTime(String scheduledTime) {
		this.scheduledTime = scheduledTime;
	}

	public Integer getRecurringEvent() {
		return this.recurringEvent;
	}

	public void setRecurringEvent(Integer recurringEvent) {
		this.recurringEvent = recurringEvent;
	}

	public Integer getObjectId() {
		return this.objectId;
	}

	public void setObjectId(Integer objectId) {
		this.objectId = objectId;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((eventType == null) ? 0 : eventType.hashCode());
		result = prime * result
				+ ((objectId == null) ? 0 : objectId.hashCode());
		result = prime * result
				+ ((queueTime == null) ? 0 : queueTime.hashCode());
		result = prime * result
				+ ((recurringEvent == null) ? 0 : recurringEvent.hashCode());
		result = prime * result
				+ ((scheduledTime == null) ? 0 : scheduledTime.hashCode());
		result = prime
				* result
				+ ((timedeventqueueId == null) ? 0 : timedeventqueueId
						.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorTimedeventqueue))
			return false;
		AbstractMonitorTimedeventqueue other = (AbstractMonitorTimedeventqueue) obj;
		if (eventType == null) {
			if (other.eventType != null)
				return false;
		} else if (!eventType.equals(other.eventType))
			return false;
		if (objectId == null) {
			if (other.objectId != null)
				return false;
		} else if (!objectId.equals(other.objectId))
			return false;
		if (queueTime == null) {
			if (other.queueTime != null)
				return false;
		} else if (!queueTime.equals(other.queueTime))
			return false;
		if (recurringEvent == null) {
			if (other.recurringEvent != null)
				return false;
		} else if (!recurringEvent.equals(other.recurringEvent))
			return false;
		if (scheduledTime == null) {
			if (other.scheduledTime != null)
				return false;
		} else if (!scheduledTime.equals(other.scheduledTime))
			return false;
		if (timedeventqueueId == null) {
			if (other.timedeventqueueId != null)
				return false;
		} else if (!timedeventqueueId.equals(other.timedeventqueueId))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorTimedeventqueue [eventType=" + eventType
				+ ", objectId=" + objectId + ", queueTime=" + queueTime
				+ ", recurringEvent=" + recurringEvent + ", scheduledTime="
				+ scheduledTime + ", timedeventqueueId=" + timedeventqueueId
				+ "]";
	}

}