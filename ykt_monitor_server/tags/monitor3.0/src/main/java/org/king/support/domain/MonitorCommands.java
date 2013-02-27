package org.king.support.domain;


/**
 * MonitorCommands entity. @author MyEclipse Persistence Tools
 */
public class MonitorCommands extends AbstractMonitorCommands implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorCommands() {
	}

	/** full constructor */
	public MonitorCommands(Integer configType, String commandName,
			String commandLine) {
		super(configType, commandName, commandLine);
	}

}
