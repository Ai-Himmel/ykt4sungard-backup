package org.king.hostservice.domain;


/**
 * AbstractMonitorServiceCheck entity provides the base persistence definition
 * of the MonitorServiceCheck entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorServiceCheck extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer serviceCheckId;
	private Integer serviceId;
	private Integer checkType;
	private Integer currentCheckAttempt;
	private Integer maxCheckAttempts;
	private Integer state;
	private Integer stateType;
	private String startTime;
	private String endTime;
	private Integer commandId;
	private String commandArgs;
	private String commandLine;
	private Integer timeout;
	private Double executionTime;
	private Double latency;
	private Integer returnCode;
	private String output;
	private String perfdata;

	// Constructors

	/** default constructor */
	public AbstractMonitorServiceCheck() {
	}

	/** full constructor */
	public AbstractMonitorServiceCheck(Integer serviceId,
			Integer checkType, Integer currentCheckAttempt,
			Integer maxCheckAttempts, Integer state,
			Integer stateType, String startTime, String endTime,
			Integer commandId, String commandArgs, String commandLine,
			Integer timeout, Double executionTime, Double latency,
			Integer returnCode, String output, String perfdata) {
		this.serviceId = serviceId;
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

	public Integer getServiceCheckId() {
		return this.serviceCheckId;
	}

	public void setServiceCheckId(Integer serviceCheckId) {
		this.serviceCheckId = serviceCheckId;
	}

	public Integer getServiceId() {
		return this.serviceId;
	}

	public void setServiceId(Integer serviceId) {
		this.serviceId = serviceId;
	}

	public Integer getCheckType() {
		return this.checkType;
	}

	public void setCheckType(Integer checkType) {
		this.checkType = checkType;
	}

	public Integer getCurrentCheckAttempt() {
		return this.currentCheckAttempt;
	}

	public void setCurrentCheckAttempt(Integer currentCheckAttempt) {
		this.currentCheckAttempt = currentCheckAttempt;
	}

	public Integer getMaxCheckAttempts() {
		return this.maxCheckAttempts;
	}

	public void setMaxCheckAttempts(Integer maxCheckAttempts) {
		this.maxCheckAttempts = maxCheckAttempts;
	}

	public Integer getState() {
		return this.state;
	}

	public void setState(Integer state) {
		this.state = state;
	}

	public Integer getStateType() {
		return this.stateType;
	}

	public void setStateType(Integer stateType) {
		this.stateType = stateType;
	}

	public String getStartTime() {
		return this.startTime;
	}

	public void setStartTime(String startTime) {
		this.startTime = startTime;
	}

	public String getEndTime() {
		return this.endTime;
	}

	public void setEndTime(String endTime) {
		this.endTime = endTime;
	}

	public Integer getCommandId() {
		return this.commandId;
	}

	public void setCommandId(Integer commandId) {
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

	public Integer getTimeout() {
		return this.timeout;
	}

	public void setTimeout(Integer timeout) {
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

	public Integer getReturnCode() {
		return this.returnCode;
	}

	public void setReturnCode(Integer returnCode) {
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
				+ ((serviceCheckId == null) ? 0 : serviceCheckId.hashCode());
		result = prime * result
				+ ((serviceId == null) ? 0 : serviceId.hashCode());
		result = prime * result
				+ ((startTime == null) ? 0 : startTime.hashCode());
		result = prime * result + ((state == null) ? 0 : state.hashCode());
		result = prime * result
				+ ((stateType == null) ? 0 : stateType.hashCode());
		result = prime * result + ((timeout == null) ? 0 : timeout.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorServiceCheck))
			return false;
		AbstractMonitorServiceCheck other = (AbstractMonitorServiceCheck) obj;
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
		if (serviceCheckId == null) {
			if (other.serviceCheckId != null)
				return false;
		} else if (!serviceCheckId.equals(other.serviceCheckId))
			return false;
		if (serviceId == null) {
			if (other.serviceId != null)
				return false;
		} else if (!serviceId.equals(other.serviceId))
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
		if (timeout == null) {
			if (other.timeout != null)
				return false;
		} else if (!timeout.equals(other.timeout))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorServiceCheck [checkType=" + checkType
				+ ", commandArgs=" + commandArgs + ", commandId=" + commandId
				+ ", commandLine=" + commandLine + ", currentCheckAttempt="
				+ currentCheckAttempt + ", endTime=" + endTime
				+ ", executionTime=" + executionTime + ", latency=" + latency
				+ ", maxCheckAttempts=" + maxCheckAttempts + ", output="
				+ output + ", perfdata=" + perfdata + ", returnCode="
				+ returnCode + ", serviceCheckId=" + serviceCheckId
				+ ", serviceId=" + serviceId + ", startTime=" + startTime
				+ ", state=" + state + ", stateType=" + stateType
				+ ", timeout=" + timeout + "]";
	}

}