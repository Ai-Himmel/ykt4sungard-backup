package org.king.termdev.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * AbstractMonitorTermdevserviceChecks entity provides the base persistence
 * definition of the MonitorTermdevserviceChecks entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorTermdevserviceChecks extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private BigDecimal termdevserviceCheckId;
	private BigDecimal termdevserviceId;
	private BigDecimal checkType;
	private BigDecimal currentCheckAttempt;
	private BigDecimal maxCheckAttempts;
	private BigDecimal state;
	private BigDecimal stateType;
	private Date startTime;
	private Date endTime;
	private BigDecimal commandId;
	private String commandArgs;
	private String commandLine;
	private BigDecimal timeout;
	private Double executionTime;
	private Double latency;
	private BigDecimal returnCode;
	private String output;
	private String perfdata;

	// Constructors

	/** default constructor */
	public AbstractMonitorTermdevserviceChecks() {
	}

	/** full constructor */
	public AbstractMonitorTermdevserviceChecks(BigDecimal termdevserviceId,
			BigDecimal checkType, BigDecimal currentCheckAttempt,
			BigDecimal maxCheckAttempts, BigDecimal state,
			BigDecimal stateType, Date startTime, Date endTime,
			BigDecimal commandId, String commandArgs, String commandLine,
			BigDecimal timeout, Double executionTime, Double latency,
			BigDecimal returnCode, String output, String perfdata) {
		this.termdevserviceId = termdevserviceId;
		this.checkType = checkType;
		this.currentCheckAttempt = currentCheckAttempt;
		this.maxCheckAttempts = maxCheckAttempts;
		this.state = state;
		this.stateType = stateType;
		this.startTime = startTime;
		this.endTime = endTime;
		this.commandId = commandId;
		this.commandArgs = commandArgs;
		this.commandLine = commandLine;
		this.timeout = timeout;
		this.executionTime = executionTime;
		this.latency = latency;
		this.returnCode = returnCode;
		this.output = output;
		this.perfdata = perfdata;
	}

	// Property accessors

	public BigDecimal getTermdevserviceCheckId() {
		return this.termdevserviceCheckId;
	}

	public void setTermdevserviceCheckId(BigDecimal termdevserviceCheckId) {
		this.termdevserviceCheckId = termdevserviceCheckId;
	}

	public BigDecimal getTermdevserviceId() {
		return this.termdevserviceId;
	}

	public void setTermdevserviceId(BigDecimal termdevserviceId) {
		this.termdevserviceId = termdevserviceId;
	}

	public BigDecimal getCheckType() {
		return this.checkType;
	}

	public void setCheckType(BigDecimal checkType) {
		this.checkType = checkType;
	}

	public BigDecimal getCurrentCheckAttempt() {
		return this.currentCheckAttempt;
	}

	public void setCurrentCheckAttempt(BigDecimal currentCheckAttempt) {
		this.currentCheckAttempt = currentCheckAttempt;
	}

	public BigDecimal getMaxCheckAttempts() {
		return this.maxCheckAttempts;
	}

	public void setMaxCheckAttempts(BigDecimal maxCheckAttempts) {
		this.maxCheckAttempts = maxCheckAttempts;
	}

	public BigDecimal getState() {
		return this.state;
	}

	public void setState(BigDecimal state) {
		this.state = state;
	}

	public BigDecimal getStateType() {
		return this.stateType;
	}

	public void setStateType(BigDecimal stateType) {
		this.stateType = stateType;
	}

	public Date getStartTime() {
		return this.startTime;
	}

	public void setStartTime(Date startTime) {
		this.startTime = startTime;
	}

	public Date getEndTime() {
		return this.endTime;
	}

	public void setEndTime(Date endTime) {
		this.endTime = endTime;
	}

	public BigDecimal getCommandId() {
		return this.commandId;
	}

	public void setCommandId(BigDecimal commandId) {
		this.commandId = commandId;
	}

	public String getCommandArgs() {
		return this.commandArgs;
	}

	public void setCommandArgs(String commandArgs) {
		this.commandArgs = commandArgs;
	}

	public String getCommandLine() {
		return this.commandLine;
	}

	public void setCommandLine(String commandLine) {
		this.commandLine = commandLine;
	}

	public BigDecimal getTimeout() {
		return this.timeout;
	}

	public void setTimeout(BigDecimal timeout) {
		this.timeout = timeout;
	}

	public Double getExecutionTime() {
		return this.executionTime;
	}

	public void setExecutionTime(Double executionTime) {
		this.executionTime = executionTime;
	}

	public Double getLatency() {
		return this.latency;
	}

	public void setLatency(Double latency) {
		this.latency = latency;
	}

	public BigDecimal getReturnCode() {
		return this.returnCode;
	}

	public void setReturnCode(BigDecimal returnCode) {
		this.returnCode = returnCode;
	}

	public String getOutput() {
		return this.output;
	}

	public void setOutput(String output) {
		this.output = output;
	}

	public String getPerfdata() {
		return this.perfdata;
	}

	public void setPerfdata(String perfdata) {
		this.perfdata = perfdata;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((checkType == null) ? 0 : checkType.hashCode());
		result = prime * result
				+ ((commandArgs == null) ? 0 : commandArgs.hashCode());
		result = prime * result
				+ ((commandId == null) ? 0 : commandId.hashCode());
		result = prime * result
				+ ((commandLine == null) ? 0 : commandLine.hashCode());
		result = prime
				* result
				+ ((currentCheckAttempt == null) ? 0 : currentCheckAttempt
						.hashCode());
		result = prime * result + ((endTime == null) ? 0 : endTime.hashCode());
		result = prime * result
				+ ((executionTime == null) ? 0 : executionTime.hashCode());
		result = prime * result + ((latency == null) ? 0 : latency.hashCode());
		result = prime
				* result
				+ ((maxCheckAttempts == null) ? 0 : maxCheckAttempts.hashCode());
		result = prime * result + ((output == null) ? 0 : output.hashCode());
		result = prime * result
				+ ((perfdata == null) ? 0 : perfdata.hashCode());
		result = prime * result
				+ ((returnCode == null) ? 0 : returnCode.hashCode());
		result = prime * result
				+ ((startTime == null) ? 0 : startTime.hashCode());
		result = prime * result + ((state == null) ? 0 : state.hashCode());
		result = prime * result
				+ ((stateType == null) ? 0 : stateType.hashCode());
		result = prime
				* result
				+ ((termdevserviceCheckId == null) ? 0 : termdevserviceCheckId
						.hashCode());
		result = prime
				* result
				+ ((termdevserviceId == null) ? 0 : termdevserviceId.hashCode());
		result = prime * result + ((timeout == null) ? 0 : timeout.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorTermdevserviceChecks))
			return false;
		AbstractMonitorTermdevserviceChecks other = (AbstractMonitorTermdevserviceChecks) obj;
		if (checkType == null) {
			if (other.checkType != null)
				return false;
		} else if (!checkType.equals(other.checkType))
			return false;
		if (commandArgs == null) {
			if (other.commandArgs != null)
				return false;
		} else if (!commandArgs.equals(other.commandArgs))
			return false;
		if (commandId == null) {
			if (other.commandId != null)
				return false;
		} else if (!commandId.equals(other.commandId))
			return false;
		if (commandLine == null) {
			if (other.commandLine != null)
				return false;
		} else if (!commandLine.equals(other.commandLine))
			return false;
		if (currentCheckAttempt == null) {
			if (other.currentCheckAttempt != null)
				return false;
		} else if (!currentCheckAttempt.equals(other.currentCheckAttempt))
			return false;
		if (endTime == null) {
			if (other.endTime != null)
				return false;
		} else if (!endTime.equals(other.endTime))
			return false;
		if (executionTime == null) {
			if (other.executionTime != null)
				return false;
		} else if (!executionTime.equals(other.executionTime))
			return false;
		if (latency == null) {
			if (other.latency != null)
				return false;
		} else if (!latency.equals(other.latency))
			return false;
		if (maxCheckAttempts == null) {
			if (other.maxCheckAttempts != null)
				return false;
		} else if (!maxCheckAttempts.equals(other.maxCheckAttempts))
			return false;
		if (output == null) {
			if (other.output != null)
				return false;
		} else if (!output.equals(other.output))
			return false;
		if (perfdata == null) {
			if (other.perfdata != null)
				return false;
		} else if (!perfdata.equals(other.perfdata))
			return false;
		if (returnCode == null) {
			if (other.returnCode != null)
				return false;
		} else if (!returnCode.equals(other.returnCode))
			return false;
		if (startTime == null) {
			if (other.startTime != null)
				return false;
		} else if (!startTime.equals(other.startTime))
			return false;
		if (state == null) {
			if (other.state != null)
				return false;
		} else if (!state.equals(other.state))
			return false;
		if (stateType == null) {
			if (other.stateType != null)
				return false;
		} else if (!stateType.equals(other.stateType))
			return false;
		if (termdevserviceCheckId == null) {
			if (other.termdevserviceCheckId != null)
				return false;
		} else if (!termdevserviceCheckId.equals(other.termdevserviceCheckId))
			return false;
		if (termdevserviceId == null) {
			if (other.termdevserviceId != null)
				return false;
		} else if (!termdevserviceId.equals(other.termdevserviceId))
			return false;
		if (timeout == null) {
			if (other.timeout != null)
				return false;
		} else if (!timeout.equals(other.timeout))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorTermdevserviceChecks [checkType=" + checkType
				+ ", commandArgs=" + commandArgs + ", commandId=" + commandId
				+ ", commandLine=" + commandLine + ", currentCheckAttempt="
				+ currentCheckAttempt + ", endTime=" + endTime
				+ ", executionTime=" + executionTime + ", latency=" + latency
				+ ", maxCheckAttempts=" + maxCheckAttempts + ", output="
				+ output + ", perfdata=" + perfdata + ", returnCode="
				+ returnCode + ", startTime=" + startTime + ", state=" + state
				+ ", stateType=" + stateType + ", termdevserviceCheckId="
				+ termdevserviceCheckId + ", termdevserviceId="
				+ termdevserviceId + ", timeout=" + timeout + "]";
	}

}