package org.king.monitor.domain;

/**
 * MapAlertTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapAlertTable extends AbstractMapAlertTable implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapAlertTable() {
	}

	/** full constructor */
	public MapAlertTable(String parameter, String name, long phonealert,
			long mailalert, long note) {
		super(parameter, name, phonealert, mailalert, note);
	}

}
