package com.kingstargroup.form;

import java.math.BigDecimal;

/**
 * Deviceworktime entity. @author MyEclipse Persistence Tools
 */
public class Deviceworktime extends AbstractDeviceworktime implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public Deviceworktime() {
	}

	/** minimal constructor */
	public Deviceworktime(long deviceid) {
		super(deviceid);
	}

	/** full constructor */
	public Deviceworktime(long deviceid, String devicename,
			String starttime, String endtime) {
		super(deviceid, devicename, starttime, endtime);
	}

}
