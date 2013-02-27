package org.king.template.domain;

/**
 * MonitorTimeranger entity. @author MyEclipse Persistence Tools
 */
public class MonitorTimeranger extends AbstractMonitorTimeranger implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorTimeranger() {
	}

	/** full constructor */
	public MonitorTimeranger(Integer timeperiodDay, String startTime,
			String endTime,MonitorTimePeriods monitorTimePeriods) {
		super(timeperiodDay, startTime, endTime,monitorTimePeriods);
	}

}
