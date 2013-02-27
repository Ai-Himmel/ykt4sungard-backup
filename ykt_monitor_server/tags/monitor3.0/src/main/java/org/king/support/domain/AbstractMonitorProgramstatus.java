package org.king.support.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * AbstractMonitorProgramstatus entity provides the base persistence definition
 * of the MonitorProgramstatus entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorProgramstatus extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private BigDecimal programstatusId;
	private Date statusUpdateTime;
	private Date programStartTime;
	private Date programEndTime;
	private BigDecimal isCurrentlyRunning;
	private Date lastCommandCheck;
	private Date lastLogRotation;
	private BigDecimal notificationsEnabled;
	private BigDecimal activeServiceChecksEnabled;
	private BigDecimal passiveServiceChecksEnabled;
	private BigDecimal activeHostChecksEnabled;
	private BigDecimal passiveHostChecksEnabled;
	private BigDecimal eventHandlersEnabled;
	private BigDecimal flapDetectionEnabled;

	// Constructors

	/** default constructor */
	public AbstractMonitorProgramstatus() {
	}

	/** full constructor */
	public AbstractMonitorProgramstatus(Date statusUpdateTime,
			Date programStartTime, Date programEndTime,
			BigDecimal isCurrentlyRunning, Date lastCommandCheck,
			Date lastLogRotation, BigDecimal notificationsEnabled,
			BigDecimal activeServiceChecksEnabled,
			BigDecimal passiveServiceChecksEnabled,
			BigDecimal activeHostChecksEnabled,
			BigDecimal passiveHostChecksEnabled,
			BigDecimal eventHandlersEnabled, BigDecimal flapDetectionEnabled) {
		this.statusUpdateTime = statusUpdateTime;
		this.programStartTime = programStartTime;
		this.programEndTime = programEndTime;
		this.isCurrentlyRunning = isCurrentlyRunning;
		this.lastCommandCheck = lastCommandCheck;
		this.lastLogRotation = lastLogRotation;
		this.notificationsEnabled = notificationsEnabled;
		this.activeServiceChecksEnabled = activeServiceChecksEnabled;
		this.passiveServiceChecksEnabled = passiveServiceChecksEnabled;
		this.activeHostChecksEnabled = activeHostChecksEnabled;
		this.passiveHostChecksEnabled = passiveHostChecksEnabled;
		this.eventHandlersEnabled = eventHandlersEnabled;
		this.flapDetectionEnabled = flapDetectionEnabled;
	}

	// Property accessors

	public BigDecimal getProgramstatusId() {
		return this.programstatusId;
	}

	public void setProgramstatusId(BigDecimal programstatusId) {
		this.programstatusId = programstatusId;
	}

	public Date getStatusUpdateTime() {
		return this.statusUpdateTime;
	}

	public void setStatusUpdateTime(Date statusUpdateTime) {
		this.statusUpdateTime = statusUpdateTime;
	}

	public Date getProgramStartTime() {
		return this.programStartTime;
	}

	public void setProgramStartTime(Date programStartTime) {
		this.programStartTime = programStartTime;
	}

	public Date getProgramEndTime() {
		return this.programEndTime;
	}

	public void setProgramEndTime(Date programEndTime) {
		this.programEndTime = programEndTime;
	}

	public BigDecimal getIsCurrentlyRunning() {
		return this.isCurrentlyRunning;
	}

	public void setIsCurrentlyRunning(BigDecimal isCurrentlyRunning) {
		this.isCurrentlyRunning = isCurrentlyRunning;
	}

	public Date getLastCommandCheck() {
		return this.lastCommandCheck;
	}

	public void setLastCommandCheck(Date lastCommandCheck) {
		this.lastCommandCheck = lastCommandCheck;
	}

	public Date getLastLogRotation() {
		return this.lastLogRotation;
	}

	public void setLastLogRotation(Date lastLogRotation) {
		this.lastLogRotation = lastLogRotation;
	}

	public BigDecimal getNotificationsEnabled() {
		return this.notificationsEnabled;
	}

	public void setNotificationsEnabled(BigDecimal notificationsEnabled) {
		this.notificationsEnabled = notificationsEnabled;
	}

	public BigDecimal getActiveServiceChecksEnabled() {
		return this.activeServiceChecksEnabled;
	}

	public void setActiveServiceChecksEnabled(
			BigDecimal activeServiceChecksEnabled) {
		this.activeServiceChecksEnabled = activeServiceChecksEnabled;
	}

	public BigDecimal getPassiveServiceChecksEnabled() {
		return this.passiveServiceChecksEnabled;
	}

	public void setPassiveServiceChecksEnabled(
			BigDecimal passiveServiceChecksEnabled) {
		this.passiveServiceChecksEnabled = passiveServiceChecksEnabled;
	}

	public BigDecimal getActiveHostChecksEnabled() {
		return this.activeHostChecksEnabled;
	}

	public void setActiveHostChecksEnabled(BigDecimal activeHostChecksEnabled) {
		this.activeHostChecksEnabled = activeHostChecksEnabled;
	}

	public BigDecimal getPassiveHostChecksEnabled() {
		return this.passiveHostChecksEnabled;
	}

	public void setPassiveHostChecksEnabled(BigDecimal passiveHostChecksEnabled) {
		this.passiveHostChecksEnabled = passiveHostChecksEnabled;
	}

	public BigDecimal getEventHandlersEnabled() {
		return this.eventHandlersEnabled;
	}

	public void setEventHandlersEnabled(BigDecimal eventHandlersEnabled) {
		this.eventHandlersEnabled = eventHandlersEnabled;
	}

	public BigDecimal getFlapDetectionEnabled() {
		return this.flapDetectionEnabled;
	}

	public void setFlapDetectionEnabled(BigDecimal flapDetectionEnabled) {
		this.flapDetectionEnabled = flapDetectionEnabled;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime
				* result
				+ ((activeHostChecksEnabled == null) ? 0
						: activeHostChecksEnabled.hashCode());
		result = prime
				* result
				+ ((activeServiceChecksEnabled == null) ? 0
						: activeServiceChecksEnabled.hashCode());
		result = prime
				* result
				+ ((eventHandlersEnabled == null) ? 0 : eventHandlersEnabled
						.hashCode());
		result = prime
				* result
				+ ((flapDetectionEnabled == null) ? 0 : flapDetectionEnabled
						.hashCode());
		result = prime
				* result
				+ ((isCurrentlyRunning == null) ? 0 : isCurrentlyRunning
						.hashCode());
		result = prime
				* result
				+ ((lastCommandCheck == null) ? 0 : lastCommandCheck.hashCode());
		result = prime * result
				+ ((lastLogRotation == null) ? 0 : lastLogRotation.hashCode());
		result = prime
				* result
				+ ((notificationsEnabled == null) ? 0 : notificationsEnabled
						.hashCode());
		result = prime
				* result
				+ ((passiveHostChecksEnabled == null) ? 0
						: passiveHostChecksEnabled.hashCode());
		result = prime
				* result
				+ ((passiveServiceChecksEnabled == null) ? 0
						: passiveServiceChecksEnabled.hashCode());
		result = prime * result
				+ ((programEndTime == null) ? 0 : programEndTime.hashCode());
		result = prime
				* result
				+ ((programStartTime == null) ? 0 : programStartTime.hashCode());
		result = prime * result
				+ ((programstatusId == null) ? 0 : programstatusId.hashCode());
		result = prime
				* result
				+ ((statusUpdateTime == null) ? 0 : statusUpdateTime.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorProgramstatus))
			return false;
		AbstractMonitorProgramstatus other = (AbstractMonitorProgramstatus) obj;
		if (activeHostChecksEnabled == null) {
			if (other.activeHostChecksEnabled != null)
				return false;
		} else if (!activeHostChecksEnabled
				.equals(other.activeHostChecksEnabled))
			return false;
		if (activeServiceChecksEnabled == null) {
			if (other.activeServiceChecksEnabled != null)
				return false;
		} else if (!activeServiceChecksEnabled
				.equals(other.activeServiceChecksEnabled))
			return false;
		if (eventHandlersEnabled == null) {
			if (other.eventHandlersEnabled != null)
				return false;
		} else if (!eventHandlersEnabled.equals(other.eventHandlersEnabled))
			return false;
		if (flapDetectionEnabled == null) {
			if (other.flapDetectionEnabled != null)
				return false;
		} else if (!flapDetectionEnabled.equals(other.flapDetectionEnabled))
			return false;
		if (isCurrentlyRunning == null) {
			if (other.isCurrentlyRunning != null)
				return false;
		} else if (!isCurrentlyRunning.equals(other.isCurrentlyRunning))
			return false;
		if (lastCommandCheck == null) {
			if (other.lastCommandCheck != null)
				return false;
		} else if (!lastCommandCheck.equals(other.lastCommandCheck))
			return false;
		if (lastLogRotation == null) {
			if (other.lastLogRotation != null)
				return false;
		} else if (!lastLogRotation.equals(other.lastLogRotation))
			return false;
		if (notificationsEnabled == null) {
			if (other.notificationsEnabled != null)
				return false;
		} else if (!notificationsEnabled.equals(other.notificationsEnabled))
			return false;
		if (passiveHostChecksEnabled == null) {
			if (other.passiveHostChecksEnabled != null)
				return false;
		} else if (!passiveHostChecksEnabled
				.equals(other.passiveHostChecksEnabled))
			return false;
		if (passiveServiceChecksEnabled == null) {
			if (other.passiveServiceChecksEnabled != null)
				return false;
		} else if (!passiveServiceChecksEnabled
				.equals(other.passiveServiceChecksEnabled))
			return false;
		if (programEndTime == null) {
			if (other.programEndTime != null)
				return false;
		} else if (!programEndTime.equals(other.programEndTime))
			return false;
		if (programStartTime == null) {
			if (other.programStartTime != null)
				return false;
		} else if (!programStartTime.equals(other.programStartTime))
			return false;
		if (programstatusId == null) {
			if (other.programstatusId != null)
				return false;
		} else if (!programstatusId.equals(other.programstatusId))
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
		return "AbstractMonitorProgramstatus [activeHostChecksEnabled="
				+ activeHostChecksEnabled + ", activeServiceChecksEnabled="
				+ activeServiceChecksEnabled + ", eventHandlersEnabled="
				+ eventHandlersEnabled + ", flapDetectionEnabled="
				+ flapDetectionEnabled + ", isCurrentlyRunning="
				+ isCurrentlyRunning + ", lastCommandCheck=" + lastCommandCheck
				+ ", lastLogRotation=" + lastLogRotation
				+ ", notificationsEnabled=" + notificationsEnabled
				+ ", passiveHostChecksEnabled=" + passiveHostChecksEnabled
				+ ", passiveServiceChecksEnabled="
				+ passiveServiceChecksEnabled + ", programEndTime="
				+ programEndTime + ", programStartTime=" + programStartTime
				+ ", programstatusId=" + programstatusId
				+ ", statusUpdateTime=" + statusUpdateTime + "]";
	}

}