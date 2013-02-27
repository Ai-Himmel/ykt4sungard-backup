package com.kingstargroup.form;

import java.math.BigDecimal;

/**
 * AbstractDeviceservice entity provides the base persistence definition of the
 * Deviceservice entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractDeviceservice implements java.io.Serializable {

	// Fields

	private String id;
	private String devicestatusid;
	private String rcvman;
	private String rcvtime;
	private long dealstatus;
	private String dealmark;

	// Constructors

	/** default constructor */
	public AbstractDeviceservice() {
	}

	/** full constructor */
	public AbstractDeviceservice(String devicestatusid, String rcvman,
			String rcvtime, long dealstatus, String dealmark) {
		this.devicestatusid = devicestatusid;
		this.rcvman = rcvman;
		this.rcvtime = rcvtime;
		this.dealstatus = dealstatus;
		this.dealmark = dealmark;
	}

	// Property accessors

	public String getId() {
		return this.id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getDevicestatusid() {
		return this.devicestatusid;
	}

	public void setDevicestatusid(String devicestatusid) {
		this.devicestatusid = devicestatusid;
	}

	public String getRcvman() {
		return this.rcvman;
	}

	public void setRcvman(String rcvman) {
		this.rcvman = rcvman;
	}

	public String getRcvtime() {
		return this.rcvtime;
	}

	public void setRcvtime(String rcvtime) {
		this.rcvtime = rcvtime;
	}

	public long getDealstatus() {
		return this.dealstatus;
	}

	public void setDealstatus(long dealstatus) {
		this.dealstatus = dealstatus;
	}

	public String getDealmark() {
		return this.dealmark;
	}

	public void setDealmark(String dealmark) {
		this.dealmark = dealmark;
	}

}