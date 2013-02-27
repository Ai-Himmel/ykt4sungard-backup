package org.king.monitor.domain;

/**
 * MapSerialostTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapSerialostTable extends AbstractMapSerialostTable implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapSerialostTable() {
	}

	/** minimal constructor */
	public MapSerialostTable(MapSerialostTableId id, String txDate,
			String txTime, long serialReason, long serialStatus) {
		super(id, txDate, txTime, serialReason, serialStatus);
	}

	/** full constructor */
	public MapSerialostTable(MapSerialostTableId id, String txDate,
			String txTime, String contactname, long serialReason,
			long serialStatus) {
		super(id, txDate, txTime, contactname, serialReason, serialStatus);
	}

}
