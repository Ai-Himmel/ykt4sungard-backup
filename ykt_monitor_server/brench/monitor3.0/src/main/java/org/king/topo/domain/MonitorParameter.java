package org.king.topo.domain;


/**
 * MonitorParameter entity. @author MyEclipse Persistence Tools
 */
public class MonitorParameter extends AbstractMonitorParameter implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorParameter() {
	}

	/** full constructor */
	public MonitorParameter(String parameter, String parametervalue,
			String parametername, String parameterunit) {
		super(parameter, parametervalue, parametername, parameterunit);
	}

}
