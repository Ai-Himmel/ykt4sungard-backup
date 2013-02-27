package com.kingstargroup.form;

import java.math.BigDecimal;

/**
 * AbstractDevicefilter entity provides the base persistence definition of the
 * Devicefilter entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractDevicefilter implements java.io.Serializable {

	// Fields

	private String id;
	private String userid;
	private long deviceid;
	private String filtertotime;
	private String remark;
	private long status;

	// Constructors

	/** default constructor */
	public AbstractDevicefilter() {
	}

	/** full constructor */
	public AbstractDevicefilter(String userid, long deviceid,
			String filtertotime, String remark, long status) {
		this.userid = userid;
		this.deviceid = deviceid;
		this.filtertotime = filtertotime;
		this.remark = remark;
		this.status = status;
	}

	// Property accessors

	public String getId() {
		return this.id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getUserid() {
		return this.userid;
	}

	public void setUserid(String userid) {
		this.userid = userid;
	}

	public long getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(long deviceid) {
		this.deviceid = deviceid;
	}

	public String getFiltertotime() {
		return this.filtertotime;
	}

	public void setFiltertotime(String filtertotime) {
		this.filtertotime = filtertotime;
	}

	public String getRemark() {
		return this.remark;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

	public long getStatus() {
		return this.status;
	}

	public void setStatus(long status) {
		this.status = status;
	}

}