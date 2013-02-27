package org.king.monitor.domain;

/**
 * MapSerialostTableId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapSerialostTableId extends AbstractMapSerialostTableId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapSerialostTableId() {
	}

	/** full constructor */
	public MapSerialostTableId(String analysistime, long serialNo,
			String deviceId) {
		super(analysistime, serialNo, deviceId);
	}

}
