package org.king.host.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * AbstractMonitorHostscheduleddowntime entity provides the base persistence
 * definition of the MonitorHostscheduleddowntime entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorHostscheduleddowntime extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer scheduleddowntimeId;
	private Integer downtimeType;
	private Integer hostId;
	private String entryTime;
	private String authorName;
	private String commentData;
	private Integer isFixed;
	private Integer duration;
	private String scheduledStartTime;
	private String scheduledEndTime;
	private Integer wasStarted;
	private String actualStartTime;
	private String actualEndTime;
	private Integer wasCancelled;

	// Constructors

	/** default constructor */
	public AbstractMonitorHostscheduleddowntime() {
	}

	/** full constructor */
	public AbstractMonitorHostscheduleddowntime(Integer downtimeType,
			Integer hostId, String entryTime, String authorName,
			String commentData, Integer isFixed, Integer duration,
			String scheduledStartTime, String scheduledEndTime,
			Integer wasStarted, String actualStartTime, String actualEndTime,
			Integer wasCancelled) {
		this.downtimeType = downtimeType;
		this.hostId = hostId;
		this.entryTime = entryTime;
		this.authorName = authorName;
		this.commentData = commentData;
		this.isFixed = isFixed;
		this.duration = duration;
		this.scheduledStartTime = scheduledStartTime;
		this.scheduledEndTime = scheduledEndTime;
		this.wasStarted = wasStarted;
		this.actualStartTime = actualStartTime;
		this.actualEndTime = actualEndTime;
		this.wasCancelled = wasCancelled;
	}

	// Property accessors

	public Integer getScheduleddowntimeId() {
		return this.scheduleddowntimeId;
	}

	public void setScheduleddowntimeId(Integer scheduleddowntimeId) {
		this.scheduleddowntimeId = scheduleddowntimeId;
	}

	public Integer getDowntimeType() {
		return this.downtimeType;
	}

	public void setDowntimeType(Integer downtimeType) {
		this.downtimeType = downtimeType;
	}

	public Integer getHostId() {
		return this.hostId;
	}

	public void setHostId(Integer hostId) {
		this.hostId = hostId;
	}

	public String getEntryTime() {
		return this.entryTime;
	}

	public void setEntryTime(String entryTime) {
		this.entryTime = entryTime;
	}

	public String getAuthorName() {
		return this.authorName;
	}

	public void setAuthorName(String authorName) {
		this.authorName = authorName;
	}

	public String getCommentData() {
		return this.commentData;
	}

	public void setCommentData(String commentData) {
		this.commentData = commentData;
	}

	public Integer getIsFixed() {
		return this.isFixed;
	}

	public void setIsFixed(Integer isFixed) {
		this.isFixed = isFixed;
	}

	public Integer getDuration() {
		return this.duration;
	}

	public void setDuration(Integer duration) {
		this.duration = duration;
	}

	public String getScheduledStartTime() {
		return this.scheduledStartTime;
	}

	public void setScheduledStartTime(String scheduledStartTime) {
		this.scheduledStartTime = scheduledStartTime;
	}

	public String getScheduledEndTime() {
		return this.scheduledEndTime;
	}

	public void setScheduledEndTime(String scheduledEndTime) {
		this.scheduledEndTime = scheduledEndTime;
	}

	public Integer getWasStarted() {
		return this.wasStarted;
	}

	public void setWasStarted(Integer wasStarted) {
		this.wasStarted = wasStarted;
	}

	public String getActualStartTime() {
		return this.actualStartTime;
	}

	public void setActualStartTime(String actualStartTime) {
		this.actualStartTime = actualStartTime;
	}

	public String getActualEndTime() {
		return this.actualEndTime;
	}

	public void setActualEndTime(String actualEndTime) {
		this.actualEndTime = actualEndTime;
	}

	public Integer getWasCancelled() {
		return this.wasCancelled;
	}

	public void setWasCancelled(Integer wasCancelled) {
		this.wasCancelled = wasCancelled;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((actualEndTime == null) ? 0 : actualEndTime.hashCode());
		result = prime * result
				+ ((actualStartTime == null) ? 0 : actualStartTime.hashCode());
		result = prime * result
				+ ((authorName == null) ? 0 : authorName.hashCode());
		result = prime * result
				+ ((commentData == null) ? 0 : commentData.hashCode());
		result = prime * result
				+ ((downtimeType == null) ? 0 : downtimeType.hashCode());
		result = prime * result
				+ ((duration == null) ? 0 : duration.hashCode());
		result = prime * result
				+ ((entryTime == null) ? 0 : entryTime.hashCode());
		result = prime * result + ((hostId == null) ? 0 : hostId.hashCode());
		result = prime * result + ((isFixed == null) ? 0 : isFixed.hashCode());
		result = prime
				* result
				+ ((scheduledEndTime == null) ? 0 : scheduledEndTime.hashCode());
		result = prime
				* result
				+ ((scheduledStartTime == null) ? 0 : scheduledStartTime
						.hashCode());
		result = prime
				* result
				+ ((scheduleddowntimeId == null) ? 0 : scheduleddowntimeId
						.hashCode());
		result = prime * result
				+ ((wasCancelled == null) ? 0 : wasCancelled.hashCode());
		result = prime * result
				+ ((wasStarted == null) ? 0 : wasStarted.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorHostscheduleddowntime))
			return false;
		AbstractMonitorHostscheduleddowntime other = (AbstractMonitorHostscheduleddowntime) obj;
		if (actualEndTime == null) {
			if (other.actualEndTime != null)
				return false;
		} else if (!actualEndTime.equals(other.actualEndTime))
			return false;
		if (actualStartTime == null) {
			if (other.actualStartTime != null)
				return false;
		} else if (!actualStartTime.equals(other.actualStartTime))
			return false;
		if (authorName == null) {
			if (other.authorName != null)
				return false;
		} else if (!authorName.equals(other.authorName))
			return false;
		if (commentData == null) {
			if (other.commentData != null)
				return false;
		} else if (!commentData.equals(other.commentData))
			return false;
		if (downtimeType == null) {
			if (other.downtimeType != null)
				return false;
		} else if (!downtimeType.equals(other.downtimeType))
			return false;
		if (duration == null) {
			if (other.duration != null)
				return false;
		} else if (!duration.equals(other.duration))
			return false;
		if (entryTime == null) {
			if (other.entryTime != null)
				return false;
		} else if (!entryTime.equals(other.entryTime))
			return false;
		if (hostId == null) {
			if (other.hostId != null)
				return false;
		} else if (!hostId.equals(other.hostId))
			return false;
		if (isFixed == null) {
			if (other.isFixed != null)
				return false;
		} else if (!isFixed.equals(other.isFixed))
			return false;
		if (scheduledEndTime == null) {
			if (other.scheduledEndTime != null)
				return false;
		} else if (!scheduledEndTime.equals(other.scheduledEndTime))
			return false;
		if (scheduledStartTime == null) {
			if (other.scheduledStartTime != null)
				return false;
		} else if (!scheduledStartTime.equals(other.scheduledStartTime))
			return false;
		if (scheduleddowntimeId == null) {
			if (other.scheduleddowntimeId != null)
				return false;
		} else if (!scheduleddowntimeId.equals(other.scheduleddowntimeId))
			return false;
		if (wasCancelled == null) {
			if (other.wasCancelled != null)
				return false;
		} else if (!wasCancelled.equals(other.wasCancelled))
			return false;
		if (wasStarted == null) {
			if (other.wasStarted != null)
				return false;
		} else if (!wasStarted.equals(other.wasStarted))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorHostscheduleddowntime [actualEndTime="
				+ actualEndTime + ", actualStartTime=" + actualStartTime
				+ ", authorName=" + authorName + ", commentData=" + commentData
				+ ", downtimeType=" + downtimeType + ", duration=" + duration
				+ ", entryTime=" + entryTime + ", hostId=" + hostId
				+ ", isFixed=" + isFixed + ", scheduledEndTime="
				+ scheduledEndTime + ", scheduledStartTime="
				+ scheduledStartTime + ", scheduleddowntimeId="
				+ scheduleddowntimeId + ", wasCancelled=" + wasCancelled
				+ ", wasStarted=" + wasStarted + "]";
	}

}