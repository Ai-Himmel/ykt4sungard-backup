package org.king.monitor.domain;

import java.math.BigDecimal;

/**
 * Devicefilter entity. @author MyEclipse Persistence Tools
 */
public class Devicefilter extends AbstractDevicefilter implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public Devicefilter() {
	}

	/** full constructor */
	public Devicefilter(String userid, long deviceid,
			String filtertotime, String remark, long status) {
		super(userid, deviceid, filtertotime, remark, status);
	}

}
