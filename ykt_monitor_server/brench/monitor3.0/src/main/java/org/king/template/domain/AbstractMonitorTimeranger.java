package org.king.template.domain;

/**
 * AbstractMonitorTimeranger entity provides the base persistence definition of
 * the MonitorTimeranger entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorTimeranger extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer timerangerId;
	private Integer timeperiodDay;
	private String startTime;
	private String endTime;
    private MonitorTimePeriods monitorTimePeriods;

	// Constructors

	/** default constructor */
	public AbstractMonitorTimeranger() {
	}

	/** full constructor */
	public AbstractMonitorTimeranger(Integer timeperiodDay,
			String startTime, String endTime,MonitorTimePeriods monitorTimePeriods) {
		this.timeperiodDay = timeperiodDay;
		this.startTime = startTime;
		this.endTime = endTime;
        this.monitorTimePeriods = monitorTimePeriods;
	}

	// Property accessors


    public Integer getTimerangerId() {
        return timerangerId;
    }

    public void setTimerangerId(Integer timerangerId) {
        this.timerangerId = timerangerId;
    }

    public Integer getTimeperiodDay() {
		return this.timeperiodDay;
	}

	public void setTimeperiodDay(Integer timeperiodDay) {
		this.timeperiodDay = timeperiodDay;
	}

    public String getStartTime() {
		return startTime;
	}

	public void setStartTime(String startTime) {
		this.startTime = startTime;
	}

	public String getEndTime() {
		return endTime;
	}

	public void setEndTime(String endTime) {
		this.endTime = endTime;
	}

	public MonitorTimePeriods getMonitorTimePeriods() {
        return monitorTimePeriods;
    }

    public void setMonitorTimePeriods(MonitorTimePeriods monitorTimePeriods) {
        this.monitorTimePeriods = monitorTimePeriods;
    }

    @Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result + ((endTime == null) ? 0 : endTime.hashCode());
		result = prime * result
				+ ((startTime == null) ? 0 : startTime.hashCode());
		result = prime * result
				+ ((timeperiodDay == null) ? 0 : timeperiodDay.hashCode());
		result = prime * result
				+ ((timerangerId == null) ? 0 : timerangerId.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorTimeranger))
			return false;
		AbstractMonitorTimeranger other = (AbstractMonitorTimeranger) obj;
		if (endTime == null) {
			if (other.endTime != null)
				return false;
		} else if (!endTime.equals(other.endTime))
			return false;
		if (startTime == null) {
			if (other.startTime != null)
				return false;
		} else if (!startTime.equals(other.startTime))
			return false;
		if (timeperiodDay == null) {
			if (other.timeperiodDay != null)
				return false;
		} else if (!timeperiodDay.equals(other.timeperiodDay))
			return false;
		if (timerangerId == null) {
			if (other.timerangerId != null)
				return false;
		} else if (!timerangerId.equals(other.timerangerId))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorTimeranger [endTime=" + endTime + ", startTime="
				+ startTime + ", timeperiodDay=" + timeperiodDay
				+ ", timeperiodId=" + timerangerId + "]";
	}

}