package org.king.termdev.domain;

/**
 * MonitorTermdevchedks entity. @author MyEclipse Persistence Tools
 */
public class MonitorTermdevchecks extends AbstractMonitorTermdevchecks
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorTermdevchecks() {
	}

	/** full constructor */
	public MonitorTermdevchecks(Integer deviceId, Integer checkType,
			Integer currentCheckAttempt, Integer maxCheckAttempts,
			Integer checkCount, Integer state, Integer stateType,
			String startTime, String endTime, Double timeLast,
			Integer commandId, String commandArgs, String commandLine,
			Integer timeout, Double executionTime, Double latency,
			Integer returnCode, String output, String perfdata) {
		super(deviceId, checkType, currentCheckAttempt, maxCheckAttempts,
				checkCount, state, stateType, startTime, endTime, timeLast,
				commandId, commandArgs, commandLine, timeout, executionTime,
				latency, returnCode, output, perfdata);
	}

}
