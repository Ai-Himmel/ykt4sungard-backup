package org.king.monitor.domain;

import java.math.BigDecimal;

/**
 * AbstractDeviceworktime entity provides the base persistence definition of the
 * Deviceworktime entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractDeviceworktime implements java.io.Serializable {

	// Fields

	private long deviceid;
	private String devicename;
	private String starttime;
	private String endtime;

	// Constructors

	/** default constructor */
	public AbstractDeviceworktime() {
	}

	/** minimal constructor */
	public AbstractDeviceworktime(long deviceid) {
		this.deviceid = deviceid;
	}

	/** full constructor */
	public AbstractDeviceworktime(long deviceid, String devicename,
			String starttime, String endtime) {
		this.deviceid = deviceid;
		this.devicename = devicename;
		this.starttime = starttime;
		this.endtime = endtime;
	}

	// Property accessors

	public long getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(long deviceid) {
		this.deviceid = deviceid;
	}

	public String getDevicename() {
		return this.devicename;
	}

	public void setDevicename(String devicename) {
		this.devicename = devicename;
	}

	public String getStarttime() {
		return this.starttime;
	}

	public void setStarttime(String starttime) {
		this.starttime = starttime;
	}

	public String getEndtime() {
		return this.endtime;
	}

	public void setEndtime(String endtime) {
		this.endtime = endtime;
	}

}