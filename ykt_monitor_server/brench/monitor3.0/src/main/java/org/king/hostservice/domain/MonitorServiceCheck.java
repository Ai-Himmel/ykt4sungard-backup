package org.king.hostservice.domain;


/**
 * MonitorServiceCheck entity. @author MyEclipse Persistence Tools
 */
public class MonitorServiceCheck extends AbstractMonitorServiceCheck implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorServiceCheck() {
	}

	/** full constructor */
	public MonitorServiceCheck(Integer serviceId, Integer checkType,
			Integer currentCheckAttempt, Integer maxCheckAttempts,
			Integer state, Integer stateType, String startTime,
			String endTime, Integer commandId, String commandArgs,
			String commandLine, Integer timeout, Double executionTime,
			Double latency, Integer returnCode, String output,
			String perfdata) {
		super(serviceId, checkType, currentCheckAttempt, maxCheckAttempts,
				state, stateType, startTime, endTime, commandId, commandArgs,
				commandLine, timeout, executionTime, latency, returnCode,
				output, perfdata);
	}

}
