package org.king.monitor.domain;

/**
 * MapContactMonitorTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapContactMonitorTable extends AbstractMapContactMonitorTable
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapContactMonitorTable() {
	}

	/** full constructor */
	public MapContactMonitorTable(String contactname, String monitorno,
			String monitorname) {
		super(contactname, monitorno, monitorname);
	}

}
