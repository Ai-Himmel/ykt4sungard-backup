package org.king.support.domain;

/**
 * AbstractMonitorCommands entity provides the base persistence definition of
 * the MonitorCommands entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorCommands extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer commandId;
	private Integer configType;
	private String commandName;
	private String commandLine;

	// Constructors

	/** default constructor */
	public AbstractMonitorCommands() {
	}

	/** full constructor */
	public AbstractMonitorCommands(Integer configType, String commandName,
			String commandLine) {
		this.configType = configType;
		this.commandName = commandName;
		this.commandLine = commandLine;
	}

	// Property accessors

	public Integer getCommandId() {
		return this.commandId;
	}

	public void setCommandId(Integer commandId) {
		this.commandId = commandId;
	}

	public Integer getConfigType() {
		return this.configType;
	}

	public void setConfigType(Integer configType) {
		this.configType = configType;
	}

	public String getCommandName() {
		return this.commandName;
	}

	public void setCommandName(String commandName) {
		this.commandName = commandName;
	}

	public String getCommandLine() {
		return this.commandLine;
	}

	public void setCommandLine(String commandLine) {
		this.commandLine = commandLine;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((commandId == null) ? 0 : commandId.hashCode());
		result = prime * result
				+ ((commandLine == null) ? 0 : commandLine.hashCode());
		result = prime * result
				+ ((commandName == null) ? 0 : commandName.hashCode());
		result = prime * result
				+ ((configType == null) ? 0 : configType.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorCommands))
			return false;
		AbstractMonitorCommands other = (AbstractMonitorCommands) obj;
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
		if (commandName == null) {
			if (other.commandName != null)
				return false;
		} else if (!commandName.equals(other.commandName))
			return false;
		if (configType == null) {
			if (other.configType != null)
				return false;
		} else if (!configType.equals(other.configType))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorCommands [commandId=" + commandId
				+ ", commandLine=" + commandLine + ", commandName="
				+ commandName + ", configType=" + configType + "]";
	}

}