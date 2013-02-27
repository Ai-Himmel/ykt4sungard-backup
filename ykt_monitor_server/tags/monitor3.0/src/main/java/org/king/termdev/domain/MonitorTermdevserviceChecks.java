package org.king.termdev.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * MonitorTermdevserviceChecks entity. @author MyEclipse Persistence Tools
 */
public class MonitorTermdevserviceChecks extends
		AbstractMonitorTermdevserviceChecks implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorTermdevserviceChecks() {
	}

	/** full constructor */
	public MonitorTermdevserviceChecks(BigDecimal termdevserviceId,
			BigDecimal checkType, BigDecimal currentCheckAttempt,
			BigDecimal maxCheckAttempts, BigDecimal state,
			BigDecimal stateType, Date startTime, Date endTime,
			BigDecimal commandId, String commandArgs, String commandLine,
			BigDecimal timeout, Double executionTime, Double latency,
			BigDecimal returnCode, String output, String perfdata) {
		super(termdevserviceId, checkType, currentCheckAttempt,
				maxCheckAttempts, state, stateType, startTime, endTime,
				commandId, commandArgs, commandLine, timeout, executionTime,
				latency, returnCode, output, perfdata);
	}

}
