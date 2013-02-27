package org.king.support.domain;

/**
 * MonitorRuntimevariables entity. @author MyEclipse Persistence Tools
 */
public class MonitorRuntimevariables extends AbstractMonitorRuntimevariables
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorRuntimevariables() {
	}

	/** full constructor */
	public MonitorRuntimevariables(String varname, String varnameZh,
			String varvalue) {
		super(varname, varnameZh, varvalue);
	}

}
