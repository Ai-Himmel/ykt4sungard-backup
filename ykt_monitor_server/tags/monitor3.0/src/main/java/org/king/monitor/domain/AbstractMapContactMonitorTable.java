package org.king.monitor.domain;

/**
 * AbstractMapContactMonitorTable entity provides the base persistence
 * definition of the MapContactMonitorTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapContactMonitorTable implements
		java.io.Serializable {

	// Fields

	private long id;
	private String contactname;
	private String monitorno;
	private String monitorname;

	// Constructors

	/** default constructor */
	public AbstractMapContactMonitorTable() {
	}

	/** full constructor */
	public AbstractMapContactMonitorTable(String contactname, String monitorno,
			String monitorname) {
		this.contactname = contactname;
		this.monitorno = monitorno;
		this.monitorname = monitorname;
	}

	// Property accessors

	public long getId() {
		return this.id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public String getContactname() {
		return this.contactname;
	}

	public void setContactname(String contactname) {
		this.contactname = contactname;
	}

	public String getMonitorno() {
		return this.monitorno;
	}

	public void setMonitorno(String monitorno) {
		this.monitorno = monitorno;
	}

	public String getMonitorname() {
		return this.monitorname;
	}

	public void setMonitorname(String monitorname) {
		this.monitorname = monitorname;
	}

}