package org.king.monitor.domain;

/**
 * MapDeviceTableId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapDeviceTableId extends AbstractMapDeviceTableId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapDeviceTableId() {
	}

	/** full constructor */
	public MapDeviceTableId(String analysistime, long deviceid) {
		super(analysistime, deviceid);
	}

}
