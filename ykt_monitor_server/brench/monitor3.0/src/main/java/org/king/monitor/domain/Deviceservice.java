package org.king.monitor.domain;

import java.math.BigDecimal;

/**
 * Deviceservice entity. @author MyEclipse Persistence Tools
 */
public class Deviceservice extends AbstractDeviceservice implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public Deviceservice() {
	}

	/** full constructor */
	public Deviceservice(String devicestatusid, String rcvman, String rcvtime,
			long dealstatus, String dealmark) {
		super(devicestatusid, rcvman, rcvtime, dealstatus, dealmark);
	}

}
