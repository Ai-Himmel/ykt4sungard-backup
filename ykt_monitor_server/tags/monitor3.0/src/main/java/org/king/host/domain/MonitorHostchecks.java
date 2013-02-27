package org.king.host.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * MonitorHostchecks entity. @author MyEclipse Persistence Tools
 */
public class MonitorHostchecks extends AbstractMonitorHostchecks implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorHostchecks() {
	}

	/** full constructor */
	public MonitorHostchecks(Integer hostId, Integer checkType,
			Integer currentCheckAttempt, Integer maxCheckAttempts,
			Integer state, Integer stateType, String startTime,
			String endTime, Integer commandId, String commandArgs,
			String commandLine, Integer timeout, Double executionTime,
			Double latency, Integer returnCode, String output,
			String perfdata) {
		super(hostId, checkType, currentCheckAttempt, maxCheckAttempts, state,
				stateType, startTime, endTime, commandId, commandArgs,
				commandLine, timeout, executionTime, latency, returnCode,
				output, perfdata);
	}

}
